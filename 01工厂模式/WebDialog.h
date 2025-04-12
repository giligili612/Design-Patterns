#ifndef WEBDIALOG_H
#define WEBDIALOG_H

#include "Dialog.h"
#include "HTMLButton.h"
class WebDialog : public Dialog{
public:
    Button* createButton() override{
        return new HTMLButton();
    }
};


#endif