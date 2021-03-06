#EL�SZ�-----------------------------------------------------------------------------------------------------------
#Mi a Monty Hall probl�ma?
#Van 3 ajt�nk amik k�z�l 1-ben nyerem�ny van, a t�bbiben nincs
#Kiv�lasztunk 1-et
#Monty Hall ezut�n kinyit egy ajt�t amiben semmi sincs
#Ekkor v�ltoztathatunk azon hogy melyik ajt�t v�lasztjuk
#Meg�ri-e v�ltoztatni?
#
#Intuit�van: Mindegy, mert �gyis 50:50 hogy melyikben van a nyerem�ny
#Val�j�ban: Meg�ri v�ltani
#Mi�rt? https://www.montyhallproblem.com/
#((note #1: hossz� �-t, �-t nem �rhatok mert nem kezel unicode-ot az R))
#((note #2: �n windowson dolgozok, ez a script VS2017 mellett m�k�dik. Ha nem m�k�dik linuxon, akkor �gyis meg tudod oldani magadt�l ha m�r linuxot haszn�lsz))


#SETUP------------------------------------------------------------------------------------------------------------
kiserletek_szama = 10000 #H�ny esetet vizsg�lunk

#sample(x,size,replace) = mintav�telez�s
#   "x" - mib�l vesz�nk mint�t
#   "size" - h�ny mint�t vesz�nk
#   "replace" - visszatessz�k-e a mint�t mintav�telez�s ut�n
nyeremeny = sample(1:3, kiserletek_szama, replace = T) #Minden esetben legener�ljuk hogy hol van a nyerem�ny (1 �s 3 k�z�tt)
jatekos = sample(1:3, kiserletek_szama, replace = T) #Melyiket v�lasztotta a j�t�kos legels�nek
musorvezeto = vector(length = kiserletek_szama) #Melyik ajt�t nyitja ki Monty Hall a 2. k�rben (m�g nem adunk �rt�ket)


#ESET 1-------------------------------------------------------------------------------------------------------
#Nem v�ltoztatunk a v�laszt�sunkon
for (i in 1:kiserletek_szama) {
    if (nyeremeny[i] == jatekos[i]) #Pont eltal�ljuk (1/3 es�ly)
        {
        #A mib�lbe bele�rjuk hogy melyik ajt�k k�z�l kell nyitnia Montynak
        mibol = setdiff(c(1, 2, 3), nyeremeny[i]) #A setdiff(x,y) halmaz kivon�s

    } else #Nem tal�ljuk el (2/3 es�ly)
        {
        #-II-
        mibol = setdiff(c(1, 2, 3), c(nyeremeny[i], jatekos[i]))

    }

    #Melyiket nyitja Monty?
    musorvezeto[i] = mibol[sample(1:length(mibol), 1)] #V�lasztunk egyet a mib�l-b�l
}

nemvaltoztatesnyer = which(nyeremeny == jatekos) #�sszeszedj�k, h�ny esetben volt az els� v�laszt�sunk a nyerem�ny = helyes


#ESET 2------------------------------------------------------------------------------------------------------
#V�ltoztatunk a v�laszt�sunkon


#A j�t�kos �j, megv�ltoztatott v�laszt�sa
jatekos_uj = vector(length = kiserletek_szama)

for (i in 1:kiserletek_szama) {
    holvalt = setdiff(c(1, 2, 3), c(musorvezeto[i], jatekos[i])) #fogalmam sincs mi�rt igy van elnevezve ez a v�ltoz�

    #Itt az eredeti k�d kiv�laszt egyet az egy-b�l:
    #   jatekos_uj[i] = holvalt[sample(1:length(holvalt), 1)] 
    #Ezt az�rt gondolom hogy lehet egyszer�s�teni, mivel a "musorvezeto" �s a "jatekos" mindig k�l�nb�zni fognak (l�sd EL�SZ�),
    #ez�rt a holvalt mindig egy egy elem� "halmaz" lesz.

    jatekos_uj[i] = holvalt
}

valtoztatesnyer = which(nyeremeny == jatekos_uj) #�sszeszedj�k, h�ny esetben volt a v�ltoztatott v�laszt�sunk a nyerem�ny

print("Kis�rletek sz�ma:", quote = FALSE)
print(kiserletek_szama)
print("H�nyszor nyer�nk v�ltoztat�s n�lk�l:", quote = FALSE)
print(length(nemvaltoztatesnyer))
print("H�nyszor nyer�nk v�ltoztat�ssal:", quote = FALSE)
print(length(valtoztatesnyer))
print("Nemv�ltoztat�s / V�ltoztat�s:", quote = FALSE)
print(length(nemvaltoztatesnyer) / length(valtoztatesnyer))
print("Nemv�ltoztat�s + V�ltoztat�s:", quote = FALSE)
print(length(nemvaltoztatesnyer) + length(valtoztatesnyer))
