/*
 *     $Id: e46a7a89ecebb045d828435de88cde319e27d25d $
 *
 *  gu_util.h
 *  Utility functions
 *
 *  Created by Rene Hexel on 24/04/10.
 *  Copyright 2010-2011 Rene Hexel. All rights reserved.
 *
 */
#ifndef _GU_UTIL_H_

#ifdef	DEBUG
#ifndef DBG
#define	DBG(x)		x
#endif
#ifndef	DPRINTF
#define	DPRINTF(x)	printf x
#endif
#else
#ifndef DBG
#define	DBG(x)
#endif
#ifndef	DPRINTF
#define	DPRINTF(x)
#endif
#endif

#define protected_msleep(ms)    protected_usleep(1000LL*(ms))
#define protected_sleep(s)     protected_usleep(1000000LL*(s))

#ifdef __cplusplus
#include <string>
#include <cstring>

extern "C"
{
#else // __cplusplus
#include <string.h>
#include <stdbool.h>
#endif // __cplusplus

#include <sys/param.h>

#if defined(BSD) && (BSD >= 199506)
#define gu_strlcpy(d,s,n)       strlcpy((d),(s),(n))
#define gu_strlcat(d,s,n)       strlcat((d),(s),(n))
#else
size_t gu_strlcpy(char *dst, const char *src, size_t size);
size_t gu_strlcat(char *dst, const char *src, size_t size);
#endif

/** Return whether a file exists
 * @param fileName	Name of the file to test
 * @return true if the file exists, false otherwise
 */
bool file_exists(const char *fileName);

/** Load the contents of a given file into a string
 * @param fileName	Name of the file to load
 * @return string with contens of file
 */
char *new_string_from_file(const char *fileName);

/** Load the contents of a given file into an int
 * @param fileName	Name of the file to load
 * @return int with the contents of the file
 */
int int_from_file(const char *fileName);

/** Load the contents of a given file into a double
 * @param fileName	Name of the file to load
 * @return double with the contents of the file
 */
double double_from_file(const char *fileName);

/** Duplicate a string
 * @param str	  original string
 * @return char * duplicated string (needs to be free()d)
 */
char *gu_strdup(const char *str);

/** Create a new string by concatenating two path components
 * @param head	  parent directory
 * @param tail	  child path component
 * @return char * with the concatenated path (needs to be free()d)
 */
char *concatenate_path(const char *head, const char *tail);

/** Get the current time of day in microseconds
 * @return long long    with the current time in us (-1LL in case of error)
 */
long long get_utime(void);

/** Protected usleep() -- guaranteed to sleep for the given time!
 * param us   number of microseconds to sleep
 */
void protected_usleep(long long us);
        
/** Return a trimmed copy of the current space by removing all
 *  leading and trailing whitespace characters
 * @param s	  the string to trim
 * @return new string void of leading
 */
const char *gu_strtrim(const char *s);

/** Set the log file for the current module
 * @param filename      name of the file to open.  If the file contains a
 *                      slash '/', it will create the directory the file
 *                      should go in with mode 01777 if non-existent
 * @return -1 in case of errors, 0 in case of success
 */
int mipal_err_file(const char *filename);

/** Print a warning to the file mipal_err_file() has been set for
 *  (or stderr if none has been set)
 * @param fmt      printf() style format string
 */
void mipal_warn(const char *fmt, ...);

/** get the basename of the current program
 * @return const char *  program name
 */
const char *gu_getprogname();
    
/** get player number
 * @return int player number
 */
int getplayernumber();

#ifdef __cplusplus
} // extern "C"

/** Load the contents of a given file into a string
 * @param fileName	Name of the file to load
 * @return string with contens of file
 */
std::string string_from_file(const char *fileName);


/** Concatenate two path components into a new string
 * @param head	  parent directory
 * @param tail	  child path component
 * @return string with the concatenated path
 */
std::string string_by_concatenating_path_components(const std::string &head, const std::string &tail);

/** Trim whitespace characters from both ends of a string.
 * This operation is in-place, so the original string gets modified!
 * @param s	  the string to trim (in place)
 * @return reference to s
 */
std::string &gu_trim(std::string &s);

/** Convert a long value to a string
 * @param value	Value to convert
 * @return string with contens value
 */
std::string gu_ltos(long val);

#endif // __cplusplus

#endif // _GU_UTIL_H_
