#timelib.c

1. convertUnixTimestampToTime() - aici nu e mare lucru, mod-uri și div-uri pentru a salva restul de secunde, minute și ore
2. convertUnixTimestampToDateWithoutLeapYears() - am sărit peste secunde, minute și ore, după am folosit acelaș principiu, am extras numărul de ani, după din zilele rămase am extras lunile una câte una scăzând la fiecare pas zilele lor din timestamp până numărul zilelor nu era mai mare ca luna curentă
3. convertUnixTimestampToDate() - acelaș principiu, doar că am implementat funcționalitatea pentru a verifica și anii bisecți
4. convertUnixTimestampToDateTimeTZ() - pentru a ușura sortarea datelor în ordine cronologică am adăugat din start la timestamp diferența UTC, apoi am folosit funcțiile implementate anterior pentru a calcula data
5. convertDateTimeTZToUnixTimestamp() - merge pe acelaș principiu ca la funcțiile anterioare, singura diferență semnificativă e că aici adaug la un timestamp valorite de timp în loc să le scad
6. printDateTimeTZ() - un simplu printf cu toate elementele convertUnixTimestampToDate


#bitpacking.c

1. TASK 7(BasicNetworkPacking()) - nu e mare lucru, citește câte o dată și o trece direct prin mască pentru a selecta doar cei 15 biți de care avem nevoie, după folosim funcția SortAndPrintDates() care sortează datele, selectează tot prin măști numărul de biți pentru zi, lună, an, după care le afișează
2. TASK 8(ComplexNetworkPacking()) - se citește mai întâi numărul de date care trebuie salvate, după currentDataPack care reprezintă unsigned int-ul de 32 de biți. Pentru fiecare dată se citesc pe rând câte 15 biți din currentDataPack, verificând fiecare bit (currentBit are valori între 0 și 31 e folosit la mască) și dacă are valoarea 1, se adaugă în date[index] și se mărește count - variabila care numără biții cu valoarea 1. Când currentBit depășește 32, însă încă nu am citit toate datele, se citește un currentDataPack nou, se resetează currentBit la 0, se salvează bitul de control pentru rândul curent și se resetează count la 0. Dacă am citit toate datele, însă au mai rămas biți neverificați în currentDataPack, atunci îi verificăm pe restul pentru a putea salva bitul de control.
În continuare am calculat o relație de recurență, la început verificăm numărul rândului dacă e divizibil cu 32, atunci citim o nnouă cifră de control. Variabila index reprezintă indexul datelor, ea începe de la 0 se verifică în perechi câte 3 (ex. rândul 0 are date 0, 1, 2; rândul 1 are datele 2, 3, 4; rândul 2 are datele 4, 5, 6 ș.a.m.d). Se verifică pe rând fiecare control_bit și ultimul bit din currentDataPack, dacă acestea sunt diferite atunci toată perechea de cele 3 numere sunt corupte și valoarea lor devine 0 (date[index] = date[index + 1] = date[index + 2] = 0). La fiecare iterație indexul datelor crește din 2 în 2, iar currentDataPack face shift dreapta cu 1 bit. 2 cazuri particulare sunt atunci când indexul rândului curent % 32 este egal cu 14, acesta este echivalent cu situația cânt într-un unsigned int nu vom avea 3 date, ci 4 ( pe 32 de biți datele vor arăta  1 - 15 - 15 - 1), în acest caz dacă rândul e corupt trebuie să modificăm și valoarea lui date[index + 3] la 0. Dacă index % 32 = 14 sau 29, acestea sunt cazurile de trecere directă când indexul își schimbă paritatea și el trebuie incrementat în plus cu 1.
Aici am reprezentat prima recurență, pe baza căreia am făcut algoritmul:

[row]|[index][index + 1][index + 2][index + 3]
[0]   [0]    [1]        [2]
[1]   [2]    [3]        [4]
[2]   [4]    [5]        [6]
[3]   [6]    [7]        [8]
[4]   [8]    [9]        [10]
[5]   [10]   [11]       [12]
[6]   [12]   [13]       [14]
[7]   [14]   [15]       [16]       [17]
[8]   [17]   [18]       [19]
[10]  [19]   [20]       [21]
[11]  [21]   [22]       [23]
[12]  [23]   [24]       [25]
[13]  [25]   [26]       [27]
[15]  [27]   [28]       [29]
[16]  [29]   [30]       [31]
[17]  [32]   [33]       [34]


Indexul 32 este echivalent cu indexul 0 ca poziție a dății în currentDataPack-ul lor respectiv.
Această relație funcționează pentru tot restul cazurilor, ea repetându-se din 32 în 32.

După ce am verificat doate datele folosim SortAndPrintDates() să le sortăm și afișăm.

#planner.c

1. Citesc numărul de timezone-uri, după care numele fiecărui timezone și utc_difference-ul într-o listă de tip TTimezone.
2. Citesc numărul de persoane și aloc memorie pentru lista de persoane.
3. Pentru fiecare persoană citesc datele ei respective (nume, timezone, numarul de intervale, ....), aloc memoria pentru lista de intervale și timezone-ul din data pack.
4. Citesc pentru fiecare persoană fiecare interval sub formă de dată, după care o transform în timestamp ca să pot lucra cu ea mai ușor. În persons[idx] adaug datele intervalului cu numărul i, timpul de start și timpul de end. Totodată verific și salvez cea mai mică dată și cea mai mare dintre toate intervalele ca să știm în ce domeniu căutăm.
5.Citesc numărul minim de persoane și durata minimă pentru ca evenimentul să se poată organiza.
6. Se caută eventStartDate cu ajutorul funcției findEventDate(). Am folosit un algoritm de tip Window Sliding, încep de la cea mai mică dată și verific câte o fereastră de lungimea evenimentului. Dat fiind că persoanele trebuie să fie prezente pe toată perioada evenimentului, am folosit un array hours care reprezintă orele necesare pentru eveniment. Pentru fiecare persoană se parcurg intervalele și notează orele când persoana este liberă. Array-ul m-a ajutat și pentru cazurile de tip 20 - 21 și 21 - 22, care îmi creau probleme. După ce au fost parcurse toate intervalele se verifică dacă toate orele sunt libere pentru persoana dată. Dacă da, atunci produsul coverAllEvent va fi 1 și persoana va fi adăugată la counter. Dacă numărul de persoane este mai mare sau egal cu numărul minim, se returnează timestampul care reprezintă timpul de start al eventului.
7. Se sortează alfabetic persoanele și se parcurge fiecare dintre ele, verificându-se dacă ea este liberă pentru eveniment. Dacă da, se afișează data, dacă nu se afișează invalid. Dacă nu a fost găsită o dată la pasul precedent se va afișa imposibil.
8. Se eliberează memoria alocată.