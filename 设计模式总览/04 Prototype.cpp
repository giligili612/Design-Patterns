#include <functional>
#include <iostream>
#include <unordered_map>

using std::string;
/**
 * 原型设计模式
 * 原型模式是一种创建型设计模式，它允许通过复制现有对象来创建新对象，而无需依赖于其类。
 * 这种模式通常用于创建复杂对象，这些对象的创建过程可能非常耗时或复杂，因此通过复制现有对象来创建新对象可以提高性能。
 * 原型模式通常包含以下几个角色：
 * 1. 原型（Prototype）：定义了一个接口，用于复制自身。
 * 2. 具体原型（Concrete Prototype）：实现了原型接口，用于复制自身。
 * 3. 客户端（Client）：使用原型接口来创建新对象。
 */
enum Type{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype{
protected:
    string prototype_name_;
    float protptype_field_;

public:
    Prototype(){}
    Prototype(string prototype_name):prototype_name_(prototype_name){}
    virtual ~Prototype(){}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float prototype_field){
        this->protptype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }
};

class ConcretePrototype1 : public Prototype{
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field) : 
    Prototype(prototype_name), 
    concrete_prototype_field1_(concrete_prototype_field){}

    Prototype* Clone() const override{
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype{
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field) : 
    Prototype(prototype_name), 
    concrete_prototype_field2_(concrete_prototype_field){}

    Prototype* Clone() const override{
        return new ConcretePrototype2(*this);
    }
};
/**
 * 原型工厂
 * 原型工厂存储了原型的实例，客户端可以通过原型工厂来创建原型的实例。
 * 需要某种原型的克隆时，客户端可以通过原型工厂来获取原型的实例，然后调用克隆方法来创建新的实例。
 */
class PrototypeFactory{
private:
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;

public:
    PrototypeFactory(){
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.0f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 60.0f);
    }

    ~PrototypeFactory(){
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type){
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory){
   std::cout << "Let's create a Prototype 1\n";
   
   Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
   prototype->Method(90.0f);
   // 客户端需要负责释放原型的内存
   delete prototype;
   std::cout << '\n';

   std::cout << "Let's create a Prototype 2\n";
   prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
   prototype->Method(100.0f);
   delete prototype;
   
}
int main(){
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory; 
    return 0;
}