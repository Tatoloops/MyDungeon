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

	unsigned int PrevTime=0;
	unsigned int CurrentTime=0;
	unsigned int Frame=0;
	unsigned int PrevFrame=0;
	wprintf(L"	Done!");
	wprintf(L"\n%c	Initializing SDL...",0x10);
	MainData.MainWindow=CreatingWindow(MainData.SCREEN_WIDTH,MainData.SCREEN_HEIGHT);
	SDL_GetWindowSize(MainData.MainWindow,&(MainData.SCREEN_WIDTH),&(MainData.SCREEN_HEIGHT));
	if(SDL_Init(SDL_INIT_AUDIO)<0) wprintf(L"\n%c	Could not initialize audio: %S",0x488,SDL_GetError());
	if(TTF_Init()<0) wprintf(L"\n%c	Could not initialize ttf: %S",0x488,TTF_GetError());
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048)<0) wprintf(L"\n%c	Could not initialize Mixer: %S",0x488,SDL_GetError());
	SDL_Renderer* MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED);
	MainData.MainRender=MainRender;
	//MainData.MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED);
	if (MainData.MainRender==NULL){
		wprintf(L"\n%c	Error:%S",0x488,SDL_GetError());
	}
	SDL_Event MainEvent;

	InitializeKeys(MainData.PreviousKey,KeyNumber); //Initializing the 14 keys
	InitializeKeys(MainData.FrameKey,KeyNumber);

	//---media files ---
	/*Here the variable 'menu' is being used as a counter, i did it that way to save memory, because i am greedy as heck*/
	Sprite SpriteList[MaxSprites];
	for(MainData.menu=0;MainData.menu<MaxSprites;++MainData.menu)
		InitializeSprite(SpriteList+MainData.menu);

	Mix_Music * SongList[MaxSongs];
	for(MainData.menu=0;MainData.menu<MaxSongs;++MainData.menu)
		SongList[MainData.menu]=NULL;

	Mix_Chunk * SoundList[MaxSounds];
	for(MainData.menu=0;MainData.menu<MaxSounds;++MainData.menu)
		SoundList[MainData.menu]=NULL;

	Instance InstanceList[MaxInstances];
	for(MainData.menu=0;MainData.menu<MaxInstances;++MainData.menu)
		InitializeInstance(InstanceList+MainData.menu);
	MainData.ins_count=0;

	MainData.InstanceList=InstanceList;
	MainData.SpriteList=SpriteList;
	MainData.SongList=SongList;
	MainData.SoundList=SoundList;

	GameVersionMain(&MainData);// -> Data/Version.h

		/* Game Loop Started */
	//random seed
	time_t t;
	srand((unsigned) time(&t));
	//ID LIST - - with every ID of every object, sprite, font
	MainData.menu=10;

	unsigned short FramesPerSecond=60;
	unsigned short TicksPerFrame=round(1000/FramesPerSecond);
	wprintf(L"\n\n%c%c%c	Game Main Loop\n",0xf,0xf,0xf);
	//--------------GAME LOOP--------------//
	while( MainData.menu>0 ){	
		
		while(SDL_PollEvent(&MainEvent)!=1 && MainData.menu>0){

			/*    FPS CONTROL       */
			
			keypressed(MainData.PreviousKey);

			CurrentTime=SDL_GetTicks();
			if (CurrentTime>PrevTime+TicksPerFrame){ // 33-> 30 fps   17->60 fps
				//StringCopy(key,framekey,KeyNumber);
				keycompare(MainData.FrameKey,MainData.PreviousKey);
				//PrevFrame=Frame;
				//++Frame;
				PrevTime=CurrentTime;
				Refresh(&MainData);
			}
			else
				usleep(1000*(PrevTime+TicksPerFrame-CurrentTime));
			/* 		END	FPS			*/

			/*		START GAME ROOMS		*/
			if 			(MainData.menu==10)	Room000(&MainData);
			else if 	(MainData.menu==20)	Room001(&MainData);
			else if 	(MainData.menu==30)	Room002(&MainData);
			else if 	(MainData.menu==40)	Room003(&MainData);
			else if 	(MainData.menu==50)	Room004(&MainData);
			else if 	(MainData.menu==60)	Room005(&MainData);
			else if 	(MainData.menu==70)	Room006(&MainData);
			else if 	(MainData.menu==80)	Room007(&MainData);

			/* 	END 	GAME 	ROOMS*/
			if(MainEvent.type==SDL_QUIT)
				MainData.menu=0;
			if(MainData.FrameKey[13]&0x1)
				if(Mix_PlayingMusic()){
					if(Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
				}
			if(MainData.FrameKey[12] & 0x1)
				MainData.menu=0;
		}
	}
	/* Game Loop ended */
	SDL_DestroyRenderer(MainData.MainRender);
	MainData.MainRender=NULL;
	wprintf(L"\n	Quitting game loop...\n");

	//Free resources and close SDL
	FreeMedia(SpriteList,SongList,SoundList);
	closing(MainData.MainWindow);
	return 0;
}