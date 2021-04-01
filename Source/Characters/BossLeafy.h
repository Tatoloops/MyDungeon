/*

*/
void Objectload_006(GlobalVariables* Main){
	int spr_pos=31; // 7 sprites

	//sprites
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+0,"media/characters/500.bmp",10,20,8); //Creation
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+1,"media/characters/501.bmp",15,4,8); //Idle
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+2,"media/characters/502.bmp",15,4,8); //walking
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+3,"media/characters/503.bmp",15,3,8); //jump
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+4,"media/characters/504.bmp",15,5,8); //dead
	//free media
	SDL_DestroyTexture((Main->SpriteList+1)->Texture);
	//here we destroy the media, because we are changing another Object's media files
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+1,"media/characters/505.bmp",5,3,8); //Enemy spot
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+6,"media/characters/506.bmp",15,3,8); //floor2

	return;
}//Leaf Enemy
void Objectload_007(GlobalVariables* Main){
	int spr_pos=28; // 1 sprites
	//sprites
	CreateAnimatedSprite(Main->MainRender,Main->SpriteList+spr_pos+0,"media/characters/507.bmp",10,19,8); //Creation


	return;
}//Leaf attack

void InstanceCreationCode_006(GlobalVariables* Main){ // main menu 1

	(Main->InstanceList+(Main->ins_count))->ID =006;
	(Main->InstanceList+(Main->ins_count))->sprite=Main->SpriteList+31;
	(Main->InstanceList+(Main->ins_count))->x=Main->SCREEN_WIDTH/2-(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth/2;
	(Main->InstanceList+(Main->ins_count))->y=Main->SCREEN_HEIGHT/2-MatrixSpace-(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight/2-50;
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
	(Main->InstanceList+(Main->ins_count))->data[0]=2; /*posición en la matriz 	1 - 2 - 3
																				4 - 5 - 6
																				7 - 8 - 9	*/
												//posicion 2 = (SCREEN_WIDTH/2,SCREEN_HEIGHT/2-MatrixSpace)
	((Main->InstanceList+(Main->ins_count))->data)[1]=0; //timer
	((Main->InstanceList+(Main->ins_count))->data)[2]=0; //contador de frame de animacion
	((Main->InstanceList+(Main->ins_count))->data)[3]=0; //contador de avance de frame de animacion
	((Main->InstanceList+(Main->ins_count))->data)[4]=-1; //movimiento actual: 0:sin movimiento 1:a la izquierda 2:derecha
	((Main->InstanceList+(Main->ins_count))->data)[5]=150+5*(Main->saved_data->lvl); //HP
	((Main->InstanceList+(Main->ins_count))->data)[6]=0; //is born
	((Main->InstanceList+(Main->ins_count))->data)[7]=0; //walking count
	((Main->InstanceList+(Main->ins_count))->data)[8]=150+5*(Main->saved_data->lvl); //MAXHP




		++(Main->ins_count);
} //leaf monster
void InstanceCreationCode_007(GlobalVariables* Main){ // main menu 1

	(Main->InstanceList+(Main->ins_count))->ID =007;
	(Main->InstanceList+(Main->ins_count))->sprite=Main->SpriteList+28;

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle1),
		0,
		0,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);

	createrectangle(&((Main->InstanceList+(Main->ins_count))->rectangle2),
		(Main->InstanceList+(Main->ins_count))->x,
		(Main->InstanceList+(Main->ins_count))->y,(Main->InstanceList+(Main->ins_count))->sprite->FrameWidth,
		(Main->InstanceList+(Main->ins_count))->sprite->FrameHeight);

	((Main->InstanceList+(Main->ins_count))->data)[0]=rand()%5+1; //speed
	((Main->InstanceList+(Main->ins_count))->data)[1]=7+Main->saved_data->lvl;//damage
	((Main->InstanceList+(Main->ins_count))->data)[2]=0; 	//frame things

	++(Main->ins_count);
} //leaf attack

