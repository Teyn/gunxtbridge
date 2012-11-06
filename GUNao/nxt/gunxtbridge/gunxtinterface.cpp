/**
 * \file  gunxtinterface.cpp
 *  gunxtinterface
 *  Created by
 *  \author Vlad Estivill-Castro 
 *  \date 9/03/2013.
 */

/*
 * 
 * This is amodule so posting to the whitebaord will produce soudns in
 * a LEGO mindstorm NXY
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


#include "gu_util.h"  // for DBG = DEBUG
#include <sstream>
#include "NXT++.h"
#include <iostream>
#include "Whiteboard.h" 
#include "gumessagecontent.h"   // to extract content fro messages

#include "gunxtinterface.h"
#include "gunxtbridge_wbmsg.h"


using namespace std;
using namespace guWhiteboard;


GUNxtInterface ::GUNxtInterface()
	{
	   wb = new Whiteboard();

	   for (int i=IN_1; i < TOTAL_IN_PORTS; i++)
		{ touchInitialized [i]=false;
		  reportingOnTouch [i]=false;
		  lightInitialized [i]=false;
		  reportingOnLight [i]=false;
		  sonarInitialized [i]=false;
		  reportingOnSonar [i]=false;
		}

	   for (int i=OUT_A; i < TOTAL_OUT_PORTS; i++)
		{ 
		  rotationInitialized [i]=false;
		  reportingOnRotation [i]=false;
		}

	    Whiteboard::WBResult wr;//WBResult

		// SOUND message responses
	    wb->subscribeToMessage(kNxtPlaySound, WB_BIND(GUNxtInterface::callBackPlay) , wr);
	    wb->subscribeToMessage(kNxtStopSound, WB_BIND(GUNxtInterface::callBackStop) , wr);

		// MOTOR message responses
	// CODE TO ADD HERE FOR LABORATORY 2

		// TOUCH message responses
	// CODE TO ADD HERE FOR LABORATORY 2

		// ROTATION message responses
	    wb->subscribeToMessage(kNxtStopRotationSensor, WB_BIND(GUNxtInterface::callBackRotationSensorStop) , wr);
	    wb->subscribeToMessage(kNxtStartRotationSensor, WB_BIND(GUNxtInterface::callBackRotationSensorStart) , wr);

		// LIGHT message responses
	// CODE TO ADD HERE FOR LABORATORY 2

		// SONAR message responses
	// CODE TO ADD HERE FOR LABORATORY 2

	}

void GUNxtInterface ::banner()
	{   cout << " GU NXT Whiteboard Bridge --- module to interface with a LEGO NXT  " << endl;
	    cout << " (c) 2012  Vlad Estivill-Castro" << endl;
	}

bool GUNxtInterface :: connect()
	{ 
    	if(NXT::Open()) //initialize the NXT and continue if it succeds
		{ 
		  cerr << "Connection established" << endl;
		  return true;
		}
   	else
		{
    		cerr << "NXT++ No connection" << endl;
		  return false;
		}
	}

int GUNxtInterface::findSensorInContent(std::string dataName, WBMsg *msg)
{
	DBG(cerr << " ** Finding Sensor ID **" << endl;)

	int sensorIndicated;

        MessageContent theMessageContent (msg);

        string content = theMessageContent.theContent();

        DBG (cout << "Message Received  ++++++>" << content << endl );

	/* any number among 1 | 2 | 3 | 4   indicates the sensor */

	if (string::npos!=content.find(SENSOR_1))
		{
			sensorIndicated=IN_1;
		}
	else
	if (string::npos!=content.find(SENSOR_2))
		{
			sensorIndicated=IN_2;
		}
	else
	if (string::npos!=content.find(SENSOR_3))
		{
			sensorIndicated=IN_3;
		}
	else
	if (string::npos!=content.find(SENSOR_4))
		{
			sensorIndicated=IN_4;
		}
	else 
		{ DBG (cout << "UNKNOWN SENSOR ID"  << content << endl );
		  return VLAD_ID_ERROR;
		}

		return sensorIndicated;
}

int GUNxtInterface::findMotorInContent(std::string dataName, WBMsg *msg)
{
	DBG(cerr << " ** Finding Motor ID **" << endl;)

	int motorIndicated;

        MessageContent theMessageContent (msg);

        string content = theMessageContent.theContent();

        DBG (cout << "Message Received  ++++++>" << content << endl );

	/* any letter among A | B | C  indicates the motor */

	if (string::npos!=content.find(kNxtmotorA))
		{
			motorIndicated=OUT_A;
		}
	else
	if (string::npos!=content.find(kNxtmotorB))
		{
			motorIndicated=OUT_B;
		}
	else
	if (string::npos!=content.find(kNxtmotorC))
		{
			motorIndicated=OUT_C;
		}
	else 
		{ 
			DBG (cout << "UNKNOWN MOTOR ID"  << content << endl );
			return VLAD_ID_ERROR;
		}

		return motorIndicated;
}

