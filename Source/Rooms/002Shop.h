/*
Room 002: Shop


*/
void Objectload_002(GlobalVariables* Main){
	wprintf(L"\n%c%c	ID:002 Store",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/
	srand(time(NULL));
	short i;
	//sprite 000
	SDL_Color color0={.r=255,.g=255,.b=255,.a=255};
	i=rand()%2;
	if(i==0) (Main->SpriteList+0)->Texture=LoadTexture(Main->MainRender,"media/backgrounds/Store (1).bmp",&error);
	else if(i==1) (Main->SpriteList+0)->Texture=LoadTexture(Main->MainRender,"media/backgrounds/Store (2).bmp",&error);
	SDL_QueryTexture((Main->SpriteList+0)->Texture,NULL,NULL,&((Main->SpriteList+0)->Width),&((Main->SpriteList+0)->Height));
	//(SpriteList+0)->Width=SCREEN_WIDTH;
	//(SpriteList+0)->Height=SCREEN_HEIGHT;
	(Main->SpriteList+0)->FrameWidth=Main->SCREEN_WIDTH;
	(Main->SpriteList+0)->FrameHeight=Main->SCREEN_HEIGHT;
	(Main->SpriteList+0)->FrameNumber=1;
	(Main->SpriteList+0)->speed=0;
	if ((Main->SpriteList+0)->Texture==NULL)
		wprintf(L"couldn't load background image %s",SDL_GetError);
	//sprite 001.
	(Main->SpriteList+1)->Texture=LoadTexture(Main->MainRender,"media/items/coin.bmp",&error);
	SDL_QueryTexture((Main->SpriteList+1)->Texture,NULL,NULL,&((Main->SpriteList+1)->Width),&((Main->SpriteList+1)->Height));
	//(SpriteList+1)->Width=SCREEN_WIDTH;
	//(SpriteList+1)->Height=SCREEN_HEIGHT;
	(Main->SpriteList+1)->FrameWidth=(Main->SpriteList+1)->Width;
	(Main->SpriteList+1)->FrameHeight=(Main->SpriteList+1)->Height;
	(Main->SpriteList+1)->FrameNumber=1;
	(Main->SpriteList+1)->speed=0;
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+2,"Items","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+3,"Stats","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+4,"Continue","fonts/Pangolin-Regular.ttf",60,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+5,"Back","fonts/Pangolin-Regular.ttf",60,&error);
	(Main->SpriteList+6)->Texture=LoadTexture(Main->MainRender,"media/items/itemmenu.bmp",&error);
	(Main->SpriteList+7)->Texture=LoadTexture(Main->MainRender,"media/items/potion1.bmp",&error);
	(Main->SpriteList+8)->Texture=LoadTexture(Main->MainRender,"media/items/potion2.bmp",&error);
	color0.r=0;
	color0.g=0;
	color0.b=0;
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+9,"health potion","fonts/Halt.ttf",50,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+10,"mana potion","fonts/Halt.ttf",50,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+11,"Health","fonts/Halt.ttf",50,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+12,"Defense","fonts/Halt.ttf",50,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+13,"Attack","fonts/Halt.ttf",50,&error);
	//SOUND 000.
	*(Main->SoundList+0)=Mix_LoadWAV("media/sounds/000.wav");
	if(*(Main->SoundList+0)==NULL) wprintf(L"\ncould not load sound: %s",SDL_GetError());
	*(Main->SoundList+1)=Mix_LoadWAV("media/sounds/001.wav");
	if(*(Main->SoundList+1)==NULL) wprintf(L"\ncould not load sound: %s",SDL_GetError());
	//Music 0
	i=rand()%2;
	if(i==0) *(Main->SongList+0)=Mix_LoadMUS("media/music/200.mp3");
	if(i==1) *(Main->SongList+0)=Mix_LoadMUS("media/music/201.mp3");
	if(*(Main->SongList+0)==NULL) wprintf(L"\ncould not load song: %s",SDL_GetError());
}//Shopkeeper
void InstanceCreationCode_002(GlobalVariables* Main){ // main menu 1
	(Main->InstanceList+(Main->ins_count))->ID =002;
	(Main->InstanceList+(Main->ins_count))->x=0;
	(Main->InstanceList+(Main->ins_count))->y=0;
	(Main->InstanceList+(Main->ins_count))->sprite=NULL;
	(Main->InstanceList+(Main->ins_count))->data[0]=1; // 1 button on items. 2 button on stats .3 button on back
	(Main->InstanceList+(Main->ins_count))->data[1]=255; // timer
	Mix_PlayMusic(*(Main->SongList+0),-1);
	++(Main->ins_count);
}
void InstanceStepCode_002(GlobalVariables* Main,Instance* CurrentInstance){
	// Object 000 is the first menu that appears on the menu 1.

	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+0)->Texture,NULL,NULL);
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
		if (Main->FrameKey[0]&1){//press up
			settings--;
			if(settings<1) settings=1;
			if(settings==3) settings=2;
			Mix_PlayChannel(0,Main->SoundList+0,1);
		}

		else if (Main->FrameKey[1]&1) 	{ //press down
			settings++;
			if(settings>4) settings=3;
			Mix_PlayChannel(0,Main->SoundList+0,1);
		}
		else if ((Main->FrameKey[2]&1)&&(settings==3))  { //press left
			settings++;

			Mix_PlayChannel(0,Main->SoundList+0,1);
		}
		else if ((Main->FrameKey[3]&1)&&(settings==4)) { //press right
			settings--;
			Mix_PlayChannel(0,Main->SoundList+0,1);
		}
		else if (Main->FrameKey[5]&1){	//press x
				if (settings==1){
					settings=5;//items
					Mix_PlayChannel(0,Main->SoundList+1,1);
				}
				else if (settings==2){
					settings=6; //stats
					Mix_PlayChannel(0,Main->SoundList+1,1);
				}
				else if (settings==3){
					settings=7;//next screen of the game
					Mix_PlayChannel(0,Main->SoundList+1,1);
				}
				else if (settings==4){
					settings=8;//back confirmed
					Mix_PlayChannel(0,Main->SoundList+0,1);
				}
			}
		else if (Main->FrameKey[12]&1)	{ //press esc
			settings=8;
			Mix_PlayChannel(0,Main->SoundList+1,1);
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
			Main->menu=40; //ir al campo de batalla
		}
		timer-=10;
	}
	else if (settings==8) {// back button pressed
		if(timer<=0){
			Main->menu=20;
		}
		timer-=10;
	}
	//end control
	SDL_Rect rect1={.x=Main->SCREEN_WIDTH/2-120,.y=(5*Main->SCREEN_HEIGHT)/6,
		.w=(Main->SpriteList+1)->Width,.h=(Main->SpriteList+1)->Height};
    SDL_Rect rect2={.x=Main->SCREEN_WIDTH/2-60,.y=(3*Main->SCREEN_HEIGHT)/6-20,
    	.w=(Main->SpriteList+2)->Width,.h=(Main->SpriteList+2)->Height};
    SDL_Rect rect3={.x=Main->SCREEN_WIDTH/2-60,.y=(4*Main->SCREEN_HEIGHT)/6-20,
    	.w=(Main->SpriteList+3)->Width,.h=(Main->SpriteList+3)->Height};
    SDL_Rect rect4={.x=2*Main->SCREEN_WIDTH/3-60,.y=(5*Main->SCREEN_HEIGHT)/6-20,
    	.w=(Main->SpriteList+4)->Width,.h=(Main->SpriteList+4)->Height};
    SDL_Rect rect5={.x=Main->SCREEN_WIDTH/3-60,.y=(5*Main->SCREEN_HEIGHT)/6-20,
    	.w=(Main->SpriteList+5)->Width,.h=(Main->SpriteList+5)->Height};
    SDL_Rect rect6={.x=Main->SCREEN_WIDTH/2-362,.y=(Main->SCREEN_HEIGHT)/2-110,
    	.w=22*Main->SCREEN_WIDTH/36,.h=22*Main->SCREEN_HEIGHT/36};
    SDL_Rect rect7={.x=7*Main->SCREEN_WIDTH/18,.y=(3*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+7)->Width,.h=(Main->SpriteList+7)->Height};
    SDL_Rect rect8={.x=7*Main->SCREEN_WIDTH/18,.y=(4*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+8)->Width,.h=(Main->SpriteList+8)->Height};
    SDL_Rect rect9={.x=8*Main->SCREEN_WIDTH/18,.y=(3*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+9)->Width,.h=(Main->SpriteList+9)->Height};
    SDL_Rect rect10={.x=8*Main->SCREEN_WIDTH/18,.y=(4*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+10)->Width,.h=(Main->SpriteList+10)->Height};
    SDL_Rect rect11={.x=7*Main->SCREEN_WIDTH/18,.y=(3*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+11)->Width,.h=(Main->SpriteList+11)->Height};
    SDL_Rect rect12={.x=7*Main->SCREEN_WIDTH/18,.y=(3.3*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+12)->Width,.h=(Main->SpriteList+12)->Height};
    SDL_Rect rect13={.x=7*Main->SCREEN_WIDTH/18,.y=(3.6*Main->SCREEN_HEIGHT)/6,
    	.w=(Main->SpriteList+13)->Width,.h=(Main->SpriteList+13)->Height};

	if 		(settings==1) // on item button
		rect1.y=3*((Main->SpriteList+0)->FrameHeight)/6;
	else if (settings==2) // on stats button
		rect1.y=4*((Main->SpriteList+0)->FrameHeight)/6;
	else if (settings==3){ // on continue button
		rect1.y=5*((Main->SpriteList+0)->FrameHeight)/6;
		rect1.x=2*(Main->SCREEN_WIDTH/3-60);
	}
	else if (settings==4){// on back button
		rect1.y=5*((Main->SpriteList+0)->FrameHeight)/6;
		rect1.x=(Main->SCREEN_WIDTH/3)-120;
	}

	else if (settings==5){//just pressed items
		smenu=1;
		if(items<4){
			if(Main->FrameKey[0]&1){
				items--;
				if(items<1) items=1;
			}
			if(Main->FrameKey[1]&1){
				items++;
				if(items>3) items=3;
			}
			if(Main->FrameKey[2]&1) items=3;
			if(Main->FrameKey[3]&1) items=1;
			if(Main->FrameKey[4]&1){
				if(items==1&&Main->saved_data->gold>=5){//life pot
					Main->saved_data->gold-=5;
					Main->saved_data->inv[1]+=1;
				}
				else if(items==2&&Main->saved_data->gold>=6){//mana pot
					Main->saved_data->gold-=6;
					Main->saved_data->inv[2]+=1;

				}
				else if(items==3){//back
					items=1;
					smenu=0;
					settings=1;
				}
			}


			if(items==1){//coin in items menu
				rect1.y=18.5*((Main->SpriteList+0)->FrameHeight)/36;
				rect1.x=13*Main->SCREEN_WIDTH/36;
			}
			else if(items==2){
				rect1.y=24.5*((Main->SpriteList+0)->FrameHeight)/36;
				rect1.x=13*Main->SCREEN_WIDTH/36;
			}
			else if(items==3){
				rect1.y=(15*Main->SCREEN_HEIGHT)/18;
				rect1.x=Main->SCREEN_WIDTH/3-100;
			}

		}
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect5);//back button
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+6)->Texture,NULL,&rect6);//paper
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+7)->Texture,NULL,&rect7);//r potion
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+8)->Texture,NULL,&rect8);//b potion
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect9);//r text
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect10);//b text
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);

		((CurrentInstance))->data[2]=items;
		if(Main->FrameKey[6]&1){
			smenu=0;
			settings=1;
		}
	}//potions menu

	else if (settings==6){//just pressed stats upgrade
		smenu=2;
		if(stats<5){
			if(stats<1) stats=1;
			if(Main->FrameKey[0]&1){
				stats--;
				if(stats<1) stats=1;
			}
			if(Main->FrameKey[1]&1){
				stats++;
				if(stats>4) stats=4;
			}
			if(Main->FrameKey[2]&1) stats=3;
			if(Main->FrameKey[3]&1) stats=1;
			if(Main->FrameKey[4]&1){
				if(stats==1&&Main->saved_data->gold>=30){//hp
					Main->saved_data->gold-=30;
					Main->saved_data->maxhp+=6;
				}
				else if(stats==2&&Main->saved_data->gold>=13){//def
					Main->saved_data->gold-=13;
					Main->saved_data->def+=1;
				}
				else if(stats==3&&Main->saved_data->gold>=10){//atk
					Main->saved_data->gold-=10;
					Main->saved_data->atk+=2;
				}
				else if(stats==4){//back
					smenu=0;
					stats=1;
					settings=1;
				}
			}
			if(stats==1){//coin in stats menu
				rect1.y=18.5*((Main->SpriteList+0)->FrameHeight)/36;
				rect1.x=13*Main->SCREEN_WIDTH/36;
			}
			else if(stats==2){
				rect1.y=20.3*((Main->SpriteList+0)->FrameHeight)/36;
				rect1.x=13*Main->SCREEN_WIDTH/36;
			}
			else if(stats==3){
				rect1.y=22*((Main->SpriteList+0)->FrameHeight)/36;
				rect1.x=13*Main->SCREEN_WIDTH/36;
			}
			else if(stats==4){
				rect1.y=(15*Main->SCREEN_HEIGHT)/18;
				rect1.x=Main->SCREEN_WIDTH/3-100;
			}

		}
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect5);//back button
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+6)->Texture,NULL,&rect6);//paper
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+11)->Texture,NULL,&rect11);//hp text
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+12)->Texture,NULL,&rect12);//def text
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+13)->Texture,NULL,&rect13);//atk text
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);//dynamic coin

		((CurrentInstance))->data[3]=stats;
		if(Main->FrameKey[6]&1){
			smenu=0;
			settings=1;
		}
	}//Stats menu

	if(smenu==0){//main store menu
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+3)->Texture,NULL,&rect3);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+4)->Texture,NULL,&rect4);
		SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect5);
	}
	//save changes on used variables
	((CurrentInstance)->data)[0]=settings;
	((CurrentInstance)->data)[1]=timer;
	((CurrentInstance))->data[2]=items;
	((CurrentInstance))->data[3]=stats;
	return;
}//bazar

void Room002(GlobalVariables* Main){
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;
	
	wprintf(L"\n\n%c%c%c 		Room 002 		%c%c%c 	\n",4,4,4,4,4,4);

	//load media
	Objectload_002(Main);

	//Create Main Instances
	InstanceCreationCode_002(Main);
	Main->menu=31;
} //Bazar