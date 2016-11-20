/* 
 * File:   main.c
 * Author: marketka
 *
 * Created on 17. listopad 2015, 16:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/*

Úkolem je vytvořit program, který bude počítat a zobrazovat počty traťových dílců potřebných pro stavbu trati zadané délky.

Předpokládáme, že výrobce dodává traťové dílce dvou velikostí. Úkolem je určit počty potřebných traťových dílců jednotlivých velikostí, které jsou potřebné pro výstavbu trati zadané délky. Při stavbě trati musíme používat dílce vždy celé (nelze je krátit).

Vstupem programu je zadání délek vyráběných traťových dílců. Jedná se o dvě navzájem různá celá čísla. Po tomto vstupu následuje zadání délky trati ke stavbě. Pro zadanou délku trati program vypočte potřebné množství traťových dílců. Zadání délky je navíc dvojího druhu:

- délka pro toto zadání program zobrazí kolika různými způsoby lze traťové dílce kombinovat, + délka pro toto zadání program vypíše nalezené kombinace a zobrazí jejich počet. Výstupem programu je počet možných způsobů, kterými lze zkombinovat traťové dílce pro zadanou vzdálenost. Podle vstupu (znaku + či - v zadání) se dále zobrazí či nezobrazí i výpis jednotlivých možných kombinací. Přesný formát výstupu je v ukázce níže. Pokud zadanou délku nelze z vyráběných dílců sestavit, program pro zadaný vstup vypíše informaci podle ukázky. Pozor, za výpisem je odřádkování (\n).

Pokud je vstup neplatný, program to musí detekovat, zobrazit chybové hlášení a ukončit se. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

délky vyráběných traťových dílců jsou nečíselné, záporné, nulové nebo jsou obě délky shodné, při zadávání délky nebyl použit ani znak + ani - pro zapnutí/vypnutí úplného výpisu všech kombinací, zadání délky trati je nečíselné nebo záporné. Program v základní verzi pracuje s malými čísly, tedy k vyřešení stačí naivní algoritmus kontrolující přípustné možnosti. Pokud má být zobrazován kompletní výpis všech možných kombinací, nelze algoritmus příliš vylepšovat. Úloha nabízí nepovinný test. V tomto testu se testuje, zda řešení dokáže rychle počítat počty možných kombinací (pracuje pouze v režimu -, tedy bez výpisu všech nalezených kombinací). Pokud nepovinný test zvládnete, dostane řešení 100% bodů. Poud v programu použijete pouze naivní algoritmus, nepovinným testem neprojdete a získáte méně než 100% bodů.

Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte se na videotutoriál (edux → výuková videa), jak testovací data použít a jak testování zautomatizovat.
 * 
 */
int main(int argc, char** argv) {
    long c, x, y, z,d,i,j=0;
    long long b;
    char s;
   printf("Delky koleji:\n");
   if ( scanf("%ld %ld",&x, &y) != 2||x<=0||y<=0||x==y)
   {printf("Nespravny vstup.\n");
   return 0;}
       printf("Vzdalenost:\n");
   if (scanf(" %c %ld", &s, &z)!=2||z<0)
   {printf("Nespravny vstup.\n");
   return 0;}
    i=z/x;
   if (s=='+')
    while (i>=0)
    {
    b=(long long)z-((long long)i*(long long)x);
    d=b%y;
        if (d==0)
        {c=b/y;
              j++;  
              printf("= %ld * %ld + %ld * %ld\n",x,i,y,c);
        };
        i--;}
   else if (s=='-') {
     while (i>=0)
    {
     b=(long long)z-((long long)i*(long long)x);
    d=b%y;
        if (d==0)
        {c=b/y;
              j++;               
        };
        i--;
     }}
   else {printf("Nespravny vstup.\n");
   return 0;}
    if (j==0)
    {printf("Reseni neexistuje.\n");
    return 0;}
    else{
    printf("Celkem variant: %ld\n", j);
    return 0;}
            
    
    
    return (EXIT_SUCCESS);
}

