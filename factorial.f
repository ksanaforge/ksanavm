\ calculate factorial using recursion
: fac ( n -- fac_n )
  dup 2 < if
    drop 1                \ fac(0) = fac(1) = 1
  else 
    dup 1 - recurse *     \ fac(n) = n * fac(n-1) 
  then 
;
.( fac of 10 is ) 10 fac .