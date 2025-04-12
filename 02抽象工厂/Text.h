#ifndef TEXT_H
#define TEXT_H
#include <iostream>

class Text{
public:
    virtual void setFont(const std::string& s) = 0;
    virtual void show() = 0;
    void setText(const std::string& s){
        
        text = s;
    }
    virtual ~Text() = default;
    
protected:
    std::string text;
};

#endif