/*
Main Character




*/
void Objectload_005(GlobalVariables* Main){
	int spr_pos=11;
	//sprites
	if(Main->saved_data->race==1){
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+0,"media/characters/player103 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+1,"media/characters/player103 (2).bmp"); //down
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+2,"media/characters/player103 (3).bmp"); //left
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+3,"media/characters/player103 (4).bmp"); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+4,"media/characters/player103 (5).bmp",10,4,8); //muerte
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+5,"media/characters/player103 (6).bmp",10,4,8); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+6,"media/characters/player103 (7).bmp",10,4,8); //right
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+7,"media/characters/player103 (8).bmp",10,4,8); //down
	}
	else if(Main->saved_data->race==2){
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+0,"media/characters/player201 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+1,"media/characters/player201 (2).bmp"); //down
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+2,"media/characters/player201 (3).bmp"); //left
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+3,"media/characters/player201 (4).bmp"); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+4,"media/characters/player201 (5).bmp",10,4,4); //muerte
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+5,"media/characters/player201 (6).bmp",10,4,4); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+6,"media/characters/player201 (7).bmp",10,2,4); //right
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+7,"media/characters/player201 (8).bmp",10,2,4); //down
	}
	else if(Main->saved_data->race==3){
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+0,"media/characters/player303 (1).bmp"); //standing :right
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+1,"media/characters/player303 (2).bmp"); //down
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+2,"media/characters/player303 (3).bmp"); //left
			CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+3,"media/characters/player303 (4).bmp"); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+4,"media/characters/player303 (5).bmp",10,7,8); //muerte
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+5,"media/characters/player303 (6).bmp",10,7,8); //up
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+6,"media/characters/player303 (7).bmp",10,7,8); //right
			CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+7,"media/characters/player303 (8).bmp",10,7,8); //down
	}
	return;
}//Player
void Objectload_008(GlobalVariables* Main){

	int spr_pos=11; // 1 sprites
	//sprites
	if (Main->saved_data->race==1) 		//human mage
		CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player103 (9).bmp",10,4,4); //Creation
	else if (Main->saved_data->race==2) 	//Rabbitman mage
		CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player203 (9).bmp",10,4,4); //Creation
	else 							//Frogman mage
		CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player303 (9).bmp",10,4,4); //Creation
	return;
}//Magical Attack
void Objectload_009(GlobalVariables* Main){

	int spr_pos=12; // 1 sprites
	//sprites
	if (Main->saved_data->race==1) 		//human archer
		CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	else if (Main->saved_data->race==2) 	//Rabbitman archer
		CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	else 							//Frogman archer
		CreateNonAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+10,"media/characters/player013.bmp"); //Creation
	return;
}//

