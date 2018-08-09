#include "jatek.h"
#include "dicsoseg.h"

dicsoseg top10[10];
int minpont;
//beolvassa a dicsoseg.txt tartalmat a top10 tombbe
bool fajl_be()
{
    FILE *fp;
    fp=fopen("dicsoseg.txt","rt");
    if(fp==NULL)
    {
        return 0;
    }
    int i;
    for(i=0; i<10; i++)
    {
        fscanf(fp,"%d",&top10[i].hely);
        fscanf(fp,"%s",top10[i].nev);
        fscanf(fp,"%d",&top10[i].pontok);
    }
    fclose(fp);
    minpont=top10[9].pontok;
    return 1;
}
//frissiti a dicsoseg.txt tartalmát
bool fajl_ki()
{
    FILE *fp;
    fp=fopen("dicsoseg.txt","w+t");
    if(fp==NULL)
    {
        return 0;
    }
    int i;
    for(i=0; i<10; i++)
    {
        fprintf(fp,"%d\t%s\t%d\n",top10[i].hely,top10[i].nev,top10[i].pontok);
    }
    fclose(fp);
    return 1;

}
//frissiti a mar beolvasott dicsoseglistat
void dicsosegFrissit(char *nev,int pontszam)
{
    int i=0;
    while(nev[i]!='\n')
        i++;
    nev[i]='\0';
    i=0;
    while(top10[i].pontok>=pontszam)
        i++;
    //az i-edik már kisebb
    char tmpnev[15];
    strcpy(tmpnev,top10[i].nev);
    int tmppont=top10[i].pontok;
    strcpy(top10[i].nev,nev);
    top10[i].pontok=pontszam;
    i++;
    while(i<=10)
    {
        strcpy(nev,top10[i].nev);
        pontszam=top10[i].pontok;
        strcpy(top10[i].nev,tmpnev);
        top10[i].pontok=tmppont;
        strcpy(tmpnev,nev);
        tmppont=pontszam;
        i++;
    }
    fajl_ki();
}
//Ha a menuben rakattintunk a dicsoseglista gombjara, kirajzolja a dicsoseglistat
void dicsosegKiir(SDL_Renderer **rend1)
{
    bool back_requested=0;
    mousepos mouse;
    SDL_SetRenderDrawColor(*rend1, 65, 200, 255, 255);
    SDL_Rect hatter= {0,0,WIN_WIDTH,WIN_HEIGHT};
    SDL_RenderFillRect(*rend1, &hatter);
    int i;
    char hely[2];
    char pontok[5];
    StructForTTF PontStruct;
    PontStruct.Color.r=255;
    PontStruct.Color.g=255;
    PontStruct.Color.b=255;
    PontStruct.Rect.x_pos=220;
    PontStruct.Rect.y_pos=10;
    PontStruct.Rect.w=160/4;
    PontStruct.Rect.h=80;
    for(i=0; i<10; i++)
    {
        PontStruct.Rect.x_pos=220;
        PontStruct.Rect.y_pos=10+i*70;
        sprintf(hely,"%d",top10[i].hely);
        sprintf(pontok,"%d",top10[i].pontok);
        TTFCreateAndPrint(rend1,hely,100,PontStruct);
        PontStruct.Rect.x_pos=210+140;
        PontStruct.Rect.w=strlen(top10[i].nev)*40;
        TTFCreateAndPrint(rend1,top10[i].nev,100,PontStruct);
        PontStruct.Rect.x_pos=840+140;
        PontStruct.Rect.w=160/4+20;
        TTFCreateAndPrint(rend1,pontok,100,PontStruct);
    }
    SDL_RenderPresent(*rend1);
    SDL_Event event;
    SDL_Rect vissza= {50,50,100,50};
    StructForTTF TTFVissza;
    TTFVissza.Color.r=255;
    TTFVissza.Color.g=255;
    TTFVissza.Color.b=255;
    TTFVissza.Rect.x_pos=50;
    TTFVissza.Rect.y_pos=50;
    TTFVissza.Rect.w=100;
    TTFVissza.Rect.h=50;
    while(!back_requested&&!close_requested)
    {
        SDL_PollEvent(&event);
        eger=SDL_GetMouseState(&mouse.egerx,&mouse.egery);
        SDL_SetRenderDrawColor(*rend1,255,125,0,255);
        SDL_RenderFillRect(*rend1,&vissza);
        TTFCreateAndPrint(rend1,"Vissza",40,TTFVissza);
        SDL_RenderPresent(*rend1);
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(teglalapban(&vissza,mouse.egerx,mouse.egery))
                back_requested=1;
        }
        if(event.type==SDL_QUIT)
            close_requested = 1;
    }
}
