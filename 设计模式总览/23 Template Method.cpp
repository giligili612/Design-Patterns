#include <iostream>  // 用于输入输出流操作

/**
 * 抽象类定义了一个模板方法，其中包含某个算法的骨架，
 * 该算法由对（通常）抽象原始操作的调用组成。
 *
 * 具体子类应实现这些操作，但保持模板方法本身不变。
 */
class AbstractClass {
  /**
   * 模板方法定义了算法的骨架。
   */
 public:
  void TemplateMethod() const {
    this->BaseOperation1();
    this->RequiredOperations1();
    this->BaseOperation2();
    this->Hook1();
    this->RequiredOperation2();
    this->BaseOperation3();
    this->Hook2();
  }
  /**
   * 这些操作已经有实现。
   */
 protected:
  void BaseOperation1() const {
    std::cout << "AbstractClass says: I am doing the bulk of the work\n";
  }
  void BaseOperation2() const {
    std::cout << "AbstractClass says: But I let subclasses override some operations\n";
  }
  void BaseOperation3() const {
    std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
  }
  /**
   * 这些操作必须在子类中实现。
   */
  virtual void RequiredOperations1() const = 0;
  virtual void RequiredOperation2() const = 0;
  /**
   * 这些是"钩子"。子类可以重写它们，但不是强制性的，
   * 因为钩子已经有默认（但为空）的实现。
   * 钩子在算法的一些关键位置提供了额外的扩展点。
   */
  virtual void Hook1() const {}
  virtual void Hook2() const {}
};

/**
 * 具体类必须实现基类的所有抽象操作。
 * 它们也可以用默认实现覆盖一些操作。
 */
class ConcreteClass1 : public AbstractClass {
 protected:
  void RequiredOperations1() const override {
    std::cout << "ConcreteClass1 says: Implemented Operation1\n";
  }
  void RequiredOperation2() const override {
    std::cout << "ConcreteClass1 says: Implemented Operation2\n";
  }
};

/**
 * 通常，具体类只覆盖基类操作的一部分。
 */
class ConcreteClass2 : public AbstractClass {
 protected:
  void RequiredOperations1() const override {
    std::cout << "ConcreteClass2 says: Implemented Operation1\n";
  }
  void RequiredOperation2() const override {
    std::cout << "ConcreteClass2 says: Implemented Operation2\n";
  }
  void Hook1() const override {
    std::cout << "ConcreteClass2 says: Overridden Hook1\n";
  }
};

/**
 * 客户端代码调用模板方法来执行算法。
 * 客户端代码不必知道它所使用的对象的具体类，
 * 只要它通过基类的接口与对象一起工作即可。
 */
void ClientCode(AbstractClass *class_) {
  // ...
  class_->TemplateMethod();
  // ...
}

int main() {
  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass1 *concreteClass1 = new ConcreteClass1;
  ClientCode(concreteClass1);
  std::cout << "\n";
  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass2 *concreteClass2 = new ConcreteClass2;
  ClientCode(concreteClass2);
  delete concreteClass1;
  delete concreteClass2;
  return 0;
}