void InstanceCreationCode_005(GlobalVariables* Main){ // main menu 1
	int spr_pos=11;

	(Main->InstanceList+(Main->ins_count))->ID =005;
	(Main->InstanceList+(Main->ins_count))->sprite=Main->SpriteList+spr_pos+1;
	(Main->InstanceList+(Main->ins_count))->x=Main->SCREEN_WIDTH/2-(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth/2;
	(Main->InstanceList+(Main->ins_count))->y=Main->SCREEN_HEIGHT/2+MatrixSpace-(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight/2;


	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle1),
		0,
		0,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);
	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle2),
		(Main->InstanceList+(Main->ins_count))->x,
		(Main->InstanceList+(Main->ins_count))->y,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);

	(Main->InstanceList+(Main->ins_count))->data[0]=8; /*posición en la matriz 	1 - 2 - 3
																		4 - 5 - 6
																		7 - 8 - 9	*/
												//posicion 5 = (SCREEN_WIDTH/2,SCREEN_HEIGHT/2)
	(Main->InstanceList+(Main->ins_count))->data[1]=	0;
	(Main->InstanceList+(Main->ins_count))->data[2]=	0; //contadores de animacion
	(Main->InstanceList+(Main->ins_count))->data[3]=	0;
	(Main->InstanceList+(Main->ins_count))->data[4]=	0; //action
	(Main->InstanceList+(Main->ins_count))->data[5]=	0; //walking count
	(Main->InstanceList+(Main->ins_count))->data[6]=	0;
	if (Main->saved_data->hp 	>	Main->saved_data->maxhp)
		Main->saved_data->hp 	=	Main->saved_data->maxhp;
	(Main->InstanceList+(Main->ins_count))->data[7]=	Main->saved_data->hp; //hp
	(Main->InstanceList+(Main->ins_count))->data[8]=	Main->saved_data->inv[1]; //red potions
	(Main->InstanceList+(Main->ins_count))->data[9]=	Main->saved_data->inv[2]; //blue potions
	(Main->InstanceList+(Main->ins_count))->data[10]=	Main->saved_data->maxenergy; //blue potions


	++(Main->ins_count);
} //player
void InstanceCreationCode_008(GlobalVariables* Main){

	(Main->InstanceList+(Main->ins_count))->ID= 8;
	(Main->InstanceList+(Main->ins_count))->sprite=Main->SpriteList+21;

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle1),
		0,
		0,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle2),
		(Main->InstanceList+(Main->ins_count))->x,
		(Main->InstanceList+(Main->ins_count))->y,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth*2,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight*2);

	((Main->InstanceList+(Main->ins_count))->data)[0]=2; //speed
	((Main->InstanceList+(Main->ins_count))->data)[1]=2; //damage
	((Main->InstanceList+(Main->ins_count))->data)[2]=0;  /*	position	1 - 2 - 3
																			4 - 5 - 6
																			7 - 8 - 9 	*/

	++(Main->ins_count);
} //player fireball attack
void InstanceCreationCode_009(GlobalVariables* Main){ // main menu 1

	(Main->InstanceList+(Main->ins_count))->ID= 9;
	(Main->InstanceList+(Main->ins_count))->sprite=Main->SpriteList+22;

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle1),
		0,
		0,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle2),
		(Main->InstanceList+(Main->ins_count))->x,
		(Main->InstanceList+(Main->ins_count))->y,(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth*2,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight*2);

	((Main->InstanceList+(Main->ins_count))->data)[0]=12; //speed
	((Main->InstanceList+(Main->ins_count))->data)[1]=1; //damage
	((Main->InstanceList+(Main->ins_count))->data)[2]=0;  /*	position	1 - 2 - 3
																4 - 5 - 6
																7 - 8 - 9 	*/

	++(Main->ins_count);
} //player arrow attack

