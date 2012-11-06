/*
 *  WBMsg.h
 *  
 *  Created by René Hexel on 21/12/11.
 *  Copyright (c) 2011 Rene Hexel.
 *  All rights reserved.
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
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
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
#ifndef gusimplewhiteboard_WBMsg_h
#define gusimplewhiteboard_WBMsg_h

#ifndef gusimplewhiteboard_Whiteboard_h
#ifndef NO_WARN_WBMSG_H
#warning *** Warning: attempt to include simple WBMsg directly without including Whiteboard.h first!
#endif
#endif

#ifdef WHITEBOARD_OLD_H
#error *** Error: attempt to mix old and simple Whiteboard in WBMsg!
#endif
#ifdef _BOOST_WHITEBOARD_H_
#error *** Error: attempt to mix boost and simple Whiteboard in WBMsg!
#endif

#include <cstdlib>
#include <string>
#include <iostream>             //for cerr
#include <sstream>              // for stringValue()
#include "gusimplewhiteboard.h" //for GU_SIMPLE_WHITEBOARD_GENERATIONS

class WBMsg
{
public:
	/**
	 * Message internal Datatype Enum
	 * @brief Allows the user to test the datatype of the message
	 */
        typedef enum wb_type
	{
		TypeBool,
		TypeInt,
		TypeFloat,
		TypeString,
		TypeArray,
		TypeBinary,
		TypeEmpty
	} WBType;
private:
        union
        {
                bool boolVal;
                int intVal;
                float floatVal;
                const void *binaryVal;
                const std::vector<int> *arrayVal;
        };
	WBType type;
	int binarySize;
	std::string typeName;
	std::string stringVal;
	bool doFree;

