#ifndef KVM_COMPILER
#define  KVM_COMPILER
#include "vm.h"
// lesson 4

void KVMComma(KsanaVm *vm);
void KVMHere(KsanaVm *vm);

// lesson 7, literal
void KVMdoLiteral(KsanaVm *vm);   // the runtime code for pushing a literal to the stack

// lesson 8 
void KVMColon(KsanaVm *vm);   // the runtime code for pushing a literal to the stack
void KVMSemicolon(KsanaVm *vm);   // the runtime code for pushing a literal to the stack
void KVMSetImmediate(KsanaVm *vm);

void adddictword(KsanaVm *vm);
void addcompilerword(KsanaVm *vm);
#endif