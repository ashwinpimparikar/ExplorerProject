#include <iostream>
#include <string.h>

using namespace std;

class Button {
public:
    virtual void paint()=0;
};

class OSXButton: public Button{
public:
    void paint(){
    std::cout<<"OSX Button\n";
    }
};

class WindowsButton: public Button{
public:
    void paint(){
    std::cout<<"Windows Button\n";
    }
};

class GUIFactory{
public:
    virtual Button *createButton(char *) = 0;
};

class Factory: public GUIFactory{
public:
    Button *createButton(char *type){
        if(strcmp(type,"Windows") == 0)
        {
            return new WindowsButton;
        }
        else if(strcmp(type,"OSX")==0)
        {
            return new OSXButton;
        }

    }
};
int main()
{
    GUIFactory* guiFactory;
    Button *btn;
    guiFactory = new Factory;

    btn = guiFactory->createButton("OSX");
    btn->paint();
    btn = guiFactory->createButton("Windows");
    btn->paint();
    cout << "Hello world!" << endl;
    return 0;
}
