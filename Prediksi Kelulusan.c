#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define nil NULL
#define info(P) (P)->info
#define nextA(P) (P)->nextA
#define nextO(P) (P)->nextO
#define first(L) (L).first
#define head(L) (L).head
#define nMax 10

typedef struct{
	float T[nMax+1];
	int neff;
}Tabel;

typedef struct tElmNilai *addressN;

typedef struct tElmNilai{
	float info;
	addressN nextA;
}ElmNilai;

typedef struct{
	addressN head;
}ListNilai;

typedef struct{
	char Nama[30];
	char Nim[3];
	int Status;
	float jarak;
}Data;

typedef struct tElmMh *addressMh;

typedef struct tElmMh{
	Data info;
	addressN nextA;
	addressMh nextO;
}ElmMh;

typedef struct{
	addressMh first;
}ListMh;

//Prototype
void CreateListMh(ListMh *Lm);
void CreateListN(ListNilai *Ln);
void CreateTab(Tabel *T);
void AddListMh(ListMh *Lm, Data D, ListNilai Ln);
void AddListNilai(ListNilai *Ln, float x);
void CetakList(ListMh Lm);
void AddTabNilai(Tabel *T, float x);
Tabel GetJarak(ListMh Lm, Tabel T);
void KillAll(ListMh *Lm);
void BubbleSort(ListMh *Lm);
int Prediksi(ListMh Lm, int k);
void CetakAll(ListMh Lm);
addressMh AlokasiMh(Data D);
addressN AlokasiNilai(float x);
void DeAlokasiAnak(addressN Del);
void DeAlokasiOrtu(addressMh Del);


int main(){
	//Kamus
	float x;
	ListMh MyList;
	Data MD, D;
	ListNilai MyNilai;
	Tabel MyTab, Jarak;
	FILE *in=fopen("Data.txt","r"), *in2=fopen("Data2.txt","r");
	int i, k;
	
	//Algoritma
	CreateListMh(&MyList);
	if(!in){
		printf("Tidak Ada File");
	}else{
		while(!feof(in)){
			fscanf(in,"%[^#]#", &D.Nim);fflush(stdin);
			fscanf(in,"%[^#]#", &D.Nama);fflush(stdin);
			fscanf(in,"%d#", &D.Status);fflush(stdin);
			CreateListN(&MyNilai);
			for(i=1;i<=3;i++){
				fscanf(in,"%f#", &x);fflush(stdin);
				AddListNilai(&MyNilai,x);
			}
			AddListMh(&MyList,D,MyNilai);
			fscanf(in,"\n");fflush(stdin);
		}
		fclose(in);
	}
	
	CetakList(MyList);
	
	printf("Masukkan Nama = "), gets(MD.Nama);
	printf("Masukkan Nim  = "), gets(MD.Nim);
	
	CreateTab(&MyTab);
	for(i=1;i<=3;i++){
		printf("Masukkan Nilai ke %d = ",i), scanf("%f",&x);
		AddTabNilai(&MyTab,x);
	}
	
	Jarak=GetJarak(MyList,MyTab);
	
	KillAll(&MyList);
	
	CreateListMh(&MyList);
	if(!in2){
		printf("Tidak Ada File");
	}else{
		while(!feof(in2)){
			fscanf(in2,"%d#",&i);fflush(stdin);
			fscanf(in2,"%[^#]#", &D.Nim);fflush(stdin);
			fscanf(in2,"%[^#]#", &D.Nama);fflush(stdin);
			fscanf(in2,"%d#", &D.Status);fflush(stdin);
			D.jarak=Jarak.T[i];
			CreateListN(&MyNilai);
			for(i=1;i<=3;i++){
				fscanf(in2,"%f#", &x);fflush(stdin);
				AddListNilai(&MyNilai,x);
			}
			AddListMh(&MyList,D,MyNilai);
			fscanf(in2,"\n");fflush(stdin);
		}
		fclose(in2);
	}
	BubbleSort(&MyList);
	
	CetakAll(MyList);
	
	printf("Input K = "), scanf("%d",&k);
	
	printf("==================================================================================\n");
	printf("No\tNIM\tNama\t\tNilai 1\tNilai 2\tNilai 3\tSTATUS\n");
	printf("==================================================================================\n");
	printf("1\t%s\t%s\t\t%.0f\t%.0f\t%.0f\t",MD.Nim,MD.Nama,MyTab.T[1],MyTab.T[2],MyTab.T[3]);
	
	if(Prediksi(MyList,k)==1){
		printf("LULUS");
	}else{
		printf("TIDAK LULUS");
	}

	printf("\n==================================================================================\n");
	
	
	return 0;
}

//Body of Prototype
void CreateListMh(ListMh *Lm){
	first(*Lm)=nil;
}

void CreateListN(ListNilai *Ln){
	head(*Ln)=nil;
}

void CreateTab(Tabel *T){
	(*T).neff=0;
}

void AddListMh(ListMh *Lm, Data D, ListNilai Ln){
	//Kamus
	addressMh Ao, P;
	
	//Algoritma
	Ao=first(*Lm);
	P=AlokasiMh(D);
	nextA(P)=head(Ln);
	if(Ao==nil){
		first(*Lm)=P;
	}else{
		while(nextO(Ao)!=nil){
			Ao=nextO(Ao);
		}
		nextO(Ao)=P;
	}
}

void AddListNilai(ListNilai *Ln, float x){
	//Kamus
	addressN Aa, P;
	
	//Algoritma
	Aa=head(*Ln);
	P=AlokasiNilai(x);
	if(Aa==nil){
		head(*Ln)=P;
	}else{
		while(nextA(Aa)!=nil){
			Aa=nextA(Aa);
		}
		nextA(Aa)=P;
	}
}

