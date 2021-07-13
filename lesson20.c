/* lesson 20
  does>

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
  create allot does>
*/

#include "compiler.h"

int example20(KsanaVm *vm)
{
//defining the datastructure and behavior
	KsanaVmEval(vm,": value create , does> r> @ ;");
//creating new instance
    KsanaVmEval(vm,"8 value k");
//execute the instance
    KsanaVmEval(vm,"k .");
}

int lesson20(KsanaVm *vm)
{
	if (KsanaVmFindWord(vm,"does>") ==0) {
        KsanaVmAddBasicWord(vm);
        KsanaVmAddDictWord(vm);
        KsanaVmAddCompilerWord(vm);
        KsanaVmAddStringWord(vm);
        KsanaVmAddFlowWord(vm);
        KsanaVmAddIOWord(vm);
        KsanaVmAddVarWord(vm);
        KsanaVmAddAliasWord(vm);
        KsanaVmAddDebugWord(vm);
        KsanaVmAddWinapiWord(vm);

		example20(vm);
	}

	KsanaVmEval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}
