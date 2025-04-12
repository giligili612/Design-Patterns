#ifndef BUTTON_H
#define BUTTON_H
#include <functional>
#include <iostream>

class Button{
public:
    //纯虚函数是必须实现的接口
    virtual void paint() = 0;
    virtual ~Button() = default;
};

#endif