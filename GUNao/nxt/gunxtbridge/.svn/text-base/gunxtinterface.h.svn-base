/**
 * \file  gunxtinterface.h
 *  gunxtinterface
 *  Created by
 *  \author Vlad Estivill-Castro & Hans Wannop 
 *  \date 9/03/2013.
 */

/*
 * 
 * This is module acts as a bridge between the whiteboard and a LEGO mindstorm
 * NXT. Sensors can be commanded to post updates and actuators can be
 * controlled. Currently the module only supports linux over USB connections.
 * 
 * 
 *  Copyright 2012 Vlad Estivill-Castro. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *
 *        This product includes software developed by Rene Hexel.
 *
 * 4. Neither the name of the author nor the names of contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */



#ifndef GUNXTINTERFACE
#define GUNXTINTERFACE
#include <iostream>
#include "Whiteboard.h"
#include "WBMsg.h"

#include "gunxtbridge_wbmsg.h"  // for MOTOR IDs
#include "gunxtconstants.h"  // for SENSOR IDs


/**
* Tricky constants (they depend on XNT++ v5.0 that is larger than all the IDs, for ports.
*/
const int VLAD_ID_ERROR = (OUT_A+OUT_B+OUT_C+IN_1+IN_2+IN_3+IN_4);

/**
* Tricky constants that is larger than all the IDs, for INPUT ports.
*/
const int TOTAL_IN_PORTS= (IN_4+1);

/**
* Tricky constants that is larger than all the IDs, for OUTPUT ports.
*/
const int TOTAL_OUT_PORTS= (OUT_C+1);



/*!
 *  To use proper Object-Orientation this is the class that constructs the
 * actual singleton object that is the interface between the whiteboard and
 * the NXTpp code.
 */
class GUNxtInterface {
  public:

	/*!
	*  constructor; initialize the list to be empty
	*/
    	GUNxtInterface();                         

	/*!
	*  announce the program
	*/
	void banner();

	/*!
	*   establish USB connection to NXT
	*/
	bool connect();

	/*!
	*   regularly report to the whiteboard the status of active TOUCH sensors
	*/
	void reportActiveTouchSensors();  

	/*!
	* regularly report to whiteboard status of active motor ROTATION  sensors
	*/
	void reportActiveRotationSensors(); 


	/*!
	* regularly report to whiteboard status of active Light  sensors
	*/
	void reportActiveLightSensors(); 

	/*!
	* regularly report to whiteboard status of active SONAR  sensors
	*/
	void reportActiveSonarSensors(); 

	/*!
	* convert from int ID of OUT port to string
	*/
	std::string rotationIDtoName(int i)
		{	switch(i){
			case OUT_A : return kNxtmotorA;
			case OUT_B : return kNxtmotorB;
			case OUT_C : return kNxtmotorC;
			default: 
			return std::string(1,' ');
			}
		};

	/*!
	* convert from int ID of INPUT  port to string
	*/
	std::string portIDtoName(int i)
		{	switch(i){
			case IN_1 : return std::string(1,SENSOR_1);
			case IN_2 : return std::string(1,SENSOR_2);
			case IN_3 : return std::string(1,SENSOR_3);
			case IN_4 : return std::string(1,SENSOR_4);
			default: 
			return std::string(1,' ');
			}
		};
	

	/*! 
	* Call back methods
	* handle the request to place a motor running forward
	*/
	virtual void callBackMotorForward(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to place a motor running backward
	*/
	virtual void callBackMotorBackward(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to halt a motor
	*/
	virtual void callBackMotorStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to stop playing sound
	*/
	virtual void callBackStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to play sound
	*/
	virtual void callBackPlay(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to stop reporting about a touch sensor
	*/
	virtual void callBackTouchSensorStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to start monitoring a touch sensor
	*/
	virtual void callBackTouchSensorStart(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to start monitoring SONAR sensor
	*/
	virtual void callBackSonarSensorStart(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to STOP monitoring SONAR sensor
	*/
	virtual void callBackSonarSensorStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to STOP monitoring rotaiton of a motor 
	*/
	virtual void callBackRotationSensorStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to START monitoring rotaiton of a motor 
	*/
	virtual void callBackRotationSensorStart(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to STOP monitor a light sensor
	*/
	virtual void callBackLightSensorStop(std::string dataName, WBMsg *msg);

	/*! 
	* handle the request to START monitor a light sensor
	*/
	virtual void callBackLightSensorStart(std::string dataName, WBMsg *msg);




  private:
	guWhiteboard::Whiteboard *wb; 

	bool touchInitialized [TOTAL_IN_PORTS];

	bool reportingOnTouch [TOTAL_IN_PORTS];

	bool rotationInitialized [TOTAL_OUT_PORTS];

	bool reportingOnRotation [TOTAL_OUT_PORTS];

	bool lightInitialized [TOTAL_IN_PORTS];

	bool reportingOnLight [TOTAL_IN_PORTS];

	bool sonarInitialized [TOTAL_IN_PORTS];

	bool reportingOnSonar [TOTAL_IN_PORTS];

	int findMotorInContent(std::string dataName, WBMsg *msg);

	int findMotorPower(std::string dataName, WBMsg *msg);

	int findSensorInContent(std::string dataName, WBMsg *msg);


};



#endif // GUNXTINTERFACE
