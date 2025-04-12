#ifndef LINUXFACTORY_H
#define LINUXFACTORY_H

#include "GUIFactory.h"

class LinuxButton : public Button{
public:
    void paint(){
        std::cout << "linux button paint.\n";
    } 
};

class LinuxCheckBox : public Checkbox{
public:
    void CheckedColor(){
        std::cout << "LinuxOS Checkbox now is checked\n";
        std::cout << "LinuxOS Checkbox's color is red!\n";
    }
};

class LinuxText : public Text{
public:
    void setFont(const std::string& s = "LinuxFont"){
        std::cout << "LinuxOS font now is " << s << '\n';
    }
    void show(){
        if(!text.empty()){
            std::cout << "LinuxOS:" << text << '\n';
        }else{
            std::cout << "there is no text.\n";
        }
    }
};

class LinuxFactory : public GUIFactory{
public:
    Button* createButton(){
        return new LinuxButton();
    }
    Checkbox* createCheckbox(){
        return new LinuxCheckBox();
    }
    Text* createText(){
        return new LinuxText();
    }
};

#endif