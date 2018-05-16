#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __unix__
#include <unistd.h>
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

FILE *fp;

int menu();
void jugar_bingo(int opcion);
void jugar_ordenador(int num_filas, int num_columnas, int *blancos);
void jugar_usuarios(int num_filas, int num_columnas, int *blancos);
void generarTableroAutomatico(int *carton, int num_filas, int num_columnas, int *blancos);
void generarTablero(int *carton, int num_filas, int num_columnas, int *blancos);
void pone_blancos_carton(int *carton, int num_filas, int num_columnas, int *blancos);
void pone_blancos_carton_manual(int *carton, int num_filas, int num_columnas, int *blancos);
void pone_nums_carton(int *carton, int num_filas, int num_columnas, int *blancos);
void pone_nums_carton_manual(int *carton, int num_filas, int num_columnas, int *blancos);
_Bool comprueba_num_en_vector(int *vec, int tamano, int num);
void ordena_vector(int *vec, int tamano);
void imprime_carton(int *carton, int num_filas, int num_columnas);
void jugar(int *carton1, int *carton2, int num_filas, int num_columnas);

void mySleep(int sleepMS);
void swap(int *xp, int *yp);
int main()
{
/*
¾Qué hace? Debe abrir un archivo y comprueba si hay un error en
la apertura. Si lo hay, muestra un mensaje de error, si no, muestra
el menú mientras la opción seleccionada no sea Salir del programa.
Antes de finalizar el programa, cierra el archivo.
*/
	srand(time(NULL));
	fp = fopen("log.txt", "w+");
	if (fp == NULL) {
		printf("El archivo no ha sido creado correctamente, errno = %d\n", errno);
		mySleep(1000);
		return 1;
	}
	int opcion = menu();
	if (opcion == 3){
		fclose(fp);
		return 0;
	} else {
		jugar_bingo(opcion);
	}
	fclose(fp);
	return 0;
}

