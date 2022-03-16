#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{
	int id;
	char no[10];
	char ad[20];
	char soyad[20];
	int topders;
	int kredi;
}OGRENCI;

typedef struct{
	int id;
	char ad[20];
	char soyad[20];
	char unvan[20];
}OGRETMEN;

typedef struct{
	char kodu[10];
	char adi[30];
	int drskredi;
	int kontenjan;
	int ortid;
}DERS;

typedef struct{
	int id;
	char ogrencino[10];
	char derskod[10];
	char kayit_birak[10];
}KAYIT;

void ogr_ekle();
void ogr_sil();
void ogr_guncelle();
void hoca_ekle();
void hoca_sil();
void hoca_guncelle();
void ders_ekle();
void ders_sil();
void ders_guncelle();
void kayit();
void kayit_silme();
void hoca_dersler();
void dersi_alanlar();
void ogrenci_dersler();
void sinif_listesi();

int main(){
	setlocale(LC_ALL,"Turkish");
	int n,a=1;
	while(a>0){
		printf("\n1.ogrenci ekleme\n");
		printf("2.ogrenci silme\n");
		printf("3.ogrenci guncelleme\n");
		printf("4.ogretim gorevlisi ekleme\n");
		printf("5.ogretim gorevlisi silme\n");
		printf("6.ogretim gorevlisi guncelleme\n");
		printf("7.ders ekleme\n");
		printf("8.ders silme\n");
		printf("9.ders guncelleme\n");
		printf("10.ogrenci ders kayit\n");
		printf("11.ogrenci ders silme\n");
		printf("12.ogretim gorevlisinin verdigi dersler\n");
		printf("13.dersi alanlar\n");
		printf("14.ogrencinin aldigi dersler\n");
		printf("15.sinif listesi\n");
		printf("0.cikis\n\n");
		
		printf("Yapmak istediginiz islemi secin: ");
		scanf("%d",&n);
		if(n==1){
			ogr_ekle();
		}
		else if(n==2){
			ogr_sil();
		}
		else if(n==3){
			ogr_guncelle();
		}
		else if(n==4){
			hoca_ekle();
		}
		else if(n==5){
			hoca_sil();
		}
		else if(n==6){
			hoca_guncelle();
		}
		else if(n==7){
			ders_ekle();
		}
		else if(n==8){
			ders_sil();
		}
		else if(n==9){
			ders_guncelle();
		}
		else if(n==10){
			kayit();
		}
		else if(n==11){
			kayit_silme();
		}
		else if(n==12){
			hoca_dersler();
		}
		else if(n==13){
			dersi_alanlar();
		}
		else if(n==14){
			ogrenci_dersler();
		}
		else if(n==15){
			sinif_listesi();
		}
		else{
			a=0;
		}
	}
}

void ogr_ekle(){
	FILE *liste=fopen("ogrenciler.txt","a+");
	OGRENCI ogr;
	int say=0,a=0;
	OGRENCI *optr;
	printf("mevcut ogrenciler:\n");
	while(!feof(liste)){
		fscanf(liste,"%d %s %s %s %d %d\n", &ogr.id, ogr.no, ogr.ad, ogr.soyad, &ogr.topders, &ogr.kredi);
		printf("%d %s %s %s %d %d\n", ogr.id, ogr.no, ogr.ad, ogr.soyad, ogr.topders, ogr.kredi);
		say++;
	}
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	printf("\n");
	printf("sirasiyla numara ad soyad toplam ders sayisi ve kredi miktarýný giriniz: ");
	scanf("%s %s %s %d %d", ogr.no, ogr.ad, ogr.soyad, &ogr.topders, &ogr.kredi);
	fprintf(liste,"\n%d %s %s %s %d %d", say+1, ogr.no, ogr.ad, ogr.soyad, ogr.topders, ogr.kredi);
	
	fseek(liste, 0, SEEK_SET);
	printf("\nyeni ogrenci listesi:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		printf("%d %s %s %s %d %d\n", optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, optr[a-1].topders, optr[a-1].kredi);
	}
	fclose(liste);
}

