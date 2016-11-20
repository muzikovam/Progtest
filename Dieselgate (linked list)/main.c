#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LIST_BY_YEAR       0
#define LIST_BY_TYPE       1

#define TYPE_MAX           100
#define SETUP_MAX          100
/*

Úkolem je realizovat funkce (ne celý program, pouze funkce), které dokáží spravovat archiv s nastavením řídící jednotky spalovacího motoru.

V aféře „dieselgate“ vystupuje jako důležitý důkaz nastavení řídící jednotky motoru. Nastavení se liší podle typu motoru a roku výroby. Vlastní nastavení pak tvoří sada čísel, která je hlavně velmi tajná (a pro implementaci tohoto úkolu ani nebude zase tak důležitá). Vaším úkolem je realizovat sadu funkcí, které dokáži s takovými nastaveními pracovat.

Nastavení chceme ukládat v podobě spojových seznamů - viz obrázek. Struktura TARCHIVE tvoří spojový seznam (ukazatel m_Next odkazuje na další prvek v seznamu), odbočky (m_Engines) pak odkazují na spojové struktury s popisem jednotlivých motorů. Celý archiv je organizovaný jedním z následujících způsobů:

LIST_BY_YEAR - odbočky m_Engines odkazují na spojový seznam popisující motory vyráběné ve stejném roce. Spojový seznam TARCHIVE je řazen vzestupně podle roku. Každý spojový seznam TENGINE je pak řazen vzestupně podle typu motoru.
LIST_BY_TYPE - odbočky m_Engines odkazují na spojový seznam popisující motory stejného typu. Spojový seznam TARCHIVE je řazen je vzestupně podle typu. Každý spojový seznam TENGINE je pak řazen vzestupně podle roku.
TENGINE

struktura popisuje jeden motor. Složka m_Year udává rok, složka m_Type je typ motoru (ASCIIZ řetězec). Složka m_Next je odkazem na další motor ve stejné kategorii nebo má hodnotu NULL pro poslední prvek spojového seznamu. Složka m_Setup je vyplněna informacemi o nastavení řídící jednotky. Vaše implementace tuto složku nepotřebuje, proto do ní nebude nijak zasahovat. Vzhledem k tajnému charakteru nastavení je dokonce zakázáno čtení a kopírování (tedy je potřeba pracovat s existujícími strukturami TENGINE a nevytvářet nové).

TARCHIVE

je pomocná struktura propojující seznamy TENGINE. Složka m_Next odkazuje na další prvek TARCHIVE (NULL pro poslední v seznamu), složka m_Engines obsahuje ukazatel na spojový seznam motorů se stejnou charakteristikou (typ/rok).

AddEngine(list, listby, engine)

dostane v parametru list odkaz na existující archiv nastavení řídících jednotek. Jejím úkolem je zařadit nový motor. Odkaz na dynamicky alokovanou strukturu s vyplněnými údaji o motoru je předaný v parameteru engine. Parametr listby má hodnotu LIST_BY_YEAR / LIST_BY_TYPE a udává, způsob organizace archivu (viz výše). Funkce použije alokovanou strukturu motoru a začlení ji do existujícího archivu. Je zakázáno strukturu kopírovat, je potřeba pouze správně proházet odkazy. Funkce vrátí ukazatel na na první prvek v archivu po provedení změny.

DelArchive(list)

funkce uvolní dynamicky alokovanou paměť, kterou používaly struktury v existujícím archivu list.

ReorderArchive(list, listBy)

funkce změní uspořádání existujícího archivu list tak, aby odpovídalo uspořádání listBy (LIST_BY_YEAR / LIST_BY_TYPE). Funkce musí zachovat existující struktury TENGINE (pouze přehazuje odkazy), může podle potřeby alokovat a uvolňovat struktury TARCHIVE. Návratovou hodnotou funkce je ukazatel na první prvek archivu po provedení úprav.

Odevzdávejte zdrojový soubor, který obsahuje implementaci požadovaných funkcí AddEngine, DelArchive a ReorderArchive. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z nich volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z přiloženého archivu. V kódu chybí vyplnit těla funkcí a případné další podpůrné funkce. Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů, deklarace struktur a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů „zmizí“, tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Očekává se základní řešení, úloha má cvičit práci se spojovými seznamy.


*/



typedef struct TEngine
 {
   struct TEngine * m_Next;
   int              m_Year;
   char             m_Type  [ TYPE_MAX ];
   int              m_Setup [ SETUP_MAX ];
 } TENGINE;

