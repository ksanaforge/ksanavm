/* lesson 5 
  call and return

  YOU WILL LEARN:
  1) return stack
  2) high level word , list of addresses
  3) calling a high level word

yap 2007.12.21 release under GPL 3.0

*/

#include "vm.h"

// dup * 
// stack effect  ( n  --  n^2  )
int do_square(KsanaVm *vm)
{
	int addr=vm->dictionary+vm->here;  // address of this high level word
	DictCompile(vm, (int)KVMDup);
	DictCompile(vm, (int)KVMMultiply);
	DictCompile(vm, (int)KVMRet);  // return to caller
	return addr;
}

/* note that this lesson is not interative , use debugger to step around*/
int lesson5(KsanaVm *vm)
{	
	int address;

	//push some data on the stack
	KVMPush(vm, 3);

	//now create a high level word  to compute the square
	address= do_square(vm);
   //check the memory window, address of functions is compiled to the dictionary

	//now execute the word
	KVMCall(vm,address);

	//set a break point, and check the vm->datastack , should be 9

	//reuse lesson3 loop
	lesson3(vm);
	return 0;
}		