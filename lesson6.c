/* lesson 6 
  the nested call

yap 2007.12.21 release under GPL 3.0

  YOU WILL LEARN
  1) the interaction between ip and return stack
*/

#include "compiler.h"

int do_sum_2_square(KsanaVm *vm, KVMXT square)
{
	int addr=vm->dictionary+vm->here;  // address of this high level word
	DictCompile(vm, (int)square);       // high level , ( n -- n*n )
	DictCompile(vm, (int)KVMSwap);  // take the second item
	DictCompile(vm, (int)square);      // high level
	DictCompile(vm, (int)KVMAdd);    // add two square
	DictCompile(vm, (int)KVMRet);  // return to caller
	return addr;
}


int lesson6(KsanaVm *vm)
{	
	//put two item on stack
	KVMPush(vm, 3);
	KVMPush(vm, 4);

	lesson6_loop(vm);
}		

int lesson6_loop(KsanaVm *vm)
{
	int address,addr_square;
	//compile a highlevel word to compute the square
	addr_square=do_square(vm);

	//compute the sum of two square =    * dup   swap   * dup   +
	address= do_sum_2_square(vm, addr_square);

	KVMCall(vm,address);

	// the result on the stack should be 0x19 or 25 
	//reuse lesson3 loop
	lesson3(vm);
	return 0;
}