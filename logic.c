/*
Ksana Minimal Virtual Machine
yap 2010.4.23
*/

#include <stdio.h>
#include "vm.h"

void KVMand(KsanaVm *vm)
{
    int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1&n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}

void KVMxor(KsanaVm *vm)
{
    int n1,n2 ,r ;
	n2=KVMPop(vm);
	n1=KVMPop(vm);
	r= n1^n2;
	KVMPush(vm,  r );

}
void KVMor(KsanaVm *vm)
{
    int n1,n2 ,r ;
	n2=KVMPop(vm);
	n1=KVMPop(vm);
	r= n1|n2;
	KVMPush(vm,  r );
}
void KVMmod(KsanaVm *vm)
{
    int n1,n2 ,r=0;
	n2=KVMPop(vm);
	n1=KVMPop(vm);
	if (n2)  {
	r= n1 % n2  ;
	}
	KVMPush(vm,  r );
}

void KsanaVmAddLogicWord(KsanaVm *vm)
{
	KVMAddWord(vm,"xor",KVMxor);
	KVMAddWord(vm,"and",KVMand);
	KVMAddWord(vm,"or",KVMor);
	KVMAddWord(vm,"mod",KVMmod);
}
