#PR�MEK-----------------------------------------------------------------------------------------
#https://www.w3resource.com/r-programming-exercises/basic/r-programming-basic-exercise-6.php
primes <- function(n) {
    if (n >= 2) {
        x = seq(2, n)
        prime_nums = c()
        for (i in seq(2, n)) {
            if (any(x == i)) {
                prime_nums = c(prime_nums, i)
                x = c(x[(x %% i) != 0], i)
            }
        }
        return(prime_nums)
    }
    else {
        stop("Input number should be at least 2.")
    }
}


#BRUN------------------------------------------------------------------------------------------
stp <- function(x)
{
    #Az els� x pr�msz�m kisz�mol�sa
    primes = primes(x)
    #A szomsz�dos pr�mek k�l�nbs�g�nek kisz�mol�sa
    diff = primes[2:length(primes)] - primes[1:length(primes) - 1]
    #Azon differenci�k indexe, amelyek 2-k
    idx = which(diff == 2)
    #Azon pr�mek amelyek szomsz�dja +2 t�vols�gra van t�l�k
    t1primes = primes[idx]
    #El�z�k szomsz�djai
    t2primes = primes[idx] + 2
    #A reciprokok �sszege
    rt1plust2 = 1 / t1primes + 1 / t2primes
    #Ezen �sszegek �sszege
    return(sum(rt1plust2))
}



x = seq(13, 100000, by = 10000)
y = sapply(x, FUN = stp)
plot(x, y, type = "b")