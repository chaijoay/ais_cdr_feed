#include "strlogutl.h"
//
// Global Variable
//
char    glb_Log_File[SIZE_FNAME+1];
char    glb_Logfile_Dir[SIZE_FNAME+1];
char    glb_StartProcessTime[SIZE_DATE_TIME_FULL];
char    glb_LastLogDate[SIZE_DATE_ONLY];
char    glb_LogPrefix[SIZE_FNAME+1];
FILE    *glb_Logfp;
int     gn_LogLevel = 0;
char	aSevStr[LOG_DBG+1][5] = {"SYS", "ERR", "WRN", "INF", "DBG"};

//
// Name         : startLogging ()
//
// Description  : Initial Log file.
//
// Parameters   : None.
//
// Return Value : None.
//
int startLogging(const char* log_dir, const char* fname_prefix, int log_level)
{
    gn_LogLevel = log_level;
    if ( glb_Logfp ) {
        fclose(glb_Logfp);
    }
    glb_Logfp = NULL;

    memset(glb_Log_File, 0x00, sizeof(glb_Log_File));
    memset(glb_Logfile_Dir, 0x00, sizeof(glb_Logfile_Dir));
    memset(glb_StartProcessTime, 0x00, sizeof(glb_StartProcessTime));
    memset(glb_LastLogDate, 0x00, sizeof(glb_LastLogDate));
    memset(glb_LogPrefix, 0x00, sizeof(glb_LogPrefix));

    strcpy(glb_Logfile_Dir, log_dir);
    strcpy(glb_LogPrefix, fname_prefix);
    strcpy(glb_StartProcessTime, getSysDTM(DTM_DATE_TIME_FULL));
    strcpy(glb_LastLogDate, getSysDTM(DTM_DATE_ONLY));
    return openLogFile();
}

//
// Name         : manageLogFile ()
//
// Description  : Check Log Date with current date for daily log file.
//
// Parameters   : None.
//
// Return Value : SUCCESS      - on Successful File Open.
//                FAILED      - on any Error.
//
int manageLogFile()
{

    if ( !*glb_LastLogDate ) {  // Is Null mean just start process
        strcpy(glb_LastLogDate, getSysDTM(DTM_DATE_ONLY));
        if ( openLogFile() ) {  // Open Log File FAILED
            return FAILED;
        }
    }
    else if ( strncmp(glb_LastLogDate, getSysDTM(DTM_DATE_ONLY), 8) ) { // Last Log File date is different from current date
        strcpy(glb_LastLogDate, getSysDTM(DTM_DATE_ONLY));
        writeLog(LOG_INF, "------------------ End of daily log ------------------");
        if ( glb_Logfp ) {
            fclose(glb_Logfp);
        }
        if ( openLogFile() ) {  // Open Log File FAILED
            return FAILED;
        }
        writeLog(LOG_INF, "--- Cont daily log: started on %s ---", glb_StartProcessTime);
    }       // Else use old log file
    return SUCCESS;

}

//
// Name         : openLogFile ()
//
// Description  : Prefixes the Log Directory path to the FileName.
//                Opens Log File.
//
// Parameters   : None.
//
// Return Value : SUCCESS - on Successful File Open.
//                FAILED  - on any Error.
//
int openLogFile()
{
    // Prepare Log File Name
    if ( access(glb_Logfile_Dir, F_OK) != 0 ) {
        fprintf(stderr, "cannot access log path %s, used ./\n\n", glb_Logfile_Dir);
        strcpy(glb_Logfile_Dir, "./");
    }
    sprintf(glb_Log_File, "%s/%s_%s.log", glb_Logfile_Dir, glb_LogPrefix, getSysDTM(DTM_DATE_ONLY));

    // Open Log file
    if ( (glb_Logfp = fopen(glb_Log_File, "a+")) == 0 ) {   // cannot open log file
        fprintf(stderr, "cannot open log file %s\n\n", glb_Log_File);
        return FAILED;
    }
    return SUCCESS;

}

void stopLogging()
{
    if ( glb_Logfp ) {
        fclose(glb_Logfp);
    }
}

//
// Name         : writeLog ()
//
// Description  : Write error infomation to the log file.
//
// Parameters   : char *iSev - INPUT - Error message type.
//                char *LogMsg - INPUT - Error message to display.
//
// Return Value : void
//
void writeLog(int iSev, const char *LogMsg, ...)
{
    va_list vl;

    va_start(vl, LogMsg);     // Initialize variable arguments.
    if ( iSev <= gn_LogLevel ) {
        if ( glb_Logfp ) {
            fprintf(glb_Logfp, "%s [%s] ", getSysDTM(DTM_DATE_TIME_FULL), aSevStr[iSev]);
            vfprintf(glb_Logfp, LogMsg, vl);
            fprintf(glb_Logfp, "\n");
            fflush(glb_Logfp);
        }
        else {
            fprintf(stderr, "%s [%s] ", getSysDTM(DTM_DATE_TIME_FULL), aSevStr[iSev]);
            vfprintf(stderr, LogMsg, vl);
            fprintf(stderr, "\n");
            fflush(stderr);
        }
    }
    va_end(vl);

}

