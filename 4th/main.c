#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#define MAX_ROW 10

typedef struct _Row{
	int index;
	int numara;
	int next;
	char isim[50];
	char soyIsim[50];
}Row;

typedef struct _Table{
	Row rows[MAX_ROW];
}Table;
Table table;

int RSHash(int no){
	return no % MAX_ROW;
}


void musteriEkle(int musteri_no,char isim[50],char soyisim[50]){
	int hash_index = RSHash(musteri_no),i;
	if(table.rows[hash_index].index==-1){
		table.rows[hash_index].numara = musteri_no;
		strcpy(table.rows[hash_index].isim,isim);
		strcpy(table.rows[hash_index].soyIsim,soyisim);
		table.rows[hash_index].index = hash_index;
		//printf("\nDebugging");
	}
	
	else{
		if(table.rows[hash_index].next==-1){
			for(int i=0;i<MAX_ROW;i++){
				if(table.rows[i].index==-1){
					table.rows[i].index=i;
					table.rows[i].numara=musteri_no;
					strcpy(table.rows[i].isim,isim);
					strcpy(table.rows[i].soyIsim,soyisim);
					table.rows[hash_index].next=i;	
					break;	
				}				
			}		
		}
		
		else{
			for(int i=0;i<MAX_ROW;i++){
				if(table.rows[i].index==-1){
					table.rows[i].index=i;
					table.rows[i].numara=musteri_no;
					strcpy(table.rows[i].isim,isim);
					strcpy(table.rows[i].soyIsim,soyisim);
					table.rows[table.rows[hash_index].next].next=i;	
					break;
				}
			}
		}
	}
}

void dosyadanCek(){
	char dosyaadi[50] = "veri.txt";
	FILE* okuyucu = fopen(dosyaadi,"r");
	int no;
	char ad[50], soyad[50];
	while(!feof(okuyucu)){
	fscanf(okuyucu,"%d %s %s",&no,ad,soyad);
	musteriEkle(no,ad,soyad);	
	}
}

void initialize_Table(){ 
	int i;
	for (i = 0; i < MAX_ROW; ++i){ 
		table.rows[i].index = -1;
		table.rows[i].numara=-1;
		table.rows[i].next=-1;
	}
}

void hashListele(){
	int i;
	for(i=0;i<MAX_ROW;i++){
		printf("%d ",table.rows[i].numara);
		printf("%d",table.rows[i].next);
		printf("\n");
	}
}

void veriListele(){
	int i;
	for(i=0;i<MAX_ROW;i++){
		while(table.rows[i].index!=-1){
			printf("%d ",table.rows[i].numara);
			printf("%s ",table.rows[i].isim);
			printf("%s ",table.rows[i].soyIsim);
			printf("\n");
			break;
		}
	}
}

int musteriAdim(int musteri_no){
	int hash_index = RSHash(musteri_no);
	if(table.rows[hash_index].numara==musteri_no){
		return 1;
	}
	else if(table.rows[hash_index].next!=-1){
		if(table.rows[table.rows[hash_index].next].numara == musteri_no){
			return  2;
		}
		else if(table.rows[table.rows[hash_index].next].numara != musteri_no && table.rows[table.rows[hash_index].next].next != -1){
				if(table.rows[table.rows[table.rows[hash_index].next].next].numara == musteri_no){
					return 3;
				}
				else
					return -1; 
		}
		else if(table.rows[table.rows[hash_index].next].numara != musteri_no && table.rows[table.rows[hash_index].next].next == -1)
			return -1;
	}
	else if(table.rows[hash_index].numara!=musteri_no && table.rows[hash_index].next==-1)
		return -1;
}

