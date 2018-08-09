extern int minpont;

typedef struct dicsoseg
{
    int hely;
    char nev[15];
    int pontok;
} dicsoseg;

bool fajl_be();
bool fajl_ki();
void dicsosegFrissit(char *nev,int pontszam);
void dicsosegKiir(SDL_Renderer **rend1);
