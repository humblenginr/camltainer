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
















/*

CAMLprim value execv_with_attr(value path)
{
	CAMLparam1 (to_print);
	int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWNS;
	pid_t p = clone(child, malloc(4096) + 4096, SIGCHLD|namespaces, NULL);
	CAMLreturn (Val_unit);
}

CAMLprim value clone_syscall(value to_print)
{
	CAMLparam1 (to_print);
	printf(String_val(to_print));
	CAMLreturn (Val_int(100));
}

nt child(void *args);

int child(void *args)
{
    printf("pid as seen in the child: %lu\n", (unsigned long)getpid());
    // unmount all
    // chroot (bind mount/pivot root dance)
    // mount /proc (make /dev?)
    // remove capabilities? or switch user
    spawn_bash();
}


*/
