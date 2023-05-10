#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/*
	No sé como funciona esto, pero habilita los colores en cualquier consola  Windows
	no tocar xd
*/
void enableColorsWindows();

void enableColorsWindows() {
    // Habilitar el procesamiento de códigos de escape ANSI en Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

//Colores para los fuentes de letras y el color del fondo
#define RESET_FONT "\033[0m"
#define BLACK_FONT "\033[30m"
#define RED_FONT "\033[31m"
#define GREEN_FONT "\033[32m"
#define YELLOW_FONT "\033[33m"
#define BLUE_FONT "\033[34m"
#define MAGENTA_FONT "\033[35m"
#define CYAN_FONT "\033[36m"
#define WHITE_FONT "\033[37m"
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDWHITE "\033[1m\033[37m"
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

#define LIMIT 25
string COLSHEADER = "ABCDEFGHIJKLMNOPQRSTUVWXY";

// Variables para controlar cuantas celdas se muestran y donde está la seleccionada
int row_pos = 0, col_pos = 0, SHOWLIMIT = 9;

string printCell(string value, int pos, bool isHeader);
bool checkNotOutBound(int n);
void drawColumnsHeader();
void drawRowHeader(int i);
void showSheet(int n, int m);
void initList();
bool showMenu();
bool showMainMenu();

/*
    Las especificaciones decian que las celdas deben tener 8 caracteres maximo, entonces, 
    a un espacio vacio de 8 caracteres, le remplazo una porcion en una posicion especifica 
    con el texto que queremos mostrar, así siempre hay el mismo tamaño
*/
string printCell(string value, int pos, bool isHeader)
{
    
    //TODO: VALIDAR QUE SIEMPRE HAYAN 8 caracteres EN EL VALOR DE LA CELDA A MOSTRAR
	string val = value;
	string cel = "        ";

	if (!isHeader)
	{
		return "|" + cel.replace(pos, val.length(), val);
	}
	else
	{
		return " " + cel.replace(pos, val.length(), val);
	}
}


//Solo imprimen las cabeceras
void drawColumnsHeader(int n, int m)
{

	cout << BG_BLUE << printCell("", 0, true);

	// Esto genera las cabeceras de las columnas  |      A     |      B      |
	for (int j = m; j < m + SHOWLIMIT; j++)
	{
		cout << BG_BLUE << printCell(COLSHEADER.substr(j, 1), 4, true);
	}
	cout << RESET_FONT << "\n";
}

void drawRowHeader(int i)
{
	// se muestra primero, qué fila es
	string pos = to_string(i + 1);

	cout << BG_WHITE << BLACK_FONT;
	cout << printCell(pos, 4, true) << RESET_FONT;
}
///////////////////////////////

//Hay un limite para el espacio de la multilist, de 25 items, si se pasa, muestra una excepcion

bool checkNotOutBound(int n){
    return n > 25 - SHOWLIMIT;
}