void InstanceStepCode_005(GlobalVariables* Main,Instance* CurrentInstance){
	int CurrentSprites=11;
	int position=(CurrentInstance->data)[0]; // position // 4 5 6
														//	7 8 9
	int timer=(CurrentInstance->data)[1];
	//			CurrentInstance->data[2] -> Frame count
	//			CurrentInstance->data[3] -> Frame advance
	int action=(CurrentInstance)->data[4]; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking up,
												2:walking down,
												3:walking left,
												4:walking right,
											//	5:getting hit,
												6:attack1, */

	float walking=(CurrentInstance)->data[5];		//walking
	int isborn=(CurrentInstance)->data[6];	//is born
	int hp=(CurrentInstance)->data[7];	//hp
	int redpotions=(CurrentInstance)->data[8];
	int bluepotions=(CurrentInstance)->data[9];
	int energy=(CurrentInstance)->data[10];


	if (hp<1 || (Main->InstanceList+2)->data[5]<1) //you are dead
		return;

	float movespeed=Main->saved_data->movspeed; //movement speed

	if (action==0){ //The player is not doing anything
		if (Main->FrameKey[0]&0x1){ //moving up
			if (position>=7 && position <=9){
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+4); //walking up
				(CurrentInstance->data)[2]=0; // reset animation
				position-=3;
				action=1;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+0);//standing up
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (Main->FrameKey[1]&1){ //pressed the key to move down
			if (position>=4 && position <=6){
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+5); //walking down
				(CurrentInstance->data)[2]=0; // reset animation
				position+=3;
				action=2;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1); //standing down
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (Main->FrameKey[2]&0x1){ //pressed the key to move left
			if (position!=4 && position !=7){
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+6); //walking left
				(CurrentInstance->data)[2]=0; // reset animation
				position-=1;
				action=3;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+2); //standing left
				(CurrentInstance->data)[2]=0;
			}
		}
		else if (Main->FrameKey[3]&1){ //pressed the key to move right
			if (position!=6 && position !=9){
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+7); //walking right
				(CurrentInstance->data)[2]=0; // reset animation
				position+=1;
				action=4;
				walking=MatrixSpace;
				walking=walking/movespeed;
			}
			else{
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+3); //standing right
				(CurrentInstance->data)[2]=0;
			}
		}
		else if(Main->FrameKey[5]&1){ //atk 1
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+4); //attacking pose
			walking=Main->saved_data->atkspeed;
			action=6;
		}
		else if(Main->FrameKey[7]&1){ //pocion //button a
			if(redpotions>0 && hp<Main->saved_data->maxhp){
				--redpotions;
				hp+=10;
				if (hp>=Main->saved_data->maxhp)
					hp=Main->saved_data->maxhp;
			}

		}
		else if(Main->FrameKey[8]&1){ //pocion //button s
			if(bluepotions>0 && energy<Main->saved_data->maxenergy){
				--bluepotions;
				energy+=10;
				if (energy>=Main->saved_data->maxenergy)
					energy=Main->saved_data->maxenergy;
			}

		}
	}
	else if(action==1){ //the player is walking up
		if (walking>0){
			(CurrentInstance)->y-=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+0);
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->y=Main->SCREEN_HEIGHT/2-(CurrentInstance)->sprite->FrameHeight/2;
			action=0;
		}//walking up
	}
	else if(action==2){ //the player is walking down
		if (walking>0){
			(CurrentInstance)->y+=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->y=Main->SCREEN_HEIGHT/2-(CurrentInstance)->sprite->FrameHeight/2+MatrixSpace;
			action=0;
		}//walking up
	}
	else if(action==3){ //the player is walking left
		if (walking>0){
			(CurrentInstance)->x-=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+2);
			(CurrentInstance->data)[2]=0;
			if (position==4 || position==7){
				(CurrentInstance)->x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else {
				(CurrentInstance)->x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			action=0;
		}//walking up
	}
	else if(action==4){ //the player is walking right
		if (walking>0){
			(CurrentInstance)->x+=movespeed;
			--walking;
		}
		else{
			walking=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+3);
			(CurrentInstance->data)[2]=0;
			if (position==5 || position==8){
				(CurrentInstance)->x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else {
				(CurrentInstance)->x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
		}//walking up
	}
	else if(action==6){ //player is attacking --ATACK
		--walking;
		if (walking<0){
			walking=0;
			action=0;
			(CurrentInstance->data)[2]=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+0);
			if (Main->saved_data->CharacterClass==3){
				InstanceCreationCode_008(Main);
				((Main->InstanceList+Main->ins_count-1)->data)[0]=3;
				((Main->InstanceList+Main->ins_count-1)->data)[1]=Main->saved_data->atk; //damage
				(Main->InstanceList+Main->ins_count-1)->rectangle2.x=CurrentInstance->rectangle2.x;
				(Main->InstanceList+Main->ins_count-1)->rectangle2.y=CurrentInstance->rectangle2.y-CurrentInstance->rectangle2.w/2;
			}
			else if (Main->saved_data->CharacterClass==1){ //warrior
				if ((Main->InstanceList+2)->data[0]==position-3 && (Main->InstanceList+2)->data[4]==0){
					(Main->InstanceList+2)->data[5]-=Main->saved_data->atk;
				}

			}
			else {
				InstanceCreationCode_009(Main);
				((Main->InstanceList+Main->ins_count-1)->data)[1]=Main->saved_data->atk; //damage
				(Main->InstanceList+Main->ins_count-1)->rectangle2.x=CurrentInstance->rectangle2.x;
				(Main->InstanceList+Main->ins_count-1)->rectangle2.y=CurrentInstance->rectangle2.y-CurrentInstance->rectangle2.w/2;
			}
		}
	}

	(CurrentInstance)->rectangle2.y=(CurrentInstance)->y;
	(CurrentInstance)->rectangle2.x=(CurrentInstance)->x;
	if (action!=0)
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	else{
		CurrentInstance->rectangle1.x=0;
		CurrentInstance->rectangle1.y=0;
	}
	SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
	(CurrentInstance->data)[0]=position; // position // 4 5 6
														//	7 8 9
	(CurrentInstance->data)[1]=timer;
	//			CurrentInstance->data[2] -> Frame count
	//			CurrentInstance->data[3] -> Frame advance
	(CurrentInstance->data)[4]=action; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking up,
												2:walking down,
												3:walking left,
												4:walking right,
												5:getting hit,
												6:attack1, */

	(CurrentInstance->data)[5]=walking;		//walking count
	(CurrentInstance->data)[6]=isborn;	//is born
	(CurrentInstance->data)[7]=hp;	//hp
	(Main->InstanceList+(Main->ins_count))->data[8]=redpotions;
	(Main->InstanceList+(Main->ins_count))->data[9]=bluepotions;
	(Main->InstanceList+(Main->ins_count))->data[10]=energy;

	return;
}//Player
void InstanceStepCode_008(GlobalVariables* Main,Instance* CurrentInstance){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int monsterx=0;
	int monstery=0;
	int monsterwidth=0;
	int monsterheight=0;
	if((Main->InstanceList+2)!=NULL){
		monsterx=(Main->InstanceList+2)->rectangle2.x;
		monstery=(Main->InstanceList+2)->rectangle2.y;
		monsterwidth=(Main->InstanceList+2)->rectangle2.w;
		monsterheight=(Main->InstanceList+2)->rectangle2.h;
	}
	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y-=speed;
	if(y<-20){ //out of window
		//destruir
		InstanceDestroy(Main,CurrentInstance);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >monsterx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <monsterx+monsterwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >monstery &&
		y+CurrentInstance->sprite->FrameHeight/2 <monstery+monsterheight){
		(Main->InstanceList+2)->data[5]-=CurrentInstance->data[1];
		InstanceDestroy(Main,CurrentInstance);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}


	//imprimir
	ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));



	//devolver variables
	CurrentInstance->rectangle2.x=x;
	CurrentInstance->rectangle2.y=y;

	return;
}//player attack1
void InstanceStepCode_009(GlobalVariables* Main,Instance* CurrentInstance){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int monsterx=0;
	int monstery=0;
	int monsterwidth=0;
	int monsterheight=0;
	if((Main->InstanceList+2)!=NULL){
		monsterx=(Main->InstanceList+2)->rectangle2.x;
		monstery=(Main->InstanceList+2)->rectangle2.y;
		monsterwidth=(Main->InstanceList+2)->rectangle2.w;
		monsterheight=(Main->InstanceList+2)->rectangle2.h;
	}
	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y-=speed;
	if(y<-20){ //out of window
		//destruir
		InstanceDestroy(Main,CurrentInstance);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >monsterx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <monsterx+monsterwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >monstery &&
		y+CurrentInstance->sprite->FrameHeight/2 <monstery+monsterheight){
		(Main->InstanceList+2)->data[5]-=CurrentInstance->data[1];
		InstanceDestroy(Main,CurrentInstance);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}


	//imprimir
	ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
	SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));



	//devolver variables
	CurrentInstance->rectangle2.x=x;
	CurrentInstance->rectangle2.y=y;

	return;
}//player attack2