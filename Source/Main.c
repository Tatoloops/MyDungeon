#include "Initialization/Initialization.h"
#include "Initialization/ClosingMedia.h"
#include "Data/Data.h"
#include "Characters/AssetPack.h"
#include "Rooms/Roompack.h"
#include "FrameUpdate/FrameUpdate.h"
//MAIN
int main( int argc, char* args[] ){
	printf("initializing variables...");

	GlobalVariables MainData;

	MainData.SCREEN_WIDTH=1280;
	MainData.SCREEN_HEIGHT=720;

	unsigned int PrevTime=0;
	unsigned int CurrentTime=0;
	unsigned int Frame=0;
	unsigned int PrevFrame=0;
	printf(" Done!\n");
	printf("Initializing SDL...");
	MainData.MainWindow=CreatingWindow(MainData.SCREEN_WIDTH,MainData.SCREEN_HEIGHT);
	SDL_GetWindowSize(MainData.MainWindow,&(MainData.SCREEN_WIDTH),&(MainData.SCREEN_HEIGHT));
	if(SDL_Init(SDL_INIT_AUDIO)<0) printf("could not initialize audio: %s",SDL_GetError());
	if(TTF_Init()<0) printf("could not initialize ttf: %s",TTF_GetError());
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048)<0) printf("could not initialize Mixer: %s",SDL_GetError());
	SDL_Renderer* MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED);
	MainData.MainRender=MainRender;
	//MainData.MainRender=SDL_CreateRenderer(MainData.MainWindow,-1,SDL_RENDERER_ACCELERATED);
	if (MainData.MainRender==NULL){
		printf("\nError:%s",SDL_GetError());
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

		/* Game Loop Started */
	//random seed
	time_t t;
	srand((unsigned) time(&t));
	//ID LIST - - with every ID of every object, sprite, font
	MainData.menu=10;
	printf("Running Game\n");
	while( MainData.menu>0 ){	//--------------GAME LOOP--------------//
		while(SDL_PollEvent(&MainEvent)!=1 && MainData.menu>0){

			CurrentTime=SDL_GetTicks();
			keypressed(MainData.PreviousKey);

			/*    FPS CONTROL       */
			if (CurrentTime>PrevTime+17){ // 33-> 30 fps   17->60 fps
				//StringCopy(key,framekey,KeyNumber);
				keycompare(MainData.FrameKey,MainData.PreviousKey);
				PrevFrame=Frame;
				++Frame;
				PrevTime=CurrentTime;
				Refresh(&MainData);
			}
			/* 		END	FPS			*/
			/*		START GAME ROOMS		*/
			if 	(MainData.menu==10){						// - - - ROOM 1 - - -
				printf("%c%c%c 		Room 000 		%c%c%c 	\n",176,177,178,178,177,176);
				Room000(&MainData);
			}
			else if (MainData.menu==20){ 	//(20) 21-30	// - - - ROOM 2 - - -
				printf("%c%c%c 		Room 001 		%c%c%c 	\n",176,177,178,178,177,176);
				Room001(&MainData);
			}
			else if 	(MainData.menu==30){	//(30) 31-40	// - - - ROOM 3 - - -
				printf("%c%c%c 		Room 002 		%c%c%c 	\n",176,177,178,178,177,176);
				Room002(&MainData);
			}
			else if 	(MainData.menu==40){	//(30) 31-40	// - - - ROOM 4 - - -
				printf("%c%c%c 		Room 003		%c%c%c 	\n",176,177,178,178,177,176);
				Room003(&MainData);
			}
			else if 	(MainData.menu==50){	//(30) 31-40	// - - - ROOM 5 - - -
				printf("%c%c%c 		Room 004 		%c%c%c 	\n",176,177,178,178,177,176);
				Room004(&MainData);
			}
			else if 	(MainData.menu==60){	//(30) 31-40	// - - - ROOM 6 - - -
				printf("%c%c%c 		Room 005 		%c%c%c 	\n",176,177,178,178,177,176);
				Room005(&MainData);
			}
			else if 	(MainData.menu==70){	//(30) 31-40	// - - - ROOM 7 - - -
				printf("%c%c%c 		Room 006 		%c%c%c 	\n",176,177,178,178,177,176);
				Room006(&MainData);
			}
			else if 	(MainData.menu==80){	//(30) 31-40	// - - - ROOM 8 - - -
				printf("%c%c%c 		Room 007 		%c%c%c 	\n",176,177,178,178,177,176);
				Room007(&MainData);
			}
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
	printf("Quitting game loop...\n");

	//Free resources and close SDL
	FreeMedia(SpriteList,SongList,SoundList);
	closing(MainData.MainWindow);
	return 0;
}