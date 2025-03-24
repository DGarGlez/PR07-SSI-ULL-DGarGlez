#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>



using namespace std;


class Rijndael{

	private:
		unsigned int iteraciones[176];  // Guardamos las iteraciones
	
    	public:
		Rijndael();         // Constructor
		~Rijndael();        // Destructor
		int k;  // Contador iteraciones
		int valorCajaS(int pos);    // Devuelve el valor cajaS
		void expandirClave(unsigned char (*arrClave)[4], unsigned char *mClaveExp); // Expande la clave
		void addRoundKey(int pos, unsigned char (*texto)[4], unsigned char *mClaveExp); // Sumamos cada byte de texto a byte de clave, columna a columna
		void subBytes(unsigned char (*texto)[4]);   // Sustituimos el texto por los valores de cajaS
		void shiftRows(unsigned char (*texto)[4]);  // Rotamos 2a fila un byte, 3a fila dos bytes y 4a fila tres bytes
		void mixColumns(unsigned char (*r)[4]); // Cada columna se multiplica por una matrix dada
		void encriptar(unsigned char (*texto)[4],unsigned char *mClaveExp); // Ciframos el texto
};