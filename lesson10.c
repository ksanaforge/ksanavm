/* lesson 9
  control flow

yap 2007.12.17 release under GPL 3.0

  YOU WILL LEARN
  1) how to construct a control flow

*/

#include "compiler.h"
#include "progflow.h"
#include "lesson.h"

// now every thing need at runtime ( functions and data)  can be prepared by DictCompile
// the compiler is almost ready



void addword10(KsanaVm *vm)
{
	addword9(vm);
	addflowword(vm);
}
void example10(KsanaVm *vm)
{
	//Eval(vm,": test 100 > if 1 then ;");
	
	Eval(vm,": test2 if s\" true \" type else s\" false \" type then ;");
	/*
	  : test2
		if 
		   s" true " type
	   else
	      s" false " type
	   then
      ;
    */

    puts("guess a number:   n guess ");
    Eval(vm,": guess dup 33 > if drop s\" to big!\" type else 33 < if s\" too small!\" type else s\" bingo!\" type then then ;");   
	/*
         : guess  ( n -- 1|0 ) 
	     dup    \  n n
		    33 >      \ n n 33
			if  
		      drop     \ drop the extra n
			  s" to big!" type
		    else
			  33 <      \ n 33
			  if 
			     s" too small" type
			  else
			     s" bingo!" type
			  then       \ end of inner if-else-then
		    then         \ end of outer if-else-then
		 ;
	*/
}
int lesson10(KsanaVm *vm)
{
	if (KVMFindWord(vm,"guess") ==0) {
		addword10(vm);
		example10(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}