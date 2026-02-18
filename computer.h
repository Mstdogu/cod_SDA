#ifndef COMPUTER_H
#define COMPUTER_H

typedef struct computer
{
    char model[20];
    char procesor[20];
    int memorie;      /* GB */
    float viteza;     /* GHz */
    float pret;       /* lei/euro */
} Computer;

void setComputer(Computer* pob, char* model, char* procesor, int memorie, float viteza, float pret);
void freeComputer(Computer* pob);
void freeArrayOfComputers(Computer* C, int n);

void readComputer(Computer* pob);
void readArrayOfComputers(Computer *C, int n);

void showComputer(Computer*pob);
void showArrayOfComputers(Computer *C, int n);

int searchComputer(Computer* C, int n, char* model);
void sortComputers(Computer *C, int n);

void modifyComputer(Computer* C, int k);

void swapComputers(Computer* C, int n, int i, int j);

Computer* appendComputer(Computer* C, int *pn, Computer a);
Computer* addFrontComputer(Computer* C, int *pn, Computer a);

Computer* insertComputer(Computer* C, int *pn, Computer a, int k);         /* inserare la pozitia k */
Computer* insertAfterComputer(Computer* C, int *pn, Computer a, int k);    /* dupa k */
Computer* insertBeforeComputer(Computer* C, int *pn, Computer a, int k);   /* inainte de k */

Computer* deleteComputer(Computer* C, int *pn, int k);

int saveInfo(Computer* C, int n, char *fname);
int loadInfo(Computer* C, int n, char* fname);

#endif