void InstanceStepCode_006(GlobalVariables* Main,Instance* CurrentInstance){
	srand(time(NULL));
	//nombrar variables
	int CurrentSprites=31;

	int position=(CurrentInstance->data)[0]; // position // 1 2 3
	int timer=(CurrentInstance->data)[1]; //timer
	int action=(CurrentInstance)->data[4]; /* 	-2:dying
												-1:being born
												0:standing,
												1:walking left,
												2:walking right,
												3:getting hit,
												4:attack1, */

	int hp=(CurrentInstance)->data[5]; //hp
	int isborn=(CurrentInstance)->data[6]; //is born
	int walking=(CurrentInstance)->data[7]; //walking count
	int movespeed=2;
	int attacknumber=0;

	if (hp<1 || (Main->InstanceList+1)->data[7]<1)
		return;

	if(action==0){ //standing
		++timer;
		if((Main->InstanceList+0)->data[position]>0){ //the monster got hit by an attack
			hp-=(Main->InstanceList+0)->data[position];
			action=-1;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+0);
			isborn=0;
		}
		if (hp<1){
			(action=-2); //monster died
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+4);
			(CurrentInstance->data)[2]=0;
			isborn=0;
		}
		if (timer%50==0){ //attack1
			int a=rand()%6;
			if(a==0||a==5){
				(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+3); //attack sprite
				(CurrentInstance->data)[2]=0;
				action=4;
				isborn=60;
			}
		}
		if (timer==500){//caminar
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+2); //walking
			(CurrentInstance->data)[2]=0;
			if (position==1) {
				position=2;
				action=2;
			}
			else if(position==2) {
				action=((rand()%2));
				if (action==0) {
					action=1;
					position=1;
				}
				else{
					action=2;
					position=3;
				}
			}
			else { //position==3
				position=2;
				action=1;
			}
			walking=MatrixSpace/movespeed;
		}
	}
	else if(action==1){
		if (walking>0){
			(CurrentInstance)->rectangle2.x-=movespeed;
			--walking;
		}
		else{
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			if (position==1){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else if (position==2){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else if (position==3){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
			timer=0;
		}//walking left
	}
	else if(action==2){ //walking right
		if (walking>0){
			(CurrentInstance)->rectangle2.x+=movespeed;
			--walking;
		}
		else{
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
			if (position==1){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2-MatrixSpace;
			}
			else if (position==2){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2;
			}
			else if (position==3){
				(CurrentInstance)->rectangle2.x=Main->SCREEN_WIDTH/2-(CurrentInstance)->sprite->FrameWidth/2+MatrixSpace;
			}
			action=0;
			timer=0;
		}
	}
	else if(action==3){

	}
	else if(action==4){ //attack1
		--isborn;
		if(isborn%12==0){
			InstanceCreationCode_007(Main);
			(Main->InstanceList+Main->ins_count-1)->rectangle2.x=(CurrentInstance)->rectangle2.x+((Main->InstanceList+Main->ins_count-1)->sprite->FrameWidth/2);
			(Main->InstanceList+Main->ins_count-1)->rectangle2.y=(CurrentInstance)->rectangle2.y;
			(Main->InstanceList+Main->ins_count-1)->data[0]=(rand()+attacknumber)%8; //speed
		}
		if(isborn==0){
			action=0;
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1);
			(CurrentInstance->data)[2]=0;
		}
	}
	else if(action==-1){ //being born
		if((CurrentInstance)->data[2]==2)
			isborn=1;
		if(isborn==1 && (CurrentInstance)->data[2]==0){
			(CurrentInstance)->sprite=(Main->SpriteList+CurrentSprites+1); //IDLE sprite
			(CurrentInstance->data)[2]=0;
			action=0;
		}

	}
	else if(action==-2){ //dead //por terminar
		if((CurrentInstance)->data[2]==2)
			isborn=1;
		if(isborn==1 && (CurrentInstance)->data[2]==0){
			(CurrentInstance->data)[2]=0;
			(Main->InstanceList+0)->data[18]=CurrentInstance->rectangle2.x;
			(Main->InstanceList+0)->data[19]=CurrentInstance->rectangle2.y;
		}

	}
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
	//devolver variables
	(CurrentInstance->data)[0]=position;
	(CurrentInstance)->data[1]=timer;
	(CurrentInstance)->data[4]=action;
	(CurrentInstance)->data[5]=hp;
	(CurrentInstance)->data[6]=isborn;
	(CurrentInstance)->data[7]=walking;
	return;
}//Leaf Monster
void InstanceStepCode_007(GlobalVariables* Main,Instance* CurrentInstance){
	//tomar varaibles

	int x=CurrentInstance->rectangle2.x;
	int y=CurrentInstance->rectangle2.y;
	int playerx=0;
	int playery=0;
	int playerwidth=0;
	int playerheight=0;
	if((Main->InstanceList+1)->ID==005){
		playerx=(Main->InstanceList+1)->rectangle2.x;
		playery=(Main->InstanceList+1)->rectangle2.y;
		playerwidth=(Main->InstanceList+1)->rectangle2.w;
		playerheight=(Main->InstanceList+1)->rectangle2.h;
	}

	int speed=CurrentInstance->data[0];
	//  CurrentInstance->data[1]; //damage


	y+=speed;
	if(y>760){ //out of window
		//destruir
		InstanceDestroy(Main,CurrentInstance);
		ActualizacionDeAnimacion(&(CurrentInstance->rectangle1),(CurrentInstance)->sprite,((CurrentInstance)->data)+2,((CurrentInstance)->data)+3);
		SDL_RenderCopy(Main->MainRender,(CurrentInstance)->sprite->Texture,&(CurrentInstance->rectangle1),&(CurrentInstance->rectangle2));
		return;
	}
	if(x+CurrentInstance->sprite->FrameWidth/2 >playerx &&  //hit player
		x+CurrentInstance->sprite->FrameWidth/2 <playerx+playerwidth &&
		y+CurrentInstance->sprite->FrameHeight/2 >playery &&
		y+CurrentInstance->sprite->FrameHeight/2 <playery+playerheight){
		int damage=CurrentInstance->data[1]-Main->saved_data->def;
		if (damage>0)
			(Main->InstanceList+1)->data[7]-=damage;
		else
			(Main->InstanceList+1)->data[7]-=1;
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
}//leaf attack1