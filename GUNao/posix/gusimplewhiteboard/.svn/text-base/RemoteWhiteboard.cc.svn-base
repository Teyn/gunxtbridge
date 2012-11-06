/*
 *  RemoteWhiteboard.cc
 *  
 *  Created by Carl Lusty on 21/12/11.
 *  Copyright (c) 2011 Carl Lusty.
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
#include <cstring>
#include <cstdio>
#include <gu_util.h>
#include "RemoteWhiteboard.h"
#include "guudpbridge/guudpBridgeManager.h"
#include <signal.h> // for kill()
//#include <stdlib.h> // for daemon()
//#include <sys/types.h>
//#include <sys/stat.h>
#include <pthread.h>

using namespace guWhiteboard;
using namespace std;

static inline bool udp_pid_fail(const pid_t pid)
{
        return pid == 0 ||
                (pid != getpid() &&
                 kill(pid, WHITEBOARD_SIGNAL) != 0);
}

static void *monitor_bridge(void *local_whiteboard)
{
    bool init_run = true;
    guWhiteboard::Whiteboard *whiteboard = (guWhiteboard::Whiteboard *)local_whiteboard;
    while(true)
    {
        pid_t pid = whiteboard->getMessage("UDP_BRIDGE_PID").getIntValue();
        if (udp_pid_fail(pid))
        {
            fprintf(stderr, "Attempt UDP Bridge start . . . \n");
            setup_udp();
        }
        if(init_run)
        {
            init_run = false;
//            gsw_vacate(whiteboard->_wbd->sem, GSW_SEM_UDP);
        }
        protected_usleep(1000000);        
    }
}

RemoteWhiteboard::RemoteWhiteboard(const char *wbName, RWBMachine n, Whiteboard *local_whiteboard): machine(RWBMachine(n+1)), Whiteboard(wbName, true, n+1), local_wb_needs_free(local_wb != NULL)
{
    if(local_whiteboard == NULL)
    {
        local_whiteboard = new Whiteboard();
    }
    local_wb = local_whiteboard;
    
//    gsw_procure(local_wb->_wbd->sem, GSW_SEM_UDP);  

    pthread_t child;
    pthread_create(&child, NULL, monitor_bridge, local_wb);

        pid_t pid;
        int i, timeout = 20;
        for (i = 0; i < timeout; i++)
        {
                pid = local_wb->getMessage("UDP_BRIDGE_PID").getIntValue();
                if (udp_pid_fail(pid))
                        usleep(50000);
                else break;
        }
        if (i >= timeout)
                fprintf(stderr, " *** Warning: UDP bridge failed to start, pid = %d\n", pid);
//    gsw_procure(local_wb->_wbd->sem, GSW_SEM_UDP);      
//    gsw_vacate(local_wb->_wbd->sem, GSW_SEM_UDP);    
}

RemoteWhiteboard::~RemoteWhiteboard()
{
    if (local_wb_needs_free && local_wb) delete local_wb;
}

void RemoteWhiteboard::addReplicationType(const std::string &type)
{    
    Whiteboard::addMessage(string(ADD_BROADCAST_TYPE_MSG_TYPE), WBMsg(type));
}

std::vector<std::string> RemoteWhiteboard::getKnownTypesForMachine()
{
    gsw_procure(_wbd->sem, GSW_SEM_MSGTYPE);
    std::vector<std::string> known_types;
    int i = 0;
    while (i < GSW_TOTAL_MESSAGE_TYPES)
    {
        if(strlen(_wbd->wb->typenames[i].hash.string) > 0)
        {
            known_types.push_back(std::string(_wbd->wb->typenames[i].hash.string));
            if(known_types.size() > _wbd->wb->num_types)
                break;
        }
        i++;
    }
    gsw_vacate(_wbd->sem, GSW_SEM_MSGTYPE);

    return known_types;
}

void RemoteWhiteboard::subscribeToMessage(const std::string &type, WBFunctorBase *func, WBResult &result)
{
    addReplicationType(type);
    Whiteboard::subscribeToMessage(type, func, result);
    protected_usleep(30000);
}
