#include <iostream>
#include <vector>
/**
 * 在产品非常复杂并且需要 extensive configuration 的情况下，
 * 可以使用 Builder 模式。
 * 与其他创建型模式不同，不同的具体构建器可以产生不相关的产品。
 * 换句话说，不同的构建器可能会产生不遵循相同接口的产品。
 */
class Product1{
public:
    std::vector<std::string> parts_;
    void ListParts()const{
        std::cout << "Product parts: ";
        for(size_t i = 0; i < parts_.size(); i++){
            if(parts_[i] == parts_.back()){
                std::cout << parts_[i];
            }else{
                std::cout << parts_[i] << ", ";
            }
        }
    }
};
/**
 * 构建器接口指定创建产品不同部分的方法。
 */
class Builder{
public:
    virtual ~Builder(){};
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};
/**
 * 具体构建器类遵循构建器接口并提供构建步骤的特定实现。
 * 你的程序可能有几个不同的构建器，实现方式不同。
 * 对于构建器接口提供的所有方法
 * 具体构建器可以选择性地实现它们。
 */
class ConcreteBuilder1 : public Builder{
private:
    Product1* product;
public:
    ConcreteBuilder1(){
        this->Reset();
    }
    ~ConcreteBuilder1(){
        delete product; 
    }
    void Reset(){
        this->product = new Product1();
    }

    void ProducePartA() const override{
        this->product->parts_.push_back("PartA1");
    }
    void ProducePartB() const override{
        this->product->parts_.push_back("PartB1");
    }
    void ProducePartC() const override{
        this->product->parts_.push_back("PartC1");
    }

    Product1* GetProduct(){
        return this->product; 
    }
};
/**
 * 导演类定义了构建步骤的顺序。
 * 它通过实现的不同方法允许创建不同类型的产品。
 */
class Director{
private:
    Builder* builder; 
public:
    void SetBuilder(Builder* builder){
        this->builder = builder;  
    }
    // 基本类型的产品
    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }
    // 完整的类型的产品
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};
/**
 * 客户端代码创建一个构建器对象，将其传递给导演，并启动构建过程。
 * 最终结果从构建器对象中获取。
 */
void ClientCode(Director& director){
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.SetBuilder(builder);
    std::cout << "Standard basic product: \n";
    director.BuildMinimalViableProduct();
    builder->GetProduct()->ListParts();
    std::cout << "\n------------------------------------------\n"; 

    std::cout << "Standard full featured product: \n";
    ConcreteBuilder1* builder2 = new ConcreteBuilder1();
    director.SetBuilder(builder2);
    director.BuildFullFeaturedProduct();
    builder2->GetProduct()->ListParts();
    std::cout << "\n------------------------------------------\n";

    delete builder;
    delete builder2;
}

int main(){
    Director* director = new Director();
    ClientCode(*director);
    delete director; 
    return 0;
}

