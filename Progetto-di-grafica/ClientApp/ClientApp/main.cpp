#include <iostream>
#include "Engine.h"
Engine* engine = new Engine();
int main(int argc, char * argv[])
{
    std::cout << "Client application starts"<<std::endl;
    //TODO sistemare dipendenze
    //engine->initEngine(1920,1080);
    //engine->renderMain(argc,argv);
    //engine->startLoop();
    //TODO: set alla Callback
    //glutDisplayFunc(displayCallback);
    //engine->reshape(reshapeCallback);
    //glutSpecialFunc(specialCallback);
    //glutKeyboardFunc(specialCallback);
    //glutMouseFunc(mouseCallback);
    //glutMotionFunc(dragCallback);
    std::cout << "Application terminated"<<std::endl;
}
