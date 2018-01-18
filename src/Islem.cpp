/**
* @file 		Islem.cpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#include "Islem.hpp"				
void Islem::huffmanYazdir(unsigned char i, ofstream & cikisD)  //Verilen bit Bit.dat dosyasina yazilir.
{
    static int bit_konumu=0;  
    static unsigned char c='\0'; //Bit blogunu ifade etmek icin kullanilan degisken

    if(i<2) //Dosya sonu degilse
    {
        if(i==1)
            c=c | (i<<(7-bit_konumu)); //Bit bloguna 1 ekle
        else //i==0
            c=c & static_cast<unsigned char>(255-(1<<(7-bit_konumu))); //Bit bloguna 0 ekle
        ++bit_konumu;
        bit_konumu%=8;
        if(bit_konumu==0)
        {
            cikisD.put(c);
            c='\0';
        }
    }
    else
    {
        cikisD.put(c);
    }
}

void Islem::dosyayaYazdir(Huffman *agc){
	Huffman *agac = agc;
	(*agac).huffmanListe((*agac).get_root(), "");
}

//input : Bitleri okumak icin gereken giris dosyasini parametre olarak alir

unsigned char Islem::huffmanOku(ifstream & girisD)
{
    static int bit_konumu=0;
    static unsigned char c=girisD.get();

    unsigned char i;

    i=(c>>(7-bit_konumu))%2; //Bit blogundan bitleri teker teker alir.
    ++bit_konumu;
    bit_konumu%=8;
    if(bit_konumu==0)
        if(!girisD.eof())
        {
            c=girisD.get();
        }
        else
            i=2;

    return i;     
}

void Islem::encoder()               //Sikistiran fonksiyon
{
    ifstream girisD("Deneme.txt", ios::in|ios::binary);  //Deneme.txt dosyasini binary ve in olarak acar.
    if(!girisD)
    {
        cout<<"Deneme.txt Dosyasi Acilamadi !!!"<<endl;  //Acilmadigi halde hata ver
        exit(1);
    }

    ofstream cikisD("Bit.dat", ios::out|ios::binary);   //Cikis dosyasini acar
    if(!cikisD)
    {
        cout<<"Bit.dat Dosya zaten var !!!"<<endl;    
        exit(1);
    }

    unsigned int f[256];    //Tablodaki ASCII karakterlerinin frekanslarini tutmaya yarayan dizi.
    for(int i=0;i<256;++i)
        f[i]=0;

    //read the whole file and count the ASCII char table frequencies
    char c;
    unsigned char ch;
    while(girisD.get(c))  //Butun dosya okunur ve ASCII karakterlerin frekanslarinin degeri yazilir. 
    {
        ch=c;
        ++f[ch];
    }
	
	
    girisD.clear(); 
    girisD.seekg(0); 

	
    Kuyruk gecici(3);         //3 Elemanli bir Kuyruk Olusturulur.
    Huffman* agac;

    for(int i=0;i<256;++i)
    {
        //char Frekanslarini cikis dosyasina yazar
        cikisD.put(static_cast<unsigned char>(f[i]>>24));
        cikisD.put(static_cast<unsigned char>((f[i]>>16)%256));
        cikisD.put(static_cast<unsigned char>((f[i]>>8)%256));
        cikisD.put(static_cast<unsigned char>(f[i]%256));
 
        if(f[i]>0)
        {
            agac=new Huffman;
            (*agac).set_freq(f[i]);
            (*agac).set_char(static_cast<unsigned char>(i));
            gecici.enq(agac);
        }
    }
	
    Huffman* agac2;
    Huffman* agac3;

    do
    {
        agac=gecici.deq();
        if(!gecici.Bosmu())
        {
            agac2=gecici.deq();
            agac3=new Huffman;       
            (*agac3).set_freq((*agac).get_freq()+(*agac2).get_freq());   //En dusuk 2 frekansli agaci alip yedek bir agacta birlesitirir.
            (*agac3).set_sol((*agac).get_root());
            (*agac3).set_sag((*agac2).get_root());
            gecici.enq(agac3);
        }
    }
    while(!gecici.Bosmu()); //Butun alt agaclar birlesene kadar devam eder.

    string H_table[256];
    unsigned char uc;
    for(unsigned short us=0;us<256;++us)
    {
        H_table[us]="";
        uc=static_cast<unsigned char>(us);
        (*agac).huf((*agac).get_root(), uc, "", H_table[us]);  //Huffman kodlarını char olarak geri dondurur.
    }
	
	dosyayaYazdir(agac);  //Huffman agacindaki butun kodlari alir. Tablo.txt'ye yerlestirir.
	
    unsigned char ch2;
    while(girisD.get(c))
    {
        ch=c; 
        for(unsigned int i=0;i<H_table[ch].size();++i)  //Bit-bit okunuyor
        {
            if(H_table[ch].at(i)=='0')
                ch2=0;
            if(H_table[ch].at(i)=='1')
                ch2=1;
            huffmanYazdir(ch2, cikisD);
        }
    }
    ch2=2;
    huffmanYazdir(ch2, cikisD);

    girisD.close();
    cikisD.close();

} 


void Islem::decoder()
{
    ifstream girisD("Bit.dat", ios::in|ios::binary);  //Bit.dat dosyasi binary olarak acilir.
    if(!girisD)
    {
        cout<<"Bit.dat Acilamadi !!!"<<endl;
        exit(1);
    }

    ofstream cikisD("genisletilmis.txt", ios::out|ios::binary); //genisletilmis.txt dosyasi acilir.
    if(!cikisD)
    {
        cout<<"genisletilmis.txt Acilamadi!!!"<<endl;
        exit(1);
    }

    //Frekans tablosunu Giris dosyasinden okur.
    unsigned int f[256];
    char c;
    unsigned char ch;
    unsigned int j=1;
    for(int i=0;i<256;++i)
    {
        f[i]=0;
        for(int k=3;k>=0;--k)
        {
            girisD.get(c);
            ch=c;
            f[i]+=ch*(j<<(8*k));
        }
    }

    Kuyruk gecici(3); //Yeniden 3 elemanli bir kuyruk olusturulur.
    Huffman* agac;

    for(int i=0;i<256;++i)
    {
        if(f[i]>0)
        {
            agac=new Huffman;
            (*agac).set_freq(f[i]);
            (*agac).set_char(static_cast<unsigned char>(i));
            gecici.enq(agac);
        }
    }

    Huffman* agac2;
    Huffman* agac3;

    do
    {
        agac=gecici.deq();
        if(!gecici.Bosmu())
        {
            
            agac2=gecici.deq();
            agac3=new Huffman;
            (*agac3).set_freq((*agac).get_freq()+(*agac2).get_freq());      //En dusuk 2 frekansli agaci alip yedek bir agacta birlesitirir.
            (*agac3).set_sol((*agac).get_root());
            (*agac3).set_sag((*agac2).get_root());
            gecici.enq(agac3);
        }
    }
    while(!gecici.Bosmu());  //Butun alt agaclar birlesene kadar devam eder.

    //Huffman kodlarini okur.
    //Karakterleri bulur ve huffman kodlari ile karsilastirarak cikis dosyasina yazar.
    string st;
    unsigned char ch2;
    unsigned int toplam_char=(*agac).get_freq();
	
    while(toplam_char>0) //Tum karakterler genisletilene edilene kadar devam eder.
    {
        st=""; //Anlik huffman kodunu tutan degisken.
        do
        {
            //Huffman stringlerini (kodlarini) bit-bit okur.
            ch=huffmanOku(girisD);
            if(ch==0)
                st=st+'0';
            if(ch==1)
                st=st+'1';
        } 
        while(!(*agac).huffmanListeVarmi(st, ch2));       //Karakter bulunana kadar devam eder.
        cikisD.put(static_cast<char>(ch2));
        --toplam_char;
    }

    girisD.close();
    cikisD.close();

} 
void Islem::ekranaYaz(){
	ifstream yaz;
	string satir;
	yaz.open("genisletilmis.txt");
	while(getline(yaz,satir))  //Satir satir okur ve ekrana yazar.
	{
		cout<<satir<<endl;
	}
}