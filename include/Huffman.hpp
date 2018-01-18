/**
* @file 		Huffman.hpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "Dugum.hpp"
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip> 
#include<cctype>  //Gerekli Kutuphaneler Eklendi

using namespace std;

class Huffman
{
    private:
        Dugum *root;
		
        Huffman(const Huffman &); //Kurucu Fonksiyon
        const Huffman & operator=(const Huffman &); //Operator overloading
        void Temizle(Dugum * N); //Agacı yok eden fonksiyon
        void Yaz(Dugum *, int) const; //ağacı olusturan fonksiyon

    public:
        Huffman(void); //Kurucu Fonksiyon
        ~Huffman(void); //Yikici Fonksiyon
        friend ostream & operator<<(ostream &, const Huffman &);
        unsigned int get_freq(void) const;   //Sinifa ait Private alanlara erişmek için kullanilan fonksiyonlar
        unsigned char get_char(void) const;
        void set_freq(unsigned int);
        void set_char(unsigned char);
        Dugum* get_sol(void) const;
        Dugum* get_sag(void) const;
        void set_sol(Dugum *);
        void set_sag(Dugum *);
        Dugum* get_root(void) const;
    
        bool operator==(const Huffman &) const;
        bool operator!=(const Huffman &) const;
        bool operator<(const Huffman &) const;
        bool operator>(const Huffman &) const;
        bool operator<=(const Huffman &) const;
        bool operator>=(const Huffman &) const;     //Operator overloading

        void huf(Dugum *, unsigned char, string, string &) const;  //Huffman kodlarını char olarak geri dondurur.

        void huffmanListe(Dugum *, string) const;  //Huffman kodlarını eslestirir.
    
        bool huffmanListeVarmi(string, unsigned char &) const; //Eger huffman agacinda verilen deger varsa Bool  deger dondurur.
        string karakterYaz(Dugum *) const; //Karakterleri Yazar.
};

#endif