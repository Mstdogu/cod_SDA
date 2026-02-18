/*
Program de gestionare a informatiilor despre calculatoare (Computer).
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"computer.h"

/* stricmp compatibil (Windows/Linux/Mac) */
static int my_stricmp(const char* a, const char* b)
{
#ifdef _WIN32
    return _stricmp(a, b);
#else
    /* pe Linux/Mac exista strcasecmp */
    return strcasecmp(a, b);
#endif
}

/* Functie pentru setarea datelor calculatorului */
void setComputer(Computer* pob, char* model, char* procesor, int memorie, float viteza, float pret)
{
    strcpy(pob->model, model);
    strcpy(pob->procesor, procesor);
    pob->memorie = memorie;
    pob->viteza  = viteza;
    pob->pret    = pret;
}

/* Functie pentru "eliberarea" unui element (aici nu e memorie dinamica in campuri) */
void freeComputer(Computer* pob)
{
    (void)pob; /* nimic de eliberat - campuri sunt tablouri fixe */
}

/* Functie pentru eliberarea memoriei alocate pentru masivul de calculatoare */
void freeArrayOfComputers(Computer* C, int n)
{
    int i;
    for(i = 0; i < n; i++)
        freeComputer(&C[i]);
    free(C);
    return;
}

/* Functie pentru citirea datelor unui calculator */
void readComputer(Computer* pob)
{
    char model[40];
    char procesor[40];
    int memorie;
    float viteza, pret;

    printf("Introduceti modelul: ");
    fflush(stdin);
    fgets(model, sizeof(model), stdin);
    model[strcspn(model, "\n")] = 0;

    printf("Introduceti procesorul: ");
    fgets(procesor, sizeof(procesor), stdin);
    procesor[strcspn(procesor, "\n")] = 0;

    printf("Memoria (GB): ");
    scanf("%d", &memorie);

    printf("Viteza (GHz): ");
    scanf("%f", &viteza);

    printf("Pretul: ");
    scanf("%f", &pret);

    /* curata restul liniei dupa ultimele scanf-uri */
    fflush(stdin);

    setComputer(pob, model, procesor, memorie, viteza, pret);
}

/* Functie pentru citirea datelor dintr-un masiv de calculatoare */
void readArrayOfComputers(Computer *C, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("Elementul %d:\n", i + 1);
        readComputer(&C[i]);
    }
    return;
}

/* Functie de afisare a datelor unui calculator */
void showComputer(Computer* pob)
{
    printf("Model: %s | CPU: %s | RAM: %dGB | %.2fGHz | Pret: %.2f\n",
           pob->model, pob->procesor, pob->memorie, pob->viteza, pob->pret);
}

/* Functie pentru afisarea datelor din masiv */
void showArrayOfComputers(Computer *C, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d. ", i + 1);
        showComputer(&C[i]);
    }
    return;
}

/* Cautare dupa model */
int searchComputer(Computer* C, int n, char* model)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(my_stricmp(C[i].model, model) == 0)
            return i;
    }
    return -1;
}

/* Sortare (dupa pret crescator) */
void sortComputers(Computer *C, int n)
{
    int i, k;
    Computer t;
    for(i = 0; i < n; i++)
    {
        for(k = 0; k < n - 1 - i; k++)
        {
            if(C[k].pret > C[k + 1].pret)
            {
                t = C[k];
                C[k] = C[k + 1];
                C[k + 1] = t;
            }
        }
    }
    return;
}

/* Modificare campuri */
void modifyComputer(Computer* C, int k)
{
    int f;
    char s[40];

    printf("Schimbati modelul? (1/0): ");
    scanf("%d", &f);
    if(f != 0)
    {
        printf("Introduceti modelul: ");
        fflush(stdin);
        gets(s);
        strcpy(C[k].model, s);
    }

    printf("Schimbati procesorul? (1/0): ");
    scanf("%d", &f);
    if(f != 0)
    {
        printf("Introduceti procesorul: ");
        fflush(stdin);
        gets(s);
        strcpy(C[k].procesor, s);
    }

    printf("Schimbati memoria? (1/0): ");
    scanf("%d", &f);
    if(f != 0)
    {
        printf("Introduceti memoria (GB): ");
        scanf("%d", &C[k].memorie);
    }

    printf("Schimbati viteza? (1/0): ");
    scanf("%d", &f);
    if(f != 0)
    {
        printf("Introduceti viteza (GHz): ");
        scanf("%f", &C[k].viteza);
    }

    printf("Schimbati pretul? (1/0): ");
    scanf("%d", &f);
    if(f != 0)
    {
        printf("Introduceti pretul: ");
        scanf("%f", &C[k].pret);
    }

    return;
}