void ogr_sil(){
	FILE *liste=fopen("ogrenciler.txt","r");
	OGRENCI ogr;
	int a=0,id,i;
	char no[10];
	char birakti[10]="BIRAKTI";
	OGRENCI *optr;
	KAYIT *kptr;
	
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	
	printf("mevcut ogrenciler:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		printf("%d %s %s %s %d %d\n", optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, optr[a-1].topders, optr[a-1].kredi);
		
	}
	
	printf("\nsilmek istediginiz ogrencinin id sini giriniz: ");
	scanf("%d",&id);
	fclose(liste);
	
	strcpy(no,optr[id-1].no);
	//printf("\n*********%s***********\n",no);
	liste=fopen("ogrenciler.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(id==optr[i].id){
				id=optr[i+1].id;
				strcpy(optr[i].no, optr[i+1].no);
				strcpy(optr[i].ad, optr[i+1].ad);
				strcpy(optr[i].soyad, optr[i+1].soyad);
				optr[i].topders=optr[i+1].topders;
				optr[i].kredi=optr[i+1].kredi;
			}
	}
	
	printf("\nyeni ogrenci listesi:\n");
	for(i=0;i<a-1;i++){
		fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
		printf("%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	a=0;
	while(!feof(liste)){
		a++;
		kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
		if(!strcmp(kptr[a-1].ogrencino,no)){
			strcpy(kptr[a-1].kayit_birak,birakti);
		}
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","w");
	for(i=0;i<a;i++){
		fprintf(liste,"%d %s %s %s\n", i+1, kptr[i].ogrencino, kptr[i].derskod, kptr[i].kayit_birak);
	}
	
	fclose(liste);
	free(optr);
	free(kptr);
}

void ogr_guncelle(){
	FILE *liste=fopen("ogrenciler.txt","r");
	OGRENCI ogr;
	int a=0,id,i;
	
	OGRENCI *optr;
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	
	printf("mevcut ogrenciler:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		printf("%d %s %s %s %d %d\n", optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, optr[a-1].topders, optr[a-1].kredi);
		
	}
	
	printf("\nguncellemek istediginiz ogrencinin id sini giriniz: ");
	scanf("%d",&id);
	fclose(liste);
	
	liste=fopen("ogrenciler.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(id==optr[i].id){
				printf("sirasiyla yeni numara ad soyad topders ve kredi miktarýný giriniz: ");
				scanf("%s %s %s %d %d", optr[i].no, optr[i].ad, optr[i].soyad, &optr[i].topders, &optr[i].kredi);
			}
	}
	printf("\nyeni ogrenci listesi:\n");
	for(i=0;i<a;i++){
		fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
		printf("%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
	}
	fclose(liste);
	free(optr);
}

void hoca_ekle(){
	FILE *liste=fopen("hocalar.txt","a+");
	OGRETMEN hoca;
	int say=0,a;
	OGRETMEN *optr;
	
	printf("mevcut ogretim uyeleri:\n");
	while(!feof(liste)){
		fscanf(liste,"%d %s %s %s\n", &hoca.id, hoca.ad, hoca.soyad, hoca.unvan);
		printf("%d %s %s %s\n", hoca.id, hoca.ad, hoca.soyad, hoca.unvan);
		say++;
	}
	optr=(OGRETMEN*)malloc(1*sizeof(OGRETMEN));
	printf("\n");
	printf("sirasiyla ad soyad ve unvan giriniz: ");
	scanf("%s %s %s", hoca.ad, hoca.soyad, hoca.unvan);
	fprintf(liste,"\n%d %s %s %s", say+1, hoca.ad, hoca.soyad, hoca.unvan);
	
	fseek(liste, 0, SEEK_SET);
	printf("\nyeni ogretim gorevlisi listesi:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRETMEN*)realloc(optr,a*sizeof(OGRETMEN));
		fscanf(liste,"%d %s %s %s\n", &optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		printf("%d %s %s %s\n", optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
	}
	fclose(liste);
}

void hoca_sil(){
	FILE *liste=fopen("hocalar.txt","a+");
	OGRETMEN hoca;
	int a=0,b=0,id,i,j,silinen,say;
	OGRETMEN *optr;
	DERS *dptr;
	KAYIT *kptr;
	optr=(OGRETMEN*)malloc(1*sizeof(OGRETMEN));
	
	printf("mevcut ogretim uyeleri:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRETMEN*)realloc(optr,a*sizeof(OGRETMEN));
		fscanf(liste,"%d %s %s %s\n", &optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		printf("%d %s %s %s\n", optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		
	}
	
	printf("\nsilmek istediginiz ogretim uyesinin id sini giriniz: ");
	scanf("%d",&id);
	silinen=id;
	fclose(liste);
	
	liste=fopen("hocalar.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(id==optr[i].id){
				//printf(" %d %d ",id,optr[i].kredi);
				id=optr[i+1].id;
				//optr[i].id=optr[i+1].id;
				strcpy(optr[i].ad, optr[i+1].ad);
				strcpy(optr[i].soyad, optr[i+1].soyad);
				strcpy(optr[i].unvan, optr[i+1].unvan);
			}
	}
	printf("\nyeni ogretim gorevlisi listesi:\n");
	for(i=0;i<a-1;i++){
		fprintf(liste,"%d %s %s %s\n", optr[i].id, optr[i].ad, optr[i].soyad, optr[i].unvan);
		printf("%d %s %s %s\n", optr[i].id, optr[i].ad, optr[i].soyad, optr[i].unvan);
	}
	fclose(liste);
	liste=fopen("dersler.txt","r");
	dptr=(DERS*)malloc(1*sizeof(DERS));
	
	a=0;
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
	}
	
	fclose(liste);
	
	liste=fopen("dersler.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
		if(silinen!=dptr[i].ortid){
			if(silinen<dptr[i].ortid){
				fprintf(liste,"%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid-1);
			}
			else{
				fprintf(liste,"%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid);
			}
		}
	}
	fclose(liste);
	free(dptr);
	
	liste=fopen("dersler.txt","r");
	dptr=(DERS*)malloc(1*sizeof(DERS));
	
	a=0;
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	b=0;
	while(!feof(liste)){
		b++;
		kptr=(KAYIT*)realloc(kptr,b*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[b-1].id, kptr[b-1].ogrencino, kptr[b-1].derskod, kptr[b-1].kayit_birak);
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","w");
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			if(!strcmp(dptr[i].kodu,kptr[j].derskod)){
				say++;
				fprintf(liste,"%d %s %s %s\n", say, kptr[j].ogrencino, kptr[j].derskod, kptr[j].kayit_birak);
			}
		}
	}
	fclose(liste);
	free(optr);
	free(dptr);
	free(kptr);
}

void hoca_guncelle(){
	FILE *liste=fopen("hocalar.txt","r");
	OGRETMEN hoca;
	int a=0,id,i;
	
	OGRETMEN *optr;
	optr=(OGRETMEN*)malloc(1*sizeof(OGRETMEN));
	
	printf("mevcut ogretim gorevlileri:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRETMEN*)realloc(optr,a*sizeof(OGRETMEN));
		fscanf(liste,"%d %s %s %s\n", &optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		printf("%d %s %s %s\n", optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		
	}
	
	printf("\nguncellemek istediginiz ogretim gorevlisinin id sini giriniz: ");
	scanf("%d",&id);
	fclose(liste);
	
	liste=fopen("hocalar.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(id==optr[i].id){
				printf("sirasiyla yeni ad soyad ve unvan giriniz: ");
				scanf("%s %s %s", optr[i].ad, optr[i].soyad, optr[i].unvan);
			}
	}
	
	printf("\nyeni ogretim gorevlisi listesi:\n");
	for(i=0;i<a;i++){
		fprintf(liste,"%d %s %s %s\n", optr[i].id, optr[i].ad, optr[i].soyad, optr[i].unvan);
		printf("%d %s %s %s\n", optr[i].id, optr[i].ad, optr[i].soyad, optr[i].unvan);
	}
	fclose(liste);
	free(optr);
}

void ders_ekle(){
	FILE *liste=fopen("dersler.txt","a+");
	DERS drs;
	int a;
	DERS *dptr;
	
	printf("mevcut dersler:\n");
	while(!feof(liste)){
		fscanf(liste,"%s %s %d %d %d\n", drs.kodu, drs.adi, &drs.drskredi, &drs.kontenjan, &drs.ortid);
		printf("%s %s %d %d %d\n", drs.kodu, drs.adi, drs.drskredi, drs.kontenjan, drs.ortid);
	}
	dptr=(DERS*)malloc(1*sizeof(DERS));
	printf("\n");
	printf("sirasiyla ders kodu, adi, ders kredisi, kontenjan ve dersi verenin id sini giriniz: ");
	scanf("%s %s %d %d %d", drs.kodu, drs.adi, &drs.drskredi, &drs.kontenjan, &drs.ortid);
	fprintf(liste,"\n%s %s %d %d %d", drs.kodu, drs.adi, drs.drskredi, drs.kontenjan, drs.ortid);
	
	fseek(liste, 0, SEEK_SET);
	printf("\nyeni ders listesi:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
		printf("%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, dptr[a-1].drskredi, dptr[a-1].kontenjan, dptr[a-1].ortid);
	}
	fclose(liste);
}

void ders_sil(){
	FILE *liste=fopen("dersler.txt","r");
	DERS drs;
	int a=0,b=0,i,j,say;
	char kod[10];
	OGRENCI *optr;
	DERS *dptr;
	KAYIT *kptr;
	dptr=(DERS*)malloc(1*sizeof(DERS));
	
	printf("mevcut dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
		printf("%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, dptr[a-1].drskredi, dptr[a-1].kontenjan, dptr[a-1].ortid);
		
	}
	
	printf("\nsilmek istediginiz dersin kodunu giriniz: ");
	scanf("%s",kod);
	fclose(liste);
	
	liste=fopen("dersler.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(!strcmp(kod, dptr[i].kodu)){
				strcpy(kod, dptr[i+1].kodu);
				strcpy(dptr[i].kodu, dptr[i+1].kodu);
				strcpy(dptr[i].adi, dptr[i+1].adi);
				dptr[i].drskredi=dptr[i+1].drskredi;
				dptr[i].kontenjan=dptr[i+1].kontenjan;
				dptr[i].ortid=dptr[i+1].ortid;
			}
	}
	printf("\nyeni ders listesi:\n");
	for(i=0;i<a-1;i++){
		fprintf(liste,"%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid);
		printf("%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid);
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	b=0;
	while(!feof(liste)){
		b++;
		kptr=(KAYIT*)realloc(kptr,b*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[b-1].id, kptr[b-1].ogrencino, kptr[b-1].derskod, kptr[b-1].kayit_birak);
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","w");
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			if(!strcmp(dptr[i].kodu,kptr[j].derskod)){
				say++;
				fprintf(liste,"%d %s %s %s\n", say, kptr[j].ogrencino, kptr[j].derskod, kptr[j].kayit_birak);
			}
		}
	}
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	b=0;
	while(!feof(liste)){
		b++;
		kptr=(KAYIT*)realloc(kptr,b*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[b-1].id, kptr[b-1].ogrencino, kptr[b-1].derskod, kptr[b-1].kayit_birak);
	}
	fclose(liste);
	
	liste=fopen("ogrenciler.txt","r");
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	a=0;
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		optr[a-1].topders=0;
	}
	fclose(liste);
	
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			if(!strcmp(kptr[j].ogrencino,optr[i].no) && strcmp(kod,kptr[j].derskod)){
				optr[i].topders+=1;
			}
		}
	}
	
	liste=fopen("ogrenciler.txt","w");
	for(i=0;i<a;i++){
		fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
	}
	
	fclose(liste);
	free(optr);
	free(dptr);
	free(kptr);
}

void ders_guncelle(){
	FILE *liste=fopen("dersler.txt","r");
	DERS drs;
	int a=0,i;
	char kod[10];
	
	DERS *dptr;
	dptr=(DERS*)malloc(1*sizeof(DERS));
	
	printf("mevcut dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
		printf("%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, dptr[a-1].drskredi, dptr[a-1].kontenjan, dptr[a-1].ortid);
		
	}
	
	printf("\nguncellemek istediginiz dersin kodunu giriniz: ");
	scanf("%s",kod);
	fclose(liste);
	
	liste=fopen("dersler.txt","w");
	fseek(liste, 0, SEEK_SET);
	
	for(i=0;i<a;i++){
			if(!strcmp(kod, dptr[i].kodu)){
				printf("sirasiyla yeni ders kodunu, adini, kredisini, kontenjanini ve ogretim gorevlisi id sini giriniz: ");
				scanf("%s %s %d %d %d", dptr[i].kodu, dptr[i].adi, &dptr[i].drskredi, &dptr[i].kontenjan, &dptr[i].ortid);
			}
	}
	printf("\nyeni ders listesi:\n");
	for(i=0;i<a;i++){
		fprintf(liste,"%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid);
		printf("%s %s %d %d %d\n", dptr[i].kodu, dptr[i].adi, dptr[i].drskredi, dptr[i].kontenjan, dptr[i].ortid);
	}
	fclose(liste);
	free(dptr);
}

void kayit(){
	FILE *liste=fopen("ogrenciler.txt","r");
	OGRENCI *optr;
	DERS *dptr;
	KAYIT *kptr;
	
	int a=0,b=0,id,i,j,say=1,krd,ek=0,max=8;
	int kntrl=0,var=0,ogrsayi,kont=0,kontmax=0;
	char kod[10];
	char kayitli[10]="KAYITLI";
	
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	
	printf("mevcut ogrenciler:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		printf("%d %s %s %s %d %d\n", optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, optr[a-1].topders, optr[a-1].kredi);
	}
	ogrsayi=a;
	printf("\nkaydolacak ogrencinin id sini giriniz: ");
	scanf("%d",&id);
	fclose(liste);
	
	liste=fopen("dersler.txt","r");
	
	dptr=(DERS*)malloc(1*sizeof(DERS));
	a=0;
	printf("mevcut dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
		printf("%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, dptr[a-1].drskredi, dptr[a-1].kontenjan, dptr[a-1].ortid);
		
	}
	
	printf("\nkaydolacagi dersin kodunu giriniz: ");
	scanf("%s",kod);
	fclose(liste);
	
	for(i=0;i<a;i++){
		if(!strcmp(kod,dptr[i].kodu)){
			kontmax=dptr[i].kontenjan;
		}
	}
	
	liste=fopen("OgrenciDersKayit.txt","r");
	
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	b=0;
	while(!feof(liste)){
		b++;
		kptr=(KAYIT*)realloc(kptr,b*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[b-1].id, kptr[b-1].ogrencino, kptr[b-1].derskod, kptr[b-1].kayit_birak);
		if(!strcmp(kod,kptr[b-1].derskod) && !strcmp(kptr[b-1].kayit_birak,kayitli)){
			kont+=1;
		}
	}
	
	optr[id-1].topders=0;
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			if(!strcmp(kptr[j].ogrencino,optr[id-1].no) && !strcmp(kptr[j].kayit_birak,kayitli) && !strcmp(dptr[i].kodu,kptr[j].derskod)){
				krd+=dptr[i].drskredi;
				optr[id-1].topders+=1;
			}
			if(!strcmp(kod,dptr[i].kodu)){
				ek=dptr[i].drskredi;
			}
		}
	}
	fclose(liste);
	
	if((krd+ek)<optr[id-1].kredi && optr[id-1].topders<max && kont<kontmax){		
		for(i=0;i<a;i++){
			if(!strcmp(dptr[i].kodu,kod)){
				var=1;
			}
		}
		
		if(var!=0){
			liste=fopen("OgrenciDersKayit.txt","r");
		
			kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
			
			a=0;
			while(!feof(liste)){
				a++;
				kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
				fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
				kptr[a-1].id=a;
				if(!strcmp(kptr[a-1].ogrencino, optr[id-1].no) && !strcmp(kptr[a-1].derskod,kod)){
					strcpy(kptr[a-1].kayit_birak, kayitli);
					kntrl=1;
				}
			}
			fclose(liste);
			
			liste=fopen("OgrenciDersKayit.txt","w");
			for(i=0;i<a;i++){
				if (kptr[i].ogrencino[0] != '\0')
				{
					fprintf(liste,"%d %s %s %s\n", kptr[i].id, kptr[i].ogrencino, kptr[i].derskod, kptr[i].kayit_birak);
					say+=1;
				}
			}
			if(kntrl!=1){
				fprintf(liste,"%d %s %s %s\n", say, optr[id-1].no, kod, kayitli);
				optr[id-1].topders+=1;
			}
			fclose(liste);
			printf("\nKAYIT OLUSTURULMUSTUR.\n");
			
			liste=fopen("ogrenciler.txt","w");
			for(i=0;i<ogrsayi;i++){
				fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
			}
			fclose(liste);
			free(kptr);
		}
		else{
			printf("bu koda sahip ders bulunmamaktadýr.\n");
		}
	}
	else{
		if((krd+ek)>=optr[id-1].kredi){
			printf("krediniz yetmemektedir.\n");
		}
		if(optr[id-1].topders>=max){
			printf("maksimum ders sinirini astiniz.\n");
		}
		if(kont>=kontmax){
			printf("kontenjan dolu\n");
		}
	}
	
		
	free(optr);
	free(dptr);
}

void kayit_silme(){
	FILE *liste=fopen("OgrenciDersKayit.txt","r");
	KAYIT *kptr;
	OGRENCI *optr;
	int a=0,id,i;
	int var=0;
	char numara[10], kod[10];
	char birakti[10]="BIRAKTI";
	
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	a=0;
	printf("KAYITLAR:\n");
	while(!feof(liste)){
		a++;
		kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
		printf("%s %s %s\n", kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
	}
	fclose(liste);
	
	printf("kaydýný silmek istediginiz ogrencinin numarasýný giriniz: ");
	scanf("%s",numara);
	printf("kaydý silmek istediginiz ders kodunu giriniz: ");
	scanf("%s",kod);
	
	for(i=0;i<a;i++){
		if(!strcmp(kptr[i].derskod,kod)){
			var=1;
		}
	}
	
	if(var!=0){
		liste=fopen("OgrenciDersKayit.txt","w");
		for(i=0;i<a;i++){
			if(!strcmp(kptr[i].ogrencino, numara) && !strcmp(kptr[i].derskod,kod)){
				strcpy(kptr[i].kayit_birak, birakti);
			}
			fprintf(liste,"%d %s %s %s\n", i+1, kptr[i].ogrencino, kptr[i].derskod, kptr[i].kayit_birak);
		}
		fclose(liste);
		printf("\nKAYIT SILINMISTIR.\n");
		
		liste=fopen("ogrenciler.txt","r");
		optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
		a=0;
		while(!feof(liste)){
			a++;
			optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
			fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		}
		fclose(liste);
		
		liste=fopen("ogrenciler.txt","w");
		for(i=0;i<a;i++){
			if(!strcmp(numara,optr[i].no)){
				fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders-1, optr[i].kredi);
			}
			else{
				fprintf(liste,"%d %s %s %s %d %d\n", optr[i].id, optr[i].no, optr[i].ad, optr[i].soyad, optr[i].topders, optr[i].kredi);
			}
		}
	}
	
	else{
		printf("bu koda sahip ders bulunmamaktadýr.\n");
	}
	fclose(liste);
	free(kptr);
	free(optr);
}

void hoca_dersler(){
	FILE *liste=fopen("hocalar.txt","r");
	OGRETMEN hoca;
	int a=0,id,i;
	DERS *dptr;
	OGRETMEN *optr;
	
	optr=(OGRETMEN*)malloc(1*sizeof(OGRETMEN));
	
	printf("mevcut ogretim gorevlileri:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRETMEN*)realloc(optr,a*sizeof(OGRETMEN));
		fscanf(liste,"%d %s %s %s\n", &optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		printf("%d %s %s %s\n", optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		
	}
	fclose(liste);
	printf("\nverdigi dersleri listelemek icin ogretim gorevlisinin id sini giriniz: ");
	scanf("%d",&id);
	
	liste=fopen("dersler.txt","r");
	dptr=(DERS*)malloc(1*sizeof(DERS));
	a=0;
	printf("verdigi dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
	}
	
	for(i=0;i<a;i++){
		if(dptr[i].ortid==id){
			printf("%s\n", dptr[i].kodu);
		}
	}
	
	fclose(liste);
	free(optr);
	free(dptr);
}

void dersi_alanlar(){
	FILE *liste=fopen("dersler.txt","r");
	DERS drs;
	int a=0,i;
	char kod[10];
	char kayitli[10]="KAYITLI";
	KAYIT *kptr;
	DERS *dptr;
	
	dptr=(DERS*)malloc(1*sizeof(DERS));
	
	printf("mevcut dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
		printf("%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, dptr[a-1].drskredi, dptr[a-1].kontenjan, dptr[a-1].ortid);
		
	}
	fclose(liste);
	printf("\ndersi alanlari gormek icin ders kodunu giriniz: ");
	scanf("%s",kod);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	a=0;
	printf("dersi alanlar:\n");
	while(!feof(liste)){
		a++;
		kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
		
	}
	
	for(i=0;i<a;i++){
		if(!strcmp(kptr[i].derskod,kod) && !strcmp(kptr[i].kayit_birak,kayitli)){
			printf("%s\n",kptr[i].ogrencino);
		}
	}
	
	fclose(liste);
	free(dptr);
	free(kptr);
}

void ogrenci_dersler(){
	FILE *liste=fopen("ogrenciler.txt","r");
	OGRENCI ogr;
	int a=0,i;
	char no[10];
	char kayitli[10]="KAYITLI";
	KAYIT *kptr;
	OGRENCI *optr;
	
	optr=(OGRENCI*)malloc(1*sizeof(OGRENCI));
	
	printf("mevcut ogrenciler:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRENCI*)realloc(optr,a*sizeof(OGRENCI));
		fscanf(liste,"%d %s %s %s %d %d\n", &optr[a-1].id, optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, &optr[a-1].topders, &optr[a-1].kredi);
		printf("%s %s %s %d %d\n", optr[a-1].no, optr[a-1].ad, optr[a-1].soyad, optr[a-1].topders, optr[a-1].kredi);
		
	}
	
	printf("\naldigi dersleri gormek icin ogrencinin numarasini giriniz: ");
	scanf("%s",no);
	fclose(liste);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	a=0;
	printf("aldigi dersler:\n");
	while(!feof(liste)){
		a++;
		kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
		
	}
	
	for(i=0;i<a;i++){
		if(!strcmp(kptr[i].ogrencino,no) && !strcmp(kptr[i].kayit_birak,kayitli)){
			printf("%s\n",kptr[i].derskod);
		}
	}
	
	fclose(liste);
	free(optr);
	free(kptr);
}

void sinif_listesi(){
	FILE *liste=fopen("hocalar.txt","r");
	OGRETMEN hoca;
	int a=0,id,i;
	char kod[10];
	char kayitli[10]="KAYITLI";
	char liste_adi[20];
	DERS *dptr;
	OGRETMEN *optr;
	KAYIT *kptr;
	
	optr=(OGRETMEN*)malloc(1*sizeof(OGRETMEN));
	
	printf("mevcut ogretim gorevlileri:\n");
	while(!feof(liste)){
		a++;
		optr=(OGRETMEN*)realloc(optr,a*sizeof(OGRETMEN));
		fscanf(liste,"%d %s %s %s\n", &optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		printf("%d %s %s %s\n", optr[a-1].id, optr[a-1].ad, optr[a-1].soyad, optr[a-1].unvan);
		
	}
	fclose(liste);
	printf("\nverdigi dersleri listelemek icin ogretim gorevlisinin id sini giriniz: ");
	scanf("%d",&id);
	
	liste=fopen("dersler.txt","r");
	dptr=(DERS*)malloc(1*sizeof(DERS));
	a=0;
	printf("verdigi dersler:\n");
	while(!feof(liste)){
		a++;
		dptr=(DERS*)realloc(dptr,a*sizeof(DERS));
		fscanf(liste,"%s %s %d %d %d\n", dptr[a-1].kodu, dptr[a-1].adi, &dptr[a-1].drskredi, &dptr[a-1].kontenjan, &dptr[a-1].ortid);
	}
	fclose(liste);
	
	for(i=0;i<a;i++){
		if(dptr[i].ortid==id){
			printf("%s\n", dptr[i].kodu);
		}
	}
	
	printf("\nders seciniz: ");
	scanf("%s",kod);
	
	liste=fopen("OgrenciDersKayit.txt","r");
	kptr=(KAYIT*)malloc(1*sizeof(KAYIT));
	
	a=0;
	while(!feof(liste)){
		a++;
		kptr=(KAYIT*)realloc(kptr,a*sizeof(KAYIT));
		fscanf(liste,"%d %s %s %s\n", &kptr[a-1].id, kptr[a-1].ogrencino, kptr[a-1].derskod, kptr[a-1].kayit_birak);
		
	}
	fclose(liste);
	
	liste_adi[0]='\0';
	strcat(liste_adi,kod);
	strcat(liste_adi,"_SINIFLISTESI.txt");
	
	liste=fopen(liste_adi,"w");
	for(i=0;i<a;i++){
		if(!strcmp(kptr[i].derskod,kod) && !strcmp(kptr[i].kayit_birak,kayitli)){
			fprintf(liste,"%s\n",kptr[i].ogrencino);
		}
	}
	printf("SINIF LISTESI OLUSTURULMUSTUR.\n");
	fclose(liste);
	free(dptr);
	free(kptr);
}


