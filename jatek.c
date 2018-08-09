#include "jatek.h"
#include "settings.h"
#include "dicsoseg.h"

int meret=35;
int eger;

SDL_Rect alma;

//ez a fuggveny ellenorzi, hogy az eger a menupontban van-e a bal egergomb lenyomasa pillanataban
bool teglalapban(SDL_Rect* menupont, int x, int y)
{
    return ((x>=menupont->x&&x<menupont->x+menupont->w)&&(y>=menupont->y&&y<menupont->y+menupont->h));
}
//Kilepeskor felszabaditja a lancolt listat
void freeList(kigyo** head)
{
    kigyo* tmp;

    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->kovnode;
        free(tmp);
    }
}
//Altalaban ez a fuggveny vegzi a kepernyore a szovegkiirást
void TTFCreateAndPrint(SDL_Renderer **rend1,char *StrToPrint,int SizeofFont,StructForTTF StructOfAll)
{
    int tex_w=0,tex_h=0;

    SDL_Rect WhereTo= {StructOfAll.Rect.x_pos,StructOfAll.Rect.y_pos,StructOfAll.Rect.w,StructOfAll.Rect.h,};
    TTF_Font *Font=TTF_OpenFont("arial.ttf",SizeofFont);
    SDL_Color TextC= {StructOfAll.Color.r,StructOfAll.Color.g,StructOfAll.Color.b};
    SDL_Surface *Surface=TTF_RenderText_Solid(Font,StrToPrint,TextC);
    SDL_Texture *Texture=SDL_CreateTextureFromSurface(*rend1,Surface);
    SDL_QueryTexture(Texture,NULL,NULL,&tex_w,&tex_h);
    SDL_RenderCopy(*rend1,Texture,NULL,&WhereTo);
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}
//Amennyiben a felhasznalo nyert, meghivodik es bekeri a nevet
void getInput(char *nev, int maxhossz)
{
    printf("Kerlek add meg a neved! (Max %d karakter, ha ennel tobbet adsz meg, csak az elso %d fog megjelenni!)\n",maxhossz-1, maxhossz-1);
    fgets(nev,maxhossz-1,stdin);
    printf("A dicsoseglista frissult!");
}
//2 jatekos mod eseten eldonti, hogy ki nyert
void Ki_Nyert(SDL_Renderer **rend1,kigyo *kigyo1,kigyo *kigyo2)
{
    StructForTTF Nyertes;
    Nyertes.Color.r=0;
    Nyertes.Color.g=110;
    Nyertes.Color.b=255;
    Nyertes.Rect.x_pos=WIN_WIDTH/2-120;
    Nyertes.Rect.y_pos=WIN_HEIGHT/2;
    Nyertes.Rect.w=240;
    Nyertes.Rect.h=60;
    if(kigyo1->fej.x==kigyo2->fej.x&&kigyo1->fej.y==kigyo2->fej.y)
    {
        TTFCreateAndPrint(rend1,"Dontetlen!",100,Nyertes);
        SDL_RenderPresent(*rend1);
        return;
    }
    kigyo *current1=kigyo1;
    while(current1!=NULL)
    {
        if(current1->fej.x==kigyo2->fej.x&&current1->fej.y==kigyo2->fej.y)
        {
            TTFCreateAndPrint(rend1,"Jatekos Egy Nyert!",100,Nyertes);
            SDL_RenderPresent(*rend1);
            return;
        }
        current1=current1->kovnode;
    }
    kigyo *current2=kigyo2;
    while(current2!=NULL)
    {
        if(current2->fej.x==kigyo2->fej.x&&current2->fej.y==kigyo2->fej.y)
        {
            TTFCreateAndPrint(rend1,"Jatekos Egy Nyert!",100,Nyertes);
            SDL_RenderPresent(*rend1);
            return;
        }
        current2=current2->kovnode;
    }
    TTFCreateAndPrint(rend1,"Jatekos Ketto Nyert!",100,Nyertes);
    SDL_RenderPresent(*rend1);
}
//Egyjatekos mod eseten megnezi, hogy nyert-e a jatekos
void Nyert_e(SDL_Renderer **rend1,int pontszam)
{
    StructForTTF Nyert;
    Nyert.Color.r=140;
    Nyert.Color.g=100;
    Nyert.Color.b=255;

    Nyert.Rect.x_pos=WIN_WIDTH/2-300;
    Nyert.Rect.y_pos=WIN_HEIGHT/2-50;
    Nyert.Rect.w=600;
    Nyert.Rect.h=60;
    if(pontszam>minpont)
    {
        TTFCreateAndPrint(rend1,"Gratulalok felkerultel a dicsoseglistara!",100,Nyert);
        Nyert.Rect.y_pos=WIN_HEIGHT/2;
        TTFCreateAndPrint(rend1,"Kerlek add meg a neved a konzolban.",100,Nyert);
        SDL_RenderPresent(*rend1);
        char nev[15];
        getInput(nev,15);
        dicsosegFrissit(nev,pontszam);
    }
    else
    {
        TTFCreateAndPrint(rend1,"Sajnos nem eleg a pontszamod",100,Nyert);
        Nyert.Rect.x_pos=WIN_WIDTH/2-120;
        Nyert.Rect.y_pos=WIN_HEIGHT/2;
        Nyert.Rect.w=240;
        TTFCreateAndPrint(rend1,"Probald ujra!",100,Nyert);
        SDL_RenderPresent(*rend1);
    }
}
//Ellenorzi, az utkozest
bool check4Clash(kigyo *kigyo1,kigyo *kigyo2)
{
    kigyo *mozgo1=kigyo1;
    while(mozgo1->kovnode!=NULL)
    {
        mozgo1=mozgo1->kovnode;
        if((kigyo1->fej.x==mozgo1->fej.x)&&(kigyo1->fej.y==mozgo1->fej.y))
            return 1;
    }
    if(kigyo2!=NULL)
    {
        kigyo *mozgo2=kigyo2;
        while(mozgo2->kovnode!=NULL)
        {
            mozgo2=mozgo2->kovnode;
            if((kigyo2->fej.x==mozgo2->fej.x)&&(kigyo2->fej.y==mozgo2->fej.y))
                return 1;
        }
        mozgo1=kigyo1;
        while(mozgo1!=NULL)
        {
            mozgo2=kigyo2;
            while(mozgo2!=NULL)
            {
                if (mozgo1->fej.x==mozgo2->fej.x&&mozgo1->fej.y==mozgo2->fej.y)
                    return 1;
                mozgo2=mozgo2->kovnode;
            }
            mozgo1=mozgo1->kovnode;
        }
    }
    return 0;
}
//Jatek vege
void GameOver(SDL_Renderer **rend1, int pontszam,bool* backtomenu,kigyo *kigyo1,kigyo *kigyo2)
{
    bool lefutottmar=0;
    mousepos mouse;
    *backtomenu=0;

    StructForTTF GO;
    GO.Color.r=255;
    GO.Color.g=255;
    GO.Color.b=255;
    GO.Rect.x_pos=WIN_WIDTH/4+200;
    GO.Rect.y_pos=WIN_HEIGHT/4+50;
    GO.Rect.w=250;
    GO.Rect.h=50;

    StructForTTF Menu;
    Menu.Color.r=255;
    Menu.Color.g=250;
    Menu.Color.b=0;
    Menu.Rect.x_pos=WIN_WIDTH/2-90;
    Menu.Rect.y_pos=WIN_HEIGHT/2+105;
    Menu.Rect.w=180;
    Menu.Rect.h=50;

    while(!close_requested&&!(*backtomenu))
    {
        eger=SDL_GetMouseState(&mouse.egerx,&mouse.egery);
        SDL_Event event;
        SDL_PollEvent(&event);

        SDL_Rect GameOverScreen= {WIN_WIDTH/4,WIN_HEIGHT/4,WIN_WIDTH/2,WIN_HEIGHT/2};
        SDL_SetRenderDrawColor(*rend1, 255, 0, 0, 255);
        SDL_RenderFillRect(*rend1,&GameOverScreen);

        TTFCreateAndPrint(rend1,"Game Over!",100,GO);

        SDL_Rect BackToMenu= {WIN_WIDTH/2-100,WIN_HEIGHT/2+100,200,60};
        SDL_SetRenderDrawColor(*rend1,45,188,255,255);
        SDL_RenderFillRect(*rend1,&BackToMenu);


        TTFCreateAndPrint(rend1,"Vissza a menube",40,Menu);
        if(!lefutottmar&&kigyo2==NULL)
        {
            Nyert_e(rend1,pontszam);
            lefutottmar=1;
        }
        if(!lefutottmar&&kigyo2!=NULL)
        {
            Ki_Nyert(rend1,kigyo1,kigyo2);
            lefutottmar=1;
        }
        if(event.type==SDL_MOUSEBUTTONUP)
        {
            if(teglalapban(&BackToMenu,mouse.egerx,mouse.egery)) *backtomenu=1;
        }
    }
}
//kezdeskor letrehozza a kigyot,utana frissiti a poziciojat/meretet
bool SnakeBodyLogic(bool *start,int spawn,kigyo **head,int* irany,int *merre,spawnpos pos)
{
    bool spawnapple=0;
    if (*start)
    {
        *head=malloc(sizeof(kigyo));
        (*head)->fej.h=meret;
        (*head)->fej.w=meret;
        (*head)->fej.x=pos.x;
        (*head)->fej.y=pos.y;

        (*head)->kovnode=(kigyo*)malloc(sizeof(kigyo));
        (*head)->kovnode->fej.h=meret;
        (*head)->kovnode->fej.w=meret;
        (*head)->fej.x=pos.x;
        (*head)->fej.y=pos.y+meret+5;

        (*head)->kovnode->kovnode=NULL;

        *irany=1;
        *start=0;
        *merre=0;
    }
    kigyo *current=*head;
    //a merre valtozo tarolja, hogy iranyvaltoztatas elott melyik iranyba ment a kigyo, es ezzel akadalyozom meg azt hogy ellenkezo iranyba lehessen menni
    if (*irany==1&&*merre==2) *irany=2;
    if (*irany==2&&*merre==1) *irany=1;
    if (*irany==3&&*merre==4) *irany=4;
    if (*irany==4&&*merre==3) *irany=3;

    if((current->fej.x-alma.x!=0)||(current->fej.y-alma.y!=0))
    {
        while(current->kovnode->kovnode!=NULL)current=current->kovnode;
        free(current->kovnode);
        current->kovnode=NULL;
    }
    else
    {
        spawnapple=1;
    }

    kigyo *ujfej=malloc(sizeof(kigyo));

    if(*irany==1||*irany==2)
        ujfej->fej.x=(*head)->fej.x;
    if(*irany==3||*irany==4)
        ujfej->fej.y=(*head)->fej.y;

    ujfej->fej.w=meret;
    ujfej->fej.h=meret;

    switch (*irany)
    {
    case 1:
        ujfej->fej.y=(*head)->fej.y-meret-5;
        *merre=1;
        break;
    case 2:
        ujfej->fej.y=(*head)->fej.y+meret+5;
        *merre=2;
        break;
    case 3:
        ujfej->fej.x=(*head)->fej.x+meret+5;
        *merre=3;
        break;
    case 4:
        ujfej->fej.x=(*head)->fej.x-meret-5;
        *merre=4;
        break;
    }
    ujfej->kovnode=*head;
    *head=ujfej;

    current=*head;
    if(current->fej.x>WIN_WIDTH-1) current->fej.x=0;
    if(current->fej.x<(-1)) current->fej.x=WIN_WIDTH;
    if(current->fej.y>WIN_HEIGHT-1) current->fej.y=0;
    if(current->fej.y<(-1)) current->fej.y=WIN_HEIGHT;
    return spawnapple;
}

