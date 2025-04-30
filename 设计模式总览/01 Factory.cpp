#include <iostream>

/**
 * 抽象出的一般产品类提供了一个接口，所有具体产品都必须实现这个接口
 */

class Product{
public:
    virtual ~Product(){};
    virtual std::string Operation() const = 0;
};

class ConcreteProduct1 : public Product{
public:
    std::string Operation() const override{
        return "{ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product{
public:
    std::string Operation() const override{
        return "{ConcreteProduct2}";
    }
};

/**
 * 抽象出的一般创建者类提供了一个工厂方法，所有具体创建者都必须实现这个方法
 * 这个方法返回一个产品对象，所有具体创建者都必须实现这个方法
 * 此外，这个方法还可以提供一些默认的实现，这些实现可以被具体创建者覆盖
 * 创建者类不止提供一般的工厂方法，还提供其他方法供子类使用
 * 这些其他的方法一般是业务逻辑，视情况可以被具体创建者覆盖，也可以提供默认的实现
 */
class Creator{
public:
    virtual ~Creator(){};
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const{
        Product* product = this->FactoryMethod();
        std::string result = "Creator: just worked with " + product->Operation();
        delete product;
        return result;
    }
};
/**
 * 具体创建者类提供了一个工厂方法的实现，这个方法返回一个具体产品对象
 */
class ConcreteCreator1 : public Creator{
public:
    Product* FactoryMethod() const override{
        return new ConcreteProduct1();
    } 
};

class ConcreteCreator2 : public Creator{
public:
    Product* FactoryMethod() const override{
        return new ConcreteProduct2();
    } 
};
/**
 * 客户端代码可以使用任何具体创建者的实例，而无需关心具体创建者的类
 * 客户端代码只需要知道创建者类提供的接口即可
 * 客户端具体选择哪个创建者实例一般取决于配置文件、用户输入或者业务逻辑
 */
void ClientCode(const Creator& creator){
    std::cout << "Client: I'm not aware of the creator's class, I still work\n";
    std::cout << creator.SomeOperation() << std::endl;
}

int main(){
   std::cout << "App: Launched with the ConcreteCreator1.\n";
   Creator* creator = new ConcreteCreator1();
   ClientCode(*creator);
   std::cout << std::endl;
   std::cout << "App: Launched with the ConcreteCreator2.\n";
   Creator* creator2 = new ConcreteCreator2();
   ClientCode(*creator2);
   delete creator;
   delete creator2; 
}

