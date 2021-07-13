/* lesson 9
  string gompiler

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
   string compiler
  
*/

#include "compiler.h"
void addword9(KsanaVm *vm)
{
	addbasicword(vm);
	adddictword(vm);   
	addcompilerword(vm);  
	addstringword(vm);
}

void example9(KsanaVm *vm)
{
	Eval(vm,": test s\" hello, world!\" type ; ");
}
int lesson9(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"s\"") ==0) {
		addword9(vm);
		example9(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}