int GUNxtInterface::findMotorPower(std::string dataName, WBMsg *msg)
{
        MessageContent theMessageContent (msg);

        string content = theMessageContent.theContent();
	int separatorPos = content.find(',');

	/* an integer between 0, 100 indicates the pwer to the motor */

          //advance content
        content=content.substr(separatorPos+1);
	return atoi( content.c_str() );

}

void GUNxtInterface::callBackRotationSensorStop(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection
	DBG(cerr << " ** STOP ROTATION SENSOR **" << endl;)

	int sensorIndicated= findMotorInContent(dataName, msg);

	if (  (OUT_A<= sensorIndicated) && ( sensorIndicated<= OUT_C) )
	{ 
	   NXT::Motor::ResetRotationCount(sensorIndicated,false); //reset the rotaiton count
          reportingOnRotation [sensorIndicated]=false;
	}
}


void GUNxtInterface::callBackRotationSensorStart(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection
	DBG(cerr << " ** START ROTATION SENSOR **" << endl;)

	int sensorIndicated= findMotorInContent(dataName, msg);

	if (  (OUT_A<= sensorIndicated) && ( sensorIndicated<= OUT_C) )
	{ if (!  rotationInitialized [sensorIndicated] )
		{ rotationInitialized [sensorIndicated]=true;
		DBG(cerr << " ** START " << sensorIndicated << endl;)
		}
		  NXT::Motor::ResetRotationCount(sensorIndicated,false); //Reset the rotaiton count
          reportingOnRotation [sensorIndicated]=true;
	}
}

void GUNxtInterface::callBackTouchSensorStart(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** START TOUCH SENSOR **" << endl;)
	int sensorIndicated = findSensorInContent(dataName, msg);

	if ((IN_1 <= sensorIndicated) && (sensorIndicated<= IN_4))
	{
		if (!touchInitialized[sensorIndicated])
		{
			touchInitialized[sensorIndicated]=true;
			DBG(cerr << " ** START " << sensorIndicated << endl;)
		}
		NXT::Sensor::SetTouch(sensorIndicated); //Reset the rotaiton count
        	reportingOnTouch[sensorIndicated]=true;
	}

}

void GUNxtInterface::callBackTouchSensorStop(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** STOP TOUCH SENSOR **" << endl;)
	int sensorIndicated = findSensorInContent(dataName, msg);

	if ((IN_1 <= sensorIndicated) && (sensorIndicated<= IN_4))
	{
		NXT::Sensor::SetTouch(sensorIndicated); //Reset the rotaiton count
		reportingOnTouch[sensorIndicated]=false;
	}
}

void GUNxtInterface::callBackSonarSensorStart(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** START SONAR SENSOR  **" << endl;)
	int sensorIndicated= findSensorInContent(dataName, msg);

	if((IN_1<=sensorIndicated) && (sensorIndicated<= IN_3))
	{
		if(!sonarInitialized[sensorIndicated])
		{
			DBG(cerr << "Starting sonar sensor..." << endl);
			sonarInitialized[sensorIndicated] = true;
			NXT::Sensor::SetSonar(sensorIndicated);
		}
	reportingOnSonar[sensorIndicated] = true;
	}
}

void GUNxtInterface::callBackSonarSensorStop(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different trhead, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** STOP SONAR SENSOR  **" << endl;)
	int sensorIndicated= findSensorInContent(dataName, msg);

	if((IN_1<=sensorIndicated) && (sensorIndicated<= IN_3))
	{
		if(!sonarInitialized[sensorIndicated])
		{
			DBG(cerr << "Stopping sonar sensor..." << endl);
			sonarInitialized[sensorIndicated] = false;
			NXT::Sensor::SetSonarOff(sensorIndicated);
		}
	reportingOnSonar[sensorIndicated] = false;
	}
}


void GUNxtInterface::callBackLightSensorStart(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different thread, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** START LIGHT SENSOR  **" << endl;)
	int sensorIndicated= findSensorInContent(dataName, msg);

	if((IN_1<=sensorIndicated) && (sensorIndicated<= IN_3))
	{
		if(!sonarInitialized[sensorIndicated])
		{
			DBG(cerr << "Starting light sensor..." << endl);
			sonarInitialized[sensorIndicated] = true;
			NXT::Sensor::SetLight(sensorIndicated, true);
		}
	reportingOnLight[sensorIndicated] = true;
	}
}

