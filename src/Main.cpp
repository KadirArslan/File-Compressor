/**
* @file 		Main.cpp
* @description 	Huffman algoritmasi ile verilen txt'yi sikistirir.
* @author 		Kadir ARSLAN <kadir.arslan1@ogr.sakarya.edu.tr>  /  Cahit TULUM <cahit.tulum@ogr.sakarya.edu.tr>
**/

#include "Islem.hpp"

int main()
{
    Islem *islemler = new Islem();
	int secim;
	char yaz;
	cout<<"1.Dosya sikistir"<<endl<<"2.Sikistirilmis dosyayi ekrana yaz"<<endl<<"Seciminiz: ";
	cin>>secim;
	switch (secim)
	{
		case 1:
			cout<<"-------~~~~~~~~~~~------- Sikistirma islemi basladi -------~~~~~~~~~~~-------"<<endl;
			islemler->encoder();
			cout<<"..."<<endl<<".."<<endl;
			cout<<"Dosya basariyla sikistirildi.";
			break;
		case 2:
			cout<<"-------~~~~~~~~~~~------- Genisletme islemi basladi -------~~~~~~~~~~~-------"<<endl;
			islemler->decoder();
			cout<<"Genisletilen dosya ekrana yazilsin mi?  (Evet: e / Hayir : h)"<<endl<<"Secim: ";
			cin>>yaz;
			if(yaz == 'e')
				islemler->ekranaYaz();
			else
				break;
			break;
		default:
			cout<<"Yanlis bir secim yaptiniz!";
			break;
	}
	
	delete islemler;
    return 0;
}