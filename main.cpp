
#include "Global.h"

extern int userMain(int argc, char** argv);
int syncPrintf(const char *format, ...);

int main(int argc, char** argv){
#ifndef BCC_BLOCK_IGNORE
	Global::inicInterrupt();
	userMain(argc,argv);
	Global::restoreInterrupt();

#endif

	return 0;
}
