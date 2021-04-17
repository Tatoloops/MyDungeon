/*
Game Version


*/


void DataEncrypter256cV0_001_01(char* EncryptPointer){
	*(EncryptPointer)="CadaPersonaQueVenceEnCualquierEmpresaDebeEstarDispuestaAQuemarSusNavesYEliminarTodasLasPosibilidadesDeDarMarchaAtrasSoloAsiPuedeTenerLaSeguridadDeMantenerEseEstadoMentalConocidoComoDeseoArdienteDeGanarEsencialParaElExitoLaMananaSiguienteAlGranIncendioDeChi";
	return;
}

void InitializeString(char* string,int size){
	for(int i=0;i<size;i++)
		string[i]='/0';

	return;
}

void GameSetVersion(GameVersion* SetVersionToMe,unsigned char* ver){

	SetVersionToMe->GameVersion[0]=ver[0];
	SetVersionToMe->GameVersion[1]=ver[1];
	SetVersionToMe->GameVersion[2]=ver[2];
	SetVersionToMe->GameVersion[3]=ver[3];
	SetVersionToMe->GameVersion[4]=ver[4];
	SetVersionToMe->GameVersion[5]=ver[5];
	SetVersionToMe->GameVersion[6]=ver[6];
	SetVersionToMe->GameVersion[7]=ver[7];
	SetVersionToMe->GameVersion[8]=ver[8];
	SetVersionToMe->GameVersion[9]=ver[9];
	SetVersionToMe->GameVersion[10]=ver[10];
	SetVersionToMe->GameVersion[11]='\0';

	SetVersionToMe->GameModel[0]=ver[0];
	SetVersionToMe->GameModel[1]=ver[1];
	SetVersionToMe->GameModel[2]=ver[2];
	SetVersionToMe->GameModel[3]='\0';

	SetVersionToMe->GameMajorUpdate[0]=ver[4];
	SetVersionToMe->GameMajorUpdate[1]=ver[5];
	SetVersionToMe->GameMajorUpdate[2]=ver[6];
	SetVersionToMe->GameMajorUpdate[3]='\0';

	SetVersionToMe->GameRevision[0]=ver[8];
	SetVersionToMe->GameRevision[1]=ver[9];
	SetVersionToMe->GameRevision[2]=ver[10];
	SetVersionToMe->GameRevision[3]='\0';

	return;
}

/*			File Handler Functions			*/

void GameSetVersionInFile(GameVersion* SetVersionToMe,FILE* Savedata){
	unsigned short BufferRead[30];

	
	//Adding version to the buffer
	for (unsigned short i=0;i<9;++i)
		BufferRead[3+i]	=27*i+386-i*13;
	for (unsigned short i=0;i<9;++i)
		BufferRead[12+i]=(BufferRead[3+i]/2)*3;

	for (unsigned short i=0;i<3;++i)
		BufferRead[21+i*3]=BufferRead[12+i*3]-BufferRead[3+i*3]-(SetVersionToMe->GameModel[i]);
	for (unsigned short i=0;i<3;++i)
		BufferRead[22+i*3]=BufferRead[13+i*3]-BufferRead[4+i*3]-(SetVersionToMe->GameMajorUpdate[i]);
	for (unsigned short i=0;i<3;++i)
		BufferRead[23+i*3]=BufferRead[14+i*3]-BufferRead[5+i*3]-(SetVersionToMe->GameRevision[i]);


	//Add Encrypt Seal
	BufferRead[0]=12243;
	BufferRead[1]=8495;
	BufferRead[2]=11478;
	unsigned short EncryptMainSeal=BufferRead[0]+BufferRead[1]+BufferRead[2];
	
	for (unsigned short i=3;i<30;++i)
		BufferRead[i]+=EncryptMainSeal;
	fwrite(BufferRead, sizeof(unsigned short), 30, Savedata);
	//return;
}
void GameGetVersionFromFile(GlobalVariables* Main,GameVersion* SetVersionToMe){
	unsigned short BufferRead[30];
	fread(BufferRead,sizeof(unsigned short),30,Main->Savedata);
	//fgets(BufferRead,30,Main->Savedata);
	unsigned short EncryptMainSeal=BufferRead[0]+BufferRead[1]+BufferRead[2];

	//Remove Main Seal
	for (unsigned short i=3;i<30;++i)
		BufferRead[i]-=EncryptMainSeal;

	SetVersionToMe->GameModel[0]		=BufferRead[12]-BufferRead[21]-BufferRead[3];
	SetVersionToMe->GameModel[1]		=BufferRead[15]-BufferRead[24]-BufferRead[6];
	SetVersionToMe->GameModel[2]		=BufferRead[18]-BufferRead[27]-BufferRead[9];
	SetVersionToMe->GameModel[3]		='\0';

	SetVersionToMe->GameMajorUpdate[0]	=BufferRead[13]-BufferRead[22]-BufferRead[4];
	SetVersionToMe->GameMajorUpdate[1]	=BufferRead[16]-BufferRead[25]-BufferRead[7];
	SetVersionToMe->GameMajorUpdate[2]	=BufferRead[19]-BufferRead[28]-BufferRead[10];
	SetVersionToMe->GameMajorUpdate[3]	='\0';

	SetVersionToMe->GameRevision[0]		=BufferRead[14]-BufferRead[23]-BufferRead[5];
	SetVersionToMe->GameRevision[1]		=BufferRead[17]-BufferRead[26]-BufferRead[8];
	SetVersionToMe->GameRevision[2]		=BufferRead[20]-BufferRead[29]-BufferRead[11];
	SetVersionToMe->GameRevision[3]		='\0';

	SetVersionToMe->GameVersion[0]	=SetVersionToMe->GameModel[0];
	SetVersionToMe->GameVersion[1]	=SetVersionToMe->GameModel[1];
	SetVersionToMe->GameVersion[2]	=SetVersionToMe->GameModel[2];
	SetVersionToMe->GameVersion[3]	='.';
	SetVersionToMe->GameVersion[4]	=SetVersionToMe->GameMajorUpdate[0];
	SetVersionToMe->GameVersion[5]	=SetVersionToMe->GameMajorUpdate[1];
	SetVersionToMe->GameVersion[6]	=SetVersionToMe->GameMajorUpdate[2];
	SetVersionToMe->GameVersion[7]	='.';
	SetVersionToMe->GameVersion[8]	=SetVersionToMe->GameRevision[0];
	SetVersionToMe->GameVersion[9]	=SetVersionToMe->GameRevision[1];
	SetVersionToMe->GameVersion[10]	=SetVersionToMe->GameRevision[2];
	SetVersionToMe->GameVersion[11]	='\0';
	//return;
}
/*			End of File Handlers			*/

