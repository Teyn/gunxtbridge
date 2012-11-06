/*
 *  Whiteboard.cc
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
#include <cstring>
#include <gu_util.h>
#include "Whiteboard.h"

#ifndef DISPATCH_QUEUE_SERIAL
#define DISPATCH_QUEUE_SERIAL NULL
#endif

extern "C" {
#ifdef GSW_IOS_DEVICE
extern void init_ios_whiteboard_name(void);
extern const char *wbname_prefixed_with_path(const char *wbname);
#else                           // IOS needs to define this in ObjC-Whiteboard
#define init_ios_whiteboard_name();
const char *gsw_global_whiteboard_name = "guWhiteboard";
#endif
}

using namespace guWhiteboard;
using namespace std;

static void subscription_callback(gu_simple_whiteboard_descriptor *wbd)
{
        Whiteboard *self = (Whiteboard *) wbd->context;
        if (self) self->subscriptionCallback();
}

Whiteboard::Whiteboard(const char *name, bool checkVersion, int number)
{
        init_ios_whiteboard_name();

        if (!name) name = gsw_global_whiteboard_name;
#ifdef GSW_IOS_DEVICE
        else name = wbname_prefixed_with_path(name);
#endif
        if (!(callback_group = dispatch_group_create()))
        {
                cerr << "Unable to create dispatch group " << number << ": '" << name << "'" << endl;
                throw "Whiteboard cannot create callback queue";
        }
        if (!(callback_queue = dispatch_queue_create(name, DISPATCH_QUEUE_SERIAL)))
        {
                cerr << "Unable to create dispatch queue " << number << ": '" << name << "'" << endl;
                throw "Whiteboard cannot create dispatch queue";
        }
        if (!(_wbd = gsw_new_numbered_whiteboard(name, number)))
        {
                cerr << "Unable to create whiteboard " << number << ": '" << name << "'" << endl;
                throw "Cannot create whiteboard";
        }
        _wbd->context = this;
        _wbd->callback = subscription_callback;
}


Whiteboard::~Whiteboard()
{
        _wbd->callback = NULL;                  // avoid starvation
        dispatch_group_wait(callback_group, DISPATCH_TIME_FOREVER);

        if (_wbd) gsw_free_whiteboard(_wbd);
        dispatch_release(callback_queue);
        dispatch_release(callback_group);
}


void Whiteboard::addMessage(gsw_hash_info *hashinfo, const WBMsg &msg, bool nonatomic, bool notifySubscribers)
{
    int t = hashinfo->msg_offset;
     
#ifdef DEBUG
    if (nonatomic < 0 || nonatomic > 1)
        cerr << " *** Nonatomic parameter " << nonatomic << " not bool (are you using a life span?) ***" << endl;
#endif
        if (!nonatomic) gsw_procure(_wbd->sem, GSW_SEM_PUTMSG);
        
        gu_simple_whiteboard *wb = _wbd->wb;
        gu_simple_message *m = gsw_next_message(wb, t);
        m->wbmsg.type = msg.getType();
        
        
        switch (m->wbmsg.type)
        {
            case WBMsg::TypeEmpty:
                m->wbmsg.len = 0;
                break;
                
            case WBMsg::TypeBool:
                m->wbmsg.len = sizeof(int);
                m->sint = msg.getBoolValue();
                break;
                
            case WBMsg::TypeInt:
                m->wbmsg.len = sizeof(int);
                m->sint = msg.getIntValue();
                break;
                
            case WBMsg::TypeFloat:
                m->wbmsg.len = sizeof(float);
                m->sfloat = msg.getFloatValue();
                break;
                
            case WBMsg::TypeString:
                gu_strlcpy(m->wbmsg.data, msg.getStringValue().c_str(), sizeof(m->wbmsg.data));
                m->wbmsg.len = strlen(m->wbmsg.data) + 1;
                break;
                
            case WBMsg::TypeArray:
            {
                int k = 0;
                for (vector<int>::const_iterator i = msg.getArrayValue().begin(); i < msg.getArrayValue().end(); i++)
                    m->ivec[k++] = *i;
                m->wbmsg.len = k;
                break;
            }
            case WBMsg::TypeBinary:
            {
                int len = msg.getSizeInBytes();
                if (len > sizeof(m->wbmsg.data)) len = sizeof(m->wbmsg.data);
                m->wbmsg.len = len;
                if (len) memcpy(m->wbmsg.data, msg.getBinaryValue(), len);
                break;
            }
        }
        gsw_increment(wb, t);
        if (!nonatomic) gsw_vacate(_wbd->sem, GSW_SEM_PUTMSG);
        if (notifySubscribers && wb->subscribed) gsw_signal_subscribers(wb);
}
 
WBMsg Whiteboard::getMessage(gsw_hash_info *hashinfo, WBResult *result)
{
    int t = hashinfo->msg_offset;
    
    gu_simple_message *m = gsw_current_message(_wbd->wb, t);
    
    if (result)
    {
        if (m->wbmsg.type || m->wbmsg.len)
            *result = METHOD_OK;
        else
            *result = METHOD_FAIL;
    }
    return getWBMsg(m);
}

gsw_hash_info *Whiteboard::getTypeOffset(std::string type)
{
    if (type != "*")
    {
        return new gsw_hash_info(gsw_offset_for_message_type(_wbd, type.c_str()));
    }
    else 
    {
        return new gsw_hash_info(GLOBAL_MSG_ID);
    }
}

#pragma mark - subscription and callbacks

void Whiteboard::subscribeToMessage(gsw_hash_info *hashinfo, WBFunctorBase *func, WBResult &result)
{
    result = Whiteboard::METHOD_OK;
    
    gsw_procure(_wbd->sem, GSW_SEM_CALLBACK);
    int offs = -1, current = -1;
    if (hashinfo->msg_offset != GLOBAL_MSG_ID) // type != "*"
    {
        offs = hashinfo->msg_offset;
        current = _wbd->wb->indexes[offs];
    }
    else for (int i = 0; i < _wbd->wb->num_types; i++)      // subscribe to all
        cball_indexes[i] = _wbd->wb->indexes[i];
    _sub.push_back(callback_descr(func, offs, current));
    gsw_vacate(_wbd->sem, GSW_SEM_CALLBACK);
    
    gsw_add_wbd_signal_handler(_wbd);
    gsw_add_process(_wbd, getpid());
}

struct callback_helper
{
        Whiteboard *self;
        gu_simple_whiteboard *wb;
        int offs, curr;
        Whiteboard::callback_descr descr;

        callback_helper(Whiteboard *s, gu_simple_whiteboard *w, int o, int c, const Whiteboard::callback_descr &d): self(s), wb(w), offs(o), curr(c), descr(d) {}
};

static void do_callback(void *m)
{
        callback_helper *h = (callback_helper *) m;

        WBMsg msg = h->self->getWBMsg(&h->wb->messages[h->offs][h->curr]);
        h->descr.func->call(h->wb->typenames[h->offs].hash.string, &msg);

        delete h;
}

void Whiteboard::subscriptionCallback(void)
{
        gu_simple_whiteboard *wb = _wbd->wb;
        gsw_procure(_wbd->sem, GSW_SEM_CALLBACK);
        for (vector<callback_descr>::iterator i = _sub.begin(); i != _sub.end(); i++)
        {
                callback_descr &descr = *i;
                int offs = descr.type;
                int curr = descr.current;
                /*
                 * offs == -1 means all types "*", otherwise only check
                 * new postings for a specific message type
                 */
                if (offs == -1) for (offs = 0; offs < wb->num_types; offs++)
                {
                        curr = cball_indexes[offs];
                        while (curr != wb->indexes[offs])       // every new message
                        {
                                if (++curr >= GU_SIMPLE_WHITEBOARD_GENERATIONS)
                                        curr = 0;
                                cball_indexes[offs] = curr;
                                callback_helper *h = new callback_helper(this, wb, offs, curr, descr);
                                dispatch_group_async_f(callback_group, callback_queue, h, do_callback);
                        }
                }
                else while (curr != wb->indexes[offs])  // for every new message
                {
                        if (++curr >= GU_SIMPLE_WHITEBOARD_GENERATIONS)
                                curr = 0;
                        descr.current = curr;
                        callback_helper *h = new callback_helper(this, wb, offs, curr, descr);
                        dispatch_group_async_f(callback_group, callback_queue, h, do_callback);
                }
        }
        gsw_vacate(_wbd->sem, GSW_SEM_CALLBACK);
}


