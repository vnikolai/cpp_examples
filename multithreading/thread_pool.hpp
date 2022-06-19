#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>

const int num_threads = std::thread::hardware_concurrency();
const auto timeout = std::chrono::microseconds(10);

class thread_pool
{
public:
    thread_pool( )
    {
    }

    ~thread_pool( )
    {
        stop();
    }

    void run( )
    {
        if ( m_running ) return;

        m_running = true;

        for ( int i = 0; i < num_threads; ++i )
        {
            m_threads.push_back( std::thread( &thread_pool::worker_thread, this ) );
        }

    }

    void stop( )
    {
        if ( !m_running ) return;

        wait();

        m_running = false;
        m_task_ready.notify_all( );

        for ( auto& thread : m_threads )
        {
            if ( thread.joinable( ) )
            {
                thread.join( );
            }
        }
    }

    void push( std::function< void(void) > function )
    {
        if ( function )
        {
            {
                std::unique_lock< std::mutex > lock( m_task_queue_lock );
                m_task_queue.push( function );
            }

            m_task_ready.notify_one( );
        }
    }

    void wait( )
    {
        if ( !m_running )
        {
            return;
        }

        while ( true )
        {
            std::unique_lock< std::mutex > lock( m_task_queue_lock );
            if ( m_task_queue.empty( ) )
            {
                break;
            }

            lock.unlock( );
            std::this_thread::yield( );
        }
    }

private:
    bool fetch_task( std::function<void(void)>& function )
    {
        if (!m_task_queue.empty())
        {
            function = std::move(m_task_queue.front());
            m_task_queue.pop();
            return true;
        }

        return false;
    }

    void worker_thread( )
    {
        while ( m_running )
        {
            std::unique_lock< std::mutex > guard( m_task_queue_lock );
            m_task_ready.wait_for( guard, timeout, [&]( ) {
                return !m_task_queue.empty( ) || !m_running;
            } );

            if ( m_running && !m_task_queue.empty( ) )
            {
                std::function<void(void)> task;
                if ( fetch_task( task ) )
                {
                    guard.unlock( );

                    task( );
                }
            }
        }
    }

private:
    std::atomic_bool m_running = false;

    std::mutex m_task_queue_lock;
    std::queue< std::function<void(void)> > m_task_queue;
    std::condition_variable m_task_ready;

    std::vector< std::thread > m_threads;
};
