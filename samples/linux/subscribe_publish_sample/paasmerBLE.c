#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char BLEip[][17] = {""};
int BLEcount = 0;
int BLEstatus[] = {};
extern void add(char *feednames,char *feedtypes,char *connectiontypes,int feedpins);

void DiscoverBlue(){
	FILE *fp;
	char data[150]; 
	const char s[2] = " ";
	char *token;
	fp = popen("sh PaasmerDiscoverBlue.sh LEDBlue","r");
        if (fp==NULL){
                //printf("fp not there\n");
        }
        while(fgets(data,sizeof(data)-1,fp)!=NULL){
                printf("%s\n",data);
        }
        data[strlen(data)-1] = '\0';
        fclose(fp);
	if(strlen(data) != 0){
	token = strtok(data, s);
	while(token != NULL){
		int i = 0,find = 0;
		for(i=0;i<BLEcount;i++){
			if(!(strcmp(BLEip[i],token))){
				find = 1;
				break;
			}
		}
		if(find == 0){
			sprintf(BLEip[BLEcount],"%s",token);
			BLEstatus[BLEcount++] = 0;
			char BLEname[] = "magicblue";
			sprintf(BLEname,"magicblue%d",BLEcount);
			add(BLEname,"actuator","BLE",BLEcount);
		}
		else if(find == 1)
			printf("The BLE Bulb already Exists in Your Device\n");
		token = strtok(NULL, s);
	}
	}
	int i=0;
	/*for(i=0;i<BLEcount;i++){
	printf("the BLEip[%d] is %s\n",i,BLEip[i]);
	}*/
}
void WriteBlue(int number, char *state){
	char command[100];
	printf("The Magic Blue's MAC ID is %s\n",BLEip[number - 1]);
	if(!(strcmp(state,"on"))){
		printf("BLE Bulb ON\n");
		sprintf(command,"python paasmerBLE.py %s %s",BLEip[number - 1],state);
		system(command);
		BLEstatus[number - 1] = 1;
	}
	else{
		printf("BLE Bulb OFF\n");
                sprintf(command,"python paasmerBLE.py %s %s",BLEip[number - 1],state);
                system(command);
                BLEstatus[number - 1] = 0;
	}
}
int ReadBlue(int number){
	printf("The Bulb's status is %d\n",BLEstatus[number - 1]);
	return BLEstatus[number - 1];
}
