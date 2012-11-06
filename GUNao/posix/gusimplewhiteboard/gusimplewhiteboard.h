/*
 *  gusimplewhiteboard.h
 *  
 *  Created by René Hexel on 20/12/11.
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
#ifndef gusimplewhiteboard_gusimplewhiteboard_h
#define gusimplewhiteboard_gusimplewhiteboard_h

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef __APPLE__
#include <AvailabilityMacros.h>
#endif
#include <dispatch/dispatch.h>
#include <sys/types.h>
#include <unistd.h>

#if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
#define GSW_IOS_SIMULATOR                               // IOS device (but not simulator)
#endif

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE && !defined (GSW_IOS_SIMULATOR)
#define GSW_IOS_DEVICE                                  // IOS device (but not simulator)
#endif

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE || defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
#define GSW_IOS                                         // IOS device or simulator
#endif
        
#define GU_SIMPLE_WHITEBOARD_VERSION            2       // version
#define GU_SIMPLE_WHITEBOARD_GENERATIONS        4       // lifespan (max)
#define GU_SIMPLE_WHITEBOARD_BUFSIZE            64      // message len (max)
#define GSW_TOTAL_MESSAGE_TYPES                 1024    // message types (max)
#define GSW_TOTAL_PROCESSES                     256     // maximum subscriber procs
#define GSW_NON_RESERVED_MESSAGE_TYPES  (GSW_TOTAL_MESSAGE_TYPES-GSW_NUM_RESERVED)

#define GSW_DEFAULT_NAME "simple_whiteboard"
#define WHITEBOARD_SIGNAL       SIGUSR2
#define WHITEBOARD_POLL_PERIOD  10000

enum gsw_message_types
{
        GSW_PRINT,                      /// print to stdout
        GSW_SAY,                        /// speech output message
        GSW_SPEECH,                     /// debug speech message
        GSW_NUM_RESERVED
};

enum gsw_semaphores
{
        GSW_SEM_PUTMSG,                 /// semaphore for adding to the whiteboard
        GSW_SEM_CALLBACK,               /// semaphore for callback data
        GSW_SEM_MSGTYPE,                /// semaphore for message type registration
        GSW_SEM_PROC,                   /// semaphore for process registration
        GSW_NUM_SEM                     /// number of semaphores
};

struct gsw_whiteboard_s;

typedef void (*gsw_subscription_f)(struct gsw_whiteboard_s *wbd);

typedef union gsw_simple_message
{
        /*
         * standard types
         */
        unsigned long long      ulonglong;      /// unsigned long long value
        long long               slonglong;      /// long long value
        unsigned long           ulong;          /// unsigned long value
        long                    slong;          /// singed long value
        unsigned                uint;           /// unsigned integer
        int                     sint;           /// signed integer
        unsigned short          ushort;         /// unsigned short
        short                   sshort;         /// signed short
        unsigned char           uchar;          /// unsigned char
        signed char             schar;          /// signed char
        char                    xchar;          /// standard char

        long double             slongdouble;    /// long double
        double                  sdouble;        /// signed double
        float                   sfloat;         /// signed float

        /*
         * POSIX defined length types
         */
        u_int64_t               u64;            /// unsigned 64 bit value
        u_int32_t               u32;            /// unsigned 32 bit value
        u_int16_t               u16;            /// unsigned 16 bit value
        u_int8_t                u8;             /// unsigned  8 bit value
        
        int64_t                 s64;            /// signed 64 bit value
        int32_t                 s32;            /// signed 32 bit value
        int16_t                 s16;            /// signed 16 bit value
        int8_t                  s8;             /// signed  8 bit value

        /**
         * vector types
         */
        unsigned long long      ullvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(unsigned long long)];
        unsigned long           ulvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(unsigned long)];
        unsigned                uivec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(unsigned)];
        unsigned short          usvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(unsigned short)];
        unsigned char           ucvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(unsigned char)];

        long long               llvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(long long)];
        long                    lvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(long)];
        int                     ivec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(int)];
        short                   svec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(short)];
        signed char             cvec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(signed char)];

        u_int64_t               u64vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int64_t)];
        u_int32_t               u32vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int32_t)];
        u_int16_t               u16vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int16_t)];
        u_int8_t                u8vec[GU_SIMPLE_WHITEBOARD_BUFSIZE];

        int64_t                 s64vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int64_t)];
        int32_t                 s32vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int32_t)];
        int16_t                 s16vec[GU_SIMPLE_WHITEBOARD_BUFSIZE/sizeof(u_int16_t)];
        int8_t                  s8vec[GU_SIMPLE_WHITEBOARD_BUFSIZE];

        /*
         * simple compound types
         */
        struct { int x,y,z,a,b,c,d,e; } coord;  /// simple integer coordinates
        struct {double x,y,z,a,b,c,d,e;} dcoord;/// simple double coordinates
        struct {float x,y,z,a,b,c,d,e;} fcoord; /// simple float coordinates

        /** string type */
        char                    string[GU_SIMPLE_WHITEBOARD_BUFSIZE];

        /** whiteboard hash type */
        struct { u_int16_t value; char string[GU_SIMPLE_WHITEBOARD_BUFSIZE-sizeof(u_int16_t)]; } hash;

        /** compatibility WBMsg type */
        struct { char data[GU_SIMPLE_WHITEBOARD_BUFSIZE-2]; unsigned char len; unsigned char type; } wbmsg;
} gu_simple_message;