/*			verifying Game Version			*/
char VerifyingVersion(GameVersion* SetVersionToMe){
	unsigned short NumberOfVersions = 3;
	char corruption=0;
	/*
	0000 0010:	Matching Version Found!
	*/
	unsigned char ApprovedVersion[NumberOfVersions][12];

	strcpy(ApprovedVersion[0],"000.001.001\0");
	strcpy(ApprovedVersion[1],"000.001.001\0");
	strcpy(ApprovedVersion[2],"000.001.003\0");

	for (unsigned short i=0;i<NumberOfVersions;++i)
		if (strcmp(ApprovedVersion[i],SetVersionToMe->GameVersion)== 0)
			corruption|=0x2;

	return corruption;
}

/*			End				*/

/*			Main			*/
void GameVersionMain(GlobalVariables* Main){
	unsigned char Version[12];
	strcpy(Version,"000.001.001\0");
	//wprintf(L"Current Game Version asdasd: %s\n",Version);
	GameSetVersion(&Main->GameVersionCurrent,Version);
	//wprintf(L"Current Game Version: %s\n",Main->GameVersionCurrent.GameVersion);
	/*		Loading or Creating new Savedata	*/
	//wprintf(L"a\n");
	Main->Savedata = fopen (Main->SavedataName, "r");
	//wprintf(L"b\n");
	if (Main->Savedata ==NULL){//Create New Savedata
		fclose(Main->Savedata);

		wprintf(L"\n%c	No Savedata found! Creating new Savedata...",0x466);
		GameSetVersion(&Main->GameVersionData,Version);

		//Opening File
		Main->Savedata =fopen (Main->SavedataName, "w");
		//Working in the File, setting the Version of the game
		GameSetVersionInFile(&Main->GameVersionData,Main->Savedata);
		//Closing File
		fclose(Main->Savedata);

	}
	else{//Savedata Found!
		//Getting previous game version.
		GameGetVersionFromFile(Main,&Main->GameVersionData);
		fclose(Main->Savedata);

		char corruption=VerifyingVersion(&Main->GameVersionData);
		if (corruption&0x2){	//Matching Savedata
			wprintf(L"\n%c	Savedata Found!",0x466);
			wprintf(L"\n%c	Savedata Version: ",0x466);
			wprintf(L"%S",Main->GameVersionData.GameVersion);
		}
		else{					//Corrupted Savedata
			Main->Savedata =fopen (Main->SavedataName, "w");
			GameSetVersion(&Main->GameVersionData,Version);
			GameSetVersionInFile(&Main->GameVersionData,Main->Savedata);
			fclose(Main->Savedata);
			wprintf(L"\n%c	Savedata Corrupted, New Savedata Created.",0x466);

			
		}
	}


	/*		Printing Results		*/
	wprintf(L"\n%c	Current Game Version: ",0x466);
	wprintf(L"%S",Main->GameVersionCurrent.GameVersion);
	
	return;
}

