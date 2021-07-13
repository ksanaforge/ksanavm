/* lesson 13
  Chinese programming language

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
 

*/

#include "compiler.h"



int example13(KsanaVm *vm)
{
	char *sqrt_source="�] ����� �s �� �s �� �@ �[ �� �G �� �@ �[ +�j �w";
	Eval(vm,"alias : �]");
	Eval(vm,"alias ; �w");
	Eval(vm,"alias dup ��");
	Eval(vm,"alias swap ��");
	Eval(vm,"alias do ��");
	Eval(vm,"alias loop �j");
	Eval(vm,"alias +loop +�j");

	Eval(vm,"alias . �L");
	Eval(vm,"alias variable ��");
	Eval(vm,"alias create ��");
	Eval(vm,"alias , �s");
	Eval(vm,"alias allot �t");
	Eval(vm,"alias does> �@");
	Eval(vm,"alias * ��");
	Eval(vm,"alias + �[");
	Eval(vm,": �s 0 ;");
	Eval(vm,": �@ 1 ;");
	Eval(vm,": �G 2 ;");
	
	Eval(vm,"�] ���� �� �� �w");
	Eval(vm,"�] �ߤ� �� �� �� �� �w");
	
	Eval(vm,sqrt_source);
	printf("source of square root: \n%s\n\n",sqrt_source);
	Eval(vm,": test dup . s\" ������ڬ�\" type ����� �L ;");
}
void addword13(KsanaVm *vm)
{
	addword10(vm);
	addioword(vm);
	addvarword(vm);
	addaliasword(vm);
}
int lesson13(KsanaVm *vm)
{	
	if (KVMFindWord(vm,"alias") ==0) {
		addword13(vm);
		example13(vm);
	}

	Eval(vm,vm->tib);
    KVMDumpStack(vm);
	return 0;
}