#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <map>

bool quit = false;

void log(const char* text)
{
    static std::mutex cout_mutex;
    std::lock_guard lock(cout_mutex);

    std::cout << text << std::endl;
}

class Object
{
    public:
        int register_listener(std::function<void(void)> listener)
        {
            std::lock_guard<decltype(m_listeners_mutex)> lock(m_listeners_mutex);
            int id = m_id++;
            m_listeners.emplace(id, listener);

            return id;
        }

        void remove_listener(int id)
        {
            std::lock_guard<decltype(m_listeners_mutex)> lock(m_listeners_mutex);
            auto it = m_listeners.find(id);
            if (it != m_listeners.end())
            {
                m_listeners.erase(it);
            }
        }

        void notify_listeners()
        {
            log("notify listeners");

            std::lock_guard<decltype(m_listeners_mutex)> lock(m_listeners_mutex);
            for (auto& listener : m_listeners)
            {
                listener.second();
            }
        }

        void notify_listeners_optimized()
        {
            log("notify listeners");

            m_listeners_mutex.lock();
            auto listeners = m_listeners;
            m_listeners_mutex.unlock();

            for (auto& listener : listeners)
            {
                listener.second();
            }
        }

    private:
        std::map<int, std::function<void(void)>> m_listeners;
        std::mutex m_listeners_mutex;
        int m_id = 0;
};


int main(int argc, const char** argv)
{
    Object object;

    std::thread notifier_thread([&object]{
        while (!quit)
        {
            object.notify_listeners();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    int id = 0;

    std::function<void(void)> listener = [&]{
        log("Listener function");
        //object.remove_listener(id);
    };

    id = object.register_listener(listener);

    notifier_thread.join();
    
    return 0;
}