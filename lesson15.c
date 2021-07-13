/* lesson 15
  loading external file

yap 2007.1.23 release under GPL 3.0

  YOU WILL LEARN
   how to load source code from eternal file

*/

#include "compiler.h"

int example15(KsanaVm *vm)
{
  Eval(vm,"include lesson15.f");
}
int lesson15(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"include") ==0) {
		addword13(vm);
		addwinapiword(vm);
		example15(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}