\ forth style comment
( bracket comment, for stack effect notation )

.( compiling hello) cr
: hello ( -- ) 
  s" hello,world from external file" type cr
;

.( running hello) cr
hello