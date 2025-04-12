#ifndef WINDOWSDIALOG_H
#define WINDOWSDIALOG_H

#include "Dialog.h"
#include "WindowsButton.h"

class WindowsDialog : public Dialog{
public:
    Button* createButton() override{
        return new WindowsButton();
    } 
};

#endif