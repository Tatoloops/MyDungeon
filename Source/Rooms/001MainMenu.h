/*
Room 001: Main Menu
Features:
New Character
Save Character
Load Characters

*/

void Objectload_001(GlobalVariables* Main){
	wprintf(L"\n%c%c	ID:001 Main Menu",0xf,0x10);
	char error=0;
	/*
	error bitmap:
	0000 0001:	There is an error in the Current Item.
	0000 0010:	There is an error in the Current Section.
	0000 0100:	There is an error in the Whole Room.
	*/
	//sprite000
	(Main->SpriteList+0)->Texture=LoadTexture(Main->MainRender,"media/backgrounds/100.bmp",&error);

	SDL_QueryTexture((Main->SpriteList+0)->Texture,NULL,NULL,&((Main->SpriteList+0)->Width),&((Main->SpriteList+0)->Height));

	(Main->SpriteList+0)->FrameWidth=Main->SCREEN_WIDTH;
	(Main->SpriteList+0)->FrameHeight=Main->SCREEN_HEIGHT;
	(Main->SpriteList+0)->FrameNumber=1;
	(Main->SpriteList+0)->speed=0;

	//font colors & size
	SDL_Color color0={.r=150,.g=20,.b=20,.a=210};
	SDL_Color color1={.r=255,.g=255,.b=255,.a=255};
	SDL_Color color2={.r=150,.g=100,.b=100,.a=180};
	int psize=60;

	//color1
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+1,"Race :","fonts/Pangolin-Regular.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+2,"Human","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+3,"Rabbitman","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+4,"Frogman","fonts/Halt.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+5,"Class :","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+6,"Warrior","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+7,"Archer","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+8,"Mage","fonts/Halt.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+9,"Start","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+10,"Back","fonts/Pangolin-Regular.ttf",psize,&error);

	//color2
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+11,"Race :","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+12,"Human","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+13,"Rabbitman","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+14,"Frogman","fonts/Halt.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+15,"Class :","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+16,"Warrior","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+17,"Archer","fonts/Halt.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+18,"Mage","fonts/Halt.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+19,"Start","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+20,"Back","fonts/Pangolin-Regular.ttf",psize,&error);
	//stats menu
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+21,"Stats","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+22,"HP","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+23,"ATK","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+24,"DEF","fonts/Pangolin-Regular.ttf",psize,&error);
	//numbers
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+25,"0","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+26,"1","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+27,"2","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+28,"3","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+29,"4","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+30,"5","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+31,"6","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+32,"7","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+33,"8","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+34,"9","fonts/Pangolin-Regular.ttf",psize,&error);

	//menu principal
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+35,"New Character","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+36,"Save Character","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+37,"Load Character","fonts/Pangolin-Regular.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+38,"New Character","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+39,"Save Character","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+40,"Load Character","fonts/Pangolin-Regular.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+41,"Save Character","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+42,"Load Character","fonts/Pangolin-Regular.ttf",psize,&error);

	//sub menu de slots (save or load)
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+43,"Slot 1","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+44,"Slot 2","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+45,"Slot 3","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+46,"Slot 4","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+47,"Slot 5","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color0,Main->SpriteList+48,"Slot 6","fonts/Pangolin-Regular.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+49,"Slot 1","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+50,"Slot 2","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+51,"Slot 3","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+52,"Slot 4","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+53,"Slot 5","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color1,Main->SpriteList+54,"Slot 6","fonts/Pangolin-Regular.ttf",psize,&error);

	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+55,"Slot 1","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+56,"Slot 2","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+57,"Slot 3","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+58,"Slot 4","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+59,"Slot 5","fonts/Pangolin-Regular.ttf",psize,&error);
	CreateNonAnimatedFont(Main->MainRender,&color2,Main->SpriteList+60,"Slot 6","fonts/Pangolin-Regular.ttf",psize,&error);
	//Song 000
	*(Main->SongList+0)=Mix_LoadMUS("media/music/100.mp3");
	if(*(Main->SongList+0)==NULL) wprintf(L"could not load song: %s",SDL_GetError());
}//Main Menu
void InstanceCreationCode_001(GlobalVariables* Main){ // main menu 1
	
	(Main->InstanceList+(Main->ins_count))->ID =001;
	(Main->InstanceList+(Main->ins_count))->x=0;
	(Main->InstanceList+(Main->ins_count))->y=0;
	(Main->InstanceList+(Main->ins_count))->sprite=NULL;
	(Main->InstanceList+(Main->ins_count))->data[0]=1; // submenu 1 button on race. 2 button on class. 3 start. 4 quit.
	(Main->InstanceList+(Main->ins_count))->data[1]=1; // race: 1=human. 2=Frogman. 3=Rabbitman.
	(Main->InstanceList+(Main->ins_count))->data[2]=1;	//class: 1=class1 2=class2 3=class3.
	(Main->InstanceList+(Main->ins_count))->data[3]=255;	//timer
	(Main->InstanceList+(Main->ins_count))->data[4]=1; //menu principal


	Mix_PlayMusic(*(Main->SongList+0),-1);
	++(Main->ins_count);
}
void InstanceStepCode_001(GlobalVariables* Main,Instance* CurrentInstance){
	//menu de elección de personaje
	SDL_RenderCopy(Main->MainRender,(Main->SpriteList+0)->Texture,NULL,NULL);
	//take variables
	int subsettings=((CurrentInstance)->data)[0];
	int race=((CurrentInstance)->data)[1];
	int CharacterClass=((CurrentInstance)->data)[2];
	int timer=((CurrentInstance)->data)[3];
	int settings=((CurrentInstance)->data)[4];
	
	if (settings==1){  //subsetting: 1:new 2:save 3:load
		if(Main->FrameKey[0]&1){ //up
			--subsettings;
			if (subsettings<1)
				subsettings=1;
		}
		else if(Main->FrameKey[1]&1){ //down
			++subsettings;
			if (subsettings>3)
				subsettings=3;
		}
		else if(Main->FrameKey[5]&1){ //enter
			if(subsettings==1){ //enter new character creation
				settings=2;
			}
			else if(subsettings==2){ //character save
				subsettings=1;
				settings=3;
			}
			else if(subsettings==3){ //character load
				subsettings=1;
				settings=4;
			}
		}

	}
	else if(settings==2){ //sub menu de creacion de raza.
		if (subsettings==1){ //race
			if 		(Main->FrameKey[2]&1){
				--race;
				if (race<1)
					race=3;
			}
			else if (Main->FrameKey[3]&1){
				++race;
				if (race>3)
					race=1;
			}
			else if (Main->FrameKey[1]&1){
				subsettings=2;
			}
			else if (Main->FrameKey[6]&1){
				subsettings=4;
			}
		}
		else if(subsettings==2){ //CharacterClass
			if 		(Main->FrameKey[2]&1){
				--CharacterClass;
				if (CharacterClass<1)
					CharacterClass=3;
			}
			else if (Main->FrameKey[3]&1){
				++CharacterClass;
				if (CharacterClass>3)
					CharacterClass=1;
			}
			else if (Main->FrameKey[1]&1){
				subsettings=3;
			}
			else if(Main->FrameKey[0]&1){
				subsettings=1;
			}
			else if (Main->FrameKey[6]&1){
				subsettings=4;
			}
		}
		else if(subsettings==3){ //start
			if 	(Main->FrameKey[2]&1){
				subsettings=4;
			}
			else if(Main->FrameKey[0]&1){
				subsettings=2;
			}
			else if (Main->FrameKey[5]&1){
				subsettings=5;
			}
			else if (Main->FrameKey[6]&1){
				subsettings=4;
			}
		}
		else if (subsettings==4){ //back
			if 	(Main->FrameKey[3]&1){
				subsettings=3;
			}
			else if(Main->FrameKey[0]&1){
				subsettings=2;
			}
			else if (Main->FrameKey[5]&1){
				subsettings=1;
				settings=1;
			}
			else if (Main->FrameKey[6]&1){
				subsettings=1;
				settings=1;
			}
		}
		else if(subsettings==5){ //starting
			timer-=10;
			if(timer<=0){
				Main->menu=30;
				CreateCharacter(Main->saved_data,CharacterClass,race);
			}
		}
	}
	else if (settings==3){ //sub menu de save de slot
		if (Main->FrameKey[0]&1){ //move up
			subsettings-=3;
			if (subsettings<1)
				subsettings+=3;
		}
		else if (Main->FrameKey[1]&1){ //move down
			subsettings+=3;
			if (subsettings>6)
				subsettings-=3;
		}
		else if (Main->FrameKey[2]&1){ //left
			--subsettings;
			if (subsettings==0 || subsettings==3)
				++subsettings;
		}
		else if (Main->FrameKey[3]&1){ //right
			++subsettings;
			if (subsettings==4 || subsettings==7)
				--subsettings;
		}
		else if (Main->FrameKey[5]&1){ //select
			if (Main->saved_data->CharacterClass!=0){
				SaveSlot(Main->saved_data,subsettings);
				subsettings=2;
				settings=1;
			}
		}
		else if (Main->FrameKey[6]&1){ //select
			subsettings=2;
			settings=1;
		}
	}
	else{ //load slot
		if (Main->FrameKey[0]&1){ //move up
			subsettings-=3;
			if (subsettings<1)
				subsettings+=3;
		}
		else if (Main->FrameKey[1]&1){ //move down
			subsettings+=3;
			if (subsettings>6)
				subsettings-=3;
		}
		else if (Main->FrameKey[2]&1){ //left
			--subsettings;
			if (subsettings==0 || subsettings==3)
				++subsettings;
		}
		else if (Main->FrameKey[3]&1){ //right
			++subsettings;
			if (subsettings==4 || subsettings==7)
				--subsettings;
		}
		else if (Main->FrameKey[5]&1){ //select
			if ((Main->saved_data+subsettings)->CharacterClass!=0){
				LoadSlot(Main->saved_data,subsettings);
				Main->menu=30;
			}
		}
		else if (Main->FrameKey[6]&1){ //back
			subsettings=3;
			settings=1;
		}
	}

	if (settings==1){ //main menu
		SDL_Rect rect1={.x=(Main->SCREEN_WIDTH)/2,.y=(16*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+35)->Width,.h=(Main->SpriteList+35)->Height};
		SDL_Rect rect2={.x=(Main->SCREEN_WIDTH)/2,.y=(18*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+36)->Width,.h=(Main->SpriteList+36)->Height};
		SDL_Rect rect3={.x=(Main->SCREEN_WIDTH)/2,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+37)->Width,.h=(Main->SpriteList+37)->Height};
		if (subsettings==1){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+38)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+36)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+37)->Texture,NULL,&rect3);
		}
		if (subsettings==2){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+35)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+39)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+37)->Texture,NULL,&rect3);
		}
		if (subsettings==3){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+35)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+36)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+40)->Texture,NULL,&rect3);
		}
	}
	else if (settings==2){
		SDL_Rect rect1={.x=(3*Main->SCREEN_WIDTH)/8,.y=(15*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+1)->Width,.h=(Main->SpriteList+1)->Height};
		SDL_Rect rect2={.x=(4*Main->SCREEN_WIDTH)/8,.y=(15*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+2)->Width,.h=(Main->SpriteList+2)->Height};
		SDL_Rect rect3={.x=(3*Main->SCREEN_WIDTH)/8,.y=(17*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+5)->Width,.h=(Main->SpriteList+5)->Height};
		SDL_Rect rect4={.x=(4*Main->SCREEN_WIDTH)/8,.y=(17*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+6)->Width,.h=(Main->SpriteList+6)->Height};
		SDL_Rect rect5={.x=(4*Main->SCREEN_WIDTH)/8,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+9)->Width,.h=(Main->SpriteList+9)->Height};
		SDL_Rect rect6={.x=(2*Main->SCREEN_WIDTH)/8,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+10)->Width,.h=(Main->SpriteList+10)->Height};

		if (subsettings==1){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+11)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==2){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+15)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==3 ||subsettings==5) {
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+19)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+10)->Texture,NULL,&rect6);
		}
		else if(subsettings==4 || subsettings==6){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+1)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+5)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+9)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+20)->Texture,NULL,&rect6);
		}
		if (race==1){
			if(subsettings==1)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+12)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+2)->Texture,NULL,&rect2);
		}
		else if(race==2){
			rect2.w=(Main->SpriteList+3)->Width;
			rect2.h=(Main->SpriteList+3)->Height;
			if(subsettings==1)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+13)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+3)->Texture,NULL,&rect2);
		}
		else{
			rect2.w=(Main->SpriteList+6)->Width;
			rect2.h=(Main->SpriteList+6)->Height;
			if(subsettings==1)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+14)->Texture,NULL,&rect2);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+4)->Texture,NULL,&rect2);
		}
		if (CharacterClass==1){
			if(subsettings==2)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+16)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+6)->Texture,NULL,&rect4);
		}
		else if(CharacterClass==2){
			rect2.w=(Main->SpriteList+7)->Width;
			rect2.h=(Main->SpriteList+7)->Height;
			if(subsettings==2)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+17)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+7)->Texture,NULL,&rect4);
		}
		else{
			rect2.w=(Main->SpriteList+8)->Width;
			rect2.h=(Main->SpriteList+8)->Height;
			if(subsettings==2)
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+18)->Texture,NULL,&rect4);
			else
				SDL_RenderCopy(Main->MainRender,(Main->SpriteList+8)->Texture,NULL,&rect4);
		}
	}
	else{
		SDL_Rect rect1={.x=(3*Main->SCREEN_WIDTH)/8,.y=(18*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+43)->Width,.h=(Main->SpriteList+43)->Height};
		SDL_Rect rect2={.x=(4*Main->SCREEN_WIDTH)/8,.y=(18*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+44)->Width,.h=(Main->SpriteList+44)->Height};
		SDL_Rect rect3={.x=(5*Main->SCREEN_WIDTH)/8,.y=(18*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+45)->Width,.h=(Main->SpriteList+45)->Height};
		SDL_Rect rect4={.x=(3*Main->SCREEN_WIDTH)/8,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+46)->Width,.h=(Main->SpriteList+46)->Height};
		SDL_Rect rect5={.x=(4*Main->SCREEN_WIDTH)/8,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+47)->Width,.h=(Main->SpriteList+47)->Height};
		SDL_Rect rect6={.x=(5*Main->SCREEN_WIDTH)/8,.y=(20*Main->SCREEN_HEIGHT)/24,.w=(Main->SpriteList+48)->Width,.h=(Main->SpriteList+48)->Height};
		if (subsettings==1){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+49)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==2){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+50)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==3){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+51)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==4){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+52)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==5){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+53)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+48)->Texture,NULL,&rect6);
		}
		if (subsettings==6){
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+43)->Texture,NULL,&rect1);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+44)->Texture,NULL,&rect2);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+45)->Texture,NULL,&rect3);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+46)->Texture,NULL,&rect4);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+47)->Texture,NULL,&rect5);
			SDL_RenderCopy(Main->MainRender,(Main->SpriteList+54)->Texture,NULL,&rect6);
		}
	}
	(CurrentInstance->data)[0]=subsettings;
	(CurrentInstance->data)[1]=race;
	(CurrentInstance->data)[2]=CharacterClass;
	(CurrentInstance->data)[3]=timer;
	(CurrentInstance->data)[4]=settings;
	return;
}//selección de personaje
void Room001(GlobalVariables* Main){ //seleccion de personaje
	//free media
	FreeMedia(Main->SpriteList,Main->SongList,Main->SoundList);
	Main->ins_count=0;

	wprintf(L"\n\n%c%c%c 		Room 001 		%c%c%c 	\n",4,4,4,4,4,4);

	//load media
	Objectload_001(Main);

	//Create Main Instances
	InstanceCreationCode_001(Main);
	
	Main->menu=21;
}//menu de elección de personaje