/* Interschimbare doua elemente (i, j) */
void swapComputers(Computer* C, int n, int i, int j)
{
    Computer t;
    if(i < 0 || j < 0 || i >= n || j >= n) return;
    t = C[i];
    C[i] = C[j];
    C[j] = t;
}

/* Adaugare la sfarsit */
Computer* appendComputer(Computer* C, int *pn, Computer a)
{
    Computer *B;
    B = (Computer*)realloc(C, ((*pn) + 1) * sizeof(Computer));
    if(B == NULL) return B;

    B[*pn] = a;
    (*pn)++;
    return B;
}

/* Adaugare la inceput */
Computer* addFrontComputer(Computer* C, int *pn, Computer a)
{
    Computer *B;
    int i;

    B = (Computer*)realloc(C, ((*pn) + 1) * sizeof(Computer));
    if(B == NULL) return B;

    for(i = *pn - 1; i >= 0; i--)
        B[i + 1] = B[i];

    B[0] = a;
    (*pn)++;
    return B;
}

/* Inserare la pozitia k (0-based) */
Computer* insertComputer(Computer* C, int *pn, Computer a, int k)
{
    Computer *B;
    int i;

    if(k < 0) k = 0;
    if(k > *pn) k = *pn;

    B = (Computer*)realloc(C, ((*pn) + 1) * sizeof(Computer));
    if(B == NULL) return B;

    for(i = *pn - 1; i >= k; i--)
        B[i + 1] = B[i];

    B[k] = a;
    (*pn)++;
    return B;
}

/* Inserare dupa k (0-based) */
Computer* insertAfterComputer(Computer* C, int *pn, Computer a, int k)
{
    return insertComputer(C, pn, a, k + 1);
}

/* Inserare inainte de k (0-based) */
Computer* insertBeforeComputer(Computer* C, int *pn, Computer a, int k)
{
    return insertComputer(C, pn, a, k);
}

/* Stergere element la index k */
Computer* deleteComputer(Computer* C, int *pn, int k)
{
    Computer *B;
    int i;

    if(*pn <= 0) return C;
    if(k < 0 || k >= *pn) return C;

    for(i = k; i < *pn - 1; i++)
        C[i] = C[i + 1];

    B = (Computer*)realloc(C, ((*pn) - 1) * sizeof(Computer));
    if(B == NULL) return B;

    (*pn)--;
    return B;
}

/* Salvare in fisier (scrie n apoi elementele) */
int saveInfo(Computer* C, int n, char *fname)
{
    FILE *fp;
    int i;

    fp = fopen(fname, "w");
    if(fp == NULL) return 0;

    fprintf(fp, "%d\n", n);
    for(i = 0; i < n; i++)
    {
        fprintf(fp, "%s %s %d %.2f %.2f\n",
                C[i].model, C[i].procesor, C[i].memorie, C[i].viteza, C[i].pret);
    }

    fclose(fp);
    return 1;
}

/* Citire din fisier (cere ca masivul sa fie alocat cu n corect) */
int loadInfo(Computer* C, int n, char* fname)
{
    FILE *fp;
    int i;
    int nf;
    char model[40], procesor[40];
    int memorie;
    float viteza, pret;

    fp = fopen(fname, "r");
    if(fp == NULL) return 0;

    /* citim n din fisier si incarcam doar min(n, nf) */
    if(fscanf(fp, "%d", &nf) != 1)
    {
        fclose(fp);
        return 0;
    }

    for(i = 0; i < n && i < nf; i++)
    {
        fscanf(fp, "%s", model);
        fscanf(fp, "%s", procesor);
        fscanf(fp, "%d", &memorie);
        fscanf(fp, "%f", &viteza);
        fscanf(fp, "%f", &pret);
        setComputer(&C[i], model, procesor, memorie, viteza, pret);
    }

    fclose(fp);
    return 1;
}
