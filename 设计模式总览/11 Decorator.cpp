#include <iostream>
/**
 * 基础组件接口定义了可以被装饰器修改的操作。
 * 具体组件、基础装饰器、具体装饰器都实现了这个接口。
 */
class Component {
public:
    virtual ~Component() {};
    virtual std::string Operation() const = 0;
};
/**
 * 具体组件提供了操作的默认实现。这些类通常会有一个用于存储基础组件的字段。
 * 基础组件的基础类通常会定义一个与其他组件接口兼容的接口。这样，你就可以
 * 始终将基础组件作为装饰器的基础组件。
 */
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    } 
};
/**
 * 基础装饰类遵循与其他组件相同的接口。该类的主要目的是定义所有具体装饰器的接口。
 * 基础装饰类也继承了基础组件的接口。
 */
class Decorator : public Component {
protected:
    Component* component_;
public:
    Decorator(Component* component) : component_(component) {};
    std::string Operation() const override {
        return this->component_->Operation();
    } 
};
// 具体装饰器重写了基础装饰器的方法，并在调用父方法之前或之后执行自己的行为。
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {};
    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    } 
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {};
    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    } 
};

void ClientCode(Component* component) {
    std::cout << "RESULT: " << component->Operation(); 
}

int main() {
    Component* simple = new ConcreteComponent();
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1); 
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";
    delete simple;
    delete decorator1;
    delete decorator2;
}