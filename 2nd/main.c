#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 5
int top=-1,islem[MAX],geri[MAX];
void elemanEkle(int val);
void elemanCikar();
void bastir();
 

int main(){
	int deger;
	char komut1[]="EKLE", komut2[]="SIL", komut3[]="YAZDIR", komut4[]="GERIAL", secilen[10];

while(1){
	printf("Isleminizi giriniz:\n"); 
	scanf("%s",&secilen);
	
	if(strcmp(komut1,secilen)==0){	//EKLE 30
		scanf("%d",&deger);
		elemanEkle(deger);
	}
	
	if(strcmp(komut2,secilen)==0){	//SIL
		elemanCikar();
	}
	
	if(strcmp(komut3,secilen)==0){	//YAZDIR
		bastir();
	}
	
	if(strcmp(komut4,secilen)==0){	//GERIAL
		printf("GERI ALINDI\n");
		
	}
}
}

void elemanCikar()
{
	if(top==-1)
	{
		printf("Stack Bos Silinemez!!\n");
	}
	else
	{
		printf("%d SILINDI\n",islem[top]);
		top=top-1;
	}
}

void bastir()
{
	int i;
	
	if(top==-1)
	{
		printf("STACK BOS !!\n");
	}
	else
	{
		printf("EKRANA YAZDIRILDI = ");
		for(i=top;i>=0;--i)
			printf("%d ",islem[i]);
		printf("\n");
	}
}

void elemanEkle(int val)
{
	if(top==MAX-1)
	{
		printf("STACK DOLU !!\n");
	}
	else
	{
		printf("DEGER EKLENDI\n");
		top=top+1;
		islem[top]=val;
	}
}
 

