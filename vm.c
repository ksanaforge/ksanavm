/*
Ksana Minimal Virtual Machine
yap 2007.12.17
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vm.h"
#include "compiler.h"

/* --------------------------Lesson 1 ------------------------*/
//constructor
KsanaVm *KsanaVmCreate()
{
	KsanaVm *vm;
	vm=(KsanaVm*)(malloc(sizeof(KsanaVm)));
	memset(vm,0,sizeof(KsanaVm));
	vm->sp=-1;
	vm->rp=-1;
	vm->abortexec=0;
	return vm;
}
//destructor
KsanaVmFree(KsanaVm *vm)
{
	free(vm);
}

void KsanaVmSetTib(KsanaVm *vm, char *tib)
{
	vm->tib=tib;
	vm->ntib=0;
}

/* get a token from tib, delimiter by space character (ascii <=32) */
int KVMNextToken(KsanaVm *vm)
{
	char *ptib,*ptoken;
	if (!vm->tib) return 0; // nothing to process

	ptib=vm->tib+vm->ntib;


	while (*ptib && *ptib <=' ') {
		ptib++;  // skip the leading delimiter
	}

	ptoken=vm->token;
	while (*ptib && *ptib>' ') {
		*ptoken++ = *ptib++;
		if ((ptoken - vm->token)>=sizeof(vm->token)-1) break;  // check if exceed maximum token
	}
	*ptoken=0;  // ending null byte

	vm->ntib = ptib - vm->tib ;//update the consumed index

	return *(vm->token);  // return true if token length>0 ( not null string)
}


/* --------------------------Lesson 2 ------------------------*/

void KVMPush(KsanaVm *vm, int v)
{
	if ( (vm->sp)  >= STACK_DEPTH) {
		puts("Stack Overflow");
		return;
	}
	vm->sp++;
	vm->datastack[vm->sp]=v;
}
int KVMPop(KsanaVm *vm)
{
	int v;
	if ( vm->sp  < 0 ) {
		puts("Stack under flow");
		return 0;
	}

	v= vm->datastack[vm->sp];
	vm->sp--;
	return v;
}




// pop two item , do multiplication and push back
// stack effect diagram ( n1 n2 -- r )
void KVMAdd(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1+n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}

// pop two item , do multiplication and push back
// ( n1 n2 -- r )
void KVMMultiply(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1*n2;              // do multiplication
	KVMPush(vm,  r );   // push to stack
}
void KVMDumpStack(KsanaVm *vm)
{
	int i;
	char buf[2048];
	char str[16];

	if (vm->sp<0) {
		puts("Empty stack");
		return;
	}
	memset(buf,0,sizeof(buf));
	memset(str,0,sizeof(str));

	strncat(buf,"stack:",sizeof(buf));
	for (i=0;i<=vm->sp;i++)
	{
		//itoa(vm->datastack[i],str,10);
		sprintf(str,"%d",vm->datastack[i]);  //aguai suggested
		strncat(buf,str,sizeof(buf));
		strncat(buf," ",sizeof(buf));
	}
	puts(buf);
}

/* --------------------------Lesson 3 ------------------------*/

/* add a new word  */
void KVMAddWord(KsanaVm *vm, char *name, KVMXT xt)
{
	if( vm->nword>=MAXWORD) {
		puts("too many words!");
		return;
	}

	strncpy( vm->vectors[vm->nword].name, name, MAXNAMELEN);
	vm->vectors[vm->nword].xt = xt;

	vm->nword++;
}
// for compability issue
KVMXT KsanaVmFindWord(KsanaVm *vm,char *name)
{
	KsanaWord *w;
	w=KsanaVmGetWord(vm,name);
	if (w) return w->xt;
	return NULL;
}


/* given a name , return the word , return NULL if not found*/
KsanaWord *KsanaVmGetWord(KsanaVm *vm,char *name)
{
	int i;
	KsanaWord *word;
	for (i=vm->nword;i>=0;i--) {  // scan from bottom, newly added word.
		word = &(vm->vectors[i]);
		if (strcmp(word->name, name)==0) return word;
	}
	return NULL;
}


