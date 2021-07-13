/* lesson 17
  print prime number 
  using the Sieve of Eratosthenes
  http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

yap 2007.1.23 release under GPL 3.0

  YOU WILL LEARN
   create array with CREATE ALLOT

*/

#include "compiler.h"

int example17(KsanaVm *vm)
{
	Eval(vm,"include prime.f");
}
int lesson17(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"prime") ==0) {
		addword13(vm);
		addwinapiword(vm);
		example17(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}