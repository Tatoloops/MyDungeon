/*
Room 000: Start Screen

*/

void Objectload_000(GlobalVariables* Main){
	printf("%c%c 	Objectload_000\n",176,177 );
	srand(time(NULL));
	short i;

	printf("%c 	Loading Background Image...",176);
	//sprite 000.
	SDL_Color color0={.r=0,.g=0,.b=0,.a=255}; // color de los textos "start" "quit"
	i=rand()%14;
	if 		(i==0) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (1).bmp");
	else if (i==1) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (2).bmp");
	else if (i==2) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (3).bmp");
	else if (i==3) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (4).bmp");
	else if (i==4) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (5).bmp");
	else if (i==5) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (6).bmp");
	else if (i==6) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (7).bmp");
	else if (i==7) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (8).bmp");
	else if (i==8) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (9).bmp");
	else if (i==9) 	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (10).bmp");
	else if (i==10)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (11).bmp");
	else if (i==11)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (12).bmp");
	else if (i==12) (((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (13).bmp");
	else 			(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (14).bmp");
	
	SDL_QueryTexture((Main->SpriteList+0)->Texture,NULL,NULL,&((Main->SpriteList+0)->Width),&((Main->SpriteList+0)->Height));
	(Main->SpriteList+0)->FrameWidth=Main->SCREEN_WIDTH;
	(Main->SpriteList+0)->FrameHeight=Main->SCREEN_HEIGHT;
	(Main->SpriteList+0)->FrameNumber=1;
	(Main->SpriteList+0)->speed=0;
	printf("	Done	\n");
	printf("%c 	Loading Textures...",176);

	//sprite 001.
	(Main->SpriteList+1)->Texture=LoadTexture(Main->MainRender,"media/items/companion.bmp");
	SDL_QueryTexture((Main->SpriteList+1)->Texture,NULL,NULL,&((Main->SpriteList+1)->Width),&((Main->SpriteList+1)->Height));
	(Main->SpriteList+1)->FrameWidth=(Main->SpriteList+1)->Width;
	(Main->SpriteList+1)->FrameHeight=(Main->SpriteList+1)->Height;
	(Main->SpriteList+1)->FrameNumber=1;
	(Main->SpriteList+1)->speed=0;
	printf(" 1");
	//sprite002
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+2,"Start","fonts/Amatic-Bold.ttf",60);
	printf(" 2");
	//sprite003
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+3,"Quit","fonts/Amatic-Bold.ttf",60);
	printf(" 3");
	printf("	Done	\n");
	printf("%c 	Loading Sound...",176);
	//SOUND 000.
	*(Main->SoundList+0)=Mix_LoadWAV("media/sounds/000.wav");
	if(*(Main->SoundList+0)==NULL) printf("could not load sound: %s",SDL_GetError());
	else printf(" 1");
	//SOUND 001.
	*(Main->SoundList+1)=Mix_LoadWAV("media/sounds/001.wav");
	if(*(Main->SoundList+1)==NULL) printf("could not load sound: %s",SDL_GetError());
	else printf(" 2");
	printf("		Done	\n");

	printf("%c 	Loading Music...",176);
	//Music 0
	i=rand()%3;
	if(i==0) *(Main->SongList+0)=Mix_LoadMUS("media/music/000.mp3");
	printf(" 1");
	if(i==1) *(Main->SongList+0)=Mix_LoadMUS("media/music/001.mp3");
	printf(" 2");
	if(i==2) *(Main->SongList+0)=Mix_LoadMUS("media/music/002.mp3");
	printf(" 3");
	if(*(Main->SongList+0)==NULL) printf("could not load song: %s",SDL_GetError());
	else printf("		Done	\n");

	return;
}//Presentation screen

void InstanceCreationCode_000(GlobalVariables* Main){ // main menu 1
	(Main->InstanceList+(Main->ins_count))->ID =000;
	(Main->InstanceList+(Main->ins_count))->x=0;
	(Main->InstanceList+(Main->ins_count))->y=0;
	(Main->InstanceList+(Main->ins_count))->sprite=NULL;
	(Main->InstanceList+(Main->ins_count))->data[0]=1; // 1 button on start. 2 button on quit
	(Main->InstanceList+(Main->ins_count))->data[1]=255; // timer
	Mix_PlayMusic(*(Main->SongList+0),-1);
	++(Main->ins_count);

}

void InstanceStepCode_000(GlobalVariables* Main, Instance* CurrentInstance){
	// Object 000 is the first menu that appears on the menu 1.

	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+0)->Texture,NULL,NULL);
	//take variables
	int settings=((CurrentInstance)->data)[0];
	int timer=((CurrentInstance)->data)[1];
	Main->saved_data->battle=0;
	//control
	/* settings 1: Start button
				2: Quit button
				3: you pressed start button and you are now starting the game
				4: you pressed the quit button and now you are quitting			*/
	if (settings<3){
		if (Main->FrameKey[0]&1){
			settings=1;
			Mix_PlayChannel(0,Main->SoundList+0,1);
		}

		else if (Main->FrameKey[1]&1) 	{ //press down
			settings=2;
			Mix_PlayChannel(0,Main->SoundList+0,1);
		}
		else if (Main->FrameKey[5]&1){
				if (settings==1){
					settings=3;//press x
					Mix_PlayChannel(0,Main->SoundList+1,1);
				}
				else if (settings==2){
					settings=4; //quit
					Mix_PlayChannel(0,Main->SoundList+1,1);
				}
			}
		else if (Main->FrameKey[6]&1)	{	//pres c
			if (settings==1){
				settings=2;
				Mix_PlayChannel(0,Main->SoundList+0,1);
			}
			else{
				settings=4;
				Mix_PlayChannel(0,Main->SoundList+1,1);
			}
		}
		else if (Main->FrameKey[12]&1)	{ //press esc
			settings=4;
			Mix_PlayChannel(0,Main->SoundList+1,1);
		}
	}
	else if (settings==3){ //start button pressed
		if (timer<=0){
			short i;
			for(i=0;i<7;++i){
			(Main->saved_data+i)->race=0;
			(Main->saved_data+i)->CharacterClass=0;
			(Main->saved_data+i)->lvl=0;
			}
			Main->menu=20; //start game
		}
		timer-=10;
	}
	else if (settings==4) {// quit button pressed
		if (timer<=0){
			Main->menu=0; // quit game
		}
		timer-=10;
	}
	//end control
	SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-120,.y=(5*Main->SCREEN_HEIGHT)/6,.w=(Main->SpriteList+1)->Width,.h=(Main->SpriteList+1)->Height};
	SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-60,.y=(4*Main->SCREEN_HEIGHT)/6-20,.w=(Main->SpriteList+2)->Width,.h=(Main->SpriteList+2)->Height};
	SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2-60,.y=(5*Main->SCREEN_HEIGHT)/6-20,.w=(Main->SpriteList+3)->Width,.h=(Main->SpriteList+3)->Height};
	if 		(settings==1 || settings==3) // on start button
		rect1.y=4*((Main->SpriteList+0)->FrameHeight)/6;
	else if (settings==2 || settings==4) // on quit button
		rect1.y=5*((Main->SpriteList+0)->FrameHeight)/6;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+3)->Texture,NULL,&rect3);
	//save changes on used variables
	((CurrentInstance)->data)[0]=settings;
	((CurrentInstance)->data)[1]=timer;
	return;
}//menu principal

void Room000(GlobalVariables* Main){

	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	//load media
	printf("%c%c 	Loading Menu...\n",176,177);
	Objectload_000(Main);
	printf("%c%c 	Done Loading Menu.\n",176,177);
	InstanceCreationCode_000(Main);
	Main->menu=11;
}//menu principal