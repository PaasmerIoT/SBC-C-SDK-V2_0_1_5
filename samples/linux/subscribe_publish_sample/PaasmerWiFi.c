#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <jsmn.h>
int BelkinCount=0;
char BelkinIP[][16] = {""};
int philips_ID[]={};
int philipsBulbNumber = 0,check=0;

extern void feedadd();
extern void print();
extern void add(char *feednames,char *feedtypes,char *connectiontypes,int feedpins);
void Philips_feed();

void getBelkinIP(){
	FILE *p;
	char data[150]={};
	const char s[2] = "/";
	const char s1[2]=":";
	char* word[51] = {};
	char* word1[51] = {};
	char *token;
	int wordcount = 0,wordcount1 = 0;
	char command[100] = "gssdp-discover -t urn:Belkin:device:1 -n 3 -i wlan0 | grep  \"Location\"";
        p = popen(command,"r");
        if (p==NULL){
                printf("fp not der\n");
        }
        while (fgets(data,sizeof(data)-1,p)!=NULL){
                printf("%s\n",data);
        }
	if(data){
        data[strlen(data)-1] = '\0';
        fclose(p);
	/* get the first token */
	if(strlen(data) != 0){
	token = strtok(data, s);
	/* walk through other tokens */
	while( token != NULL ) {
		word[wordcount++] = token;
		token = strtok(NULL, s);
	}
	if(strlen(word[1]) != 0){
	token = strtok(word[1], s1);
	while( token != NULL ) {
		word1[wordcount1++] = token;
		token = strtok(NULL, s);
	}
	int i = 0,find = 0;
	for(i=0;i<BelkinCount;i++){
		if(!(strcmp(BelkinIP[i],word1[0]))){
			find = 1;
			break;
		}
	}
	if(find == 0){
			sprintf(BelkinIP[BelkinCount++],"%s",word1[0]);
                        char BelkinName[] = "Belkin";
                        sprintf(BelkinName,"Belkin%d",BelkinCount);
                        add(BelkinName,"actuator","Wifi",BelkinCount);
                }
                else if(find == 1)
                        printf("The Belkin is Already Added to your Device\n");
	}}
        }
	}



void Belkin_Write(int belkinNumber,char* message){
char command[100];
        snprintf(command,sizeof(command),"sudo timeout 2s wemo -h %s -a %s",BelkinIP[belkinNumber - 1],message);
        printf("\nBelkin %s\n",message);
        system(command);
        strcpy(command,"\0");
}

int Belkin_Read(int belkinNumber,char* IP){
char command[100];
int i=0,j=0;
        FILE *fp;
        char data[150]={},a[150]={};
        snprintf(command,sizeof(command),"sudo timeout 2s wemo -h %s -a GETSTATE",IP);
        fp = popen(command,"r");
        if (fp==NULL){
                printf("fp not der\n");
        }
        while (fgets(data,sizeof(data)-1,fp)!=NULL){
                printf("The data is %s",data);
        }
	if(data){
        strcpy(a,data);
        fclose(fp);
        for (i=0;j<sizeof(a);i++){
                if(a[i]=='8')
                        return 1;
                else
                        return 0;
        }
	}
	else 
		return 0;
}
//************************ End of Belkin Functions ***************

// *********************** Philips *******************************

const char* getPhilipsIP(){
        FILE *fp;

        char data[150],a[150];
        char ip[16],ip_philips[16];
        char command[100] = "gssdp-discover -t urn:schemas-upnp-org:device:basic:1 -n 3 -i wlan0 | grep \"Location\"";
        fp = popen(command,"r");
        if (fp==NULL){
                //printf("fp not der\n");
        }
        while (fgets(data,sizeof(data)-1,fp)!=NULL){
                printf("Get Philips IP data is %s",data);
        }
        strcpy(a,data);
        fclose(fp);

        int i=0,j=0;
        while(a[i]){
                if(a[i]>='0' && a[i]<= '9'|| a[i]=='.' ){
                        if(j<15){
                                ip[j] = a[i];
                                printf("%c",ip[j]);
                                j++;
                        }
                        else{
                                break;
                }
                }
                i++;
        }
        return ip;
}

