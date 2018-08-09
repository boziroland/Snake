#include "settings.h"
#include "jatek.h"
//beolvassa a felhasznalotol a kivant egysegmeretet és frissiti az adott valtozot
void MeretCsere()
{
    printf("Add meg hany pixel legyen egy egyseg merete!(Alap: 35)\n(40-nel osztva 35 maradekot ado szamok mukodnek biztosan stabilan.(tobbe-kevesbe))\n");
    int megadott=35;
    scanf("%d",&megadott);
    meret=megadott;
    printf("Beallitasok mentve! Mostantol egy egyseg %d pixel meretu lesz.\n",meret);
}
//a beallitasok menupont grafikai részéért felel
void beallitas(SDL_Renderer** rend1)
{
    SDL_Rect hatter= {0,0,WIN_WIDTH,WIN_HEIGHT};
    SDL_SetRenderDrawColor(*rend1, 0, 0, 255, 255); //háttér
    SDL_RenderFillRect(*rend1, &hatter);

    bool back_requested=0;

    StructForTTF Rbeall;
    Rbeall.Color.r=255;
    Rbeall.Color.g=255;
    Rbeall.Color.b=255;
    Rbeall.Rect.x_pos=450;
    Rbeall.Rect.y_pos=310;
    Rbeall.Rect.w=strlen("Meretezes")*40;
    Rbeall.Rect.h=100;

    TTFCreateAndPrint(rend1,"Meretezes",100,Rbeall);

    SDL_Rect MeretGomb= {450,310,strlen("Meretezes")*40,100};
    SDL_Rect KlikkOnMeret= {WIN_WIDTH/4,WIN_HEIGHT/4,WIN_WIDTH/2,WIN_HEIGHT/2};
    SDL_Rect OkGomb= {WIN_WIDTH/2-100,WIN_HEIGHT/2+100,200,60};

    StructForTTF TTFmeret;
    TTFmeret.Color.r=140;
    TTFmeret.Color.g=100;
    TTFmeret.Color.b=255;
    TTFmeret.Rect.x_pos=WIN_WIDTH/2-300;
    TTFmeret.Rect.y_pos=WIN_HEIGHT/2-50;
    TTFmeret.Rect.w=600;
    TTFmeret.Rect.h=60;

    mousepos mouse;
    SDL_Event event;
    bool ok;
    SDL_Rect vissza= {50,50,100,50};
    StructForTTF TTFVissza;
    TTFVissza.Color.r=255;
    TTFVissza.Color.g=255;
    TTFVissza.Color.b=255;
    TTFVissza.Rect.x_pos=50;
    TTFVissza.Rect.y_pos=50;
    TTFVissza.Rect.w=100;
    TTFVissza.Rect.h=50;
    StructForTTF TTFok;
    TTFok.Color.r=255;
    TTFok.Color.g=255;
    TTFok.Color.b=255;
    TTFok.Rect.x_pos=OkGomb.x+60;
    TTFok.Rect.y_pos=OkGomb.y;
    TTFok.Rect.w=80;
    TTFok.Rect.h=OkGomb.h;
    bool lefutas;
    while(!back_requested&&!close_requested)
    {
        ok=0;
        lefutas=0;
        SDL_PollEvent(&event);
        eger=SDL_GetMouseState(&mouse.egerx,&mouse.egery);
        SDL_SetRenderDrawColor(*rend1,0,0,255,255);
        SDL_RenderFillRect(*rend1,&hatter);
        SDL_SetRenderDrawColor(*rend1,0,100,255,255);
        SDL_RenderFillRect(*rend1,&MeretGomb);
        TTFCreateAndPrint(rend1,"Meretezes",100,Rbeall);
        SDL_SetRenderDrawColor(*rend1,255,125,0,255);
        SDL_RenderFillRect(*rend1,&vissza);
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(teglalapban(&MeretGomb,mouse.egerx,mouse.egery))
            {
                while(!ok)
                {
                    SDL_PollEvent(&event);
                    eger=SDL_GetMouseState(&mouse.egerx,&mouse.egery);
                    SDL_SetRenderDrawColor(*rend1,255,255,255,255);
                    SDL_RenderFillRect(*rend1,&KlikkOnMeret);
                    TTFCreateAndPrint(rend1,"Add meg a konzolban a kivant meretet!",100,TTFmeret);
                    SDL_SetRenderDrawColor(*rend1,45,188,255,255);
                    SDL_RenderFillRect(*rend1,&OkGomb);
                    TTFCreateAndPrint(rend1,"Vissza",40,TTFVissza);
                    TTFCreateAndPrint(rend1,"OK",60,TTFok);
                    SDL_RenderPresent(*rend1);
                    if(!lefutas)
                        MeretCsere();
                    if(event.type==SDL_MOUSEBUTTONDOWN)
                        if(teglalapban(&OkGomb,mouse.egerx,mouse.egery))
                            ok=1;
                    lefutas=1;
                }
            }
            if(teglalapban(&vissza,mouse.egerx,mouse.egery))
                back_requested=1;
        }
        if(event.type==SDL_QUIT)
            close_requested = 1;
        TTFCreateAndPrint(rend1,"Vissza",40,TTFVissza);
        SDL_RenderPresent(*rend1);
    }
}
