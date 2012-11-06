/**
 *      $Id: 621932462f94699979b4c2cc4fef20f92ee086c2 $
 *
 * @file: gutexttowbd.cpp
 * @author: Steven Chi Hang Kuok, Vlad Estivill-Castro and Rene Hexel
 * @version: $Revision$
 * @date: $Date$
 * @section LICENSE:
 *  Created by Steven Chi Hang Kuok on 16/JUNE/2010.
 *  Copyright 2010-2012 Steven Chi Hang Kuok Carl Lusty, and Rene Hexel. All rights reserved.
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

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <strings.h>
#include <string>
#include <map>
#include "Whiteboard.h"
#include "WBMsg.h"
#include "gu_util.h"  // for DBG = DEBUG

#ifdef USE_READLINE
#include <libgen.h>
#include <readline/readline.h>
#include <readline/history.h>

static const char *progname;    // Linux does not have getprogname()

#define TYPE_HISTORY    ((string(".") + progname + "_msgtype_history").c_str())
#define CONT_HISTORY    ((string(".") + progname + "_msgcont_history").c_str())
#define DATATYPE_HISTORY    ((string(".") + progname + "_msgdatatype_history").c_str())

static char *history_matcher(const char *text, int state)
{
        static int list_index, len;
        
        if (!state)
        {
                list_index = 0;
                len = strlen(text);
        }
        
        HIST_ENTRY **list = history_list(), *entry;
        while ((entry = list[list_index]))
        {
                const char *name = entry->line;
                list_index++;
                
                if (!name[0]) continue;
                if (len < 1 || strncasecmp(name, text, len) == 0)
                        return gu_strdup(name);
        }
        
        /* no names matched */
        return NULL;
}

static char **history_completion (const char *text, int start, int end)
{
        return rl_completion_matches(text, history_matcher);
}

static void init_readline(void)
{
        using_history();
        rl_readline_name = (char *) progname;
        rl_attempted_completion_function = history_completion;
}

static const char *last_history(void)
{
        if (history_length <= 0) return NULL;
        HIST_ENTRY **list = history_list();
        return list[history_length-1]->line;
}
#endif  // USE_READLINE



using namespace guWhiteboard;
using namespace std;

static const char * const SHUTDOWN_WHITEBOARD = "SHUTDOWN_WHITEBOARD";

Whiteboard *whiteboard;

WBMsg::WBType convStringToType(string str)
{
    if(str.compare("String") == 0) return WBMsg::TypeString;
    if(str.compare("Int") == 0) return WBMsg::TypeInt;    
    if(str.compare("Bool") == 0) return WBMsg::TypeBool;    
    if(str.compare("Float") == 0) return WBMsg::TypeFloat;
    if(str.compare("Array") == 0) return WBMsg::TypeArray;
    if(str.compare("Binary") == 0) return WBMsg::TypeBinary;    
        
    return WBMsg::TypeEmpty;
}

vector<int> convToArrayType(string str)
{
    const char *sep = "|,";
    std::vector<int> array;
    char * cord2 = strtok ((char *)str.c_str(), sep);	
    while (cord2 != NULL)
    {
        array.push_back(atoi(cord2));
        cord2 = strtok (NULL, sep);
    }
    return array;
}

