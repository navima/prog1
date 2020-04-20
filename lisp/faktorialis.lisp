(write-line "Hello World")

(defun recursive (x) 
    (if ( <= x 1)
        1
        (* x ( recursive ( - x 1)))))
        
(defun factorial(n)
    (let ((f 1))
        (dotimes (i n)
            (setf f (* f (+ i 1))))
        f
    )
)
        
(write-line (write-to-string (recursive 10)))
(write-line (write-to-string (factorial 10)))