(define (div x y) (/ (- x (modulo x y)) y))

(define (day-of-week day month year)
  (let ((m (if (< month 3) (+ 12 month) month))
        (K (modulo year 100))
        (j (div year 100)))
    (modulo (+ day
       (div (* 13 (+ m 1)) 5)
       (+ K 6)
       (div K 4)
       (div j 4)
       (- (* 2 j))) 7)))