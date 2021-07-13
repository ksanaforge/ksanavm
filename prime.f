\ Using Algorithm in http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
\ by yap yapcheahshen@gmail.com 2008.1.23

: n 1024 ;                                     \ find all prime below N
: sqrt 0 swap 0 do 1 + dup 2 * 1 + +loop ;  \ square root
create buffer n allot                           \ buffer to hold numbers 
buffer n 255 fill                    \ initial value, all numbers are prime

\ sieve ( r -- )  remove all proper multiply of r , 
\ which are r*2, r*3, r*4 ... r*m < n 
: sieve n over dup + do 0 i buffer + c! dup +loop drop ; 

\ sieve all number less than square root of N
: eratosthenes n sqrt 2 do buffer i + c@ if i sieve then loop ; 

: prime eratosthenes n 2 do buffer i + c@ if i . then loop ;
.( Prime numbers below ) n . cr prime