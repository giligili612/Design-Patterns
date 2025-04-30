#include <iostream>
#include <string>

class MagicSingleton {
public:
/**
 * C++11标准规定：如果控制流在变量初始化时同时进入声明，并发执行应等待初始化完成。
 * 这意味着，在多线程环境中，静态局部变量的初始化将是线程安全的，并且只会在第一次访问时执行一次。
 */
    static MagicSingleton& GetInstance(const std::string& value = "DEFAULT") {
        // 静态局部变量，只在第一次调用时初始化
        // 这确保了只有一个实例被创建，并且在整个程序生命周期内都是可用的。
        // 第二次调用GetInstance时，不会执行初始化，而是直接返回已存在的实例。
        static MagicSingleton instance(value);
        return instance;
    }

    void PrintValue() const {
        std::cout << "Value: " << value_ << std::endl;
    }

    // 删除拷贝构造和赋值
    MagicSingleton(const MagicSingleton&) = delete;
    MagicSingleton& operator=(const MagicSingleton&) = delete;

private:
    std::string value_;
    
    // 私有构造函数
    explicit MagicSingleton(const std::string& value) : value_(value) {
        std::cout << "Singleton initialized\n";
    }
    
    ~MagicSingleton() {
        std::cout << "Singleton destroyed\n";
    }
};

int main() {
    auto& s1 = MagicSingleton::GetInstance("First");
    auto& s2 = MagicSingleton::GetInstance("Second"); // 这行不会重新初始化
    
    s1.PrintValue(); // 输出 "First"
    s2.PrintValue(); // 同样输出 "First"
    
    return 0;
}