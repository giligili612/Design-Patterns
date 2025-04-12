#ifndef WINDOWSBUTTON_H
#define WINDOWSBUTTON_H

#include "Button.h"
#include <iostream>

//concrete Products:具体产品
class WindowsButton : public Button{
public:
    void render() override{ 
        std::cout << "WindowsDialog rendering!\n";
    }

    void onClick(std::function<void()> cb) override{
        std::cout << "Binding windows function event to click.\n";
        cb();
    }
};


#endif