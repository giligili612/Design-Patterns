#include <iostream>
/**
 * 子系统可以接受来自外观或客户端的请求。
 */
class Subsystem1 {
public:
    std::string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    std::string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};
/**
 * 外观可以同时与多个子系统一起工作。
 */
class Subsystem2 {
public:
    std::string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    std::string OperationZ() const {
        return "Subsystem2: Fire!\n";
    } 
};
/**
 * 外观类提供了一个简单的接口，用于对子系统的复杂逻辑进行封装。
 * 外观将客户端的请求委托给子系统中的适当对象。
 * 外观还负责管理它们的生命周期。
 * 所有这些都使客户端免受子系统的不想要的复杂性的影响。
 */
class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
public:
    Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) :
    subsystem1_(subsystem1 ? subsystem1 : new Subsystem1),
    subsystem2_(subsystem2 ? subsystem2 : new Subsystem2)
    {} 
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ(); 
        return result;
    }
};
// 另一个外观类
// 可以定制多个外观类来满足不同的需求。
class AnotherFacade : public Facade {
public:
    AnotherFacade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) : 
    Facade(subsystem1, subsystem2) {}
    std::string Another_Operation() {
        std::string result = "AnotherFacade initializes subsystems:\n";
        result += this->Operation();
        result += "AnotherFacade orders subsystems to perform the action:\n";
        result += this->subsystem2_->OperationZ();
        result += this->subsystem1_->OperationN();
        return result;
    }
};

void ClientCode(Facade* facade) {
    std::cout << facade->Operation(); 
}

int main() {
    Facade* facade = new Facade(new Subsystem1, new Subsystem2);
    ClientCode(facade);
    delete facade; 
    std::cout << "\n";
    AnotherFacade* another_facade = new AnotherFacade(new Subsystem1, new Subsystem2);
    std::cout << another_facade->Another_Operation();
    delete another_facade;
    return 0;
}