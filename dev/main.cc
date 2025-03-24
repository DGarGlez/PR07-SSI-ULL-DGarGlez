/*
 *
 * REPOSITORIO: https://github.com/DGarGlez/PR07-SSI-ULL-DGarGlez.git
 * 
 */
#include "Rijndael.h"

using namespace std;

int main(){  

	unsigned int* iter;             // Puntero a array de iteraciones
	unsigned char mClaveExp[176];   // Contendra la expansion de clave	
	unsigned char clave[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};    // Clave  ejemplo  
   	unsigned char arrTexto[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff}; // Primer texto a cifrar ejemplo   
    unsigned char arrTexto2[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // Segundo texto a cifrar ejemplo   

    char resp;                  // Respuesta del usuario
	unsigned char texto[4][4];  // Matriz 4x4 con el texto a cifrar
	unsigned char mClave[4][4]; // Matriz 4x4 con la clave a cifrar

    unsigned char iv[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // Vector de inicialización (IV)
	
	system("clear");    // Limpiamos pantalla
                 	
	cout << "********************************************************************************" << endl;
	cout << "*                                 PRÁCTICA CBC                                 *" << endl;
	cout << "********************************************************************************" << endl << endl;
	
	cout << "CLAVE:\t\t";   // Mostramos la clave
	for (int i = 0; i < 16; i++){   // Recorremos la clave
        // Uso printf porque cout no admite %02x, (%02x es para que muestre en hexadecimal)
		printf(" %02x ",clave[i]);
	} 
	cout << "\nTEXTO ORIGINAL 1: ";   // Mostramos el texto original
	for (int i = 0; i < 16; i++){       // Recorremos el texto original
        // Uso printf porque cout no admite %02x, (%02x es para que muestre en hexadecimal) 
		printf(" %02x ",arrTexto[i]);
	}
    cout << "\nTEXTO ORIGINAL 2: ";   // Mostramos el texto original
	for (int i = 0; i < 16; i++){       // Recorremos el texto original
        // Uso printf porque cout no admite %02x, (%02x es para que muestre en hexadecimal) 
		printf(" %02x ",arrTexto2[i]);
	}
  
	cout << "\nDESEA MODIFICAR LOS DATOS:(S/N):";
	cin >> resp;    // SI: S/s NO: N/n
	cin.clear();    // Limpiamos buffer
	fflush(stdin);  // Limpiamos buffer

	if(resp == 's' || resp == 'S') {    // Si la respuesta es S/s

        cout << "CLAVE EN HEXADECIMAL: ";
        for(int i = 0; i < 16; i++){	
            // Uso scanf porque cin no admite %02x, (%02x es para que muestre en hexadecimal)
            scanf("%02x",&clave[i]);
        }
        cin.clear();    // Limpiamos buffer
        fflush(stdin);  // Limpiamos buffer
    
        cout << "TEXTO 1 EN HEXAMECIMAL: ";
        for(int i = 0; i < 16; i++){
            // Uso scanf porque cin no admite %02x, (%02x es para que muestre en hexadecimal)
            scanf("%02x",&arrTexto[i]);
        }
        cin.clear();    // Limpiamos buffer
        fflush(stdin);  // Limpiamos buffer

        cout << "TEXTO 2 EN HEXAMECIMAL: ";
        for(int i = 0; i < 16; i++){
            // Uso scanf porque cin no admite %02x, (%02x es para que muestre en hexadecimal)
            scanf("%02x",&arrTexto2[i]);
        }
        cin.clear();    // Limpiamos buffer
        fflush(stdin);  // Limpiamos buffer
    }
    else if (resp != 'n' && resp != 'N'){    // Si la respuesta no es N/n
        cerr << "\nRESPUESTA INVÁLIDA --> SI: S/s NO: N/n\n" << endl;    // Mostramos mensaje de error
        return 1;   // Salimos del programa
    }
		
	for (int i = 0; i < 4; i++){    // Recorremos la matriz
	    for (int j = 0; j < 4; j++){    // Recorremos la matriz
            mClave[j][i] = clave[i*4 + j]; // Convierte clave a cifrar en una matriz 4X4
        }
    }
	
	for (int i = 0; i < 4; i++){    // Recorremos la matriz
	    for (int j = 0; j < 4; j++){    // Recorremos la matriz
            texto[j][i] = arrTexto[i*4 + j]; // Texto a cifrar en una matriz 4X4
        }
    }

    Rijndael aes; // Creamos un objeto de la clase Rijndael
	aes.expandirClave(mClave, mClaveExp);  // Expandir la clave y guardarla en un array

        // XOR con IV para el primer bloque
        for (int v = 0; v < 4; v++) {
            for (int r = 0; r < 4; r++) {
                texto[v][r] ^= iv[r*4 + v];
            }
        }

        // Ciframos el bloque
        aes.encriptar(texto, mClaveExp);

        cout << "\n********************************************************************************************" << endl;
        cout << "TEXTO CIFRADO 1: ";   // Mostramos el texto cifrado
        for (int z = 0; z < 4; z++){    // Recorremos la matriz
            for (int j = 0; j < 4; j++){    // Recorremos la matriz
                // Uso printf porque cout no admite %02x, (%02x es para que muestre en hexadecimal)
                printf(" %02x ",texto[j][z]);   // Mostramos el texto cifrado
            }
        }

        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                iv[k*4 + j] = texto[j][k];
            }
        }

        Rijndael aes2; // Creamos un objeto de la clase Rijndael
	    aes2.expandirClave(mClave, mClaveExp);  // Expandir la clave y guardarla en un array

        for (int i = 0; i < 4; i++){    // Recorremos la matriz
            for (int j = 0; j < 4; j++){    // Recorremos la matriz
                texto[j][i] = arrTexto2[i*4 + j]; // Texto a cifrar en una matriz 4X4
            }
        }
        // XOR con el bloque cifrado anterior
        for (int v = 0; v < 4; v++) {
            for (int r = 0; r < 4; r++) {
                texto[v][r] ^= iv[r*4 + v];
            }
        }

        // Ciframos el bloque
        aes2.encriptar(texto, mClaveExp);

        cout << "\n********************************************************************************************" << endl;
        cout << "TEXTO CIFRADO 2: ";   // Mostramos el texto cifrado
        for (int z = 0; z < 4; z++){    // Recorremos la matriz
            for (int j = 0; j < 4; j++){    // Recorremos la matriz
                // Uso printf porque cout no admite %02x, (%02x es para que muestre en hexadecimal)
                printf(" %02x ",texto[j][z]);   // Mostramos el texto cifrado
            }
        }
        cout << "\n********************************************************************************************" << endl;        


    }

