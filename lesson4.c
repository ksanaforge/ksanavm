/* lesson 4 
  the Dictionary

  YOU WILL LEARN:
  1) Dictionary is a continuous memory space to hold compiled code and data
  2) three C functions  to manipulate dictionary
  3) two new words "here" and ","
  4) use "here" to see the consumed space (in byte) 
  5) 100 ,   to compile a number into dictionary
  6) view the dictionary with memory window

  yap 2007.12.21 release under GPL 3.0
*/

#include "compiler.h"



int lesson4(KsanaVm *vm)
{	
	if (KVMFindWord(vm,",")==0) adddictword(vm);  // adding the words for once.

	// try this out 
	// 100  , 200 ,    use memory window to observe the change of dictionary

	lesson3(vm); //reuse loop of lesson 3
	return 0;
}		