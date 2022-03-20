#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class Singleton
{
public:
    static Singleton *GetInstance(const std::string& values);
    Singleton(Singleton &) = delete;
    Singleton operator=(const Singleton &) = delete;
    std::string value() const
    {
        return value_;
    }

protected:
    Singleton(std::string value) : value_(value){};
    ~Singleton() {};
    std::string value_;

private:
    static std::mutex mutex_;
    static Singleton *singleton_;
};

Singleton *Singleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (singleton_ == nullptr)
    {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}
std::mutex Singleton::mutex_;
Singleton *Singleton::singleton_{nullptr};




void ThreadFoo()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}
