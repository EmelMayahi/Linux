#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
struct namefile{
	char name[20];
	char path[30];
};
struct namefile names[200];
void main(){
	sleep(10);
	FILE *myfile;
	FILE *in;
	char buff[20];
	int len;
	char buff1[10];
	
	myfile = fopen("myfile.text","w");
	if(!myfile){
		printf("Cannot Open File \n");
		exit(1);
	}
	char str[]="ProcessID - ProcessEXEName - ProcessState - ParentID - GroupID - SessionID\n";
	fputs(str,myfile);

	in = fopen("procfile.text","r");
	if(!in){
		printf("Cannot Open Directory \n");
		exit(1);
	}
	
	int i=0;		
	while(!feof(in)){ 
		fscanf(in,"%s",buff);
		strcpy(names[i].name,buff);
		//printf("%d) %s\n",i,names[i].name);
		++i; 
	}
	
	len=i;
	for(int i=0; i<len ; i++){
		char str1[30];
		strcpy(str1,"/proc/");
		strcat(str1,names[i].name);
		strcat(str1,"/stat");
		strcpy(names[i].path,str1);
		//printf("path: %s\n",names[i].path);
			
	}
	fclose(in);
		
	
	for(int i=0; i<60 ;i++){
		FILE *fp;
		//printf("%s\n",names[i].path);
		fp = fopen(names[i].path,"r");

		fscanf(fp,"%s",buff1); //pid
		strcat(buff1,"\t\t");
		fprintf(myfile,buff1);

		fscanf(fp,"%s",buff1); //NameEXX
		strcat(buff1,"\t");
		fprintf(myfile,buff1);

		fscanf(fp,"%s",buff1); //status
		strcat(buff1,"\t");
		fprintf(myfile,buff1);

		fscanf(fp,"%s",buff1); //PPid
		strcat(buff1,"\t");
		fprintf(myfile,buff1);

		fscanf(fp,"%s",buff1); //GroupID
		strcat(buff1,"\t");
		fprintf(myfile,buff1);

		fscanf(fp,"%s",buff1); //SetionID
		strcat(buff1,"\n");
		fprintf(myfile,buff1);
		fclose(fp);
		
	}

	sleep(20);
	char str1[30];
	//information about my_file
	in = fopen("psfile.text","r");
	fscanf(in,"%s",buff1);
	strcpy(str1,"/proc/");
	strcat(str1,buff1);
	strcat(str1,"/stat");
	fclose(in);

	FILE *f;
	f = fopen(str1,"r");
	fprintf(myfile,"\n***information my_file***\n");

	fscanf(f,"%s",buff1); //pid
	strcat(buff1,"\t\t");
	fprintf(myfile,buff1);

	fscanf(f,"%s",buff1); //NameEXX
	strcat(buff1,"\t");
	fprintf(myfile,buff1);

	fscanf(f,"%s",buff1); //status
	strcat(buff1,"\t");
	fprintf(myfile,buff1);

	fscanf(f,"%s",buff1); //PPid
	strcat(buff1,"\t");
	fprintf(myfile,buff1);

	fscanf(f,"%s",buff1); //GroupID
	strcat(buff1,"\t");
	fprintf(myfile,buff1);

	fscanf(f,"%s",buff1); //SetionID
	strcat(buff1,"\n");
	fprintf(myfile,buff1);
	fclose(f);	
			
	fclose(myfile);
	
}