int menu() {
/*
Devuelve: la opción leída
Recibe: nada
¾Qué hace? Muestra un menú por pantalla y lee una opción, comprobando
si es correcta (valor entre 1 y 3). Si no es correcta, muestra
un mensaje de error e imprime de nuevo el menú por pantalla hasta
que la opción leída sea correcta. La función devuelve la opción leída.
*/
	int opcion = 0;

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
 Recibe: la opción elegida
 ¾Qué hace? Se lee el tamaño del cartón (número de filas y número
de columnas) y el número de blancos por fila. Si los valores indicados
son negativos o 0 o si el número de blancos es negativo o mayor que
el número de columnas, se muestra un mensaje de error y se vuelven
a leer hasta que sean correctos. Según el argumento (la opción de
menú que se ha leído por teclado) se juega al bingo automáticamente
o manualmente, indicando además el tamaño de cartón y el número
de blancos por fila. Además, se escribe en el archivo si el juego va a ser
automático (ordenador vs ordenador) o manual (jugador vs jugador).
*/
	int filas = -1, columnas = -1, blanco = -1;
	while (filas < 1){
		printf("Indicar numero de filas\n");
		#ifdef __unix__
			scanf("%d", &filas);
		#endif
		#if defined(_WIN32) || defined(_WIN64)
			scanf_s("%d", &filas);
		#endif
		while (getchar() != '\n') {		//clear char cache and fix issue with valid number followed by chars getting accepted
			filas = -1;
		}
		if (filas < 1) {
			printf("ERROR: Numero de filas no valido\n");
			mySleep(1000);
		}
	}
	while (columnas < 1) {
		printf("Indicar numero de columnas\n");
		#ifdef __unix__
			scanf("%d", &columnas);
		#endif
		#if defined(_WIN32) || defined(_WIN64)
			scanf_s("%d", &columnas);
		#endif
		while (getchar() != '\n') {		//clear char cache and fix issue with valid number followed by chars getting accepted
			columnas = -1;
		}
		if (columnas < 1) {
			printf("ERROR: Numero de columnas no valido\n");
			mySleep(1000);
		}
	}
	int *blancos = malloc(filas * sizeof(*blancos));
	if (!blancos) {
		printf("There was a problem with malloc.");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < filas; i++) {
		while (blanco > columnas || blanco < 0) {
			printf("Indicar numero de blancos para la fila %d \n", i+1);
			#ifdef __unix__
			scanf("%d", &blanco);
			#endif
			#if defined(_WIN32) || defined(_WIN64)
			scanf_s("%d", &blanco);
			#endif
			while (getchar() != '\n') {		//clear char cache and fix issue with valid number followed by chars getting accepted
				blanco = -1;
			}
			if (blanco > columnas || blanco < 0) {
				printf("ERROR: Numero de blancos no valido\n");
				mySleep(1000);
			}
		} 
		blancos[i] = blanco;
		blanco = -1;
	}
	if(opcion == 1){
		fprintf(fp, "Ordenador vs Ordenador\n");
		jugar_ordenador(filas, columnas, blancos);
	}
	else {
		fprintf(fp, "Jugador vs Jugador\n");
		jugar_usuarios(filas, columnas, blancos);
	}
}
void jugar_ordenador(int num_filas, int num_columnas, int *blancos) {
/*
 Devuelve: nada
 Recibe: el número de filas del cartón, el número de columnas del
cartón y el número de blancos en cada fila.
 ¾Qué hace? Reserva espacio para dos cartones del tamaño apropiado
y los inicializa automáticamente. A continuación, los imprime por
pantalla y en el archivo. Por último, juega al bingo con esos cartones.
*/

	int *carton1 = malloc((num_filas * num_columnas) * sizeof(*carton1));
	int *carton2 = malloc((num_filas * num_columnas) * sizeof(*carton2));
	generarTableroAutomatico(carton1, num_filas, num_columnas, blancos);
	generarTableroAutomatico( carton2, num_filas, num_columnas, blancos);
	imprime_carton(carton1, num_filas, num_columnas);
	imprime_carton(carton2, num_filas, num_columnas);
	//Imprimir en el archivo
	jugar(carton1, carton2, num_filas, num_columnas);
}
void jugar_usuarios(int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
 Recibe: el número de filas del cartón, el número de columnas del
cartón y el número de blancos en cada fila.
 ¾Qué hace? Reserva espacio para dos cartones del tamaño apropiado
y los inicializa manualmente. A continuación, los imprime por pantalla
y en el archivo. Por último, juega al bingo con esos cartones.
*/

	//Seria mejor reservarles el espacio en jugar_bingo para evitar redundancia e imprimirlos una vez estemos en la funcion jugar(...)
	int *carton1, *carton2;
	carton1 = (int *)malloc(sizeof(int) * (num_filas * num_columnas));
	carton2 = (int *)malloc(sizeof(int) * (num_filas * num_columnas));
	generarTablero(carton1, num_filas, num_columnas, blancos);
	generarTablero(carton2, num_filas, num_columnas, blancos);
	imprime_carton(carton1, num_filas, num_columnas);
	imprime_carton(carton2, num_filas, num_columnas);
	//Imprimir al archivo
	jugar(carton1, carton2, num_filas, num_columnas);
}
void generarTableroAutomatico(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
 Devuelve: nada
Recibe: el cartón, el número de filas del cartón, el número de columnas
del cartón y el número de blancos en cada fila.
¾Qué hace? Esta función inicializa el cartón a 0, pone el número de
blancos que indique el argumento en cada fila del cartón de forma
aleatoria y por último, rellena las posiciones restantes del cartón con
números aleatorios de 1 a 99 no repetidos ordenados de menor a
mayor.
*/
	int cartonSize = num_filas * num_columnas;

	for (int i = 0; i < cartonSize; i++) {
		carton[i] = 0;
	}
	pone_blancos_carton(carton, num_filas, num_columnas, blancos);
	pone_nums_carton(carton, num_filas, num_columnas, blancos);

}
void generarTablero(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
 Recibe: el cartón, el número de filas del cartón, el número de columnas
del cartón y el número de blancos en cada fila.
 ¾Qué hace? Esta función inicializa el cartón a 0, pone el número
de blancos que indique el argumento en cada fila del cartón en las
posiciones que indique el usuario (comprobando que son válidas) y
por último, rellena las posiciones restantes del cartón con los números
que indique el usuario, comprobando que no se repitan y que estén
de 1 a 99 ordenados de menor a mayor.
*/
	int cartonSize = num_filas * num_columnas;

	for (int i = 0; i < cartonSize; i++) {
		carton[i] = 0;
	}
	pone_blancos_carton_manual(carton, num_filas, num_columnas, blancos);
	pone_nums_carton_manual(carton, num_filas, num_columnas, blancos);
}
void pone_blancos_carton(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
Recibe: el cartón, el número de fifilas del cartón, el número de columnas
del cartón y el número de blancos en cada fifila.
¾Qué hace? Esta función genera aleatoriamente las posiciones donde
irá un blanco en cada fila del cartón. Como resultado el cartón
tendrá en cada fila los blancos especificados por el número pasado
como argumento.
*/
	int p;
	for (int i = 0; i < num_filas; i++){
		for (int j = 0; j < blancos[i]; j++) {
			do{ 
			p = rand() % num_columnas;

			} while (carton[p + (i * num_columnas)] == -1);
			carton[p + (i * num_columnas)] = -1;
		}
	}
}
void pone_blancos_carton_manual(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
Recibe: el cartón, el número de filas del cartón, el número de columnas
del cartón y el número de blancos en cada fila.
¾Qué hace? Esta función lee las posiciones donde irá un blanco
(tantas como indica el argumento) indicadas por el usuario. La función
ha de comprobar que las posiciones indicadas por el usuario son
válidas.
*/
}
void pone_nums_carton(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
Recibe: el cartón, el número de filas del cartón, el número de columnas
del cartón y el número de blancos en cada fila.
¾Qué hace? Genera números aleatorios distintos de 1 a 99 y los coloca
en el cartón ordenados de menor a mayor por columnas donde no haya
blancos. Para ello usamos un vector de tamaño igual al número de
posiciones del cartón que no tienen blanco. Se inicializa a 0 el vector y
luego se rellena de números aleatorios de 1 a 99 no repetidos. Después
se ordena y finalmente se almacena en el cartón.
*/
	int cartonSize = num_filas * num_columnas;
	int numBlancos = 0, val;
	for (int i = 0; i < num_filas; i++) {
		numBlancos += blancos[i];
	}
	int *numeros = malloc((cartonSize - numBlancos) * sizeof(*numeros));
	for (int i = 0; i < cartonSize - numBlancos; i++) {
		numeros[i] = 0;
	}
	for (int i = 0; i < cartonSize - numBlancos; i++) {
		do{
			val = (rand() % 99) + 1;

		} while (comprueba_num_en_vector(numeros, cartonSize - numBlancos, val));
		numeros[i] = val;
	}
	ordena_vector(numeros, cartonSize - numBlancos);
	mySleep(8);
}
void pone_nums_carton_manual(int *carton, int num_filas, int num_columnas, int *blancos) {
/*
Devuelve: nada
Recibe: el cartón, el número de filas del cartón, el número de columnas
del cartón y el número de blancos en cada fila.
¾Qué hace? Lee números distintos de 1 a 99 y los coloca en el cartón
ordenados de menor a mayor por columnas donde no haya blancos.
Para ello usamos un vector de tamaño igual al número de posiciones
del cartón que no tienen blanco. Se inicializa a 0 el vector y luego se
rellena de con números indicados por el usuario de 1 a 99 no repetidos.
Después se ordena y finalmente se almacena en el cartón.
*/
}
_Bool comprueba_num_en_vector(int *vec, int tamano, int num) {
/*
Devuelve: un valor si el número está en el vector y otro en caso
contrario
Recibe: un vector, su tamaño y un número.
¾Qué hace? Se comprueba si el número está en el vector. Devuelve
un valor si el número está y otro en caso contrario.
*/
	for (int i = 0; i < tamano; i++) {
		if (vec[i]==num) {
			return 1;
		}
	}
	return 0;
}
void ordena_vector(int *vec, int tamano) {
/*
Devuelve: nada
Recibe: un vector y su tamaño
¾Qué hace? La función ordena los números de dicho vector de menor
a mayor.
*/
	//bubbleSort
	int i, j;
	for (i = 0; i < tamano - 1; i++)  
		for (j = 0; j < tamano - i - 1; j++)
			if (vec[j] > vec[j + 1])
				swap(&vec[j], &vec[j + 1]);
}
void imprime_carton(int *carton, int num_filas, int num_columnas) {
/*
Devuelve: nada
Recibe: el cartón y su tamaño
¾Qué hace? La función imprime el cartón por pantalla distinguiendo
las posiciones donde hay números que no han salido, de los que sí
han salido y de las posiciones en blanco. Por ejemplo, se puede hacer
lo siguiente: en las posiciones donde hay un blanco se imprime una
X. En las posiciones donde hay un número se imprime el número. En
las posiciones donde hay un número que ya ha salido, se imprime un
$. El cartón se imprime de forma organizada (cada fila ocupa una
línea y los valores que están en la misma columna, están alineados).
También se imprime en el archivo.
*/
}
void jugar(int *carton1,int *carton2, int num_filas, int num_columnas) {
/*
Devuelve: nada.
Recibe: dos cartones y su tamaño.
¾Qué hace? Primero inicializa un vector de 99 enteros (las bolas que
salen) a 0. Después, mientras no haya fila, genera un número aleatorio
de 1 a 99 sin repeticiones y se imprime por pantalla. A continuación,
se comprueba si ese número está en los cartones. También ha de
comprobar si se ha cantado fila (sólo se puede cantar una fila, por
el primer jugador que lo haga) y si se ha cantado bingo. Si se canta
fila, imprime por pantalla el cartón del jugador que ha cantado fila e
indica quién es. Una vez que se ha cantado fila, se siguen generando
números aleatorios de 1 a 99 sin repeticiones, se siguen imprimiendo
por pantalla y se comprueba si se canta bingo. Si se canta bingo,
se imprime el cartón del jugador que ha perdido e indica quién ha
ganado, acabando el juego (se vuelve a mostrar el menú).
*/
}
_Bool comprobar_ganador(int *carton, int num_filas, int num_columnas) {
/*
Devuelve: un valor en función de si dicho cartón tiene o no tiene
bingo.
7
Recibe: un cartón y su tamaño.
Qué hace? Devuelve un valor en función de si dicho el cartón pasado
como argumento tiene o no tiene bingo.
*/
}
_Bool comprobar_fila(int *carton, int num_filas, int num_columnas) {
/*
Devuelve: un valor en función de si el cartón tiene una fila completa
o no.
Recibe: un cartón y su tamaño.
¾Qué hace? Devuelve un valor en función de si dicho cartón tiene o
no tiene una fila completa (han salido todos los números de esa fila).
*/
}
void comprueba_carton(int *carton, int num_filas, int num_columnas) {
/*
Devuelve: nada.
Recibe: un cartón y su tamaño.
¾Qué hace? Si el cartón tiene el número, lo marca como que ha salido
(puede almacenar un 0 en esa posición para indicar que ha salido).
*/
}
_Bool comprueba_si_ha_salido_bola() {
/*
Devuelve: un valor en función de si dicho número está o no está en
el vector.
Recibe: un vector de 99 enteros y un número.
¾Qué hace? Devuelve un valor en función de si dicho número está o
no está en el vector.
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
void swap(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}