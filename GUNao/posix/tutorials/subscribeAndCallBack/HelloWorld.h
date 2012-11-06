#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

#include "Whiteboard.h"
#include "WBMsg.h"

using namespace std;

//Example class
class HelloWorld
{
  
 //Attributes declaration 
 private:
   string _helloWorld;
   guWhiteboard::Whiteboard *wb; //Whiteboard class instance(note that the constructor of Whiteboard class is not called yet)
 
 
 public:
   
  HelloWorld(string helloWorld);//Class constructor

  //Methods:
  
 
 string getHello()
 {
    return _helloWorld;
 }
 
  void setSaySomething(string something)
 {
    _helloWorld = something;
 }
 
 //SetUp and call method
 void setUpHelloWorld();
 
 //Call back method
virtual void callBackTest(std::string dataName, WBMsg *msg);
  
  
};
