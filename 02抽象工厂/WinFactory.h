#ifndef WINFACTORY_H
#define WINFACTORY_H
#include "GUIFactory.h"

class WinButton : public Button{
public:
    void paint(){
        std::cout << "windows button paint.\n";
    } 
};

class WinCheckBox : public Checkbox{
public:
    void CheckedColor(){
        std::cout << "Windows Checkbox now is checked\n";
        std::cout << "Windows Checkbox's color is red!\n";
    }
};

class WinText : public Text{
public:
    void setFont(const std::string& s = "Consolas"){
        std::cout << "Windows font now is " << s << '\n';
    }
    void show(){
        if(!text.empty()){
            std::cout << "Windows:" << text << '\n';
        }else{
            std::cout << "there is no text.\n";
        }
    }
};

class WinFactory : public GUIFactory{
public:
    Button* createButton(){
        return new WinButton();
    }
    Checkbox* createCheckbox(){
        return new WinCheckBox();
    }
    Text* createText(){
        return new WinText();
    }
};

#endif