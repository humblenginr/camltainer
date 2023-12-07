#define _GNU_SOURCE    
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/param.h>

#include <unistd.h>

#include <mlvalues.h>
#include <memory.h>

// CLONE_NEWUTS - 0
// CLONE_NEWPID - 1
// CLONE_NEWNS - 2

CAMLprim value unix_unshare(value flags) 
{
	CAMLparam1 (flags);
	int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWNS|CLONE_FS|CLONE_FILES;
	unshare(namespaces);
	CAMLreturn (Val_unit);
}

CAMLprim value unix_sethostname(value hostname, value length) 
{
	CAMLparam2 (hostname, length);
        sethostname(String_val(hostname),Int_val(length));
	CAMLreturn (Val_unit);
}

CAMLprim value unix_mount(value src, value target,value type,value flags, value data) 
{
	CAMLparam5 (flags, type, src, target, data);
        // mount("proc","proc", 0, "");
        mount(String_val(src), String_val(target),String_val(type),Int_val(flags),String_val(data));
	CAMLreturn (Val_unit);
}
