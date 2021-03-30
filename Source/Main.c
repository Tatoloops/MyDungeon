//Using SDL and standard IO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Initialization.h"


#define MaxSprites 200
#define MaxInstances 200
#define MaxSongs 10
#define MaxSounds 30
#define KeyNumber 14
#define MatrixSpace 200 //space between boxes of the matrixes
//max per room


typedef struct{
	SDL_Texture* Texture;
	int Width;			//size of the whole file in pixels
	int Height;
	int FrameWidth;		//size of each rectangle
	int FrameHeight;
	int FrameNumber; 	//number of frames
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
	SDL_Rect rectangle1; 	//sprite rectangle
	SDL_Rect rectangle2;	//position in window rectangle
	int data[20];
	float floatdata[20];
	char dataname[20];
}Instance;

typedef struct{
	char name[20];
	int race; // 1: human 2:Rabbitman 3:dwarf
	int class; //1: warrior 2:archer 3:mage
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





/* 		CODIGOS DE CARGA MULTIMEDIA 		 */
//sub codigos de carga de archivos multimedia...

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

SDL_Surface* LoadTexture(SDL_Renderer* redertarget,const char* impath){
	SDL_Texture* newtexture =NULL;
	SDL_Surface* surface=SDL_LoadBMP(impath);
	if(surface==NULL)
		printf("error:%s",SDL_GetError());
	else{
		newtexture=SDL_CreateTextureFromSurface(redertarget,surface);
		if (newtexture==NULL)
			printf("error loading texture %s: %s",impath,SDL_GetError());
	}
	SDL_FreeSurface(surface);
	return newtexture;
}
SDL_Texture* CreateTextureFont(SDL_Renderer* renderer,SDL_Color* color,Sprite* SpriteList,
	const char*text,int ptsize,const char*impath){

	TTF_Font*font=TTF_OpenFont(impath,ptsize); //ptsize es el size del font (size de la letra)
	SDL_Surface*surface=TTF_RenderText_Solid(font,text,*color);
	SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return texture;
}
void CreateAnimatedSprite(SDL_Renderer* rendertarget,Sprite* spr,const char* impath,int speed,int frames,int framestoleft){
	spr->Texture=LoadTexture(rendertarget,impath);
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
void CreateNonAnimatedSprite(SDL_Renderer* rendertarget,Sprite* spr,const char* impath){
	spr->Texture=LoadTexture(rendertarget,impath);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
	spr->FrameWidth=(spr->Width);
	spr->FrameHeight=(spr->Height);
	spr->FrameNumber=1;
	spr->speed=0;
}
void CreateNonAnimatedFont(SDL_Renderer* rendertarget,SDL_Color* color,Sprite* spr,char* text,const char* impath,int size){
	spr->Texture=CreateTextureFont(rendertarget,color,spr,text,size,impath);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
	spr->FrameWidth=spr->Width;
	spr->FrameHeight=spr->Height;
	spr->FrameNumber=1;
	spr->speed=0;
}
void SaveSlot(Save* save_data,int slot){
	short i;
	short j;
	for (i=0;i<20;++i){
		(save_data+slot)->name[i]=(save_data)->name[i];
	}
	(save_data+slot)->race=(save_data->race);
	(save_data+slot)->class=(save_data->class);
	(save_data+slot)->lvl=(save_data->lvl);
	(save_data+slot)->exp=(save_data->exp);
	(save_data+slot)->gold=(save_data->gold);

	(save_data+slot)->maxhp=(save_data->maxhp);
	(save_data+slot)->maxenergy=(save_data->maxenergy);
	(save_data+slot)->hp=(save_data->hp);
	(save_data+slot)->def=(save_data->def);
	(save_data+slot)->atk=(save_data->atk);
	(save_data+slot)->atkspec=(save_data->atkspec);
	(save_data+slot)->energy=(save_data->energy);
	(save_data+slot)->movspeed=(save_data->movspeed);
	(save_data+slot)->atkspeed=(save_data->atkspeed);
	for (i=0;i<20;++i){
		(save_data+slot)->inv[i]=(save_data)->inv[i];
	}

	FILE * save;
	if ((save = fopen("save.dat", "w")) == NULL ){
        printf("File could not be opened.\n");
    }
 	else{
 		for(i=1;i<7;++i){
 			fprintf(save, "%s\n",(save_data+i)->name);
 			fprintf(save, "%d\n",(save_data+i)->race);
 			fprintf(save, "%d\n",(save_data+i)->class);
 			fprintf(save, "%d\n",(save_data+i)->lvl);
 			fprintf(save, "%d\n",(save_data+i)->exp);
 			fprintf(save, "%d\n",(save_data+i)->gold);
 			fprintf(save, "%d\n",(save_data+i)->maxhp);
 			fprintf(save, "%d\n",(save_data+i)->maxenergy);
 			fprintf(save, "%d\n",(save_data+i)->hp);
 			fprintf(save, "%d\n",(save_data+i)->def);
 			fprintf(save, "%d\n",(save_data+i)->atk);
 			fprintf(save, "%d\n",(save_data+i)->atkspec);
 			fprintf(save, "%d\n",(save_data+i)->energy);
 			fprintf(save, "%f\n",(save_data+i)->movspeed);
 			fprintf(save, "%f\n",(save_data+i)->atkspeed);
 			for (j=0;j<20;++j){
				fprintf(save, "%d ",(save_data+i)->inv[j]);
			}
 		}
 	}
}
void LoadSlot(Save* save_data,int slot){
	short i;
	(save_data->race)=(save_data+slot)->race;
	(save_data->class)=(save_data+slot)->class;
	(save_data->lvl)=(save_data+slot)->lvl;
	(save_data->exp)=(save_data+slot)->exp;
	(save_data->gold)=(save_data+slot)->gold;
	(save_data->maxhp)=(save_data+slot)->maxhp;
	(save_data->maxenergy)=(save_data+slot)->maxenergy;
	(save_data->hp)=(save_data+slot)->hp;
	(save_data->def)=(save_data+slot)->def;
	(save_data->atk)=(save_data+slot)->atk;
	(save_data->atkspec)=(save_data+slot)->atkspec;
	(save_data->energy)=(save_data+slot)->energy;
	(save_data->movspeed)=(save_data+slot)->movspeed;
	(save_data->atkspeed)=(save_data+slot)->atkspeed;
	(save_data->race)=(save_data+slot)->race;
	for (i=0;i<20;++i){
		(save_data)->inv[i]=(save_data+slot)->inv[i];
	}
}
void CreateCharacter(Save* saved_data,int class,int race){

	//race  1: human 2:Rabbitman 3:dwarf
	//class 1: warrior 2:archer 3:mage

	short i;
	//
	saved_data->lvl=1;
	saved_data->exp=0;
	saved_data->gold=50;
	saved_data->class=class;
	saved_data->race=race;

	for(i=0;i<20;++i)
		saved_data->inv[i]=0;
	//stats por raza
	if (race==1){		//HUMAN
		if (class==1){ //warrior
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=10;
			saved_data->atkspec=12;

			saved_data->movspeed=1.5;
			saved_data->atkspeed=35;
		}
		else if (class==2){ //archer
			saved_data->maxhp=17;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=1;
			saved_data->atk=3;
			saved_data->atkspec=10;

			saved_data->movspeed=2; saved_data->atkspeed=35;
		}
		else if (class==3){ //mage
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=8;
			saved_data->atkspec=16;

			saved_data->movspeed=1.5;
			saved_data->atkspeed=35;
		}
	}
	else if (race==2){	//Rabbitman
		if (class==1){ //warrior
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
		else if (class==2){ //archer
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
		else if (class==3){ //mage
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
	}
	else if (race==3){	//dwarf
		if (class==1){ //warrior
			saved_data->maxhp=35;
			saved_data->maxenergy=8;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=3;
			saved_data->atk=15;
			saved_data->atkspec=20;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
		else if (class==2){ //archer
			saved_data->maxhp=22;
			saved_data->maxenergy=8;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=10;
			saved_data->atkspec=14;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
		else if (class==3){ //mage
			saved_data->maxhp=25;
			saved_data->maxenergy=12;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=12;
			saved_data->atkspec=22;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
	}
}
void levelup(Save* saved_data){
	if (saved_data->race==1){
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=3;
		saved_data->maxenergy+=2;
		saved_data->def+=1;
		saved_data->atk+=1;
		saved_data->atkspec+=2;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.05;
		saved_data->atkspeed-=2;
	}
	else if (saved_data->race==2){
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=1;
		saved_data->maxenergy+=1;
		saved_data->def+=0;
		saved_data->atk+=1;
		saved_data->atkspec+=1;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.25;
		saved_data->atkspeed-=3;
	}
	else{
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=5;
		saved_data->maxenergy+=5;
		saved_data->def+=1;
		saved_data->atk+=3;
		saved_data->atkspec+=2;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.02;
		saved_data->atkspeed-=1;
	}
	printf("level up, new stats:\n Level:%d \n HP: %d \n Energy: %d \n  Defense: %d \n Atack: %d \n  Movement speed: %f \n Atack speed: %f \n",
		saved_data->lvl,
		saved_data->maxhp,
		saved_data->maxenergy,
		saved_data->def,
		saved_data->atk,
		saved_data->movspeed,
		saved_data->atkspeed);
	printf("%d\n",saved_data->inv[0]);
}

//Object Load
void Objectload_000(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	srand(time(NULL));
	short i;

	//sprite 000.
	SDL_Color color0={.r=0,.g=0,.b=0,.a=255}; // color de los textos "start" "quit"
	i=rand()%14;
	if(i==0) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (1).bmp");
	else if(i==1) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (2).bmp");
	else if(i==2) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (3).bmp");
	else if(i==3) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (4).bmp");
	else if(i==4) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (5).bmp");
	else if(i==5) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (6).bmp");
	else if(i==6) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (7).bmp");
	else if(i==7) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (8).bmp");
	else if(i==8) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (9).bmp");
	else if(i==9) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (10).bmp");
	else if(i==10) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (11).bmp");
	else if(i==11) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (12).bmp");
	else if(i==12) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (13).bmp");
	else (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Warrior (14).bmp");

	SDL_QueryTexture((SpriteList+0)->Texture,NULL,NULL,&((SpriteList+0)->Width),&((SpriteList+0)->Height));
	(SpriteList+0)->FrameWidth=SCREEN_WIDTH;
	(SpriteList+0)->FrameHeight=SCREEN_HEIGHT;
	(SpriteList+0)->FrameNumber=1;
	(SpriteList+0)->speed=0;

	//sprite 001.
	(SpriteList+1)->Texture=LoadTexture(rendertarget,"media/items/companion.bmp");
	SDL_QueryTexture((SpriteList+1)->Texture,NULL,NULL,&((SpriteList+1)->Width),&((SpriteList+1)->Height));
	(SpriteList+1)->FrameWidth=(SpriteList+1)->Width;
	(SpriteList+1)->FrameHeight=(SpriteList+1)->Height;
	(SpriteList+1)->FrameNumber=1;
	(SpriteList+1)->speed=0;

	//sprite002
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+2,"Start","fonts/Amatic-Bold.ttf",60);
	//sprite003
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+3,"Quit","fonts/Amatic-Bold.ttf",60);

	//SOUND 000.
	*(SoundList+0)=Mix_LoadWAV("media/sounds/000.wav");
	if(*(SoundList+0)==NULL) printf("could not load sound: %s",SDL_GetError());
	//SOUND 001.
	*(SoundList+1)=Mix_LoadWAV("media/sounds/001.wav");
	if(*(SoundList+1)==NULL) printf("could not load sound: %s",SDL_GetError());

	//Music 0
	i=rand()%3;
	if(i==0) *(SongList+0)=Mix_LoadMUS("media/music/000.mp3");
	if(i==1) *(SongList+0)=Mix_LoadMUS("media/music/001.mp3");
	if(i==2) *(SongList+0)=Mix_LoadMUS("media/music/002.mp3");
	if(*(SongList+0)==NULL) printf("could not load song: %s",SDL_GetError());
	return;
}
void Objectload_001(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){

	//sprite000
	(SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/100.bmp");

	SDL_QueryTexture((SpriteList+0)->Texture,NULL,NULL,&((SpriteList+0)->Width),&((SpriteList+0)->Height));

	(SpriteList+0)->FrameWidth=SCREEN_WIDTH;
	(SpriteList+0)->FrameHeight=SCREEN_HEIGHT;
	(SpriteList+0)->FrameNumber=1;
	(SpriteList+0)->speed=0;

	//font colors & size
	SDL_Color color0={.r=150,.g=20,.b=20,.a=210};
	SDL_Color color1={.r=255,.g=255,.b=255,.a=255};
	SDL_Color color2={.r=150,.g=100,.b=100,.a=180};
	int psize=60;

	//color1
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+1,"Race :","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+2,"Human","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+3,"Rabbitman","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+4,"Frogman","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+5,"Class :","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+6,"Warrior","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+7,"Archer","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+8,"Mage","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+9,"Start","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+10,"Back","fonts/Amatic-Bold.ttf",psize);

	//color2
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+11,"Race :","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+12,"Human","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+13,"Rabbitman","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+14,"Frogman","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+15,"Class :","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+16,"Warrior","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+17,"Archer","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+18,"Mage","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+19,"Start","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+20,"Back","fonts/Amatic-Bold.ttf",psize);
	//stats menu
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+21,"Stats","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+22,"HP","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+23,"ATK","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+24,"DEF","fonts/Amatic-Bold.ttf",psize);
	//numbers
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+25,"0","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+26,"1","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+27,"2","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+28,"3","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+29,"4","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+30,"5","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+31,"6","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+32,"7","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+33,"8","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+34,"9","fonts/Amatic-Bold.ttf",psize);

	//menu principal
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+35,"New Character","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+36,"Save Character","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+37,"Load Character","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+38,"New Character","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+39,"Save Character","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+40,"Load Character","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+41,"Save Character","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+42,"Load Character","fonts/Amatic-Bold.ttf",psize);

	//sub menu de slots (save or load)
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+43,"Slot 1","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+44,"Slot 2","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+45,"Slot 3","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+46,"Slot 4","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+47,"Slot 5","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+48,"Slot 6","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+49,"Slot 1","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+50,"Slot 2","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+51,"Slot 3","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+52,"Slot 4","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+53,"Slot 5","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color1,SpriteList+54,"Slot 6","fonts/Amatic-Bold.ttf",psize);

	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+55,"Slot 1","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+56,"Slot 2","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+57,"Slot 3","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+58,"Slot 4","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+59,"Slot 5","fonts/Amatic-Bold.ttf",psize);
	CreateNonAnimatedFont(rendertarget,&color2,SpriteList+60,"Slot 6","fonts/Amatic-Bold.ttf",psize);
	//Song 000
	*(SongList+0)=Mix_LoadMUS("media/music/100.mp3");
	if(*(SongList+0)==NULL) printf("could not load song: %s",SDL_GetError());
}
void Objectload_002(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	srand(time(NULL));
	short i;
	//sprite 000
	SDL_Color color0={.r=255,.g=255,.b=255,.a=255};
	i=rand()%2;
	if(i==0) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Store (1).bmp");
	else if(i==1) (SpriteList+0)->Texture=LoadTexture(rendertarget,"media/backgrounds/Store (2).bmp");
	SDL_QueryTexture((SpriteList+0)->Texture,NULL,NULL,&((SpriteList+0)->Width),&((SpriteList+0)->Height));
	//(SpriteList+0)->Width=SCREEN_WIDTH;
	//(SpriteList+0)->Height=SCREEN_HEIGHT;
	(SpriteList+0)->FrameWidth=SCREEN_WIDTH;
	(SpriteList+0)->FrameHeight=SCREEN_HEIGHT;
	(SpriteList+0)->FrameNumber=1;
	(SpriteList+0)->speed=0;
	if ((SpriteList+0)->Texture==NULL)
		printf("couldn't load background image %s",SDL_GetError);
	//sprite 001.
	(SpriteList+1)->Texture=LoadTexture(rendertarget,"media/items/coin.bmp");
	SDL_QueryTexture((SpriteList+1)->Texture,NULL,NULL,&((SpriteList+1)->Width),&((SpriteList+1)->Height));
	//(SpriteList+1)->Width=SCREEN_WIDTH;
	//(SpriteList+1)->Height=SCREEN_HEIGHT;
	(SpriteList+1)->FrameWidth=(SpriteList+1)->Width;
	(SpriteList+1)->FrameHeight=(SpriteList+1)->Height;
	(SpriteList+1)->FrameNumber=1;
	(SpriteList+1)->speed=0;
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+2,"Items","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+3,"Stats","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+4,"Continue","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+5,"Back","fonts/Amatic-Bold.ttf",60);
	(SpriteList+6)->Texture=LoadTexture(rendertarget,"media/items/itemmenu.bmp");
	(SpriteList+7)->Texture=LoadTexture(rendertarget,"media/items/potion1.bmp");
	(SpriteList+8)->Texture=LoadTexture(rendertarget,"media/items/potion2.bmp");
	color0.r=0;
	color0.g=0;
	color0.b=0;
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+9,"health potion","fonts/Amatic-Bold.ttf",50);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+10,"mana potion","fonts/Amatic-Bold.ttf",50);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+11,"Health","fonts/Amatic-Bold.ttf",50);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+12,"Defense","fonts/Amatic-Bold.ttf",50);
	CreateNonAnimatedFont(rendertarget,&color0,SpriteList+13,"Attack","fonts/Amatic-Bold.ttf",50);
	//SOUND 000.
	*(SoundList+0)=Mix_LoadWAV("media/sounds/000.wav");
	if(*(SoundList+0)==NULL) printf("could not load sound: %s",SDL_GetError());
	*(SoundList+1)=Mix_LoadWAV("media/sounds/001.wav");
	if(*(SoundList+1)==NULL) printf("could not load sound: %s",SDL_GetError());
	//Music 0
	i=rand()%2;
	if(i==0) *(SongList+0)=Mix_LoadMUS("media/music/200.mp3");
	if(i==1) *(SongList+0)=Mix_LoadMUS("media/music/201.mp3");
	if(*(SongList+0)==NULL) printf("could not load song: %s",SDL_GetError());
}
void Objectload_004(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	//sprites
	CreateNonAnimatedSprite(rendertarget,SpriteList+0,"media/backgrounds/400.bmp"); //background
	CreateNonAnimatedSprite(rendertarget,SpriteList+1,"media/characters/400.bmp"); //Enemy spot
	CreateNonAnimatedSprite(rendertarget,SpriteList+2,"media/characters/400.bmp"); //Player spot

	SDL_Color Color1={.r=255,.g=255,.b=255,.a=255};
	SDL_Color Color2={.r=255,.g=0,.b=100,.a=255};

	CreateNonAnimatedFont(rendertarget,&Color1,SpriteList+3,"Back to the Bazar","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&Color1,SpriteList+4,"Next Battle","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&Color1,SpriteList+5,"Retry","fonts/Amatic-Bold.ttf",60);

	CreateNonAnimatedFont(rendertarget,&Color2,SpriteList+6,"Back to the Bazar","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&Color2,SpriteList+7,"Next Battle","fonts/Amatic-Bold.ttf",60);
	CreateNonAnimatedFont(rendertarget,&Color2,SpriteList+8,"Retry","fonts/Amatic-Bold.ttf",60);

	CreateNonAnimatedFont(rendertarget,&Color2,SpriteList+9,"YOU WIN !","fonts/Arizonia-Regular.ttf",72);
	CreateNonAnimatedFont(rendertarget,&Color2,SpriteList+10,"You're dead...","fonts/Arizonia-Regular.ttf",72);


	*(SongList+0)=Mix_LoadMUS("media/music/400.mp3");
	if(*(SongList+0)==NULL) printf("could not load song: %s",SDL_GetError());
	return;
}
void Objectload_005(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	int spr_pos=11;
	//sprites
	if(saved_data->race==1){
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+0,"media/characters/player103 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+1,"media/characters/player103 (2).bmp"); //down
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+2,"media/characters/player103 (3).bmp"); //left
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+3,"media/characters/player103 (4).bmp"); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+4,"media/characters/player103 (5).bmp",10,4,8); //muerte
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+5,"media/characters/player103 (6).bmp",10,4,8); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+6,"media/characters/player103 (7).bmp",10,4,8); //right
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+7,"media/characters/player103 (8).bmp",10,4,8); //down
	}
	else if(saved_data->race==2){
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+0,"media/characters/player201 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+1,"media/characters/player201 (2).bmp"); //down
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+2,"media/characters/player201 (3).bmp"); //left
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+3,"media/characters/player201 (4).bmp"); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+4,"media/characters/player201 (5).bmp",10,4,4); //muerte
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+5,"media/characters/player201 (6).bmp",10,4,4); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+6,"media/characters/player201 (7).bmp",10,2,4); //right
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+7,"media/characters/player201 (8).bmp",10,2,4); //down
	}
	else if(saved_data->race==3){
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+0,"media/characters/player303 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+1,"media/characters/player303 (2).bmp"); //down
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+2,"media/characters/player303 (3).bmp"); //left
			CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+3,"media/characters/player303 (4).bmp"); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+4,"media/characters/player303 (5).bmp",10,7,8); //muerte
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+5,"media/characters/player303 (6).bmp",10,7,8); //up
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+6,"media/characters/player303 (7).bmp",10,7,8); //right
			CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+7,"media/characters/player303 (8).bmp",10,7,8); //down
	}
	return;
}//Player
void Objectload_006(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	int spr_pos=31; // 7 sprites

	//sprites
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+0,"media/characters/500.bmp",10,20,8); //Creation
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+1,"media/characters/501.bmp",15,4,8); //Idle
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+2,"media/characters/502.bmp",15,4,8); //walking
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+3,"media/characters/503.bmp",15,3,8); //jump
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+4,"media/characters/504.bmp",15,5,8); //dead
	//free media
	SDL_DestroyTexture((SpriteList+1)->Texture);
	//here we destroy the media, because we are changing another Object's media files
	CreateAnimatedSprite(rendertarget,SpriteList+1,"media/characters/505.bmp",5,3,8); //Enemy spot
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+6,"media/characters/506.bmp",15,3,8); //floor2

	return;
}
void Objectload_007(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	int spr_pos=28; // 1 sprites
	//sprites
	CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+0,"media/characters/507.bmp",10,19,8); //Creation


	return;
}
void Objectload_008(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	int spr_pos=11; // 1 sprites
	//sprites
	if (saved_data->race==1) 		//human mage
		CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player103 (9).bmp",10,4,4); //Creation
	else if (saved_data->race==2) 	//Rabbitman mage
		CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player203 (9).bmp",10,4,4); //Creation
	else 							//Frogman mage
		CreateAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player303 (9).bmp",10,4,4); //Creation
	return;
}
void Objectload_009(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){//leaf enemy

	int spr_pos=12; // 1 sprites
	//sprites
	if (saved_data->race==1) 		//human archer
		CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	else if (saved_data->race==2) 	//Rabbitman archer
		CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	else 							//Frogman archer
		CreateNonAnimatedSprite(rendertarget,SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	return;
}

/*		CODIGOS DE DESTRUCCION		*/
void InstanceDestroy(SDL_Renderer* rendertarget,Instance* InstanceToDestroy,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	InstanceToDestroy->ID=-1;
	short i=0;
	short j=0;
	int thisID;
	while (1) {
		thisID=(InstanceList+i)->ID;
		if(thisID<0){
			--*ins_count;
			(InstanceList+i)->ID=(InstanceList+*ins_count)->ID;
			(InstanceList+i)->x=(InstanceList+*ins_count)->x;
			(InstanceList+i)->y=(InstanceList+*ins_count)->y;
			(InstanceList+i)->sprite=(InstanceList+*ins_count)->sprite;
			copyrectangle(&(InstanceList+*ins_count)->rectangle1,&(InstanceList+i)->rectangle1);
			copyrectangle(&(InstanceList+*ins_count)->rectangle2,&(InstanceList+i)->rectangle2);
			for(j=0;j<20;++j){
				(InstanceList+i)->data[j]=(InstanceList+*ins_count)->data[j];
				(InstanceList+i)->floatdata[j]=(InstanceList+*ins_count)->floatdata[j];
				(InstanceList+i)->dataname[j]=(InstanceList+*ins_count)->dataname[j];
			}
			(InstanceList+*ins_count)->ID=-1;
			return;
		}
		++i;
	}
}



/* 		CODIGOS DE CREACION 		*/
void InstanceCreationCode_000(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1
	(InstanceList+(*ins_count))->ID =000;
	(InstanceList+(*ins_count))->x=0;
	(InstanceList+(*ins_count))->y=0;
	(InstanceList+(*ins_count))->sprite=NULL;
	(InstanceList+(*ins_count))->data[0]=1; // 1 button on start. 2 button on quit
	(InstanceList+(*ins_count))->data[1]=255; // timer
	Mix_PlayMusic(*(SongList+0),-1);
	++(*ins_count);

}
void InstanceCreationCode_001(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1

	(InstanceList+(*ins_count))->ID =001;
	(InstanceList+(*ins_count))->x=0;
	(InstanceList+(*ins_count))->y=0;
	(InstanceList+(*ins_count))->sprite=NULL;
	(InstanceList+(*ins_count))->data[0]=1; // submenu 1 button on race. 2 button on class. 3 start. 4 quit.
	(InstanceList+(*ins_count))->data[1]=1; // race: 1=human. 2=Frogman. 3=Rabbitman.
	(InstanceList+(*ins_count))->data[2]=1;	//class: 1=class1 2=class2 3=class3.
	(InstanceList+(*ins_count))->data[3]=255;	//timer
	(InstanceList+(*ins_count))->data[4]=1; //menu principal


	Mix_PlayMusic(*(SongList+0),-1);
	++(*ins_count);
}
void InstanceCreationCode_002(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1
	(InstanceList+(*ins_count))->ID =002;
	(InstanceList+(*ins_count))->x=0;
	(InstanceList+(*ins_count))->y=0;
	(InstanceList+(*ins_count))->sprite=NULL;
	(InstanceList+(*ins_count))->data[0]=1; // 1 button on items. 2 button on stats .3 button on back
	(InstanceList+(*ins_count))->data[1]=255; // timer
	Mix_PlayMusic(*(SongList+0),-1);
	++(*ins_count);
}
void InstanceCreationCode_004(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1
	(InstanceList+(*ins_count))->ID =004;
	(InstanceList+(*ins_count))->x=SCREEN_WIDTH/2;
	(InstanceList+(*ins_count))->y=SCREEN_HEIGHT/2;
	(InstanceList+(*ins_count))->sprite=NULL;
	(InstanceList+(*ins_count))->data[0]=0;
	(InstanceList+(*ins_count))->data[1]=0;  //matrix  de datas: 	1 - 2 - 3
	(InstanceList+(*ins_count))->data[2]=0; //						4 - 5 - 6
	(InstanceList+(*ins_count))->data[3]=0; //						7 - 8 - 9
	(InstanceList+(*ins_count))->data[4]=0;
	(InstanceList+(*ins_count))->data[5]=0;
	(InstanceList+(*ins_count))->data[6]=0;
	(InstanceList+(*ins_count))->data[7]=0;
	(InstanceList+(*ins_count))->data[8]=0;
	(InstanceList+(*ins_count))->data[9]=0;
	(InstanceList+(*ins_count))->data[10]=0;
	(InstanceList+(*ins_count))->data[11]=0; //contador de frame de animacion 1
	(InstanceList+(*ins_count))->data[12]=0;//contador de avance de frame de animacion 1
	(InstanceList+(*ins_count))->data[13]=0; //win por lose
	(InstanceList+(*ins_count))->data[19]=100; //wait


	Mix_PlayMusic(*(SongList+0),-1);
	++(*ins_count);

} // battlefield
void InstanceCreationCode_005(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1
	int spr_pos=11;

	(InstanceList+(*ins_count))->ID =005;
	(InstanceList+(*ins_count))->sprite=SpriteList+spr_pos+1;
	(InstanceList+(*ins_count))->x=SCREEN_WIDTH/2-(InstanceList+(*ins_count))->sprite->FrameWidth/2;
	(InstanceList+(*ins_count))->y=SCREEN_HEIGHT/2+MatrixSpace-(InstanceList+(*ins_count))->sprite->FrameHeight/2;


	createrectangle(&((InstanceList+(*ins_count))->rectangle1),0,0,(InstanceList+(*ins_count))->sprite->FrameWidth,
		(InstanceList+(*ins_count))->sprite->FrameHeight);
	createrectangle(&((InstanceList+(*ins_count))->rectangle2),(InstanceList+(*ins_count))->x
		,(InstanceList+(*ins_count))->y,(InstanceList+(*ins_count))->sprite->FrameWidth,
		(InstanceList+(*ins_count))->sprite->FrameHeight);

	(InstanceList+(*ins_count))->data[0]=8; /*posición en la matriz 	1 - 2 - 3
																		4 - 5 - 6
																		7 - 8 - 9	*/
												//posicion 5 = (SCREEN_WIDTH/2,SCREEN_HEIGHT/2)
	(InstanceList+(*ins_count))->data[1]=0;
	(InstanceList+(*ins_count))->data[2]=0; //contadores de animacion
	(InstanceList+(*ins_count))->data[3]=0;
	(InstanceList+(*ins_count))->data[4]=0; //action
	(InstanceList+(*ins_count))->data[5]=0; //walking count
	(InstanceList+(*ins_count))->data[6]=0;
	if (saved_data->hp>saved_data->maxhp)
		saved_data->hp=saved_data->maxhp;
	(InstanceList+(*ins_count))->data[7]=saved_data->hp; //hp
	(InstanceList+(*ins_count))->data[8]=saved_data->inv[1]; //red potions
	(InstanceList+(*ins_count))->data[9]=saved_data->inv[2]; //blue potions
	(InstanceList+(*ins_count))->data[10]=saved_data->maxenergy; //blue potions


	++(*ins_count);
} //player
void InstanceCreationCode_006(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1

	(InstanceList+(*ins_count))->ID =006;
	(InstanceList+(*ins_count))->sprite=SpriteList+31;
	(InstanceList+(*ins_count))->x=SCREEN_WIDTH/2-(InstanceList+(*ins_count))->sprite->FrameWidth/2;
	(InstanceList+(*ins_count))->y=SCREEN_HEIGHT/2-MatrixSpace-(InstanceList+(*ins_count))->sprite->FrameHeight/2-50;
	createrectangle(&((InstanceList+(*ins_count))->rectangle1),0,0,(InstanceList+(*ins_count))->sprite->FrameWidth,
		(InstanceList+(*ins_count))->sprite->FrameHeight);
	createrectangle(&((InstanceList+(*ins_count))->rectangle2),(InstanceList+(*ins_count))->x
		,(InstanceList+(*ins_count))->y,(InstanceList+(*ins_count))->sprite->FrameWidth,
		(InstanceList+(*ins_count))->sprite->FrameHeight);
	(InstanceList+(*ins_count))->data[0]=2; /*posición en la matriz 	1 - 2 - 3
																		4 - 5 - 6
																		7 - 8 - 9	*/
												//posicion 2 = (SCREEN_WIDTH/2,SCREEN_HEIGHT/2-MatrixSpace)
	((InstanceList+(*ins_count))->data)[1]=0; //timer
	((InstanceList+(*ins_count))->data)[2]=0; //contador de frame de animacion
	((InstanceList+(*ins_count))->data)[3]=0; //contador de avance de frame de animacion
	((InstanceList+(*ins_count))->data)[4]=-1; //movimiento actual: 0:sin movimiento 1:a la izquierda 2:derecha
	((InstanceList+(*ins_count))->data)[5]=150+5*saved_data->lvl; //HP
	((InstanceList+(*ins_count))->data)[6]=0; //is born
	((InstanceList+(*ins_count))->data)[7]=0; //walking count
	((InstanceList+(*ins_count))->data)[8]=150+5*saved_data->lvl; //MAXHP




		++(*ins_count);
} //leaf monster
void InstanceCreationCode_007(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1

	(InstanceList+(*ins_count))->ID =007;
	(InstanceList+(*ins_count))->sprite=SpriteList+28;

	createrectangle(&((InstanceList+(*ins_count))->rectangle1),0,0,(InstanceList+(*ins_count))->sprite->FrameWidth,
	(InstanceList+(*ins_count))->sprite->FrameHeight);

	createrectangle(&((InstanceList+(*ins_count))->rectangle2),(InstanceList+(*ins_count))->x
	,(InstanceList+(*ins_count))->y,(InstanceList+(*ins_count))->sprite->FrameWidth,
	(InstanceList+(*ins_count))->sprite->FrameHeight);

	((InstanceList+(*ins_count))->data)[0]=rand()%5+1; //speed
	((InstanceList+(*ins_count))->data)[1]=7+saved_data->lvl;//damage
	((InstanceList+(*ins_count))->data)[2]=0; 	//frame things

	++(*ins_count);
} //leaf attack
void InstanceCreationCode_008(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1

	(InstanceList+(*ins_count))->ID= 8;
	(InstanceList+(*ins_count))->sprite=SpriteList+21;

	createrectangle(&((InstanceList+(*ins_count))->rectangle1),0,0,(InstanceList+(*ins_count))->sprite->FrameWidth,
	(InstanceList+(*ins_count))->sprite->FrameHeight);

	createrectangle(&((InstanceList+(*ins_count))->rectangle2),(InstanceList+(*ins_count))->x
	,(InstanceList+(*ins_count))->y,(InstanceList+(*ins_count))->sprite->FrameWidth*2,
	(InstanceList+(*ins_count))->sprite->FrameHeight*2);

	((InstanceList+(*ins_count))->data)[0]=2; //speed
	((InstanceList+(*ins_count))->data)[1]=2; //damage
	((InstanceList+(*ins_count))->data)[2]=0;  /*	position	1 - 2 - 3
																4 - 5 - 6
																7 - 8 - 9 	*/

	++(*ins_count);
} //player fireball attack
void InstanceCreationCode_009(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ // main menu 1

	(InstanceList+(*ins_count))->ID= 9;
	(InstanceList+(*ins_count))->sprite=SpriteList+22;

	createrectangle(&((InstanceList+(*ins_count))->rectangle1),0,0,(InstanceList+(*ins_count))->sprite->FrameWidth,
	(InstanceList+(*ins_count))->sprite->FrameHeight);

	createrectangle(&((InstanceList+(*ins_count))->rectangle2),(InstanceList+(*ins_count))->x
	,(InstanceList+(*ins_count))->y,(InstanceList+(*ins_count))->sprite->FrameWidth*2,
	(InstanceList+(*ins_count))->sprite->FrameHeight*2);

	((InstanceList+(*ins_count))->data)[0]=12; //speed
	((InstanceList+(*ins_count))->data)[1]=1; //damage
	((InstanceList+(*ins_count))->data)[2]=0;  /*	position	1 - 2 - 3
																4 - 5 - 6
																7 - 8 - 9 	*/

	++(*ins_count);
} //player arrow attack

/* 			CODIGOS DE ACTUALIZACION POR FRAME						*/
void ActualizacionDeAnimacion(SDL_Rect* rect,Sprite* spr,int* FrameCount,int* ContadorDeAvance){

	++*ContadorDeAvance;
	if (*ContadorDeAvance>spr->speed){
		*ContadorDeAvance=1;
		++*FrameCount;
		if (*FrameCount>spr->FrameNumber-1)
			*FrameCount=0;
	}

	int a=*FrameCount;
	rect->x=(spr->FrameWidth)*a;
	rect->y=0;
	while(a>spr->FramesToTheLeft-1){
		rect->y+=spr->FrameHeight;
		rect->x-=spr->Width;
		a-=spr->FramesToTheLeft;
	}

	return;
}
void InstanceStepCode_000(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	// Object 000 is the first menu that appears on the menu 1.

	SDL_RenderCopy(rendertarget,(SpriteList+0)->Texture,NULL,NULL);
	//take variables
	int settings=((CurrentInstance)->data)[0];
	int timer=((CurrentInstance)->data)[1];
	saved_data->battle=0;
	//control
	/* settings 1: Start button
				2: Quit button
				3: you pressed start button and you are now starting the game
				4: you pressed the quit button and now you are quitting			*/
	if (settings<3){
		if (key[0]&1){
			settings=1;
			Mix_PlayChannel(0,SoundList+0,1);
		}

		else if (key[1]&1) 	{ //press down
			settings=2;
			Mix_PlayChannel(0,SoundList+0,1);
		}
		else if (key[5]&1){
				if (settings==1){
					settings=3;//press x
					Mix_PlayChannel(0,SoundList+1,1);
				}
				else if (settings==2){
					settings=4; //quit
					Mix_PlayChannel(0,SoundList+1,1);
				}
			}
		else if (key[6]&1)	{	//pres c
			if (settings==1){
				settings=2;
				Mix_PlayChannel(0,SoundList+0,1);
			}
			else{
				settings=4;
				Mix_PlayChannel(0,SoundList+1,1);
			}
		}
		else if (key[12]&1)	{ //press esc
			settings=4;
			Mix_PlayChannel(0,SoundList+1,1);
		}
	}
	else if (settings==3){ //start button pressed
		if (timer<=0){
			short i;
			for(i=0;i<7;++i){
			(saved_data+i)->race=0;
			(saved_data+i)->class=0;
			(saved_data+i)->lvl=0;
			}
			*menu=20; //start game
		}
		timer-=10;
	}
	else if (settings==4) {// quit button pressed
		if (timer<=0){
			*menu=0; // quit game
		}
		timer-=10;
	}
	//end control
	SDL_Rect rect1={.x=SCREEN_WIDTH/2-120,.y=(5*SCREEN_HEIGHT)/6,.w=(SpriteList+1)->Width,.h=(SpriteList+1)->Height};
	SDL_Rect rect2={.x=SCREEN_WIDTH/2-60,.y=(4*SCREEN_HEIGHT)/6-20,.w=(SpriteList+2)->Width,.h=(SpriteList+2)->Height};
	SDL_Rect rect3={.x=SCREEN_WIDTH/2-60,.y=(5*SCREEN_HEIGHT)/6-20,.w=(SpriteList+3)->Width,.h=(SpriteList+3)->Height};
	if 		(settings==1 || settings==3) // on start button
		rect1.y=4*((SpriteList+0)->FrameHeight)/6;
	else if (settings==2 || settings==4) // on quit button
		rect1.y=5*((SpriteList+0)->FrameHeight)/6;
	SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	SDL_RenderCopy(rendertarget,(SpriteList+3)->Texture,NULL,&rect3);
	//save changes on used variables
	((CurrentInstance)->data)[0]=settings;
	((CurrentInstance)->data)[1]=timer;
	return;
}//menu principal
void InstanceStepCode_001(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	//menu de elección de personaje
	SDL_RenderCopy(rendertarget,(SpriteList+0)->Texture,NULL,NULL);
	//take variables
	int subsettings=((CurrentInstance)->data)[0];
	int race=((CurrentInstance)->data)[1];
	int class=((CurrentInstance)->data)[2];
	int timer=((CurrentInstance)->data)[3];
	int settings=((CurrentInstance)->data)[4];
	if (settings==1){  //subsetting: 1:new 2:save 3:load
		if(key[0]&1){ //up
			--subsettings;
			if (subsettings<1)
				subsettings=1;
		}
		else if(key[1]&1){ //down
			++subsettings;
			if (subsettings>3)
				subsettings=3;
		}
		else if(key[5]&1){ //enter
			if(subsettings==1){ //enter new character creation
				settings=2;
			}
			else if(subsettings==2){ //character save
				subsettings=1;
				settings=3;
			}
			else if(subsettings==3){ //character load
				subsettings=1;
				settings=4;
			}
		}

	}
	else if(settings==2){ //sub menu de creacion de raza.
		if (subsettings==1){ //race
			if 		(key[2]&1){
				--race;
				if (race<1)
					race=3;
			}
			else if (key[3]&1){
				++race;
				if (race>3)
					race=1;
			}
			else if (key[1]&1){
				subsettings=2;
			}
			else if (key[6]&1){
				subsettings=4;
			}
		}
		else if(subsettings==2){ //class
			if 		(key[2]&1){
				--class;
				if (class<1)
					class=3;
			}
			else if (key[3]&1){
				++class;
				if (class>3)
					class=1;
			}
			else if (key[1]&1){
				subsettings=3;
			}
			else if(key[0]&1){
				subsettings=1;
			}
			else if (key[6]&1){
				subsettings=4;
			}
		}
		else if(subsettings==3){ //start
			if 	(key[2]&1){
				subsettings=4;
			}
			else if(key[0]&1){
				subsettings=2;
			}
			else if (key[5]&1){
				subsettings=5;
			}
			else if (key[6]&1){
				subsettings=4;
			}
		}
		else if (subsettings==4){ //back
			if 	(key[3]&1){
				subsettings=3;
			}
			else if(key[0]&1){
				subsettings=2;
			}
			else if (key[5]&1){
				subsettings=1;
				settings=1;
			}
			else if (key[6]&1){
				subsettings=1;
				settings=1;
			}
		}
		else if(subsettings==5){ //starting
			timer-=10;
			if(timer<=0){
				*menu=30;
				CreateCharacter(saved_data,class,race);
			}
		}
	}
	else if (settings==3){ //sub menu de save de slot
		if (key[0]&1){ //move up
			subsettings-=3;
			if (subsettings<1)
				subsettings+=3;
		}
		else if (key[1]&1){ //move down
			subsettings+=3;
			if (subsettings>6)
				subsettings-=3;
		}
		else if (key[2]&1){ //left
			--subsettings;
			if (subsettings==0 || subsettings==3)
				++subsettings;
		}
		else if (key[3]&1){ //right
			++subsettings;
			if (subsettings==4 || subsettings==7)
				--subsettings;
		}
		else if (key[5]&1){ //select
			if (saved_data->class!=0){
				SaveSlot(saved_data,subsettings);
				subsettings=2;
				settings=1;
			}
		}
		else if (key[6]&1){ //select
			subsettings=2;
			settings=1;
		}
	}
	else{ //load slot
		if (key[0]&1){ //move up
			subsettings-=3;
			if (subsettings<1)
				subsettings+=3;
		}
		else if (key[1]&1){ //move down
			subsettings+=3;
			if (subsettings>6)
				subsettings-=3;
		}
		else if (key[2]&1){ //left
			--subsettings;
			if (subsettings==0 || subsettings==3)
				++subsettings;
		}
		else if (key[3]&1){ //right
			++subsettings;
			if (subsettings==4 || subsettings==7)
				--subsettings;
		}
		else if (key[5]&1){ //select
			if ((saved_data+subsettings)->class!=0){
				LoadSlot(saved_data,subsettings);
				*menu=30;
			}
		}
		else if (key[6]&1){ //back
			subsettings=3;
			settings=1;
		}
	}

	if (settings==1){ //main menu
		SDL_Rect rect1={.x=(SCREEN_WIDTH)/2,.y=(16*SCREEN_HEIGHT)/24,.w=(SpriteList+35)->Width,.h=(SpriteList+35)->Height};
		SDL_Rect rect2={.x=(SCREEN_WIDTH)/2,.y=(18*SCREEN_HEIGHT)/24,.w=(SpriteList+36)->Width,.h=(SpriteList+36)->Height};
		SDL_Rect rect3={.x=(SCREEN_WIDTH)/2,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+37)->Width,.h=(SpriteList+37)->Height};
		if (subsettings==1){
			SDL_RenderCopy(rendertarget,(SpriteList+38)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+36)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+37)->Texture,NULL,&rect3);
		}
		if (subsettings==2){
			SDL_RenderCopy(rendertarget,(SpriteList+35)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+39)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+37)->Texture,NULL,&rect3);
		}
		if (subsettings==3){
			SDL_RenderCopy(rendertarget,(SpriteList+35)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+36)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+40)->Texture,NULL,&rect3);
		}
	}
	else if (settings==2){
		SDL_Rect rect1={.x=(3*SCREEN_WIDTH)/8,.y=(15*SCREEN_HEIGHT)/24,.w=(SpriteList+1)->Width,.h=(SpriteList+1)->Height};
		SDL_Rect rect2={.x=(4*SCREEN_WIDTH)/8,.y=(15*SCREEN_HEIGHT)/24,.w=(SpriteList+2)->Width,.h=(SpriteList+2)->Height};
		SDL_Rect rect3={.x=(3*SCREEN_WIDTH)/8,.y=(17*SCREEN_HEIGHT)/24,.w=(SpriteList+5)->Width,.h=(SpriteList+5)->Height};
		SDL_Rect rect4={.x=(4*SCREEN_WIDTH)/8,.y=(17*SCREEN_HEIGHT)/24,.w=(SpriteList+6)->Width,.h=(SpriteList+6)->Height};
		SDL_Rect rect5={.x=(4*SCREEN_WIDTH)/8,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+9)->Width,.h=(SpriteList+9)->Height};
		SDL_Rect rect6={.x=(2*SCREEN_WIDTH)/8,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+10)->Width,.h=(SpriteList+10)->Height};

		if (subsettings==1){
			SDL_RenderCopy(rendertarget,(SpriteList+11)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==2){
			SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+15)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==3 ||subsettings==5) {
			SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+19)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==4 || subsettings==6){
			SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+20)->Texture,NULL,&rect6);
		}
		if (race==1){
			if(subsettings==1)
				SDL_RenderCopy(rendertarget,(SpriteList+12)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
		}
		else if(race==2){
			rect2.w=(SpriteList+3)->Width;
			rect2.h=(SpriteList+3)->Height;
			if(subsettings==1)
				SDL_RenderCopy(rendertarget,(SpriteList+13)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+3)->Texture,NULL,&rect2);
		}
		else{
			rect2.w=(SpriteList+6)->Width;
			rect2.h=(SpriteList+6)->Height;
			if(subsettings==1)
				SDL_RenderCopy(rendertarget,(SpriteList+14)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+4)->Texture,NULL,&rect2);
		}
		if (class==1){
			if(subsettings==2)
				SDL_RenderCopy(rendertarget,(SpriteList+16)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+6)->Texture,NULL,&rect4);
		}
		else if(class==2){
			rect2.w=(SpriteList+7)->Width;
			rect2.h=(SpriteList+7)->Height;
			if(subsettings==2)
				SDL_RenderCopy(rendertarget,(SpriteList+17)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+7)->Texture,NULL,&rect4);
		}
		else{
			rect2.w=(SpriteList+8)->Width;
			rect2.h=(SpriteList+8)->Height;
			if(subsettings==2)
				SDL_RenderCopy(rendertarget,(SpriteList+18)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(rendertarget,(SpriteList+8)->Texture,NULL,&rect4);
		}
	}
	else{
		SDL_Rect rect1={.x=(3*SCREEN_WIDTH)/8,.y=(18*SCREEN_HEIGHT)/24,.w=(SpriteList+43)->Width,.h=(SpriteList+43)->Height};
		SDL_Rect rect2={.x=(4*SCREEN_WIDTH)/8,.y=(18*SCREEN_HEIGHT)/24,.w=(SpriteList+44)->Width,.h=(SpriteList+44)->Height};
		SDL_Rect rect3={.x=(5*SCREEN_WIDTH)/8,.y=(18*SCREEN_HEIGHT)/24,.w=(SpriteList+45)->Width,.h=(SpriteList+45)->Height};
		SDL_Rect rect4={.x=(3*SCREEN_WIDTH)/8,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+46)->Width,.h=(SpriteList+46)->Height};
		SDL_Rect rect5={.x=(4*SCREEN_WIDTH)/8,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+47)->Width,.h=(SpriteList+47)->Height};
		SDL_Rect rect6={.x=(5*SCREEN_WIDTH)/8,.y=(20*SCREEN_HEIGHT)/24,.w=(SpriteList+48)->Width,.h=(SpriteList+48)->Height};
		if (subsettings==1){
			SDL_RenderCopy(rendertarget,(SpriteList+49)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==2){
			SDL_RenderCopy(rendertarget,(SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+50)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==3){
			SDL_RenderCopy(rendertarget,(SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+51)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==4){
			SDL_RenderCopy(rendertarget,(SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+52)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==5){
			SDL_RenderCopy(rendertarget,(SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+53)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==6){
			SDL_RenderCopy(rendertarget,(SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(rendertarget,(SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(rendertarget,(SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(rendertarget,(SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(rendertarget,(SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(rendertarget,(SpriteList+54)->Texture,NULL,&rect6);
		}
	}
	(CurrentInstance->data)[0]=subsettings;
	(CurrentInstance->data)[1]=race;
	(CurrentInstance->data)[2]=class;
	(CurrentInstance->data)[3]=timer;
	(CurrentInstance->data)[4]=settings;
	return;
}//selección de personaje
void InstanceStepCode_002(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	// Object 000 is the first menu that appears on the menu 1.

	SDL_RenderCopy(rendertarget,(SpriteList+0)->Texture,NULL,NULL);
	//take variables
	int settings=((CurrentInstance)->data)[0];
	int timer=((CurrentInstance))->data[1];
	int items=((CurrentInstance))->data[2];
	int stats=((CurrentInstance))->data[3];
	int smenu=0;
	//control
	/* settings 1: Item button
				2: Stats button
				3: Continue button
				4: Back button
				5: you pressed Item button and you are about to buy potions
				6: you pressed the Stats button and now you are buying stats
				7: you pressed the continue button and you are going back to the game
				8: you pressed the back button */
	if (settings<5){
		if (key[0]&1){//press up
			settings--;
			if(settings<1) settings=1;
			if(settings==3) settings=2;
			Mix_PlayChannel(0,SoundList+0,1);
		}

		else if (key[1]&1) 	{ //press down
			settings++;
			if(settings>4) settings=3;
			Mix_PlayChannel(0,SoundList+0,1);
		}
		else if ((key[2]&1)&&(settings==3))  { //press left
			settings++;

			Mix_PlayChannel(0,SoundList+0,1);
		}
		else if ((key[3]&1)&&(settings==4)) { //press right
			settings--;
			Mix_PlayChannel(0,SoundList+0,1);
		}
		else if (key[5]&1){	//press x
				if (settings==1){
					settings=5;//items
					Mix_PlayChannel(0,SoundList+1,1);
				}
				else if (settings==2){
					settings=6; //stats
					Mix_PlayChannel(0,SoundList+1,1);
				}
				else if (settings==3){
					settings=7;//next screen of the game
					Mix_PlayChannel(0,SoundList+1,1);
				}
				else if (settings==4){
					settings=8;//back confirmed
					Mix_PlayChannel(0,SoundList+0,1);
				}
			}
		else if (key[12]&1)	{ //press esc
			settings=8;
			Mix_PlayChannel(0,SoundList+1,1);
		}
	}
	else if (settings==5){ //Item button pressed
		if (timer<=0){

		}
		timer-=10;

	}
	else if (settings==6) {// Stats button pressed
		if (timer<=0){
		}
		timer-=10;
	}
	else if (settings==7) {// continue button pressed
		if (timer<=0){
			*menu=40; //ir al campo de batalla
		}
		timer-=10;
	}
	else if (settings==8) {// back button pressed
		if(timer<=0){
			*menu=20;
		}
		timer-=10;
	}
	//end control
	SDL_Rect rect1={.x=SCREEN_WIDTH/2-120,.y=(5*SCREEN_HEIGHT)/6,.w=(SpriteList+1)->Width,.h=(SpriteList+1)->Height};
    SDL_Rect rect2={.x=SCREEN_WIDTH/2-60,.y=(3*SCREEN_HEIGHT)/6-20,.w=(SpriteList+2)->Width,.h=(SpriteList+2)->Height};
    SDL_Rect rect3={.x=SCREEN_WIDTH/2-60,.y=(4*SCREEN_HEIGHT)/6-20,.w=(SpriteList+3)->Width,.h=(SpriteList+3)->Height};
    SDL_Rect rect4={.x=2*SCREEN_WIDTH/3-60,.y=(5*SCREEN_HEIGHT)/6-20,.w=(SpriteList+4)->Width,.h=(SpriteList+4)->Height};
    SDL_Rect rect5={.x=SCREEN_WIDTH/3-60,.y=(5*SCREEN_HEIGHT)/6-20,.w=(SpriteList+5)->Width,.h=(SpriteList+5)->Height};
    SDL_Rect rect6={.x=SCREEN_WIDTH/2-362,.y=(SCREEN_HEIGHT)/2-110,.w=22*SCREEN_WIDTH/36,.h=22*SCREEN_HEIGHT/36};
    SDL_Rect rect7={.x=7*SCREEN_WIDTH/18,.y=(3*SCREEN_HEIGHT)/6,.w=(SpriteList+7)->Width,.h=(SpriteList+7)->Height};
    SDL_Rect rect8={.x=7*SCREEN_WIDTH/18,.y=(4*SCREEN_HEIGHT)/6,.w=(SpriteList+8)->Width,.h=(SpriteList+8)->Height};
    SDL_Rect rect9={.x=8*SCREEN_WIDTH/18,.y=(3*SCREEN_HEIGHT)/6,.w=(SpriteList+9)->Width,.h=(SpriteList+9)->Height};
    SDL_Rect rect10={.x=8*SCREEN_WIDTH/18,.y=(4*SCREEN_HEIGHT)/6,.w=(SpriteList+10)->Width,.h=(SpriteList+10)->Height};
    SDL_Rect rect11={.x=7*SCREEN_WIDTH/18,.y=(3*SCREEN_HEIGHT)/6,.w=(SpriteList+11)->Width,.h=(SpriteList+11)->Height};
    SDL_Rect rect12={.x=7*SCREEN_WIDTH/18,.y=(3.3*SCREEN_HEIGHT)/6,.w=(SpriteList+12)->Width,.h=(SpriteList+12)->Height};
    SDL_Rect rect13={.x=7*SCREEN_WIDTH/18,.y=(3.6*SCREEN_HEIGHT)/6,.w=(SpriteList+13)->Width,.h=(SpriteList+13)->Height};
	if 		(settings==1) // on item button
		rect1.y=3*((SpriteList+0)->FrameHeight)/6;
	else if (settings==2) // on stats button
		rect1.y=4*((SpriteList+0)->FrameHeight)/6;
	else if (settings==3){ // on continue button
		rect1.y=5*((SpriteList+0)->FrameHeight)/6;
		rect1.x=2*(SCREEN_WIDTH/3-60);
	}
	else if (settings==4){// on back button
		rect1.y=5*((SpriteList+0)->FrameHeight)/6;
		rect1.x=(SCREEN_WIDTH/3)-120;
	}

	else if (settings==5){//just pressed items
		smenu=1;
		if(items<4){
			if(key[0]&1){
				items--;
				if(items<1) items=1;
			}
			if(key[1]&1){
				items++;
				if(items>3) items=3;
			}
			if(key[2]&1) items=3;
			if(key[3]&1) items=1;
			if(key[4]&1){
				if(items==1&&saved_data->gold>=5){//life pot
					saved_data->gold-=5;
					saved_data->inv[1]+=1;
				}
				else if(items==2&&saved_data->gold>=6){//mana pot
					saved_data->gold-=6;
					saved_data->inv[2]+=1;

				}
				else if(items==3){//back
					items=1;
					smenu=0;
					settings=1;
				}
			}


			if(items==1){//coin in items menu
				rect1.y=18.5*((SpriteList+0)->FrameHeight)/36;
				rect1.x=13*SCREEN_WIDTH/36;
			}
			else if(items==2){
				rect1.y=24.5*((SpriteList+0)->FrameHeight)/36;
				rect1.x=13*SCREEN_WIDTH/36;
			}
			else if(items==3){
				rect1.y=(15*SCREEN_HEIGHT)/18;
				rect1.x=SCREEN_WIDTH/3-100;
			}

		}
		SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect5);//back button
		SDL_RenderCopy(rendertarget,(SpriteList+6)->Texture,NULL,&rect6);//paper
		SDL_RenderCopy(rendertarget,(SpriteList+7)->Texture,NULL,&rect7);//r potion
		SDL_RenderCopy(rendertarget,(SpriteList+8)->Texture,NULL,&rect8);//b potion
		SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect9);//r text
		SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect10);//b text
		SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);

		((CurrentInstance))->data[2]=items;
		if(key[6]&1){
			smenu=0;
			settings=1;
		}
	}//potions menu

	else if (settings==6){//just pressed stats upgrade
		smenu=2;
		if(stats<5){
			if(stats<1) stats=1;
			if(key[0]&1){
				stats--;
				if(stats<1) stats=1;
			}
			if(key[1]&1){
				stats++;
				if(stats>4) stats=4;
			}
			if(key[2]&1) stats=3;
			if(key[3]&1) stats=1;
			if(key[4]&1){
				if(stats==1&&saved_data->gold>=30){//hp
					saved_data->gold-=30;
					saved_data->maxhp+=6;
				}
				else if(stats==2&&saved_data->gold>=13){//def
					saved_data->gold-=13;
					saved_data->def+=1;
				}
				else if(stats==3&&saved_data->gold>=10){//atk
					saved_data->gold-=10;
					saved_data->atk+=2;
				}
				else if(stats==4){//back
					smenu=0;
					stats=1;
					settings=1;
				}
			}
			if(stats==1){//coin in stats menu
				rect1.y=18.5*((SpriteList+0)->FrameHeight)/36;
				rect1.x=13*SCREEN_WIDTH/36;
			}
			else if(stats==2){
				rect1.y=20.3*((SpriteList+0)->FrameHeight)/36;
				rect1.x=13*SCREEN_WIDTH/36;
			}
			else if(stats==3){
				rect1.y=22*((SpriteList+0)->FrameHeight)/36;
				rect1.x=13*SCREEN_WIDTH/36;
			}
			else if(stats==4){
				rect1.y=(15*SCREEN_HEIGHT)/18;
				rect1.x=SCREEN_WIDTH/3-100;
			}

		}
		SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect5);//back button
		SDL_RenderCopy(rendertarget,(SpriteList+6)->Texture,NULL,&rect6);//paper
		SDL_RenderCopy(rendertarget,(SpriteList+11)->Texture,NULL,&rect11);//hp text
		SDL_RenderCopy(rendertarget,(SpriteList+12)->Texture,NULL,&rect12);//def text
		SDL_RenderCopy(rendertarget,(SpriteList+13)->Texture,NULL,&rect13);//atk text
		SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);//dynamic coin

		((CurrentInstance))->data[3]=stats;
		if(key[6]&1){
			smenu=0;
			settings=1;
		}
	}//Stats menu

	if(smenu==0){//main store menu
		SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,NULL,&rect1);
		SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
		SDL_RenderCopy(rendertarget,(SpriteList+3)->Texture,NULL,&rect3);
		SDL_RenderCopy(rendertarget,(SpriteList+4)->Texture,NULL,&rect4);
		SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect5);
	}
	//save changes on used variables
	((CurrentInstance)->data)[0]=settings;
	((CurrentInstance)->data)[1]=timer;
	((CurrentInstance))->data[2]=items;
	((CurrentInstance))->data[3]=stats;
	return;
}//bazar
void InstanceStepCode_004(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){

	int win=CurrentInstance->data[13];
	int battle=saved_data->battle;

	if (win==1){ //win
		Mix_PauseMusic();
		win=3;
		int newgold=rand()%50;
		int newexp=rand()%50+50;
		printf("+%d gold!\n",newgold);
		printf("+%d exp!\n",newexp);
		saved_data->hp=(InstanceList+1)->data[7];
		if (saved_data->hp<1)
			saved_data->hp=1;
		saved_data->gold+=newgold;
		saved_data->exp+=newexp;
		saved_data->inv[1]=(InstanceList+1)->data[8];
		saved_data->inv[2]=(InstanceList+1)->data[9];
		if (saved_data->exp>100){
			levelup(saved_data);
		}
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect1);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==2){ //lose
		win=4;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect1);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==3){ //win button back to tabern
		if (CurrentInstance->data[19]>1)
			--CurrentInstance->data[19];
		else
			if (*menu<72)
				*menu+=9;
			else{
				if(key[3]&1){
					win=5; //next battle button
				}
				else if(key[5]&1){
					*menu=30;
				}
			}
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=SCREEN_WIDTH/2+MatrixSpace/2,.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(rendertarget,(SpriteList+3)->Texture,NULL,&rect2);
		SDL_RenderCopy(rendertarget,(SpriteList+7)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if (win==4){ //lose button back to tabbern
		if (CurrentInstance->data[19]>1)
			--CurrentInstance->data[19];
		else
			if(key[3]&1){
				win=6; //next battle button
			}
			else if(key[5]&1){
				*menu=30;
			}
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=SCREEN_WIDTH/2+MatrixSpace/2,.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(rendertarget,(SpriteList+3)->Texture,NULL,&rect2);
		SDL_RenderCopy(rendertarget,(SpriteList+8)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==5){ //win button back to tabern
		if(key[2]&1){
			win=3; //next battle button
		}
		else if(key[5]&1){
			*menu=40;
		}
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+9)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=SCREEN_WIDTH/2+MatrixSpace/2,.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(rendertarget,(SpriteList+6)->Texture,NULL,&rect2);
		SDL_RenderCopy(rendertarget,(SpriteList+4)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if (win==6){ //lose button back to tabbern
		if(key[2]&1){
			win=4; //next battle button
		}
		else if(key[5]&1){
			*menu=40;
		}
		SDL_SetRenderDrawColor(rendertarget,0,0,0,255);
		SDL_RenderFillRect(rendertarget,NULL);
		SDL_Rect rect1={.x=SCREEN_WIDTH/2-MatrixSpace,.y=SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(rendertarget,(SpriteList+10)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=SCREEN_WIDTH/2+MatrixSpace/2,.y=SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(rendertarget,(SpriteList+6)->Texture,NULL,&rect2);
		SDL_RenderCopy(rendertarget,(SpriteList+5)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	if ((InstanceList+2)->data[5]<1) //monster died
		win=1;
	else if((InstanceList+1)->data[7]<1) //human died
		win=2;

	SDL_RenderCopy(rendertarget,(SpriteList+0)->Texture,NULL,NULL);
	// (CurrentInstance)->data[11]; //contador de frame
	// (CurrentInstance)->data[12]; //contador de avance
	SDL_Rect rect1a={
		.x=0,
		.y=0,
		.w=(SpriteList+1)->FrameWidth,
		.h=(SpriteList+1)->FrameHeight};
	ActualizacionDeAnimacion(&rect1a,(SpriteList+1),(CurrentInstance)->data+11,(CurrentInstance)->data+12);
	SDL_Rect rect1b={
		.x=SCREEN_WIDTH/2-MatrixSpace-((SpriteList+1)->FrameWidth)/2,
		.y=SCREEN_HEIGHT/2-MatrixSpace-((SpriteList+1)->FrameHeight)/2,
		.w=(SpriteList+1)->FrameWidth,
		.h=(SpriteList+1)->FrameHeight}; //enemy spot

	SDL_Rect rect2={
		.x=SCREEN_WIDTH/2-MatrixSpace-((SpriteList+2)->FrameWidth)/2,
		.y=SCREEN_HEIGHT/2-((SpriteList+2)->FrameHeight)/2,
		.w=(SpriteList+2)->FrameWidth,
		.h=(SpriteList+2)->FrameHeight}; //player spot

	//printing the battlefield
	//monster spot
	SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,&rect1a,&rect1b);
	rect1b.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,&rect1a,&rect1b);
	rect1b.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+1)->Texture,&rect1a,&rect1b);
	//player spot
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	rect2.x-=2*MatrixSpace;
	rect2.y+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(rendertarget,(SpriteList+2)->Texture,NULL,&rect2);

	//printing monster hp and player hp

	int hpheight=SCREEN_HEIGHT-80;
	//monster hp bar
	int monsterHP=(InstanceList+2)->data[5];

	if (monsterHP>0){
		int monsterMAXHP=(InstanceList+2)->data[8];
		SDL_Rect monsterHPext={.x=SCREEN_WIDTH-65,.y=30,.w=60,.h=SCREEN_HEIGHT-60};
		SDL_Rect monsterHPint={.x=SCREEN_WIDTH-55,.y=40,.w=40,.h=hpheight};

		monsterHPint.h=(hpheight*monsterHP)/monsterMAXHP;

		SDL_SetRenderDrawColor(rendertarget,10,10,10,255);
		SDL_RenderFillRect(rendertarget,&monsterHPext);
		SDL_SetRenderDrawColor(rendertarget,255,10,60,255);
		SDL_RenderFillRect(rendertarget,&monsterHPint);
	}
	//player hp bar

	int playerHP=(InstanceList+1)->data[7];

	if (playerHP>0){
		int playerbarwidth=100;

		int playerMAXHP=saved_data->maxhp;

		SDL_Rect playerHPext={.x=10,.y=SCREEN_HEIGHT-24,.w=playerbarwidth+4,.h=14};
		SDL_Rect playerHPint={.x=12,.y=SCREEN_HEIGHT-22,.w=playerbarwidth,.h=10};

		playerHPint.w=(playerbarwidth*playerHP)/playerMAXHP;

		SDL_SetRenderDrawColor(rendertarget,10,10,10,255);
		SDL_RenderFillRect(rendertarget,&playerHPext);
		SDL_SetRenderDrawColor(rendertarget,255,10,60,255);
		SDL_RenderFillRect(rendertarget,&playerHPint);
	}

	CurrentInstance->data[13]=win;
	return;
}//Battlefield
void InstanceStepCode_005(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){




	int CurrentSprites=11;

	int position=(CurrentInstance->data)[0]; // position // 4 5 6
														//	7 8 9
	int timer=(CurrentInstance->data)[1];
	//			CurrentInstance->data[2] -> Frame count
	//			CurrentInstance->data[3] -> Frame advance
	int action=(CurrentInstance)->data[4]; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking up,
												2:walking down,
												3:walking left,
												4:walking right,
											//	5:getting hit,
												6:attack1, */

	float walking=(CurrentInstance)->data[5];		//walking
	int isborn=(CurrentInstance)->data[6];	//is born
	int hp=(CurrentInstance)->data[7];	//hp
	int redpotions=(CurrentInstance)->data[8];
	int bluepotions=(CurrentInstance)->data[9];
	int energy=(CurrentInstance)->data[10];


	if (hp<1 || (InstanceList+2)->data[5]<1) //you are dead
		return;

	float movespeed=saved_data->movspeed; //movement speed

	if (action==0){ //The player is not doing anything
		if (key[0]&1){ //moving up
			if (position>=7 && position <=9){
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+4); //walking up
				(CurrentInstance->data)[2]=0; // reset animation
				position-=3;
				action=1;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+0);//standing up
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (key[1]&1){ //pressed the key to move down
			if (position>=4 && position <=6){
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+5); //walking down
				(CurrentInstance->data)[2]=0; // reset animation
				position+=3;
				action=2;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1); //standing down
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (key[2]&1){ //pressed the key to move left
			if (position!=4 && position !=7){
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+6); //walking left
				(CurrentInstance->data)[2]=0; // reset animation
				position-=1;
				action=3;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+2); //standing left
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (key[3]&1){ //pressed the key to move right
			if (position!=6 && position !=9){
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+7); //walking right
				(CurrentInstance->data)[2]=0; // reset animation
				position+=1;
				action=4;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+3); //standing right
				(CurrentInstance->data)[2]=0;
			}
		}
		else if(key[5]&1){ //atk 1
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+4); //attacking pose
			walking=saved_data->atkspeed;
			action=6;
		}
		else if(key[7]&1){ //pocion //button a
			if(redpotions>0 && hp<saved_data->maxhp){
				--redpotions;
				hp+=10;
				if (hp>=saved_data->maxhp)
					hp=saved_data->maxhp;
			}

		}
		else if(key[8]&1){ //pocion //button s
			if(bluepotions>0 && energy<saved_data->maxenergy){
				--bluepotions;
				energy+=10;
				if (energy>=saved_data->maxenergy)
					energy=saved_data->maxenergy;
			}

		}
	}
	else if(action==1){ //the player is walking up
		if (walking>0){
			(CurrentInstance)->y-=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+0);
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->y=SCREEN_HEIGHT/2-(CurrentInstance)->sprite->FrameHeight/2;
			action=0;
		}//walking up
	}
	else if(action==2){ //the player is walking down
		if (walking>0){
			(CurrentInstance)->y+=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->y=SCREEN_HEIGHT/2-(CurrentInstance)->sprite->FrameHeight/2+MatrixSpace;
			action=0;
		}//walking up
	}
	else if(action==3){ //the player is walking left
		if (walking>0){
			(CurrentInstance)->x-=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+2);
			(CurrentInstance->data)[2]=0;
			if (position==4 || position==7){
				(CurrentInstance)->x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else {
				(CurrentInstance)->x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			action=0;
		}//walking up
	}
	else if(action==4){ //the player is walking right
		if (walking>0){
			(CurrentInstance)->x+=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+3);
			(CurrentInstance->data)[2]=0;
			if (position==5 || position==8){
				(CurrentInstance)->x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else {
				(CurrentInstance)->x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
		}//walking up
	}
	else if(action==6){ //player is attacking --ATACK
		--walking;
		if (walking<0){
			walking=0;
			action=0;
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+0);
			if (saved_data->class==3){
				InstanceCreationCode_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
				((InstanceList+*ins_count-1)->data)[0]=3;
				((InstanceList+*ins_count-1)->data)[1]=saved_data->atk; //damage
				(InstanceList+*ins_count-1)->rectangle2.x=CurrentInstance->rectangle2.x;
				(InstanceList+*ins_count-1)->rectangle2.y=CurrentInstance->rectangle2.y-CurrentInstance->rectangle2.w/2;
			}
			else if (saved_data->class==1){ //warrior
				if ((InstanceList+2)->data[0]==position-3 && (InstanceList+2)->data[4]==0){
					(InstanceList+2)->data[5]-=saved_data->atk;
				}

			}
			else {
				InstanceCreationCode_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
				((InstanceList+*ins_count-1)->data)[1]=saved_data->atk; //damage
				(InstanceList+*ins_count-1)->rectangle2.x=CurrentInstance->rectangle2.x;
				(InstanceList+*ins_count-1)->rectangle2.y=CurrentInstance->rectangle2.y-CurrentInstance->rectangle2.w/2;
			}
		}
	}

	(CurrentInstance)->rectangle2.y=(CurrentInstance)->y;
	(CurrentInstance)->rectangle2.x=(CurrentInstance)->x;
	if (action!=0)
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	else{
		CurrentInstance->rectangle1.x=0;
		CurrentInstance->rectangle1.y=0;
	}
	SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
	(CurrentInstance->data)[0]=position; // position // 4 5 6
														//	7 8 9
	(CurrentInstance->data)[1]=timer;
	//			CurrentInstance->data[2] -> Frame count
	//			CurrentInstance->data[3] -> Frame advance
	(CurrentInstance->data)[4]=action; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking up,
												2:walking down,
												3:walking left,
												4:walking right,
												5:getting hit,
												6:attack1, */

	(CurrentInstance->data)[5]=walking;		//walking count
	(CurrentInstance->data)[6]=isborn;	//is born
	(CurrentInstance->data)[7]=hp;	//hp
	(InstanceList+(*ins_count))->data[8]=redpotions;
	(InstanceList+(*ins_count))->data[9]=bluepotions;
	(InstanceList+(*ins_count))->data[10]=energy;

	return;
}//Player
void InstanceStepCode_006(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	srand(time(NULL));
	//nombrar variables
	int CurrentSprites=31;

	int position=(CurrentInstance->data)[0]; // position // 1 2 3
	int timer=(CurrentInstance->data)[1]; //timer
	int action=(CurrentInstance)->data[4]; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking left,
												2:walking right,
												3:getting hit,
												4:attack1, */

	int hp=(CurrentInstance)->data[5]; //hp
	int isborn=(CurrentInstance)->data[6]; //is born
	int walking=(CurrentInstance)->data[7]; //walking count
	int movespeed=2;
	int attacknumber=0;

	if (hp<1 || (InstanceList+1)->data[7]<1)
		return;

	if(action==0){ //standing
		++timer;
		if((InstanceList+0)->data[position]>0){ //the monster got hit by an attack
			hp-=(InstanceList+0)->data[position];
			action=-1;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+0);
			isborn=0;
		}
		if (hp<1){
			(action=-2); //monster died
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+4);
			(CurrentInstance->data)[2]=0;
			isborn=0;
		}
		if (timer%50==0){ //attack1
			int a=rand()%6;
			if(a==0||a==5){
				(CurrentInstance)->sprite=(SpriteList+CurrentSprites+3); //attack sprite
				(CurrentInstance->data)[2]=0;
				action=4;
				isborn=60;
			}
		}
		if (timer==500){//caminar
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+2); //walking
			(CurrentInstance->data)[2]=0;
			if (position==1) {
				position=2;
				action=2;
			}
			else if(position==2) {
				action=((rand()%2));
				if (action==0) {
					action=1;
					position=1;
				}
				else{
					action=2;
					position=3;
				}
			}
			else { //position==3
				position=2;
				action=1;
			}
			walking=MatrixSpace/movespeed;
		}
	}
	else if(action==1){
		if (walking>0){
			(CurrentInstance)->rectangle2.x-=movespeed;
			--walking;
		}
		else{
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			if (position==1){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else if (position==2){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else if (position==3){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
			timer=0;
		}//walking left
	}
	else if(action==2){ //walking right
		if (walking>0){
			(CurrentInstance)->rectangle2.x+=movespeed;
			--walking;
		}
		else{
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			if (position==1){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else if (position==2){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else if (position==3){
				(CurrentInstance)->rectangle2.x=SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
			timer=0;
		}
	}
	else if(action==3){

	}
	else if(action==4){ //attack1
		--isborn;
		if(isborn%12==0){
			InstanceCreationCode_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
			(InstanceList+*ins_count-1)->rectangle2.x=(CurrentInstance)->rectangle2.x+((InstanceList+*ins_count-1)->sprite->FrameWidth/2);
			(InstanceList+*ins_count-1)->rectangle2.y=(CurrentInstance)->rectangle2.y;
			(InstanceList+*ins_count-1)->data[0]=(rand()+attacknumber)%8; //speed
		}
		if(isborn==0){
			action=0;
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
		}
	}
	else if(action==-1){ //being born
		if((CurrentInstance)->data[2]==2)
			isborn=1;
		if(isborn==1 && (CurrentInstance)->data[2]==0){
			(CurrentInstance)->sprite=(SpriteList+CurrentSprites+1); //IDLE sprite
			(CurrentInstance->data)[2]=0;
			action=0;
		}

	}
	else if(action==-2){ //dead //por terminar
		if((CurrentInstance)->data[2]==2)
			isborn=1;
		if(isborn==1 && (CurrentInstance)->data[2]==0){
			(CurrentInstance->data)[2]=0;
			(InstanceList+0)->data[18]=CurrentInstance->rectangle2.x;
			(InstanceList+0)->data[19]=CurrentInstance->rectangle2.y;
		}

	}
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
	//devolver variables
	(CurrentInstance->data)[0]=position;
	(CurrentInstance)->data[1]=timer;
	(CurrentInstance)->data[4]=action;
	(CurrentInstance)->data[5]=hp;
	(CurrentInstance)->data[6]=isborn;
	(CurrentInstance)->data[7]=walking;
	return;
}//Leaf Monster
void InstanceStepCode_007(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int playerx=0;
	int playery=0;
	int playerwidth=0;
	int playerheight=0;
	if((InstanceList+1)->ID==005){
		playerx=(InstanceList+1)->rectangle2.x;
		playery=(InstanceList+1)->rectangle2.y;
		playerwidth=(InstanceList+1)->rectangle2.w;
		playerheight=(InstanceList+1)->rectangle2.h;
	}

	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y+=speed;
	if(y>760){ //out of window
		//destruir
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >playerx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <playerx+playerwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >playery &&
		y+CurrentInstance->sprite->FrameHeight/2 <playery+playerheight){
		int damage=CurrentInstance->data[1]-saved_data->def;
		if (damage>0)
			(InstanceList+1)->data[7]-=damage;
		else
			(InstanceList+1)->data[7]-=1;
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));

		return;
	}


	//imprimir
	ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));



	//devolver variables
	CurrentInstance->rectangle2.x=x;
	CurrentInstance->rectangle2.y=y;

	return;
}//leaf attack1
void InstanceStepCode_008(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int monsterx=0;
	int monstery=0;
	int monsterwidth=0;
	int monsterheight=0;
	if((InstanceList+2)!=NULL){
		monsterx=(InstanceList+2)->rectangle2.x;
		monstery=(InstanceList+2)->rectangle2.y;
		monsterwidth=(InstanceList+2)->rectangle2.w;
		monsterheight=(InstanceList+2)->rectangle2.h;
	}
	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y-=speed;
	if(y<-20){ //out of window
		//destruir
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >monsterx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <monsterx+monsterwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >monstery &&
		y+CurrentInstance->sprite->FrameHeight/2 <monstery+monsterheight){
		(InstanceList+2)->data[5]-=CurrentInstance->data[1];
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}


	//imprimir
	ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));



	//devolver variables
	CurrentInstance->rectangle2.x=x;
	CurrentInstance->rectangle2.y=y;

	return;
}//player attack1
void InstanceStepCode_009(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int monsterx=0;
	int monstery=0;
	int monsterwidth=0;
	int monsterheight=0;
	if((InstanceList+2)!=NULL){
		monsterx=(InstanceList+2)->rectangle2.x;
		monstery=(InstanceList+2)->rectangle2.y;
		monsterwidth=(InstanceList+2)->rectangle2.w;
		monsterheight=(InstanceList+2)->rectangle2.h;
	}
	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y-=speed;
	if(y<-20){ //out of window
		//destruir
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >monsterx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <monsterx+monsterwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >monstery &&
		y+CurrentInstance->sprite->FrameHeight/2 <monstery+monsterheight){
		(InstanceList+2)->data[5]-=CurrentInstance->data[1];
		InstanceDestroy(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}


	//imprimir
	ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	SDL_RenderCopy(rendertarget,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));



	//devolver variables
	CurrentInstance->rectangle2.x=x;
	CurrentInstance->rectangle2.y=y;

	return;
}//player attack2
void InstanceStepCodes(SDL_Renderer* rendertarget,Instance* CurrentInstance,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){

	int obj = (CurrentInstance)->ID;
	if 		(obj==0) InstanceStepCode_000(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==1) InstanceStepCode_001(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==2) InstanceStepCode_002(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==4) InstanceStepCode_004(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==5) InstanceStepCode_005(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==6) InstanceStepCode_006(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==7) InstanceStepCode_007(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==8) InstanceStepCode_008(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	else if (obj==9) InstanceStepCode_009(rendertarget,CurrentInstance,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
}
void refresh(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){

	SDL_RenderClear(rendertarget);
	short i;
	for(i=0;i<*ins_count;++i){
		Instance* CurrentInstance=InstanceList+i;
		InstanceStepCodes(rendertarget,CurrentInstance,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	}
	SDL_RenderPresent(rendertarget);
}

// presion de las "key"
void keypressed(char* key){
	const Uint8*currentstate=SDL_GetKeyboardState(NULL);
	if(currentstate[SDL_SCANCODE_UP]) //key is being pressed
			if (key[0]&0x4) key[0]=0x4; // 0100 //Still pressed
			else 			key[0]=0x5;	// 0101 //just pressed
	else 	if (key[0]&0x4)	key[0]=0xA;	// 1010 //was being pressed-> just released
			else 			key[0]=0x8; // 1000 //Still released
	if(currentstate[SDL_SCANCODE_DOWN])
			if (key[1]&0x4) key[1]=0x4;
			else 			key[1]=0x5;
	else 	if (key[1]&0x4)	key[1]=0xA;
			else 			key[1]=0x8;
	if(currentstate[SDL_SCANCODE_LEFT])
			if (key[2]&0x4) key[2]=0x4;
			else 			key[2]=0x5;
	else 	if (key[2]&0x4)	key[2]=0xA;
			else 			key[2]=0x8;
	if(currentstate[SDL_SCANCODE_RIGHT])
			if (key[3]&0x4) key[3]=0x4;
			else 			key[3]=0x5;
	else 	if (key[3]&0x4)	key[3]=0xA;
			else 			key[3]=0x8;
	if(currentstate[SDL_SCANCODE_Z])
			if (key[4]&0x4) key[4]=0x4;
			else 			key[4]=0x5;
	else 	if (key[4]&0x4)	key[4]=0xA;
			else 			key[4]=0x8;
	if(currentstate[SDL_SCANCODE_X])
			if (key[5]&0x4) key[5]=0x4;
			else 			key[5]=0x5;
	else 	if (key[5]&0x4)	key[5]=0xA;
			else 			key[5]=0x8;
	if(currentstate[SDL_SCANCODE_C])
			if (key[6]&0x4) key[6]=0x4;
			else 			key[6]=0x5;
	else 	if (key[6]&0x4)	key[6]=0xA;
			else 			key[6]=0x8;
	if(currentstate[SDL_SCANCODE_A])
			if (key[7]&0x4) key[7]=0x4;
			else 			key[7]=0x5;
	else 	if (key[7]&0x4)	key[7]=0xA;
			else 			key[7]=0x8;
	if(currentstate[SDL_SCANCODE_S])
			if (key[8]&0x4) key[8]=0x4;
			else 			key[8]=0x5;
	else 	if (key[8]&0x4)	key[8]=0xA;
			else 			key[8]=0x8;
	if(currentstate[SDL_SCANCODE_I])
			if (key[9]&0x4) key[9]=0x4;
			else 			key[9]=0x5;
	else 	if (key[9]&0x4)	key[9]=0xA;
			else 			key[9]=0x8;
	if(currentstate[SDL_SCANCODE_SPACE])
			if (key[10]&0x4)key[10]=0x4;
			else 			key[10]=0x5;
	else 	if (key[10]&0x4)key[10]=0xA;
			else 			key[10]=0x8;
	if(currentstate[SDL_SCANCODE_RETURN])
			if (key[11]&0x4)key[11]=0x4;
			else 			key[11]=0x5;
	else 	if (key[11]&0x4)key[11]=0xA;
			else 			key[11]=0x8;
	if(currentstate[SDL_SCANCODE_ESCAPE])
			if (key[12]&0x4)key[12]=0x4;
			else 			key[12]=0x5;
	else 	if (key[12]&0x4)key[12]=0xA;
			else 			key[12]=0x8;
	if(currentstate[SDL_SCANCODE_P])
			if (key[13]&0x4)key[13]=0x4;
			else 			key[13]=0x5;
	else 	if (key[13]&0x4)key[13]=0xA;
			else 			key[13]=0x8;
}
void keycompare(char* key1, char* key2){ //key1 your frame key key2 your bullshit key
	short i;
	for(i=0;i<KeyNumber;++i){
		if (!(key1[i] & key2[i])){
			if (key1[i]&8 && key2[i]&4) //key got pressed
				key1[i]=5;
			else key1[i]=0xA;
		}
		else if(key1[i]&8) key1[i]=8;
			else key1[i]=4;
	}
}





/*		CIERRE DE MULTIMEDIA		*/
void closing_texture(SDL_Texture* mytexture){
	SDL_DestroyTexture(mytexture);
}
void closing_surface(SDL_Surface* mysurface){
	SDL_FreeSurface( mysurface);
}
void closing_window(SDL_Window* mywindow){
	SDL_DestroyWindow( mywindow);
}
void FreeMedia(Sprite* SpriteList,Mix_Music**song,Mix_Chunk**sound){
	short i;
	printf("Freeing Media Files...");
	for(i=0;i<MaxSprites;++i){
		if((SpriteList+i)->Texture!=NULL){
			SDL_DestroyTexture((SpriteList+i)->Texture);
			(SpriteList+i)->Texture=NULL;
		}
	}
	for(i=0;i<MaxSongs;++i){
		if(*(song+i)!=NULL){
			Mix_FreeMusic(*(song+i));
			*(song+i)=NULL;
		}
	}
	for(i=0;i<MaxSounds;++i){
		if(*(sound+i)!=NULL){
			Mix_FreeChunk(*(sound+i));
			*(sound+i)=NULL;
		}
	}
	printf("Done!\n");
}
void closing(SDL_Window* mainwindow){ //closing game
    //Deallocate main surface
	//closing_surface(mainsurface);
    //Destroy main window
    closing_window( mainwindow );

    //Quit SDL subsystems
    printf("Goodbye User...");
    TTF_Quit();
    Mix_CloseAudio();
    SDL_VideoQuit();
    SDL_AudioQuit();
    SDL_Quit();
}





/*		GAME SECTIONS		*/

void Room1(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){

	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Menu...");

	Objectload_000(rendertarget,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);

	printf("Done!\n");

	InstanceCreationCode_000(rendertarget,InstanceList,SpriteList,
	SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);

	*menu=11;
}//menu principal
void Room2(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save* saved_data){ //seleccion de personaje
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Room2...");
	Objectload_001(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_001(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=21;
}//menu de elección de personaje
void Room3(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Store...");
	Objectload_002(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_002(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=31;
} //Bazar
void Room4(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Battlefield...");
	Objectload_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=41;
} //Battlefield1
void Room5(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Battlefield...");
	Objectload_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=51;
} //Battlefield2
void Room6(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Battlefield...");
	Objectload_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=61;
} //Battlefield3
void Room7(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Battlefield...");
	Objectload_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=71;
} //Battlefield4
void Room8(SDL_Renderer* rendertarget,Instance* InstanceList,Sprite* SpriteList,
	Mix_Music** SongList,Mix_Chunk** SoundList,char* key,int* menu,int* ins_count,
	int SCREEN_WIDTH,int SCREEN_HEIGHT,Save *saved_data){
	//free media
	FreeMedia(SpriteList,SongList,SoundList);
	*ins_count=0;
	//load media
	printf("Loading Battlefield...");
	Objectload_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_007(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_008(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	Objectload_009(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	printf("Done!\n");

	InstanceCreationCode_004(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_005(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	InstanceCreationCode_006(rendertarget,InstanceList,SpriteList,SongList,SoundList,key,menu,ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,saved_data);
	*menu=81;
} //Battlefield5

//MAIN
int main( int argc, char* args[] ){
	printf("initializing variables...");
	int menu;
	int SCREEN_WIDTH=1280;
	int SCREEN_HEIGHT=720;

	unsigned int PrevTime=0;
	unsigned int CurrentTime=0;
	unsigned int Frame=0;
	unsigned int PrevFrame=0;
	printf(" Done!\n");
	printf("Initializing SDL...");
	SDL_Window* mainwindow=CreatingWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
	SDL_GetWindowSize(mainwindow,&SCREEN_WIDTH,&SCREEN_HEIGHT);
	if(SDL_Init(SDL_INIT_AUDIO)<0) printf("could not initialize audio: %s",SDL_GetError());
	if(TTF_Init()<0) printf("could not initialize ttf: %s",TTF_GetError());
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048)<0) printf("could not initialize Mixer: %s",SDL_GetError());
	SDL_Renderer* mainrender=SDL_CreateRenderer(mainwindow,-1,SDL_RENDERER_ACCELERATED);
	SDL_Event ev1;
	//unsigned int key;
	char framekey[KeyNumber];
	char key[KeyNumber]; // 14 keys to be pressed and used in the game

	InitializeKeys(key,KeyNumber); //Initializing the 14 keys
	InitializeKeys(framekey,KeyNumber);

	Save saved_data[7]; //slot 0

	//---media files ---
	Sprite SpriteList[MaxSprites];
	for(menu=0;menu<MaxSprites;++menu)
		InitializeSprite(SpriteList+menu);

	Mix_Music * SongList[MaxSongs];
	for(menu=0;menu<MaxSongs;++menu)
		SongList[menu]=NULL;

	Mix_Chunk * SoundList[MaxSounds];
	for(menu=0;menu<MaxSounds;++menu)
		SoundList[menu]=NULL;

	Instance InstanceList[MaxInstances];
	for(menu=0;menu<MaxInstances;++menu)
		InitializeInstance(InstanceList+menu);
	int ins_count=0;

	//---END media---


		/* Game Loop Started */
	//random seed
	time_t t;
	srand((unsigned) time(&t));
	//ID LIST - - with every ID of every object, sprite, font
	menu=10;
	printf("Running Game\n");

	while( menu>0 ){	//--------------GAME LOOP--------------//


		while(SDL_PollEvent(&ev1)!=1 && menu>0){

			CurrentTime=SDL_GetTicks();
			keypressed(key);

			/*    FPS CONTROL       */
			if (CurrentTime>PrevTime+17){ // 33-> 30 fps   17->60 fps
				//StringCopy(key,framekey,KeyNumber);
				keycompare(framekey,key);
				PrevFrame=Frame;
				++Frame;
				PrevTime=CurrentTime;
				refresh(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			}
			/* 		END	FPS			*/


			/*		START GAME ROOMS		*/

			if 	(menu==10) 							// - - - ROOM 1 - - -
				Room1(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if (menu==20) 	//(20) 21-30	// - - - ROOM 2 - - -
				Room2(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==30)	//(30) 31-40	// - - - ROOM 3 - - -
				Room3(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==40)	//(30) 31-40	// - - - ROOM 4 - - -
				Room4(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==50)	//(30) 31-40	// - - - ROOM 5 - - -
				Room5(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==60)	//(30) 31-40	// - - - ROOM 6 - - -
				Room6(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==70)	//(30) 31-40	// - - - ROOM 7 - - -
				Room7(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);
			else if 	(menu==80)	//(30) 31-40	// - - - ROOM 8 - - -
				Room8(mainrender,InstanceList,SpriteList,SongList,SoundList,framekey,&menu,&ins_count,SCREEN_WIDTH,SCREEN_HEIGHT,&saved_data);


			/* 	END 	GAME 	ROOMS*/

			if(ev1.type==SDL_QUIT)
				menu=0;
			if(key[13]&0x1)
				if(Mix_PlayingMusic()){
					if(Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
				}
			if(key[12] & 0x1)
				menu=0;
		}
	}

	/* Game Loop ended */

	SDL_DestroyRenderer(mainrender);
	mainrender=NULL;
	printf("Quitting game loop...\n");

	//Free resources and close SDL
	FreeMedia(SpriteList,SongList,SoundList);
	closing(mainwindow);
	return 0;
}