typedef struct TArchive
 {
   struct TArchive * m_Next;
   TENGINE         * m_Engines;
 } TARCHIVE;

TENGINE * createEngine  ( const char      * type,
                          int               year )
 {
   int i;
   TENGINE * res = (TENGINE *) malloc ( sizeof  (*res ) );

   res -> m_Next = NULL;
   res -> m_Year = year;
   strncpy ( res -> m_Type, type, sizeof ( res -> m_Type ) );
   for ( i = 0; i < SETUP_MAX; i ++ )
    res -> m_Setup[i] = 0;
   return res;
 }


#endif /* __PROGTEST__ */

TARCHIVE *createList(void)
{
TARCHIVE *list =(TARCHIVE *)malloc(sizeof(*list));
if (!list) return 0;
list->m_Next=NULL;
list->m_Engines=NULL;
return list;
}

TARCHIVE         * AddEngine( TARCHIVE  * list, int listBy,TENGINE   * engine )
 { TENGINE *cur=NULL, *cur3=NULL;
 TARCHIVE *cur2=NULL, *tmpAn=NULL;
 int cmp=0;

    if (!list) 
    {list=createList();
list->m_Engines = engine;
return list;
   }
    if (listBy==0)
/* 0 =year*/
    {for (cur2 = list;; cur2 = cur2->m_Next)
    {
        if (cur2->m_Engines->m_Year == engine->m_Year)
          {  cur3=cur2->m_Engines;
          for (cur = cur2->m_Engines;; cur = cur->m_Next) 
    {cmp=strcmp(cur->m_Type,engine->m_Type);
             if (cmp==0)
        { engine->m_Next = cur->m_Next;
            cur->m_Next = engine;
            return list;} 
           
             if (cmp > 0)
        {
              if ((cur->m_Next==NULL&&cur2->m_Engines->m_Next==NULL)||cur3==cur) 
              {engine->m_Next = cur;
            cur = engine;
            cur2->m_Engines=cur;
            return list;}
              else
              {engine->m_Next = cur;
            cur = engine;
            cur3->m_Next=cur;
            return list;}

            
        }
            if (cur->m_Next==NULL)
                { engine->m_Next = cur->m_Next;
            cur->m_Next = engine;
            return list;} 
    cur3=cur;
        }
          }
    
        if (cur2->m_Engines->m_Year > engine->m_Year)
        {
            tmpAn=createList();
             
           
            tmpAn->m_Next= cur2->m_Next;
            cur2->m_Next= tmpAn;
            
            cur2->m_Next->m_Engines=cur2->m_Engines;
            cur2->m_Engines = engine;
            
            return list;
         
        
            
        }
        if (!cur2->m_Next)
        {
        tmpAn=createList();
            cur2->m_Next= tmpAn;
            
            cur2->m_Next->m_Engines=engine;
            
            return list;
        }
        
    }}
        
        
    
    else if (listBy==1)
    {for (cur2 = list;; cur2 = cur2->m_Next)
    {cmp=strcmp(cur2->m_Engines->m_Type,engine->m_Type);
        if (cmp == 0)
        {  for (cur = cur2->m_Engines;; cur = cur->m_Next) 
    {
             if (cur->m_Year == engine->m_Year)
        { engine->m_Next = cur->m_Next;
            cur->m_Next = engine;
            return list;} 
             if (cur->m_Year > engine->m_Year)
        {
               
            
            engine->m_Next = cur;
            cur = engine;
            cur2->m_Engines=cur;
            return list;
            
        }
            if (cur->m_Next==NULL)
                { engine->m_Next = cur->m_Next;
            cur->m_Next = engine;
            return list;} 
      
        }
          }
    
        if (cmp > 0)
        {
            tmpAn=createList();
           
            tmpAn->m_Next= cur2->m_Next;
            cur2->m_Next= tmpAn;
            cur2->m_Next->m_Engines=cur2->m_Engines;
            cur2->m_Engines = engine;
           
            return list;
         
        
            
        }
        if (!cur2->m_Next)
        {
            tmpAn=createList();
            cur2->m_Next= tmpAn;
            
            cur2->m_Next->m_Engines=engine;
/*
            cur2->m_Next->m_Next=NULL;
*/
            return list;
         
        
            
        }
    }}
    else return 0;
}
void                    DelArchive ( TARCHIVE  * list )
 { TARCHIVE * akt,*stara;
 TENGINE *akt2, *stara2;
 if (list==NULL) goto bla; 
 akt=list->m_Next;
 akt2=list->m_Engines;
 while(akt2!=0)
 {stara2=akt2;
 akt2=akt2->m_Next;
 free(stara2);}
 
 while(akt!=0)
 {akt2=akt->m_Engines;
 while(akt2!=0)
 {stara2=akt2;
 akt2=akt2->m_Next;
 free(stara2);}
 akt=akt->m_Next;
 }
 akt=list->m_Next;
  while(akt!=0)
  {stara=akt;
  akt=akt->m_Next;
  free(stara);
  }
 free(list);
 bla:;
      
}
TARCHIVE         * ReorderArchive    ( TARCHIVE   * list, int  listBy )
 { TARCHIVE *list2=NULL, *cur2=NULL;
 TENGINE *cur=NULL, *tmp=NULL;
 if (list==NULL) return list;   
 if (listBy==0)
    {cur2 = list;
        while(cur2)
        
        {
            cur = cur2->m_Engines;
            cur2 = cur2->m_Next;
            while(cur)
            
    {tmp=cur;
    
    cur = cur->m_Next;
    tmp->m_Next=NULL;
        list2=AddEngine(list2,LIST_BY_YEAR,tmp);
        
            }
    
        }
    while (list)
    { TARCHIVE * p = list->m_Next;
free ( list );
list = p;}
       
    return list2;
    }
    else if (listBy==1)
    {cur2 = list;
        while(cur2)
        
        {
            cur = cur2->m_Engines;
            cur2 = cur2->m_Next;
            while(cur)
            
    {tmp=cur;
    
    cur = cur->m_Next;
    tmp->m_Next=NULL;
        list2=AddEngine(list2,LIST_BY_TYPE,tmp);
        
            }
    
        }
  while (list)
    { TARCHIVE * p = list->m_Next;
free ( list );
list = p;}
    return list2;
    }
    else return 0;
    




}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   TARCHIVE * a;


   a = NULL;
   a = AddEngine ( a, LIST_BY_YEAR, createEngine ( "TDI 1.9", 2010 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_YEAR, createEngine ( "TDI 1.9", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_YEAR, createEngine ( "TSI 1.2", 2010 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_YEAR, createEngine ( "TDI 2.0", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 2.0" )
            && a -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_YEAR, createEngine ( "MPI 1.4", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "MPI 1.4" )
            && a -> m_Engines -> m_Next -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Next -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Next -> m_Type, "TDI 2.0" )
            && a -> m_Engines -> m_Next -> m_Next -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   a = ReorderArchive ( a, LIST_BY_TYPE );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "MPI 1.4" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Next -> m_Engines -> m_Type, "TDI 2.0" )
            && a -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
   DelArchive ( a );

   a = NULL;
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "TDI 1.9", 2010 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "TDI 1.9", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "TSI 1.2", 2010 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "TDI 2.0", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 2.0" )
            && a -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Next -> m_Engines -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "MPI 1.4", 2005 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "MPI 1.4" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Next -> m_Engines -> m_Type, "TDI 2.0" )
            && a -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
   a = AddEngine ( a, LIST_BY_TYPE, createEngine ( "TDI 1.9", 2010 ) );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "MPI 1.4" )
            && a -> m_Engines -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Next -> m_Next -> m_Engines -> m_Type, "TDI 2.0" )
            && a -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next
            && a -> m_Next -> m_Next -> m_Next -> m_Engines
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Next -> m_Next -> m_Engines -> m_Next == NULL
            && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
   a = ReorderArchive ( a, LIST_BY_YEAR );
   assert ( a
            && a -> m_Engines
            && a -> m_Engines -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Type, "MPI 1.4" )
            && a -> m_Engines -> m_Next -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Engines -> m_Next -> m_Next -> m_Year == 2005
            && ! strcmp ( a -> m_Engines -> m_Next -> m_Next -> m_Type, "TDI 2.0" )
            && a -> m_Engines -> m_Next -> m_Next -> m_Next == NULL
            && a -> m_Next
            && a -> m_Next -> m_Engines
            && a -> m_Next -> m_Engines -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Type, "TDI 1.9" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Year == 2010
            && ! strcmp ( a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Type, "TSI 1.2" )
            && a -> m_Next -> m_Engines -> m_Next -> m_Next -> m_Next == NULL
            && a -> m_Next -> m_Next == NULL );
   DelArchive ( a );


   return 0;
 }
#endif /* __PROGTEST__ */
