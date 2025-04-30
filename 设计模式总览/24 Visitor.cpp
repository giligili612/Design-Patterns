#include <iostream>  // 用于输入输出流操作
#include <array>     // 用于 std::array

/**
 * 访问者接口声明了一组与组件类相对应的访问方法。
 * 访问方法的签名允许访问者识别它所处理的组件的确切类。
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

/**
 * 组件接口声明了一个`accept`方法，该方法应接受基础访问者接口作为参数。
 */

class Component {
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

/**
 * 每个具体组件都必须以这样一种方式实现`Accept`方法，
 * 即它调用与组件类相对应的访问者方法。
 */
class ConcreteComponentA : public Component {
    /**
     * 请注意，我们正在调用`visitConcreteComponentA`，这与
     * 当前类名相匹配。通过这种方式，我们让访问者知道它所处理的组件的类。
     */
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    /**
     * 具体组件可能有其基类或接口中不存在的特殊方法。
     * 访问者仍然能够使用这些方法，因为它知道组件的具体类。
     */
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public Component {
    /**
     * 这里也是一样：visitConcreteComponentB => ConcreteComponentB
     */
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const {
        return "B";
    }
};

/**
 * 具体访问者实现了同一算法的多个版本，这些版本可以
 * 与所有具体组件类一起使用。
 *
 * 当在复杂的对象结构（如组合树）中使用访问者模式时，
 * 你可以体验到它的最大好处。在这种情况下，
 * 在对结构中的各种对象执行访问者方法时存储算法的一些中间状态可能会有所帮助。
 */
class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};

/**
 * 客户端代码可以在任何元素集上运行访问者操作，而无需
 * 弄清楚它们的具体类。接受操作将调用定向到访问者对象中的适当操作。
 */
void ClientCode(std::array<const Component*, 2> components, Visitor* visitor) {
    //...
    for (const Component* comp : components) {
        comp->Accept(visitor);
    }
    //...
}

int main() {
    std::array<const Component*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}