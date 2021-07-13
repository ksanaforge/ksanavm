#include "vm.h"

// ( -- str len )
void KVMdoStrQ(KsanaVm *vm)
{
   int len=*(int*)vm->ip;
   int align;
   KVMPush(vm,vm->ip+CELLSIZE);
   KVMPush(vm,len);
   align= (vm->here+len ) % 4;
   if (align) len+=4-align;

   vm->ip+=CELLSIZE+len;  //skip the str len and str body
}

//string compiler
void  KVMStrQ(KsanaVm *vm)
{
	char *ending;
	char *starting= vm->tib+vm->ntib+1 ;
	int n,align;

	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}

	ending=strchr(starting,'"');
	if (!ending) ending=starting+strlen(starting);

	n=ending-starting;
	vm->ntib += n+2;

	DictCompile(vm, KVMdoStrQ); // runtime code
    DictCompile(vm, n+1 ) ;         // length of the string

	strncpy(vm->dictionary+vm->here  , starting, n );
	*(char*)(vm->dictionary+vm->here +n)='\0';//ending null byte
	n++;

	align=((vm->here+n) % 4);
	if (align)	n += 4-align;  //alignment to 4

	vm->here += n;
}

void KVMType(KsanaVm *vm)
{
	int sz=KVMPop(vm);
	char *s=KVMPop(vm);
	(vm->textout)(vm,s);
}

void KVMBracketComment(KsanaVm *vm)
{
	char *starting= vm->tib+vm->ntib+1 ;
	char *ending;

	ending=strchr(starting,')');
	if (!ending) ending=starting+strlen(starting);

	vm->ntib += ending-starting+2;
}

void KVMComment(KsanaVm *vm)
{
	char *starting= vm->tib+vm->ntib+1 ;
	vm->ntib += strlen(starting);
}

void KVMDotBracket(KsanaVm *vm)
{
	char *ending,*starting= vm->tib+vm->ntib+1 ;
	char temp;
	int n;

	ending=strchr(starting,')');
	if (!ending) ending=starting+strlen(starting);

	n=ending-starting;
	vm->ntib += n+2;
	temp=*(starting+n);
	*(starting+n)=0;
	(vm->textout)(vm,starting);
	*(starting+n)=temp;
}
void KVMDotQuote(KsanaVm *vm)
{
    KVMStrQ(vm);
    DictCompile(vm, KVMType);
}

void KVMZCount(KsanaVm *vm)
{
    char * tos=(char*)KVMTOS(vm);
    if (!tos) KVMPush(vm,0); else
    KVMPush(vm,strlen(tos));
}
void KsanaVmAddStringWord(KsanaVm *vm)
{
	KVMAddWord(vm, "s\"", KVMStrQ); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	KVMAddWord(vm,"type",KVMType);

	//lesson 15
	KVMAddWord(vm, "(", KVMBracketComment); KVMSetImmediate(vm);
	KVMAddWord(vm, "\\", KVMComment); KVMSetImmediate(vm);
	KVMAddWord(vm,".(",KVMDotBracket);

    KVMAddWord(vm,".\"",KVMDotQuote); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	//ksp
	KVMAddWord(vm,"zcount",KVMZCount);
}
