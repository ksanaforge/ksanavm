/* lesson 14
  Windows API

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
  windows API

*/

#include "compiler.h"

int example14(KsanaVm *vm)
{
	Eval(vm, "loadlibrary user32.dll");  
	Eval(vm, "user32.dll @ 4 winapi MessageBoxA");
	Eval(vm,": test 0 s\" hello, world!\" drop s\" WinApi Test\" drop 0 MessageBoxA drop ;");
}
int lesson14(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"winapi") ==0) {
		addword13(vm);
		addwinapiword(vm);
		example14(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}