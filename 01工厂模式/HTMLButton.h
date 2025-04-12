#ifndef HTMLBUTTON_H
#define HTMLBUTTON_H

#include "Button.h"
#include <iostream>

//concrete Products:具体产品
class HTMLButton : public Button{
public:
    void render() override{
        std::cout << "HTML is rendering!\n";
    }
    void onClick(std::function<void()> cb) override{
        std::cout << "Binding HTML function event to click.\n";
        cb();
    }
};

#endif