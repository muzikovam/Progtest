/* 
 * File:   main.c
 * Author: marketka
 *
 * Created on 3. listopad 2015, 18:49
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 Úkolem je vytvořit program, který bude počítat množství roztoku potřebné pro dosažení zadané koncentrace.

Předpokládáme, že máme k dispozici dva roztoky dané látky, každý roztok má nějakou koncentraci. Pro oba roztoky známe jejich koncentrace a jejich množství. Na vstupu dále dostaneme požadovanou koncentraci a požadované množství výsledného roztoku. Program vypočte, jaké množství roztoku č. 1 a roztoku č. 2 je potřeba smíchat, aby vzniklo zadané množství roztoku o cílové koncentraci.

Vstupem programu je zadání parametrů celkem 3 roztoků:

roztok č. 1,
roztok č. 2 a
výsledný roztok.
Každý roztok je určen svým množstvím a koncentrací. Množství i koncentrace jsou desetinná čísla.

Výstupem programu je informace o množství roztoku č. 1 a roztoku č. 2, které je potřeba smíchat, aby vzniklo požadované množství roztoku o zadané cílové koncentraci. Pokud nelze připravit požadované množství cílového roztoku v zadané koncentraci, zobrazí program informaci o nemožnosti vytvoření požadovaného cílového roztoku. V obou případech program zobrazí výsledek výpočtu ve formátu podle ukázky níže. Pozor, za výpisem je odřádkování (\n).

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

nečíselné zadání množství nebo koncentrace,
záporné množství,
koncentrace mimo interval 0.0 až 1.0.
 
 */

double m1 (double x, double y, double z)
{
    
  if (z==y&&z==x) return x;
  else if ((x==y&&x!=z)||(x==z&&x!=y)) return -1;
  else return (z-y)/(x-y);
}
double m2 (double x, double y, double z)
{
    
  if (z==y && z==x) return y;
  else if ((x==y&&x!=z)||(y==z&&x!=y)) return -1;
  else return (z-x)/(y-x);
}


int main(void) {
    
    double x, z, y, c, a, b; 
  
   printf("Hmotnost a koncentrace #1:\n");
   if ( scanf ( "%lf %lf", &a,&x ) != 2 ||a<0||x<0||x>1)
    {printf ( "Nespravny vstup.\n" );
      return 0;}
     printf("Hmotnost a koncentrace #2:\n");
     if ( scanf ( "%lf %lf", &b,&y ) != 2 ||b<0||y<0||y>1)
    {printf ( "Nespravny vstup.\n" );
      return 0;}
  printf("Hmotnost a koncentrace vysledku:\n");
     if ( scanf ( "%lf %lf", &c,&z ) != 2 ||c<0||z<0||z>1)
    {printf ( "Nespravny vstup.\n" );
      return 0;}
  if((c>a+b||m1(x, y, z)<0||m2(x, y, z)<0||(float)(m1(x, y, z)*c)>a||(float)(m2(x,y, z)*c)>b)&&c!=0)
  {printf("Nelze dosahnout.\n");
  return 0;}
  else if (c==0)
  {printf("%f x #1 + %f x #2\n", 0.000000,0.000000);
  return 0;}
   else if (m1(x, y, z)==x || m2(x, y, z)==y)
   {
       if (a<=c){
 printf("%f x #1 + %f x #2\n", a, c-a);
       return 0;}
   else{
           printf("%f x #1 + %f x #2\n",c , 0.000000);
           return 0;}
}
 else
 {printf("%f x #1 + %f x #2\n", m1(x, y, z)*c, m2(x, y, z)*c);
  return 0;}
 
     return (EXIT_SUCCESS);
}

