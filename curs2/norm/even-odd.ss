;even-odd
(define(even-bits n)
  (cond((= n 0)1)
       (else (if (= (remainder n 2) 0) (even-bits (quotient n 2))
                 (odd-bits (quotient n 2)) ))
  )
)

(define(odd-bits n)
  (cond((= n 0)0)
       (else (cond ((=(remainder n 2)0) (odd-bits (quotient n 2)))
             (else (even-bits (quotient n 2)))
	         )
	   )
  )
)

(define(display-bin n)
  (display(remainder n 2))
  (if (= n 0) 0 (display-bin (quotient n 2)))
)

(define(report-results n)
  (display "Happy birthday to you!\n\t")
  (display n)    (display " (decimal)\n\t")
  (display-bin n)(display "(reversed binary)\n")
  (display "\teven?\t")(cond ((= (even-bits n) 1) (display "yes") 1) (else (display "no") 0))
  (newline)
  (display "\todd?\t") (cond ((= (odd-bits n) 1) (display "yes") 1)  (else (display "no") 0))
  (newline)
  0
)
;***** Date of YOUR birthday *******
(define dd     20)
(define mm      9)
(define yyyy 1999)
;***********************************
(report-results (+ (* dd 1000000)
                   (* mm 10000)
                      yyyy))

