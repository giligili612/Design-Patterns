#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <algorithm>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <iterator>

/**
 * 策略接口声明了所有支持的算法版本共有的操作。
 *
 * 上下文使用此接口调用具体策略定义的算法。
 */
 class Strategy
 {
 public:
     virtual ~Strategy() = default;
     virtual std::string doAlgorithm(std::string_view data) const = 0;
 };
 
 /**
  * 上下文定义了客户感兴趣的接口。
  */
 
 class Context
 {
     /**
      * @var Strategy 上下文维护对其中一个策略对象的引用。
      * 上下文不知道策略的具体类。它应该通过策略接口与所有策略一起工作。
      */
 private:
     std::unique_ptr<Strategy> strategy_;
     /**
      * 通常，上下文通过构造函数接受策略，但也提供了在运行时更改策略的设置器。
      */
 public:
     explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy))
     {
     }
     /**
      * 通常，上下文允许在运行时替换策略对象。
      */
     void set_strategy(std::unique_ptr<Strategy> &&strategy)
     {
         strategy_ = std::move(strategy);
     }
     /**
      * 上下文将一些工作委托给策略对象，而不是自己实现多个版本的算法。
      */
     void doSomeBusinessLogic() const
     {
         if (strategy_) {
             std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
             std::string result = strategy_->doAlgorithm("aecbd");
             std::cout << result << "\n";
         } else {
             std::cout << "Context: Strategy isn't set\n";
         }
     }
 };
 
 /**
  * 具体策略在遵循基础策略接口的同时实现算法。
  * 该接口使它们在上下文中可以互换。
  */
 class ConcreteStrategyA : public Strategy
 {
 public:
     std::string doAlgorithm(std::string_view data) const override
     {
         std::string result(data);
         std::sort(std::begin(result), std::end(result));
 
         return result;
     }
 };
 
 class ConcreteStrategyB : public Strategy
 {
 public: // 添加了访问修饰符
     std::string doAlgorithm(std::string_view data) const override
     {
         std::string result(data);
         std::sort(std::begin(result), std::end(result), std::greater<>());
 
         return result;
     }
 };
 
 /**
  * 客户端代码选择一个具体策略并将其传递给上下文。
  * 客户端应该了解策略之间的差异，以便做出正确的选择。
  */
 
 void clientCode()
 {
     Context context(std::make_unique<ConcreteStrategyA>());
     std::cout << "Client: Strategy is set to normal sorting.\n";
     context.doSomeBusinessLogic();
     std::cout << "\n";
     std::cout << "Client: Strategy is set to reverse sorting.\n";
     context.set_strategy(std::make_unique<ConcreteStrategyB>());
     context.doSomeBusinessLogic();
 }
 
 int main()
 {
     clientCode();
     return 0;
 }