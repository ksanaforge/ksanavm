#include "vm.h"
#include "io.h"
void KVMDot(KsanaVm *vm)
{
    char buf[16];
    snprintf(buf,sizeof(buf),"%d ",KVMPop(vm));
	(vm->textout)(vm,buf);
}
void KVMHDot(KsanaVm *vm)
{
    char buf[16];
    snprintf(buf,sizeof(buf),"%x ",KVMPop(vm));
	(vm->textout)(vm,buf);
}
void KVMDotR(KsanaVm *vm)
{
    char format[16],buf[16];
    snprintf(format,sizeof(format),"%%0%dd",KVMPop(vm));
	snprintf(buf,sizeof(buf),format,KVMPop(vm));
	(vm->textout)(vm,buf);
}
void KVMHDotR(KsanaVm *vm)
{
    char format[16],buf[16];
    snprintf(format,sizeof(format),"%%0%dx",KVMPop(vm));
	snprintf(buf,sizeof(buf),format,KVMPop(vm));
	(vm->textout)(vm,buf);
}
void KVMemit(KsanaVm *vm)
{
    char buf[16];
    snprintf(buf,sizeof(buf),"%c",KVMPop(vm));
	(vm->textout)(vm,buf);
}

void KVMCr(KsanaVm *vm)
{
	(vm->textout)(vm,"\n");
}

// ( zstring -- )
void KVMEval(KsanaVm *vm)
{
    char *toeval=(char*)KVMPop(vm);
    int ip=vm->ip;
    KsanaVmEval(vm,toeval);
    vm->ip=ip;
    vm->abortexec=0;
}

void KsanaVmAddIOWord(KsanaVm *vm)
{
	KVMAddWord(vm,".",KVMDot);
	KVMAddWord(vm,"h.",KVMHDot);
	KVMAddWord(vm,".r",KVMDotR);
	KVMAddWord(vm,"h.r",KVMHDotR);
	KVMAddWord(vm,"emit",KVMemit);
	KVMAddWord(vm,"cr",KVMCr);
	KVMAddWord(vm,"eval",KVMEval);

}
void KsanaSetTextOut(KsanaVm *vm, KsanaTextOut textout)
{
    vm->textout = textout;
}
void KsanaSetErrTextOut(KsanaVm *vm, KsanaTextOut errtextout)
{
    vm->errtextout = errtextout;
}
