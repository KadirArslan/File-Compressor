/**
* @file 		Kuyruk.cpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#include "Kuyruk.hpp"

Kuyruk::Kuyruk(int cck)		//Yapici fonksiyon yeni bir kuyruk olusutur.
{
    if(cck<2) cck=2; //En kucuk 2 cocuk olmalı.
    cocuk = cck;
    arka=0;
    boyut=BOYUT;
    dizi = new Huffman*[boyut];
}

bool Kuyruk::Bosmu(void) const
{
    return (arka<=0);		//Kuyruk bos mu onu kontrol eder.
}

bool Kuyruk::Dolumu(void) const
{
    return (arka>=boyut);	//Dolulugu kontrol eder.
}

Huffman* Kuyruk::deq(void)			//Ondeki elemani cikartan fonksiyon.
{
    if(Bosmu())		//Kuyruk bos ise hata verir.
    {
        cout<<"Kuyruk bos!"<<endl;
        exit(1);
    }

    Huffman* deger=dizi[0];
    dizi[0]=dizi[arka-1]; //Arkadaki eleman one dogru hareket eder.
    --arka;
    heapAsagi(0, arka-1); 
    return deger;
}

Huffman* Kuyruk::On(void)
{
    if(Bosmu())
    {
        cout<<"Kuyruk bos!"<<endl;
        exit(1);
    }

    return dizi[0];
}

void Kuyruk::enq(Huffman* foo)			//Kuyuruga yeni eleman ekler.
{
    if(Dolumu()) //Eger dizi doluysa daha buyugunu yapar.
    {
        int nsize=boyut+BOYUT; //Dizinin yeni boyutu.
        Huffman **ndizi=new Huffman*[nsize]; //yeni dizi
        for(int i=0;i<boyut;++i) //eski diziyi yenisine kopyalar.
            ndizi[i]=dizi[i];
        delete[] dizi; //Eski diziyi cop olusmamasi icin siler.
        dizi=ndizi; //pointerlarin gosterdigi yerler guncellenir.
        boyut=nsize; //boyut guncellenir.
    }

    //Yeni eleman kuyrugun sonuna eklendi.
    dizi[arka++]=foo;
    heapYukari(0, arka-1); 
}

void Kuyruk::heapYukari(int kok, int assagi)		//Bu fonksiyon ondeki kuyruk sirasini duzenler ve rekursif olarak calisir.
{
    int ebeveyn;

    if(assagi > kok)
    {
        ebeveyn=(assagi-1)/cocuk;
  
        if(*dizi[ebeveyn] > *dizi[assagi])
        {
            degistir(dizi[ebeveyn], dizi[assagi]);
            heapYukari(kok, ebeveyn);
        }
    }
}

void Kuyruk::heapAsagi(int root, int bottom)					//Bu fonksiyon arkadaki kuyruk sirasini duzenler ve rekursif olarak calisir.
{
    int kucukCocuk, ilkCocuk, Cocuk;

    ilkCocuk=root*cocuk+1; //Ilk cocugun pozisyonu verildi.

    if(ilkCocuk <= bottom)
    {
        kucukCocuk=ilkCocuk; //ilk cocuk en kucuk cocuktur.

        for(int i=2;i <= cocuk;++i)
        {
            Cocuk=root*cocuk+i;
            if(Cocuk <= bottom)
            {
                if(*dizi[Cocuk] < *dizi[kucukCocuk])
                {
                    kucukCocuk=Cocuk;
                }
            }
        }
        if(*dizi[root] > *dizi[kucukCocuk])
        {
            degistir(dizi[root], dizi[kucukCocuk]);
            heapAsagi(kucukCocuk, bottom);
        }
    } 
}

void Kuyruk::degistir(Huffman *&a, Huffman *&b)		//Degisecek 2 degiskenin degerleri parametre olarak geldi.
{
    Huffman* c;
    c=a;
    a=b;
    b=c;
}

Kuyruk::~Kuyruk(void)			//Cop olusmamasi icin yikici fonksiyonda dizi silindi.
{
    delete[] dizi;
}