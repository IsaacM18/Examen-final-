#include <iostream>
#include <string>
#include <windows.h>  // Necesario para SetConsoleCursorPosition

using namespace std;

const int MAX_VIAJEROS = 100;// se da un maximo de 100 viajeros, ya sea para registrar, borar o consultar 

struct Viajero {
    string cedula;  // Usar cédula como identificador y va a ser como el id, cada opcion se hara con la cedula
    string nombre;
    string direccion;
};

struct Ingreso { 
    string cedulaViajero;
    string fechaIngreso;
    string lugarIngreso;
};

struct Salida {
    string cedulaViajero;
    string fechaSalida;
    string lugarSalida;
};

struct Pais {
    string cedulaViajero;
    string nombrePaisOrigen;
    string nombrePaisDestino;
};

Viajero viajeros[MAX_VIAJEROS];
Ingreso ingresos[MAX_VIAJEROS];
Salida salidas[MAX_VIAJEROS];
Pais paises[MAX_VIAJEROS];
int contadorViajeros = 0;
int contadorIngresos = 0;
int contadorSalidas = 0;
int contadorPaises = 0;

void mostrarMenu();
void registrarViajero();
void registrarIngresoSalida();
void borrarViajero();
void consultarViajero();
void salir();
void gotoxy(int x, int y);  // Declaración de la función gotoxy

