#include "Version.h"
#include "Savedata/V0.001.h"


void SaveSlot(Save* save_data,int slot){
	short i;
	short j;
	for (i=0;i<20;++i){
	(save_data+slot)->name[i]=(save_data)->name[i];
	}
	(save_data+slot)->race=(save_data->race);
	(save_data+slot)->CharacterClass=(save_data->CharacterClass);
	(save_data+slot)->lvl=(save_data->lvl);
	(save_data+slot)->exp=(save_data->exp);
	(save_data+slot)->gold=(save_data->gold);

	(save_data+slot)->maxhp=(save_data->maxhp);
	(save_data+slot)->maxenergy=(save_data->maxenergy);
	(save_data+slot)->hp=(save_data->hp);
	(save_data+slot)->def=(save_data->def);
	(save_data+slot)->atk=(save_data->atk);
	(save_data+slot)->atkspec=(save_data->atkspec);
	(save_data+slot)->energy=(save_data->energy);
	(save_data+slot)->movspeed=(save_data->movspeed);
	(save_data+slot)->atkspeed=(save_data->atkspeed);
	for (i=0;i<20;++i){
		(save_data+slot)->inv[i]=(save_data)->inv[i];
	}

	FILE * save;
	if ((save = fopen("save.dat", "w")) == NULL ){
        wprintf(L"File could not be opened.\n");
    }
 	else{
 		for(i=1;i<7;++i){
 			fprintf(save, "%s\n",(save_data+i)->name);
 			fprintf(save, "%d\n",(save_data+i)->race);
 			fprintf(save, "%d\n",(save_data+i)->CharacterClass);
 			fprintf(save, "%d\n",(save_data+i)->lvl);
 			fprintf(save, "%d\n",(save_data+i)->exp);
 			fprintf(save, "%d\n",(save_data+i)->gold);
 			fprintf(save, "%d\n",(save_data+i)->maxhp);
 			fprintf(save, "%d\n",(save_data+i)->maxenergy);
 			fprintf(save, "%d\n",(save_data+i)->hp);
 			fprintf(save, "%d\n",(save_data+i)->def);
 			fprintf(save, "%d\n",(save_data+i)->atk);
 			fprintf(save, "%d\n",(save_data+i)->atkspec);
 			fprintf(save, "%d\n",(save_data+i)->energy);
 			fprintf(save, "%f\n",(save_data+i)->movspeed);
 			fprintf(save, "%f\n",(save_data+i)->atkspeed);
 			for (j=0;j<20;++j){
				fprintf(save, "%d ",(save_data+i)->inv[j]);
			}
 		}
 	}
}

