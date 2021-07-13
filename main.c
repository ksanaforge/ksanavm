//main loop of Ksana Minimal Virtual Machine
//release under GPL 3.0
//yap 2007.12.20


#include "vm.h"
#include "lesson.h"

int mytextout (KsanaVm *vm, char *toprint)
{
    printf("%s",toprint);
}


void main()
{
	char cmd [1024];            // buffer to hold input command
	KsanaVm *vm;               // the instance of virtual machine
	vm=KsanaVmCreate();          // create the virtual machine

	memset(cmd,0,sizeof(cmd));

	puts("Tutorial of Ksana Minimal Virtual Machine");
	puts("http://tutor.ksana.tw");

    KsanaSetTextOut(vm,mytextout);
    KsanaSetErrTextOut(vm,mytextout);
	while (1) {
		if (!vm->compiling) printf("ok>");                    // the command prompt
		gets(cmd);                        // get the command from console
		KsanaVmSetTib(vm,cmd);         // set it as Vm's terminal input buffer
        lesson20(vm);
		if (vm->terminate) break;
	}

	KsanaVmFree(vm);             // free the virtual machine
}
