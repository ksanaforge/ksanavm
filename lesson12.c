/* lesson 12
  variables

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
  variable
 
  variable var        \ create a new variable
  var                    \ get the address of v
  var @                \ fetch the value
  new_value var !  \ set v to new_value

*/

#include "compiler.h"


int lesson12(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"variable") ==0) {
		addword10(vm);
		addioword(vm);
		addvarword(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}