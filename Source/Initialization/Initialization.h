#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define MaxSprites 200
#define MaxInstances 100
#define MaxSongs 4
#define MaxSounds 10
#define KeyNumber 14
#define MatrixSpace 200 //space between boxes of the matrixes
#define MaxDataSaves 7

typedef struct{
    SDL_Texture* Texture;
    int Width;          //size of the whole file in pixels
    int Height;
    int FrameWidth;     //size of each rectangle
    int FrameHeight;
    int FrameNumber;    //number of frames
    int speed;

    int FramesToTheLeft;
}Sprite;

typedef struct{
    int ID;
    char name[20];
    float x;
    float y;
    //int* IDList;
    Sprite* sprite;
    SDL_Rect rectangle1;    //sprite rectangle
    SDL_Rect rectangle2;    //position in window rectangle
    int data[20];
    float floatdata[20];
    char dataname[20];
}Instance;

typedef struct{
    char name[20];
    int race; // 1: human 2:Rabbitman 3:dwarf
    int CharacterClass; //1: warrior 2:archer 3:mage
    int lvl;
    int exp;
    int gold;


    int maxhp;
    int maxenergy;
    int hp;
    int def;
    int atk;
    int atkspec;
    int energy;

    float movspeed;
    float atkspeed;

    int inv[20];
    int battle;
}Save;

typedef struct{
    SDL_Window* MainWindow;
    SDL_Renderer* MainRender;

    Instance* InstanceList;
    Sprite* SpriteList;
    Mix_Music** SongList;
    Mix_Chunk** SoundList;

    char PreviousKey[KeyNumber];
    char FrameKey[KeyNumber];
    int menu;
    int ins_count;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    Save saved_data[MaxDataSaves];
}GlobalVariables;

/*		INIZIALIZACION DE ESTRUCTURAS		*/
SDL_Window* CreatingWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT){

    SDL_Window* win=NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        win = NULL;
    }
    else
    {
    	printf(" Done!\n");
    	printf("Creating a window...");
        //Create window
        win = SDL_CreateWindow( "Dragons & Knights", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        	SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( win == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else{
        	 SDL_Surface* iconsurface=SDL_LoadBMP("media/icon.bmp");
        	SDL_SetWindowIcon(win,iconsurface);
        	SDL_FreeSurface(iconsurface);
        	iconsurface=NULL;
        	printf(" Done!\n");
        }
    }

    return win;
}
void createrectangle(SDL_Rect* rectangle, int xx, int yy, int ww, int hh){
	rectangle->x=xx;
	rectangle->y=yy;
	rectangle->w=ww;
	rectangle->h=hh;
}
void copyrectangle(SDL_Rect* recttocopy,SDL_Rect* recttobecopied){
	recttobecopied->x=recttocopy->x;
	recttobecopied->y=recttocopy->y;
	recttobecopied->w=recttocopy->w;
	recttobecopied->h=recttocopy->h;
}
void InitializeSprite(Sprite* sprite){
	sprite->Texture=NULL;
	sprite->Width=0;			//size of the whole file in pixels
	sprite->Height=0;
	sprite->FrameWidth=0;	//size of each rectangle
	sprite->FrameHeight=0;
	sprite->FrameNumber=0; 	//number of frames
	sprite->speed=0;
}
void InitializeInstance(Instance* ins){
	ins->name[0]=0;
	ins->ID=-1;
	ins->x=0;
	ins->y=0;
}
void InitializeKeys(char* array,int n){ //puntero a array - n: numero de elemntos en el array
	int i;
	for (i=0;i<n;++i)
		*(array+i)=0x8;
}
/*      SDL TEXTURES        */
/*
SDL_Surface* optimizedsurface(SDL_Surface* mainsurface,const char*impath ){
    SDL_Surface* optimized_surf=NULL;
    SDL_Surface* surface=SDL_LoadBMP(impath);
    if(surface==NULL)
        printf("error: %s",SDL_GetError());
    else{
        optimized_surf=SDL_ConvertSurface(surface,mainsurface->format,0);
        if (optimized_surf==NULL)
            printf("error: %s",SDL_GetError());
    }
    closing_surface(surface);
    return optimized_surf;
}
*/
SDL_Surface* LoadTexture(SDL_Renderer* MainRender,const char* impath){
    SDL_Texture* newtexture =NULL;
    SDL_Surface* surface=SDL_LoadBMP(impath);
    if(surface==NULL)
        printf("error:%s",SDL_GetError());
    else{
        newtexture=SDL_CreateTextureFromSurface(MainRender,surface);
        if (newtexture==NULL)
            printf("\nerror loading texture %s: %s",impath,SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return newtexture;
}

SDL_Texture* CreateTextureFont(SDL_Renderer* MainRender,SDL_Color* color,const char*text,int ptsize,const char*impath){
    TTF_Font*font;
    font=TTF_OpenFont(impath,ptsize);
    if (font==NULL){ //ptsize es el size del font (size de la letra)
        printf("\n");
        printf(TTF_GetError());
        }
    SDL_Surface*surface;
    surface=TTF_RenderText_Solid(font,text,*color);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(MainRender,surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}
/*      Sprites         */
void CreateAnimatedSprite(SDL_Renderer* MainRender,Sprite* spr,const char* impath,int speed,int frames,int framestoleft){
    spr->Texture=LoadTexture(MainRender,impath);
    SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));

    spr->FrameWidth=(spr->Width)/framestoleft;

    int SquaresHeight;

    if (frames>framestoleft)
        SquaresHeight=spr->Height/((frames/framestoleft)+1);
    else
        SquaresHeight=spr->Height;

    spr->FrameHeight=SquaresHeight;
    spr->FrameNumber=frames;
    spr->speed=speed;
    spr->FramesToTheLeft=framestoleft;
}
void CreateNonAnimatedSprite(SDL_Renderer* MainRender,Sprite* spr,const char* impath){
    spr->Texture=LoadTexture(MainRender,impath);
    SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
    spr->FrameWidth=(spr->Width);
    spr->FrameHeight=(spr->Height);
    spr->FrameNumber=1;
    spr->speed=0;
}
void CreateNonAnimatedFont(SDL_Renderer* MainRender,SDL_Color* color,Sprite* spr,char* text,const char* impath,int size){
    spr->Texture=CreateTextureFont(MainRender,color,text,size,impath);
    SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
    spr->FrameWidth=spr->Width;
    spr->FrameHeight=spr->Height;
    spr->FrameNumber=1;
    spr->speed=0;
}