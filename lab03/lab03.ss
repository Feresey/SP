(define VARIANT 13)
(define LAST-DIGIT-OF-GROUP-NUMBER 8)
(define LARGEST-COIN 20)

;(define (implication? x? y?)
  ;(not (and
   ;     x?
    ;    (not y?)
  ;      )
 ; )
;)

(define (cc amount largest-coin)
  (if ( = amount 0)
     (if (= largest-coin 1)
        1 
        (if (not(= largest-coin 0))
           (+ (cc amount  (next-coin largest-coin))
               (cc (- amount largest-coin) largest-coin))
           0
           )
        )
     (if (> amount 0)
        (if (not(= largest-coin 0))
           (+ (cc amount  (next-coin largest-coin))
               (cc (- amount largest-coin) largest-coin))
           0
           )
        0
        )
     )
  )

(define (count-change amount)
  (cc amount LARGEST-COIN)
)

(define (next-coin coin)
  (cond ((= coin 20) 10)
        ((= coin 10) 5)
        ((= coin 5) 3)
        ((= coin 3) 2)
        ((= coin 2) 1)
        (else 0)
  )
)

(define (GR-AMOUNT)
  (remainder (+(* 100  LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 137)
)

(display " LOR variant ")
(display VARIANT)
(newline)
(display " 1-3-5-10-20")
(newline)
(display "count-change for 100 \t= ")
(display (count-change 100))
(newline)
(display "count-change for ")
(display (GR-AMOUNT))
(display " \t= ")
(display (count-change (GR-AMOUNT)))

