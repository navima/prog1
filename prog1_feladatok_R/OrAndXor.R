#   Copyright (C) 2019  Dr. Norbert Bátfai, nbatfai@gmail.com
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# https://youtu.be/Koyw6IH5ScQ

library(neuralnet)

#OR----
#setting up training set (truth table)
a1 <- c(0, 1, 0, 1)
a2 <- c(0, 0, 1, 1)
OR <- c(0, 1, 1, 1)

or.data <- data.frame(a1, a2, OR)

#training up neural network
nn.or <- neuralnet(OR ~ a1 + a2, or.data, hidden = 0, linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

#plot
plot(nn.or)

#see deviation from training set
compute(nn.or, or.data[, 1:2])

#compute arbitrary stuff to see if training was successful
asd1 <- c(1, 0, 0, 1)
asd2 <- c(0, 0, 0, 0)

asdData <- data.frame(asd1,asd2)


#ORAND----
#setting up training set
a1 <- c(0, 1, 0, 1)
a2 <- c(0, 0, 1, 1)
OR <- c(0, 1, 1, 1)
AND <- c(0, 0, 0, 1)

orand.data <- data.frame(a1, a2, OR, AND)

#train neural network
nn.orand <- neuralnet(OR + AND ~ a1 + a2, orand.data, hidden = 0, linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

#plot
plot(nn.orand)

#test Training
compute(nn.orand, orand.data[, 1:2])

#test Arbitrary
b1 <- c(0, 1, 1, 0)
b2 <- c(0, 0, 1, 1)

bData <- data.frame(b1,b2)

compute(nn.orand, bData)


#XOR - No hidden neurons----
a1 <- c(0, 1, 0, 1)
a2 <- c(0, 0, 1, 1)
EXOR <- c(0, 1, 1, 0)

exor.data <- data.frame(a1, a2, EXOR)

nn.exor <- neuralnet(EXOR ~ a1 + a2, exor.data, hidden = 0, linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

plot(nn.exor)

compute(nn.exor, exor.data[, 1:2])


#XOR - 3----
nn.exor <- neuralnet(EXOR ~ a1 + a2, exor.data, hidden = c(3), linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

plot(nn.exor)

compute(nn.exor, exor.data[, 1:2])



#XOR - 4----
nn.exor <- neuralnet(EXOR ~ a1 + a2, exor.data, hidden = c(4), linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

plot(nn.exor)

compute(nn.exor, exor.data[, 1:2])


#XOR - 6,4,6----
nn.exor <- neuralnet(EXOR ~ a1 + a2, exor.data, hidden = c(6, 4, 6), linear.output = FALSE, stepmax = 1e+07, threshold = 0.000001)

plot(nn.exor)

compute(nn.exor, exor.data[, 1:2])
