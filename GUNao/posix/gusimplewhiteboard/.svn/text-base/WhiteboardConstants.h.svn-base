/*
 *  WhiteboardConstants.h
 *  guboostwhiteboard
 *
 *  Created by Rene Hexel on 1/05/11.
 *  Copyright 2011 Rene Hexel. All rights reserved.
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
#ifndef _WHITEBOARD_CONSTANTS_H_
#define _WHITEBOARD_CONSTANTS_H_

namespace guWhiteboard
{
	/** Soap callback key for message subscriber method */
	extern const char *kOnWhiteboard;
	
	/** Hello World message name */
	extern const char *kHelloWBMsg;
        
	/** Speech message (string) */
	extern const char *kSay;

	/** Queuing speech message (string) */
	extern const char *kQSay;
        
	/** Debug speech message (string) -- only use for debugging,
         *  as this will only work if "SpeechOutput" "On" was sent
         *  previously
         */
	extern const char *kSpeechWBMsg;

	/** Queuing debug speech message (string) -- only use for debugging,
         *  as this will only work if "SpeechOutput" "On" was sent
         *  previously
         */
	extern const char *kQSpeech;

        /** Whiteboard message for conditional speech output.
         *  Content (string) should be "On" to turn on speech or "Off"
         *  to turn off speech (will not affect the "Say" command).
         */
        extern const char *kSpeechOutput;

	/** Whiteboard message (string) for updating all proofs */
	extern const char *kUpdateAllProofs;

	/** Whiteboard message (string) for updating proofs for a given theory */
	extern const char *kUpdateAllProofsForTheory;

	/** Whiteboard message (string) for updating a proof for a given output */
	extern const char *kUpdateProof;
	
	/** Whiteboard message (string) for turn on modules */
	extern const char *kOn;
	
	/** Whiteboard message (string) for turn off modules */
	extern const char *kOff;
}

#endif // _WHITEBOARD_CONSTANTS_H_
