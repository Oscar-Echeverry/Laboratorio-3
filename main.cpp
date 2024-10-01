#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

void Problema1();
void Problema2();
string metodo1(string texto, int semilla);
string metodo2(string texto, int semilla);

int main()
{
    int opcion = 1;
    cout << "Bienvenido a la practica 3" << endl;
    while (opcion != 0)
    {
        cout << "\n";
        cout << "=============================\n";
        cout << "        MENU PRINCIPAL        \n";
        cout << "=============================\n";
        cout << "1. Programa para codificar archivos de texto\n";
        cout << "2. Programa para decodificar el archivo.\n";
        cout << "0. Salir\n";
        cout << "=============================\n";
        cout << "Por favor ingresa la opcion" << endl;
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ejecutando el problema 1 ..." << endl;
            Problema1();
            break;
        case 2:
            cout << "Ejecutando el problema 2 ..." << endl;
            Problema2();
            break;
        default:
            if (opcion != 0)
                cout << "Opcion no valida" << endl;
            cout << "\n";
            cout << "*****************************************\n";
            cout << "*               GRACIAS                *\n";
            cout << "*                                     *\n";
            cout << "*           Echo por Oscar Echeverry   *\n";
            cout << "*                                     *\n";
            cout << "*****************************************\n";
            break;
        }
    }
    return 0;
}

void Problema1() {
    ofstream fout;
    ifstream fin;
    string archivoEntrada, archivoSalida;
    string texto;
    int semilla, metodo;

    cout << "Ingrese el nombre del archivo a codificar: ";
    cin >> archivoEntrada;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> archivoSalida;
    cout << "Ingrese la semilla de codificacion (numero entero): ";
    cin >> semilla;
    cout << "Seleccione el metodo de codificacion (1 o 2): ";
    cin >> metodo;

    try {
        fin.open(archivoEntrada);
        if (!fin.is_open()) {
            throw '1';  // Error al abrir archivo
        }
        // Leer el contenido del archivo
        string linea;
        while (getline(fin, linea)) {
            texto += linea + "\n";
        }
        fin.close();

        if (texto.empty()) {
            throw '4';  // El archivo está vacío
        }

        // Codificación del texto
        string textoCodificado;
        if (metodo == 1) {
            textoCodificado = metodo1(texto, semilla);
        } else if (metodo == 2) {
            textoCodificado = metodo2(texto, semilla);
        } else {
            throw '3';  // Método de codificación no válido
        }

        fout.open(archivoSalida);
        if (!fout.is_open()) {
            throw '2';  // Error al abrir archivo de salida
        }

        fout << textoCodificado;
        fout.close();

        cout << "Archivo codificado y guardado exitosamente en " << archivoSalida << endl;

    } catch (char err) {
        if (err == '1') {
            cout << "Error al abrir el archivo de entrada." << endl;
        } else if (err == '2') {
            cout << "Error al abrir el archivo de salida." << endl;
        } else if (err == '3') {
            cout << "Metodo de codificacion no valido." << endl;
        } else if (err == '4') {
            cout << "El archivo de entrada esta vacio. No se puede codificar." << endl;
        } else {
            cout << "Se produjo un error inesperado." << endl;
        }
    }
}

void Problema2() {
    cout << "Funcion de decodificacion." << endl;
}

string metodo1(string texto, int semilla) {
    string textoBinario = "";
    for (char c : texto) {
        textoBinario += bitset<8>(c).to_string();
    }
    string textoCodificado = "";
    for (size_t i = 0; i < textoBinario.size(); i += semilla) {
        string bloque = textoBinario.substr(i, semilla);
        if (i == 0) {
            // Invertir bits del primer bloque
            for (char &bit : bloque) {
                bit = (bit == '0') ? '1' : '0';
            }
        } else {
            string bloqueAnterior = textoBinario.substr(i - semilla, semilla);
            int unos = count(bloqueAnterior.begin(), bloqueAnterior.end(), '1');
            int ceros = count(bloqueAnterior.begin(), bloqueAnterior.end(), '0');

            if (unos == ceros) {
                for (char &bit : bloque) {
                    bit = (bit == '0') ? '1' : '0';
                }
            } else if (ceros > unos) {
                for (size_t j = 0; j < bloque.size(); j += 2) {
                    bloque[j] = (bloque[j] == '0') ? '1' : '0';
                }
            } else {
                for (size_t j = 0; j < bloque.size(); j += 3) {
                    bloque[j] = (bloque[j] == '0') ? '1' : '0';
                }
            }
        }
        textoCodificado += bloque;
    }
    return textoCodificado;
}
string metodo2(string texto, int semilla) {

    return texto; // Implementación placeholder

}
