#include <iostream>
#include <thread>
/**
 * 单例类定义了GetInstance方法，该方法向客户端隐藏了构造函数，同时允许客户端访问相同的实例。
 * 单例类的构造函数应该始终是私有的，以防止直接使用new运算符进行构造调用。
 * 单例类不应被克隆。
 * 单例类不应被赋值。
 */
class Singleton{
protected:
    Singleton(const std::string value): value_(value) {};
    // 静态字段标志单例类是否已经被实例化。
    static Singleton* singleton_;
    std::string value_;
public:
    Singleton(Singleton& other) = delete;
    Singleton& operator=(Singleton& other) = delete;
    static Singleton* GetInstance(const std::string& value);
    void SomeBusinessLogic() {std::cout << "SomeBusinessLogic" << std::endl;};
    std::string value() const {return value_;};
};

Singleton* Singleton::singleton_ = nullptr;
/**
 * 静态方法应该在类外定义。
 * GetInstance方法向客户端隐藏了调用私有构造函数的细节。
 * 让客户端能够访问相同的实例。
 * 返回静态字段
 */
 // 该方法不是线程安全的，在多线程环境下可能会创建多个实例。
Singleton* Singleton::GetInstance(const std::string &value){
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
// 如果输出结果相同，则单例模式工作正常。
// 如果输出结果不同，是因为上面的代码是线程不安全的
// t1,t2可能同时执行到if (singleton_ == nullptr)，导致创建多个实例。
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