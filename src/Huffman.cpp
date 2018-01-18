/**
* @file 		Huffman.cpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#include "Huffman.hpp"

//Kurucu
Huffman::Huffman(void)
{
    Dugum* N=new Dugum;
    root=N;
}

//Tum Huffman'i silmek icin yinelemeli fonksiyon
void Huffman::Temizle(Dugum *N)
{
    if(N)
    {
        Temizle(N->sol);
        Temizle(N->sag);
        delete N;
    }
}

//Huffman Yikici Fonksiyonu
Huffman::~Huffman(void)
{
    Temizle(root);
}

unsigned int Huffman::get_freq(void) const
{
    return root->freq;
}

unsigned char Huffman::get_char(void) const
{
    return root->ch;
}

void Huffman::set_freq(unsigned int f)
{
    root->freq=f;
}

void Huffman::set_char(unsigned char c)
{
    root->ch=c;
}

Dugum* Huffman::get_sol(void) const
{
    return root->sol;
}

Dugum* Huffman::get_sag(void) const
{
    return root->sag;
}

void Huffman::set_sol(Dugum* N)
{
    root->sol=N;
}

void Huffman::set_sag(Dugum* N)
{
    root->sag=N;
}

Dugum* Huffman::get_root(void) const
{
    return root;
}

//Huffman Agacini ekrana yazar
void Huffman::Yaz(Dugum * curr, int level) const
{
    if(curr)
    {
        Yaz(curr->sag,level+1); 
        cout<<setw(level*5)<<karakterYaz(curr)<<":"
            <<curr->freq<<endl;
        Yaz(curr->sol,level+1); 
    }
}

bool Huffman::operator==(const Huffman & T) const
{
    return (root->freq == T.root->freq);    
}

bool Huffman::operator!=(const Huffman & T) const
{
    return (root->freq != T.root->freq);    
}

bool Huffman::operator<(const Huffman & T) const
{
    return (root->freq < T.root->freq);    
}

bool Huffman::operator>(const Huffman & T) const
{
    return (root->freq > T.root->freq);    
}

bool Huffman::operator<=(const Huffman & T) const
{
    return (root->freq <= T.root->freq);    
}

bool Huffman::operator>=(const Huffman & T) const
{
    return (root->freq >= T.root->freq);    
}

//Ozyinelemeli string(kod) bulan fonksiyon
void Huffman::huf(Dugum* N, unsigned char c, string str, string & s) const
{
    if(N) //Dugum NULL Degil ise devam et
    {
        if(!N->sol && !N->sag && N->ch == c)
        {
            s=str; //Yapraksa Kod'u al
        }
        else
        {
            //Eger Yaprak degilse aramaya devam et.
            huf(N->sol, c, str+"0",s);
            huf(N->sag, c, str+"1",s);
        }
    }
}

void Huffman::huffmanListe(Dugum* N, string str) const  //Tablo Olusturur.
{
	fstream kadir;										//fstream kutuphanesinden nesne olusturuldu.
	kadir.open("Tablo.txt",ios::app);                   //Tablo.txt adinda ve ustune yazilabilecek sekilde acildi
    if(N) //Dugum NULL degilse devam et
    {
        if(!N->sol && !N->sag)
		{			//Yaprak mı kontrolu
			string cahit = karakterYaz(N);
			if(cahit == "/040")
				kadir<<"@"<<" "<<str<<endl;
			else if(cahit=="/012"||cahit=="/015")
				kadir<<">"<<" "<<str<<endl;
			else
				kadir<<cahit<<" "<<str<<endl;
		} 
		else
        {
            //Yaprak degilse devam ediyor.
            huffmanListe(N->sol, str+"0");
            huffmanListe(N->sag, str+"1");
        }
    }
}


//Karakter bulur.
bool Huffman::huffmanListeVarmi(string s, unsigned char & c) const
{
    Dugum * curr=root;
    for(unsigned int i=0;i<s.size();++i)
    {
        if(s[i]=='0') //Huffman Agacinda Sola git
            curr=curr->sol;
        if(s[i]=='1') // Huffman Agacinda Saga Git
            curr=curr->sag;
    }

    bool found=false;

    if(!curr->sol && !curr->sag) //Eger yapraksa devam et
    {
        found=true;
        c=curr->ch;
    }

    return found;
}

string Huffman::karakterYaz(Dugum * N) const
{
    string s="";

    if(!N->sol && !N->sag) // Eger yapraksa devam et
    {
        unsigned char c=N->ch;

        //Octal turunden ASCII kod
        if(iscntrl(c) || c==32) //32:blank char
        {
            //3 Basamak olacak sekilde char karakterlerini donusturur.
            char* cp=new char;
            for(int i=0;i<3;++i)
            {
                sprintf(cp,"%i",c%8);
                c-=c%8;
                c/=8;
                s=(*cp)+s;
            }
            s='/'+s; // Octal kodun karsısına ekler.
        }
        else
            s=c;
    }
    return s;
}