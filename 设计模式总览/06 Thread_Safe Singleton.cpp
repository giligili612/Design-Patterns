#include <iostream>
#include <thread>
#include <mutex>
/**
 * 单例类定义了GetInstance方法，该方法向客户端隐藏了构造函数，同时允许客户端访问相同的实例。
 * 单例类的构造函数应该始终是私有的，以防止直接使用new运算符进行构造调用。
 * 单例类不应被克隆。
 * 单例类不应被赋值。
 * 线程安全的单例类有静态锁和静态字段。
 * 静态锁用于保护静态字段。
 * 静态字段用于存储单例类的实例。
 * 静态方法用于控制对单例类实例的访问。
 */
class Singleton{
private:
    static std::mutex mutex_;
    // 静态字段标志单例类是否已经被实例化。
    static Singleton* singleton_;
protected:
    Singleton(const std::string value): value_(value) {};
    
    std::string value_;
public:
    Singleton(Singleton& other) = delete;
    Singleton& operator=(Singleton& other) = delete;
    static Singleton* GetInstance(const std::string& value);
    void SomeBusinessLogic() {std::cout << "SomeBusinessLogic" << std::endl;};
    std::string value() const {return value_;};
};

Singleton* Singleton::singleton_ = nullptr;
std::mutex Singleton::mutex_;
/**
 * 静态方法应该在类外定义。
 * GetInstance方法向客户端隐藏了调用私有构造函数的细节。
 * 让客户端能够访问相同的实例。
 * 返回静态字段
 */
 // 该方法是线程安全的，因为它使用了互斥锁来保护对静态字段的访问。
Singleton* Singleton::GetInstance(const std::string &value){
    // 使用整个类的互斥锁来保护对静态字段的访问。
    // 这确保了只有一个线程可以访问静态字段。
    // lock_guard是一个RAII类，它在构造函数中获取互斥锁，并在析构函数中释放互斥锁。
    // 出作用域后，lock_guard会自动释放互斥锁。
    std::lock_guard<std::mutex> lock(mutex_);
    if (singleton_ == nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << std::endl;
}

void ThreadBar(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << std::endl; 
}

int main(){
    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n"; 
    std::thread t1(ThreadBar);
    std::thread t2(ThreadFoo);
    t1.join();
    t2.join();
    return 0;
}