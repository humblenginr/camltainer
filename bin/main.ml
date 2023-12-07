external unshare : int -> unit
   = "unix_unshare"


external sethostname : string -> int -> unit
   = "unix_sethostname"


external mount : string -> string -> string -> int -> string -> unit
   = "unix_mount"

let usage = "caml run <command> --container <fspath>"

let fspath = ref ""
let command = ref ""

let parse_args () = 
    let verb  = try Sys.argv.(1) with _ -> failwith ("Invalid usage\n Usage: "^usage) in
    match verb with 
    | "run" -> begin 
      try command := Sys.argv.(2);fspath := Sys.argv.(4) with _ -> failwith ("Invalid usage\n Usage: " ^ usage);
      end
    | _ -> failwith ("Invalid usage\n Usage: "^usage) 
  
    
let () = 
        parse_args ();
        (* unshare has to be called here because the kernel creates a new namespace, but doesn't automatically put the current process into it. Only the first child process ofthe current process will be put into the new namespace*)
        unshare 0;
        let pid = Unix.fork () in
        if pid = 0 then
        begin
            sethostname "container" 9;
            Unix.chroot (!fspath);
            Unix.chdir "/";
            mount "proc" "proc" "proc" 0 "";
            Unix.execv (!command) [||]
        end
        else
            let _ =  Unix.waitpid [] (-1) in
            ()
            

