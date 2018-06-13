#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <ctype.h>

#define ROZM 5
#define IPWYGR 4
#define GLEB 3


void siatka(); // funkcja sluzy do wizualizacji siatki
void przeczytajruch(char wnr);  // funkcja sluzy do przeczytania ruchu uzytkownika
int kontrolawygranej(char wnr); // funkcja sluzy do sprawdzenia wystapienia wygranej (w wierszach, kolumnach i na skosie)
int skonczgre(); // funkcja sluzy do sprawdzenia czy wszystkie kratki sa zajete

/* Funkcje dla sztucznej inteligencji */
void move (void);
int zbadajruch (char wnr, int glebokosc);

char kik[ROZM][ROZM];

int main (int argc, char *argv[])
{
    int i,j,gracz,rewanz;
    char symbol, wybor;

    repeat:

    printf("Witamy w grze kolko i krzyzyk! \n\n");
    printf("1) USER VS USERS \n");
    printf("2) USER VS PC \n\n");
    printf("\t Dokonaj wyboru : ");
    wybor = getch();


        /* Inicjalizacja siatki */

        for(i = 0; i<ROZM; i++)
            for(j = 0; j<ROZM; j++)
                kik[i][j] = ' ';

        switch(wybor)
        {
            /* 1 Wybor - 2 gracze */
        case '1':
            for(i=0;;++i)
            {
                /* Jezeli w cyklu liczba i jest parzysta to kolej wypada na X - nieparzysta na O. */
                if(i%2 == 0)
                    symbol ='X';
                else
                    symbol ='O';

                system("cls");
                siatka();
                przeczytajruch(symbol);
                if(kontrolawygranej(symbol))
                {
                    system("cls");
                    siatka();
                    printf("Gracz %c wygral! \n", symbol);
                    break;
                }
                if(skonczgre())
                {
                    system("cls");
                    siatka();
                    printf("Remis! \n");
                    break;
                }
            }
            break; // Wyjscie z case 1.


            /* 2 - Wybor User vs Pc
                Przyjmujemy wartosci :
                1 = gracz
                0 = komputer
             */
        case '2':
            for(i=0;;++i)
            {
               if(i%2==0)
               {
                   gracz = 1;
                   symbol = 'X';
               }
               else
               {
                   gracz = 0;
                   symbol = 'O';
               }

               system("cls");
               siatka();

               if(gracz==1)
                przeczytajruch(symbol);
               else if(gracz==0)
                move();

                if(kontrolawygranej(symbol))
                {
                    system("cls");
                    siatka();
                    if(gracz==1)
                        printf("Wygrales! \n");
                    else if (gracz==0)
                        printf("Komputer wygral!\n");
                    break;
                }
                if(skonczgre())
                {
                    system("cls");
                    siatka();
                    printf("Remis! \n");
                    break;
                }
            }
            break;

        default:
                printf("ERROR : Podany wybor jest niemozliwy!\n");

        }

        system("Pauza");
        system("cls");

        do
        {

            printf("Wcisnij Enter zeby zagrac od nowa. \n");
            printf("Wcisnij ESC zeby wyjsc \n");
            rewanz = getch();

            if(rewanz==13)
            {
                system("cls");
                goto repeat;
            }
            if(rewanz==27)
                return 0;
        }
        while(rewanz!=13 && rewanz != 27);
}


void siatka()
{
    int i,j;

     printf("\n  ");
     for(i=0;i<ROZM;i++)
          printf("  %d", i);
     putchar('\n');

     for(i=0;i<ROZM;i++)
     {
          printf(" %c ", i+65);
          for(j=0;j<ROZM;j++)
               printf("[%1c]",kik[i][j]);
          putchar('\n');
     }
}





void przeczytajruch(char wnr)
{
    /*
        Wczytuje ruch jako wspolrzedne .
        Na przyklad : a1, A1, B2, b2, C5.
        Funkcja dziala poprawnie dla duzych i malych liter.

        W tej funkcji pojawi sie :
        -Ruch X poziomo (numer)
        -Ruch Y pionowo (litera)
    */

    char ruchX, ruchY;

    do
    {
        printf("\nJest kolej : %c, Wpisz ruch ktory chcesz dokonac: ", wnr);
          ruchY = toupper(getch());
          ruchX = getch();
    }
    while(kik[ruchY-65][ruchX-48] != ' ');

    kik[ruchY-65][ruchX-48]=wnr;

}




int kontrolawygranej(char wnr)
{

    register int count,i,j;

    /* Kontrola wierszy */
    for(i=0;i<ROZM; i++)
    {
        count=0;
        for(j=0;j<ROZM;j++)
        {

            if(kik[i][j]==wnr)
            {
            count++;
            if(count==IPWYGR) return 1;
            }
            else
                count=0;
        }
    }

    /* Kontrola kolumn*/

    for(j=0; j<ROZM; j++)
     {
          count=0;
          for(i=0; i<ROZM; i++)
          {
               if(kik[i][j]==wnr)
               {
                    count++;
                    if(count==IPWYGR) return 1;
               }
               else
                    count=0;
          }
     }

     return 0;
}



int skonczgre()
{
    register int i,j;

    for(i=0;i<ROZM;i++)
        for(j=0;j<ROZM;j++)
        if(kik[i][j]==' ') return 0;
    return 1;
}



/* FUNKCJE DLA SZTUCZNEJ INTELIGENCJI */


int zbadajruch(char wnr, int glebokosc)
{
     register int i, j, res, tmp;

        if(kontrolawygranej('O'))
                return INT_MAX;
        if(glebokosc < 0 || skonczgre())
                return 0;
        if(wnr=='X')
        {
                res=1;
                for(i=0;i<ROZM;i++)
                        for(j=0;j<ROZM;j++)
                        {
                                if(kik[i][j]==' ')
                                {
                                        kik[i][j]='X';
                                        if(kontrolawygranej('X'))
                                                if(glebokosc == GLEB)
                                                {
                                                        kik[i][j]=' ';
                                                        return INT_MIN;
                                                }
                                                else
                                                        res-=2;
                                        else if((tmp=zbadajruch('O', glebokosc - 1))<res)
                                                res=tmp;
                                        kik[i][j]=' ';
                                }
                        }
        }
        else
        {
                res=-1;
                for(i=0;i<ROZM;i++)
                        for(j=0;j<ROZM;j++)
                        {
                                if(kik[i][j]==' ')
                                {
                                        kik[i][j]='O';
                                        if(kontrolawygranej('O'))
                                                res+=2;
                                        else if((tmp=zbadajruch('X', glebokosc - 1))>res)
                                                res=tmp;
                                        kik[i][j]=' ';
                                }
                        }
        }
        return res;
}



void move()
{
     int i,j;
     int max=INT_MIN, mi=1, mj=1, t;

     for(i=0;i<ROZM;i++)
          for(j=0;j<ROZM;j++)
               if(kik[i][j]==' ')
               {
                    kik[i][j]='O';
                    t=zbadajruch('X', GLEB);
                    printf("%d\n",t);
                    if(t>=max)
                    {
                         max=t;
                         mi=i;
                         mj=j;
                    }
                    kik[i][j]=' ';
               }
     system("PAUSE");
     kik[mi][mj]='O';
}




