#include <iostream>
#include <vector>
/**
 * 处理者接口声明了所有具体处理者的通用方法。
 * 它还声明了一个方法来设置处理者的后继者。
 * 注意，处理者可以访问它的后继者，即使它是通过基本处理者接口设置的。
 * 这允许在运行时动态地组合处理者。
 */
class Handler{
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler{
private:
    Handler* next_handler_; 
public:
    AbstractHandler() : next_handler_(nullptr) {};
    // 可以设置后继者的方法
    Handler* SetNext(Handler* handler) override{
        this->next_handler_ = handler;
        return handler;
    }
    // 默认处理者方法：调用后继者的处理方法
    std::string Handle(std::string request) override{
        if(this->next_handler_){
            return this->next_handler_->Handle(request);
        }
        return {};
    }
};
// 具体处理者：实现了具体的处理逻辑
class MonkeyHandler : public AbstractHandler{
public:
    std::string Handle(std::string request) override{
        if(request == "Banana"){
            return "Monkey: I'll eat the " + request + ".\n";
        }else{
            return AbstractHandler::Handle(request);
        }
    } 
};

class SquirrelHandler : public AbstractHandler{
public:
    std::string Handle(std::string request) override{
        if(request == "Nut"){
            return "Squirrel: I'll eat the " + request + ".\n";
        }else{
            return AbstractHandler::Handle(request);
        }
    } 
};

class DogHandler : public AbstractHandler{
public:
    std::string Handle(std::string request) override{
        if(request == "MeatBall"){
            return "Dog: I'll eat the " + request + ".\n";
        }else{
            return AbstractHandler::Handle(request);
        }
        }
};
// 客户端代码
void ClientCode(Handler* handler){
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"}; 
    for(const std::string& f : food){
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler->Handle(f); 
        if(!result.empty()){
            std::cout << "  " << result; 
        }else{
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}

int main(){
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler; 
    monkey->SetNext(squirrel)->SetNext(dog);
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(squirrel);
    delete monkey;
    delete squirrel;
    delete dog;
    return 0;
}