int main(int argc, char **argv) 
{
			Whiteboard::WBResult r; /**< Return message from wb methods. */ 

	whiteboard = new Whiteboard("guWhiteboard", false);
	fprintf(stderr,"\nCopyright 2010-2012 Machine Intelligence and Pattern Analysis Laboratory. All rights reserved.\n\n");	
	string oldType;
	string oldContent;
	string oldWBType;    
        string type;
        string message_content;
        string message_type;

        map<string,string> dataTypes;

	cout << "If you hit <return> and leave empty previous input for field is preserved" << endl;
	cout<<"Terminate with ^C\n" << endl;
	
#ifdef USE_READLINE
        progname = basename(argv[0]);
        init_readline();
#endif
	while (!cin.eof())
        {
                /*
                 * get the message type
                 */
                string prompt;
#ifdef USE_READLINE
                clear_history();
                if (read_history(TYPE_HISTORY) != 0)
                {
                        add_history(kSpeechOutput);
                        add_history(kSay);
                        add_history(SHUTDOWN_WHITEBOARD);
                }
                if (oldType.length() == 0)
                {
                        const char *h = last_history();
                        oldType = h ? h : "-non-empty-";
                }
                prompt = string("msg type (") + oldType + ")? ";
                char *line = readline(prompt.c_str());
                if (line)
                {
                        type = line;
                        gu_trim(type);
                        if (type.length() && type != oldType)
                        {
                                add_history(type.c_str());
                                write_history(TYPE_HISTORY);
                        }
                        free(line);
                }
#else
		cout << "message type: ";
		getline(cin, type);
                gu_trim(type);
#endif
		DBG (cerr << type << endl);
                /*
                 * get the message content
                 */
                if(type.length() == 0)
                        type = oldType;
                if (type != SHUTDOWN_WHITEBOARD)
                {
#ifdef USE_READLINE
                        r = Whiteboard::METHOD_FAIL;
                        WBMsg msg = whiteboard->getMessage(type, &r);
                        if (r == Whiteboard::METHOD_OK) switch (msg.getType())
                        {
                                case WBMsg::TypeEmpty:
                                        cout << "    EMPTY --> ()" << endl;
                                        break;
                                case WBMsg::TypeBool:
                                        cout << "     bool --> " << msg.getBoolValue() << endl;
                                        break;
                                case WBMsg::TypeInt:
                                        cout << "      int --> " << msg.getIntValue() << endl;
                                        break;
                                case WBMsg::TypeFloat:
                                        cout << "    float --> " << msg.getFloatValue() << endl;
                                        break;
                                case WBMsg::TypeString:
                                        cout << "   string --> '" << msg.getStringValue() << "'" << endl;
                                        break;
                                case WBMsg::TypeArray:
                                        cout << "   array --> '";
                                        for(int i = 0; i < msg.getArrayValue().size(); i++)
                                        {
                                            cout << msg.getArrayValue()[i];
                                            if(i != msg.getArrayValue().size() -1)
                                                cout << " | ";
                                        }
                                        cout << endl;                                
                                        break;                                
                                default:
                                        int len = msg.getSizeInBytes();
                                        cout << "   binary --> size " << len << endl;
                                        break;
                        }
                        else cout << " -> NOT ON WHITEBOARD YET <- " << endl;

                        clear_history();
                        if (read_history(CONT_HISTORY) != 0)
                        {
                                add_history("On");
                                add_history("Off");
                        }
                        char *line = readline(" content? ");
                        if (line)
                        {
                                message_content = line;
                                gu_trim(message_content);
                                if (message_content.length() &&
                                    message_content != oldContent)
                                {
                                        add_history(message_content.c_str());
                                        write_history(CONT_HISTORY);
                                }
                                free(line);
                        }
#else
                        cout << " content? ";
                        getline(cin, message_content);
                        gu_trim(message_content);
#endif

                    if (dataTypes.count(type))
                        oldWBType = dataTypes[type];
                    if (oldWBType.length() == 0)
                    {
                        if (message_content.find_first_of('|') != string::npos ||
                            message_content.find_first_of(',') != string::npos)
                                oldWBType = "Array";
                        else if (atoi(message_content.c_str()) || message_content[0] == '0')
                        {
                                if (message_content.find_first_of('.') != string::npos)
                                        oldWBType = "Float";
                                else
                                        oldWBType = "Int";
                        }
                        else oldWBType = "String";
                    }
                    prompt = string(" data type (") + oldWBType + ")? ";

#ifdef USE_READLINE                    
                    clear_history();
                    if (read_history(DATATYPE_HISTORY) != 0)
                    {
                        add_history("Empty");                                                
                        add_history("Float");                        
                        add_history("Bool");                        
                        add_history("Int");                        
                        add_history("Array");
                        add_history("String");                        
                    }
                    line = readline(prompt.c_str());
                    if (line)
                    {
                        message_type = line;
                        gu_trim(message_type);
                        free(line);
                    }                    
#else                    
                    cout << prompt;
                    getline(cin, message_type);
                    gu_trim(message_type);                    
#endif                    
                }
		DBG (cerr << message_content << endl);
		DBG (cerr << message_type << endl);            

		if(type.length() == 0)
			type = oldType;
		if(message_content.length() == 0)
			message_content = oldContent;
            if(message_type.length() == 0)
                message_type = oldWBType;            
		if(type.length() != 0 && (message_content.length() || r == Whiteboard::METHOD_FAIL))
        {
                const char *s = message_content.c_str();
            WBMsg::WBType inputType = convStringToType(message_type);
            cout << inputType << "<---" << endl;
            switch (inputType)
            {
                case WBMsg::TypeEmpty:
                    whiteboard->addMessage(type, WBMsg());
                    break;
                case WBMsg::TypeBool:
                        if (strcasecmp(s, "true") == 0 || strcasecmp(s, "yes") == 0 || strcasecmp(s, "on") == 0|| atoi(s))
                        {
                                whiteboard->addMessage(type, WBMsg(true));
                        }
                        else
                        {
                                whiteboard->addMessage(type, WBMsg(false));                    
                        }
                        break;
                case WBMsg::TypeInt:
                        whiteboard->addMessage(type, WBMsg(atoi((char *)message_content.c_str())));                    
                    break;
                case WBMsg::TypeFloat:
                        whiteboard->addMessage(type, WBMsg((float)atof((char *)message_content.c_str())));                    
                    break;
                case WBMsg::TypeString:
                        whiteboard->addMessage(type, WBMsg(message_content));                    
                    break;
                case WBMsg::TypeArray:
                    whiteboard->addMessage(type, WBMsg(convToArrayType(message_content)));                    
                    break;                    
                default:
                    cout << "binary not supported " << endl;
                    break;
            }
        }
		oldType = type;
            oldWBType = message_type;            
		oldContent = message_content;

                if (type == "SHUTDOWN_WHITEBOARD") exit (EXIT_SUCCESS);
	}
	delete whiteboard;
	return EXIT_SUCCESS;
}	
