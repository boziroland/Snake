#include "jatek.h"
#include "settings.h"
#include "dicsoseg.h"

bool close_requested = 0;

bool InitWinRender(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags);

int main(int argc, char** argv)
{

    SDL_Window *win=NULL;
    SDL_Renderer **rend1=(SDL_Renderer**)malloc(sizeof(SDL_Renderer*));
    Uint32 render_flags;

    InitWinRender(win,rend1,&render_flags);

    TTF_Init();
    TTF_Font *font=TTF_OpenFont("rampage.ttf",150);
    SDL_Color MenuSnake= {0,0,0};

    SDL_Surface *start;
    start=TTF_RenderText_Solid(font,"Start",MenuSnake);
    SDL_Texture* Tstart;
    Tstart=SDL_CreateTextureFromSurface(*rend1,start);
    SDL_FreeSurface(start);

    SDL_Surface *dicsosegtabla;
    dicsosegtabla=TTF_RenderText_Solid(font,"Top10",MenuSnake);
    SDL_Texture* Tdics;
    Tdics=SDL_CreateTextureFromSurface(*rend1,dicsosegtabla);
    SDL_FreeSurface(dicsosegtabla);

    SDL_Surface *beallitasok;
    beallitasok=TTF_RenderText_Solid(font,"Beall",MenuSnake);
    SDL_Texture* Tbea;
    Tbea=SDL_CreateTextureFromSurface(*rend1,beallitasok);
    SDL_FreeSurface(beallitasok);

    TTF_Font *fontki=TTF_OpenFont("rampage.ttf",100);

    SDL_Surface *kilep;
    kilep=TTF_RenderText_Solid(fontki,"X",MenuSnake);
    SDL_Texture *Tkilep;
    Tkilep=SDL_CreateTextureFromSurface(*rend1,kilep);
    SDL_FreeSurface(kilep);

    SDL_Color clr= {255,255,255};
    SDL_Surface *p1=TTF_RenderText_Solid(font,"1P",clr);
    SDL_Texture *Tp1=SDL_CreateTextureFromSurface(*rend1,p1);
    SDL_FreeSurface(p1);

    SDL_Surface *p2=TTF_RenderText_Solid(font,"2P",clr);
    SDL_Texture *Tp2=SDL_CreateTextureFromSurface(*rend1,p2);
    SDL_FreeSurface(p2);

    fajl_be();
    mousepos mouse;
    while(!close_requested)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        SDL_RenderClear(*rend1); //kép megtisztítása

        SDL_SetRenderDrawColor(*rend1, 255, 240, 220, 255); //háttér
        SDL_Rect menuhatter= {0,0,WIN_WIDTH,WIN_HEIGHT};
        SDL_RenderFillRect(*rend1, &menuhatter);

        //képernyőn lévő gombok kirajzolása, szövegek elhelyezése, valószínűleg túl van bonyolítva, egyszerűsítésük, rendszerezésük tervben van,

        SDL_SetRenderDrawColor(*rend1, 255, 0, 0, 255); //renderelési szín megváltoztatása
        SDL_Rect menupont1= {WIN_WIDTH/3,WIN_HEIGHT/4+160,425,150}; //téglalap létrehozása
        SDL_RenderFillRect(*rend1, &menupont1); //téglalap kirajzolásra kész

        SDL_Rect menupont11= {WIN_WIDTH/3+WIN_WIDTH/9-75,WIN_HEIGHT/4+170,425-WIN_WIDTH/9-200,100}; //téglalap létrehozása
        SDL_QueryTexture(Tdics,NULL,NULL,&menupont11.w,&menupont11.h);
        SDL_RenderCopy(*rend1,Tdics,NULL,&menupont11);

        SDL_SetRenderDrawColor(*rend1, 255, 0, 0, 255); //renderelési szín megváltoztatása
        SDL_Rect menupont2= {WIN_WIDTH/3,WIN_HEIGHT/4+320,425,150}; //téglalap létrehozása
        SDL_RenderFillRect(*rend1, &menupont2); //téglalap kirajzolásra kész

        SDL_Rect menupont21= {WIN_WIDTH/3+WIN_WIDTH/9-75,WIN_HEIGHT/4+330,425-WIN_WIDTH/9-200,100};
        SDL_QueryTexture(Tbea,NULL,NULL,&menupont21.w,&menupont21.h);
        SDL_RenderCopy(*rend1,Tbea,NULL,&menupont21);


        SDL_SetRenderDrawColor(*rend1, 255, 0, 0, 255); //renderelési szín megváltoztatása
        SDL_Rect kilepes= {WIN_WIDTH-150,WIN_HEIGHT/4+320+75,75,75}; //téglalap létrehozása
        SDL_RenderFillRect(*rend1, &kilepes); //téglalap kirajzolásra kész

        SDL_Rect kilep= {WIN_WIDTH-130,WIN_HEIGHT/4+320+69,75,75}; //téglalap létrehozása
        SDL_QueryTexture(Tkilep,NULL,NULL,&kilep.w,&kilep.h);
        SDL_RenderCopy(*rend1,Tkilep,NULL,&kilep);

        SDL_Rect oneplayer= {WIN_WIDTH/3,WIN_HEIGHT/4,215,150};
        SDL_Rect TTFoneplayer= {WIN_WIDTH/3+50,WIN_HEIGHT/4+10,215,150};

        SDL_Rect twoplayer= {WIN_WIDTH/2,WIN_HEIGHT/4,215,150};
        SDL_Rect TTFtwoplayer= {WIN_WIDTH/2+50,WIN_HEIGHT/4+10,215,150};

        eger=SDL_GetMouseState(&mouse.egerx,&mouse.egery);

        SDL_SetRenderDrawColor(*rend1, 0, 0, 200, 255);
        SDL_RenderFillRect(*rend1, &oneplayer);
        SDL_QueryTexture(Tp1,NULL,NULL,&TTFoneplayer.w,&TTFoneplayer.h);
        SDL_RenderCopy(*rend1,Tp1,NULL,&TTFoneplayer);

        SDL_SetRenderDrawColor(*rend1, 0, 0, 100, 255);
        SDL_RenderFillRect(*rend1, &twoplayer);
        SDL_QueryTexture(Tp2,NULL,NULL,&TTFtwoplayer.w,&TTFtwoplayer.h);
        SDL_RenderCopy(*rend1,Tp2,NULL,&TTFtwoplayer);

        switch(event.type)
        {
        case SDL_QUIT:
            close_requested = 1;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(teglalapban(&oneplayer,mouse.egerx,mouse.egery))
                egyjatekos(win,rend1,render_flags);
            if(teglalapban(&twoplayer,mouse.egerx,mouse.egery))
                ketjatekos(win,rend1,render_flags);
            if(teglalapban(&menupont1,mouse.egerx,mouse.egery))
                dicsosegKiir(rend1);
            if(teglalapban(&menupont2,mouse.egerx,mouse.egery))
                beallitas(rend1);
            if(teglalapban(&kilepes,mouse.egerx,mouse.egery))
                close_requested = 1;
            break;
        }
        SDL_RenderPresent(*rend1);
        system("cls");
    }
    //memóriafelszabadítás
    SDL_DestroyTexture(Tstart);
    SDL_DestroyTexture(Tbea);
    SDL_DestroyTexture(Tkilep);
    SDL_DestroyTexture(Tdics);
    TTF_CloseFont(font);
    TTF_CloseFont(fontki);
    TTF_Quit();
    SDL_DestroyRenderer(*rend1);
    free(*rend1);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

//SDL inicializálása, ablak létrehozása, renderelő létrehozása
bool InitWinRender(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags)
{
    //inicializálás, SDL_Init nullát returnöl siker esetén
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)!=0)
    {
        printf("Hiba: %s\n",SDL_GetError());
        return 0;
    }
    //ablak létrehozása, fgv(ablaknév, x poz,y poz,szélesség,magasság,flagek
    win = SDL_CreateWindow("Snake",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,0);
    //ha nem sikerül, hibáról    információ kiiratása és kilépés
    if(!win)
    {
        printf("Hiba: %s\n",SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *render_flags = SDL_RENDERER_ACCELERATED;
    *rend1 = SDL_CreateRenderer(win,-1, *render_flags);
    if(!rend1)
    {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 0;
    }
    return 1;
}
