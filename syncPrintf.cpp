#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include <stdlib.h>
#include "Global.h"


int syncPrintf(const char *format, ...)
{
	int res;
#ifndef BCC_BLOCK_IGNORE
	va_list args;
	Global::lock();
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	Global::unlock();
		return res;
#endif
}