void Whiteboard::unsubscribeToMessage(gsw_hash_info *hashinfo, WBResult &result)
{
    result = Whiteboard::METHOD_FAIL;
    
    gsw_procure(_wbd->sem, GSW_SEM_CALLBACK);
    for (vector<callback_descr>::iterator i = _sub.begin(); i != _sub.end(); i++)
    {
        callback_descr &descr = *i;
        int offs = descr.type;
        if ((offs == -1 && hashinfo->msg_offset == GLOBAL_MSG_ID) ||
            hashinfo->msg_offset == offs)
        {
            _sub.erase(i);
            result = Whiteboard::METHOD_OK;
            break;
        }
    }
    if (!_sub.size()) gsw_remove_process(_wbd, getpid());
    gsw_vacate(_wbd->sem, GSW_SEM_CALLBACK);
}

#pragma mark - functions NOT using hash container

void Whiteboard::addMessage(const std::string &type, const WBMsg &msg, bool nonatomic, bool notifySubscribers)
{
    gsw_hash_info tmp = gsw_hash_info(gsw_hash_info(gsw_offset_for_message_type(_wbd, type.c_str())));
    addMessage(&tmp, msg, nonatomic, notifySubscribers);
}

WBMsg Whiteboard::getMessage(string type, WBResult *result)
{
    gsw_hash_info tmp = gsw_hash_info(gsw_hash_info(gsw_offset_for_message_type(_wbd, type.c_str())));    
    return getMessage(&tmp, result);
}

void Whiteboard::subscribeToMessage(const string &type, WBFunctorBase *func, WBResult &result)
{
    gsw_hash_info tmp;
    if (type != "*")
    {
        tmp = gsw_hash_info(gsw_hash_info(gsw_offset_for_message_type(_wbd, type.c_str())));    
    }
    else 
    {
        tmp = gsw_hash_info(GLOBAL_MSG_ID);
    }    

    return subscribeToMessage(&tmp, func, result);
}

void Whiteboard::unsubscribeToMessage(string type, WBResult &result)
{
    gsw_hash_info tmp;
    if (type != "*")
    {
        tmp = gsw_hash_info(gsw_hash_info(gsw_offset_for_message_type(_wbd, type.c_str())));    
    }
    else 
    {
        tmp = gsw_hash_info(GLOBAL_MSG_ID);
    }    

    return unsubscribeToMessage(&tmp, result);
}
