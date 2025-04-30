#include <iostream>
/**
 * 每一种产品都应该有一个基础接口。
 * 所有的产品变体都必须实现这个接口。
 */
class AbstractProductA{
public:
    virtual ~AbstractProductA(){};
    virtual std::string UsefulFunctionA() const = 0;
};
/**
 * 具体的产品由相应的具体工厂创建。
 */
class ConcreteProductA1 : public AbstractProductA{
public:
    std::string UsefulFunctionA() const override{
        return "Product A1";
    }
};

class ConcreteProductA2 : public AbstractProductA{
public:
    std::string UsefulFunctionA() const override{
        return "Product A2";
    } 
};

class AbstractProductB{
public:
    virtual ~AbstractProductB(){};
    virtual std::string UsefulFunctionB() const = 0;
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0; 
};

class ConcreteProductB1 : public AbstractProductB{
public:
    std::string UsefulFunctionB() const override{
        return "Product B1";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        const std::string result = collaborator.UsefulFunctionA();
        return "B1 collaborates with the ( " + result + " )";     
    } 
};

class ConcreteProductB2 : public AbstractProductB{
public:
    std::string UsefulFunctionB() const override{
        return "Product B2";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override{
        const std::string result = collaborator.UsefulFunctionA();
        return "B2 collaborates with the ( " + result + " )";     
    } 
};

/**
 * 一个抽象工厂类可以创建一个产品家族。
 * 每个具体的工厂类都可以创建一个特定的产品家族。
 * 一个产品家族包含不同种类的产品。
 * 设计上，一个产品家族内的产品通常是相互兼容、可以互动的。
 * 不同产品家族内的产品通常是不兼容也不互动的。
 */
class AbstractFactory{
public:
    virtual ~AbstractFactory(){};
    virtual AbstractProductA *CreateProductA() const = 0;
    virtual AbstractProductB *CreateProductB() const = 0; 
};

class ConcreteFactory1 : public AbstractFactory{
public:
    AbstractProductA *CreateProductA() const override{
        return new ConcreteProductA1();
    }
    AbstractProductB *CreateProductB() const override{
        return new ConcreteProductB1();
    } 
};

class ConcreteFactory2 : public AbstractFactory{
public:
    AbstractProductA *CreateProductA() const override{
        return new ConcreteProductA2();
    }
    AbstractProductB *CreateProductB() const override{
        return new ConcreteProductB2();
    } 
};

/**
 * 客户端代码只与抽象工厂和抽象产品交互。
 */
void ClientCode(const AbstractFactory &factory){
    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    std::cout << product_a->UsefulFunctionA() << "\n";
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

/**
 * 下面的代码先测试一个产品家族，然后测试另一个产品家族。
 */
int main(){
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *factory1 = new ConcreteFactory1();
    ClientCode(*factory1);
    delete factory1;
    std::cout << "\n";
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *factory2 = new ConcreteFactory2();
    ClientCode(*factory2);
    delete factory2;
    return 0;
}