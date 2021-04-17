void SaveFileDataV0x001x01(GlobalVariables* Main,int slot){
	/*
	Infinite Slot Sistem
	Slots from 1 to infinity
	Use 0 If new slot
	*/
	char EncryptionFullCode[256];
	DataEncrypter256cV0_001_01(EncryptionFullCode);
	Main->Savedata=fopen(Main->SavedataName, "r+");
}
void LoadFileDataV0x001x01(GlobalVariables* Main,int slot){
	
	char EncryptionFullCode[256];
	DataEncrypter256cV0_001_01(EncryptionFullCode);
	Main->Savedata=fopen(Main->SavedataName, "r");
}