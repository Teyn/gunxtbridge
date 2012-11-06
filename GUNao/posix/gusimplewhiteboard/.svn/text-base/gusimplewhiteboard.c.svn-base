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
#ifdef __linux
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#endif
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <gu_util.h>
#include "gusimplewhiteboard.h"

#define WHITEBOARD_MAGIC        0xfeeda11deadbeef5ULL
#define SEMAPHORE_MAGIC_KEY     4242
#define SEM_ERROR               -1


#ifndef SEM_A
#define SEM_A		0200	/* alter permission */
#define SEM_R		0400	/* read permission */
#endif

#ifdef _SEM_SEMUN_UNDEFINED
union semun
{
        int val;                           // value for SETVAL
        struct semid_ds *buf;              // buffer for IPC_STAT & IPC_SET
        unsigned short int *array;         // array for GETALL & SETALL
        struct seminfo *__buf;             // buffer for IPC_INFO
};
#endif

static const char *known_message_types[GSW_NUM_RESERVED] =
{
        "Print", "Say", "Speech"
};


void gsw_init_semaphores(gsw_sema_t s)
{
        union semun init;
        init.val = 1;
        for (enum gsw_semaphores i = 0; i < GSW_NUM_SEM; i++)
        {
#ifdef GSW_IOS_DEVICE
                if (s[i]) dispatch_release(s[i]);
                s[i] = dispatch_semaphore_create(init.val);
#else
                if (semctl(s, i, SETVAL, init) == -1)
                        fprintf(stderr, "Warning; failed to initialise whiteboard semaphore %d: %s\n", i, strerror(errno));
#ifdef DEBUG
                if (semctl(s, i, GETVAL, NULL) != init.val)
                        fprintf(stderr, "Warning; failed to initialise whiteboard semaphore %d: %s\n", i, strerror(errno));
#endif
#endif
        }
}


gsw_sema_t gsw_setup_semaphores(int key)
{
#ifdef GSW_IOS_DEVICE
        gsw_sema_t s = calloc(sizeof(dispatch_semaphore_t), GSW_NUM_SEM);
        if (!s) return (gsw_sema_t) SEM_ERROR;
        gsw_init_semaphores(s);
#else
        int semflg = SEM_R|SEM_A|(SEM_R>>3)|(SEM_A>>3)|(SEM_R>>6)|(SEM_A>>6);
        gsw_sema_t s = semget(key, GSW_NUM_SEM, semflg);

        if (s == SEM_ERROR)
        {
                s = semget(key, GSW_NUM_SEM, semflg | IPC_CREAT);
                if (s == SEM_ERROR) return s;

                gsw_init_semaphores(s);
        }
#endif
        return s;
}


gu_simple_whiteboard_descriptor *gsw_new_numbered_whiteboard(const char *name, int n)
{
        gu_simple_whiteboard_descriptor *wbd = calloc(sizeof(gu_simple_whiteboard_descriptor), 1);
        if (!wbd)
        {
                fprintf(stderr, "Not enough memory to create whiteboard '%s': %s\n", name, strerror(errno));
                return NULL;
        }

        wbd->sem = gsw_setup_semaphores(SEMAPHORE_MAGIC_KEY + n);
        if (wbd->sem == (gsw_sema_t) SEM_ERROR)
                fprintf(stderr, "Warning; cannot get semaphore %d for whiteboard '%s': %s (proceeding without)\n", SEMAPHORE_MAGIC_KEY + n, name, strerror(errno));

        bool init = false;
        wbd->wb = gsw_create(name, &wbd->fd, &init);
        if (!wbd->wb)
        {
                gsw_free_whiteboard(wbd);
                return NULL;
        }
        if (init)
        {
                gsw_init_semaphores(wbd->sem);

                for (enum gsw_message_types i = 0; i < GSW_NUM_RESERVED; i++)
                        gsw_register_message_type(wbd, known_message_types[i]);
        }
        wbd->callback_queue = dispatch_queue_create(NULL, NULL);
        return wbd;
}


