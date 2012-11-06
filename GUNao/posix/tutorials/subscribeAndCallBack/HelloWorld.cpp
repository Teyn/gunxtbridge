/**
 * \file  HelloWorld.cpp
 *  HelloWorld
 *  Created by
 *  \author Jonathan Ferrer Mestres on 
 *  \date 26/10/11.
 */

/*
 * 
 * This module is a simple example of how to subscribe Whiteboard messages.
 * 
 * Operation:
 * 
 * 1-Run the Whiteboard(make host if you want to run on your own machine)
 * 2-Run the gutest module(make host)
 * 3-Write TestModule in the msg type of Whiteboard running
 * 4-Write anything in the content field
 * 5-In the gutest execution, the module prints HelloWorld + your content message written in the Whiteboard content field.
 *
 */


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <string>
#include "HelloWorld.h"
#include "Whiteboard.h" 

using namespace std;
using namespace guWhiteboard;


//HelloWorld constructor

/*Note that in the header file, we instancied the Whiteboard class, but is here when we create the new object using the Whiteboard constructor,
because the Whiteboard can't be static, so it's recomended to create the new object on your main class constructor.*/

 HelloWorld::HelloWorld(string helloWorld)
 {
    wb = new Whiteboard();
    cout << "Proba" << endl;
    cout.flush();
    _helloWorld = helloWorld;
 }

//Set Up method
//In this method, we subscribe the message to the Whiteboard using the subscribeToMessage Whiteboard method.
void HelloWorld::setUpHelloWorld()
{
  
   Whiteboard::WBResult wr;//WBResult
     
   //subscribe method (msg type, callback function, WBResult).
   //This method contains 3 parameters: The message type, the call back method, and the WBResult object(Declared previously)
   wb->subscribeToMessage("TestModule", WB_BIND(HelloWorld::callBackTest) , wr);//I can put the message type on an extern C file with a char pointer variable(Recomended if you have a lot of msg type.)
  
}

//My call back method

void HelloWorld::callBackTest(std::string dataName, WBMsg *msg)
{

  ostringstream text;

      string content;//Will contain the content message written on the whiteboard, after the message type: "TestModule"
      
		        /* Extract the Message written on the Whiteboard, in the content field*/
        		if (msg->getType() == WBMsg::TypeString)
                		text << msg->getStringValue();
        		else if (msg->getType() == WBMsg::TypeInt)
                		text << msg->getIntValue();
        		else if (msg->getType() == WBMsg::TypeFloat)
                		text << msg->getFloatValue();
        		else if (msg->getType() == WBMsg::TypeBool)
                		text << ( msg->getBoolValue() ? "Yes." : "No." );
        		else text << msg->getSizeInBytes() << " bytes of gibberish";

        		content= text.str();//Parse text to string
		
			//It prints HelloWorld + the content message that we wrote on the Whiteboard.
			cout << "HelloWorld " << content << endl; 
      
}

int main(int argc, char **argv)
{

  HelloWorld *hw = new HelloWorld("Hello World!\n");//HelloWorld constructor
  hw->setUpHelloWorld();//Set Up method call
    
  //This is not recommended, but now we need to non stop the running on the Whiteboard
   while(1){sleep(300);};
  
}

