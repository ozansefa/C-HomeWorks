#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ogrenci {
   int ogrno;
   char ad[50];
   int sonhane;
   struct ogrenci *sonraki;
};

struct ogrenci *listebasi = NULL;
struct ogrenci *current = NULL;
int frekans[10]={0};
int sira[10]={0};
void siraHesapla(){
	int i,j,enb=0,konum=0;
	for( i=0;i<10;i++){
		enb=0;
		konum=0;
		for(j=0;j<10;j++){
			if(frekans[j]>enb){
			enb = frekans[j];
			konum=j;
			}
		}
		frekans[konum]=0;
		sira[i]=konum;
	}
	for(i=0;i<10;i++){
		//printf("%d\n",sira[i]);
	}
}

void ListeSirala() {
   int i, j,k,geciciogrno,gecicisonhane;
   char geciciAd[50];
   struct ogrenci *kontrol=listebasi;
   struct ogrenci *sonraki=NULL;
   k = listeBoyutu();
   for ( i = 0 ; i < listeBoyutu() - 1 ; i++, k-- ) {
      kontrol = listebasi;
      sonraki = listebasi->sonraki;
      for ( j = 1 ; j < k ; j++ ) {      
        	 if (sonraki->sonhane>kontrol->sonhane) {
            strcpy(geciciAd,kontrol->ad);           
            strcpy(kontrol->ad,sonraki->ad);                      
            strcpy(sonraki->ad,geciciAd);          
            geciciogrno = kontrol->ogrno;
            kontrol->ogrno = sonraki->ogrno;
            sonraki->ogrno = geciciogrno;                       
            gecicisonhane = kontrol->sonhane;
            kontrol->sonhane = sonraki->sonhane;
            sonraki->sonhane = gecicisonhane;
         }		
         kontrol = kontrol->sonraki;
         sonraki = sonraki->sonraki;
      }
   }
}
void Listele() {
   struct ogrenci *ogr = listebasi;
   printf("Ogrenci Listesi\n");
   while(ogr != NULL) {
      printf("%d %s\n",ogr->ogrno,ogr->ad);
      ogr = ogr->sonraki;
   }
   printf("\n");
}
void ogrenciEkle(int ogrno, char ad[50]) {
   struct ogrenci *yeniogrenci = (struct ogrenci*) malloc(sizeof(struct ogrenci));	
   yeniogrenci->ogrno = ogrno;
   strcpy(yeniogrenci->ad,ad);
   yeniogrenci->sonhane=ogrno%10;
   yeniogrenci->sonraki = listebasi;
   listebasi = yeniogrenci;
   frekans[ogrno%10]++;
}

void sonaogrenciEkle(int ogrno, char ad[50]) {
   struct ogrenci *yeniogrenci = (struct ogrenci*) malloc(sizeof(struct ogrenci));
	struct ogrenci *temp;
   yeniogrenci->ogrno = ogrno;
   strcpy(yeniogrenci->ad,ad);
   yeniogrenci->sonhane=ogrno%10;
   if(listebasi==NULL){
   	yeniogrenci->sonraki = listebasi;
   listebasi = yeniogrenci;
   }
   else{
   	yeniogrenci->sonraki=NULL;
   temp=listebasi;
   
   while(temp != NULL && temp->sonraki != NULL){
   	if(yeniogrenci->sonhane==temp->sonhane){
   		yeniogrenci->sonraki=temp->sonraki;
   		temp->sonraki=yeniogrenci;
   		break;
	   }
   	  temp = temp->sonraki;
   }
   temp->sonraki = yeniogrenci;
   }
   frekans[ogrno%10]++;
}

int listeBoyutu() {
   int sayac = 0;
   struct ogrenci *kontrol;
   for(kontrol = listebasi; kontrol != NULL; kontrol = kontrol->sonraki) {
      sayac++;
   }
   return sayac;
}
void OgrenciAra(int ogrno) {
	int sayac=0;
   struct ogrenci* kontrol = listebasi;
   if(listebasi == NULL) {
   	printf("Listede eleman yok.\n");
   	return;
   }
   while(kontrol->ogrno != ogrno) {
      sayac++;
	  if(kontrol->sonraki == NULL) {
      	printf("Ogrenci Bulunamadi.\n");
         return;
      } else {
         kontrol = kontrol->sonraki;
      }
   }
   printf("Ogrencinin onunde %d kisi var.\n",sayac);
   printf("%d %s\n",kontrol->ogrno,kontrol->ad);
}
void dosyadanCek(){
	char dosyaadi[50] = "kisiler.txt";
	FILE* okuyucu = fopen(dosyaadi,"r");
	int no;
	char ad[50], soyad[50];
	while(!feof(okuyucu)){
	fscanf(okuyucu,"%d %s",&no,ad);
	sonaogrenciEkle(no,ad);	
	}
   printf("Veriler Dosyadan Eklendi.\n");
}


void main() {
	dosyadanCek();
   	int secim,i=0;
   	for(i=0;i<10;i++){
   		sira[i]=i;  		
	}
   	siraHesapla();
   while(secim!=5){
   	printf("1-Ogrenci Ekle\n2-Ogrenci Ara\n3-Listele\nSecim>>");
   	scanf("%d",&secim);
   	int ogrno;
   	char ad[50];
   	switch(secim){
   		case 1:
   			printf("Ogrenci Bilgilerini Giriniz (OncelikNo Ad):");
   			scanf("%d %s",&ogrno,&ad);
   			sonaogrenciEkle(ogrno,ad);
   			printf("Ekleme islemi basarili.\n");
   			break;
   		case 2:
   			printf("Aramak Istediginiz Ogrenci Numarasini Oncelik Numarasini Giriniz:\n");
   			scanf("%d",&ogrno);
   			OgrenciAra(ogrno);
   			break;
   		case 3:
   			Listele();
   			break;   		
   		default:
   			break;
	   }
   }
}