//Az almakat hozza letre
void spawnApple(kigyo *kigyo1,kigyo* kigyo2)
{
    alma.w=meret;
    alma.h=meret;
    alma.x=(rand()%(WIN_WIDTH/(meret+5)))*(meret+5);
    alma.y=(rand()%(WIN_HEIGHT/(meret+5)))*(meret+5);
    kigyo* current=kigyo1;
    while(current!=NULL)
    {
        if(current->fej.x==alma.x&&current->fej.y==alma.y)
        {
            alma.x=(rand()%(WIN_WIDTH/(meret+5)))*(meret+5);
            alma.y=(rand()%(WIN_HEIGHT/(meret+5)))*(meret+5);
            current=kigyo1;
        }
        current=current->kovnode;
    }
    current=kigyo2;
    while(current!=NULL)
    {
        if(current->fej.x==alma.x&&current->fej.y==alma.y)
        {
            alma.x=(rand()%(WIN_WIDTH/(meret+5)))*(meret+5);
            alma.y=(rand()%(WIN_HEIGHT/(meret+5)))*(meret+5);
            current=kigyo2;
        }
        current=current->kovnode;
    }
}

//A palyat hozza letre
bool **CreateGame()
{
    int x,y;
    bool **palya;
    palya = (bool**) malloc(WIN_HEIGHT * sizeof(bool*));
    palya[0] = (bool*) malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(bool));
    for (y = 1; y < WIN_HEIGHT; y++)
        palya[y] = palya[0] + y*WIN_WIDTH;
