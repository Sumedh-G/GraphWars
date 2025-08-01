#include "utils.h"
#include "raylib.h"
#include <time.h>

#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_RESET   "\x1b[0m"

void CustomLog(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "[%H:%M:%S] %h %d, %Y", tm_info);

    switch (msgType)
    {
        case LOG_INFO:    printf("[" ANSI_BLUE    "INFO"  ANSI_RESET "] : "); break;
        case LOG_ERROR:   printf("[" ANSI_RED     "ERROR" ANSI_RESET "]: "); break;
        case LOG_WARNING: printf("[" ANSI_YELLOW  "WARN"  ANSI_RESET "] : "); break;
        case LOG_DEBUG:   printf("[" ANSI_MAGENTA "DEBUG" ANSI_RESET "]: "); break;
        default: break;
    }

    int n = vprintf(text, args);

    printf(" %*s ", 135-n, timeStr);
    printf("\n");
}

void WriteLog(int msgType, const char *format_string, ...)
{
    va_list args;
    va_start(args, format_string);
    CustomLog(msgType, format_string, args);
    va_end(args);

    return;
}