typedef struct gsw_simple_whiteboard_s
{
        u_int16_t               version;        /// whiteboard version
        u_int16_t               eventcount;     /// current event count
        u_int16_t               subscribed;     /// subscribed processes
        u_int16_t               num_types;      /// total number of current, registered types

        u_int8_t                indexes[GSW_TOTAL_MESSAGE_TYPES];       /// ring buffer indexes

        /**
         * the actual messages stored in the whiteboard
         */
        gu_simple_message       messages[GSW_TOTAL_MESSAGE_TYPES][GU_SIMPLE_WHITEBOARD_GENERATIONS];

        /**
         * hashes for registered message types
         */
        gu_simple_message       hashes[GSW_TOTAL_MESSAGE_TYPES];

        /**
         * message types for numbers
         */
        gu_simple_message       typenames[GSW_TOTAL_MESSAGE_TYPES];

        /**
         * list of subscribed processes
         */
        pid_t                   processes[GSW_TOTAL_PROCESSES];

        /**
         * end of whiteboard marker
         */
        u_int64_t               magic;
} gu_simple_whiteboard;

#ifdef GSW_IOS_DEVICE
typedef dispatch_semaphore_t *gsw_sema_t;
#else
typedef int gsw_sema_t;
#endif

typedef struct gsw_whiteboard_s
{
        gu_simple_whiteboard    *wb;            /// the actual whiteboard in shared mem
        gsw_sema_t               sem;           /// semaphore to use
        int                      fd;            /// the associated memory-mapped file
        dispatch_queue_t         callback_queue;/// subscription callback queue
        gsw_subscription_f       callback;      /// subscription callback function
        void                    *context;       /// callback context
        bool                     got_monitor;   /// have a running monitor
        bool                     exit_monitor;  /// exit the monitor
} gu_simple_whiteboard_descriptor;

/**
 * global whiteboard name
 */
extern const char *gsw_global_whiteboard_name;

/**
 * access a named whiteboard: this is the designated constructore for C programs
 * @param name  name of the whiteboard
 */
extern gu_simple_whiteboard_descriptor *gsw_new_whiteboard(const char *name);

/**
 * access a named whiteboard: this is the designated constructore for C programs
 * that want to assign a whiteboard number (uses a different semaphore than the default)
 * @param name  name of the whiteboard
 * @param num   whiteboard number (0 for local, default whiteboard)
 */
extern gu_simple_whiteboard_descriptor *gsw_new_numbered_whiteboard(const char *name, int num);

/**
 * free the given whiteboard descriptor
 * @param name  name of the whiteboard
 * @param fdp   pointer to internal file descriptor storage (NULL if not needed)
 */
extern void gsw_free_whiteboard(gu_simple_whiteboard_descriptor *wbd);

/**
 * register a new whiteboard message type
 * @param name  string to use for identification
 * @return numerical identifier to use
 */
extern int gsw_register_message_type(gu_simple_whiteboard_descriptor *wbd, const char *name);

/**
 * get the numerical index of a whiteboard message type
 * @param name  string to use for identification
 * @return numerical identifier to use
 */
extern int gsw_offset_for_message_type(gu_simple_whiteboard_descriptor *wbd, const char *name);

/**
 * create a simple whiteboard
 * @param name  name of the whiteboard
 * @param fdp   pointer to internal file descriptor storage (NULL if not needed)
 * @param ini   pointer to boolean recording wb initialisation
 */
extern gu_simple_whiteboard *gsw_create(const char *name, int *fdp, bool *ini);

/**
 * free the whiteboard
 * @param wb    whiteboard to free
 * @param fd    file descriptor to close (-1 to skip)
 */
extern void gsw_free(gu_simple_whiteboard *wb, int fd);

/**
 * set up a semaphore array for the whiteboard
 * @param key   semaphore key
 * @return semaphore array to use
 */
extern gsw_sema_t gsw_setup_semaphores(int key);

/**
 * grab a whiteboard semaphore
 * @param sem   semaphore descriptor
 * @param s     semaphore to procure
 */
extern int gsw_procure(gsw_sema_t sem, enum gsw_semaphores s);

/**
 * release a whiteboard semaphore
 * @param sem   semaphore descriptor
 * @param s     semaphore to vacate
 */
extern int gsw_vacate(gsw_sema_t sem, enum gsw_semaphores s);

/**
 * initialise the whiteboard semaphores
 * @param sem   whiteboard semaphore descriptor
 */
extern void gsw_init_semaphores(gsw_sema_t s);

/**
 * get the current shared memory location for the given whiteboard message type i
 */
gu_simple_message *gsw_current_message(gu_simple_whiteboard *wb, int i);

/**
 * get the next shared memory location for the given whiteboard message type i
 */
gu_simple_message *gsw_next_message(gu_simple_whiteboard *wb, int i);

/**
 * get the next shared memory location for the given whiteboard message type i
 */
void gsw_increment(gu_simple_whiteboard *wb, int i);
        

#pragma mark - subscription and callbacks

/**
 * subscribe a new process to receive signals
 */
extern void gsw_add_process(gu_simple_whiteboard_descriptor *wbd, const pid_t proc);

/**
 * add subscription signal handler
 */
extern void gsw_add_wbd_signal_handler(gu_simple_whiteboard_descriptor *wbd);

/**
 * remove subscription signal handler
 */
extern void gsw_remove_wbd_signal_handler(gu_simple_whiteboard_descriptor *wbd);

/**
 * add process for subscription signalling
 */
void gsw_add_process(gu_simple_whiteboard_descriptor *wbd, const pid_t proc);

/**
 * remove process for subscription signalling
 */
void gsw_remove_process(gu_simple_whiteboard_descriptor *wbd, const pid_t proc);

/**
 * signal all subscribing processes
 */
void gsw_signal_subscribers(gu_simple_whiteboard *wb);

#ifdef __cplusplus
}
#endif

#endif
