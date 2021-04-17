#include "Initialization/Initialization.h"
#include "Initialization/ClosingMedia.h"
#include "Data/Data.h"
#include "Characters/AssetPack.h"
#include "Rooms/Roompack.h"
#include "FrameUpdate/FrameUpdate.h"


//MAIN
int main( int argc, char* args[] ){

	SetUTF8();
	wprintf(L"%c%c%c 		Initializing 		%c%c%c 	\n",4,4,4,4,4,4);
	wprintf(L"\n%c	initializing variables...",0x10);

	GlobalVariables MainData;

	MainData.SCREEN_WIDTH=1280;
	MainData.SCREEN_HEIGHT=704;

	
	unsigned int Frame=0;
	unsigned int PrevFrame=0;
	wprintf(L"	Done!");
	wprintf(L"\n%c	Initializing SDL...",0x10);
	MainData.MainWindow=CreatingWindow(MainData.SCREEN_WIDTH,MainData.SCREEN_HEIGHT);
	SDL_GetWindowSize(MainData.MainWindow,&(MainData.SCREEN_WIDTH),&(MainData.SCREEN_HEIGHT));
	if(SDL_Init(SDL_INIT_AUDIO)<0) wprintf(L"\n%c	Could not initialize audio: %S",0x488,SDL_GetError());
	if(TTF_Init()<0) wprintf(L"\n%c	Could not initialize ttf: %S",0x488,TTF_GetError());
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048)<0) wprintf(L"\n%c	Could not initialize Mixer: %S",0x488,SDL_GetError());
	MainData.MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	//MainData.MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED);
	if (MainData.MainRender==NULL){
		wprintf(L"\n%c	Error:%S",0x488,SDL_GetError());
	}
	SDL_Event MainEvent;

	InitializeKeys(MainData.PreviousKey,KeyNumber); //Initializing the 14 keys
	InitializeKeys(MainData.FrameKey,KeyNumber);

	//---media files ---
	InitializeGlobal(&MainData);


	GameVersionMain(&MainData);// -> Data/Version.h

		/* Game Loop Started */
	//random seed
	time_t t;
	srand((unsigned) time(&t));
	//ID LIST - - with every ID of every object, sprite, font

	MainData.PrevTime=0;
	MainData.CurrentTime=0;
	MainData.FramesPerSecond=60;
	MainData.TicksPerFrame=round(1000/MainData.FramesPerSecond);

	wprintf(L"\n\n%c%c%c	Game Main Loop\n",0xf,0xf,0xf);
	//--------------GAME LOOP--------------//
	while( MainData.RoomCurrentID>0 ){	
		
		while(SDL_PollEvent(&MainData.MainEvent)!=1 && MainData.RoomCurrentID>0){

			/*		START GAME ROOMS		*/
			/*
			Room States, booleans to determine the state of the current Room:
			RoomState=0000 0001:	Loop Ended, and now changing Rooms
			RoomState=0000 0010:	Room is in continuous Loop
			RoomState=0000 0100:	Room in Pause

			*/
			if (MainData.RoomState&0x1){
				if 			(MainData.RoomCurrentID==	1	)	RoomMain_002(&MainData);
				else if 	(MainData.RoomCurrentID==	2	)	RoomMain_002(&MainData);
			}
		}
	}
	/* Game Loop ended */
	MainData.MainRender=NULL;
	wprintf(L"\n	Quitting game loop...\n");

	//Free resources and close SDL
	Closing(&MainData);
	return 0;
}