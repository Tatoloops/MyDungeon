#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <io.h>
#include <fcntl.h>

#include "LoadTextures.h"





void SetUTF8(){
	/*
	Sets UTF-8 to be printable in the console.
	*/
	_setmode(_fileno(stdout), _O_U8TEXT);
	return;
}

/*		INIZIALIZACION DE ESTRUCTURAS		*/
SDL_Window* CreatingWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT){
	SDL_Window* win=NULL;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		wprintf(L"\n%c  SDL could not initialize! SDL_Error: %s\n",0x488, SDL_GetError() );
		win = NULL;
	}
	else{
		wprintf(L" Done!");
		wprintf(L"\n%c	Creating a window...",0x10);
		//Create window
		win = SDL_CreateWindow( "My Dungeon", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( win == NULL ){
			wprintf(L"\n%c  Window could not be created! SDL_Error: %s\n",0x488, SDL_GetError() );
		}
		else{
			 SDL_Surface* iconsurface=SDL_LoadBMP("media/icon.bmp");
			SDL_SetWindowIcon(win,iconsurface);
			SDL_FreeSurface(iconsurface);
			iconsurface=NULL;
			wprintf(L" Done!\n");
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
void InitializeGlobal(GlobalVariables* Main){
	Main->RoomState=0x1;
	Main->RoomCurrentID=001;
	strcpy(Main->SavedataName,"Savedata.dat\0");
	for(unsigned short i=0;i<MaxSprites;++i)
		InitializeSprite(Main->SpriteList+i);
	for(unsigned short i=0;i<MaxInstances;++i)
		InitializeInstance(Main->InstanceList+i);
	for(unsigned short i=0;i<MaxSongs;++i)
		*(Main->SongList+i)=NULL;
	for(unsigned short i=0;i<MaxSounds;++i)
		*(Main->SoundList+i)=NULL;
}
void InitializeKeys(char* array,int n){ //puntero a array - n: numero de elemntos en el array
	int i;
	for (i=0;i<n;++i)
		*(array+i)=0x8;
}

int StringWidthEnglish(const char* StringRead,Language* Lang,int Flags){
	/*	
	LangSpr:	First pointer to Language Sprite.
	StringRead: String to get the width from.
	Flags:		

		XXXX XXXX 0000 0000 0000 0000 0000 0000:Languages:
			0000 0001:English Language.
			0000 0010:Spanish Language.
			0000 0011:French Language.
			0000 0100:German Language.
			0000 0101:Japanese Language.
			0000 0110:Russian
			0000 0111:Indonesian.
			0000 1000:Ukranian.
			...
		4x 4x 1000 0000 0000 0000 0000 0000:Include All Numbers.
		4x 4x 0100 0000 0000 0000 0000 0000:Include LowerCase Letters.
		4x 4x 0010 0000 0000 0000 0000 0000:Include UpperCase Letters.
		4x 4x 0001 0000 0000 0000 0000 0000:Include All Symbols.
	*/
	int PixelWidth=0;
	int SpaceWidth=10;	//pixels used by space
	if (Flags>>24 == 1)		//English Language
		if (Flags&0x800000 && Flags&0x400000 && Flags&0x200000 && Flags&0x100000){
			//Numbers-LowerC-UpperC-Symbols
			char Character;
			unsigned short i=0; //count
			do{
				Character=StringRead[i];
				while (Character==' '){
					i++;
					PixelWidth+=SpaceWidth;
					Character=StringRead[i];
				}
				if(Character!='\0')
					PixelWidth+=(Lang->SrcRect+Character-33)->w;
				i++;
			}
			while (Character!='\0');
		}
	return PixelWidth;
}


int RoomPlacePhraseRects(InsText* Ins,const char* Phrase,Language* Lang,int x, int y,int Flags){
	/*	
	Phrase:		Phrase to place, must contain '\0'.
	ImgSpot: 	Pointer to Image.
	FirstSpr:	Pointer to Alphabet sprite.
	x:			Left most pixel in the showing screen.
				Middle pixel if centered.
	y:			Top most pixel in the showing screen.
	Flags:		

		XXXX XXXX 0000 0000 0000 0000 0000 0000:Languages:
			0000 0001:English Language.
			0000 0010:Spanish Language.
			0000 0011:French Language.
			0000 0100:German Language.
			0000 0101:Japanese Language.
			0000 0110:Russian
			0000 0111:Indonesian.
			0000 1000:Ukranian.
			...
		4x 4x 1000 0000 0000 0000 0000 0000:Include All Numbers.
		4x 4x 0100 0000 0000 0000 0000 0000:Include LowerCase Letters.
		4x 4x 0010 0000 0000 0000 0000 0000:Include UpperCase Letters.
		4x 4x 0001 0000 0000 0000 0000 0000:Include All Symbols.
		4x 4x 0000 XX00 0000 0000 0000 0000:Phrase X Position
			01:From Right (X) to Left.			[0xuuu40000]
			10:From Left (X) to right.			[0xuuu80000]
			11:Centered (X) is middle point.	[0xuuuC0000]
	*/
	int NumberOfItemsPlaced=0;
	int SpaceWidth=10;

	int CRoom=0;
	int PhraseWidth;
	int Top,Left;
	if (Flags & 0x00080000 && Flags & 0x00040000){
		//Centered.
		PhraseWidth=StringWidthEnglish(Phrase,Lang,Flags);
		Top=y;
		Left=x-PhraseWidth/2;
	}
	else if (Flags & 0x00080000){
		//Left to right
		Top=y;
		Left=x;
	}
	else if (Flags & 0x00040000){
		//Right to Left
		PhraseWidth=StringWidthEnglish(Phrase,Lang,Flags);
		Top=y;
		Left=x-PhraseWidth;
	}
	int i=0; // count

	PhraseWidth=0;
	if (Flags>>24 == 1 && Flags&0x800000 && Flags&0x400000 && Flags&0x200000 && Flags&0x100000){//English Language
		while (Phrase[i]!='\0'){
			while(Phrase[i]==' '){
				PhraseWidth+=SpaceWidth;
				i++;
			}
			while(Phrase[i]!= '\0' && (Phrase[i]<'!' ||Phrase[i]>'~')){
				++i;
			}
			if(Phrase[i]!='\0'){
				Ins[NumberOfItemsPlaced].PtrToLang=Lang;

			Ins[NumberOfItemsPlaced].SrcR.x=Lang->SrcRect[Phrase[i]-'!'].x;
			Ins[NumberOfItemsPlaced].SrcR.y=Lang->SrcRect[Phrase[i]-'!'].y;
			Ins[NumberOfItemsPlaced].SrcR.w=Lang->SrcRect[Phrase[i]-'!'].w;
			Ins[NumberOfItemsPlaced].SrcR.h=Lang->SrcRect[Phrase[i]-'!'].h;

			Ins[NumberOfItemsPlaced].DestR.x=Left+PhraseWidth;
			Ins[NumberOfItemsPlaced].DestR.y=y;
			Ins[NumberOfItemsPlaced].DestR.w=Lang->SrcRect[Phrase[i]-'!'].w;
			Ins[NumberOfItemsPlaced].DestR.h=Lang->SrcRect[Phrase[i]-'!'].h;		

			PhraseWidth+=Ins[NumberOfItemsPlaced].DestR.w;
			NumberOfItemsPlaced++;
			//wprintf(L" \nplaced itemsBBB:%d",NumberOfItemsPlaced);
			++i;
			}
		}
	}
	//wprintf(L" \nplaced items:%d",NumberOfItemsPlaced);
	return NumberOfItemsPlaced;
}