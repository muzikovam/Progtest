/* 
 * File:   main.c
 * Author: marketka
 *
 * Created on 18. prosinec 2015, 22:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>
#define MAXT 1100
#define maxsize 10
/*
 * 
 
 Úkolem je vytvořit program, který bude zobrazovat nápovědu při zadání vyhledávaného výrazu.

Chceme realizovat program, který bude implementovat část funkcionality našeptávání - autocomplete. Program si pamatuje seznam často zadávaných frází. Pro každou frázi si pamatujeme její četnost. Chceme realizovat program, který načte seznam často zadávaných frází a následně bude schopen v tomto seznamu vyhledávat pravděpodobné fráze na základě zadání jejich částí.

Vstupem programu je seznam často zadávaných frází. Tyto fráze jsou zadané v podobě:

číslo:text fráze kde číslo je četnost dotazu (desetinné číslo) a text fráze je řetězec. Často hledaných frází je dopředu neznámý počet, jejich zadávání končí zadáním prázdného řádku. Po zadání často vyhledávaných frází následuje vlastní vyhodnocování našeptávání. Na řádce vstupu je zadaný text dotazu, tento text tvoří frázi nebo její část. Texty dotazu jsou zadávané na jednotlivých řádkách, jejich zpracování skončí po dosažení konce vstupu (EOF). Výstupem programu je počet frází, které vyhoví zadanému textu dotazu. Text dotazu se může ve frázi vyskytovat kdekoliv (nemusí být na začátku), při porovnávání nerozlišujeme malá a velká písmena. Za výpisem počtu vyhovujících frází následuje jejich výpis v pořadí klesající četnosti. Zobrazeno bude nejvýše 50 frází s nejvyšší četností. Tento výstup bude zobrazen pro každý text dotazu na vstupu.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

u zadávané fráze není uvedena četnost nebo četnost není desetinné číslo, chybí dvojtečka oddělující četnost a frázi, byl zadán nulový počet frází. Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení). V povinných testech jsou zadávané rozumné dotazy (frází je málo). Pro zvládnutí povinných testů postačuje rozumná implementace naivního algoritmu. Úloha nabízí bonusový test, kde je objem zpracovávaných dat velký (fráze jsou dlouhé, je jich mnoho). Pro zvládnutí bonusového testu je potřeba použít lepší algoritmu, který dokáže rychle eliminovat neperspektivní fráze.


 */
typedef struct {
char text[MAXT];
double pocet;
} AUTOC;
int textCompare ( AUTOC *a, AUTOC *b ) {
double x = a->pocet - b->pocet;
return x > 0.0 ? 1 : x < 0.0 ? -1 : 0;
}
void sortText (AUTOC a[], int n ) {
qsort ( (void*)a, n, sizeof(a[0]),
(int(*) (const void *, const void *)) textCompare );
}



void resizeArray( AUTOC ** text, int *maxSize )
{AUTOC *pom;

  (*maxSize ) *= 2;
    ( pom ) = ( AUTOC * ) realloc( *text, (*maxSize) * sizeof(AUTOC) );
    if (!pom)
    {(*maxSize)=-1;
   
    free(*text);
    (*text)=NULL;}
    else {(*text)=pom; 

    }
}
int compare       ( char * s1, char * s2, int len )
 {
   while ( len -- )
    if ( toupper ( *s1 ) != toupper ( *s2 ) )
      return ( 0 );
     else
      {
        s1++;
        s2++;
      }
   return ( 1 );
 }
char * strcasestr ( char * pattern, char * text )
 {
   int patternLen = strlen ( pattern );

   while ( * text )
    {
      if ( compare ( text, pattern, patternLen ) ) return ( text );
      text ++;
    }
   return ( NULL );
 }
void  removeLF    ( char * x )
 {
   int l = strlen ( x );
   if ( l > 0 && x[l-1] == '\n' ) x[l-1] = 0;
 }
int main(int argc, char** argv) {
    AUTOC *pole=NULL;
    char pattern[MAXT];
    int i=0, j=0, count; 
    double poc;
    int max=maxsize;
    
    char *where;
    unsigned char ch;
    resizeArray( &pole, &max );
        if (max==-1) {return 1;}
    
/*
     pole = (char *)malloc(bufsize * sizeof(char));
*/
    
    printf("Casto hledane fraze:\n");
    ch=fgetc(stdin);
        if(ch=='\n')       
       {printf("Nespravny vstup.\n");
       free(pole);
        return 1;}
    
        ungetc(ch,stdin);
    while(1)
    {
        ch=fgetc(stdin);
        if(ch=='\n') break;
        if(ch==EOF)
       {printf("Nespravny vstup.\n");
       free(pole);
        return 1;}
        ungetc(ch,stdin);
        if (scanf("%lf%c",&poc,&ch)!=2)
        {printf("Nespravny vstup.\n");
        free(pole);
        return 1;}
        if (ch!=':')
             {printf("Nespravny vstup.\n");
        free(pole);
        return 1;}
        pole[i].pocet=poc;
         ch=fgetc(stdin);
        if(ch=='\n') break;
        if(ch==EOF)
       {printf("Nespravny vstup.\n");
       free(pole);
        return 1;}
        ungetc(ch,stdin);
        fgets(pole[i].text,sizeof(pole[i].text),stdin);
         removeLF(pole[i].text);
        if (i==max-3)
        {resizeArray(&pole,&max);
        if (max==-1) {return 1;}}
        
        i++;
    }
   
    sortText(pole, i);
    
   
/*
     printf("%f %s\n",pole[j].pocet, pole[j].text);
    scanf("%c",&c);
    
*/
/*for (j=0;j<i;j++)
 * {
    printf("%f %s\n",pole[j].pocet, pole[j].text);
   
 * }
*/
    printf("Hledani:\n");
    while(1)
    {
/*
           if(ch=='\n')       
       {printf("Nespravny vstup.\n");
        __fpurge(stdin);
     goto znovu;}
        ungetc(ch,stdin);
*/
        fgets ( pattern, sizeof ( pattern ), stdin ) ;
   
    removeLF(pattern);
/*
    strstr(pole[j].text,pattern);
*/
    if (feof(stdin)) break;
    count=0;
    for (j=0;j<i;j++)
    {
     where = strcasestr ( pattern, pole[j].text );
      if ( where )
        {
          count++;
              }
      
    }

    
            
    printf("Nalezeno: %d\n",count);
    for (j=i;j>=0;j--)
    { where = strcasestr ( pattern, pole[j].text);
      if ( where )
        {
          printf ( "> %s\n",pole[j].text) ;
              }
       
    }
     
}   
/*
    for(j=0;j<i+1;j++)
    {free(pole[j].text);}
*/
    
        free(pole);        
    return (EXIT_SUCCESS);
}

