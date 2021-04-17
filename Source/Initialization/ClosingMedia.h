void InstanceDestroy(GlobalVariables* Main,Instance* InstanceToDestroy){
	InstanceToDestroy->ID=-1;
	short i=0;
	short j=0;
	int thisID;
	while (1) {
		thisID=(Main->InstanceList+i)->ID;
		if(thisID<0){
			--(Main->ins_count);
			(Main->InstanceList+i)->ID 		=	(Main->InstanceList+Main->ins_count)->	ID;
			(Main->InstanceList+i)->x 		=	(Main->InstanceList+Main->ins_count)->	x;
			(Main->InstanceList+i)->y 		=	(Main->InstanceList+Main->ins_count)->	y;
			(Main->InstanceList+i)->sprite 	=	(Main->InstanceList+Main->ins_count)->	sprite;
			copyrectangle(&(Main->InstanceList+Main->ins_count)->rectangle1,&(Main->InstanceList+i)->rectangle1);
			copyrectangle(&(Main->InstanceList+Main->ins_count)->rectangle2,&(Main->InstanceList+i)->rectangle2);
			for(j=0;j<20;++j){
				(Main->InstanceList+i)->data[j]		=(Main->InstanceList+Main->ins_count)->data[j];
				(Main->InstanceList+i)->floatdata[j]=(Main->InstanceList+Main->ins_count)->floatdata[j];
				(Main->InstanceList+i)->dataname[j]	=(Main->InstanceList+Main->ins_count)->dataname[j];
			}
			(Main->InstanceList+Main->ins_count)->ID=-1;
			return;
		}
		++i;
	}
}

/*		CIERRE DE MULTIMEDIA		*/
void FreeMedia(GlobalVariables* Main){
	wprintf(L"\n%c	Deleting Media Files...",0x11);
	for(unsigned short i=0;i<MaxSprites;++i){
		if((Main->SpriteList+i)->Texture!=NULL){
			SDL_DestroyTexture((Main->SpriteList+i)->Texture);
			(Main->SpriteList+i)->Texture=NULL;
		}
	}
	for(unsigned short i=0;i<MaxSongs;++i){
		if(*(Main->SongList+i)!=NULL){
			Mix_FreeMusic(*(Main->SongList+i));
			*(Main->SongList+i)=NULL;
		}
	}
	for(unsigned short i=0;i<MaxSounds;++i){
		if(*(Main->SoundList+i)!=NULL){
			Mix_FreeChunk(*(Main->SoundList+i));
			*(Main->SoundList+i)=NULL;
		}
	}
	wprintf(L"Done!");
}
void Closing(GlobalVariables* Main){ //closing game
    //Deallocate main surface
	//closing_surface(mainsurface);
    //Destroy main window
    SDL_DestroyRenderer(Main->MainRender);
    SDL_DestroyWindow(Main->MainWindow);
    //Quit SDL subsystems
    wprintf(L"\n%c%c	Goodbye User...",0x11,0x11);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_VideoQuit();
    SDL_AudioQuit();
    SDL_Quit();
}