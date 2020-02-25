#ELÖSZÓ-----------------------------------------------------------------------------------------------------------
#Mi a Monty Hall probléma?
#Van 3 ajtónk amik közül 1-ben nyeremény van, a többiben nincs
#Kiválasztunk 1-et
#Monty Hall ezután kinyit egy ajtót amiben semmi sincs
#Ekkor változtathatunk azon hogy melyik ajtót választjuk
#Megéri-e változtatni?
#
#Intuitívan: Mindegy, mert úgyis 50:50 hogy melyikben van a nyeremény
#Valójában: Megéri váltani
#Miért? https://www.montyhallproblem.com/
#((note #1: hosszú ö-t, ü-t nem írhatok mert nem kezel unicode-ot az R))
#((note #2: én windowson dolgozok, ez a script VS2017 mellett müködik. Ha nem müködik linuxon, akkor úgyis meg tudod oldani magadtól ha már linuxot használsz))


#SETUP------------------------------------------------------------------------------------------------------------
kiserletek_szama = 10000 #Hány esetet vizsgálunk

#sample(x,size,replace) = mintavételezés
#   "x" - miböl veszünk mintát
#   "size" - hány mintát veszünk
#   "replace" - visszatesszük-e a mintát mintavételezés után
nyeremeny = sample(1:3, kiserletek_szama, replace = T) #Minden esetben legeneráljuk hogy hol van a nyeremény (1 és 3 között)
jatekos = sample(1:3, kiserletek_szama, replace = T) #Melyiket választotta a játékos legelsönek
musorvezeto = vector(length = kiserletek_szama) #Melyik ajtót nyitja ki Monty Hall a 2. körben (még nem adunk értéket)


#ESET 1-------------------------------------------------------------------------------------------------------
#Nem változtatunk a választásunkon
for (i in 1:kiserletek_szama) {
    if (nyeremeny[i] == jatekos[i]) #Pont eltaláljuk (1/3 esély)
        {
        #A mibölbe beleírjuk hogy melyik ajtók közül kell nyitnia Montynak
        mibol = setdiff(c(1, 2, 3), nyeremeny[i]) #A setdiff(x,y) halmaz kivonás

    } else #Nem találjuk el (2/3 esély)
        {
        #-II-
        mibol = setdiff(c(1, 2, 3), c(nyeremeny[i], jatekos[i]))

    }

    #Melyiket nyitja Monty?
    musorvezeto[i] = mibol[sample(1:length(mibol), 1)] #Választunk egyet a miböl-böl
}

nemvaltoztatesnyer = which(nyeremeny == jatekos) #Összeszedjük, hány esetben volt az elsö választásunk a nyeremény = helyes


#ESET 2------------------------------------------------------------------------------------------------------
#Változtatunk a választásunkon


#A játékos új, megváltoztatott választása
jatekos_uj = vector(length = kiserletek_szama)

for (i in 1:kiserletek_szama) {
    holvalt = setdiff(c(1, 2, 3), c(musorvezeto[i], jatekos[i])) #fogalmam sincs miért igy van elnevezve ez a változó

    #Itt az eredeti kód kiválaszt egyet az egy-böl:
    #   jatekos_uj[i] = holvalt[sample(1:length(holvalt), 1)] 
    #Ezt azért gondolom hogy lehet egyszerüsíteni, mivel a "musorvezeto" és a "jatekos" mindig különbözni fognak (lásd ELÖSZÓ),
    #ezért a holvalt mindig egy egy elemü "halmaz" lesz.

    jatekos_uj[i] = holvalt
}

valtoztatesnyer = which(nyeremeny == jatekos_uj) #Összeszedjük, hány esetben volt a változtatott választásunk a nyeremény

print("Kisérletek száma:", quote = FALSE)
print(kiserletek_szama)
print("Hányszor nyerünk változtatás nélkül:", quote = FALSE)
print(length(nemvaltoztatesnyer))
print("Hányszor nyerünk változtatással:", quote = FALSE)
print(length(valtoztatesnyer))
print("Nemváltoztatás / Változtatás:", quote = FALSE)
print(length(nemvaltoztatesnyer) / length(valtoztatesnyer))
print("Nemváltoztatás + Változtatás:", quote = FALSE)
print(length(nemvaltoztatesnyer) + length(valtoztatesnyer))