void LoadSlot(Save* save_data,int slot){
	short i;
	(save_data->race)=(save_data+slot)->race;
	(save_data->CharacterClass)=(save_data+slot)->CharacterClass;
	(save_data->lvl)=(save_data+slot)->lvl;
	(save_data->exp)=(save_data+slot)->exp;
	(save_data->gold)=(save_data+slot)->gold;
	(save_data->maxhp)=(save_data+slot)->maxhp;
	(save_data->maxenergy)=(save_data+slot)->maxenergy;
	(save_data->hp)=(save_data+slot)->hp;
	(save_data->def)=(save_data+slot)->def;
	(save_data->atk)=(save_data+slot)->atk;
	(save_data->atkspec)=(save_data+slot)->atkspec;
	(save_data->energy)=(save_data+slot)->energy;
	(save_data->movspeed)=(save_data+slot)->movspeed;
	(save_data->atkspeed)=(save_data+slot)->atkspeed;
	(save_data->race)=(save_data+slot)->race;
	for (i=0;i<20;++i){
		(save_data)->inv[i]=(save_data+slot)->inv[i];
	}
}
void CreateCharacter(Save* saved_data,int CharacterClass,int race){

	//race  1: human 2:Rabbitman 3:dwarf
	//CharacterClass 1: warrior 2:archer 3:mage

	short i;
	//
	saved_data->lvl=1;
	saved_data->exp=0;
	saved_data->gold=50;
	saved_data->CharacterClass=CharacterClass;
	saved_data->race=race;

	for(i=0;i<20;++i)
		saved_data->inv[i]=0;
	//stats por raza
	if (race==1){		//HUMAN
		if (CharacterClass==1){ //warrior
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=10;
			saved_data->atkspec=12;

			saved_data->movspeed=1.5;
			saved_data->atkspeed=35;
		}
		else if (CharacterClass==2){ //archer
			saved_data->maxhp=17;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=1;
			saved_data->atk=3;
			saved_data->atkspec=10;

			saved_data->movspeed=2; saved_data->atkspeed=35;
		}
		else if (CharacterClass==3){ //mage
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=8;
			saved_data->atkspec=16;

			saved_data->movspeed=1.5;
			saved_data->atkspeed=35;
		}
	}
	else if (race==2){	//Rabbitman
		if (CharacterClass==1){ //warrior
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
		else if (CharacterClass==2){ //archer
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
		else if (CharacterClass==3){ //mage
			saved_data->maxhp=20;
			saved_data->maxenergy=20;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=0;
			saved_data->atk=10;
			saved_data->atkspec=18;

			saved_data->movspeed=2.0;
			saved_data->atkspeed=30;
		}
	}
	else if (race==3){	//dwarf
		if (CharacterClass==1){ //warrior
			saved_data->maxhp=35;
			saved_data->maxenergy=8;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=3;
			saved_data->atk=15;
			saved_data->atkspec=20;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
		else if (CharacterClass==2){ //archer
			saved_data->maxhp=22;
			saved_data->maxenergy=8;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=10;
			saved_data->atkspec=14;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
		else if (CharacterClass==3){ //mage
			saved_data->maxhp=25;
			saved_data->maxenergy=12;

			saved_data->hp=saved_data->maxhp;
			saved_data->energy=saved_data->maxenergy;

			saved_data->def=2;
			saved_data->atk=12;
			saved_data->atkspec=22;

			saved_data->movspeed=1.2;
			saved_data->atkspeed=40;
		}
	}
}
void levelup(Save* saved_data){
	if (saved_data->race==1){
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=3;
		saved_data->maxenergy+=2;
		saved_data->def+=1;
		saved_data->atk+=1;
		saved_data->atkspec+=2;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.05;
		saved_data->atkspeed-=2;
	}
	else if (saved_data->race==2){
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=1;
		saved_data->maxenergy+=1;
		saved_data->def+=0;
		saved_data->atk+=1;
		saved_data->atkspec+=1;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.25;
		saved_data->atkspeed-=3;
	}
	else{
		saved_data->exp-=100;
		saved_data->lvl+=1;
		saved_data->maxhp+=5;
		saved_data->maxenergy+=5;
		saved_data->def+=1;
		saved_data->atk+=3;
		saved_data->atkspec+=2;
		saved_data->hp=saved_data->maxhp;
		saved_data->movspeed+=0.02;
		saved_data->atkspeed-=1;
	}
	wprintf(L"level up, new stats:\n Level:%d \n HP: %d \n Energy: %d \n  Defense: %d \n Atack: %d \n  Movement speed: %f \n Atack speed: %f \n",
		saved_data->lvl,
		saved_data->maxhp,
		saved_data->maxenergy,
		saved_data->def,
		saved_data->atk,
		saved_data->movspeed,
		saved_data->atkspeed);
	wprintf(L"%d\n",saved_data->inv[0]);
}
// presion de las "key"
void keypressed(char* key){
	const Uint8*currentstate=SDL_GetKeyboardState(NULL);
	if(currentstate[SDL_SCANCODE_UP]) //key is being pressed
			if (key[0]&0x4) key[0]=0x4; // 0100 //Still pressed
			else 			key[0]=0x5;	// 0101 //just pressed
	else 	if (key[0]&0x4)	key[0]=0xA;	// 1010 //was being pressed-> just released
			else 			key[0]=0x8; // 1000 //Still released
	if(currentstate[SDL_SCANCODE_DOWN])//0x9
			if (key[1]&0x4) key[1]=0x4;
			else 			key[1]=0x5;
	else 	if (key[1]&0x4)	key[1]=0xA;
			else 			key[1]=0x8;
	if(currentstate[SDL_SCANCODE_LEFT])
			if (key[2]&0x4) key[2]=0x4;
			else 			key[2]=0x5;
	else 	if (key[2]&0x4)	key[2]=0xA;
			else 			key[2]=0x8;
	if(currentstate[SDL_SCANCODE_RIGHT])
			if (key[3]&0x4) key[3]=0x4;
			else 			key[3]=0x5;
	else 	if (key[3]&0x4)	key[3]=0xA;
			else 			key[3]=0x8;
	if(currentstate[SDL_SCANCODE_Z])
			if (key[4]&0x4) key[4]=0x4;
			else 			key[4]=0x5;
	else 	if (key[4]&0x4)	key[4]=0xA;
			else 			key[4]=0x8;
	if(currentstate[SDL_SCANCODE_X])
			if (key[5]&0x4) key[5]=0x4;
			else 			key[5]=0x5;
	else 	if (key[5]&0x4)	key[5]=0xA;
			else 			key[5]=0x8;
	if(currentstate[SDL_SCANCODE_C])
			if (key[6]&0x4) key[6]=0x4;
			else 			key[6]=0x5;
	else 	if (key[6]&0x4)	key[6]=0xA;
			else 			key[6]=0x8;
	if(currentstate[SDL_SCANCODE_A])
			if (key[7]&0x4) key[7]=0x4;
			else 			key[7]=0x5;
	else 	if (key[7]&0x4)	key[7]=0xA;
			else 			key[7]=0x8;
	if(currentstate[SDL_SCANCODE_S])
			if (key[8]&0x4) key[8]=0x4;
			else 			key[8]=0x5;
	else 	if (key[8]&0x4)	key[8]=0xA;
			else 			key[8]=0x8;
	if(currentstate[SDL_SCANCODE_I])
			if (key[9]&0x4) key[9]=0x4;
			else 			key[9]=0x5;
	else 	if (key[9]&0x4)	key[9]=0xA;
			else 			key[9]=0x8;
	if(currentstate[SDL_SCANCODE_SPACE])
			if (key[10]&0x4)key[10]=0x4;
			else 			key[10]=0x5;
	else 	if (key[10]&0x4)key[10]=0xA;
			else 			key[10]=0x8;
	if(currentstate[SDL_SCANCODE_RETURN])
			if (key[11]&0x4)key[11]=0x4;
			else 			key[11]=0x5;
	else 	if (key[11]&0x4)key[11]=0xA;
			else 			key[11]=0x8;
	if(currentstate[SDL_SCANCODE_ESCAPE])
			if (key[12]&0x4)key[12]=0x4;
			else 			key[12]=0x5;
	else 	if (key[12]&0x4)key[12]=0xA;
			else 			key[12]=0x8;
	if(currentstate[SDL_SCANCODE_P])
			if (key[13]&0x4)key[13]=0x4;
			else 			key[13]=0x5;
	else 	if (key[13]&0x4)key[13]=0xA;
			else 			key[13]=0x8;
}
void keycompare(char* key1, char* key2){ //key1 your frame key key2 your bullshit key
	short i;
	for(i=0;i<KeyNumber;++i){
		if (!(key1[i] & key2[i])){
			if (key1[i]&8 && key2[i]&4) //key got pressed
				key1[i]=5;
			else key1[i]=0xA;
		}
		else if(key1[i]&8) key1[i]=8;
			else key1[i]=4;
	}
}
