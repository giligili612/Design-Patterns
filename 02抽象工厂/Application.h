#ifndef APPLICATION_H
#define APPLICATION_H

#include "GUIFactory.h"
#include "MacFactory.h"
#include "LinuxFactory.h"
#include "WinFactory.h"

struct Config{
    std::string config = "Windows";
};

class Application{
public:
    Application(GUIFactory* gui):guifactory_(gui){
        btn = guifactory_->createButton();
        chkbox = guifactory_->createCheckbox();
        text = guifactory_->createText();
    }
    void createUI(){
        if(chkbox->ifIsChecked()){
            chkbox->CheckedColor();
        }
        text->show();
    }
    void setText(const std::string& s){
        text->setText(s);
    }
    void clickCheckbox(){
        chkbox->clickCheckbox();
    }
    void paint(){
        btn->paint();
        createUI();
    }
    void close(){
        delete btn;
        delete chkbox;
        delete text;
        delete guifactory_;
    }
private:
    GUIFactory* guifactory_;
    Button* btn;
    Checkbox* chkbox;
    Text* text;
};

#endif