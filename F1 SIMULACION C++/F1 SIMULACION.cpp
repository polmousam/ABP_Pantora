#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

const int PAUSA_ENTRE_CARACTERES = 10;
const double RANGO_ALEATORIO = 0.5;

// Funcion para calcular el tiempo por vuelta
double calcularTiempoPorVuelta(double tiempo_base, double factor_neumaticos, double factor_meteorologico, double factor_aerodinamica) {
    return tiempo_base + factor_neumaticos + factor_meteorologico + factor_aerodinamica;
}

// Funcion para generar un pequenio ajuste aleatorio
double generarAjusteAleatorio() {
    static bool inicializado = false;
    if (!inicializado) {
        srand(time(0));
        inicializado = true;
    }
    return ((double)rand() / RAND_MAX) * RANGO_ALEATORIO - (RANGO_ALEATORIO / 2);
}

// Funcion para convertir segundos a minutos:segundos:milisegundos
string formatoTiempo(double tiempo) {
    int minutos = tiempo / 60;
    int segundos = static_cast<int>(tiempo) % 60;
    int milisegundos = static_cast<int>((tiempo - static_cast<int>(tiempo)) * 1000);
    return to_string(minutos) + ":" + to_string(segundos) + ":" + to_string(milisegundos);
}

// Funcion para validar la entrada del usuario
char validarEntrada(char opcion) {
    while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N') {
        cout << "Entrada no valida. Por favor, ingrese 's' para si o 'n' para no: ";
        cin >> opcion;
        cout << " " << endl;
    }
    return opcion;
}

// Funcion para configurar las opciones de neumaticos y carga aerodinamica
void configurarOpciones(string nombre_piloto, int& neumaticos, int& carga_aerodinamica) {
    cout << "Selecciona los neumaticos para " << nombre_piloto << ":" << endl;
    cout << "1. Blando" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Duro" << endl;
    cout << "Opcion: ";
    cin >> neumaticos;
    cout << " " << endl;
    neumaticos--; // Ajuste de indice

    cout << "Selecciona la carga aerodinamica para " << nombre_piloto << ":" << endl;
    cout << "1. Baja" << endl;
    cout << "2. Media" << endl;
    cout << "3. Alta" << endl;
    cout << "Opcion: ";
    cin >> carga_aerodinamica;
    cout << " " << endl;
    carga_aerodinamica--; // Ajuste de indice
}