int main() {
    int opcion;
    do {
        system("cls");  // Limpia la pantalla
        mostrarMenu();
        gotoxy(10, 10);
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Ignora el salto de línea restante 

        switch (opcion) {
            case 1:
                registrarViajero();
                break;
            case 2:
                registrarIngresoSalida();
                break;
            case 3:
                borrarViajero();
                break;
            case 4:
                consultarViajero();
                break;
            case 5:
                salir();
                break;
            default:
                cout << "Opcion invalida. Por favor intente de nuevo." << endl;
        }

        if (opcion != 5) {
            cout << "Presione cualquier tecla para continuar...";
            cin.get(); // Espera a que el usuario presione una tecla y ya sale de la pantalla 
        }
    } while (opcion != 5);

    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mostrarMenu() {
    gotoxy(10, 2);  //uso del gotoxy para una interfaz mas bonita 
    cout << "===== Menu de Control de Migracion =====" << endl;
    gotoxy(10, 4);
    cout << "1. Registrar Nombre, Cedula, Pais de Origen y Pais de Destino" << endl;
    gotoxy(10, 5);
    cout << "2. Registrar Fecha de Ingreso y Salida (antes de ingresar aca debera de registrarse )" << endl;
    gotoxy(10, 6);
    cout << "3. Borrar Registro de Viajero" << endl;
    gotoxy(10, 7);
    cout << "4. Consultar Informacion de Viajero" << endl;
    gotoxy(10, 8);
    cout << "5. Salir" << endl;
}

void registrarViajero() {
    if (contadorViajeros < MAX_VIAJEROS) {
        Viajero nuevoViajero;
        cout << "Ingrese la cedula del viajero (sin espacios): " << endl;
        cin >> nuevoViajero.cedula;
        cin.ignore(); // Ignora el salto de linea restante 
        cout << "Ingrese el nombre del viajero (puede contener espacios):" << endl;
        getline(cin, nuevoViajero.nombre);
        cout << "Ingrese la direccion del viajero (puede contener espacios): " << endl;
        getline(cin, nuevoViajero.direccion);

        viajeros[contadorViajeros] = nuevoViajero;

        Pais nuevoPais;
        nuevoPais.cedulaViajero = nuevoViajero.cedula;
        cout << "Ingrese el pais de origen del viajero (sin espacios): " << endl;
        getline(cin, nuevoPais.nombrePaisOrigen);
        cout << "Ingrese el pais de destino del viajero (sin espacios): "; // se usa sin espacios por que el programa me da error
        getline(cin, nuevoPais.nombrePaisDestino);

        paises[contadorPaises] = nuevoPais;

        contadorViajeros++;
        contadorPaises++;

        cout << "Viajero registrado." << endl;
    } else {
        cout << "No se pueden registrar mas viajeros." << endl;
    }
}

void registrarIngresoSalida() {
    if (contadorIngresos < MAX_VIAJEROS && contadorSalidas < MAX_VIAJEROS) {
        string cedula;
        cout << "Ingrese la cedula del viajero: ";
        cin >> cedula;
        cin.ignore(); // Ignora el salto de lunea restante 
        bool encontrado = false;
        for (int i = 0; i < contadorViajeros; i++) {
            if (viajeros[i].cedula == cedula) {
                Ingreso nuevoIngreso;
                nuevoIngreso.cedulaViajero = cedula;
                cout << "Ingrese la fecha de ingreso (sin espacios): ";
                getline(cin, nuevoIngreso.fechaIngreso);
                cout << "Ingrese el lugar de ingreso (puede contener espacios): ";
                getline(cin, nuevoIngreso.lugarIngreso);

                ingresos[contadorIngresos] = nuevoIngreso;
                contadorIngresos++;

                Salida nuevaSalida;
                nuevaSalida.cedulaViajero = cedula;
                cout << "Ingrese la fecha de salida (sin espacios): ";
                getline(cin, nuevaSalida.fechaSalida);
                cout << "Ingrese el lugar de salida (puede contener espacios): ";
                getline(cin, nuevaSalida.lugarSalida);

                salidas[contadorSalidas] = nuevaSalida;
                contadorSalidas++;

                cout << "Ingreso y salida registrados exitosamente." << endl;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Viajero no encontrado." << endl;
        }
    } else {
        cout << "No se pueden registrar mas ingresos o salidas." << endl;
    }
}

void borrarViajero() {
    string cedula;
    cout << "Ingrese la cedula del viajero a borrar: ";
    cin >> cedula;
    cin.ignore(); // Ignora el salto de linea restante 

    bool encontrado = false;
    for (int i = 0; i < contadorViajeros; i++) {
        if (viajeros[i].cedula == cedula) {
            viajeros[i] = Viajero(); // Reinicia el viajero 
            // También necesitar eliminar o marcar los ingresos y salidas
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        cout << "Registro de viajero borrado exitosamente." << endl;
    } else {
        cout << "Viajero no encontrado." << endl;
    }
}

void consultarViajero() {
    string cedula, paisDestino;
    cout << "Ingrese la cedula del viajero: ";
    cin >> cedula;
    cin.ignore(); // Ignora el salto de línea restante 
    cout << "Ingrese el pais de destino: ";
    getline(cin, paisDestino);

    bool encontrado = false;
    for (int i = 0; i < contadorViajeros; i++) {
        if (viajeros[i].cedula == cedula) {
            cout << "Nombre: " << viajeros[i].nombre << endl;
            cout << "Cedula: " << viajeros[i].cedula << endl;
            cout << "Direccion: " << viajeros[i].direccion << endl;

            for (int j = 0; j < contadorPaises; j++) {
                if (paises[j].cedulaViajero == cedula && paises[j].nombrePaisDestino == paisDestino) {
                    cout << "Pais de origen: " << paises[j].nombrePaisOrigen << endl;
                    cout << "Pais de destino: " << paises[j].nombrePaisDestino << endl;
                    break;
                }
            }

            for (int j = 0; j < contadorIngresos; j++) {
                if (ingresos[j].cedulaViajero == cedula) {
                    cout << "Fecha de Ingreso: " << ingresos[j].fechaIngreso << endl;
                    cout << "Lugar de Ingreso: " << ingresos[j].lugarIngreso << endl;
                    break;
                }
            }

            for (int j = 0; j < contadorSalidas; j++) {
                if (salidas[j].cedulaViajero == cedula) {
                    cout << "Fecha de Salida: " << salidas[j].fechaSalida << endl;
                    cout << "Lugar de Salida: " << salidas[j].lugarSalida << endl;
                    break;
                }
            }

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Viajero no encontrado." << endl;
    }
}

void salir() {
    cout << "Saliendo del sistema..." << endl;
}