gu_simple_whiteboard_descriptor *gsw_new_whiteboard(const char *name)
{
        return gsw_new_numbered_whiteboard(name, 0);
}


void gsw_free_whiteboard(gu_simple_whiteboard_descriptor *wbd)
{
        if (wbd)
        {
                gsw_remove_wbd_signal_handler(wbd);
                if (wbd->wb) gsw_free(wbd->wb, wbd->fd);
                if (wbd->callback_queue) dispatch_release(wbd->callback_queue);
                free(wbd);
        }
}


gu_simple_whiteboard *gsw_create(const char *name, int *fdp, bool *initial)
{
        assert(sizeof(gu_simple_message) == GU_SIMPLE_WHITEBOARD_BUFSIZE);
        char path[PATH_MAX]
#ifdef GSW_IOS_DEVICE
        = "";
#else
        = "/tmp/";
#endif
        if (!name || strlen(name) > PATH_MAX-strlen(path)-1) name = GSW_DEFAULT_NAME;
        gu_strlcat(path, name, sizeof(path));

        int fd = open(path, O_CREAT|O_RDWR, 0666);
        if (fd == -1)
        {
                fprintf(stderr, "Cannot open/create '%s': %s\n", path, strerror(errno));
                return NULL;
        }

        if (ftruncate(fd, sizeof(gu_simple_whiteboard)) == -1)
            fprintf(stderr, "Warning; cannot reserve %lu bytes for '%s': %s\n", (unsigned long) sizeof(gu_simple_whiteboard), path, strerror(errno));

        gu_simple_whiteboard *wb = mmap(NULL, sizeof(*wb), PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fd, 0);
        if (!wb)
        {
                fprintf(stderr, "Cannot mmap '%s': %s\n", path, strerror(errno));
                close(fd);
                return NULL;
        }
        else if (fdp) *fdp = fd;

        if (wb->magic != WHITEBOARD_MAGIC)      // new whiteboard? -> initialise
        {
                memset(wb, 0, sizeof(*wb));
                wb->version      = GU_SIMPLE_WHITEBOARD_VERSION;
                wb->magic = WHITEBOARD_MAGIC;

                if (initial) *initial = true;

                DBG(printf("New Whiteboard version %d created and initialised at '%s'\n", wb->version, path));
        }
        else if (initial) *initial = false;

        bool bailout = wb->version != GU_SIMPLE_WHITEBOARD_VERSION;
        if (bailout) fprintf(stderr, "*** Unexpected Whiteboard version %d (expected %d for '%s')\n", wb->version, GU_SIMPLE_WHITEBOARD_VERSION, path);

        if (bailout)
        {
                gsw_free(wb, fd);
                return NULL;
        }
        return wb;
}


void gsw_free(gu_simple_whiteboard *wb, int fd)
{
        if (munmap(wb, sizeof(*wb)) == -1)
                fprintf(stderr, "Cannot unmap whiteboard at %p with fd %d: %s\n", wb, fd, strerror(errno));
        if (fd >= 0) if (close(fd) == -1)
                fprintf(stderr, "Cannot close whiteboard at %p with fd %d: %s\n", wb, fd, strerror(errno));
}


int gsw_procure(gsw_sema_t sem, enum gsw_semaphores s)
{
#ifdef GSW_IOS_DEVICE
        while (dispatch_semaphore_wait(sem[s], DISPATCH_TIME_FOREVER))
        {
                if (errno != EAGAIN)
                        return -1;
        }
        return 0;
#else
        struct sembuf op = { s, -1, 0 };
        int rv;
        while ((rv = semop(sem, &op, 1)) == -1)
               if (errno != EAGAIN)
                       break;
        return rv;
#endif
}


int gsw_vacate(gsw_sema_t sem, enum gsw_semaphores s)
{
#ifdef GSW_IOS_DEVICE
        dispatch_semaphore_signal(sem[s]);
        return 0;
#else
        struct sembuf op = { s, 1, 0 };
        int rv;
        while ((rv = semop(sem, &op, 1)) == -1)
                if (errno != EAGAIN)
                        break;
        return rv;
#endif
}


