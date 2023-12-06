This is a play container runtime written in ocaml.

Syntax: caml run [cmd] [args]

When we run this, we want this cmd to be ru 

Basically what I need is a docker like container runtime where I can do 
`caml run [cmd] [args]` and my container runtime should run that process in a completely new namespace with no connection or whatsoever to the host system.


The next step would be to test using a different filesystem. For that, I need to have an ubuntu filesystem


