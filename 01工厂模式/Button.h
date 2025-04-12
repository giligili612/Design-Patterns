#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

//Product interface:产品接口
class Button{
public:
    virtual void render() = 0;
    virtual void onClick(std::function<void()> cb) = 0;
    ~Button() = default;
};


#endif