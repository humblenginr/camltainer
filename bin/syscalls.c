#define _GNU_SOURCE    
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <mlvalues.h>
#include <memory.h>

// CLONE_NEWUTS - 0
// CLONE_NEWPID - 1
// CLONE_NEWNS - 2

CAMLprim value unix_unshare(value flags) 
{
	CAMLparam1 (flags);
	int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWNS|CLONE_NEWUSER;
	unshare(namespaces);
	CAMLreturn (Val_unit);
}

CAMLprim value unix_sethostname(value hostname, value length) 
{
	CAMLparam2 (hostname, length);
    sethostname(String_val(hostname),Int_val(length));
	CAMLreturn (Val_unit);
}

