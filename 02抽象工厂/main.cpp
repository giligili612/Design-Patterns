#include "Application.h"

int main(){
    Application app1(new WinFactory());
    app1.createUI();
    app1.clickCheckbox();
    app1.setText("Windows Text!!!");
    app1.paint();
    app1.close();
    
    std::cout << "----------------------------------\n";
    Application app2(new MacFactory());
    app2.createUI();
    app2.clickCheckbox();
    app2.setText("MacOS Text!!!");
    app2.paint();
    app2.close();

    std::cout << "----------------------------------\n";
    Application app3(new LinuxFactory());
    app3.createUI();
    app3.clickCheckbox();
    app3.setText("Linux Text!!!");
    app3.paint();
    app3.close();
    return 0;
}