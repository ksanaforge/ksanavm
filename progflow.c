/*
Ksana Minimal Virtual Machine
yap 2007.12.21
*/

#include "progflow.h"


/* --------------------------Lesson 9 ------------------------*/
void branch(KsanaVm *vm)
{
	vm->ip=*(int*)(vm->ip);
}
void doIf(KsanaVm *vm)
{
	if (0==KVMPop(vm)) branch(vm);
	else vm->ip+=CELLSIZE;
}

/*
 FORTH:  xxx if true_clause then yyy

	xxx
	doIf
	[address]           //jump to address if not true
       true_clause
address:
    yyy

FORTH:   xxx if true_clause else false_clause then yyy

    xxx
    doIf
	[addr1]              // jump to addr1 if not true
	   code for "true"

    branch
	[addr2]   -->      // address after "then"
addr1:
	   code for "false"
addr2:
    yyy

*/
void KVMIf(KsanaVm *vm)
{
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}
	DictCompile(vm,doIf);
	KVMPush(vm,vm->dictionary +vm->here); //current dictionary pointer
	DictCompile(vm,0xFFFFFFFF) ; //jump address
}
void KVMThen(KsanaVm *vm)
{
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}
	*(int*)(KVMPop(vm)) = vm->dictionary +vm->here ;
}
void KVMElse(KsanaVm *vm)
{
	int jmp;
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}

	jmp=KVMPop(vm);
	DictCompile(vm,branch);
	KVMPush(vm,vm->dictionary +vm->here);
	DictCompile(vm,0xEEEEEEEE);
	*(int *)(jmp) = vm->dictionary +vm->here;
}


/* --------------------------Lesson 11 ------------------------*/
/*

FORTH:  xxx DO to_do LOOP yyy

xxx
doDo
address:
    to_do
doLoop
[address]
yyy

DO       ( limit index -- )
LOOP
+LOOP   add top of stack to index
I    put the index on data stack
*/

//runtime code of DO
void doDo(KsanaVm *vm)
{
	int index= KVMPop(vm);
	int limit= KVMPop(vm);

	//push limit and index on return stack
	KVMRPush(vm,limit);
	KVMRPush(vm, index);
}

//runtime code of LOOP
void doLoop(KsanaVm *vm)
{
  int index,limit;
  index=KVMRPop(vm)+1;
  limit=KVMRPop(vm);
  if (index>=limit) {
	  vm->ip+=CELLSIZE;
  } else {
	  KVMRPush(vm,limit);
	  KVMRPush(vm,index);
	  branch(vm);                // jump to code after DO
  }
}

//runtime code of +LOOP
//runtime code of +LOOP
void doPlusLoop(KsanaVm *vm)
{
  int index,limit,delta;

  index=KVMRPop(vm);
  delta=KVMPop(vm);
  limit=KVMRPop(vm);
  if ((delta>0&&index>=limit)||delta<0&&index<=limit) {
	  vm->ip+=CELLSIZE;
  } else {
	  index+=delta;
	  KVMRPush(vm,limit);
	  KVMRPush(vm,index);
	  vm->ip =*(int*)(vm->ip);  // loop back
  }
}

void KVMDo(KsanaVm *vm)
{
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}

	DictCompile(vm,doDo);           // runtime of do
	KVMPush(vm,vm->dictionary +vm->here); // save HERE to stack
}

void KVMLoop(KsanaVm *vm)
{
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}

	DictCompile(vm,doLoop);          // the runtime of loop
    DictCompile(vm, KVMPop(vm)); // begin address of Do
}
void KVMPlusLoop(KsanaVm *vm)
{
	if (!vm->compiling ) {
		printf("must be in compile state!");
		return;
	}
	DictCompile(vm,doPlusLoop);    // the runtime of +loop
    DictCompile(vm, KVMPop(vm)); // begin address of Do
}
void KVMI(KsanaVm *vm)
{
    KVMPush( vm, KVMRTOS(vm) );  //get index
}

/* --------------------------Lesson 16 ------------------------*/
void KVMRecurse(KsanaVm *vm)
{
	DictCompile(vm,vm->newword.xt);
}

void KsanaVmAddFlowWord(KsanaVm *vm)
{
	//lesson 10
	KVMAddWord(vm, "if", KVMIf); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	KVMAddWord(vm, "then", KVMThen); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	KVMAddWord(vm, "else", KVMElse); KVMSetImmediate(vm); KVMSetCompileOnly(vm);

	//lesson 11
	KVMAddWord(vm,"do",KVMDo); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	KVMAddWord(vm,"loop",KVMLoop); KVMSetImmediate(vm);  KVMSetCompileOnly(vm);
	KVMAddWord(vm,"+loop",KVMPlusLoop); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
	KVMAddWord(vm,"i",KVMI); KVMSetCompileOnly(vm);

	//lesson 15
	KVMAddWord(vm,"recurse",KVMRecurse); KVMSetImmediate(vm); KVMSetCompileOnly(vm);
}

/*
http://claymore.engineer.gvsu.edu/~steriana/Software/pfavr/design.html
*/