static u_int32_t hash_of(const char *s)
{
        u_int32_t hash = *s;
        while (*s++)
        {
                u_int32_t stir = hash & 0xf8000000U;
                hash &= 0x07ffffffU;
                hash <<= 5;
                hash ^= stir >> 27;
                hash ^= *s;
        }
        return hash;
}


static u_int32_t alt_hash(const char *s)
{
        u_int32_t hash = *s;
        while (*s++)
        {
                hash &= 0x0fffffffU;
                hash <<= 4;
                hash += *s;
                u_int32_t stir = hash & 0xf0000000U;
                if (stir != 0)
                {
                        hash ^= stir >> 24;
                        hash ^= stir;
                }
        }
        hash |= 1;              // needs to be an odd number

        return hash;
}


int gsw_register_message_type(gu_simple_whiteboard_descriptor *wbd, const char *name)
{
        gsw_procure(wbd->sem, GSW_SEM_MSGTYPE);

        //bool exists = false;
        gu_simple_whiteboard *wb = wbd->wb;
        unsigned offs = hash_of(name) % GSW_TOTAL_MESSAGE_TYPES;
        gu_simple_message *type = &wb->hashes[offs];

        while (wb->num_types < GSW_TOTAL_MESSAGE_TYPES)
        {
                type = &wb->hashes[offs];
                if (!*type->hash.string)
                {
                        gu_strlcpy(type->hash.string, name, sizeof(type->hash.string));
                        DBG(printf(" - registering wb message type #%d for '%s' at %d\n", wb->num_types, type->hash.string, offs));
                        type->hash.value = wb->num_types++;
                        wb->typenames[type->hash.value] = *type;
                        break;
                }
                if (strcmp(type->hash.string, name) == 0)
                {
                        //exists = true;
                        break;
                }
                /* collision, add to the offset */
                DBG(printf("Hash collision at offset %u: %u == %u %% %d for:\n'%s' <> '%s'",
                           offs, hash_of(name), hash_of(type->hash.string), GSW_TOTAL_MESSAGE_TYPES,
                           name, type->hash.string));
                offs += alt_hash(name);
                offs %= GSW_TOTAL_MESSAGE_TYPES;
        }

        gsw_vacate(wbd->sem, GSW_SEM_MSGTYPE);

        if (wb->num_types < GSW_TOTAL_MESSAGE_TYPES)
                return type->hash.value;

        fprintf(stderr, "Cannot register whiteboard message type '%s': hash table capacity %d reached!\n", name, wb->num_types);

        return -1;
}


int gsw_offset_for_message_type(gu_simple_whiteboard_descriptor *wbd, const char *name)
{
        gu_simple_whiteboard *wb = wbd->wb;
        unsigned offs = hash_of(name) % GSW_TOTAL_MESSAGE_TYPES;
        gu_simple_message *type; // = &wb->hashes[offs];
        for (int i = 0; i < GSW_TOTAL_MESSAGE_TYPES; i++)
        {
                type = &wb->hashes[offs];
                if (!*type->hash.string)                        // new message type?
                        return gsw_register_message_type(wbd, name);
                if (strcmp(type->hash.string, name) == 0)
                        return type->hash.value;
                /* hash collision, add to the offset */
                offs += alt_hash(name);
                offs %= GSW_TOTAL_MESSAGE_TYPES;
        }

        fprintf(stderr, "Cannot get offset for message type '%s': hash table full (%d entries)\n", name, wb->num_types);

        return -1;
}

gu_simple_message *gsw_current_message(gu_simple_whiteboard *wb, int i)
{
        u_int8_t j = wb->indexes[i];
        if (j >= GU_SIMPLE_WHITEBOARD_GENERATIONS) j = 0;
        return &wb->messages[i][j];
}


gu_simple_message *gsw_next_message(gu_simple_whiteboard *wb, int i)
{
        u_int8_t j = wb->indexes[i];
        if (++j >= GU_SIMPLE_WHITEBOARD_GENERATIONS) j = 0;
        return &wb->messages[i][j];
}


