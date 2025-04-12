#include "Application.h"

int main(){
    Application app1;
    app1.initialize("Windows");
    app1.run();
    
    Application app2;
    app2.initialize("Web");
    app2.run();

    return 0;
}