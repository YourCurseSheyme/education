(define (variable? x)
  (symbol? x))

(define (same-variable? x y)
  (and (variable? x) (variable? y) (eq? x y)))

(define (make-sum x y)
  (list '+ x y))

(define (make-subtraction x y)
  (list '- x y))

(define (make-product x y)
  (list '* x y))

(define (make-division x y)
  (list '/ x y))

(define (make-expt x y)
  (list 'expt x y))

(define (make-exp x)
  (list 'exp x))

(define (make-log x)
  (list 'log x))

(define (make-sin x)
  (list 'sin x))

(define (make-cos x)
  (list 'cos x))

(define (sum? x)
  (and (pair? x) (eq? '+ (car x))))

(define (subtraction? x)
  (and (pair? x) (pair? (cddr x)) (eq? '- (car x))))

(define (addend x)
  (cadr x))

(define (augend x)
  (caddr x))

(define (product? x)
  (and (pair? x) (eq? '* (car x))))

(define (multiplier x)
  (cadr x))

(define (multiplicand x)
  (caddr x))

(define (division? x)
  (and (pair? x) (eq? '/ (car x))))

(define (dividend x)
  (cadr x))

(define (divider x)
  (caddr x))

(define (expt? x)
  (and (pair? x) (eq? 'expt (car x))))

(define (exp? x)
  (and (pair? x) (eq? 'exp (car x))))

(define (cons-in-x? x)
  (and (pair? x) (eq? 'expt (car x)) (or (number? (cadr x)) (same-variable? (cadr x) 'e))))

(define (sin? x)
  (and (pair? x) (eq? 'sin (car x))))

(define (cos? x)
  (and (pair? x) (eq? 'cos (car x))))

(define (anglee x)
  (cadr x))

(define (base x)
  (cadr x))

(define (power x)
  (caddr x))

(define (less-power x)
  (cond ((number? (caddr x)) (- (caddr x) 1))
        ((ntv-num? (caddr x)) (list '- (+ 1 (cadr (caddr x)))))
        (else (simplify (list '- (caddr x) 1)))))

(define (log? x)
  (and (pair? x) (eq? 'log (car x))))

(define (arg x)
  (cadr x))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (ntv-num? exp)
  (and (pair? exp) (null? (cddr exp)) (eq? '- (car exp)) (number? (cadr exp))))

(define (ntv? exp)
  (and (pair? exp) (null? (cddr exp)) (eq? '- (car exp)) (variable? (cadr exp))))

(define (check xs)
  (cond ((pair? xs)
         (let ((len (length xs)))
           (cond ((= len 2) (check (cadr xs)))
                 ((= len 3) (check (cadr xs))
                            (check (caddr xs)))
                 (else (set-cdr! (cdr xs) (cons (append (list (car xs) (caddr xs)) (cdddr xs)) '()))
                       (check (cadr xs))
                       (check (caddr xs))))))))

(define (simplify x)
  (let ((premake (check x)))
    (cond ((null? x) 0)
          ((symbol? x) x)
          ((number? x) x)
          ((ntv-num? x) x)
          ((ntv? x) '('* (- 1) (simplify (cadr x))))
          ((same-variable? x 'e) x)
          ((sum? x) (let ((a (simplify (addend x)))
                          (b (simplify (augend x))))
                      (cond ((=number? a 0) b)
                            ((=number? b 0) a)
                            ((and (ntv-num? a) (ntv-num? b))
                             (simplify (list '- (+ (cadr a) (cadr b)))))
                            ((and (ntv? a) (ntv? b))
                             (simplify (list '- (make-sum (cadr a) (cadr b)))))
                            ((or (ntv-num? a) (ntv? a))
                             (simplify (make-subtraction b (cadr a))))
                            ((or (ntv-num? b) (ntv? b))
                             (simplify (make-subtraction a (cadr b))))
                            ((and (number? a) (number? b)) (+ a b))
                            (else (make-sum a b)))))
          ((subtraction? x) (let ((a (simplify (addend x)))
                                  (b (simplify (augend x))))
                              (cond ((=number? a 0) (list '- b))
                                    ((=number? b 0) a)
                                    ((and (ntv-num? a) (ntv-num? b))
                                     (simplify (make-subtraction (cadr b) (cadr a))))
                                    ((and (ntv? a) (ntv? b))
                                     (simplify (make-subtraction (cadr b) (cadr a))))
                                    ((or (ntv-num? a) (ntv? a))
                                     (simplify (list '- (simplify (make-sum (cadr a) b)))))
                                    ((or (ntv-num? b) (ntv? b))
                                     (simplify (make-sum a (cadr b))))
                                    ((and (number? a) (number? b)) (- a b))
                                    (else (make-subtraction a b)))))
          ((product? x) (let ((a (simplify (multiplier x)))
                              (b (simplify (multiplicand x))))
                          (cond ((or (=number? a 0) (=number? b 0)) 0)
                                ((=number? a 1) b)
                                ((=number? b 1) a)
                                ((and (number? a) (number? b)) (* a b))
                                (else (make-product a b)))))
          ((division? x) (let ((a (simplify (dividend x)))
                               (b (simplify (divider x))))
                           (cond ((or (and (number? a) (number? b))
                                      (and (ntv-num? a) (ntv-num? b))) (/ a b))
                                 ((or (and (number? a) (ntv-num? b))
                                      (and (ntv-num? a) (number? b))) (list '- (/ a b)))
                                 (else (make-division a b)))))
          ((cons-in-x? x) (let ((a (simplify (base x)))
                                (b (simplify (power x))))
                            (make-expt a b)))
          ((expt? x) (let ((a (simplify (base x)))
                           (b (simplify (power x))))
                       (cond ((same-variable? a 'e) (make-expt a b))
                             ((=number? a 0) 0)
                             ((=number? b 0) 1)
                             ((=number? a 1) 1)
                             ((=number? b 1) a)
                             ((and (number? a) (number? b)) (expt a b))
                             ((and (ntv-num? a) (ntv-num? b))
                              (if (even? (cadr b))
                                  (/ 1 (expt (cadr a) (cadr b)))
                                  (list '- (/ 1 (expt (cadr a) (cadr b))))))
                             ((ntv-num? a) (cond ((number? b)
                                                  (if (even? b)
                                                      (expt (cadr a) b)
                                                      (list '- (expt (cadr a) b))))
                                                 (else (make-expt a b))))
                             ((ntv-num? b) (cond ((number? a)
                                                  (/ 1 (expt a (cadr b))))
                                                 (else (make-expt a b))))
                             (else (make-expt a b)))))
          ((exp? x) (let ((a (simplify (base x))))
                      (make-exp a)))
          ((log? x) (let ((a (simplify (arg x))))
                     (cond ((number? a) (log a))
                           (else (make-log a)))))
          ((sin? x) (let ((a (simplify (anglee x))))
                      (make-sin a)))
          ((cos? x) (let ((a (simplify (anglee x))))
                      (make-cos a)))
          (else (error "not correct simplify aye")))))

(define (deriv exp var)
  (cond ((number? exp) 0)
        ((ntv-num? exp) 0)
        ((ntv? exp) (if (same-variable? (cadr exp) var) '(- 1) exp))
        ((variable? exp) (if (same-variable? exp var) 1 0))
        ((same-variable? exp 'e) (simplify exp))
        ((sum? exp) (simplify (make-sum (deriv (addend exp) var)
                                        (deriv (augend exp) var))))
        ((subtraction? exp) (simplify (make-subtraction (deriv (addend exp) var)
                                                        (deriv (augend exp) var))))
        ((product? exp) (simplify (make-sum (make-product (multiplier exp)
                                                          (deriv (multiplicand exp) var))
                                            (make-product (deriv (multiplier exp) var)
                                                          (multiplicand exp)))))
        ((division? exp) (simplify (make-division (make-subtraction
                                                   (make-product (deriv (dividend exp) var) (divider exp))
                                                   (make-product (deriv (divider exp) var) (dividend exp)))
                                                  (simplify (make-expt (divider exp) 2)))))
        ((cons-in-x? exp) (simplify (if (same-variable? (base exp) 'e)
                                        (make-product (make-expt (base exp) (power exp))
                                                      (deriv (power exp) var))
                                        (make-product (make-log (base exp))
                                                      (make-product (make-expt (base exp) (power exp))
                                                                    (deriv (power exp) var))))))
        ((expt? exp) (simplify (make-product (power exp)
                                (make-product (make-expt (base exp) (less-power exp))
                                              (deriv (base exp) var)))))
        ((exp? exp) (simplify (make-product exp
                                            (deriv (base exp) var))))
        ((log? exp) (simplify (make-division (deriv (arg exp) var) (arg exp))))
        ((sin? exp) (simplify (make-product (make-cos (anglee exp))
                                            (deriv (anglee exp) var))))
        ((cos? exp) (simplify (make-product (make-product (- 1) (make-sin (anglee exp)))
                                            (deriv (anglee exp) var))))
        (else (error "not correct deriv aye"))))

(define (derivative exp)
  (let ((premake (check exp)))
    (deriv exp 'x)))

;; я хотел бы сделать еще приведение подобных в нескольких суммах или произведениях
;; но я истощен. надеюсь так зайдет/сойдет..

;(define-syntax fl
;  (syntax-rules ()
;    ((fl xs)
;     (let loop ((node (xs))
;                (ans '()))
;       (cond ((null? node) ans)
;             ((pair? node) (loop (car node) (loop (cdr node) ans)))
;             (else (cons (curr node) ans)))))))


(define-syntax rev
  (syntax-rules ()
    ((_ () (result ...)) (result ...))
    ((_ (x xs ...) (result ...)) (rev (xs ...) (x result ...)))))

(define-syntax iter
  (syntax-rules ()
    ((_ ((xs ...) ys ...) (result ...))
     (iter (xs ... ys ...) (result ...)))
    ((_ (x xs ...) (result ...))
     (iter (xs ...) (x result ...)))
    ((_ () (result ...))
     (rev (result ...) ()))))

;; документацию искать так.. вкусно

(define-syntax flatten
  (syntax-rules ()
    ((flatten xs) (iter xs ()))))

;(define a 2)
;(define b *)
;(define c 3)
;(a . b .c) -> error
; а в рэкете бы вывел 6. обидно