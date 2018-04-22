#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
#include <unistd.h>
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

int menu();

void mySleep(int sleepMS);
int main()
{
/*
�Qu� hace? Debe abrir un archivo y comprueba si hay un error en
la apertura. Si lo hay, muestra un mensaje de error, si no, muestra
el men� mientras la opci�n seleccionada no sea Salir del programa.
Antes de finalizar el programa, cierra el archivo.
*/
	int opcion = menu();
	switch (opcion) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;

	return 0;
	}
}

int menu() {
/*
Devuelve: la opci�n le�da
Recibe: nada
�Qu� hace? Muestra un men� por pantalla y lee una opci�n, comprobando
si es correcta (valor entre 1 y 3). Si no es correcta, muestra
un mensaje de error e imprime de nuevo el men� por pantalla hasta
que la opci�n le�da sea correcta. La funci�n devuelve la opci�n le�da.
*/
	int opcion = 0;
	int nitems;

	while(opcion < 1 || opcion > 3){
		#ifdef __unix__
			system("clear");
		#endif
		#if defined(_WIN32) || defined(_WIN64)
			system("cls");
		#endif

		printf("1. Jugar (ordenador vs ordenador)\n");
		printf("2. Jugar (jugador vs jugador)\n");
		printf("3. Salir\n");
		#ifdef __unix__
			scanf("%d", &opcion);
		#endif
		#if defined(_WIN32) || defined(_WIN64)
			scanf_s("%d", &opcion);
		#endif
		while (getchar() != '\n') {		//clear char cache and fix issue with valid number followed by chars getting accepted
			opcion = -1;
		} 

		if(opcion < 1 || opcion > 3){
			printf("ERROR: Opcion Invalida\n");
			mySleep(1000);
		}
	}
	return opcion;

}
void jugar_bingo(int opcion) {
/*
Devuelve: nada
 Recibe: la opci�n elegida
 �Qu� hace? Se lee el tama�o del cart�n (n�mero de filas y n�mero
de columnas) y el n�mero de blancos por fila. Si los valores indicados
son negativos o 0 o si el n�mero de blancos es negativo o mayor que
el n�mero de columnas, se muestra un mensaje de error y se vuelven
a leer hasta que sean correctos. Seg�n el argumento (la opci�n de
men� que se ha le�do por teclado) se juega al bingo autom�ticamente
o manualmente, indicando adem�s el tama�o de cart�n y el n�mero
de blancos por fila. Adem�s, se escribe en el archivo si el juego va a ser
autom�tico (ordenador vs ordenador) o manual (jugador vs jugador).
*/
}
void jugar_ordenador(int num_filas, int num_columnas, int blancos[]) {
/*
 Devuelve: nada
 Recibe: el n�mero de filas del cart�n, el n�mero de columnas del
cart�n y el n�mero de blancos en cada fila.
 �Qu� hace? Reserva espacio para dos cartones del tama�o apropiado
y los inicializa autom�ticamente. A continuaci�n, los imprime por
pantalla y en el archivo. Por �ltimo, juega al bingo con esos cartones.
*/
}
void jugar_usuarios(int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
 Recibe: el n�mero de filas del cart�n, el n�mero de columnas del
cart�n y el n�mero de blancos en cada fila.
 �Qu� hace? Reserva espacio para dos cartones del tama�o apropiado
y los inicializa manualmente. A continuaci�n, los imprime por pantalla
y en el archivo. Por �ltimo, juega al bingo con esos cartones.
*/
}
void generarTableroAutomatico(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
 Devuelve: nada
Recibe: el cart�n, el n�mero de filas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fila.
�Qu� hace? Esta funci�n inicializa el cart�n a 0, pone el n�mero de
blancos que indique el argumento en cada fila del cart�n de forma
aleatoria y por �ltimo, rellena las posiciones restantes del cart�n con
n�meros aleatorios de 1 a 99 no repetidos ordenados de menor a
mayor.
*/
}
void generarTablero(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
 Recibe: el cart�n, el n�mero de filas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fila.
 �Qu� hace? Esta funci�n inicializa el cart�n a 0, pone el n�mero
de blancos que indique el argumento en cada fila del cart�n en las
posiciones que indique el usuario (comprobando que son v�lidas) y
por �ltimo, rellena las posiciones restantes del cart�n con los n�meros
que indique el usuario, comprobando que no se repitan y que est�n
de 1 a 99 ordenados de menor a mayor.
*/
}
void pone_blancos_carton(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
Recibe: el cart�n, el n�mero de fifilas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fifila.
�Qu� hace? Esta funci�n genera aleatoriamente las posiciones donde
ir� un blanco en cada fila del cart�n. Como resultado el cart�n
tendr� en cada fila los blancos especificados por el n�mero pasado
como argumento.
*/
}
void pone_blancos_carton_manual(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
Recibe: el cart�n, el n�mero de filas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fila.
�Qu� hace? Esta funci�n lee las posiciones donde ir� un blanco
(tantas como indica el argumento) indicadas por el usuario. La funci�n
ha de comprobar que las posiciones indicadas por el usuario son
v�lidas.
*/
}
void pone_nums_carton(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
Recibe: el cart�n, el n�mero de filas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fila.
�Qu� hace? Genera n�meros aleatorios distintos de 1 a 99 y los coloca
en el cart�n ordenados de menor a mayor por columnas donde no haya
blancos. Para ello usamos un vector de tama�o igual al n�mero de
posiciones del cart�n que no tienen blanco. Se inicializa a 0 el vector y
luego se rellena de n�meros aleatorios de 1 a 99 no repetidos. Despu�s
se ordena y finalmente se almacena en el cart�n.
*/
}
void pone_nums_carton_manual(int carton[], int num_filas, int num_columnas, int blancos[]) {
/*
Devuelve: nada
Recibe: el cart�n, el n�mero de filas del cart�n, el n�mero de columnas
del cart�n y el n�mero de blancos en cada fila.
�Qu� hace? Lee n�meros distintos de 1 a 99 y los coloca en el cart�n
ordenados de menor a mayor por columnas donde no haya blancos.
Para ello usamos un vector de tama�o igual al n�mero de posiciones
del cart�n que no tienen blanco. Se inicializa a 0 el vector y luego se
rellena de con n�meros indicados por el usuario de 1 a 99 no repetidos.
Despu�s se ordena y finalmente se almacena en el cart�n.
*/
}
_Bool comprueba_num_en_vector(int vec[], int tamano, int num) {
/*
Devuelve: un valor si el n�mero est� en el vector y otro en caso
contrario
Recibe: un vector, su tama�o y un n�mero.
�Qu� hace? Se comprueba si el n�mero est� en el vector. Devuelve
un valor si el n�mero est� y otro en caso contrario.
*/
}
void ordena_vector(int vec[], int tamano) {
/*
Devuelve: nada
Recibe: un vector y su tama�o
�Qu� hace? La funci�n ordena los n�meros de dicho vector de menor
a mayor.
*/
}
void imprime_carton(int carton[], int tamano) {
/*
Devuelve: nada
Recibe: el cart�n y su tama�o
�Qu� hace? La funci�n imprime el cart�n por pantalla distinguiendo
las posiciones donde hay n�meros que no han salido, de los que s�
han salido y de las posiciones en blanco. Por ejemplo, se puede hacer
lo siguiente: en las posiciones donde hay un blanco se imprime una
X. En las posiciones donde hay un n�mero se imprime el n�mero. En
las posiciones donde hay un n�mero que ya ha salido, se imprime un
$. El cart�n se imprime de forma organizada (cada fila ocupa una
l�nea y los valores que est�n en la misma columna, est�n alineados).
Tambi�n se imprime en el archivo.
*/
}
void jugar(int carton1[], int tamano1, int carton2[], int tamano2) {
/*
Devuelve: nada.
Recibe: dos cartones y su tama�o.
�Qu� hace? Primero inicializa un vector de 99 enteros (las bolas que
salen) a 0. Despu�s, mientras no haya fila, genera un n�mero aleatorio
de 1 a 99 sin repeticiones y se imprime por pantalla. A continuaci�n,
se comprueba si ese n�mero est� en los cartones. Tambi�n ha de
comprobar si se ha cantado fila (s�lo se puede cantar una fila, por
el primer jugador que lo haga) y si se ha cantado bingo. Si se canta
fila, imprime por pantalla el cart�n del jugador que ha cantado fila e
indica qui�n es. Una vez que se ha cantado fila, se siguen generando
n�meros aleatorios de 1 a 99 sin repeticiones, se siguen imprimiendo
por pantalla y se comprueba si se canta bingo. Si se canta bingo,
se imprime el cart�n del jugador que ha perdido e indica qui�n ha
ganado, acabando el juego (se vuelve a mostrar el men�).
*/
}
_Bool comprobar_ganador(int carton[], int tamano) {
/*
Devuelve: un valor en funci�n de si dicho cart�n tiene o no tiene
bingo.
7
Recibe: un cart�n y su tama�o.
Qu� hace? Devuelve un valor en funci�n de si dicho el cart�n pasado
como argumento tiene o no tiene bingo.
*/
}
_Bool comprobar_fila(int carton[], int tamano) {
/*
Devuelve: un valor en funci�n de si el cart�n tiene una fila completa
o no.
Recibe: un cart�n y su tama�o.
�Qu� hace? Devuelve un valor en funci�n de si dicho cart�n tiene o
no tiene una fila completa (han salido todos los n�meros de esa fila).
*/
}
void comprueba_carton(int carton[], int tamano) {
/*
Devuelve: nada.
Recibe: un cart�n y su tama�o.
�Qu� hace? Si el cart�n tiene el n�mero, lo marca como que ha salido
(puede almacenar un 0 en esa posici�n para indicar que ha salido).
*/
}
_Bool comprueba_si_ha_salido_bola() {
/*
Devuelve: un valor en funci�n de si dicho n�mero est� o no est� en
el vector.
Recibe: un vector de 99 enteros y un n�mero.
�Qu� hace? Devuelve un valor en funci�n de si dicho n�mero est� o
no est� en el vector.
*/
}
void mySleep(int sleepMs){
#ifdef __unix__
	usleep(sleepMs * 1000);
#endif
#if defined(_WIN32) || defined(_WIN64)
	Sleep(sleepMs);
#endif
}