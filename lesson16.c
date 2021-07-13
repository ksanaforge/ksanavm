/* lesson 16
 get Factorial by recursion

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
  recursion
*/

#include "compiler.h"

int example16(KsanaVm *vm)
{
	Eval(vm,"include factorial.f");
}

int lesson16(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"recurse") ==0) {
		addword13(vm);
		addwinapiword(vm);	
		example16(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}