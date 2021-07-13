/* lesson 1 
  First lesson, processing the tokens.

yap 2007.12.17 release under GPL 3.0

*/

#include "vm.h"


/* process all token in TIB and print it out */
/* tell the main loop to quit by returning 1 if token "bye" is  met */
int lesson1(KsanaVm *vm)
{	
	// fetch all token , and print it out
	while ( KVMNextToken(vm) ) {
		puts(vm->token);
		if (strcmp(vm->token,"bye")==0) vm->terminate=1;
	}
	return 0;
}		