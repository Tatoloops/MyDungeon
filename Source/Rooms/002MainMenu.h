/*
Room 001: Main Menu
Features:
New Character
Save Character
Load Characters
*/

/*			Definitions			*/
	//Room Data
#define R002MaxBackground	4
#define R002MaxInsText		500
#define R002PhraseCountMax	50


typedef struct{
	Sprite 			Background[R002MaxBackground];
	SDL_Rect		BackRect[R002MaxBackground-2];
	unsigned char 	BackHorizontalRep[R002MaxBackground-2];
	unsigned char 	BackVerticalRep[R002MaxBackground-2];
	char			BackXSpeed[R002MaxBackground-2];
	char			BackYSpeed[R002MaxBackground-2];

	Language		Language01;
	Language		Language02;
	InsText			InsText[R002MaxInsText];

	int Menu;
	unsigned short	PhraseLength[R002PhraseCountMax];
	unsigned short	PhraseBegin[R002PhraseCountMax];
	short			PhraseTilt[R002MaxInsText];
	SDL_Color		Blender[3];
	char			BlendModifier[3];
	// the number indicates the amount of buttons in main menu +1

	int InsTextCount;	//Placed Characters

}Room002;



void RoomLoad_002(GlobalVariables* Main,Room002* Room){
	wprintf(L"\n%c%c	RoomID:002 Main Menu",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/
	wprintf(L"\n%c	Loading Background Images...",0x10);
	/*			Loading Background Textures			*/
	CreateNonAnimatedBackground(Main,Main->MainRender,Room->Background+0,"media/backgrounds/Back001.bmp",&error);
	if (!error&0x3)
		wprintf(L" 1");
	error=~(~error|0x1);
	CreateNonAnimatedSprite(Main->MainRender,Room->Background+1,"media/backgrounds/DoorPerimetter2.bmp",&error);
	if (!error&0x3)
		wprintf(L" 2	Done");
	error=~(~error|0x1);
	CreateNonAnimatedBackground(Main,Main->MainRender,Room->Background+2,"media/backgrounds/Alpha01.bmp",&error);
	if (!error&0x3)
		wprintf(L" 3");
	


	/*			Loading Letter Textures			*/
	wprintf(L"\n%c	Loading Language...",0x10);
	error=~(~error|0x3);
	SDL_Color Color1={.r=255,.g=255,.b=255,.a=255};
	CreateLanguageEnglish94TextureLoad(Main,&Color1,&Room->Language01,"fonts/FrederickatheGreat-Regular.ttf",40,0,0,&error);
	CreateLanguageEnglish94TextureLoad(Main,&Color1,&Room->Language02,"fonts/AlmendraDisplay-Regular.ttf",40,0,0,&error);
	if (!error&0x3)
		wprintf(L"		Done");


	//Song 000
	*(Main->SongList+0)=Mix_LoadMUS("media/music/100.mp3");
	if(*(Main->SongList+0)==NULL) wprintf(L"\n%c	Could not load song: %S",0x488,SDL_GetError());

	if (error)
		wprintf(L"\n%c%c 	Failed to load Room without problems \n",0x488,0x488);
	else
		wprintf(L"\n%c%c 	Room Correctly loaded into memory! \n",0xf,0x10);
	return;
}//Main Menu
void RoomCreationCode_002(GlobalVariables* Main,Room002* Room){ // main menu 1
	/*			Background			*/
	for(unsigned char i=0;i<R002MaxBackground-2;++i){
		int ratio=2*i;
		Room->BackXSpeed[i]=-R002MaxBackground+i+2;
		//Room->BackYSpeed[i]=-3/(ratio+1);
		//Room->BackXSpeed[i]=R002MaxBackground-i;
		Room->BackYSpeed[i]=-R002MaxBackground+i+2;
		(Room->BackRect+i)->w=round(((Room->Background+1)->Width)/(ratio+1));
		(Room->BackRect+i)->h=round(((Room->Background+1)->Height/(ratio+1)));
		//	X
		int Rep=Main->SCREEN_WIDTH/(Room->BackRect+i)->w;
		int Horizontalrepres=Main->SCREEN_WIDTH%(Room->BackRect+i)->w;
		if (Horizontalrepres>0)
			Rep++;
		if (Rep%2==0){
			(Room->BackRect+i)->x=Main->SCREEN_WIDTH/2-((Rep/2)*(Room->BackRect+i)->w);
		}
		else{
			(Room->BackRect+i)->x=Main->SCREEN_WIDTH/2-(Room->BackRect+i)->w/2-(((Rep-1)/2)*(Room->BackRect+i)->w);
		}
		//	Y
		Rep=Main->SCREEN_HEIGHT/(Room->BackRect+i)->h;
		int Verticalrepres=Main->SCREEN_HEIGHT%(Room->BackRect+i)->h;
		if (Verticalrepres>0)
			Rep++;
		if (Rep%2==0){
			(Room->BackRect+i)->y=Main->SCREEN_HEIGHT/2-((Rep/2)*(Room->BackRect+i)->h);
		}
		else{
			(Room->BackRect+i)->y=Main->SCREEN_HEIGHT/2-((Room->BackRect+i)->h)/2-((Rep/2)*(Room->BackRect+i)->h);
		}
		//wprintf(L"\nback%d:	x:%d	y:%d	w:%d	h:%d",i,(Room->BackRect+i)->x,(Room->BackRect+i)->y,(Room->BackRect+i)->w,(Room->BackRect+i)->h);
		//wprintf(L"\nrepx:%d	repY:%d",Room->BackHorizontalRep[i],Room->BackVerticalRep[i]);
	}


	/*	Main Menu	*/
	Room->Menu=1;
	Room->InsTextCount=0;
	int YSep=Main->SCREEN_HEIGHT/12;
	int instances;

	Room->PhraseBegin[0]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"`~!@#$%^&*()_-=+[]'><:;|(*@#*&@%?\"\\{}.,/{\0",
		&Room->Language01,Main->SCREEN_WIDTH/2,YSep*6,0x01fc0000);
	Room->PhraseLength[0]=instances;
	Room->InsTextCount+=instances;

	Room->PhraseBegin[1]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(&(Room->InsText[Room->InsTextCount]),"Support The Game\0",
		&Room->Language01,Main->SCREEN_WIDTH/2,YSep*7,0x01fc0000);
	Room->PhraseLength[1]=instances;
	Room->InsTextCount+=instances;

	Room->PhraseBegin[2]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"Ranking\0",
		&Room->Language01,Main->SCREEN_WIDTH/2-Main->SCREEN_WIDTH/8,YSep*8,0x01fc0000);
	Room->PhraseLength[2]=instances;
	Room->InsTextCount+=instances;

	Room->PhraseBegin[3]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"Badges\0",
		&Room->Language01,Main->SCREEN_WIDTH/2+Main->SCREEN_WIDTH/8,YSep*8,0x01fc0000);
	Room->PhraseLength[3]=instances;
	Room->InsTextCount+=instances;
	Room->PhraseBegin[4]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"Changes\0",
		&Room->Language01,Main->SCREEN_WIDTH/2-Main->SCREEN_WIDTH/8,YSep*9,0x01fc0000);
	Room->PhraseLength[4]=instances;
	Room->InsTextCount+=instances;
	Room->PhraseBegin[5]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"About\0",
		&Room->Language01,Main->SCREEN_WIDTH/2+Main->SCREEN_WIDTH/8,YSep*9,0x01fc0000);
	Room->PhraseLength[5]=instances;
	Room->InsTextCount+=instances;
	Room->PhraseBegin[6]=Room->InsTextCount;
	instances=RoomPlacePhraseRects(Room->InsText+(Room->InsTextCount),"Quit\0",
		&Room->Language01,Main->SCREEN_WIDTH/2,YSep*10,0x01fc0000);
	Room->PhraseLength[6]=instances;
	Room->InsTextCount+=instances;

	for(unsigned short i=0;i<Room->InsTextCount;++i){
		Room->PhraseTilt[i]=0;
	}
	//Blending
	Room->BlendModifier[0]=1;
	Room->BlendModifier[1]=1;
	Room->Blender[0].r=150;
	Room->Blender[0].g=180;
	Room->Blender[0].b=0;
	Room->Blender[0].a=255;
	//Number of Files Saved, Extract from Savedata.
	//Main->Savedata = fopen (Main->SavedataName, "r+");

	Mix_PlayMusic(*(Main->SongList+0),1);
}

