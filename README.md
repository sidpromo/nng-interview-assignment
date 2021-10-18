# nng-interview-assignment
A feladat azoknak a házszámoknak a kiírása, amelyek duplán szerepelnek.  
Például ha a Kossuth utca az egyik szegmensen a páratlan oldalon szerepel, 43–47-ig, egy másikon 47–49-ig, akkor a 47 duplán van. Ha van 45–59 is, akkor a 45–49 van "duplán", a triplázás nem érdekes.  
A mixed és az odd/even átfedések kezelése tetszőleges, de legyen jó/logikus, a kimenetben nem baj ha külön odd-ként és even-ként jelenik meg egy mixed átfedés.  
Az output legyen ez: [utca neve]: [scheme] [from] [to]  
pl.  
Kossuth utca: O 45 49  
Kossuth utca: E 12 12  
stb.  
  
Az algoritmus legyen külön a betöltéstől, vagyis előbb töltsd be a memóriába az adatot, és azt dolgozd fel. Elég, ha azt a részét, azokat az oszlopokat olvasod be, amelyeken dolgozni fogsz. A megoldás futási ideje ne függjön a házszámok számszerű méretétől, vagyis ugyanannyi idő alatt fusson le akkor is, ha minden számot felszorzunk 100-zal (vagy 101-gyel, hogy a paritás ne változzon).  
  
  
Jó lenne, ha minél önállóbban, minél kevesebb kérdéssel meg tudnád oldani. A betöltést úgy hack-eled össze, ahogy akarod, de az algoritmus részét szeretném megérteni a kódból. C++-t használj konzolalkalmazásként. A bementi file neve "network.mid", a kimenet standard outputra menjen.
