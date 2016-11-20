/* 
 * File:   main.c
 * Author: marketka
 *
 * Created on 19. listopad 2015, 21:51
 
 Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude počítat nešťastné pátky 13 v zadaném intervalu dat.

Pátek 13 bývá označován za nešťastný den. Samozřejmě, že je to jen pověra bez racionálního základu, kterou je potřeba zcela ignorovat. Ale přesto není radno podcenit třináctý pátek 13 ve svém životě. Nebo podcenit Progtestovou úlohu zadanou po pátku 13. Zde pomůže požadovaná funkce.

Naše funkce dostane parametrem dvě data - počátek a konec časového intervalu, ve kterém hledáme pátky 13. Počátek i konec je dán rokem, měsícem a dnem. Funkce spočítá, kolik pátků 13 bylo v zadaném intervalu (obě meze počítáme do intervalu, pokud některá mez je pátek 13, bude započtena).

Požadovaná funkce má rozhraní:

int CountFriday13 ( int y1, int m1, int d1, 
                    int y2, int m2, int d2, 
                    long long int * cnt )
y1, m1, d1 jsou vstupní parametry, které představují rok, měsíc a den počátku intervalu,

y2, m2, d2 jsou vstupní parametry, které představují rok, měsíc a den konce intervalu,

cnt je výstupní parametr, do kterého funkce uloží vypočtený počet pátků 13 v zadaném období. Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá tento výstupní parametr beze změn. Vypočtená hodnota zahrnuje i případné pátky 13 v krajních bodech zadaného intervalu.

návratová hodnota funkce bude nastavena na hodnotu 1 pro úspěch (správné vstupní parametry) nebo 0 pro neúspěch (nesprávné vstupní parametry).

Pokud jsou zadané nesprávné vstupní parametry, je potřeba vrátit hodnotu 0 (neúspěch). Správné hodnoty vstupních parametrů musí splňovat:

rok je větší roven 1900,
měsíc je platný (1 až 12),
den je platný (1 až počet dní v měsíci),
zadaný okamžik počátku intervalu nenastane až po zadaném okamžiku konce intervalu.
Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce CountFriday13. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z CountFriday13 volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci CountFriday13 (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů „zmizí“, tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Při výpočtu času uvažujeme Gregoriánský kalendář. Tedy měsíce mají vždy 30 nebo vždy 31 dní, výjimkou je únor, který má 28 dní (nepřestupný rok) nebo 29 dní (přestupný rok). Podle Gregoriánského kalendáře platí:

roky nejsou přestupné,
s výjimkou let dělitelných 4, které jsou přestupné,
s výjimkou let dělitelných 100, které nejsou přestupné,
s výjimkou let dělitelných 400, které jsou přestupné,
s výjimkou let dělitelných 4000, které nejsou přestupné.
Tedy roky 1901, 1902, 1903, 1905, … jsou nepřestupné (pravidlo 1), roky 1904, 1908, …, 1996, 2004, … jsou přestupné (pravidlo 2), roky 1700, 1800, 1900, 2100, … nejsou přestupné (pravidlo 3), roky 1600, 2000, 2400, …, 3600, 4400, … jsou přestupné (pravidlo 4) a roky 4000, 8000, … nejsou přestupné (pravidlo 5).

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující v povinných testech může získat nominálních 100% bodů. Bonusové testy vyžadují časově efektivní výpočet i pro velké intervaly (vysoké roky hodně převyšující 4000).
 
 
 
 */

#ifndef __PROGTEST__ 
#include <stdio.h> 
#include <assert.h> 
#endif /* __PROGTEST__ */ 
int CountDay(int y, int m)
{int Day;
int d=1;
Day=(d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400-y/4000)%7;
/*
by Michael Keith and Tom Crave
*/
return (Day);
}
int CountFriday13 (int y1, int m1, int d1, int y2, int m2, int d2, long long int * cnt) { 
    int i, m;
    long long c=0;
 
  if((y1==y2&&m1==m2&&d1>d2)||(y1==y2&&m1>m2)||y1>y2||
           (y1%4!=0&&m1==2&&d1>28)||((y1%100==0&&y1%400!=0)&&m1==2&&d1>28)||((y1%4000==0)&&m1==2&&d1>28)||
             (y2%4!=0&&m2==2&&d2>28)||((y2%100==0&&y2%400!=0)&&m2==2&&d2>28)||((y2%4000==0)&&m2==2&&d2>28)||
          (m1==1&&d1>31)||(m1==2&&d1>29)||(m1==3&&d1>31)||(m1==4&&d1>30)||(m1==5&&d1>31)||(m1==6&&d1>30)||
          (m1==7&&d1>31)||(m1==8&&d1>31)||(m1==9&&d1>30)||(m1==10&&d1>31)||(m1==11&&d1>30)||(m1==12&&d1>31)||
           (m2==1&&d2>31)||(m2==2&&d2>29)||(m2==3&&d2>31)||(m2==4&&d2>30)||(m2==5&&d2>31)||(m2==6&&d2>30)||
          (m2==7&&d2>31)||(m2==8&&d2>31)||(m2==9&&d2>30)||(m2==10&&d2>31)||(m2==11&&d2>30)||(m2==12&&d2>31)||(m1||m2)<1||(m1||m2)>12||(d1||d2)<1)
  {
  return 0;}
     if ((y1==y2&&m1==m2&&d1>13)||(y1==y2&&m1==m2&&(d1==d2&&d1!=13)))
    {*cnt=0;
    return 1;}
     else if (y1==y2&&m1==m2&&d1<=13&&d2>=13)
    {{if (CountDay(y1,m1)==0)
        c++;}
        *cnt=c;
    return 1;}
     else if(y1==y2)
     {if (d1<=13)
    {if (CountDay(y1,m1)==0)
        c++;}
    m=m1+1;
    do
    {if (CountDay(y1,m)==0)
    { c++;}
    m++;}while(m<m2);
     if (d2>=13)
    {if (CountDay(y1,m2)==0)
        c++;}
    *cnt=c;
     return 1;}
         
    if (d1<=13)
    {if (CountDay(y1,m1)==0)
        c++;}
    m=m1+1;
    do
    {if (CountDay(y1,m)==0)
    { c++;}
    m++;}while(m<13);
    i=y1+1;
while(i<y2)
    {m=1;
       do
       {if (CountDay(i,m)==0)
    { c++;}
    m++;}while(m!=13);
    i++;}         
    m=1;
    while(m<m2)
    {if(CountDay(y2,m)==0)
    {c++;}
    m++;};
    if (d2>=13)
        {if(CountDay(y2,m2)==0)
        c++;}
    *cnt=c;
    return 1;
} 
 
