#pragma once
#include <stdio.h>

void CustomLog(int msgType, const char *text, va_list args);
void WriteLog(int msgType, const char *format_string, ...);
