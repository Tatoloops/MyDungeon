/* 			CODIGOS DE ACTUALIZACION POR FRAME						*/
void ActualizacionDeAnimacion(SDL_Rect* rect,Sprite* spr,int* FrameCount,int* ContadorDeAvance){

	++*ContadorDeAvance;
	if (*ContadorDeAvance>spr->speed){
		*ContadorDeAvance=1;
		++*FrameCount;
		if (*FrameCount>spr->FrameNumber-1)
			*FrameCount=0;
	}

	int a=*FrameCount;
	rect->x=(spr->FrameWidth)*a;
	rect->y=0;
	while(a>spr->FramesToTheLeft-1){
		rect->y+=spr->FrameHeight;
		rect->x-=spr->Width;
		a-=spr->FramesToTheLeft;
	}

	return;
}
void InstanceStepCodes(GlobalVariables* Main, Instance* CurrentInstance){
	

	/*		Instances step codes		*/
	int obj = (CurrentInstance)->ID;
	
 	if (obj==5) InstanceStepCode_005(Main,CurrentInstance);
	else if (obj==6) InstanceStepCode_006(Main,CurrentInstance);
	else if (obj==7) InstanceStepCode_007(Main,CurrentInstance);
	else if (obj==8) InstanceStepCode_008(Main,CurrentInstance);
	else if (obj==9) InstanceStepCode_009(Main,CurrentInstance);
}
void Refresh(GlobalVariables* Main){
	for(unsigned short i=0;i<Main->ins_count;++i){
		Instance* CurrentInstance=(Main->InstanceList)+i;
		InstanceStepCodes(Main,CurrentInstance);
	}
	SDL_RenderPresent(Main->MainRender);
}
