/* lesson 7 
  compiling literals and use it at runtime

yap 2007.12.21 release under GPL 3.0

  YOU WILL LEARN
  1) compiling data on dictionary, and use it on runtime
  2) name the high level word
*/

#include "compiler.h"

int test_literal(KsanaVm *vm)
{
	int addr=vm->dictionary+vm->here;  // address of this high level word
	DictCompile(vm, (int)KVMdoLiteral); 
	DictCompile(vm, 3 );  
	DictCompile(vm, (int)KVMDup );  
	DictCompile(vm, (int)KVMMultiply );  
	DictCompile(vm, (int)KVMRet);  // return to caller
	return addr;
}
// now every thing need at runtime ( functions and data)  can be prepared by DictCompile
// the compiler is almost ready

int lesson7(KsanaVm *vm)
{	
	KVMXT xt;
	int v;
	int address_littest;
	

	if (KVMFindWord(vm,"test")==0){
		//create a new high level word
		address_littest=test_literal(vm);
		//bind the address with a name, so that it can be type in the console
		KVMAddWord(vm,"test",address_littest);
	}

	if (KVMFindWord(vm,"+")==0) addbasicword(vm);   // to allow "bye"

//almost same as lesson3
	while ( KVMNextToken(vm) ) {
		xt = KVMFindWord(vm,vm->token);
		if (xt) {
			KVMExecute(vm, xt);          //!!!  (*xt)(vm) has been replaced by KVMExecute , to allow execution of high level word  
		} else {                                // the rest are same as lesson 3
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