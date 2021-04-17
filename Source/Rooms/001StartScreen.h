/*
Room 000: Start Screen

*/
/*			Definitions			*/
#define R001MaxBackground 		1
#define R001MaxLogos			5
#define R001MaxInstances		5
/*			Structures			*/

typedef struct{
	SDL_Rect DestR;		//position in window rectangle
	Sprite* Spr;
}Room001Instance;

typedef struct{
	Uint32 TimeBegin;
	Uint32 TimeCurrent;
	Uint32 TimePerLogo;	//miliseconds

	int Section;
	unsigned char NumberOfLogos;
	Uint32	TimeAlphaChange;
	Uint8	LogoAlpha;
	double	TimeAlphaFix;

	Sprite 			Background[R001MaxBackground];
	Sprite 			Logos[R001MaxLogos];
	Room001Instance RIns[R001MaxInstances];
}Room001;
void RoomLoad_001(GlobalVariables* Main,Room001* Room){
	wprintf(L"\n%c%c	RoomID:001 Presentation Screen",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/

	/*			Loading Backgrounds			*/
	wprintf(L"\n%c	Loading Background Image...",0x10);
	//Background 000.
	CreateNonAnimatedBackground(Main,Main->MainRender,Room->Background+0,"media/backgrounds/Back001.bmp",&error);
	if (!error & 0x3)
		wprintf(L"	Done");	


	/*			Loading Sprites			*/
	wprintf(L"\n%c 	Loading Textures...",0x10);
	error=~(~error|0x3);
	//Logo 000.
	CreateNonAnimatedSprite(Main->MainRender,Room->Logos+0,"media/Logos/TatoloopsLogo.bmp",&error);
	if (!error&0x3)
		wprintf(L" 1");
	//Logo 001.
	error=~(~error|0x1);
	CreateNonAnimatedSprite(Main->MainRender,Room->Logos+1,"media/Logos/ScottBuckley.bmp",&error);
	if (!error&0x3)
		wprintf(L" 2		Done");

	if (error)
		wprintf(L"\n%c%c 	Failed to load Room without problems \n",0x488,0x488);
	else
		wprintf(L"\n%c%c 	Room Correctly loaded into memory! \n",0xf,0x10);
	return;
}//Presentation screen
void RoomCreationCode_001(GlobalVariables* Main,Room001* Room){ // main menu 1
	Room->Section=0;
	Room->TimePerLogo=5000;	//Miliseconds
	Room->TimeAlphaChange=1000;

	double ope= Room->TimeAlphaChange;
	Room->TimeAlphaFix=255/(ope*ope);

	Room->LogoAlpha=0;
	Room->NumberOfLogos=2;
	Room->TimeBegin=SDL_GetTicks();

	for (unsigned char i =0; i<R001MaxLogos;i++){
		(Room->RIns+i)->Spr=(Room->Logos+i);
		(Room->RIns+i)->DestR.x=(Main->SCREEN_WIDTH/2)-((Room->Logos+i)->Width/2);
		(Room->RIns+i)->DestR.y=(Main->SCREEN_HEIGHT/2)-((Room->Logos+i)->Height/2);
		(Room->RIns+i)->DestR.w=(Room->Logos+i)->Width;
		(Room->RIns+i)->DestR.h=(Room->Logos+i)->Height;
	}
}
void RoomStepCode_001(GlobalVariables* Main,Room001* Room){
	/*			Copy Background			*/
	SDL_RenderCopy(Main->MainRender,(Room->Background+0)->Texture,NULL,NULL);

	Room->TimeCurrent=SDL_GetTicks();

	if(Room->TimeCurrent	>=	Room->TimePerLogo+Room->TimeBegin){
		Room->Section++;
		Room->TimeBegin=Room->TimeCurrent;
	}

	double CurrentX=Room->TimeCurrent-Room->TimeBegin;
	double p0=0;
	double p1=Room->TimeAlphaChange;
	double p2=Room->TimePerLogo-Room->TimeAlphaChange;
	double p3=Room->TimePerLogo;

	//Check alpha
	if (CurrentX	<  p1){
		Room->LogoAlpha=round(CurrentX*CurrentX*(Room->TimeAlphaFix));
		SDL_SetTextureAlphaMod((Room->RIns+Room->Section)->Spr->Texture,Room->LogoAlpha);
		
	}
	else if(CurrentX	<  p2){
		SDL_GetTextureAlphaMod((Room->RIns+Room->Section)->Spr->Texture,&Room->LogoAlpha);
		if (Room->LogoAlpha != 255){
			Room->LogoAlpha=255;
			SDL_SetTextureAlphaMod((Room->RIns+Room->Section)->Spr->Texture,Room->LogoAlpha);
		}
	}
	else if (CurrentX	<  p3){
		Room->LogoAlpha=round((CurrentX-p3)*(CurrentX-p3)*(Room->TimeAlphaFix));
		SDL_SetTextureAlphaMod(((Room->RIns+(Room->Section))->Spr)->Texture,Room->LogoAlpha);
	}

	/*			Logos & Section			*/
	if (Room->Section	<	Room->NumberOfLogos){
		SDL_RenderCopy(Main->MainRender,(Room->RIns+Room->Section)->Spr->Texture,NULL,&(Room->RIns+(Room->Section))->DestR);//
	}
	else{
		Main->RoomCurrentID=2;
		Main->RoomState|=0x1;
		Main->RoomState=~(~Main->RoomState|0x2);
	}
		return;
}//menu principal
void RoomFree_001(Room001* Room){
	for(unsigned short i=0;i<R001MaxBackground;++i){
		if((Room->Background+i)->Texture!=NULL){
			SDL_DestroyTexture((Room->Background+i)->Texture);
			(Room->Background+i)->Texture=NULL;
		}
	}
	for(unsigned short i=0;i<R001MaxLogos;++i){
		if((Room->Logos+i)->Texture!=NULL){
			SDL_DestroyTexture((Room->Logos+i)->Texture);
			(Room->Logos+i)->Texture=NULL;
		}
	}
}
void RoomMain_001(GlobalVariables* Main){
	wprintf(L"\n\n%c%c%c 		Room 001 		%c%c%c 	\n",4,4,4,4,4,4);
	Room001 Room;
	//load media
	RoomLoad_001(Main,&Room);
	//Create Main Instances
	RoomCreationCode_001(Main,&Room);
	
	/*	Room States:
		booleans to determine the state of the current Room:
		RoomState=0000 0001:	Loop Ended, and now changing Rooms
		RoomState=0000 0010:	Room is in continuous Loop
		RoomState=0000 0100:	Room in Pause
	*/
	/*			Room 000 Loop			*/
	Main->RoomState=~(~Main->RoomState|0x1);
	Main->RoomState|=0x2;
	while(Main->RoomState & 0x2)
		while(SDL_PollEvent(&Main->MainEvent)!=1 && Main->RoomState & 0x2){
			/*    FPS CONTROL       */
			keypressed(Main->PreviousKey);
			Main->CurrentTime=SDL_GetTicks();
			if (Main->CurrentTime>Main->PrevTime+Main->TicksPerFrame){ // 33-> 30 fps   17->60 fps
				//StringCopy(key,framekey,KeyNumber);
				keycompare(Main->FrameKey,Main->PreviousKey);
				//PrevFrame=Frame;
				//++Frame;
				Main->PrevTime=Main->CurrentTime;
				SDL_RenderClear(Main->MainRender);
				RoomStepCode_001(Main,&Room);
				Refresh(Main);
			}
			else
				SDL_Delay(Main->PrevTime+Main->TicksPerFrame-Main->CurrentTime);
			/* 		END	FPS			*/
				/* 	END 	GAME 	ROOMS*/
			if(Main->MainEvent.type==SDL_QUIT){
				Main->RoomCurrentID=0;
				Main->RoomState|0x1;
				Main->RoomState=~(~Main->RoomState|0x2);
			}
			if(Main->FrameKey[13]&0x1)
				if(Mix_PlayingMusic()){
					if(Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
				}
			if(Main->FrameKey[12] & 0x1){
				Main->RoomCurrentID=0;
				Main->RoomState|0x1;
				Main->RoomState=~(~Main->RoomState|0x2);
			}
		}
	RoomFree_001(&Room);
	FreeMedia(Main);
}
