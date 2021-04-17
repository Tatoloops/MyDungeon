/*      SDL TEXTURES        */
/*
SDL_Surface* optimizedsurface(SDL_Surface* mainsurface,const char*impath ){
    SDL_Surface* optimized_surf=NULL;
    SDL_Surface* surface=SDL_LoadBMP(impath);
    if(surface==NULL)
        printf("error: %s",SDL_GetError());
    else{
        optimized_surf=SDL_ConvertSurface(surface,mainsurface->format,0);
        if (optimized_surf==NULL)
            printf("error: %s",SDL_GetError());
    }
    closing_surface(surface);
    return optimized_surf;
}
*/

#define MaxSprites 		210
#define MaxInstances 	100
#define MaxSongs		4
#define MaxSounds		10
#define KeyNumber		14
#define MatrixSpace		200 //space between boxes of the matrixes
#define MaxDataSaves	7


typedef struct{
    SDL_Texture* Texture;
    int Width;          //Queried Texture: size of the whole file in pixels
    int Height;
    int FrameWidth;     //size of each rectangle, for animations
    int FrameHeight;
    int FrameNumber;    //number of frames
    int speed;

    int FramesToTheLeft;
}Sprite;

#define LangSize		94
typedef struct{
	SDL_Texture* 	Texture;				//Full Texture
	SDL_Rect		SrcRect[LangSize];		//Rectangles containing all letters and characters.
	//SDL_Rect		TrueRect[LangSize];		//Position and size usable when characters are too big or bad positioned.
	SDL_Color		Blender;				//Colors and Alpha. (rgba, Uint8)
}Language;

typedef struct{
	Language*			PtrToLang;	//Language Texture pointer
	SDL_Rect			SrcR;		//Position of the Letter in Language Texture
	SDL_Rect 			DestR;		//position in window rectangle
}InsText;

typedef struct{
    int ID;
    char name[20];
    int intx;
    int inty;
    float x;
    float y;
    //int* IDList;
    Sprite* sprite;
    SDL_Rect rectangle1;    //sprite rectangle
    SDL_Rect rectangle2;    //position in window rectangle
    int data[20];
    float floatdata[20];
    char dataname[20];
}Instance;

typedef struct{
    char name[20];
    int race; // 1: human 2:Rabbitman 3:dwarf
    int CharacterClass; //1: warrior 2:archer 3:mage
    int lvl;
    int exp;
    int gold;


    int maxhp;
    int maxenergy;
    int hp;
    int def;
    int atk;
    int atkspec;
    int energy;

	float movspeed;
	float atkspeed;

	int inv[20];
	int battle;
}Save;



typedef struct{
	/*  
	GameVersion: "1.016.001'\0'"
	->GameModel         =   "001'\0'"
	->GameMajorUpdate   =   "016'\0'"  
	->GameRevision      =   "001'\0'"    */ 
	unsigned char GameVersion[12];
	unsigned char GameModel[4];
	unsigned char GameMajorUpdate[4];
	unsigned char GameRevision[4];
}GameVersion;


typedef struct{
	SDL_Window* MainWindow;
	SDL_Renderer* MainRender;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	Instance	InstanceList[MaxInstances];
	Sprite		SpriteList[MaxSprites];
	Mix_Music*	SongList[MaxSongs];
	Mix_Chunk*	SoundList[MaxSounds];
	int ins_count;

	unsigned char	RoomCurrentID;
	unsigned char	RoomState;
	
	SDL_Event MainEvent;

	//FPS Control
	Uint32  FramesPerSecond;
	Uint32  TicksPerFrame;
	Uint32	PrevTime;
	Uint32	CurrentTime;


	char PreviousKey[KeyNumber];
	char FrameKey[KeyNumber];
	
	Save saved_data[MaxDataSaves];
	FILE* Savedata;
	char SavedataName[16];
	GameVersion GameVersionCurrent;
	GameVersion GameVersionData;
}GlobalVariables;

SDL_Surface* LoadTexture(SDL_Renderer* MainRender,const char* impath,char* error){
	SDL_Texture* newtexture =NULL;
	SDL_Surface* surface=SDL_LoadBMP(impath);
	if(surface==NULL){
		wprintf(L"\n%c	Error:%S",0x488,SDL_GetError());
		*(error)=*error|0x3;
	}
	else{
		newtexture=SDL_CreateTextureFromSurface(MainRender,surface);
		if (newtexture==NULL){
			wprintf(L"\n%c	Error loading texture %S: %S",0x488,impath,SDL_GetError());
			*error|=0x7;
		}
	}
	SDL_FreeSurface(surface);
	return newtexture;
}

