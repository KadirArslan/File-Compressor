hepsi: derle calistir
derle:
	g++ -I ./include/ -o ./lib/Dugum.o -c ./src/Dugum.cpp
	g++ -I ./include/ -o ./lib/Huffman.o -c ./src/Huffman.cpp
	g++ -I ./include/ -o ./lib/Kuyruk.o -c ./src/Kuyruk.cpp
	g++ -I ./include/ -o ./lib/Islem.o -c ./src/Islem.cpp
	g++ -I ./include/ -o ./bin/Test ./lib/Dugum.o ./lib/Huffman.o ./lib/Kuyruk.o ./lib/Islem.o ./src/Main.cpp
calistir:
	./bin/Test