public:
        /**
	 * WBMsg - empty constructor.
	 * Initialises a WBMsg with no attached data.
	 */
	WBMsg(): type(TypeEmpty) {}

	/**
	 * WBMsg - Boolean constructor.
	 * Initialises a WBMsg with a given boolean value.
	 * @param val Boolean value to store in the Whiteboard message.
	 */
	WBMsg(bool val): boolVal(val), type(TypeBool) {}

	/**
	 * WBMsg - Integer constructor.
	 * Initialises a WBMsg with a given int value.
	 * @param val Int value to store in the Whiteboard message.
	 */

	WBMsg(int val): intVal(val), type(TypeInt) {}
	/**
	 * WBMsg - Float constructor.
	 * Initialises a WBMsg with a given float value.
	 * @param val Float value to store in the Whiteboard message.
	 */

	WBMsg(float val): floatVal(val), type(TypeFloat) {}

	/**
	 * WBMsg - String constructor.
	 * Initialises a WBMsg with a standard C++ string value.
	 * @param val String to store in the Whiteboard message.
	 */
	WBMsg(const std::string &val): type(TypeString), stringVal(val) {}

	/**
	 * WBMsg - String constructor.
	 * Initialises a WBMsg with a standard C string value.
	 * @param val String to store in the Whiteboard message.
	 */
	WBMsg(const char *val): type(TypeString), stringVal(val) {}

	/**
	 * WBMsg - Binary data constructor.
	 * Initialises a WBMsg with some binary data.
	 * @param data Pointer to a data constrct to store in the Whiteboard
	 *             message.
	 * @param nBytes Size of the data in bytes.
	 * @param needsFree If this is non-zero, will free the contents of the data 
	 *                  buffer when this WBMsg is deleted.
	 */
	WBMsg(const void *data, int nBytes, bool needsFree = false): binaryVal(data), type(TypeBinary), binarySize(nBytes), doFree(needsFree) {}

	/**
	 * WBMsg - Vector<int> pointer constructor.
	 * Initialises a WBMsg with a standard C++ string value.
	 * @param val String to store in the Whiteboard message.
	 */
	WBMsg(const std::vector<int> *val, bool needsFree = false): arrayVal(val), type(TypeArray), doFree(needsFree) {}

	/**
	 * WBMsg - Vector<int> constructor.
	 * Initialises a WBMsg with a standard C++ string value.
	 * @param val String to store in the Whiteboard message.
         * @param needsFree destroys the original vector immediately if true
	 */
	WBMsg(const std::vector<int> &val, bool needsFree = false): arrayVal(new std::vector<int>(val)), type(TypeArray), doFree(true) { if (needsFree) delete &val; }

	/**
	 * getType.
	 * @return The data type this WBMsg represents as a WBType.
	 */
	WBType getType() const { return type; }

	/**
	 * setTypeName
	 */
        void setTypeName(const std::string &t) { typeName = t; }

	/**
	 * getTypeName
	 * @return The message type string
	 */
        const std::string &getTypeName() const { return typeName; }

	/**
	 * getLifeSpan
	 * @return The original message lifespan
	 */	
	int getLifeSpan() const { return GU_SIMPLE_WHITEBOARD_GENERATIONS; }

	/**
	 * setLifeSpan
	 */	
	void setLifeSpan(int life)
        {
                std::cerr << "Setting a life span (" << life << ") not supported on WBMsg()\n" << std::endl;
        }

	/**
	 * boolValue.
	 * @return The value of this message "intelligently" interpreted as a boolean
	 */
	bool boolValue() const
        {
                switch (type)
                {
                        case TypeBool:
                                return boolVal;
                        case TypeInt:
                                return intVal != 0;
                        case TypeFloat:
                                return floatVal != 0.0;
                        case TypeString:
                                return toupper(stringVal[0]) == 'Y' ||
                                       toupper(stringVal[0]) == 'T' ||
                                       stringVal == "on" || stringVal == "On" ||
                                       stringVal == "ON" ||
                                       atoi(stringVal.c_str()) != 0;
                        case TypeArray:
                                return !arrayVal->size() || (*arrayVal)[0];
                        default:
                                return true;
                }
        }

        /**
         * intValue.
         * @return Message value "intelligently" interpreted as integer
         */
         int intValue() const
         {
                 switch (type)
                 {
                         case TypeBool:
                                 return int(boolVal);
                         case TypeInt:
                                 return intVal;
                         case TypeFloat:
                                 return int(floatVal);
                         case TypeString:
                                 return atoi(stringVal.c_str());
                         case TypeArray:
                                 if (arrayVal->size()) return (*arrayVal)[0];
                         default:
                                 return 0;
                 }
         }

        /**
         * floatValue.
         * @return Message value "intelligently" interpreted as float
         */
        int floatValue() const
        {
                switch (type)
                {
                        case TypeBool:
                                return float(boolVal);
                        case TypeInt:
                                return float(intVal);
                        case TypeFloat:
                                return floatVal;
                        case TypeString:
                                return atof(stringVal.c_str());
                        case TypeArray:
                                if (arrayVal->size()) return (*arrayVal)[0];
                        default:
                                return 0;
                }
        }

        /**
	 * stringValue.
	 * @return The value of this message "intelligently" interpreted as a string
	 */
	const std::string stringValue() const
        {
                std::stringstream ss;
                switch (type)
                {
                        case TypeBool:
                                ss << boolVal;
                                break;
                        case TypeInt:
                                ss << intVal;
                                break;
                        case TypeFloat:
                                ss << floatVal;
                                break;
                        case TypeString:
                                return stringVal;
                        case TypeArray:
                        {
                                std::vector<int>::const_iterator i = arrayVal->begin();
                                ss << *i++;
                                while (i != arrayVal->end())
                                {
                                        ss << ", ";
                                        ss << *i++;
                                }
                                break;
                        }
                        case TypeBinary:
                        {
                                const unsigned char *c = (const unsigned char *) binaryVal;
                                ss.setf(std::ios::hex);
                                for (int i = 0; i < binarySize; i++)
                                {
                                        ss << static_cast<unsigned>(c[i]);
                                        if (i < binarySize-1)
                                                ss << " ";
                                }
                                break;
                        }
                        default:
                                break;
                }
                return ss.str();
        }

	/**
	 * getBoolValue.
	 * @return The boolean value of this WBMsg if it is storing a boolean.
	 *         Returns NULL otherwise.
	 */ 
	bool getBoolValue() const { return boolVal; }
	
	/**
	 * getIntValue.
	 * @return The int value of this WBMsg if it is storing an int.
	 *         Returns NULL otherwise.
	 */ 
	int getIntValue() const { return intVal; }
	
	/**
	 * getFloatValue.
	 * @return The float value of this WBMsg if it is storing a float.
	 *         Returns NULL otherwise.
	 */ 
	float getFloatValue() const { return floatVal; }
	
	/**
	 * getStringValue.
	 * @return The string value of this WBMsg if it is storing a string.
	 *         Returns an empty string otherwise.
	 */ 
	const std::string &getStringValue() const { return stringVal; }

	/**
	 * getBinaryValue.
	 * @return The data buffer of this WBMsg if it is storing binary data.
	 *         Returns NULL otherwise.
	 */
	const void *getBinaryValue() const { return binaryVal; }

	/**
	 * getArrayValue.
	 * @return The array<int> value of this WBMsg if it is storing an array.
	 *         undefined otherwise.
	 */ 
	const std::vector<int> &getArrayValue() const { return *arrayVal; }

	/**
	 * getSizeInBytes.
	 * @return The size in bytes of the data buffer of this WBMsg if it is 
	 *         storing binary data.  Returns NULL otherwise.
	 */
	int getSizeInBytes() const { return binarySize; }

        /**
         * default destructor
         */
	~WBMsg() { if (doFree) { if (type == TypeBinary) free((void *) binaryVal); else if (type == TypeArray) delete arrayVal; } }
};

#endif
