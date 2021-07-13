#include "compiler.h"

//lesson 12
void  KVMdoVariable(KsanaVm *vm)
{
	KVMPush(vm,vm->ip);
	KVMRet(vm);
}
// ( -name- )
void  KVMVariable(KsanaVm *vm)
{
	KVMNextToken(vm);
	strncpy(vm->newword.name,vm->token,sizeof(vm->newword));
	vm->newword.xt = vm->dictionary + vm->here;

	DictCompile(vm, KVMdoVariable);  // must add this for high level word
	DictCompile(vm,0);                      //initial value
	KVMAddWord(vm,vm->newword.name,vm->newword.xt);
}

// ( v -- n )
void  KVMFetch(KsanaVm *vm)
{
	int *p, i=0, invectors;
	p=KVMPop(vm);
	invectors= (p>= &(vm->vectors[0])) && (p<= &(vm->vectors[vm->nword]));
	if (invectors || (p>=vm->dictionary && p<=vm->dictionary +vm->here)) {
		i= *p;
		KVMPush (vm, i);
	} else {
		(vm->errtextout)(vm,"invalid fetch address");
	}
}
// ( n v  --  )
void  KVMStore(KsanaVm *vm)
{
	int *p, i;
	p=KVMPop(vm);
	i=KVMPop(vm);
	if (p>=vm->dictionary && p<=vm->dictionary +vm->here) {
		*p=i;
	} else {
		(vm->errtextout)(vm,"invalid store address");
	}
}

// ( v -- n )
void  KVMCFetch(KsanaVm *vm)
{
	char *p, i=0, invectors;
	p=KVMPop(vm);
	invectors= (p>= &(vm->vectors[0])) && (p<= &(vm->vectors[vm->nword]));
	if ((p>=vm->dictionary && p<=vm->dictionary +vm->here) || invectors) {
		i= *p & 0xff;
		KVMPush (vm, i);
	} else {
		(vm->errtextout)(vm,"invalid cfetch address");
	}
}
// ( n v  --  )
void  KVMCStore(KsanaVm *vm)
{
	char *p, i;
	p=KVMPop(vm);
	i=(char)KVMPop(vm);
	if (p>=vm->dictionary && p<=vm->dictionary +vm->here) {
		*p=i;
	} else {
		(vm->errtextout)(vm,"invalid cstore address");
	}
}
// ( address count c -- )
void  KVMFill(KsanaVm *vm)
{
	char c=KVMPop(vm);
	int count=KVMPop(vm);
	char *p=KVMPop(vm);
	int i;

	if ((p>=vm->dictionary && p<=vm->dictionary +vm->here)
	  &&((p+count)>=vm->dictionary && (p+count)<=vm->dictionary +vm->here)){
		  for (i=0;i<count;i++)  {
			  *p++=c;
		  }
	} else {
		printf("invalid address 0x%x\n", p);
	}
}

//lesson 12
void  KVMcreate(KsanaVm *vm)
{
	KVMNextToken(vm);
	strncpy(vm->newword.name,vm->token,sizeof(vm->newword));
	vm->newword.xt = vm->dictionary + vm->here;

	DictCompile(vm, KVMdoVariable);  // must add this for high level word
	KVMAddWord(vm,vm->newword.name,vm->newword.xt);
}
//lesson 17
void  KVMAllot(KsanaVm *vm)
{
	vm->here += KVMPop(vm);
}

void ChangeCreateCodeField(KsanaVm *vm,KVMXT xt)
{
	*(int*)vm->newword.xt = xt;
}
void  KVMDoes(KsanaVm *vm)
{
	//point xt to code address after does>
	ChangeCreateCodeField(vm, vm->ip);
	//stop here, code following does> are not executed.
	KVMRet(vm);
}

void KVMrfrom(KsanaVm *vm)
{
	KVMPush(vm,KVMRPop(vm));
}

void KsanaVmAddVarWord(KsanaVm *vm)
{
	//lesson 12
	KVMAddWord(vm,"variable",KVMVariable);
	KVMAddWord(vm, "@", KVMFetch);
	KVMAddWord(vm, "!", KVMStore);
	KsanaVmEval(vm,": ? @ . ; ");

	//lesson 17
	KVMAddWord(vm, "create", KVMcreate);
	KVMAddWord(vm, "allot", KVMAllot);
	KVMAddWord(vm, "c@", KVMCFetch);
	KVMAddWord(vm, "c!", KVMCStore);
	KVMAddWord(vm, "fill", KVMFill);


	KVMAddWord(vm,"r>",KVMrfrom);
	KVMAddWord(vm, "does>", KVMDoes);
	KsanaVmEval(vm,": value create , does> r> @ ; ");

}
