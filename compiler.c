/*
Ksana Minimal Virtual Machine
yap 2007.12.21
*/

#include "compiler.h"



/* --------------------------Lesson 4 ------------------------*/
void DictCompile(KsanaVm *vm, int i)
{
	//write an integer to the dictionary
	*(int*)(vm->dictionary + vm->here) = i;
	//advance the here pointer
	vm->here+=CELLSIZE;
}

// ( n -- )
void KVMComma(KsanaVm *vm)
{
	DictCompile(vm, KVMPop(vm) );
}

// (  -- here )
void KVMHere(KsanaVm *vm)
{
	KVMPush(vm,vm->here);
}






// lesson 7, literal

void KVMdoLiteral(KsanaVm *vm)   // the runtime code for pushing a literal to the stack
{
	int lit=*(int*)(vm->ip);                 //fetch the literal from the next xt to be executed
	KVMPush(vm,lit);
	vm->ip+=CELLSIZE;
}


// lesson 8, the colon compiler
// ( -name- )
void KVMColon(KsanaVm *vm)    // begin a colon compiler
{
	KVMNextToken(vm);
	strncpy(vm->newword.name,vm->token,sizeof(vm->newword));
	vm->newword.xt = vm->dictionary + vm->here;
	vm->compiling  = 1;
	DictCompile(vm, KVMdoColon); //2010/4/30 sam request
}
// end compile of  a construct a high level
void KVMSemicolon(KsanaVm *vm)    // begin a colon compiler
{
	vm->compiling  = 0;
	DictCompile(vm, KVMRet);  // must add this for high level word
	KVMAddWord(vm,vm->newword.name,vm->newword.xt);
}

//( -- )  set the newly added word to immediate
void KVMSetImmediate(KsanaVm *vm)
{
	if (!vm->nword) return;
	vm->vectors[vm->nword-1].immediate =1;
}
//( -- )  set the newly added word to compileonly
void KVMSetCompileOnly(KsanaVm *vm)
{
	if (!vm->nword) return;
	vm->vectors[vm->nword-1].compileonly =1;
}

void KsanaVmAddDictWord(KsanaVm *vm)
{
	KVMAddWord(vm,"here",KVMHere);	    // write to dictionary from *here*
	KVMAddWord(vm,",",KVMComma);	    // write a integer to dictionary
}

void KsanaVmAddCompilerWord(KsanaVm *vm)
{
	KVMAddWord(vm,":",KVMColon);
	KVMAddWord(vm,";",KVMSemicolon); KVMSetImmediate(vm);  KVMSetCompileOnly(vm);
	KVMAddWord(vm,"immediate",KVMSetImmediate);

}