#ifndef __PROGTEST__ 
int main(int argc, char * argv []) { 
    long long int cnt; 
 

  assert ( CountFriday13 ( 1900,  1,  1, 2015,  1,  1, &cnt ) == 1 && cnt == 197LL );
 assert ( CountFriday13 ( 1900,  1,  1, 2015,  2,  1, &cnt ) == 1 && cnt == 197LL );
    assert ( CountFriday13 ( 1900,  1,  1, 2015,  1, 13, &cnt ) == 1 && cnt == 197LL );
    assert ( CountFriday13 ( 1900,  1,  1, 2015,  2, 13, &cnt ) == 1 && cnt == 198LL ); 
    assert ( CountFriday13 ( 1904,  1,  1, 2015,  1,  1, &cnt ) == 1 && cnt == 189LL ); 
    assert ( CountFriday13 ( 1904,  1,  1, 2015,  2,  1, &cnt ) == 1 && cnt == 189LL ); 
    assert ( CountFriday13 ( 1904,  1,  1, 2015,  1, 13, &cnt ) == 1 && cnt == 189LL ); 
    assert ( CountFriday13 ( 1904,  1,  1, 2015,  2, 13, &cnt ) == 1 && cnt == 190LL ); 
    assert ( CountFriday13 ( 1905,  2, 13, 2015,  1,  1, &cnt ) == 1 && cnt == 187LL ); 
    assert ( CountFriday13 ( 1905,  2, 13, 2015,  2,  1, &cnt ) == 1 && cnt == 187LL ); 
    assert ( CountFriday13 ( 1905,  2, 13, 2015,  1, 13, &cnt ) == 1 && cnt == 187LL ); 
    assert ( CountFriday13 ( 1905,  2, 13, 2015,  2, 13, &cnt ) == 1 && cnt == 188LL ); 
    assert ( CountFriday13 ( 1905,  1, 13, 2015,  1,  1, &cnt ) == 1 && cnt == 188LL ); 
    assert ( CountFriday13 ( 1905,  1, 13, 2015,  2,  1, &cnt ) == 1 && cnt == 188LL ); 
    assert ( CountFriday13 ( 1905,  1, 13, 2015,  1, 13, &cnt ) == 1 && cnt == 188LL ); 
  assert ( CountFriday13 ( 1905,  1, 13, 2015,  2, 13, &cnt ) == 1 && cnt == 189LL ); 
    assert ( CountFriday13 ( 2015, 11,  1, 2015, 10,  1, &cnt ) == 0 );
    assert ( CountFriday13 ( 2015, 10, 32, 2015, 11, 10, &cnt ) == 0 ); 
    assert ( CountFriday13 ( 2090,  2, 29, 2090,  2, 29, &cnt ) == 0 ); 
    assert ( CountFriday13 ( 2096,  2, 29, 2096,  2, 29, &cnt ) == 1 && cnt == 0LL ); 
    assert ( CountFriday13 ( 2100,  2, 29, 2100,  2, 29, &cnt ) == 0 ); 
    assert ( CountFriday13 ( 2000,  2, 29, 2000,  2, 29, &cnt ) == 1 && cnt == 0LL ); 
    assert ( CountFriday13 ( 1945, 3, 28, 1945, 5, 2, &cnt ) == 1 && cnt == 1LL );
 assert ( CountFriday13 ( 1900, 3,  1,  1900,  3, 13, &cnt ) == 1 && cnt == 0LL );
 assert ( CountFriday13 ( 1900, 1,  1,  1965,  1, 13, &cnt ) == 1 && cnt == 113LL );
assert ( CountFriday13 ( 1944, 2,  1,  1944,  1, 31, &cnt ) == 0);
assert ( CountFriday13 ( 1900, 3, 1, 1900, 3, 13, &cnt ) == 1 && cnt == 0LL );
assert ( CountFriday13 ( 1900, 3,  1,  1900,  3, 13, &cnt ) == 1 && cnt == 0LL );
assert ( CountFriday13 ( 1900,  1,  1, 1900,  4, 13, &cnt ) == 1 && cnt == 1LL );
assert ( CountFriday13 ( 1900, 1, 1, 1965, 1, 13, &cnt ) == 1 && cnt == 113LL );

return 0; 
} 
#endif /* __PROGTEST__ */