int musteriAra(int musteri_no){
	int hash_index = RSHash(musteri_no);
	if(table.rows[hash_index].numara==musteri_no){
		printf("%d ",musteri_no);
		printf("%s ",table.rows[hash_index].isim);
		printf("%s \n",table.rows[hash_index].soyIsim);
		return 1;
	}
	else if(table.rows[hash_index].next!=-1){
		if(table.rows[table.rows[hash_index].next].numara == musteri_no){
			printf("%d ",table.rows[table.rows[hash_index].next].numara);
			printf("%s ",table.rows[table.rows[hash_index].next].isim);
			printf("%s \n",table.rows[table.rows[hash_index].next].soyIsim);
			return  2;
		}
		else if(table.rows[table.rows[hash_index].next].numara != musteri_no && table.rows[table.rows[hash_index].next].next != -1){
				if(table.rows[table.rows[table.rows[hash_index].next].next].numara == musteri_no){
					printf("%d ",table.rows[table.rows[table.rows[hash_index].next].next].numara);
					printf("%s ",table.rows[table.rows[table.rows[hash_index].next].next].isim);
					printf("%s \n",table.rows[table.rows[table.rows[hash_index].next].next].soyIsim);
					return 3;
				}
				else 
					return -1;
					//printf("Veri bulunamadi \n");
		}
		else if(table.rows[table.rows[hash_index].next].numara != musteri_no && table.rows[table.rows[hash_index].next].next == -1)
			return -1;
		//	printf("Veri Bulunamadi \n");
	}
	else if(table.rows[hash_index].numara!=musteri_no && table.rows[hash_index].next==-1)
		return -1;
	//	printf("Veri bulunamadi \n");
}

void musteriSil(int musteri_no){
	int i;
	for(i=0;i<MAX_ROW;i++){
		if(table.rows[i].numara==musteri_no){
			table.rows[i].index = -1;	
			table.rows[i].numara = -1;
			//break;
		}
	}	
}

void ortlamaAdim(){
	int i,topAdim=0,adim=0,sayac=0;
	float ortAdim;
	for(i=0;i<MAX_ROW;i++){
		if(table.rows[i].index != -1){
			sayac += 1;
			adim = musteriAdim(table.rows[i].numara);
			topAdim = topAdim + adim;
		}
	}
	ortAdim = float(topAdim)/float(sayac);	
	printf("Ortalama adim saysi>> %f",ortAdim);
}

void varMi(int adim){
	if(adim == -1){
		printf("Veri bulunamadi.\n");
	}
	else
		printf("Veri %d adimda bulundu.\n",adim);
}

int main(){
	initialize_Table();
	dosyadanCek();
	int secim,musteri_no,adim=0;
	while(secim!=7){
   	printf("\n1-Ekleme Islemi\n2-Arama Islemi\n3-Silme Islemi\n4-Hash Tablosunu Listele\n5-Veri Dizisini Listeleme\n6-Ortalama Adim\n7-Cikis\nSecim>>");
   	scanf("%d",&secim);
   	char ad[50],soyad[50];
   	switch(secim){
   		case 1:
   			printf("Musteri Bilgilerini Girin (Mstrno Ad Soyad):\n>>");
   			scanf("%d %s %s",&musteri_no,ad,soyad);
   			musteriEkle(musteri_no,ad,soyad);
   			printf("Ekleme islemi basarili.\n");
   			break;
   		case 2:
   			printf("Aramak Istediginiz Musteri Numarasini Giriniz:\n>>");
   			scanf("%d",&musteri_no);
   			adim = musteriAra(musteri_no);
   			varMi(adim);
   			//printf("Veri %d adimda bulundu.\n",adim);
   			break;
   		case 3:
   			printf("Silmek Istediginiz Musteri Numarasini Giriniz:\n>>");
   			scanf("%d",&musteri_no);
   			musteriSil(musteri_no);
   			break;
   		case 4:
   			hashListele();
   			break;
   		case 5:
   			veriListele();
   			break;
   		case 6:
   			ortlamaAdim();
   			break;
   		default:
   			break;
	   }
	}
}