void RoomStepCode_002(GlobalVariables* Main,Room002* Room){
	/*			Background			*/
	SDL_RenderCopy(Main->MainRender,(Room->Background+0)->Texture,NULL,NULL);
	for(short i=R002MaxBackground-3;i>=0;--i){
		//	X adjust
		if(Room->BackRect[i].x < -1* Room->BackRect[i].w)
			Room->BackRect[i].x+=Room->BackRect[i].w;
		else if(Room->BackRect[i].x >0)
			Room->BackRect[i].x-=Room->BackRect[i].w;
		//	Y adjust
		if(Room->BackRect[i].y < -1* Room->BackRect[i].h)
			Room->BackRect[i].y+=Room->BackRect[i].h;
		else if(Room->BackRect[i].y >0)
			Room->BackRect[i].y-=Room->BackRect[i].h;

		int holderX=Room->BackRect[i].x;
		int holderY=Room->BackRect[i].y;

		while(Room->BackRect[i].x<Main->SCREEN_WIDTH){
			while(Room->BackRect[i].y<Main->SCREEN_HEIGHT){
				SDL_RenderCopy(Main->MainRender,(Room->Background+1)->Texture,NULL,(Room->BackRect+i));
				Room->BackRect[i].y+=(Room->BackRect[i].h);
			}
			Room->BackRect[i].x+=(Room->BackRect[i].w);
			Room->BackRect[i].y=holderY;
		}
		Room->BackRect[i].x=holderX;

		Room->BackRect[i].x+=Room->BackXSpeed[i];
		Room->BackRect[i].y+=Room->BackYSpeed[i];
		
	}
	SDL_RenderCopy(Main->MainRender,(Room->Background+2)->Texture,NULL,NULL);





	/*			End Of Background			*/


	//take variables
	int RMenu=Room->Menu;
	/*	Menu:
	[0-100]:Main Screen
		1-Enter Dungeon
		2-Support Game
		3-Ranking
		4-Badges
		5-Changes/news
		6-About
		7-Quit
	[1001-2000]:Enter The Dungeon
	[2001-3000]:Support Game
	[3001-4000]:Ranking
	[4001-5000]:Badges
	[5001-6000]:Changes
	[6001-7000]:About
	[7001-8000]:Quit
	Maybe more buttons in the future...
	*/

	/*	Abort Screen	*/
	if (RMenu==0){
		
	}
	/*	Main Screen		*/
	else if (RMenu<100){
		
		if(Main->FrameKey[0]&0x1){ //up
			if(RMenu==4||RMenu==6||RMenu==7||RMenu==5)
				RMenu--;
			--RMenu;
			if (RMenu<1)
				RMenu=1;
		}
		else if(Main->FrameKey[1]&0x1){ //down
			if(RMenu==4||RMenu==3||RMenu==5)
				RMenu++;
			++RMenu;
			if (RMenu>7)
				RMenu=7;
		}
		else if(Main->FrameKey[2]&0x1){//Left
			if(RMenu==4 || RMenu==6)
				RMenu--;
		}
		else if(Main->FrameKey[3]&0x1){//Right
			if(RMenu==3 || RMenu==5)
				RMenu++;
		}
		else if(Main->FrameKey[5]&0x1){ //enter
			RMenu=RMenu*1000+1;
		}
		else if(Main->FrameKey[6]&0x1){	//Back
			if (RMenu==7) 	RMenu==7001;
			else				RMenu=7;

		}		
	}

	/*	Enter The Dungeon	*/
	else if(RMenu>1000 && RMenu<=2000){
		
		
	}

	/*	Support The Game	*/
	else if(RMenu>2000 && RMenu<=3000){
		
	}

	/*	Ranking	*/
	else if(RMenu>3000 && RMenu<=4000){
		
	}

	/*	Badges	*/
	else if(RMenu>4000 && RMenu<=5000){
		
	}

	/*	News/Changes/Updates	*/
	else if(RMenu>5000 && RMenu<=6000){
		
	}

	/*	About	*/
	else if(RMenu>6000 && RMenu<=7000){
		
	}

	/*	Quit	*/
	else if(RMenu>7000 && RMenu<=8000){
		
	}

	/*			Draw Event			*/
	/*	
	All the drawing is done in this section of the code
	The first part is only the mechanism.
	*/

	if (RMenu>0 && RMenu<100){
		for(unsigned short i=0;i<7;++i){
			if (RMenu==i+1){
				//	Changing	Blender
				Room->Blender[0].r+=Room->BlendModifier[0];
				if 		(Room->Blender[0].r>200){
					Room->BlendModifier[0]=-1;
					Room->Blender[0].g+=Room->BlendModifier[1];
					if 		(Room->Blender[0].g==255){
						Room->BlendModifier[1]=-1;
						
					}
					else if (Room->Blender[0].g==0)
						Room->BlendModifier[1]=1;
				}
				else if (Room->Blender[0].r<160)
					Room->BlendModifier[0]=1;
				//	Blending and Printing
				SDL_SetTextureColorMod((Room->InsText+0)->PtrToLang->Texture,Room->Blender[0].r,Room->Blender[0].g,Room->Blender[0].b);
				for(unsigned short j=Room->PhraseBegin[i];j<Room->PhraseBegin[i]+Room->PhraseLength[i];++j)
					SDL_RenderCopy(Main->MainRender,(Room->InsText+j)->PtrToLang->Texture,&(Room->InsText+j)->SrcR,&(Room->InsText+j)->DestR);
				SDL_SetTextureColorMod((Room->InsText+0)->PtrToLang->Texture,255,255,255);
			}
			else{
				for(unsigned short j=Room->PhraseBegin[i];j<Room->PhraseBegin[i]+Room->PhraseLength[i];++j)
					SDL_RenderCopy(Main->MainRender,(Room->InsText+j)->PtrToLang->Texture,&(Room->InsText+j)->SrcR,&(Room->InsText+j)->DestR);
			}
		}
	}
	/*	Enter The Dungeon	*/
	else if(RMenu>1000 && RMenu<=2000){
		
		
	}

	/*	Support The Game	*/
	else if(RMenu>2000 && RMenu<=3000){
		
	}

	/*	Ranking	*/
	else if(RMenu>3000 && RMenu<=4000){
		
	}

	/*	Badges	*/
	else if(RMenu>4000 && RMenu<=5000){
		
	}

	/*	News/Changes/Updates	*/
	else if(RMenu>5000 && RMenu<=6000){
		
	}

	/*	About	*/
	else if(RMenu>6000 && RMenu<=7000){
		
	}

	/*	Quit	*/
	else if(RMenu>7000 && RMenu<=8000){
		
	}



	Room->Menu=RMenu;
	return;
}//selección de personaje
void RoomFree_002(Room002* Room){

}
void RoomMain_002(GlobalVariables* Main){
	wprintf(L"\n\n%c%c%c 		Room 002 		%c%c%c 	\n",4,4,4,4,4,4);
	Room002 Room;
	//load media
	RoomLoad_002(Main,&Room);
	//Create Main Instances
	RoomCreationCode_002(Main,&Room);
	
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
			//Uint32 MyFormat=SDL_GetWindowPixelFormat(Main->MainWindow);
			//wprintf(L"\n %d",MyFormat);
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
				RoomStepCode_002(Main,&Room);
				//wprintf(L"\nim here again wowod a ");
				Refresh(Main);
				//wprintf(L"\nim here again wowod b ");
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
	RoomFree_002(&Room);
	FreeMedia(Main);
	//SDL_SetRenderDrawBlendMode(Main->MainRender,SDL_BLENDMODE_ADD);
	for(short alpha=0;alpha<255;++alpha){
	SDL_SetRenderDrawColor(Main->MainRender, 0,0,0, alpha);
	SDL_RenderClear(Main->MainRender);
	SDL_RenderPresent(Main->MainRender);
	SDL_Delay(4);
	}
	
}