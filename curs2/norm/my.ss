(define(even-bits n)
  (cond((= n 0)1)
       (else(odd-bits(quotient n 2)))
       ))
