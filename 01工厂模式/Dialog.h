#ifndef DIALOG_H
#define DIALOG_H

#include "Button.h"
#include <iostream>
//Creator : 创建者
class Dialog{
public:
    virtual Button* createButton() = 0;
    void render(){
        Button* btn = createButton();
        btn->onClick([this]() { closeDialog();});
        btn->render();
        delete btn;
    }
    virtual ~Dialog() = default;
private:
    void closeDialog(){
        std::cout << "Closing the dialog\n";
    }
};

#endif