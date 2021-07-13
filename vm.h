#ifndef KSANA4TH_VM
#define KSANA4TH_VM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct KsanaVm;
typedef struct KsanaVm KsanaVm;
#define MAXNAMELEN 15
// lesson 3
typedef void (*KVMXT)(KsanaVm *vm);  // the execution vector

typedef int (*KsanaTextOut) (KsanaVm *vm, char *toprint);

typedef struct {
	char name[MAXNAMELEN+1];  // the name
	KVMXT xt;                             // the execuate vector

	//lesson 8
	char immediate;                       // execute immediately regardless of state
	char compileonly;
} KsanaWord ;   // Word is the execution unit in ksana virtual machine


/* main structure of Virtual Machine */
struct KsanaVm {
//Lesson 1
	char *tib;             //terminal input buffer, hold the text to be interpreted.
	int ntib;                //consumed index
	char token[1024];  //current token
	int terminate;       // true if VM is terminating

//Lesson 2
#define STACK_DEPTH 256
	int datastack [STACK_DEPTH]; // the stack
	int sp ;                                  // the stack pointer

//Lesson 3
#define MAXWORD 256
	KsanaWord vectors[MAXWORD];    // array to hold name and execution vector
	int nword;                                   //number of words

//Lesson 4
#define DICTSIZE 4096
#define CELLSIZE (sizeof(int))
	char dictionary[DICTSIZE];           // holds the compiled words and data
	int here;                                     // write from here

//Lesson 5
	int returnstack [STACK_DEPTH];    // the stack
	int rp ;                                       // the stack pointer

//Lesson 6
	int abortexec;                             // abort execution
	int ip;                                        // the instruction pointer, point to the next xt to be executed

//Lesson 8
	int compiling;                             // true if in compile state
	KsanaWord newword;                 // the high level word under construction

    KsanaTextOut textout;
    KsanaTextOut errtextout;
    int quit;                         // quit ksp
    int sourceline;
    char *sourcefile;
// generic usage
    void *context;
} ;


//macro for getting the Top-Of-Stack
#define KVMTOS(vm)  ((vm)->datastack[(vm)->sp])
#define KVMRTOS(vm)  ((vm)->returnstack[(vm)->rp])

//lesson 1
KsanaVm *KVMCreate();
void KsanaVmFree(KsanaVm *vm);
void KsanaVmSetTib(KsanaVm *vm, char *tib);
int KsanaVmNextToken(KsanaVm *vm);


//lesson 2
void KVMDumpStack(KsanaVm *vm);
void KVMAdd(KsanaVm *vm);
void KVMMultiply(KsanaVm *vm);
void KVMPush(KsanaVm *vm, int v);
int KVMPop(KsanaVm *vm);

// lesson 3
KVMXT KsanaVmFindWord(KsanaVm *vm,char *name);
KsanaWord *KsanaVmGetWord(KsanaVm *vm,char *name);

void KVMAddWord(KsanaVm *vm, char *name, KVMXT xt);

void KVMMinus(KsanaVm *vm);
void KVMDivide(KsanaVm *vm);
void KVMDup(KsanaVm *vm);
void KVMDrop(KsanaVm *vm);
void KVMSwap(KsanaVm *vm);
void KVMOver(KsanaVm *vm);
void KVMBye(KsanaVm *vm);

// lesson 4
int inDictionary(KsanaVm *vm, int address); //see if an address within the scope of dictionary
void DictCompile(KsanaVm *vm, int i);  // compile an integer to the dictionary

// Lesson 5
void KVMRPush(KsanaVm *vm, int v);
int KVMRPop(KsanaVm *vm);
void KVMCall(KsanaVm *vm, int startaddr); // invoke a high level call
void KVMRet(KsanaVm *vm);                    //return to caller

int do_square(KsanaVm *vm);

// Lesson 6

// Lesson 7
void KsanaVmExecute(KsanaVm *vm, void *xt);

//Lesson 9
void KsanaVmEval(KsanaVm *vm, char *s);
void KsanaVmAddBasicWord(KsanaVm *vm);
void KVMdoColon(KsanaVm *vm);
#endif
