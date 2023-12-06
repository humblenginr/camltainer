external unshare : int -> unit
   = "unix_unshare"


external sethostname : string -> int -> unit
   = "unix_sethostname"


external mount : string -> string -> string -> int -> string -> unit
   = "unix_mount"

let () = 
        unshare 0;
        let pid = Unix.fork () in
        if pid = 0 then
        begin
            sethostname "container" 9;
            Unix.chroot "/root/ubuntu-fs";
            Unix.chdir "/";
            mount "proc" "proc" "proc" 0 "";
            mount "thing" "mytemp" "tempfs" 0 "";
            Unix.execv "/bin/bash" [||]
            (*do not forget to unmount proc*)
        end
        else
            let _ =  Unix.waitpid [] (-1) in
            ()
            

