#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include "Button.h"
#include "Text.h"
#include "Checkbox.h"

class GUIFactory{
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual Text* createText() = 0;
    virtual ~GUIFactory() = default;  
};

#endif