void gsw_increment(gu_simple_whiteboard *wb, int i)
{
        u_int8_t j = wb->indexes[i];
        if (++j >= GU_SIMPLE_WHITEBOARD_GENERATIONS) j = 0;
        wb->indexes[i] = j;
}

#pragma mark - subscription and callbacks

void gsw_add_process(gu_simple_whiteboard_descriptor *wbd, const pid_t proc)
{
        gsw_procure(wbd->sem, GSW_SEM_PROC);
        gu_simple_whiteboard *wb = wbd->wb;
        u_int16_t i;
        for (i = 0; i < wb->subscribed; i++)
                if (!wb->processes[i] || proc == wb->processes[i])
                        break;
        if (i < GSW_TOTAL_PROCESSES)
        {
                wb->processes[i++] = proc;
                if (i > wb->subscribed)
                        wb->subscribed = i;
        }
        else fprintf(stderr, "Warning: process table full (%d): cannot subscribe %d\n", i, proc);
        gsw_vacate(wbd->sem, GSW_SEM_PROC);
}


void gsw_remove_process(gu_simple_whiteboard_descriptor *wbd, const pid_t proc)
{
        gsw_procure(wbd->sem, GSW_SEM_PROC);
        gu_simple_whiteboard *wb = wbd->wb;
        u_int16_t i;
        for (i = 0; i < wb->subscribed; i++)
                if (proc == wb->processes[i])
                        break;
        if (i < GSW_TOTAL_PROCESSES)
        {
                wb->processes[i] = 0;
                if (i == wb->subscribed-1)
                         wb->subscribed = i;
        }
        else fprintf(stderr, "Warning: cannot remove %d -- process not found!\n", proc);
        gsw_vacate(wbd->sem, GSW_SEM_PROC);
}

void gsw_signal_subscribers(gu_simple_whiteboard *wb)
{
        wb->eventcount++;
#ifdef USE_WHITEBOARD_SIGNAL
        for (int i = 0; i < wb->subscribed; i++)
        {
                pid_t proc = wb->processes[i];
                if (proc) kill(proc, WHITEBOARD_SIGNAL);
        }
#endif
}

static void subscription_callback(void *param)
{
        gu_simple_whiteboard_descriptor *wbd = param;
        if (wbd->callback) wbd->callback(wbd);
}

typedef void (*gsw_sig_t)(int sig);
static gsw_sig_t old_handler = SIG_DFL;

static void monitor_subscriptions(void *param)
{
        gu_simple_whiteboard_descriptor *wbd = param;
        gu_simple_whiteboard *wb = wbd->wb;
        u_int16_t counter = wb->eventcount;
        while (!wbd->exit_monitor)
        {
                if (counter != wb->eventcount)
                {
                        counter = wb->eventcount;
                        if (wbd && wbd->callback_queue)
                                dispatch_async_f(wbd->callback_queue, wbd, subscription_callback);
                }
                else usleep(WHITEBOARD_POLL_PERIOD);
        }
        wbd->got_monitor = false;
}

/* signal handler */
static void sig_handler(int signum)
{
        /* do nothing */
}

void gsw_add_wbd_signal_handler(gu_simple_whiteboard_descriptor *wbd)
{
        gsw_procure(wbd->sem, GSW_SEM_PROC);
        if (old_handler == SIG_DFL)
                old_handler = signal(WHITEBOARD_SIGNAL, sig_handler);
        if (!wbd->got_monitor)
        {
                wbd->got_monitor = true;
                dispatch_async_f(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), wbd, monitor_subscriptions);
        }
        gsw_vacate(wbd->sem, GSW_SEM_PROC);
}


void gsw_remove_wbd_signal_handler(gu_simple_whiteboard_descriptor *wbd)
{
        while (wbd->got_monitor)
        {
                wbd->exit_monitor = true;
                usleep(2*WHITEBOARD_POLL_PERIOD);
        }
}
