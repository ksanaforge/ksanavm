#include "vm.h"



/* lesson 2:  working with the Data Stack
  Data Stack is a storage for calucation
  it is a First-In-Last-Out data structure.
  
  yap 2007.12.17 release under GPL 3.0

YOU WILL LEARN:
  1)the Data Stack and the Stack Pointer
  2)basic stack operation : Push, Pop  
  3)two operation : add and multiply
  4)stack effect diagram


in the console, type the following:
1 
2
3
4 
+
+
+

the final result is 10
*/

void lesson2(KsanaVm *vm)
{	
	int v;
	
	while ( KVMNextToken(vm) ) {
		if (strcmp(vm->token,"+")==0) {
			KVMAdd(vm);          // perform addition
		} else if (strcmp(vm->token,"*")==0) {
			KVMMultiply(vm);    // perform multiplication
		} else if (strcmp(vm->token,"bye")==0) {
			vm->terminate =1;     // terminate the VM
		} else {                      // unknown command 
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
}		