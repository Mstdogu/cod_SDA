#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"computer.h"

int main()
{
    Computer *C = NULL, *B = NULL, a = {0};
    char model[20], fname[50];
    int n = 0, nm, f, k, i, j;

    while(1)
    {
        puts("\t MENIU:");
        puts("1.  Alocarea dinamica a memoriei pentru tablou");
        puts("2.  Introducerea informatiei despre elemente de la tastatura");
        puts("3.  Afisarea informatiei despre elemente la ecran");
        puts("4.  Cautarea elementului in tablou (dupa model)");
        puts("5.  Modificarea campurilor unui element din tablou");
        puts("6.  Interschimbarea a doua elemente indicate din tablou");
        puts("7.  Sortarea tabloului (dupa pret)");
        puts("8.  Adaugarea unui element nou la sfarsitul tabloului");
        puts("9.  Adaugarea unui element nou la inceputul tabloului");
        puts("10. Inserarea unui element nou dupa elementul indicat");
        puts("11. Inserarea unui element nou inainte de elementul indicat");
        puts("12. Stergerea elementului indicat");
        puts("13. Salvarea informatiei in fisier");
        puts("14. Citirea informatiei din fisier");
        puts("15. Eliberarea memoriei alocate pentru tablou");
        puts("0.  Iesire din program");

        printf("\nSelectati un element de meniu: ");
        scanf("%d", &nm);

        switch(nm)
        {
        case 1:
            if(C != NULL)
            {
                freeArrayOfComputers(C, n);
                C = NULL;
                n = 0;
            }

            printf("Introduceti numarul de calculatoare: ");
            scanf("%d", &n);

            C = (Computer*)calloc(n, sizeof(Computer));
            if(C == NULL)
            {
                puts("Memoria nu este alocata");
                exit(1);
            }
            puts("Memoria alocata cu succes");
            break;

        case 2:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti informatiile despre calculatoare: ");
            readArrayOfComputers(C, n);
            break;

        case 3:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Informatii despre calculatoare: ");
            showArrayOfComputers(C, n);
            break;

        case 4:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti modelul pentru cautare: ");
            fflush(stdin);
            gets(model);

            k = searchComputer(C, n, model);
            if(k < 0) puts("Calculatorul nu a fost gasit in tablou");
            else
            {
                puts("Informatii despre calculatorul gasit: ");
                showComputer(&C[k]);
            }
            break;

        case 5:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti modelul calculatorului pentru modificare: ");
            fflush(stdin);
            gets(model);

            k = searchComputer(C, n, model);
            if(k < 0) puts("Calculatorul nu a fost gasit in tablou");
            else
            {
                puts("Informatii curente: ");
                showComputer(&C[k]);
                modifyComputer(C, k);
                puts("Modificarea a fost efectuata.");
            }
            break;

        case 6:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            printf("Introduceti doua pozitii i si j (1..n): ");
            scanf("%d%d", &i, &j);
            i--; j--;

            swapComputers(C, n, i, j);
            puts("Interschimbarea a fost efectuata (daca indexii au fost corecti).");
            break;

        case 7:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            sortComputers(C, n);
            puts("Sortarea a fost finalizata cu succes");
            break;

        case 8:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti informatiile despre noul calculator: ");
            readComputer(&a);

            B = appendComputer(C, &n, a);
            if(B == NULL) puts("Adaugarea elementului la sfarsit a esuat");
            else { puts("Adaugarea la final s-a finalizat cu succes"); C = B; }
            break;

        case 9:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti informatiile despre noul calculator: ");
            readComputer(&a);

            B = addFrontComputer(C, &n, a);
            if(B == NULL) puts("Adaugarea elementului la inceput a esuat");
            else { puts("Adaugarea la inceput s-a finalizat cu succes"); C = B; }
            break;

        case 10:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti informatiile despre calculator pentru inserare: ");
            readComputer(&a);

            printf("Introduceti pozitia dupa care inserati (1..n): ");
            scanf("%d", &k);
            k--; /* 0-based */

            B = insertAfterComputer(C, &n, a, k);
            if(B == NULL) puts("Inserarea a esuat.");
            else { puts("Inserarea dupa element a fost finalizata cu succes"); C = B; }
            break;

        case 11:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti informatiile despre calculator pentru inserare: ");
            readComputer(&a);

            printf("Introduceti pozitia inaintea careia inserati (1..n): ");
            scanf("%d", &k);
            k--; /* 0-based */

            B = insertBeforeComputer(C, &n, a, k);
            if(B == NULL) puts("Inserarea a esuat.");
            else { puts("Inserarea inainte de element a fost finalizata cu succes"); C = B; }
            break;

        case 12:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            printf("Introduceti pozitia elementului de sters (1..n): ");
            scanf("%d", &k);
            k--;

            if(k < 0 || k >= n){ puts("Pozitie invalida!"); break; }

            puts("Elementul ce va fi sters:");
            showComputer(&C[k]);

            B = deleteComputer(C, &n, k);
            if(B == NULL && n > 0) puts("Stergerea a esuat.");
            else
            {
                puts("Elementul a fost sters cu succes.");
                C = B;
                if(n == 0) C = NULL;
            }
            break;

        case 13:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti numele fisierului: ");
            fflush(stdin);
            gets(fname);

            f = saveInfo(C, n, fname);
            if(f == 1) puts("Scrierea in fisier s-a finalizat cu succes");
            else puts("Fisierul nu a putut fi deschis pentru scriere.");
            break;

        case 14:
            if(C == NULL){ puts("Mai intai alocati memoria (1)!"); break; }
            puts("Introduceti numele fisierului: ");
            fflush(stdin);
            gets(fname);

            f = loadInfo(C, n, fname);
            if(f == 1) puts("Citirea din fisier s-a finalizat cu succes");
            else puts("Fisierul nu a putut fi deschis pentru citire / fisier invalid.");
            break;

        case 15:
            if(C == NULL){ puts("Memoria este deja eliberata / nu e alocata."); break; }
            freeArrayOfComputers(C, n);
            C = NULL;
            n = 0;
            puts("Memoria a fost eliberata cu succes");
            break;

        case 0:
            printf("Doriti sa iesiti din program? (1/0): ");
            scanf("%d", &f);
            if(f == 1) return 0;
            puts("Pentru a continua, apasati Enter.");
            break;

        default:
            puts("Va rugam sa selectati elementul corect din meniu!");
        }
    }
}
