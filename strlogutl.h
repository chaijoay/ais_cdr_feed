/*
**++
**  FACILITY    : PPFDS Log File Utility Functions
**
**  FILE NAME   : logutil.h
**
**  ABSTRACT    : Constant & Header of Log Utility Functions for Prepaid Fruad Development System (PPFDS)
**
**  AUTHOR      : Kawee.W.
**
**  CREATE DATE : 29-Nov-2002
**
**  CURRENT VERSION NO : 0.1
**
**  LAST RELEASE DATE  : 30-Jun-2003
**
**  MODIFICATION HISTORY :
**  0.1     29-Nov-2002 First Version of Log Utility Functions
**
**++
*/

#ifndef __STR_LOG_UTL_H__
#define __STR_LOG_UTL_H__

#ifndef _XOPEN_SOURCE
    #define _XOPEN_SOURCE           700
#endif
#ifndef _XOPEN_SOURCE_EXTENDED
    #define _XOPEN_SOURCE_EXTENDED  1
#endif
#ifndef _BSD_SOURCE
    #define _BSD_SOURCE
#endif
#ifndef _POSIX_SOURCE
    #define _POSIX_C_SOURCE         200112L
#endif

#ifdef  __cplusplus
    extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

//
// Severity Constants used for Error Log File
//
typedef enum {
    LOG_SYS  = 0,
    LOG_ERR,
    LOG_WRN,
    LOG_INF,
    LOG_DBG
} LOG_LEVEL;


#define SIZE_FNAME          256

#ifndef SUCCESS
    #define SUCCESS         0
#endif
#ifndef FAILED
    #define FAILED          -1
#endif

#define SIZE_DATE_ONLY           9
#define SIZE_TIME_ONLY           6
#define SIZE_DATE_TIME           15
#define SIZE_DATE_FORM           11
#define SIZE_TIME_FORM           9
#define SIZE_DATE_TIME_FULL      20

typedef enum {
    DTM_DATE_ONLY = 0,          // YYYYMMDD
    DTM_TIME_ONLY,              // H24MiSS
    DTM_DATE_TIME,              // YYYYMMDDH24MiSS
    DTM_DATE_FORM,              // YYYY/MM/DD
    DTM_TIME_FORM,              // H24:Mi:SS
    DTM_DATE_TIME_FULL          // YYYY/MM/DD H24:Mi:SS
} DTM_FORMAT;

//
// Function prototypes for Logging Purpose
//
int     startLogging(const char* log_dir, const char* fname_prefix, int log_level);
int     manageLogFile();
int     openLogFile();
void    writeLog(int iSev, const char *LogMsg, ...);
void    stopLogging();

//
// Function prototypes for DateTime Purpose
//
void    getSysDate(char *sysdate, char *dateformat);
char    *getSysDTM(int n_format);
char    *getFileTimeM(char *inpfile, char *dateformat);

//
// Function prototypes for String Manipulation
//
void    trimStr(char *buff);
void    strToLower(char *, char *);
void    strToUpper(char *, char *);

char	*strrstr(char *x, char *y);
#ifndef _BSD_SOURCE
/*-
 * Copyright (c) 1990, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
char    *strsep(char **stringp, const char *delim);
#endif

#ifdef  __cplusplus
    }
#endif


#endif  // __STR_LOG_UTL_H__