int main() {
    // Mensaje de bienvenida mostrado poco a poco
    string mensaje_bienvenida = "Bienvenido al programa de simulacion de tiempos por vuelta del equipo ASTON MARTIN ARAMCO FORMULA ONE TEAM \n";
    for (char c : mensaje_bienvenida) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(PAUSA_ENTRE_CARACTERES));
    }

    // Arte ASCII
    cout << R"(
                                                                                                    
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        
        @                                    @#      .@                                    @        
          @@         :-=+++*%*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+%**=*=-:         @@          
           @@@@@@+.       .-= @@%  @ +@ @ @     @@ @  @ @ + @ @   @ @@ =-.       .+%@@@@@           
              @@@@@@+      == @# #  . # @ . =:% @   %  @  @ @ @  *  %@ +=.     +@@@@@@-             
                  @@@@@@      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      %@@@@@                  
                       *@@@@*   @    @   @   @  @  @  @   @   @    @   +@@@@#                       
                             @@   @@   @@  @@  @    @  @@  @@   @@   @@                             
                               @@@   -@   @@   @ @@ .=  @@   @+   @@@                               
                                    @@@@@@    @@@  @@@    @@@@@@                                    
                                          .@@@@      @@@@:                                          

                                                                                                    
      @-    @+:@@ @@@@.@@ @@#++#@@  .@     @@      @      *@     @+    @@ -@@ @@@@.@@ @@  @-     @  
     @ @    @        @   @@      @@  @@@   +@      @@    @@@    @ @    @   +@    @    @+  @%@    @  
    @@ @@   :@@@%    @   @       :@  @ .@@  @     %- @  @@ @   @@ @@   @@@@      @    @=  @  @@  @  
   @#   @@      @    @   @@      @@  @   @@@@     @  =@#@  @  @@   @@  @  @@     @    @+  @   %@*@  
  *@     @@@@: @@   -@    @@=-:%@%  +@     @@     @   @@   @@ @     @@ @@  @@-  .@    @@  @     @@ 


)";

    // Mensaje "Presiona Enter para empezar" mostrado poco a poco
    string mensaje_presiona_enter = "Presiona Enter para empezar.";
    for (char c : mensaje_presiona_enter) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(PAUSA_ENTRE_CARACTERES));
    }
    cin.get();  // Esperar a que el usuario presione Enter

    char opcion;

    do {
        int circuito;

        // Mostrar menu de circuitos
        cout << "Seleccione un circuito:" << endl;
        cout << "1. Barcelona-Catalunya (Montmelo)" << endl;
        cout << "2. Circuito de Spa-Francorchamps" << endl;
        cout << "3. Circuito de Monaco" << endl;
        cout << "4. Circuito de Suzuka" << endl;
        cout << "Opcion: ";
        cin >> circuito;
        cout << " " << endl;

        // Definir los tiempos base y factores de ajuste segun el circuito seleccionado
        double tiempo_base;
        double factor_neumaticos[] = { 0, 0.8, 1.5 }; // Blando, Medio, Duro
        double factor_meteorologico[] = { 0, 1.3, 4.5 }; // Soleado, Nublado con viento ligero, Lluvia ligera con viento
        double factor_aerodinamica[] = { 0.9, 0, 1.7 }; // Media, Baja, Alta

        if (circuito == 1) {
            tiempo_base = 72.272; // 1'12"272 en segundos
        }
        else if (circuito == 2) {
            tiempo_base = 124.518; // 2'04"518 en segundos
        }
        else if (circuito == 3) {
            tiempo_base = 78.4; // 1'18"400 en segundos
        }
        else if (circuito == 4) {
            tiempo_base = 97.123; // 1'37"123 en segundos
        }
        else {
            cout << "Opcion invalida. Seleccionando Barcelona-Catalunya por defecto." << endl;
            tiempo_base = 72.272; // 1'12"272 en segundos (Barcelona-Catalunya por defecto)
        }

        // Configurar las condiciones meteorologicas
        int condiciones_meteorologicas;
        cout << "Selecciona las condiciones meteorologicas:" << endl;
        cout << "1. Soleado" << endl;
        cout << "2. Nublado con viento ligero" << endl;
        cout << "3. Lluvia ligera con viento" << endl;
        cout << "Opcion: ";
        cin >> condiciones_meteorologicas;
        cout << " " << endl;
        condiciones_meteorologicas--; // Ajuste de indice

        // Configurar los neumaticos y carga aerodinamica para Fernando Alonso
        int neumaticos_alonso, carga_aerodinamica_alonso;
        configurarOpciones("Fernando Alonso", neumaticos_alonso, carga_aerodinamica_alonso);

        // Configurar los neumaticos y carga aerodinamica para Lance Stroll
        int neumaticos_stroll, carga_aerodinamica_stroll;
        configurarOpciones("Lance Stroll", neumaticos_stroll, carga_aerodinamica_stroll);

        // Calcular y mostrar los tiempos por vuelta
        cout << "Tiempos por vuelta para Fernando Alonso:" << endl;
        double tiempo_alonso = calcularTiempoPorVuelta(tiempo_base, factor_neumaticos[neumaticos_alonso],
            factor_meteorologico[condiciones_meteorologicas],
            factor_aerodinamica[carga_aerodinamica_alonso]);
        tiempo_alonso += generarAjusteAleatorio(); // Agregar un peque�o ajuste aleatorio
        cout << "Tiempo: " << formatoTiempo(tiempo_alonso) << endl;

        cout << "Tiempos por vuelta para Lance Stroll:" << endl;
        double tiempo_stroll = calcularTiempoPorVuelta(tiempo_base, factor_neumaticos[neumaticos_stroll],
            factor_meteorologico[condiciones_meteorologicas],
            factor_aerodinamica[carga_aerodinamica_stroll]);
        tiempo_stroll += generarAjusteAleatorio(); // Agregar un peque�o ajuste aleatorio
        cout << "Tiempo: " << formatoTiempo(tiempo_stroll) << endl;

        // Preguntar al usuario si desea realizar otra simulaci�n
        cout << "Desea realizar otra simulacion? (s/n): ";
        cin >> opcion;
        opcion = validarEntrada(opcion);
        cout << " " << endl;
    } while (opcion == 's' || opcion == 'S');

    cout << "Gracias por utilizar nuestro simulador. Hasta luego!" << endl;

    return 0;
}
