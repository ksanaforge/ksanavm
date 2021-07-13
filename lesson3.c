/* lesson 3 
  The execution vector (function pointer)

yap 2007.12.17 release under GPL 3.0

  by adding new command into the VM, the loop become more complicated and difficult to maintain,
  in this lesson, we create an array to store the name of forth's words and and it execution vector.
  to understand this lesson, you should know the concept of function pointer in C.

YOU WILL LEARN:
  1) the structure of execution vector
  2) more stack operation  dup , drop , swap, over
  3) arithmetic operation - /  
  4) adding new words 

*/

#include "vm.h"





int lesson3(KsanaVm *vm)
{	
	KVMXT xt;
	int v;
	
	if (KVMFindWord(vm,"+")==0) addbasicword(vm);  // adding the words for once.

	// fetch all token , and print it out
	while ( KVMNextToken(vm) ) {
		xt = KVMFindWord(vm,vm->token);
		if (xt) {
			(*xt)(vm) ;   // execute !
		} else {
			v=atoi(vm->token); // see if it is a numeric value
			if ((0==v) && (0!=strcmp(vm->token,"0"))) { 
				printf("unknown command %s\n",vm->token); 
			} else {
				// got a valid numeric value, push the value into the stack
				KVMPush(vm,v);
			}
		}
	}
	KVMDumpStack(vm);   //dump the status of the stack to console
	return 0;
}		