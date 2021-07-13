#include "vm.h"
#include "io.h"

void KVMfind(KsanaVm *vm)
{
    int i,cfa=0;
    char *name;

    KVMPop(vm);//drop count
    name=KVMPop(vm);
    for (i=0;i<vm->nword;i++) {
        if (0==strcmp(name,vm->vectors[i].name)) {
            cfa=vm->vectors[i].xt;
            break;
        }
    }
    if (0==cfa) {
        (vm->errtextout)(vm,"no such word ");
        (vm->errtextout)(vm,name);
    }
    KVMPush(vm,cfa);

}
void KVMtick(KsanaVm *vm)
{
    KVMNextToken(vm);

    KVMPush(vm,vm->token);
    KVMZCount(vm);
    KVMfind(vm);
}

void KVMtoname(KsanaVm *vm)
{
    int i,nfa=0,cfa=0;
    cfa=KVMPop(vm);
    for (i=0;i<vm->nword;i++) {
        if (vm->vectors[i].xt==cfa) {
            nfa=vm->vectors[i].name;
            break;
        }
    }
    if (0==nfa) {
        (vm->errtextout)(vm,"no such cfa");
    }
    KVMPush(vm,nfa);
}

void KVMtor(KsanaVm *vm)
{
    KVMRPush(vm,KVMPop(vm));
}
void KVMrat(KsanaVm *vm)
{
    KVMPush( vm,KVMRTOS(vm));
}
/* ( cfa -- 0|1 ) */
void KVMiscodeword(KsanaVm *vm)
{
    int p=KVMPop(vm);
    KVMPush(vm, !(p>=vm->dictionary && p<=vm->dictionary +vm->here));

}
void KVMfirstword(KsanaVm *vm)
{
    KVMPush(vm, &(vm->vectors[0]));
}
void KVMlastword(KsanaVm *vm)
{
    KVMPush(vm, &(vm->vectors[vm->nword-1]));
}
void KVMDebug1(KsanaVm *vm)
{
    int i=0;
}
void KVMDebug2(KsanaVm *vm)
{
    int i=0;
}
void KVMDebug3(KsanaVm *vm)
{
    int i=0;
}
void KVMpick(KsanaVm *vm)
{
    int i=KVMPop(vm);
    KVMPush( vm, vm->datastack[vm->sp-i]);
}
void KVMdepth(KsanaVm *vm)
{
    KVMPush( vm, vm->sp+1);
}

void KVMabort(KsanaVm *vm)
{
    vm->abortexec=1;
    vm->quit=1;
}

void KVMcmove(KsanaVm *vm)
{
    char *source,*dest;
    int u;
    u=KVMPop(vm);
    dest=KVMPop(vm);
    source=KVMPop(vm);
    if (!(inDictionary(vm,source) && inDictionary(vm,source+u)))
    {
        (vm->errtextout)(vm,"invalid CMOVE source address");
            return 0;
    }
    if (!(inDictionary(vm,dest) && inDictionary(vm,dest+u)))
    {
        (vm->errtextout)(vm,"invalid CMOVE Destination address");
            return 0;
    }

    memcpy(dest,source,u);
}

//scan tib until delimiter
//return a null terminated string
char zword_buf[1024];
void KVMzword(KsanaVm *vm)
{
    char c,delimiter;
    int n=0;

    delimiter = (char)KVMPop(vm);

    //skip leading delimiter
    while (c=*(vm->tib+vm->ntib)) {
        if (c!=delimiter) break;
        vm->ntib++;

    }


    while (c=*(vm->tib+vm->ntib)) {
        vm->ntib++;
        if (c==delimiter) break;
        zword_buf[n++]=c;
    }
    zword_buf[n]=0;

    KVMPush(vm,zword_buf);
}
void KVMtoinfetch(KsanaVm *vm)
{
    KVMPush(vm,vm->ntib);
}

void KVMexecute(KsanaVm *vm)
{
    void *xt=KVMPop(vm);
    KsanaVmExecute(vm,xt);
    vm->abortexec=0;

}

void KVMtoinstore(KsanaVm *vm)
{
    vm->ntib=KVMPop(vm);
}
void KVMleave(KsanaVm *vm)
{
    KVMRPop(vm);
    KVMRPop(vm);
}

void KVMstatefetch(KsanaVm *vm)
{
    KVMPush(vm,vm->compiling);
}

void KVMstatestore(KsanaVm *vm)
{
    vm->compiling=KVMPop(vm);
}

void KVMcompileonly(KsanaVm *vm)
{
    KVMSetCompileOnly(vm);
}


void KsanaVmAddDebugWord(KsanaVm *vm)
{
	KVMAddWord(vm,"'",KVMtick);
	KVMAddWord(vm,"find",KVMfind);
	KVMAddWord(vm,">r", KVMtor);
	KVMAddWord(vm,"r@", KVMrat);

	KVMAddWord(vm,"firstword", KVMfirstword);
	KVMAddWord(vm,"lastword", KVMlastword);

	KsanaVmEval(vm,": compile ' , ; ");
	KsanaVmEval(vm,": [compile] ' , ; immediate");
	KVMAddWord(vm,"debug1",KVMDebug1);
	KVMAddWord(vm,"debug2",KVMDebug2);
	KVMAddWord(vm,"debug3",KVMDebug3);
	KVMAddWord(vm,"pick",KVMpick);
	KVMAddWord(vm,"depth",KVMdepth);

	KVMAddWord(vm,"abort",KVMabort);

	KVMAddWord(vm,"state@",KVMstatefetch);
	KVMAddWord(vm,"state!",KVMstatestore);

	KVMAddWord(vm,"compile-only",KVMcompileonly);

	KVMAddWord(vm,"cmove",KVMcmove);
	KVMAddWord(vm,"zword",KVMzword);
	KVMAddWord(vm,">in@",KVMtoinfetch);
	KVMAddWord(vm,">in!",KVMtoinstore);

	KVMAddWord(vm,"execute",KVMexecute);
	KVMAddWord(vm,"leave",KVMleave);
    KVMAddWord(vm,">name",KVMtoname);

	KVMAddWord(vm,"iscodeword",KVMiscodeword); // ( cfa -- 0!1)

}
