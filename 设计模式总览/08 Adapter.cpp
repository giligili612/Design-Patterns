#include <iostream>
#include <algorithm>
/**
 * Target类定义了客户端代码所期望的接口。
 */
class Target {
public:
	virtual ~Target() = default;

    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

/**
 * Adaptee类包含一些有用的行为，但其接口与现有客户端代码不兼容。
 * 因此，Adaptee需要进行一些调整才能与客户端代码一起使用。
 */
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }	
};
/**
 * Adapter类使Adaptee的接口与Target的接口兼容。
 * Adapter类继承自Target类，并包含一个指向Adaptee对象的指针。
 * 在Adapter类的Request方法中，它调用Adaptee对象的SpecificRequest方法，并对其结果进行一些处理。
 * 这样，客户端代码就可以使用Adapter对象来调用Adaptee对象的方法，而不需要对其进行任何修改。
 */
class Adapter : public Target {
private:
    Adaptee *adaptee_;	
public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

void Client(const Target* target){
    std::cout << target->Request();
}

int main() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    Client(target);
    std::cout << "\n\n";
    // 直接调用Adaptee的方法
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    // 调用Adapter的方法
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    Client(adapter);
    std::cout << '\n';
    delete target;
    delete adaptee;
    delete adapter;

	return 0;
}