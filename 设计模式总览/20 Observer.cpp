/**
 * 观察者设计模式
 *
 * 意图： 让你定义一种订阅机制，以便在被观察对象发生任何事件时通知多个对象。
 *
 * 请注意，与该模式相关的有很多含义相似的不同术语。
 * 只需记住，主题（Subject）也被称为发布者（Publisher），而观察者（Observer）通常被称为订阅者（Subscriber），反之亦然。
 * 此外，“观察（observe）”、“监听（listen）” 或 “跟踪（track）” 这些动词通常表示相同的意思。
 */

 #include <iostream>
 #include <list>
 #include <string>
 
 class IObserver {
  public:
   virtual ~IObserver(){};
   virtual void Update(const std::string &message_from_subject) = 0;
 };
 
 class ISubject {
  public:
   virtual ~ISubject(){};
   virtual void Attach(IObserver *observer) = 0;
   virtual void Detach(IObserver *observer) = 0;
   virtual void Notify() = 0;
 };
 
 /**
  * 主题拥有一些重要的状态，并在状态发生变化时通知观察者。
  */
 
 class Subject : public ISubject {
  public:
   virtual ~Subject() {
     std::cout << "Goodbye, I was the Subject.\n";
   }
 
   /**
    * 订阅管理方法。
    */
   void Attach(IObserver *observer) override {
     list_observer_.push_back(observer);
   }
   void Detach(IObserver *observer) override {
     list_observer_.remove(observer);
   }
   void Notify() override {
     std::list<IObserver *>::iterator iterator = list_observer_.begin();
     HowManyObserver();
     while (iterator != list_observer_.end()) {
       (*iterator)->Update(message_);
       ++iterator;
     }
   }
 
   void CreateMessage(std::string message = "Empty") {
     this->message_ = message;
     Notify();
   }
   void HowManyObserver() {
     std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
   }
 
   /**
    * 通常，订阅逻辑只是主题实际功能的一部分。
    * 主题通常包含一些重要的业务逻辑，每当有重要事情即将发生时（或发生后），这些逻辑会触发通知方法。
    */
   void SomeBusinessLogic() {
     this->message_ = "change message message";
     Notify();
     std::cout << "I'm about to do some thing important\n";
   }
 
  private:
   std::list<IObserver *> list_observer_;
   std::string message_;
 };
 
 class Observer : public IObserver {
  public:
   Observer(Subject &subject) : subject_(subject) {
     this->subject_.Attach(this);
     std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
     this->number_ = Observer::static_number_;
   }
   virtual ~Observer() {
     std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
   }
 
   void Update(const std::string &message_from_subject) override {
     message_from_subject_ = message_from_subject;
     PrintInfo();
   }
   void RemoveMeFromTheList() {
     subject_.Detach(this);
     std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
   }
   void PrintInfo() {
     std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
   }
 
  private:
   std::string message_from_subject_;
   Subject &subject_;
   static int static_number_;
   int number_;
 };
 
 int Observer::static_number_ = 0;
 
 void ClientCode() {
   Subject *subject = new Subject;
   Observer *observer1 = new Observer(*subject);
   Observer *observer2 = new Observer(*subject);
   Observer *observer3 = new Observer(*subject);
   Observer *observer4;
   Observer *observer5;
 
   subject->CreateMessage("Hello World! :D");
   observer3->RemoveMeFromTheList();
 
   subject->CreateMessage("The weather is hot today! :p");
   observer4 = new Observer(*subject);
 
   observer2->RemoveMeFromTheList();
   observer5 = new Observer(*subject);
 
   subject->CreateMessage("My new car is great! ;)");
   observer5->RemoveMeFromTheList();
 
   observer4->RemoveMeFromTheList();
   observer1->RemoveMeFromTheList();
 
   delete observer5;
   delete observer4;
   delete observer3;
   delete observer2;
   delete observer1;
   delete subject;
 }
 
 int main() {
   ClientCode();
   return 0;
 }