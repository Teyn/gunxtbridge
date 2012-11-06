/**
 *  \file  gunxtbridge_wbmsg.c
 *  Created by Vlad Estivill-Castro on 11/03/2012.
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
#include "gunxtbridge_wbmsg.h"

/**  This is a messgae type-this module responds to:
 *  and if an NXT is connected it will   play a sound.
 *   content is duration  (in MILI - seconds)
 */
const char *kNxtPlaySound = "gunxt_playSound";
const char *kNxtStopSound = "gunxt_stopSound";
const char *kNxtRunForwardMotor = "gunxt_runForwardMotor";
const char *kNxtRunBackwardMotor = "gunxt_runBackwardMotor";
const char *kNxtStopMotor = "gunxt_stopMotor";

const char *kNxtStopTouchSensor = "gunxt_stopTouchSensor";
const char *kNxtStartTouchSensor = "gunxt_startTouchSensor";
const char *kNxtValueTouchSensor = "gunxt_valueTouchSensor";

const char *kNxtStopRotationSensor = "gunxt_stopRotationSensor";
const char *kNxtStartRotationSensor = "gunxt_startRotationSensor";
const char *kNxtValueRotationSensor = "gunxt_valueRotationSensor";

const char *kNxtStopLightSensor = "gunxt_stopLightSensor";
const char *kNxtStartLightSensor = "gunxt_startLightSensor";
const char *kNxtValueLightSensor = "gunxt_valueLightSensor";


/**  This is a messgae type-this module responds to:
 *   starts a Sonar  sensor reporting to the whiteboard
 *   messgage-content is input port  1, 2, 3, or 4. 
 */
const char *kNxtStartSonarSensor = "gunxt_startSonarSensor";

/**  This is a messgae type-this module responds to:
 *   starts a Sonar  sensor reporting to the whiteboard
 *   messgage-content is input port  1, 2, 3, or 4. 
 */
const char *kNxtStopSonarSensor = "gunxt_stopSonarSensor";


/**  This is a messgae type-this module POSTS :
 * the message type is appended the input port
 *   messgage-content is the value read by the sensor.
 */
const char *kNxtValueSonarSensor = "gunxt_valueSonarSensor";


/**  Names of the ports for the motors. 
 *   Name for Motor A
 */
const char *kNxtmotorA = "A";

/** 
 *   Name for Motor B
 */
const char *kNxtmotorB = "B";

/** 
 *   Name for Motor C
 */
const char *kNxtmotorC = "C";

