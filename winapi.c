#include "vm.h"
#include "windows.h"

typedef int (*FARG0)(void);
typedef int (*FARG1)(int);
typedef int (*FARG2)(int,int);
typedef int (*FARG3)(int,int,int);
typedef int (*FARG4)(int,int,int,int);
typedef int (*FARG5)(int,int,int,int,int);
typedef int (*FARG6)(int,int,int,int,int,int);
typedef int (*FARG7)(int,int,int,int,int,int,int);
typedef int (*FARG8)(int,int,int,int,int,int,int,int);
typedef int (*FARG9)(int,int,int,int,int,int,int,int,int);
typedef int (*FARG10)(int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG11)(int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG12)(int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG13)(int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG14)(int,int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG15)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG16)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG17)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG18)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
typedef int (*FARG19)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);


// ( -dllname- )  create a new variable named dllname
void KVMLoadLib(KsanaVm *vm)
{
	int dll;
	KVMcreate(vm);
	dll=LoadLibraryA(vm->token);   // get the handle
	DictCompile(vm,dll);
}


void KVMdoWinapi(KsanaVm *vm)
{
	int i,p,r, proc=*(int*)vm->ip;
	int paracount=*(int*)(vm->ip+CELLSIZE);

#define SPOP KVMPop(vm)
    switch (paracount) {
        case 0: r=((FARG0)(proc))() ; break;
        case 1: r=((FARG1)(proc))(SPOP ); break;
        case 2: r=((FARG2)(proc))( SPOP,SPOP); break;
        case 3: r=((FARG3)(proc))( SPOP,SPOP ,SPOP ); break;
        case 4:r= ((FARG4)(proc))( SPOP,SPOP,SPOP ,SPOP  ); break;
        case 5: r=((FARG5)(proc))( SPOP ,SPOP ,SPOP,SPOP ,SPOP ); break;
        case 6:r= ((FARG6)(proc))( SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP); break;
        case 7:r= ((FARG7)(proc))( SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP,SPOP ); break;
        case 8: r=((FARG8)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP,SPOP ,SPOP ); break;
        case 9:r= ((FARG9)(proc))( SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP,SPOP ,SPOP ,SPOP ); break;
        case 10:r= ((FARG10)(proc))( SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP,SPOP ,SPOP ,SPOP ,SPOP ); break;
        case 11:r= ((FARG11)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP,SPOP
               ,SPOP ,SPOP ,SPOP ,SPOP ); break;
        case 12:r= ((FARG12)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP  );break;
        case 13:r= ((FARG13)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP  );break;
        case 14:r= ((FARG14)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP  );break;
        case 15:r= ((FARG15)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP,SPOP  );break;
        case 16:r= ((FARG16)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP,SPOP,SPOP  );break;
        case 17:r= ((FARG17)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP,SPOP,SPOP,SPOP   );break;
        case 18:r= ((FARG18)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP,SPOP,SPOP,SPOP ,SPOP   );break;
        case 19:r= ((FARG19)(proc))( SPOP ,SPOP ,SPOP ,SPOP ,SPOP,SPOP ,SPOP,SPOP ,SPOP
               ,SPOP ,SPOP ,SPOP,SPOP,SPOP,SPOP,SPOP,SPOP ,SPOP ,SPOP   );break;
    }

#undef SPOP
	KVMPush(vm,r);
	//leave the high level defined by "CREATE" in Winapi
	KVMRet(vm);
}

// ( dll n -name- )
void KVMWinapi(KsanaVm *vm)
{
	int proc,paracount=KVMPop(vm);
	int dll=KVMPop(vm);
	KVMcreate(vm);                                         // create a new word with same name

	proc=GetProcAddress(dll,vm->token);          // windows API

	ChangeCreateCodeField(vm,KVMdoWinapi);  // change code field
	DictCompile(vm,proc);                                // entry point of API
	DictCompile(vm,paracount);                        // number of parameter
}
//lesson 15
void KVMInclude(KsanaVm *vm)
{
	FILE *f;
	int linecount=0;
	char *fn;
	char *pfn;
	char buffer[1024];
	char errbuf[1024];
	char *tempsourcefile;

	fn=(char*)KVMPop(vm);

	pfn=fn+strlen(fn)-1;
	//trim ending spaces
	while (*pfn<32 && pfn>fn) {
	    *pfn=0;
	    pfn--;
	}
	f=fopen(fn,"r");
	if (!f) {
	    snprintf(errbuf,sizeof(errbuf),"Error loading file %s",fn);
        (vm->errtextout)(vm,errbuf);
		return;
	}

    vm->sourceline=0;
    tempsourcefile=vm->sourcefile;
    vm->sourcefile=fn;
	while (!feof(f)) {
		fgets(buffer,1024,f);
		vm->sourceline++;
		KsanaVmEval(vm,buffer);
		if (vm->quit) {
		    sprintf(errbuf,"error at %d, file %s", vm->sourceline,fn);
		    (vm->errtextout)(vm,errbuf);
		    break;
		}
	}
	vm->sourcefile=tempsourcefile;
	fclose(f);
}

void KsanaVmAddWinapiWord(KsanaVm *vm)
{
	//lesson 9
	KVMAddWord(vm, "loadlibrary", KVMLoadLib);
	KVMAddWord(vm, "winapi", KVMWinapi);

	//lesson 15
	KVMAddWord(vm, "include", KVMInclude);
    KsanaVmEval(vm, ": fload 32 zword include ;");

}
