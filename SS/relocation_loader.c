#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
	FILE *obj;
	int i, j, start, saddr2, cadr2;
	char line[100], name[10], name2[10], saddr[10], mask[15], code[10], cadr[10];
	printf("Enter the program name:");
	scanf("%s", name);
	obj=fopen("objWithModBits.txt", "r");
	fscanf(obj, "%s", line);
	for (i=0, j=2; i<6; i++, j++)
		name2[i]=line[j];
	name2[i]='\0';
	if (strcmp(name, name2)==0){
		printf("Enter the starting address:");
		scanf("%x", &start);
		do{
			fscanf(obj, "%s", line);
			if (line[0]=='T'){
				for(i=2,j=0;i<8,j<6;i++,j++)
					saddr[j]=line[i];
				saddr[j]='\0';
				saddr2=(int)strtol(saddr, NULL, 16)+start;
				mask[0]='\0';
				for (i=12; i<15; i++){
					switch(line[i]){
						case '0':
							strcat(mask, "0000");
							break;
						case '1':
							strcat(mask, "0001");
							break;
						case '2':
							strcat(mask, "0010");
							break;
						case '3':
							strcat(mask, "0011");
							break;
						case '4':
							strcat(mask, "0100");
							break;
						case '5':
							strcat(mask, "0101");
							break;
						case '6':
							strcat(mask, "0110");
							break;
						case '7':
							strcat(mask, "0111");
							break;
						case '8':
							strcat(mask, "1000");
							break;
						case '9':
							strcat(mask, "1001");
							break;
						case 'a':
							strcat(mask, "1010");
							break;
						case 'b':
							strcat(mask, "1011");
							break;
						case 'c':
							strcat(mask, "1100");
							break;
						case 'd':
							strcat(mask, "1101");
							break;
						case 'e':
							strcat(mask, "1110");
							break;
						case 'f':
							strcat(mask, "1111");
							break;
					}
				}
				i=16;
				int k=0;
				while(line[i]!='$'){
					if (line[i]!='^'){
						for (j=0, i; j<6; j++, i++){
							code[j]=line[i];
							if (j>1)
								cadr[j-2]=line[i];
						}
						code[j]='\0';
						cadr[j-2]='\0';
						if (mask[k]=='1'){
							cadr2=(int)strtol(cadr, NULL, 16)+start;
							printf("%x\t%c%c%x\n", saddr2, code[0], code[1], cadr2);
						}
						else{
							printf("%x\t%s\n",saddr2,code);
						}
						saddr2+=0x3;
						k++;
					}
					else{
						i++;
					}
				}
			}
			if (line[0]=='E'){
				printf("Jump to address: %x\n", start);
				break;
			}
		}while(!feof(obj));
		
	}
	fclose(obj);
}