#include <iostream>
#include <thread>
#include <shared_mutex>

bool quit = false;

class Object
{
    public:
    
    void render(void* context)
    {
        m_shared_mutex.lock_shared();

        // render to context
        std::this_thread::sleep_for(std::chrono::microseconds(250));

        m_shared_mutex.unlock_shared();
    }

    void recalculate()
    {
        m_shared_mutex.lock();

        // update object data
        std::this_thread::sleep_for(std::chrono::microseconds(250));

        m_shared_mutex.unlock();
    }

    std::shared_mutex m_shared_mutex;
};

Object object;

int main(int argc, const char** argv)
{
    const int num_threads = 12;

    auto renderer = []{
        void* this_thread_context = nullptr;
        while (!quit)
        {
            object.render(this_thread_context);
        }
    };

    std::thread renderer1(renderer);
    std::thread renderer2(renderer);

    while (!quit)
    {
        object.recalculate();

        std::this_thread::sleep_for(std::chrono::microseconds(250));
    }

    renderer1.join();
    renderer2.join();

    return 0;
}
