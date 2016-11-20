/* 
 * File:   newmain2.c
 * Author: marketka
 *
 * Created on 11. prosinec 2015, 1:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define maxsize 10
/*
 * 
 Úkolem je vytvořit program, který dokáže vyhledávat v zadaných bodových hodnoceních.

Vstupem našeho programu je seznam bodových hodnocení v předmětu PA1. Jedna vstupní hodnota bodů představuje hodnocení jednoho studenta. Následně chceme tato data analyzovat. Tedy chceme zjistit kolik studentů připadá na zadaný interval bodového hodnocení.

Vstupem je nejprve seznam bodových hodnocení. Bodové hodnocení studenta je celé číslo v intervalu 0 až 1000000000 včetně. Bodová hodnocení jsou zadaná ve složených závorkách, jednotlivé hodnoty jsou oddělené právě jednou čárkou. Po zadání bodových hodnocení přicházejí dotazy. Každý dotaz je zadaný jako interval (uzavřený, polootevřený, otevřený), meze intervalu jsou zadané jako celá čísla, čísla jsou oddělená středníkem. Intervalů může být zadaných mnoho, zpracování dotazů pokračuje do konce vstupu (EOF).

Výstupem programu je počet studentů, který dosáhl bodového hodnocení pro každý dotazovaný interval.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

hodnocení studentů není zadané jako celé číslo v intervalu 0 až 1000000000,
hodnocení studentů není ve složených závorkách,
hodnocení studentů nejsou oddělena čárkou,
musí být zadaný alespoň jeden hodnocený student,
dotazovaný interval není zadaný jako otevřený, polootevřený ani jako uzavřený,
meze dotazovaného intervalu nejsou celá čísla (mohou být i záporná),
meze dotazovaného intervalu nejsou oddělené středníkem.
Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Velikost vstupu není explicitně omezena, zadaných hodnocení může být velmi mnoho (milióny). Zároveň je v základním testu velmi omezena velikost dostupné paměti, tedy paměť nelze alokovat staticky. Časové omezení nepředstavuje problém pro povinné testy. Limity v povinných testech jsou velmi benevolentní, počítají s rozumnou implementací naivního algoritmu. Časové omezení se uplatní pro bonusové testy - pro jejich zvládnutí je potřeba použít lepší než naivní algoritmus.


 
 */

void resizeArray( int ** text, int * maxSize )
{int *pom;
 ( *maxSize ) *= 2;
    ( pom ) = ( int * ) realloc( *text, (* maxSize) * sizeof( int ) );
    if (!pom)
    {(*maxSize)=-1;
    free(*text);
    (*text)=NULL;}
    else {(*text)=pom; 
/*
    free(pom);
*/
    }
}
int intCompare ( const void *a, const void *b ) {
return ( *(int*)a - *(int*)b ); 
}
int konec()
{    
    printf("Nespravny vstup.\n");
        
    return 1;

}
int main(int argc, char** argv) {
    char znaky, c, zav1, zav2;
    int *x=NULL; 
    int i=0, pom=maxsize, j=0, k=0;
    int inter=0, pom2, a, b, pom3;
    resizeArray( &x, &pom );
        if (pom==-1) {return 1;}
 
    

   printf("Pocty bodu:\n");
  scanf(" %c", &c);
  
   if (c!='{')
    {konec();
    free(x);
   return 1;}
   while(1)
    {
       if (scanf("%d %c ", &pom2,&znaky)!=2)
       {konec();
    free(x);
       return 1;}
       
        x[i]=pom2;
        i++;
        if (i==(pom-3)) 
       {resizeArray( &x, &pom );
        if (pom==-1) {return 1;}}
        
        
        if (znaky == '}') break;
        
        if (feof (stdin))
            break;
         if (pom>=1000000000||znaky!=','||pom<0)
    {konec();
    free(x);
            return 1;}   
       
     
    }
   if (znaky!='}')
    {konec();
    free(x);
            return 1;}
   qsort( (void*)x, i, sizeof(x[0]), intCompare );
  
 
    printf("Intervaly:\n");
    while(1)
    { 
      znovu:  
    inter=0;
 
    
  pom3=scanf(" %c%d;%d%c",&zav1,&a, &b, &zav2);
  
  if(pom3==EOF)
  {break;}
  else if(pom3!=4)
  {printf("Nespravny vstup.\n");
  __fpurge(stdin);
            goto znovu;}
    if (zav1=='<'&&zav2=='>') 
    {
        for (j=0; j<i; j++) 
        {if (x[j]>=a&&x[j]<=b)
        {break;}}
        for (k=i-1;k>0;k--)
            {if (x[k]<=b&&x[k]>=a)
        {break;}
            
        } 
    }
    else if(zav1=='('&&zav2==')')
    {  for (j=0; j<i; j++) 
        {if (x[j]>a&&x[j]<b)
        {break;}}
        for (k=i-1;k>0;k--)
            {if (x[k]<b&&x[k]>a)
        {break;}
            
        }  }
    else if(zav1=='('&&zav2=='>') 
    { for (j=0; j<i; j++) 
        {if (x[j]>a&&x[j]<=b)
        {break;}}
        for (k=i-1;k>0;k--)
            {if (x[k]<=b&&x[k]>a)
        {break;}
            
        }  }
    else if(zav1=='<'&&zav2==')') 
    {  for (j=0; j<i; j++) 
        {if (x[j]>=a&&x[j]<b)
        {break;}}
        for (k=i-1;k>0;k--)
            {if (x[k]<b&&x[k]>=a)
        {break;}
            
        }  }
    else {printf("Nespravny vstup.\n");
    __fpurge(stdin);
     goto znovu;}
    if (feof (stdin))
     break;  
    if (k==0&&j==i)
    {
    printf(" -> 0\n");
    }
    else{
    inter=k-j+1;
    printf(" -> %d\n",inter);
    }
    
    }
    free(x);
    
  
    return (EXIT_SUCCESS);
}