int Philips_config(){
        char philips_ip[15], command[100] = "gssdp-discover -t urn:schemas-upnp-org:device:basic:1 -n 3 -i wlan0 | grep \"Location\"";
        char data[150],reg[200];
        FILE *fp = popen(command,"r");
        if (fp==NULL){
               // printf("fp not der\n");
        }
         while (fgets(data,sizeof(data)-1,fp)!=NULL){
                printf("%s\n",data);
        }
	if(check==0){
        if (data){
                strcpy(philips_ip,getPhilipsIP());
                printf("Philip IP is %s\n",philips_ip);
                if (philips_ip){
                        snprintf(reg,sizeof(reg),"hue -H %s register",philips_ip);
                        system(reg);
			check=1;
			return 1;
                }
        }
	}
}

void Philips_Write(int pin,char* message){
	char data[20]={};
	sprintf(data,"hue lights %d %s",pin,message);
	system(data);
}

int Philips_read(int message){
	FILE *fp;
	char command[20]={},data[100]={},a[100]={};
	sprintf(command,"hue lights %d",message);
	fp = popen(command,"r");
	if(fp == NULL){
		printf("No Bulbs are Connected to the Bridge\n");
	}
	while(fgets(data,sizeof(data)-1,fp)!=NULL){
		//printf("The value id %s\n",data);
	}
	strcpy(a,data);
	fclose(fp);
	if(strstr(a,"on")){
		return 1;
	}
	else{
		return 0;
	}
}
	
// ******************** WiFi set And Discovery ****************

int wifi_setup(){
        system("sudo ./discover.sh");
        char data[150],a[150],BelkinIP[16];
        char command[100] = "gssdp-discover -t urn:schemas-upnp-org:device:basic:1 -n 3 -i wlan0 | grep \"Location\"";
        FILE *fp = popen(command,"r");
                if (fp==NULL){
                        printf("fp not der\n");
                 }
                while (fgets(data,sizeof(data)-1,fp)!=NULL){
                        printf("%s\n",data);
                 }
                strcpy(a,data);
                fclose(fp);
        if (strlen(a) != 0){
                int value = Philips_config();
		strcpy(command,"\0");
                return value;
        }
	else{
		printf("There is No Philips Connected to Your Network..");
		return 0;
	}
}

void DiscoverWifi(){
        int status= wifi_setup();
        const char a[50]="\0";
	char data[150],b[][10]={""};
        char command[20] = "hue lights";
        int i=0;
	if (status == 1){
                FILE *fp = popen(command,"r"),*File;
                if (fp==NULL){
                        //printf("fp not der\n");
                 }

		system("sudo rm hari.txt");
                while (fgets(data,sizeof(data)-1,fp)!=NULL){

			File=fopen("hari.txt","a+");
			fprintf(File,"%s",data);
			fclose(File);
                 }
                fclose(fp);
				
		Philips_feed();
        }
        getBelkinIP();
}

void Philips_feed(){	
	int i=0;
	char string[][10]={};
	char line[100];
	char data[10];
	FILE *fp;
	fp = fopen("hari.txt","r");
	if(fp == NULL)
		printf("Philips not present\n");
	else{
		int find=0;
		while(fgets(line,sizeof(line),fp) != NULL){
			sprintf(data,"philips%c",line[3]);
			for(i=0;i<philipsBulbNumber;i++)
			{
				if(philips_ID[i] ==(int)(line[3]-'0'))
				{
					find = 1;
					break;
				}
			}
			if(find==0)
			{
				add(data,"actuator","Wifi",(int)(line[3]-'0'));
				philips_ID[philipsBulbNumber] = (int)(line[3]-'0');
				philipsBulbNumber++;
			}
				
			else
				printf(" The Bulb already exists in the Database\n");
			
		}
	
	}
	fclose(fp);
}
void WifiWrite(char* feedname, int feedpin, char* state){
        char feed[20];
        if(strstr(feedname,"philips")){
                if (!strcmp(state,"ON")){
                        Philips_Write(feedpin,"on");
                }
		if (!strcmp(state,"OFF")){
                        Philips_Write(feedpin,"off");
                }

        }
        else if(strstr(feedname,"Belkin")){
                Belkin_Write(feedpin,state);
        }
}

int WifiRead(char* feedname,int feedpin){
	int i=0;
	for(i=0;i<BelkinCount;i++){
        }
	int data;
	if (strstr(feedname,"philips")){
		data=Philips_read(feedpin);
		return data;	
	}
	else if (strstr(feedname,"Belkin")){
		data = Belkin_Read(feedpin,BelkinIP[feedpin-1]);
		return data;
	}
}

