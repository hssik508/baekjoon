ADD X7, X1, X2
SUB X8, X3, X4
ADDI X9, X0, 3
ADD X10, X5, X6
LOOP:
SUB X9, X9, X1
BEQ X9, X0, FUNC1
ADD X11, X7, X8
SLLI X11, X11, 1
SRL X15, X11, X2
JAL X1, FUNC3
BNE X15, X14, LOOP
FUNC2:
ADD X14, X15, X10
JALR X0, 0(X1)
FUNC1:
SUB X16, X14, X10
ADD X17, X15, X9
ADD X9, X15, X10
SUB X10, X17, X16
BNE X16, X14, FUNC3
BEQ X10, X9, FUNC3