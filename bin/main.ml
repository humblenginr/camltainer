external unshare : int -> unit
   = "unix_unshare"


external sethostname : string -> int -> unit
   = "unix_sethostname"


        (*
            int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWNS|CLONE_NEWUSER;
            unshare(namespaces);
            int pid = fork();
            if (pid != 0) {
                printf("parent pid: %i\n", getpid());
                int status;
                waitpid(-1, &status, 0);
                return status;
            }
            printf("My pid: %i\n", getpid());
            char *args[]={"",NULL};
            sethostname("container",9);
            execv("/bin/bash",args);
        *)

let () = 
        unshare 0;
        let pid = Unix.fork () in
        if pid = 0 then
        begin
            let child_pid = Unix.getpid () in
            print_endline ("I am the child speaking with pid: " ^ Int.to_string child_pid);
            sethostname "container" 9;
            Unix.execv "/bin/bash" [||]
        end
        else
            let parent_pid = Unix.getpid () in
            print_endline ("I am the parente speaking with pid: " ^ Int.to_string parent_pid);
            let _ =  Unix.waitpid [] (-1) in
            ()
            

