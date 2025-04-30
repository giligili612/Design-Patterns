#include <iostream>
/**
 * 实现类接口定义了所有具体实现类的通用接口。
 * 它不需要与抽象接口匹配。
 * 实际上，两个具体实现接口可以完全不同。
 * 通常实现接口只提供原始操作，而抽象接口则基于这些原始操作定义更高层次的操作。
 */
class Implementation{
public:
    virtual ~Implementation(){};
    virtual std::string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation{
public:
    std::string OperationImplementation() const override{
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    } 
};

class ConcreteImplementationB : public Implementation{
public:
    std::string OperationImplementation() const override{
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    } 
};
/**
 * 抽象定义了实现层次结构的控制部分的接口。
 * 它保留了对实现层次结构对象的引用，并将所有真实工作委派给这个对象。
 */
class Abstraction{
protected:
    Implementation* implementation_;
public:
    Abstraction(Implementation* implementation) : implementation_(implementation){};
    virtual ~Abstraction(){};

    virtual std::string Operation() const{
        return "Abstraction: Base operation with:\n" + this->implementation_->OperationImplementation();
    }
};
/**
 * 你可以在不改变实现类的情况下扩展抽象。
 */
class ExtendedAbstraction : public Abstraction{
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation){}; 
    std::string Operation() const override{
        return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->OperationImplementation(); 
    }
};

void ClientCode(const Abstraction& abstraction){
    std::cout << abstraction.Operation();
}

int main(){
    Implementation* implementation = new ConcreteImplementationA();
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB();
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;
    return 0;
}