void getSysDate(char *sysdate, char *dateformat)
{
    struct tm *sys_time;
    time_t t;
    char nowtm[30+1];

    memset(nowtm, 0x00, sizeof(nowtm));
    t = time('\0');
    sys_time = localtime(&t);
    strftime(nowtm, 30, dateformat, sys_time);  /* format : HH24MI */
    strcpy(sysdate, nowtm);

}

char *getSysDTM(int n_format)
{
    time_t sys_sec;
    struct tm * time_info;
    char date_time_format[80];
    static char szDateStr[SIZE_DATE_TIME_FULL];

    time(&sys_sec);
    time_info = localtime(&sys_sec);

    memset(date_time_format, 0x00, sizeof(date_time_format));
    switch ( n_format ) {
        case DTM_DATE_ONLY:
            strcpy(date_time_format, "%Y%m%d");
            break;
        case DTM_TIME_ONLY:
            strcpy(date_time_format, "%H%M%S");
            break;
        case DTM_DATE_TIME:
            strcpy(date_time_format, "%Y%m%d%H%M%S");
            break;
        case DTM_DATE_FORM:
            strcpy(date_time_format, "%Y/%m/%d");
            break;
        case DTM_TIME_FORM:
            strcpy(date_time_format, "%H:%M:%S");
            break;
        case DTM_DATE_TIME_FULL:
            strcpy(date_time_format, "%Y/%m/%d %H:%M:%S");
            break;
        default:
            strcpy(date_time_format, "%Y/%m/%d %H:%M:%S");
            break;
    }
    strftime(szDateStr, sizeof(szDateStr), date_time_format, time_info);
    return szDateStr;
}

char *getFileTimeM(char *inpfile, char *dateformat)
{
    struct stat stat_buf;
    struct tm * time_info;
    static char szDateStr[SIZE_DATE_TIME_FULL];

    memset(&stat_buf, 0x00, sizeof(stat_buf));

    if ( !lstat(inpfile, &stat_buf) ) {
        time_info = localtime(&(stat_buf.st_mtime));
        strftime(szDateStr, sizeof(szDateStr), dateformat, time_info);
    }
    else {
        getSysDate(szDateStr, dateformat);
    }
    return szDateStr;
}

void trimStr(char *buff)
{

    short   i = strlen(buff);
    /* while (i-- && *(buff+i) == ' '); */
    while (i-- && *(buff + i) < 33)
        ;  /* ascii value 0 - 32 */
    *(buff + i + 1) = '\0';

}

void strToLower(char *dest, char *src)
{
    int i=0;
    while ( *(src+i) != 0 ) {
        *(dest+i) = tolower(*(src+i));
        i++;
    }
    *(dest+i) = 0;
}

void strToUpper(char *dest, char *src)
{
    int i=0;
    while ( *(src+i) != 0 ) {
        *(dest+i) = toupper(*(src+i));
        i++;
    }
    *(dest+i) = 0;
}

char *strrstr(char *x, char *y) {
	int m = strlen(x);
	int n = strlen(y);
	char *X = malloc(m+1);
	char *Y = malloc(n+1);
	int i;
	for (i=0; i<m; i++) X[m-1-i] = x[i]; X[m] = 0;
	for (i=0; i<n; i++) Y[n-1-i] = y[i]; Y[n] = 0;
	char *Z = strstr(X,Y);
	if (Z) {
		int ro = Z-X;
		int lo = ro+n-1;
		int ol = m-1-lo;
		Z = x+ol;
	}
	free(X); free(Y);
	return Z;
}

#ifndef _BSD_SOURCE
/*
 * Get next token from string *stringp, where tokens are possibly-empty
 * strings separated by characters from delim.
 *
 * Writes NULs into the string at *stringp to end tokens.
 * delim need not remain constant from call to call.
 * On return, *stringp points past the last NUL written (if there might
 * be further tokens), or is NULL (if there are definitely no more tokens).
 *
 * If *stringp is NULL, strsep returns NULL.
 */
char *strsep(char **stringp, const char *delim)
{
    char *s;
    const char *spanp;
    int c, sc;
    char *tok;

    if ( (s = *stringp) == NULL)
        return (NULL);
    for (tok = s;;) {
        c = *s++;
        spanp = delim;
        do {
            if ( (sc = *spanp++) == c) {
                if ( c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                *stringp = s;
                return (tok);
            }
        } while (sc != 0);
    }
    /* NOTREACHED */
}
#endif
// --------- Example of Using strsep --------
// void dummy_test
// {

    // int idx, col = 1;
    // char *token, *string, *tofree, szSep[2];

    // sprintf(szSep, "%c", sep);
    // tofree = string = strdup(line);
    // while ( (token = strsep(&string, szSep) ) != NULL) {
        // if ( col == pat_col ) {
            // fprintf(*out, "%d|", pat_val);
        // }
        // else {
            // fprintf(*out, "%s|", token);
        // }
        // col++;
    // }
    // free(tofree);
    // fprintf(*out, "\n");

// }