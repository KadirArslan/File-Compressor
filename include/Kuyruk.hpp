#ifndef KUYRUK_HPP
/**
* @file 		Kuyruk.hpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#define KUYRUK_HPP

#include "Huffman.hpp"
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip> //for width()
#include<cctype> //for sprintf()

using namespace std;

class Kuyruk
{
	private:
        int arka; //Kuyruktaki son elemani gosteren pointer.
        Huffman **dizi; //Dinamik Huffman dizisi.
        int boyut; //Kuyrugun anlik boyutu;
        static const int BOYUT=10;
        int cocuk; //Bir ebeveynin sahip olabilicegi maximum cocuk sayisi.
        Kuyruk(const Kuyruk &); //Private alanda gizlenmiş yapici fonksiyon.
        const Kuyruk & operator=(const Kuyruk &);
        //Bir eleman eklendiginde veya cikartildiginda calisacak fonksiyonlar.
        void heapYukari(int, int);
        void heapAsagi(int, int);
        void degistir(Huffman *&, Huffman *&); //Cocuklari ahreket ettirirken gerekirse swap fonksiyonu cagirilir.

    public:
        Kuyruk(int d=2); //Yapici fonksiyon 
        ~Kuyruk(void); //Yikici fonksiyon
        void enq(Huffman*); //Kuyruga eleman eklemek icin kullanilan fonksiyon.
        Huffman* deq(void); //Kuyruktan eleman cikartmak icin kullanilan fonksiyon.
		Huffman* On(void); //En bastaki elemani donduren fonksiyon.
        bool Bosmu(void) const; //Kuyrugun bos olup olmadigini kontrol eden fonksiyon.
        bool Dolumu(void) const; //Kuyrugun dolup dolmadigini kontrol eden fonksiyon.
};

#endif