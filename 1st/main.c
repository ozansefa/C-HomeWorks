#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct ogrenci {
   int ogrno;
   char ad[50];
   char soyad[50];
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
   char geciciAd[50],geciciSoyad[50];
   struct ogrenci *kontrol=listebasi;
   struct ogrenci *sonraki=NULL;
   k = listeBoyutu();
   for ( i = 0 ; i < listeBoyutu() - 1 ; i++, k-- ) {
      kontrol = listebasi;
      sonraki = listebasi->sonraki;
      for ( j = 1 ; j < k ; j++ ) {  
      
        	 if (sonraki->sonhane>kontrol->sonhane) {
            strcpy(geciciAd,kontrol->ad);
            strcpy(geciciSoyad,kontrol->soyad);
            
            strcpy(kontrol->ad,sonraki->ad);
            strcpy(kontrol->soyad,sonraki->soyad);
            
            strcpy(sonraki->ad,geciciAd);
            strcpy(sonraki->soyad,geciciSoyad);

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
      printf("%d %s %s\n",ogr->ogrno,ogr->ad,ogr->soyad);
      ogr = ogr->sonraki;
   }
   printf("\n");
}
void ogrenciEkle(int ogrno, char ad[50],char soyad[50]) {
   struct ogrenci *yeniogrenci = (struct ogrenci*) malloc(sizeof(struct ogrenci));
	
   yeniogrenci->ogrno = ogrno;
   strcpy(yeniogrenci->ad,ad);
   strcpy(yeniogrenci->soyad,soyad);
   yeniogrenci->sonhane=ogrno%10;
   yeniogrenci->sonraki = listebasi;
   listebasi = yeniogrenci;
   frekans[ogrno%10]++;
}

void sonaogrenciEkle(int ogrno, char ad[50],char soyad[50]) {
   struct ogrenci *yeniogrenci = (struct ogrenci*) malloc(sizeof(struct ogrenci));
	struct ogrenci *temp;
   yeniogrenci->ogrno = ogrno;
   strcpy(yeniogrenci->ad,ad);
   strcpy(yeniogrenci->soyad,soyad);
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
void ogrenciSil(int ogrno) 
{ 
    struct ogrenci* geciciOgr = listebasi, *oncekiogrenci; 
    if (geciciOgr != NULL && geciciOgr->ogrno == ogrno) 
    { 
        listebasi = geciciOgr->sonraki;  
        free(geciciOgr);             
        return; 
    } 
    while (geciciOgr != NULL && geciciOgr->ogrno != ogrno) 
    { 
        oncekiogrenci = geciciOgr; 
        geciciOgr = geciciOgr->sonraki; 
    } 
    if (geciciOgr == NULL) {
    printf("Kayit Bulunamadi.\n");
	return; 	
	}
	frekans[geciciOgr->ogrno%10]--;
    oncekiogrenci->sonraki = geciciOgr->sonraki; 
    free(geciciOgr); 
	printf("Silme islemi basarili.\n"); 
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
   printf("Ogrenci %d adimda bulundu.\n",sayac);
   printf("%d %s %s\n",kontrol->ogrno,kontrol->ad,kontrol->soyad);
}
void dosyadanCek(){
	char dosyaadi[50] = "ogrenciler.txt";
	FILE* okuyucu = fopen(dosyaadi,"r");
	int no;
	char ad[50], soyad[50];
	while(!feof(okuyucu)){
	fscanf(okuyucu,"%d %s %s",&no,ad,soyad);
	sonaogrenciEkle(no,ad,soyad);	
	}
   printf("Veriler Dosyadan Eklendi.\n");
}
void dosyayaKaydet(){
	struct ogrenci *ptr = listebasi;
	FILE* kayit = fopen("Kayitlar.txt","w");
   while(ptr != NULL) {
      fprintf(kayit,"%d %s %s\n",ptr->ogrno,ptr->ad,ptr->soyad);
      ptr = ptr->sonraki;
   }
   fprintf(kayit,"\n");
   printf("Veriler Kayitlar.txt dosyasina kaydedildi.\n");
}
void main() {
   //ogrenciEkle(58,"Ali","Demir");
   //ogrenciEkle(16,"Fatma","Verimli");
   //ogrenciEkle(26,"Ayse","Korkmaz");
   //ogrenciEkle(38,"Naci","Mutlu");
   //ogrenciEkle(471,"Osman","Cetin");
	dosyadanCek();
   	int secim,i=0;
   	for(i=0;i<10;i++){
   		sira[i]=i;
   		//printf("%d = %d \n",i,frekans[i]);
	}
   	siraHesapla();
   while(secim!=5){
   	printf("1-Ogrenci Ekle\n2-Ogrenci Ara\n3-Listele\n4-Ogrenci Sil\n5-Kaydet ve Cik\nSecim>>");
   	scanf("%d",&secim);
   	int ogrno;
   	char ad[50],soyad[50];
   	switch(secim){
   		case 1:
   			printf("Ogrenci Bilgilerini Giriniz (Ogrno Ad Soyad):");
   			scanf("%d %s %s",&ogrno,ad,soyad);
   			sonaogrenciEkle(ogrno,ad,soyad);
   			printf("Ekleme islemi basarili.\n");
   			break;
   		case 2:
   			printf("Aramak Istediginiz Ogrenci Numarasini Giriniz:\n");
   			scanf("%d",&ogrno);
   			OgrenciAra(ogrno);
   			break;
   		case 3:
   			Listele();
   			break;
   		case 4:
   			printf("Silmek Istediginiz Ogrenci Numarasini Giriniz:\n");
   			scanf("%d",&ogrno);
   			ogrenciSil(ogrno);
   			break;
   		case 5:
   			dosyayaKaydet();
   			break;
   		default:
   			break;
	   }
   }
}
