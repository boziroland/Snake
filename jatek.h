#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

extern bool close_requested;
extern int eger;

//láncolt lista
typedef struct kigyo
{
    SDL_Rect fej;
    struct kigyo *kovnode;
} kigyo;

typedef struct
{
    int egerx,egery;
} mousepos;

typedef struct
{
    int x,y;
} spawnpos;

typedef struct
{
    int r;
    int g;
    int b;
} TextColor;

typedef struct
{
    int x_pos;
    int y_pos;
    int h;
    int w;

} RectData;

typedef struct
{
    TextColor Color;
    RectData Rect;

} StructForTTF;

bool teglalapban(SDL_Rect *menupont, int x, int y);
void freeList(kigyo** head);
void TTFCreateAndPrint(SDL_Renderer **rend1,char *StrToPrint,int SizeofFont,StructForTTF StructOfAll);
void getInput(char *nev, int maxhossz);
void Ki_Nyert(SDL_Renderer **rend1,kigyo *kigyo1,kigyo *kigyo2);
void Nyert_e(SDL_Renderer **rend1,int pontszam);
void GameOver(SDL_Renderer **rend1, int pontszam,bool* backtomenu,kigyo *kigyo1,kigyo *kigyo2);
bool check4Clash(kigyo *kigyo1,kigyo *kigyo2);
bool SnakeBodyLogic(bool *start,int spawn,kigyo **head,int* irany,int *merre,spawnpos pos);
void spawnApple(kigyo *kigyo1,kigyo* kigyo2);
bool **CreateGame();
void DrawPoints(SDL_Renderer **rend1,SDL_Surface *surface,SDL_Texture *texture,SDL_Color pontok,TTF_Font *font,char* osszpont);
void DrawOnScreen(bool **palya,SDL_Renderer **rend1,SDL_Event event,SDL_Surface *surface,SDL_Texture *texture,SDL_Color pontok,TTF_Font *font,char* osszpont,kigyo **headnr1,kigyo **headnr2);
void input(SDL_Event event,int *irany);
void inputp2(SDL_Event event, int *irany);


void egyjatekos(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags);
void ketjatekos(SDL_Window *win, SDL_Renderer **rend1,Uint32 *render_flags);
