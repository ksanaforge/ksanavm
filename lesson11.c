/* lesson 11
  do loop 
  
yap 2007.1.20 release under GPL 3.0

  YOU WILL LEARN
  1) how to construct a loop
  2) output numberic value
*/

#include "compiler.h"

void example11(KsanaVm *vm)
{
    Eval(vm,": row 10 1 do dup i * . loop drop ;");
    Eval(vm,": 9x9 10 1 do  i row cr loop ;");

    Eval(vm,": sq dup * ;");
    Eval(vm,": sqrt 0 swap 0 do 1 + dup 2 * 1 + +loop ;");  
	/*
	by Wil Baden
       : SQRT ( n1 -- n2, n2**2<=n1 )
              0                 \ �ڤ����
              SWAP 0        \ �] N1 �� limit
              DO 1+ DUP   \ ��s��
              2* 1+           \ ( 2n+1 )
              +LOOP          \ �� 2N+1 �[���`�M�A�p�G�p��N1�h�A���A�_�h����
		;
	*/ 
    Eval(vm,": tri sq swap sq + sqrt ;");  // third side of a right angle triangle
	printf("tri ( s1 s2 -- s2 ) \n");
	printf("sqrt ( n -- root ) \n");
}
int lesson11(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"sqrt") ==0) {
		addword10(vm);
		addioword(vm);
		example11(vm);
	}
	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}