// ( n -- n n )
void KVMDup(KsanaVm *vm)
{
	if ( (vm->sp)  >= STACK_DEPTH) {
		puts("Stack Overflow");
		return;
	}
	KVMPush(vm, KVMTOS(vm));
}
// ( n -- )
void KVMDrop(KsanaVm *vm)
{
	KVMPop(vm);
}
// ( n1 n2 -- n2 n1 )
void KVMSwap(KsanaVm *vm)
{
	int temp;
	if (vm->sp<1) {
		puts("need at least 2 items on stack");
		return;
	}

	temp=KVMTOS(vm);
	KVMTOS(vm)=((vm)->datastack[(vm)->sp-1]);
	((vm)->datastack[(vm)->sp-1]) = temp;
}

// ( n1 n2 -- n1 n2 n1 )
void KVMOver(KsanaVm *vm)
{
	int temp;
	if (vm->sp<1) {
		puts("need at least 2 items on stack");
		return;
	}

	temp=((vm)->datastack[(vm)->sp-1]);
	KVMPush(vm,temp);
}


void KVMMinus(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1-n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}

// pop two item , do division and push back
// ( n1 n2 -- r )
void KVMDivide(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1 /n2;              // do multiplication
	KVMPush(vm,  r );   // push to stack
}
void KVMBye(KsanaVm *vm)
{
	vm->terminate=1;
}
/* --------------------------Lesson 4 ------------------------*/
int inDictionary(KsanaVm *vm, int address)
{
	return (address>=vm->dictionary) && (address<=vm->dictionary+DICTSIZE);
}




/* --------------------------Lesson 5 ------------------------*/
//push to return stack
void KVMRPush(KsanaVm *vm, int v)
{
	if ( (vm->rp)  >= STACK_DEPTH) {
		puts("Return Stack Overflow");
		return;
	}
	vm->rp++;
	vm->returnstack[vm->rp]=v;
}
//pop from return stack
int KVMRPop(KsanaVm *vm)
{
	int v;
	if ( vm->rp  < 0 ) {
		puts("Return Stack under flow");
		return 0;
	}

	v= vm->returnstack[vm->rp];
	vm->rp--;
	return v;
}


// invoke a high level word,  the forth "innerloop"
void KVMCall(KsanaVm *vm, int startaddr)
{
  int addr;

  vm->abortexec=0;
  vm->ip=startaddr;


  do {
    if (0==vm->ip) {
      vm->abortexec=1;
      exit;
    } else {

    addr=*((int*)vm->ip);
    vm->ip+=CELLSIZE;
    if (inDictionary(vm,addr)) {
      KVMRPush(vm,vm->ip);
      KVMCall(vm,addr);
    } else {
      (*(KVMXT)(addr))(vm);
    }

    }
  } while (!vm->abortexec) ;
  vm->abortexec = vm->ip ? 0 : 1;  // 當 vm->ip 還有東西時， 馬上又把 vm->abortexec 清掉。讓上一層 KVMCall() 完成遺志。
}

void KVMdoColon(KsanaVm *vm)
{
  //  vm->ip+=CELLSIZE;
  //nothing , just a place holder
}
void KVMRet(KsanaVm *vm)            // return to caller
{
  vm->abortexec=1;  // stop innerloop *2*
  if (vm->rp < 0) {
      vm->ip = 0; // 增加這個 NULL 攜帶充分的訊息給上層參考
  } else {
      vm->ip=KVMRPop(vm);
  }
}
/* --------------------------Lesson 7 ------------------------*/
void KsanaVmExecute(KsanaVm *vm, void *xt)
{
	if (inDictionary(vm,xt)) {         //** these two line is added to check if a high level word
	    KVMRPush(vm,vm->ip);
		KVMCall(vm, xt);               //** execute high level word, set a break point here and type test
	} else {
		(*(KVMXT)(xt))(vm) ;       // cast to KVMXT and execute the code-word ( c function )
	}
}


