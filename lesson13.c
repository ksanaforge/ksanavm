/* lesson 13
  Chinese programming language

yap 2007.1.21 release under GPL 3.0

  YOU WILL LEARN
 

*/

#include "compiler.h"



int example13(KsanaVm *vm)
{
	char *sqrt_source="設 平方根 零 換 零 返 一 加 複 二 乘 一 加 +迴 定";
	Eval(vm,"alias : 設");
	Eval(vm,"alias ; 定");
	Eval(vm,"alias dup 複");
	Eval(vm,"alias swap 換");
	Eval(vm,"alias do 返");
	Eval(vm,"alias loop 迴");
	Eval(vm,"alias +loop +迴");

	Eval(vm,"alias . 印");
	Eval(vm,"alias variable 變");
	Eval(vm,"alias create 創");
	Eval(vm,"alias , 編");
	Eval(vm,"alias allot 配");
	Eval(vm,"alias does> 作");
	Eval(vm,"alias * 乘");
	Eval(vm,"alias + 加");
	Eval(vm,": 零 0 ;");
	Eval(vm,": 一 1 ;");
	Eval(vm,": 二 2 ;");
	
	Eval(vm,"設 平方 複 乘 定");
	Eval(vm,"設 立方 複 複 乘 乘 定");
	
	Eval(vm,sqrt_source);
	printf("source of square root: \n%s\n\n",sqrt_source);
	Eval(vm,": test dup . s\" 的平方根為\" type 平方根 印 ;");
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