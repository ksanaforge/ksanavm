/* lesson 8 
  the colon defination

yap 2007.12.21 release under GPL 3.0

  YOU WILL LEARN
  1) the dual-state compilation
  2) construct a high level word in the console
*/

#include "compiler.h"


int lesson8(KsanaVm *vm)
{	
	KsanaWord *w;
	int v;
	
	//bind the address with a name, so that it can be type in the console

	if (KVMFindWord(vm,"+")==0) addbasicword(vm);   // to allow "bye"
	if (KVMFindWord(vm,",")==0) adddictword(vm);   
	if (KVMFindWord(vm,":")==0) addcompilerword(vm);  

//the main loop need some changes...
	while ( KVMNextToken(vm) ) {
		w = KVMGetWord(vm,vm->token);
		if (w) {
			if (vm->compiling && !w->immediate) { // immediate word must be run immediately regardless of state
				DictCompile(vm, w->xt);         //!!  compile the xt to dictionary , instead of running it
			} else {
				KVMExecute(vm, w->xt);       // not in compiling state (interpreting state)   , simply execute 
			}
		} else {                                // the rest are same as lesson 3
			v=atoi(vm->token); // see if it is a numeric value
			if ((0==v) && (0!=strcmp(vm->token,"0"))) { 
				printf("unknown command %s\n",vm->token); 
			} else {
				// got a valid numeric value, push the value into the stack
				if (vm->compiling) {                        // compiling mode
					DictCompile(vm, (int)KVMdoLiteral); 	//!! compile a literal
					DictCompile(vm, v);                    // at runtime, the v will be push to stack
				} else {
					KVMPush(vm,v);                        // interpreter mode, simply push on stack
				}
			}
		}
	}

	KVMDumpStack(vm);   //dump the status of the stack to console
	return 0;
}		