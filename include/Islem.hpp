/**
* @file 		Islem.hpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#ifndef ISLEM_HPP
#define ISLEM_HPP
#include "Kuyruk.hpp"
#include "Huffman.hpp"
#include "Dugum.hpp"
#include <iostream>

using namespace std;

class Islem{
	public:
		void huffmanYazdir(unsigned char, ofstream &);
		unsigned char huffmanOku(ifstream &);
		void dosyayaYazdir(Huffman *);
		void encoder();
		void decoder();
		void ekranaYaz();
};

#endif