void CetakList(ListMh Lm){
	//Kamus
	addressMh Ao;
	addressN Aa;
	Data D;
	int i;
	
	//Algoritma
	Ao=first(Lm);
	i=0;
	printf("==================================================================================\n");
	printf("No\tNIM\tNama\t\tNilai 1\tNilai 2\tNilai 3\tSTATUS\n");
	printf("==================================================================================\n");
	while(Ao!=nil){
		i++;
		printf("%d\t", i);
		D=info(Ao);
		printf("%s\t",D.Nim);
		printf("%s\t",D.Nama);
		Aa=nextA(Ao);
		while(Aa!=nil){
			printf("%.0f\t",info(Aa));
			Aa=nextA(Aa);
		}
		if(D.Status==1){
			printf("LULUS");
		}else{
			printf("TIDAK LULUS");
		}
		printf("\n");
		Ao=nextO(Ao);
	}
	printf("==================================================================================\n");
}

void AddTabNilai(Tabel *T, float x){
	if((*T).neff<nMax){
		(*T).neff++;
		(*T).T[(*T).neff]=x;
	}
}

Tabel GetJarak(ListMh Lm, Tabel T){
	//Kamus
	Tabel J;
	float jarak, x;
	addressMh Ao;
	addressN Aa;
	int i;
	
	//Algoritma
	Ao=first(Lm);
	CreateTab(&J);
	while(Ao!=nil){
		i=0;
		jarak=0;
		Aa=nextA(Ao);
		while(Aa!=nil){
			i++;
			x=T.T[i]-info(Aa);
			x=pow(x,2);
			jarak=jarak+x;
			Aa=nextA(Aa);
		}
		jarak=sqrt(jarak);
		AddTabNilai(&J,jarak);
		Ao=nextO(Ao);
	}
	
	return J;
}

void KillAll(ListMh *Lm){
	//Kamus
	addressMh Ao, delO;
	addressN Aa, delA;
	
	//Algoritma
	Ao=first(*Lm);
	while(Ao!=nil){
		Aa=nextA(Ao);
		while(nextA(Ao)!=nil){
			nextA(Ao)=nextA(Aa);
			delA=Aa;
			Aa=nextA(Aa);
			DeAlokasiAnak(delA);
		}
		first(*Lm)=nextO(Ao);
		delO=Ao;
		DeAlokasiOrtu(delO);
		Ao=nextO(Ao);
	}
}

void DeAlokasiAnak(addressN Del){
	free(Del);
}

void DeAlokasiOrtu(addressMh Del){
	free(Del);
}

void BubbleSort(ListMh *Lm){
	//Kamus
	addressMh Aa, sort, cek;
	Data x, y, tmp;
	ListNilai Ln;
	
	//Algoritma
	Aa=first(*Lm);
	while(Aa!=nil){
		sort=first(*Lm);
		cek=nextO(sort);
		while(cek!=nil){
			x=info(sort);
			y=info(cek);
			if(x.jarak>y.jarak){
				head(Ln)=nextA(cek);
				tmp=info(cek);
				info(cek)=info(sort);
				info(sort)=tmp;
				nextA(cek)=nextA(sort);
				nextA(sort)=head(Ln);
			}
			sort=nextO(sort);
			cek=nextO(cek);
		}
		Aa=nextO(Aa);
	}
}

int Prediksi(ListMh Lm, int k){
	//Kamus
	addressMh Ao;
	Data D;
	int i, L, TL;
	
	//Algoritma
	Ao=first(Lm);
	i=0;
	L=0;
	TL=0;
	while(Ao!=nil && i!=k){
		i++;
		D=info(Ao);
		if(D.Status==1){
			L++;
		}else{
			TL++;
		}
		Ao=nextO(Ao);
	}
	if(L>TL){
		return 1;
	}else{
		return 0;
	}
}

void CetakAll(ListMh Lm){
	//Kamus
	addressMh Ao;
	addressN Aa;
	Data D;
	int i;
	
	//Algoritma
	Ao=first(Lm);
	i=0;
	printf("==================================================================================\n");
	printf("No\tNIM\tNama\t\tNilai 1\tNilai 2\tNilai 3\tSTATUS\t\tJARAK\n");
	printf("==================================================================================\n");
	while(Ao!=nil){
		i++;
		printf("%d\t", i);
		D=info(Ao);
		printf("%s\t",D.Nim);
		printf("%s\t",D.Nama);
		Aa=nextA(Ao);
		while(Aa!=nil){
			printf("%.0f\t",info(Aa));
			Aa=nextA(Aa);
		}
		if(D.Status==1){
			printf("LULUS\t");
		}else{
			printf("TIDAK LULUS");
		}
		printf("\t%.2f",D.jarak);
		printf("\n");
		Ao=nextO(Ao);
	}
	printf("==================================================================================\n");
}

addressMh AlokasiMh(Data D){
	//Kamus
	addressMh Px;
	
	//Algoritma
	Px=(addressMh)malloc(sizeof(ElmMh));
	info(Px)=D;
	nextA(Px)=nil;
	nextO(Px)=nil;
	
	return Px;
}

addressN AlokasiNilai(float x){
	//Kamus
	addressN Px;
	
	//Algoritma
	Px=(addressN)malloc(sizeof(ElmNilai));
	info(Px)=x;
	nextA(Px)=nil;
	
	return Px;
}
