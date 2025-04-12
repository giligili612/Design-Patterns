#ifndef APPLICATION_H
#define APPLICATION_H
#include "Dialog.h"
#include "WindowsDialog.h"
#include "WebDialog.h"

struct Config{
    std::string OS;
};

Config readConfig(const std::string& s){
    return {s};
};

class Application{
private:
    Dialog* dialog;
public:
    void initialize(const std::string& s){
        Config config = readConfig(s);
        if(config.OS == "Windows"){
            dialog = new WindowsDialog();
        }else if (config.OS == "Web"){
            dialog = new WebDialog();
        }else{
            throw std::runtime_error("Error:Unknown system.");
        }
    }

    void run(){
        dialog->render();
    }
    ~Application() { delete dialog; }
};

#endif