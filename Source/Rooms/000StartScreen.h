/*
Room 000: Start Screen

*/

void Objectload_000(GlobalVariables* Main){
	wprintf(L"\n%c%c	ID:000 Presentation Screen",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/
	srand(time(NULL));
	short i;

	wprintf(L"\n%c	Loading Background Image...",0x10);
	//sprite 000.
	SDL_Color color0={.r=0,.g=0,.b=0,.a=255}; // color de los textos "start" "quit"
	i=rand()%14;
	if 		(i==0)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (1).bmp",&error);
	else if (i==1)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (2).bmp",&error);
	else if (i==2)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (3).bmp",&error);
	else if (i==3)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (4).bmp",&error);
	else if (i==4)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (5).bmp",&error);
	else if (i==5)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (6).bmp",&error);
	else if (i==6)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (7).bmp",&error);
	else if (i==7)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (8).bmp",&error);
	else if (i==8)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (9).bmp",&error);
	else if (i==9)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (10).bmp",&error);
	else if (i==10)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (11).bmp",&error);
	else if (i==11)	(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (12).bmp",&error);
	else if (i==12) (((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (13).bmp",&error);
	else			(((Main->SpriteList)+0)->Texture)=LoadTexture(Main->MainRender,"media/backgrounds/Warrior (14).bmp",&error);
	
	SDL_QueryTexture((Main->SpriteList+0)->Texture,NULL,NULL,&((Main->SpriteList+0)->Width),&((Main->SpriteList+0)->Height));
	(Main->SpriteList+0)->FrameWidth=Main->SCREEN_WIDTH;
	(Main->SpriteList+0)->FrameHeight=Main->SCREEN_HEIGHT;
	(Main->SpriteList+0)->FrameNumber=1;
	(Main->SpriteList+0)->speed=0;
	if (!error & 0x3)
		wprintf(L"	Done");	


	wprintf(L"\n%c 	Loading Textures...",0x10);
	//sprite 001.
	error=~(~error|0x3);
	(Main->SpriteList+1)->Texture=LoadTexture(Main->MainRender,"media/items/companion.bmp",&error);
	SDL_QueryTexture((Main->SpriteList+1)->Texture,NULL,NULL,&((Main->SpriteList+1)->Width),&((Main->SpriteList+1)->Height));
	(Main->SpriteList+1)->FrameWidth=(Main->SpriteList+1)->Width;
	(Main->SpriteList+1)->FrameHeight=(Main->SpriteList+1)->Height;
	(Main->SpriteList+1)->FrameNumber=1;
	(Main->SpriteList+1)->speed=0;
	if (!error&0x3)
		wprintf(L" 1");
	//sprite002
	error=~(~error|0x1);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+2,"Start","fonts/Pangolin-Regular.ttf",60,&error);
	if (!error & 0x3)
		wprintf(L" 2");
	//sprite003
	error=~(~error|0x1);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+3,"Quit","fonts/Pangolin-Regular.ttf",60,&error);
	if (!error&0x3){
		wprintf(L" 3	Done");
	}
	
	wprintf(L"\n%c	Loading Sound...",0x10);

	error=~(~error|0x3);
	//SOUND 000.
	*(Main->SoundList+0)=Mix_LoadWAV("media/sounds/000.wav");
	if(*(Main->SoundList+0)==NULL) {
		wprintf(L"\n%c	could not load sound: %S",0x488,SDL_GetError());
		error|=0x3;
	}
	else {
		wprintf(L" 1");
		
	}
	//SOUND 001.
	error=~(~error|0x1);
	*(Main->SoundList+1)=Mix_LoadWAV("media/sounds/001.wav");
	if(*(Main->SoundList+1)==NULL) {
		wprintf(L"\n%c	Could not load sound: %S",0x488,SDL_GetError());
		error|=0x3;
	}
	else if (!error & 0x3){
		wprintf(L" 2		Done");
	}
	

	wprintf(L"\n%c 	Loading Music...",0x10);
	//Music 0
	error=~(~error|0x1);
	*(Main->SongList+0)=Mix_LoadMUS("media/music/000.mp3");
	if(*(Main->SongList+0)==NULL) {
		wprintf(L"\n%c	Could not load song: %S",0x488,SDL_GetError());
	}
	else wprintf(L"		Done\n");
	if (error){
		wprintf(L"\n%c%c 	Failed to load Room without problems \n",0x488,0x488);
	}

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
	wprintf(L"\n\n%c%c%c 		Room 000 		%c%c%c 	\n",4,4,4,4,4,4);
	//load media
	Objectload_000(Main);
	//Create Main Instances
	InstanceCreationCode_000(Main);
	Main->menu=11;
}//menu principal