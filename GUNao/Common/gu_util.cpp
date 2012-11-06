/*
 *     $Id: 8ab2d8985878326521e86ca9a91e0b5481db395e $
 *
 *  gu_util.cpp
 *  gucdlmodule
 *
 *  Created by Rene Hexel on 24/04/10.
 *  Copyright 2010-2011 Rene Hexel. All rights reserved.
 *
 */
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <unistd.h>
#include <libgen.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "gu_util.h"

extern "C"
{
        bool file_exists(const char *fileName)
        {
                struct stat buf;
                return stat(fileName, &buf) >= 0;
        }

	char *new_string_from_file(const char *fileName)
	{
		char *content;
		int file = open(fileName, O_RDONLY);
		if (file < 0) return NULL;

		size_t len = lseek(file, 0, SEEK_END);
		if ((content = (char *) malloc(len+1)))
		{
			lseek(file, 0, SEEK_SET);
			if (read(file, content, len) == len)
				content[len] = '\0';
			else
			{
				free(content);
				content = NULL;
			}
		}
		close(file);

		return content;
	}


        int int_from_file(const char *fileName)
        {
                char *s = new_string_from_file(fileName);

                if (!s) return -1;

                int i = atoi(s);

                free(s);

                return i;
        }

        
        double double_from_file(const char *fileName)
        {
                char *s = new_string_from_file(fileName);
                
                if (!s) return -1;
                
                double d = atof(s);
                
                free(s);
                
                return d;
        }

        char *gu_strdup(const char *s)
        {
                int n = 1;

                if (s) n = int(strlen(s))+1;

                char *dest = static_cast<char *>(calloc(1, n));
                
                if (s && dest) strcpy(dest, s);
                
                return dest;
        }
        

        char *concatenate_path(const char *head, const char *tail)
        {
                return gu_strdup(string_by_concatenating_path_components(head, tail).c_str());
        }

        long long get_utime(void)
        {
                struct timeval tv;
                if (gettimeofday(&tv, NULL) == -1) return -1LL;

                long long t = (long long) tv.tv_usec +
                                (long long) tv.tv_sec * 1000000LL;
                return t;
        }

        void protected_usleep(long long us)
        {
                long long deadline = get_utime() + us;
                while (us > 0)
                {
                    usleep(unsigned(us));
                    us = deadline - get_utime();
                }
        }

        const char *gu_strtrim(const char *s)
        {
                std::string str(s);
                return gu_strdup(gu_trim(str).c_str());
        }

        static FILE *warn_file;

        int mipal_err_file(const char *filename)
        {
                if (warn_file) fclose(warn_file);

                if (strchr(filename, '/')) do
                {
                        /*
                         * copy filename because some implementations of
                         * dirname() may overwrite the string contents
                         */
                        char *f_copy = gu_strdup(filename);

                        if (!f_copy) break;

                        char *dir = dirname(f_copy);

                        mkdir(dir, 01777);

                        free(f_copy);
                } while (0);

                warn_file = fopen(filename, "a");

                return warn_file ? 0 : -1;
        }

        void mipal_warn(const char *fmt, ...)
        {
                va_list ap;
                FILE *file = warn_file ? warn_file : stderr;
                char buf[256];

                time_t t = time(NULL);
                const struct tm *btm = localtime(&t);

                va_start(ap, fmt);
                strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", btm);
                fprintf(file, "%s: %s - ", gu_getprogname(), buf);
                vfprintf(file, fmt, ap);
                fputc('\n', file);
                fflush(file);
                va_end(ap);
        }

#ifndef BSD
        static char *prog_name;
#endif
        const char *gu_getprogname()
        {
#ifdef BSD
                return getprogname();
#else
//                if (!prog_name)
//                        prog_name = new_string_from_file("/proc/self/cmdline");

                if (!prog_name)
                {
                        const int len = 30;
                        prog_name = (char *) calloc(len, 1);
                        snprintf(prog_name, len, "pid %d", getpid());
                }
                return basename(prog_name);
#endif
        }
    
        int getplayernumber()
        {
            char path[30] = "/home/nao/data/player";
            
            int fd = open(path, O_RDONLY);
            if (fd < 0)
            {
                return -1;
            }
            char num[10];
            ssize_t t = read(fd, &num, 1);
            if (t <= 0) return 0;
            return atoi(&num[0]);
        }


#if !defined(BSD) || (BSD < 199506)
        size_t gu_strlcpy(char *dst, const char *src, size_t size)
        {
                strncpy(dst, src, size--);
                dst[size] = 0;
		return strlen(dst);
        }

        size_t gu_strlcat(char *dst, const char *src, size_t size)
        {
                strncat(dst, src, size--);
                dst[size] = 0;
		return strlen(dst);
        }
#endif
}

using namespace std;

string string_from_file(const char *fileName)
{
	char *s = new_string_from_file(fileName);

        if (!s) return "";

	string t(s);
	free(s);

	return t;
}


string string_by_concatenating_path_components(const string &h, const string &t)
{
        const char *head = h.c_str();
        const char *tail = t.c_str();
        std::string path(head);
        size_t len = path.length();
        
        if (len)
        {
                if (head[len-1] == '/')
                {
                        if (tail[0] == '/') tail++;
                }
                else
                {
                        if (tail[0] != '/') path += "/";
                }
        }

        return path + tail;
}


static const string whitespace = " \t\v\r\n";

string &gu_trim(string &s)
{
        string::size_type pos = s.find_last_not_of(whitespace);
        if (pos != string::npos)
        {
                s.erase(pos+1);
                pos = s.find_first_not_of(whitespace);
                if (pos != string::npos)
                        s.erase(0, pos);
        }
        else    s.erase(s.begin(), s.end());

        return s;
}


std::string gu_ltos(long val)
{
        char buf[80];
        snprintf(buf, sizeof(buf), "%ld", val);

        return buf;
}

