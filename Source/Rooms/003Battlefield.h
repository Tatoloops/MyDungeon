/*
Room 003:Main Battlefield

*/

void Objectload_003(GlobalVariables* Main){//Battlefield
	wprintf(L"\n%c%c	ID:003 BattleField",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/
	
	//sprites
	CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+0,"media/backgrounds/400.bmp",&error); //background
	CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+1,"media/characters/400.bmp",&error); //Enemy spot
	CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+2,"media/characters/400.bmp",&error); //Player spot

	SDL_Color Color1={.r=255,.g=255,.b=255,.a=255};
	SDL_Color Color2={.r=255,.g=0,.b=100,.a=255};

	CreateNonAnimatedFont(Main->MainRender,&Color1,Main->SpriteList+3,"Back to the Bazar","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&Color1,Main->SpriteList+4,"Next Battle","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&Color1,Main->SpriteList+5,"Retry","fonts/Pangolin-Regular.ttf",60,&error);

	CreateNonAnimatedFont(Main->MainRender,&Color2,Main->SpriteList+6,"Back to the Bazar","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&Color2,Main->SpriteList+7,"Next Battle","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&Color2,Main->SpriteList+8,"Retry","fonts/Pangolin-Regular.ttf",60,&error);

	CreateNonAnimatedFont(Main->MainRender,&Color2,Main->SpriteList+9,"YOU WIN !","fonts/Stylish-Regular.ttf",72,&error);
	CreateNonAnimatedFont(Main->MainRender,&Color2,Main->SpriteList+10,"You're dead...","fonts/MortifiedDrip.ttf",72,&error);


	*(Main->SongList+0)=Mix_LoadMUS("media/music/400.mp3");
	if(*(Main->SongList+0)==NULL) wprintf(L"could not load song: %s",SDL_GetError());
	return;
}//Battlefield
void InstanceCreationCode_003(GlobalVariables* Main){ // Battlefield
	(Main->InstanceList+(Main->ins_count))->ID =004;
	(Main->InstanceList+(Main->ins_count))->x=Main->SCREEN_WIDTH/2;
	(Main->InstanceList+(Main->ins_count))->y=Main->SCREEN_HEIGHT/2;
	(Main->InstanceList+(Main->ins_count))->sprite=NULL;
	(Main->InstanceList+(Main->ins_count))->data[0]=0;
	(Main->InstanceList+(Main->ins_count))->data[1]=0;  //matrix  de datas: 	1 - 2 - 3
	(Main->InstanceList+(Main->ins_count))->data[2]=0; //						4 - 5 - 6
	(Main->InstanceList+(Main->ins_count))->data[3]=0; //						7 - 8 - 9
	(Main->InstanceList+(Main->ins_count))->data[4]=0;
	(Main->InstanceList+(Main->ins_count))->data[5]=0;
	(Main->InstanceList+(Main->ins_count))->data[6]=0;
	(Main->InstanceList+(Main->ins_count))->data[7]=0;
	(Main->InstanceList+(Main->ins_count))->data[8]=0;
	(Main->InstanceList+(Main->ins_count))->data[9]=0;
	(Main->InstanceList+(Main->ins_count))->data[10]=0;
	(Main->InstanceList+(Main->ins_count))->data[11]=0; //contador de frame de animacion 1
	(Main->InstanceList+(Main->ins_count))->data[12]=0;//contador de avance de frame de animacion 1
	(Main->InstanceList+(Main->ins_count))->data[13]=0; //win por lose
	(Main->InstanceList+(Main->ins_count))->data[19]=100; //wait


	Mix_PlayMusic(*(Main->SongList+0),-1);
	++(Main->ins_count);
} // battlefield
void InstanceStepCode_003(GlobalVariables* Main,Instance* CurrentInstance){

	int win=CurrentInstance->data[13];
	int battle=Main->saved_data->battle;

	if (win==1){ //win
		Mix_PauseMusic();
		win=3;
		int newgold=rand()%50;
		int newexp=rand()%50+50;
		wprintf(L"+%d gold!\n",newgold);
		wprintf(L"+%d exp!\n",newexp);
		Main->saved_data->hp=(Main->InstanceList+1)->data[7];
		if (Main->saved_data->hp<1)
			Main->saved_data->hp=1;
		Main->saved_data->gold+=newgold;
		Main->saved_data->exp+=newexp;
		Main->saved_data->inv[1]=(Main->InstanceList+1)->data[8];
		Main->saved_data->inv[2]=(Main->InstanceList+1)->data[9];
		if (Main->saved_data->exp>100){
			levelup(Main->saved_data);
		}
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect1);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==2){ //lose
		win=4;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect1);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==3){ //win button back to tabern
		if (CurrentInstance->data[19]>1)
			--CurrentInstance->data[19];
		else
			if (Main->menu<72)
				Main->menu+=9;
			else{
				if(Main->FrameKey[3]&1){
					win=5; //next battle button
				}
				else if(Main->FrameKey[5]&1){
					Main->menu=30;
				}
			}
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2+MatrixSpace/2,.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+3)->Texture,NULL,&rect2);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+7)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if (win==4){ //lose button back to tabbern
		if (CurrentInstance->data[19]>1)
			--CurrentInstance->data[19];
		else
			if(Main->FrameKey[3]&1){
				win=6; //next battle button
			}
			else if(Main->FrameKey[5]&1){
				Main->menu=30;
			}
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2+MatrixSpace/2,.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+3)->Texture,NULL,&rect2);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+8)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if(win==5){ //win button back to tabern
		if(Main->FrameKey[2]&1){
			win=3; //next battle button
		}
		else if(Main->FrameKey[5]&1){
			Main->menu=40;
		}
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2+MatrixSpace/2,.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+6)->Texture,NULL,&rect2);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+4)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	else if (win==6){ //lose button back to tabbern
		if(Main->FrameKey[2]&1){
			win=4; //next battle button
		}
		else if(Main->FrameKey[5]&1){
			Main->menu=40;
		}
		SDL_SetRenderDrawColor(Main->MainRender,0,0,0,255);
		SDL_RenderFillRect(Main->MainRender,NULL);
		SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-MatrixSpace,.y=Main->SCREEN_HEIGHT/2-MatrixSpace,.w=MatrixSpace*2,.h=MatrixSpace};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect1);
		SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-(3*MatrixSpace/2),.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2+MatrixSpace/2,.y=Main->SCREEN_HEIGHT/2,.w=MatrixSpace,.h=MatrixSpace/2};
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+6)->Texture,NULL,&rect2);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect3);
		CurrentInstance->data[13]=win;
		return;
	}
	if ((Main->InstanceList+2)->data[5]<1) //monster died
		win=1;
	else if((Main->InstanceList+1)->data[7]<1) //human died
		win=2;

	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+0)->Texture,NULL,NULL);
	// (CurrentInstance)->data[11]; //contador de frame
	// (CurrentInstance)->data[12]; //contador de avance
	SDL_Rect rect1a={
		.x=0,
		.y=0,
		.w=(Main->SpriteList+1)->FrameWidth,
		.h=(Main->SpriteList+1)->FrameHeight};
	ActualizacionDeAnimacion(&rect1a,(Main->SpriteList+1),(CurrentInstance)->data+11,(CurrentInstance)->data+12);
	SDL_Rect rect1b={
		.x=Main->SCREEN_WIDTH/2-MatrixSpace-((Main->SpriteList+1)->FrameWidth)/2,
		.y=Main->SCREEN_HEIGHT/2-MatrixSpace-((Main->SpriteList+1)->FrameHeight)/2,
		.w=(Main->SpriteList+1)->FrameWidth,
		.h=(Main->SpriteList+1)->FrameHeight}; //enemy spot

	SDL_Rect rect2={
		.x=Main->SCREEN_WIDTH/2-MatrixSpace-((Main->SpriteList+2)->FrameWidth)/2,
		.y=Main->SCREEN_HEIGHT/2-((Main->SpriteList+2)->FrameHeight)/2,
		.w=(Main->SpriteList+2)->FrameWidth,
		.h=(Main->SpriteList+2)->FrameHeight}; //player spot

	//printing the battlefield
	//monster spot
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,&rect1a,&rect1b);
	rect1b.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,&rect1a,&rect1b);
	rect1b.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,&rect1a,&rect1b);
	//player spot
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	rect2.x-=2*MatrixSpace;
	rect2.y+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
	rect2.x+=MatrixSpace;
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);

	//printing monster hp and player hp

	int hpheight=Main->SCREEN_HEIGHT-80;
	//monster hp bar
	int monsterHP=(Main->InstanceList+2)->data[5];

	if (monsterHP>0){
		int monsterMAXHP=(Main->InstanceList+2)->data[8];
		SDL_Rect monsterHPext={.x=Main->SCREEN_WIDTH-65,.y=30,.w=60,.h=Main->SCREEN_HEIGHT-60};
		SDL_Rect monsterHPint={.x=Main->SCREEN_WIDTH-55,.y=40,.w=40,.h=hpheight};

		monsterHPint.h=(hpheight*monsterHP)/monsterMAXHP;

		SDL_SetRenderDrawColor(Main->MainRender,10,10,10,255);
		SDL_RenderFillRect(Main->MainRender,&monsterHPext);
		SDL_SetRenderDrawColor(Main->MainRender,255,10,60,255);
		SDL_RenderFillRect(Main->MainRender,&monsterHPint);
	}
	//player hp bar

	int playerHP=(Main->InstanceList+1)->data[7];

	if (playerHP>0){
		int playerbarwidth=100;

		int playerMAXHP=Main->saved_data->maxhp;

		SDL_Rect playerHPext={.x=10,.y=Main->SCREEN_HEIGHT-24,.w=playerbarwidth+4,.h=14};
		SDL_Rect playerHPint={.x=12,.y=Main->SCREEN_HEIGHT-22,.w=playerbarwidth,.h=10};

		playerHPint.w=(playerbarwidth*playerHP)/playerMAXHP;

		SDL_SetRenderDrawColor(Main->MainRender,10,10,10,255);
		SDL_RenderFillRect(Main->MainRender,&playerHPext);
		SDL_SetRenderDrawColor(Main->MainRender,255,10,60,255);
		SDL_RenderFillRect(Main->MainRender,&playerHPint);
	}

	CurrentInstance->data[13]=win;
	return;
}//Battlefield
void Room003(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	wprintf(L"\n\n%c%c%c 		Room 003 		%c%c%c 	\n",4,4,4,4,4,4);
	//load media
	Objectload_003(Main);
	Objectload_005(Main);
	Objectload_006(Main);
	Objectload_007(Main);
	Objectload_008(Main);
	Objectload_009(Main);
	

	InstanceCreationCode_003(Main);
	InstanceCreationCode_005(Main);
	InstanceCreationCode_006(Main);
	Main->menu=41;
} //Battlefield
void Room004(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	wprintf(L"\n\n%c%c%c 		Room 004 		%c%c%c 	\n",4,4,4,4,4,4);
	//load media
	Objectload_003(Main);
	Objectload_005(Main);
	Objectload_006(Main);
	Objectload_007(Main);
	Objectload_008(Main);
	Objectload_009(Main);

	InstanceCreationCode_003(Main);
	InstanceCreationCode_005(Main);
	InstanceCreationCode_006(Main);
	Main->menu=51;
} //Battlefield2
void Room005(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	//load media
	wprintf(L"\n\n%c%c%c 		Room 005 		%c%c%c 	\n",4,4,4,4,4,4);
	Objectload_003(Main);
	Objectload_005(Main);
	Objectload_006(Main);
	Objectload_007(Main);
	Objectload_008(Main);
	Objectload_009(Main);

	InstanceCreationCode_003(Main);
	InstanceCreationCode_005(Main);
	InstanceCreationCode_006(Main);
	Main->menu=61;
} //Battlefield3
void Room006(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	//load media
	wprintf(L"\n\n%c%c%c 		Room 006 		%c%c%c 	\n",4,4,4,4,4,4);
	Objectload_003(Main);
	Objectload_005(Main);
	Objectload_006(Main);
	Objectload_007(Main);
	Objectload_008(Main);
	Objectload_009(Main);

	InstanceCreationCode_003(Main);
	InstanceCreationCode_005(Main);
	InstanceCreationCode_006(Main);
	Main->menu=71;
} //Battlefield4
void Room007(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	wprintf(L"\n\n%c%c%c 		Room 007 		%c%c%c 	\n",4,4,4,4,4,4);
	//load media
	Objectload_003(Main);
	Objectload_005(Main);
	Objectload_006(Main);
	Objectload_007(Main);
	Objectload_008(Main);
	Objectload_009(Main);

	InstanceCreationCode_003(Main);
	InstanceCreationCode_005(Main);
	InstanceCreationCode_006(Main);
	Main->menu=81;
} //Battlefield5