//ha nem nullazom le akkor minden futtatasnal kapok uzenetet arrol, hogy a program kodolasa megvaltozott, ami zavart
    for(y=0; y<WIN_HEIGHT; y++)
        for(x=0; x<WIN_WIDTH; x++)
            palya[y][x]=0;

    return palya;
}
//Kiirja a pontszamot a kepernyore
void DrawPoints(SDL_Renderer **rend1,SDL_Surface *surface,SDL_Texture *texture,SDL_Color pontok,TTF_Font *font,char* osszpont)
{
    int texW=0,texH=0;
    SDL_Rect pont1= {0,0,200,50};
    surface = TTF_RenderText_Solid(font, osszpont, pontok);
    texture = SDL_CreateTextureFromSurface(*rend1, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    SDL_RenderCopy(*rend1, texture, NULL, &pont1);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
//Ez a fuggveny frissiti a kepernyot
void DrawOnScreen(bool **palya,SDL_Renderer **rend1,SDL_Event event,SDL_Surface *surface,SDL_Texture *texture,SDL_Color pontok,TTF_Font *font,char* osszpont,kigyo **headnr1,kigyo **headnr2)
{
    SDL_SetRenderDrawColor(*rend1, 0, 0, 0, 255); //renderelési szín megváltoztatása
    SDL_RenderClear(*rend1);

    SDL_SetRenderDrawColor(*rend1, 0, 255, 0, 255);
    kigyo *current1=*headnr1;
    while(current1!=NULL)
    {
        SDL_RenderFillRect(*rend1,&current1->fej);
        current1=current1->kovnode;
    }
    if(headnr2!=NULL)
    {
        SDL_SetRenderDrawColor(*rend1,140,100,255,255);
        kigyo *current2=*headnr2;
        while(current2!=NULL)
        {
            SDL_RenderFillRect(*rend1,&current2->fej);
            current2=current2->kovnode;
        }
    }
    SDL_SetRenderDrawColor(*rend1,255,0,0,255);
    SDL_RenderFillRect(*rend1,&alma);
    if(headnr2==NULL) DrawPoints(rend1,surface,texture,pontok,font,osszpont);
    SDL_RenderPresent(*rend1);
}
//PLAYER1
//A felhasznaloi inputokat kezeli
void input(SDL_Event event,int *irany)
{
    switch(event.type)
    {
    case SDL_QUIT:
        close_requested = 1;
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=1;
            break;
        case SDL_SCANCODE_DOWN:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=2;
            break;
        case SDL_SCANCODE_RIGHT:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=3;
            break;
        case SDL_SCANCODE_LEFT:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=4;
            break;
        default:
            break;
        }
    }
}
//PLAYER2
//A felhasznaloi inputokat kezeli
void inputp2(SDL_Event event, int *irany)
{
    if(event.type==SDL_KEYDOWN)
    {
        switch(event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=1;
            break;
        case SDL_SCANCODE_S:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=2;
            break;
        case SDL_SCANCODE_D:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=3;
            break;
        case SDL_SCANCODE_A:
            SDL_FlushEvent(SDL_KEYDOWN);
            *irany=4;
            break;
        default:
            break;
        }
    }
}

//A fo fuggveny, melyben az egyjatekos mod fut
void egyjatekos(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags)
{
    bool start=1;
    bool **palya=CreateGame();
    srand(time(0));
    kigyo *head=NULL;
    TTF_Init();
    TTF_Font *font=TTF_OpenFont("rampage.ttf",100);
    SDL_Color pontok= {255,255,255};
    SDL_Surface *surface;
    SDL_Texture *texture;
    int pontszam=0;
    char osszpont[13];//10 000 pont fölött nem működik
    sprintf(osszpont,"Pontok: %4d",0);
    int almaSpawn=0;
    SDL_Event event;
    int irany=0;
    int merre;
    spawnpos pos= {0,0};
    bool back_requested=0;
    spawnApple(head,NULL);
    while(!close_requested&&!back_requested)
    {
        SDL_PollEvent(&event);
        input(event,&irany);
        almaSpawn=SnakeBodyLogic(&start,almaSpawn,&head,&irany,&merre,pos);
        if(almaSpawn) spawnApple(head,NULL);
        if (almaSpawn)
        {
            pontszam++;
            sprintf(osszpont,"Pontok: %4d",pontszam);
        }
        if(check4Clash(head,NULL)) GameOver(rend1,pontszam,&back_requested,head,NULL);
        DrawOnScreen(palya,rend1,event,surface,texture,pontok,font,osszpont,&head,NULL);
        SDL_Delay(1000/10);
    }
    freeList(&head);
    free(palya[0]); //palya[0]
    free(palya);//palya
    TTF_CloseFont(font);
    TTF_Quit();
}
//a fo fuggveny melyben a ketjatekos mod fut
void ketjatekos(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags)
{
    bool start=1;
    bool **palya=CreateGame();
    srand(time(0));
    kigyo *player_one=NULL;
    kigyo *player_two=NULL;
    int irany1=0;
    int irany2=0;
    SDL_Event event;
    bool almaSpawn=0;
    SDL_Color pontok= {255,255,255};
    int merre1;
    int merre2;
    spawnpos pos1= {0,0};
    spawnpos pos2= {WIN_WIDTH-meret-5,0};
    bool lefutottmar=0;
    spawnApple(player_one,player_two);
    bool back_requested=0;
    while(!close_requested&&!back_requested)
    {
        SDL_PollEvent(&event);
        input(event,&irany1);
        inputp2(event,&irany2);
        almaSpawn=SnakeBodyLogic(&start,almaSpawn,&player_one,&irany1,&merre1,pos1);
        if(lefutottmar==0) start=1;
        almaSpawn|=SnakeBodyLogic(&start,almaSpawn,&player_two,&irany2,&merre2,pos2);
        if(almaSpawn)spawnApple(player_one,player_two);
        if(check4Clash(player_one,player_two)) GameOver(rend1,0,&back_requested,player_one,player_two);
        lefutottmar=1;
        DrawOnScreen(palya,rend1,event,NULL,NULL,pontok,NULL,NULL,&player_one,&player_two);
        SDL_Delay(1000/10);
    }
    freeList(&player_one);
    freeList(&player_two);
    free(palya[0]);//palya[0]
    free(palya);//palya
    if(close_requested)
    {
        SDL_DestroyRenderer(*rend1);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
}
