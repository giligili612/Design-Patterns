#include <iostream>
/**
 * 服务接口
 * 客户端可以通过这个接口与服务进行交互
 * 代理与服务实现了相同的接口
 */
class Subject {
public:
    virtual void Request() const = 0;
};
// 真实服务，提供了具体的服务
class RealSubject : public Subject {
public:
    void Request() const override {
        std::cout << "RealSubject: Handling request.\n";
    }
};
// 代理，提供了与真实服务相同的接口
// 代理可以在真实服务之前或之后执行一些额外的操作，比如访问控制、日志记录等
class Proxy : public Subject {
private:
    RealSubject* real_subject_;

    bool CheckAccess() const {
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }

    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    } 
public:
    Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {}

    ~Proxy() {
        delete real_subject_;
    }

    void Request() const override {
        if (this->CheckAccess()) {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

void Client(const Subject& subject){
    subject.Request();
}

int main(){
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject* real_subject = new RealSubject;
    Client(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the client code with a proxy:\n";
    Proxy* proxy = new Proxy(real_subject);
    Client(*proxy);
    delete real_subject;
    delete proxy;
    return 0;
}