/* --------------------------Lesson 9 ------------------------*/

void KVMGT(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1>n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}
void KVMLT(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1<n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}
void KVMEqual(KsanaVm *vm)
{
	int n1,n2 ,r ;
	n2=KVMPop(vm);    // pop second operand
	n1=KVMPop(vm);    // pop first operand
	r= n1==n2;              // do addition
	KVMPush(vm,  r );   // push to stack
}

/* ------------- lesson 9 ---------------*/
void KsanaVmEval(KsanaVm *vm, char *s)
{
	KsanaWord *w;
	int v;
	char *cmd=vm->tib; //save current tib
	int ntib=vm->ntib;
	char errbuf[256];

	KsanaVmSetTib(vm,s);
	vm->abortexec=0;

//the main loop need some changes...
	while ( KVMNextToken(vm) ) {
		w = KsanaVmGetWord(vm,vm->token);
		if (w) {
		    if (vm->compiling) {
		        if (w->immediate) {
		            KsanaVmExecute(vm, w->xt);
		        } else {
		            DictCompile(vm, w->xt);         //!!  compile the xt to dictionary , instead of running it
		        }

		    } else {  // interpreter mode
		        if (!w->compileonly) {
		            KsanaVmExecute(vm, w->xt);
		        }

		        if (w->compileonly) {
                    snprintf(errbuf,sizeof(errbuf),"'%s' is a compile only word",vm->token );
                    (vm->errtextout)(vm,errbuf);
		        }
		    }

		} else {
		                                    // the rest are same as lesson 3
            if ('$'==vm->token[0]) {
                v=0;
                sscanf(vm->token+1,"%x",&v);
            } else {
                v=atoi(vm->token); // see if it is a numeric value
            }
			if ((0==v) && (0!=strcmp(vm->token,"0"))) {

                snprintf(errbuf,sizeof(errbuf),"? %s",vm->token);
				(vm->errtextout)(vm,errbuf);
			} else {
				// got a valid numeric value, push the value into the stack
				if (vm->compiling) {                        // compiling mode
					DictCompile(vm, KVMdoLiteral); 	//!! compile a literal
					DictCompile(vm, v);                    // at runtime, the v will be push to stack
				} else {
					KVMPush(vm,v);                        // interpreter mode, simply push on stack
				}
			}
		}
		if (vm->quit) break;
	}
	KsanaVmSetTib(vm,cmd);//restore
	vm->ntib=ntib;        //restore ntib
}

// lesson 13
void KVMAlias(KsanaVm *vm)
{
	KsanaWord *word;
	KVMNextToken(vm);
	word=KsanaVmGetWord(vm,vm->token);

	KVMNextToken(vm);
	KVMAddWord(vm,vm->token, word->xt);
	if (word->immediate) KVMSetImmediate(vm);
	if (word->compileonly) KVMSetCompileOnly(vm);
}


void KsanaVmAddBasicWord(KsanaVm *vm)
{
	KVMAddWord(vm,"+",KVMAdd);
	KVMAddWord(vm,"-",KVMMinus);
	KVMAddWord(vm,"*",KVMMultiply);
	KVMAddWord(vm,"/",KVMDivide);
	KVMAddWord(vm,"drop",KVMDrop);
	KVMAddWord(vm,"dup",KVMDup);
	KVMAddWord(vm,"swap",KVMSwap);
	KVMAddWord(vm,"over",KVMOver);
	KVMAddWord(vm,"bye",KVMBye);
	KVMAddWord(vm,">",KVMGT);
	KVMAddWord(vm,"<",KVMLT);
	KVMAddWord(vm,"=",KVMEqual);
}

void KsanaVmAddAliasWord(KsanaVm *vm)
{
	KVMAddWord(vm,"alias",KVMAlias);
}