SDL_Texture* CreateTextureFont(SDL_Renderer* MainRender,SDL_Color* color,const char*text,
	int ptsize,const char*impath,int outline,int hinting,char* error){

	TTF_Font*font;
	font=TTF_OpenFont(impath,ptsize);
	if (font==NULL){ //ptsize es el size del font (size de la letra)
		wprintf(L"%c\n	Error:%S",0x488,TTF_GetError());
		*error=(*error)|0x7;
		}
	else{
		TTF_SetFontOutline(font,outline);
		TTF_SetFontHinting(font,hinting);
	}
	
	SDL_Surface*surface;
	surface=TTF_RenderText_Blended(font,text,*color);
	//surface=TTF_RenderText_Solid(font,text,*color);
	SDL_Texture* texture=SDL_CreateTextureFromSurface(MainRender,surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}
/*      Sprites         */
void CreateAnimatedSprite(SDL_Renderer* MainRender,Sprite* spr,const char* impath,int speed,int frames,int framestoleft,char* error){
	spr->Texture=LoadTexture(MainRender,impath,error);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));

	spr->FrameWidth=(spr->Width)/framestoleft;

	int SquaresHeight;

	if (frames>framestoleft)
		SquaresHeight=spr->Height/((frames/framestoleft)+1);
	else
		SquaresHeight=spr->Height;

	spr->FrameHeight=SquaresHeight;
	spr->FrameNumber=frames;
	spr->speed=speed;
	spr->FramesToTheLeft=framestoleft;
}
void CreateNonAnimatedSprite(SDL_Renderer* MainRender,Sprite* spr,const char* impath,char* error){
	spr->Texture=LoadTexture(MainRender,impath,error);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
	spr->FrameWidth=(spr->Width);
	spr->FrameHeight=(spr->Height);
	spr->FrameNumber=1;
	spr->speed=0;
}
void CreateNonAnimatedFont(SDL_Renderer* MainRender,SDL_Color* color,Sprite* spr,char* text,const char* impath,int size,int outline,int hinting,char* error){
	spr->Texture=CreateTextureFont(MainRender,color,text,size,impath,outline,hinting,error);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
	spr->FrameWidth=spr->Width;
	spr->FrameHeight=spr->Height;
	spr->FrameNumber=1;
	spr->speed=0;
}
void CreateNonAnimatedBackground(GlobalVariables* Main,SDL_Renderer* MainRender,Sprite* spr,const char* impath,char* error){
	spr->Texture=LoadTexture(MainRender,impath,error);
	SDL_QueryTexture(spr->Texture,NULL,NULL,&(spr->Width),&(spr->Height));
	spr->FrameWidth=Main->SCREEN_WIDTH;
	spr->FrameHeight=Main->SCREEN_HEIGHT;
	spr->FrameNumber=1;
	spr->speed=0;
}
void CreateAlphabetEnglishCSensitive52(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,
	const char* impath,int size,int outline,int hinting,char* error){
	int PackSize=52;	//Amount of characters to convert.
	char HalfPackSize=26;
	/*
	SDL_Renderer* Renderer		//	Renderer
	SDL_Color* color			//	Color of the Letters
	Sprite* SprList				//	Pointer to the SpriteList
	const char* impath			//	path of the Font to use
	int size					//	Size of Letters
	char* error					//	pointer to error
	*/
	char Character='a';
	for(unsigned short i=0;i<HalfPackSize;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
	Character='A';
	for(unsigned short i=HalfPackSize;i<PackSize;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
}
void CreateNumbersEnglish10(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,
	const char* impath,int size,int outline,int hinting,char* error){
	int PackSize=10;	//Amount of characters to convert.
	char Character='0';
	for(unsigned short i=0;i<PackSize;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
}
void CreateSymbolsEnglish32(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,
	const char* impath,int size,int outline,int hinting,char* error){/*
											*(pointer+62)='!'	*(pointer+63)='"'
	*(pointer+64)='#'	*(pointer+65)='$'	*(pointer+66)='%'	*(pointer+67)='&'
	*(pointer+68)='''	*(pointer+69)='('	*(pointer+70)=')'	*(pointer+71)='*'
	*(pointer+72)='+'	*(pointer+73)=','	*(pointer+74)='-'	*(pointer+75)='.'
	*(pointer+76)='/'	
						*(pointer+77)=':'	*(pointer+78)=';'	*(pointer+79)='<'
	*(pointer+80)='='	*(pointer+81)='>'	*(pointer+82)='?'	*(pointer+83)='@'

	*(pointer+84)='['	*(pointer+85)='\'	*(pointer+86)=']'	*(pointer+87)='^'
	*(pointer+88)='_'	*(pointer+89)='`'	
											*(pointer+90)='{'	*(pointer+91)='|'
	*(pointer+92)='}'	*(pointer+93)='~'
	*/
	unsigned short PackPart1=	15;				//15
	unsigned short PackPart2=	PackPart1+7;	//22
	unsigned short PackPart3=	PackPart2+6;	//28
	unsigned short PackSize	=	PackPart3+4;	//32
	char Character='!';
	for(unsigned short i =0;i<PackPart1;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
	Character=':';
	for(unsigned short i =PackPart1;i<PackPart2;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
	Character='[';
	for(unsigned short i =PackPart2;i<PackPart3;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
	Character='{';
	for(unsigned short i =PackPart3;i<PackSize;++i){
		CreateNonAnimatedFont(Renderer,Color,SprList+i,&Character,impath,size,outline,hinting,error);
		Character++;
	}
}
void CreateLanguageEnglishRegular94(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,const char* impath,int size,
	int outline,int hinting,char* error){
	/*
	UTF 8 // ASCII ORDER
	'!' = 33	-> ~ = 126 
	*/
	for (char Character =33;Character<127;++Character){
		CreateNonAnimatedFont(Renderer,Color,SprList+Character-'!',&Character,impath,size,outline,hinting,error);
	}
	
}
void CreateLanguageEnglishBasic(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,
	const char* impath,int size,int outline,int hinting,char* error){
	unsigned char PackSize=94;
	/*
	*(pointer+0)='0'	*(pointer+1)='1'	*(pointer+2)='2'	*(pointer+3)='3'
	*(pointer+4)='4'	*(pointer+5)='5'	*(pointer+6)='6'	*(pointer+7)='7'
	*(pointer+8)='8'	*(pointer+9)='9'	
											*(pointer+10)='a'	*(pointer+11)='b'
	*(pointer+12)='c'	*(pointer+13)='d'	*(pointer+14)='e'	*(pointer+15)='f'
	*(pointer+16)='g'	*(pointer+17)='h'	*(pointer+18)='i'	*(pointer+19)='j'
	*(pointer+20)='k'	*(pointer+21)='l'	*(pointer+22)='m'	*(pointer+23)='n'
	*(pointer+24)='o'	*(pointer+25)='p'	*(pointer+26)='q'	*(pointer+27)='r'
	*(pointer+28)='s'	*(pointer+29)='t'	*(pointer+30)='u'	*(pointer+31)='v'
	*(pointer+32)='w'	*(pointer+33)='x'	*(pointer+34)='y'	*(pointer+35)='z'

	*(pointer+36)='A'	*(pointer+37)='B'	*(pointer+38)='C'	*(pointer+39)='D'
	*(pointer+40)='E'	*(pointer+41)='F'	*(pointer+42)='G'	*(pointer+43)='H'
	*(pointer+44)='I'	*(pointer+45)='J'	*(pointer+46)='K'	*(pointer+47)='L'
	*(pointer+48)='M'	*(pointer+49)='N'	*(pointer+50)='O'	*(pointer+51)='P'
	*(pointer+52)='Q'	*(pointer+53)='R'	*(pointer+54)='S'	*(pointer+55)='T'
	*(pointer+56)='U'	*(pointer+57)='V'	*(pointer+58)='W'	*(pointer+59)='X'
	*(pointer+60)='Y'	*(pointer+61)='Z'	
											*(pointer+62)='!'	*(pointer+63)='"'
	*(pointer+64)='#'	*(pointer+65)='$'	*(pointer+66)='%'	*(pointer+67)='&'
	*(pointer+68)='''	*(pointer+69)='('	*(pointer+70)=')'	*(pointer+71)='*'
	*(pointer+72)='+'	*(pointer+73)=','	*(pointer+74)='-'	*(pointer+75)='.'
	*(pointer+76)='/'	
						*(pointer+77)=':'	*(pointer+78)=';'	*(pointer+79)='<'
	*(pointer+80)='='	*(pointer+81)='>'	*(pointer+82)='?'	*(pointer+83)='@'

	*(pointer+84)='['	*(pointer+85)='\'	*(pointer+86)=']'	*(pointer+87)='^'
	*(pointer+88)='_'	*(pointer+89)='`'	
											*(pointer+90)='{'	*(pointer+91)='|'
	*(pointer+92)='}'	*(pointer+93)='~'
	*/
	CreateNumbersEnglish10(Renderer,Color,SprList,impath,size,outline,hinting,error);
	CreateAlphabetEnglishCSensitive52(Renderer,Color,SprList+10,impath,size,outline,hinting,error);
	CreateSymbolsEnglish32(Renderer,Color,SprList+10+52,impath,size,outline, hinting,error);
}

void CreateLanguageEnglish94TextureLoad(GlobalVariables* Main,SDL_Color* Color,Language* Lang,const char* impath,
	int size,int outline,int hinting,char* error){
	//SDL_Renderer* TempRenderer=SDL_CreateRenderer(Main->MainWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	int TemporaryWidth=0;
	int TemporaryHeight=0;
	int FinalWidth=0;
	int FinalHeight=0;
	TTF_Font* TempFont=TTF_OpenFont(impath,size);
	if (TempFont==NULL){ //size es el size del font (size de la letra)
		wprintf(L"\n%c	Error:%S",0x488,TTF_GetError());
		*error=(*error)|0x7;
		}
	else{
		TTF_SetFontOutline(TempFont,outline);
		TTF_SetFontHinting(TempFont,hinting);
	}
	
	
	for(unsigned short i=0;i<LangSize;++i){
		if (i==0)		{TTF_SizeText(TempFont,"!",&TemporaryWidth,&TemporaryHeight);}		
		else if (i==1)	{TTF_SizeText(TempFont,"\"",&TemporaryWidth,&TemporaryHeight);}
		else if (i==2)	{TTF_SizeText(TempFont,"#",&TemporaryWidth,&TemporaryHeight);}
		else if (i==3)	{TTF_SizeText(TempFont,"$",&TemporaryWidth,&TemporaryHeight);}
		else if (i==4)	{TTF_SizeText(TempFont,"%",&TemporaryWidth,&TemporaryHeight);}
		else if (i==5)	{TTF_SizeText(TempFont,"&",&TemporaryWidth,&TemporaryHeight);}
		else if (i==6)	{TTF_SizeText(TempFont,"'",&TemporaryWidth,&TemporaryHeight);}
		else if (i==7)	{TTF_SizeText(TempFont,"(",&TemporaryWidth,&TemporaryHeight);}
		else if (i==8)	{TTF_SizeText(TempFont,")",&TemporaryWidth,&TemporaryHeight);}
		else if (i==9)	{TTF_SizeText(TempFont,"*",&TemporaryWidth,&TemporaryHeight);}
		else if (i==10)	{TTF_SizeText(TempFont,"+",&TemporaryWidth,&TemporaryHeight);}
		else if (i==11)	{TTF_SizeText(TempFont,",",&TemporaryWidth,&TemporaryHeight);}
		else if (i==12)	{TTF_SizeText(TempFont,"-",&TemporaryWidth,&TemporaryHeight);}
		else if (i==13)	{TTF_SizeText(TempFont,".",&TemporaryWidth,&TemporaryHeight);}
		else if (i==14)	{TTF_SizeText(TempFont,"/",&TemporaryWidth,&TemporaryHeight);}
		else if (i==15)	{TTF_SizeText(TempFont,"0",&TemporaryWidth,&TemporaryHeight);}
		else if (i==16)	{TTF_SizeText(TempFont,"1",&TemporaryWidth,&TemporaryHeight);}
		else if (i==17)	{TTF_SizeText(TempFont,"2",&TemporaryWidth,&TemporaryHeight);}
		else if (i==18)	{TTF_SizeText(TempFont,"3",&TemporaryWidth,&TemporaryHeight);}
		else if (i==19)	{TTF_SizeText(TempFont,"4",&TemporaryWidth,&TemporaryHeight);}
		else if (i==20)	{TTF_SizeText(TempFont,"5",&TemporaryWidth,&TemporaryHeight);}
		else if (i==21)	{TTF_SizeText(TempFont,"6",&TemporaryWidth,&TemporaryHeight);}
		else if (i==22)	{TTF_SizeText(TempFont,"7",&TemporaryWidth,&TemporaryHeight);}
		else if (i==23)	{TTF_SizeText(TempFont,"8",&TemporaryWidth,&TemporaryHeight);}
		else if (i==24)	{TTF_SizeText(TempFont,"9",&TemporaryWidth,&TemporaryHeight);}
		else if (i==25)	{TTF_SizeText(TempFont,":",&TemporaryWidth,&TemporaryHeight);}
		else if (i==26)	{TTF_SizeText(TempFont,";",&TemporaryWidth,&TemporaryHeight);}
		else if (i==27)	{TTF_SizeText(TempFont,"<",&TemporaryWidth,&TemporaryHeight);}
		else if (i==28)	{TTF_SizeText(TempFont,"=",&TemporaryWidth,&TemporaryHeight);}
		else if (i==29)	{TTF_SizeText(TempFont,">",&TemporaryWidth,&TemporaryHeight);}
		else if (i==30)	{TTF_SizeText(TempFont,"?",&TemporaryWidth,&TemporaryHeight);}
		else if (i==31)	{TTF_SizeText(TempFont,"@",&TemporaryWidth,&TemporaryHeight);}
		else if (i==32)	{TTF_SizeText(TempFont,"A",&TemporaryWidth,&TemporaryHeight);}
		else if (i==33)	{TTF_SizeText(TempFont,"B",&TemporaryWidth,&TemporaryHeight);}
		else if (i==34)	{TTF_SizeText(TempFont,"C",&TemporaryWidth,&TemporaryHeight);}
		else if (i==35)	{TTF_SizeText(TempFont,"D",&TemporaryWidth,&TemporaryHeight);}
		else if (i==36)	{TTF_SizeText(TempFont,"E",&TemporaryWidth,&TemporaryHeight);}
		else if (i==37)	{TTF_SizeText(TempFont,"F",&TemporaryWidth,&TemporaryHeight);}
		else if (i==38)	{TTF_SizeText(TempFont,"G",&TemporaryWidth,&TemporaryHeight);}
		else if (i==39)	{TTF_SizeText(TempFont,"H",&TemporaryWidth,&TemporaryHeight);}
		else if (i==40)	{TTF_SizeText(TempFont,"I",&TemporaryWidth,&TemporaryHeight);}
		else if (i==41)	{TTF_SizeText(TempFont,"J",&TemporaryWidth,&TemporaryHeight);}
		else if (i==42)	{TTF_SizeText(TempFont,"K",&TemporaryWidth,&TemporaryHeight);}
		else if (i==43)	{TTF_SizeText(TempFont,"L",&TemporaryWidth,&TemporaryHeight);}
		else if (i==44)	{TTF_SizeText(TempFont,"M",&TemporaryWidth,&TemporaryHeight);}
		else if (i==45)	{TTF_SizeText(TempFont,"N",&TemporaryWidth,&TemporaryHeight);}
		else if (i==46)	{TTF_SizeText(TempFont,"O",&TemporaryWidth,&TemporaryHeight);}
		else if (i==47)	{TTF_SizeText(TempFont,"P",&TemporaryWidth,&TemporaryHeight);}
		else if (i==48)	{TTF_SizeText(TempFont,"Q",&TemporaryWidth,&TemporaryHeight);}
		else if (i==49)	{TTF_SizeText(TempFont,"R",&TemporaryWidth,&TemporaryHeight);}
		else if (i==50)	{TTF_SizeText(TempFont,"S",&TemporaryWidth,&TemporaryHeight);}
		else if (i==51)	{TTF_SizeText(TempFont,"T",&TemporaryWidth,&TemporaryHeight);}
		else if (i==52)	{TTF_SizeText(TempFont,"U",&TemporaryWidth,&TemporaryHeight);}
		else if (i==53)	{TTF_SizeText(TempFont,"V",&TemporaryWidth,&TemporaryHeight);}
		else if (i==54)	{TTF_SizeText(TempFont,"W",&TemporaryWidth,&TemporaryHeight);}
		else if (i==55)	{TTF_SizeText(TempFont,"X",&TemporaryWidth,&TemporaryHeight);}
		else if (i==56)	{TTF_SizeText(TempFont,"Y",&TemporaryWidth,&TemporaryHeight);}
		else if (i==57)	{TTF_SizeText(TempFont,"Z",&TemporaryWidth,&TemporaryHeight);}
		else if (i==58)	{TTF_SizeText(TempFont,"[",&TemporaryWidth,&TemporaryHeight);}
		else if (i==59)	{TTF_SizeText(TempFont,"\\",&TemporaryWidth,&TemporaryHeight);}
		else if (i==60)	{TTF_SizeText(TempFont,"]",&TemporaryWidth,&TemporaryHeight);}
		else if (i==61)	{TTF_SizeText(TempFont,"^",&TemporaryWidth,&TemporaryHeight);}
		else if (i==62)	{TTF_SizeText(TempFont,"_",&TemporaryWidth,&TemporaryHeight);}
		else if (i==63)	{TTF_SizeText(TempFont,"`",&TemporaryWidth,&TemporaryHeight);}
		else if (i==64)	{TTF_SizeText(TempFont,"a",&TemporaryWidth,&TemporaryHeight);}
		else if (i==65)	{TTF_SizeText(TempFont,"b",&TemporaryWidth,&TemporaryHeight);}
		else if (i==66)	{TTF_SizeText(TempFont,"c",&TemporaryWidth,&TemporaryHeight);}
		else if (i==67)	{TTF_SizeText(TempFont,"d",&TemporaryWidth,&TemporaryHeight);}
		else if (i==68)	{TTF_SizeText(TempFont,"e",&TemporaryWidth,&TemporaryHeight);}
		else if (i==69)	{TTF_SizeText(TempFont,"f",&TemporaryWidth,&TemporaryHeight);}
		else if (i==70)	{TTF_SizeText(TempFont,"g",&TemporaryWidth,&TemporaryHeight);}
		else if (i==71)	{TTF_SizeText(TempFont,"h",&TemporaryWidth,&TemporaryHeight);}
		else if (i==72)	{TTF_SizeText(TempFont,"i",&TemporaryWidth,&TemporaryHeight);}
		else if (i==73)	{TTF_SizeText(TempFont,"j",&TemporaryWidth,&TemporaryHeight);}
		else if (i==74)	{TTF_SizeText(TempFont,"k",&TemporaryWidth,&TemporaryHeight);}
		else if (i==75)	{TTF_SizeText(TempFont,"l",&TemporaryWidth,&TemporaryHeight);}
		else if (i==76)	{TTF_SizeText(TempFont,"m",&TemporaryWidth,&TemporaryHeight);}
		else if (i==77)	{TTF_SizeText(TempFont,"n",&TemporaryWidth,&TemporaryHeight);}
		else if (i==78)	{TTF_SizeText(TempFont,"o",&TemporaryWidth,&TemporaryHeight);}
		else if (i==79)	{TTF_SizeText(TempFont,"p",&TemporaryWidth,&TemporaryHeight);}
		else if (i==80)	{TTF_SizeText(TempFont,"q",&TemporaryWidth,&TemporaryHeight);}
		else if (i==81)	{TTF_SizeText(TempFont,"r",&TemporaryWidth,&TemporaryHeight);}
		else if (i==82)	{TTF_SizeText(TempFont,"s",&TemporaryWidth,&TemporaryHeight);}
		else if (i==83)	{TTF_SizeText(TempFont,"t",&TemporaryWidth,&TemporaryHeight);}
		else if (i==84)	{TTF_SizeText(TempFont,"u",&TemporaryWidth,&TemporaryHeight);}
		else if (i==85)	{TTF_SizeText(TempFont,"v",&TemporaryWidth,&TemporaryHeight);}
		else if (i==86)	{TTF_SizeText(TempFont,"w",&TemporaryWidth,&TemporaryHeight);}
		else if (i==87)	{TTF_SizeText(TempFont,"x",&TemporaryWidth,&TemporaryHeight);}
		else if (i==88)	{TTF_SizeText(TempFont,"y",&TemporaryWidth,&TemporaryHeight);}
		else if (i==89)	{TTF_SizeText(TempFont,"z",&TemporaryWidth,&TemporaryHeight);}
		else if (i==90)	{TTF_SizeText(TempFont,"{",&TemporaryWidth,&TemporaryHeight);}
		else if (i==91)	{TTF_SizeText(TempFont,"|",&TemporaryWidth,&TemporaryHeight);}
		else if (i==92)	{TTF_SizeText(TempFont,"}",&TemporaryWidth,&TemporaryHeight);}
		else if (i==93)	{TTF_SizeText(TempFont,"~",&TemporaryWidth,&TemporaryHeight);}
		else			{TTF_SizeText(TempFont,"?",&TemporaryWidth,&TemporaryHeight);}


		if(TemporaryHeight>FinalHeight)
			FinalHeight=TemporaryHeight;
		FinalWidth+=TemporaryWidth;
	}

	TTF_CloseFont(TempFont);


	/*			Creating Final Texture By its Size			*/
	Lang->Texture=SDL_CreateTexture(Main->MainRender,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,FinalWidth,FinalHeight);
	if (Lang->Texture==NULL){
		wprintf(L"\n%c	Error loading texture : %S",0x488,SDL_GetError());
		*error|=0x7;
	}
	//SDL_SetTextureBlendMode(Lang->Texture, SDL_BLENDMODE_BLEND);//This sets the texture in blendmode

	//Uint8 alpha = 0 ;//this section should be where you alter the alpha value. You can make fade in-fade out effects, etc... Just put the changes here.

	//SDL_SetTextureAlphaMod(Lang->Texture, alpha); //sets the alpha into the texture

	//SDL_RenderCopy(Main->MainRender, Lang->Texture, NULL,NULL); //Redraws the image with a fresh, new alpha ~
	/*
	SDL_Surface* TempSurf=SDL_CreateRGBSurface(0,FinalWidth,FinalHeight,32,0xFF000000,0x00FF0000,0x0000FF00,0x000000FF);
	if(TempSurf==NULL){
		wprintf(L"\n%c	Error:%S",0x488,SDL_GetError());
		*(error)=*error|0x7;
	}
	else{
		Lang->Texture=SDL_CreateTextureFromSurface(Main->MainRender,TempSurf);
		if (Lang->Texture==NULL){
			wprintf(L"\n%c	Error loading texture %S: %S",0x488,impath,SDL_GetError());
			*error|=0x7;
		}
	}
	SDL_FreeSurface(TempSurf);

	*/


	SDL_SetRenderTarget(Main->MainRender,Lang->Texture);
	SDL_SetTextureBlendMode(Lang->Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Main->MainRender, 90,0,30, 0);
	SDL_RenderClear(Main->MainRender);

	/*			End Of Section			*/
	int CurrentWidth=0;

	for(unsigned short i=0;i<LangSize;++i){
		SDL_Texture* TemporaryTexture=NULL;
		//Temporary Texture
		if (i==0)		{ TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"!",size,impath,outline,hinting,error);}		
		else if (i==1)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"\"",size,impath,outline,hinting,error);}
		else if (i==2)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"#",size,impath,outline,hinting,error);}
		else if (i==3)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"$",size,impath,outline,hinting,error);}
		else if (i==4)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"%",size,impath,outline,hinting,error);}
		else if (i==5)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"&",size,impath,outline,hinting,error);}
		else if (i==6)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"'",size,impath,outline,hinting,error);}
		else if (i==7)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"(",size,impath,outline,hinting,error);}
		else if (i==8)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,")",size,impath,outline,hinting,error);}
		else if (i==9)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"*",size,impath,outline,hinting,error);}
		else if (i==10)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"+",size,impath,outline,hinting,error);}
		else if (i==11)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,",",size,impath,outline,hinting,error);}
		else if (i==12)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"-",size,impath,outline,hinting,error);}
		else if (i==13)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,".",size,impath,outline,hinting,error);}
		else if (i==14)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"/",size,impath,outline,hinting,error);}
		else if (i==15)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"0",size,impath,outline,hinting,error);}
		else if (i==16)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"1",size,impath,outline,hinting,error);}
		else if (i==17)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"2",size,impath,outline,hinting,error);}
		else if (i==18)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"3",size,impath,outline,hinting,error);}
		else if (i==19)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"4",size,impath,outline,hinting,error);}
		else if (i==20)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"5",size,impath,outline,hinting,error);}
		else if (i==21)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"6",size,impath,outline,hinting,error);}
		else if (i==22)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"7",size,impath,outline,hinting,error);}
		else if (i==23)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"8",size,impath,outline,hinting,error);}
		else if (i==24)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"9",size,impath,outline,hinting,error);}
		else if (i==25)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,":",size,impath,outline,hinting,error);}
		else if (i==26)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,";",size,impath,outline,hinting,error);}
		else if (i==27)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"<",size,impath,outline,hinting,error);}
		else if (i==28)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"=",size,impath,outline,hinting,error);}
		else if (i==29)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,">",size,impath,outline,hinting,error);}
		else if (i==30)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"?",size,impath,outline,hinting,error);}
		else if (i==31)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"@",size,impath,outline,hinting,error);}
		else if (i==32)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"A",size,impath,outline,hinting,error);}
		else if (i==33)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"B",size,impath,outline,hinting,error);}
		else if (i==34)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"C",size,impath,outline,hinting,error);}
		else if (i==35)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"D",size,impath,outline,hinting,error);}
		else if (i==36)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"E",size,impath,outline,hinting,error);}
		else if (i==37)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"F",size,impath,outline,hinting,error);}
		else if (i==38)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"G",size,impath,outline,hinting,error);}
		else if (i==39)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"H",size,impath,outline,hinting,error);}
		else if (i==40)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"I",size,impath,outline,hinting,error);}
		else if (i==41)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"J",size,impath,outline,hinting,error);}
		else if (i==42)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"K",size,impath,outline,hinting,error);}
		else if (i==43)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"L",size,impath,outline,hinting,error);}
		else if (i==44)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"M",size,impath,outline,hinting,error);}
		else if (i==45)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"N",size,impath,outline,hinting,error);}
		else if (i==46)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"O",size,impath,outline,hinting,error);}
		else if (i==47)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"P",size,impath,outline,hinting,error);}
		else if (i==48)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"Q",size,impath,outline,hinting,error);}
		else if (i==49)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"R",size,impath,outline,hinting,error);}
		else if (i==50)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"S",size,impath,outline,hinting,error);}
		else if (i==51)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"T",size,impath,outline,hinting,error);}
		else if (i==52)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"U",size,impath,outline,hinting,error);}
		else if (i==53)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"V",size,impath,outline,hinting,error);}
		else if (i==54)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"W",size,impath,outline,hinting,error);}
		else if (i==55)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"X",size,impath,outline,hinting,error);}
		else if (i==56)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"Y",size,impath,outline,hinting,error);}
		else if (i==57)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"Z",size,impath,outline,hinting,error);}
		else if (i==58)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"[",size,impath,outline,hinting,error);}
		else if (i==59)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"\\",size,impath,outline,hinting,error);}
		else if (i==60)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"]",size,impath,outline,hinting,error);}
		else if (i==61)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"^",size,impath,outline,hinting,error);}
		else if (i==62)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"_",size,impath,outline,hinting,error);}
		else if (i==63)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"`",size,impath,outline,hinting,error);}
		else if (i==64)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"a",size,impath,outline,hinting,error);}
		else if (i==65)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"b",size,impath,outline,hinting,error);}
		else if (i==66)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"c",size,impath,outline,hinting,error);}
		else if (i==67)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"d",size,impath,outline,hinting,error);}
		else if (i==68)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"e",size,impath,outline,hinting,error);}
		else if (i==69)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"f",size,impath,outline,hinting,error);}
		else if (i==70)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"g",size,impath,outline,hinting,error);}
		else if (i==71)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"h",size,impath,outline,hinting,error);}
		else if (i==72)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"i",size,impath,outline,hinting,error);}
		else if (i==73)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"j",size,impath,outline,hinting,error);}
		else if (i==74)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"k",size,impath,outline,hinting,error);}
		else if (i==75)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"l",size,impath,outline,hinting,error);}
		else if (i==76)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"m",size,impath,outline,hinting,error);}
		else if (i==77)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"n",size,impath,outline,hinting,error);}
		else if (i==78)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"o",size,impath,outline,hinting,error);}
		else if (i==79)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"p",size,impath,outline,hinting,error);}
		else if (i==80)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"q",size,impath,outline,hinting,error);}
		else if (i==81)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"r",size,impath,outline,hinting,error);}
		else if (i==82)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"s",size,impath,outline,hinting,error);}
		else if (i==83)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"t",size,impath,outline,hinting,error);}
		else if (i==84)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"u",size,impath,outline,hinting,error);}
		else if (i==85)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"v",size,impath,outline,hinting,error);}
		else if (i==86)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"w",size,impath,outline,hinting,error);}
		else if (i==87)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"x",size,impath,outline,hinting,error);}
		else if (i==88)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"y",size,impath,outline,hinting,error);}
		else if (i==89)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"z",size,impath,outline,hinting,error);}
		else if (i==90)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"{",size,impath,outline,hinting,error);}
		else if (i==91)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"|",size,impath,outline,hinting,error);}
		else if (i==92)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"}",size,impath,outline,hinting,error);}
		else if (i==93)	{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"~",size,impath,outline,hinting,error);}
		else			{TemporaryTexture=CreateTextureFont(Main->MainRender,Color,"?",size,impath,outline,hinting,error);}
		if (TemporaryTexture==NULL){
			wprintf(L"\n%c	Error loading texture : %S",0x488,SDL_GetError());
			*error|=0x7;
		}
		else{
			SDL_QueryTexture(TemporaryTexture,NULL,NULL,&(Lang->SrcRect+i)->w,&(Lang->SrcRect+i)->h);
			(Lang->SrcRect+i)->x=CurrentWidth;
			(Lang->SrcRect+i)->y=0;
			

			SDL_RenderCopy(Main->MainRender,TemporaryTexture,NULL,(Lang->SrcRect+i));

			SDL_DestroyTexture(TemporaryTexture);

			CurrentWidth+=	(Lang->SrcRect+i)->w;
		}
		
	}

	SDL_RenderPresent(Main->MainRender);
	SDL_SetRenderTarget(Main->MainRender,NULL);
}

void CreateLanguageEnglish94(SDL_Renderer* Renderer,SDL_Color* Color,Sprite* SprList,const char* impath,int size,int outline,int hinting,char* error){
	/*
	UTF 8 // ASCII ORDER
	'!' = 33	-> ~ = 126 
	*/
	for (char Character =33;Character<127;++Character){
		CreateNonAnimatedFont(Renderer,Color,SprList+Character-'!',&Character,impath,size,outline,hinting,error);
	}
}