void GUNxtInterface::callBackLightSensorStop(std::string dataName, WBMsg *msg)
{
   // TODO: this is a different thread, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** STOP LIGHT SENSOR  **" << endl;)
	int sensorIndicated= findSensorInContent(dataName, msg);

	if((IN_1<=sensorIndicated) && (sensorIndicated<= IN_3))
	{
		if(!sonarInitialized[sensorIndicated])
		{
			DBG(cerr << "Stopping light sensor..." << endl);
			sonarInitialized[sensorIndicated] = false;
			NXT::Sensor::SetLight(sensorIndicated, false);
		}
	reportingOnLight[sensorIndicated] = false;
	}
}

void GUNxtInterface::callBackMotorStop(std::string dataName, WBMsg *msg)
{
	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** STOP MOTORS  **" << endl;)
	int motorIndicated = findMotorInContent(dataName, msg);

	if((OUT_A<=motorIndicated) && (motorIndicated<= OUT_C))
	{
		DBG(cerr << "Stopping motor..." << endl);
		NXT::Motor::Stop(motorIndicated, true);	
	}

}

void GUNxtInterface::callBackMotorBackward(std::string dataName, WBMsg *msg)
{
	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** BACKWARD MOTORS  **" << endl;)
	int motorIndicated = findMotorInContent(dataName, msg);

	if((OUT_A<=motorIndicated) && (motorIndicated<= OUT_C))
	{
		DBG(cerr << "Backwarding motor..." << endl);
		NXT::Motor::SetReverse(motorIndicated, 50);	
	}

}

void GUNxtInterface::callBackMotorForward(std::string dataName, WBMsg *msg)
{
	// CODE TO ADD HERE FOR LABORATORY 2
	DBG(cerr << " ** FORWARD MOTORS  **" << endl;)
	int motorIndicated = findMotorInContent(dataName, msg);

	if((OUT_A<=motorIndicated) && (motorIndicated<= OUT_C))
	{
		DBG(cerr << "Forwarding motor..." << endl);
		NXT::Motor::SetForward(motorIndicated, 50);	
	}

}

void GUNxtInterface::callBackStop(std::string dataName, WBMsg *msg)
{
	DBG(cerr << " ** STOP  **" << endl;)
	NXT::StopSound();
}

void GUNxtInterface::callBackPlay(std::string dataName, WBMsg *msg)
{
	DBG(cerr << " ** PLAY  **" << endl;)

        MessageContent theMessageContent (msg);

        string content = theMessageContent.theContent();

        DBG (cout << "Message Received  ++++++>" << content << endl );

	int duration = atoi ( (char *) content.c_str() );

	if (duration >0)
		NXT::PlayTone(400, duration);
	else
		NXT::PlayTone(400, 75);
}


void GUNxtInterface::reportActiveTouchSensors()
{   // TODO: this is a different thread, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	for (int i=OUT_A; i<TOTAL_OUT_PORTS; i++)
		if ( ( touchInitialized[i] && reportingOnTouch[i]))
		{ 
			DBG(cerr << " ** Reporting for touch sonar" << i << endl;)
			int newCount = NXT::Sensor::GetValue(i);
			wb->addMessage(kNxtValueTouchSensor+portIDtoName(i) ,WBMsg(newCount),true);
		}

}

void GUNxtInterface::reportActiveRotationSensors()
{   // TODO: this is a different thread, may need semaphore protection
	//DBG(cerr << " ** Report Rotation  **" << endl;)
	for (int i=OUT_A; i<TOTAL_OUT_PORTS; i++)
		if ( ( rotationInitialized[i] && reportingOnRotation[i]))
		{ 
			DBG(cerr << " ** Reporting for motor" << i << endl;)
			int newCount = NXT::Motor::GetRotationCount(i);
			wb->addMessage(kNxtValueRotationSensor+rotationIDtoName(i) ,WBMsg(newCount),true);
		}

}

void GUNxtInterface::reportActiveLightSensors()
{   // TODO: this is a different thread, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	for (int i=OUT_A; i<TOTAL_OUT_PORTS; i++)
		if ( ( lightInitialized[i] && reportingOnLight[i]))
		{ 
			DBG(cerr << " ** Reporting for light sonat" << i << endl;)
			int newCount = NXT::Sensor::LSGetStatus(i);
			wb->addMessage(kNxtValueLightSensor+portIDtoName(i) ,WBMsg(newCount),true);
		}
}

void GUNxtInterface::reportActiveSonarSensors()
{   // TODO: this is a different thread, may need semaphore protection

	// CODE TO ADD HERE FOR LABORATORY 2
	for (int i=OUT_A; i<TOTAL_OUT_PORTS; i++)
		if ( ( sonarInitialized[i] && reportingOnSonar[i]))
		{ 
			DBG(cerr << " ** Reporting for active sonar" << i << endl;)
			int newCount = NXT::Sensor::GetSonarValue(i);
			wb->addMessage(kNxtValueSonarSensor+portIDtoName(i) ,WBMsg(newCount),true);
		}
}
