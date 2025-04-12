#ifndef MACFACTORY_H
#define MACFACTORY_H

#include "GUIFactory.h"

class MacButton : public Button{
public:
    void paint(){
        std::cout << "mac button paint.\n";
    } 
};

class MacCheckBox : public Checkbox{
public:
    void CheckedColor(){
        std::cout << "MacOS Checkbox now is checked\n";
        std::cout << "MacOS Checkbox's color is red!\n";
    }
};

class MacText : public Text{
public:
    void setFont(const std::string& s = "MacFont"){
        std::cout << "MacOS font now is " << s << '\n';
    }
    void show(){
        if(!text.empty()){
            std::cout << "MacOS:" << text << '\n';
        }else{
            std::cout << "there is no text.\n";
        }
    }
};

class MacFactory : public GUIFactory{
public:
    Button* createButton(){
        return new MacButton();
    }
    Checkbox* createCheckbox(){
        return new MacCheckBox();
    }
    Text* createText(){
        return new MacText();
    }
};

#endif