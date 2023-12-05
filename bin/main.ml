external unshare : int -> unit
   = "unix_unshare"


external sethostname : string -> int -> unit
   = "unix_sethostname"


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
            

