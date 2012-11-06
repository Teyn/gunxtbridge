/**
 * \file  gumessagecontent.h 
 *  
 *  Created by
 *  \author Vlad Estivill-Castro on 
 *  \date 06/04/11.
 *  Copyright 2010 Vlad Estivill-Castro. All rights reserved.
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
 *    software must display the following acknowledgment:
 *
 *        This product includes software developed by Vlad Estivill-Castro.
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

#ifndef _MSG_CONTENTE_
#define _MSG_CONTENTE_

#include <stdlib.h>

/*! 
 * This type of code to parse a Whiteboard message in a call-back is everywhere
 * in the MiPal code. This is an attempt to put it in one single place.
 * The interface to the Whietbaord needs re-factoring and built into a
 * framework where functionality like this to parse the type and content
 * of a message in a call-backs is simplified.
*/
class MessageContent {

	private:
		std::string content;
	
	public:
		/*!
		 *  This is the method that obtains the content of a message as a string
		*/
		MessageContent(WBMsg *msg)
		{
                std::ostringstream text;	
		        /* Extract the Message          */
        		if (msg->getType() == WBMsg::TypeString)
                		text << msg->getStringValue();
        		else if (msg->getType() == WBMsg::TypeInt)
                		text << msg->getIntValue();
        		else if (msg->getType() == WBMsg::TypeFloat)
                		text << msg->getFloatValue();
        		else if (msg->getType() == WBMsg::TypeBool)
                		text << ( msg->getBoolValue() ? "1" : "0" );
        		else text << msg->getSizeInBytes() << " bytes of gibberish";

        		content= text.str();
		}

		/*!
		 *  After MessageContent has been called, returns the content as a string
		*/
		std::string theContent() { return content;}

		/*!
		 *  After MessageContent has been called, returns the content as an int
		*/
		int theContentToInt() { return atoi ( (char *) content.c_str() ); }

};
#endif//  _MSG_CONTENTE_
