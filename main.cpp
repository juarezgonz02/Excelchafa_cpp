#include <iostream>
#include <string>
#include <Windows.h>
#include "display.cpp"
#include "saves.cpp"
//#include "data.cpp"

using namespace std;

string printCell(string value, int pos, bool isHeader);
bool checkNotOutBound(int n);
void drawColumnsHeader();
void drawRowHeader(int i);
void initList();
bool showMenu();
bool showMainMenu();


// Aqui empieza la lista, la posicion 0,0.
ROW *multilist = new ROW();

/*
	Se podria decir que estas posiciones desde cual se van a imprimir los datos  
*/
ROW *start_row; COLUMN *start_col;

//MODIFICAR ESTA POS DE MEMORIA PARA CAMBIAR LA CELDA SELECCIONADA 
COLUMN *selected_cell;

// Crea la lista con los datos
void initList()
{

	ROW *row = multilist;

	/*
		Crear el primer nodo
	*/
	row->back = NULL;
	row->value = new COLUMN();

	/*
		Crear el cada nodo y avanzar
	*/
	for (int i = 0; i < LIMIT; i++)
	{

		// Inicializar los nodos
		row->value = new COLUMN();
		row->next = new ROW();
		row->back = row;
		COLUMN *col = row->value;

		// Inicializar las columnas y llenarlas
		for (int j = 0; j < LIMIT; j++)
		{

			// TODO: AQUI EL VALOR DE LA
			//col->value = new string(to_string(i * 25 + j));
			col->value = new string("");
			col->back = col;
			col->next = new COLUMN();
			col = col->next;
		}
		row = row->next;
		col = row->value;
	}

	start_row = multilist;
	start_col = start_row->value;
}

/*
Imprime la multilist en formato hoja de calculo
*/
void showSheet(COLUMN *col_mem, ROW *row_mem, int n, int m)
{
	/*
	Test

	cout << checkNotOutBound(n) << "\n";
	cout << checkNotOutBound(m) << "\n";
	*/

	string BG;

	if (checkNotOutBound(n))
	{
		n = LIMIT - SHOWLIMIT;
	}

	if (checkNotOutBound(m))
	{
		m = LIMIT - SHOWLIMIT;
	}

	ROW *row = row_mem;
	COLUMN *col = col_mem;

	drawColumnsHeader(n, m);

	for (int i = 0; i < SHOWLIMIT; i++)
	{
		drawRowHeader(i + n);

		cout << RESET_FONT;
		if (i % 2 == 0)
		{
			// Establecer el color de fondo en verde para las filas pares
			BG = BG_GREEN;
		}
		else
		{
			// Establecer el color de fondo en blanco para las filas impares
			BG = BG_WHITE;
		}

		cout << BG;
		cout << BLACK_FONT; // Texto negro

		/*
		Dibuja la celda con los valores de la multilist
		*/
		for (int j = 0; j < SHOWLIMIT; j++)
		{
			string val = *(col->value);
			if (selected_cell == col)
			{
				cout << BG_YELLOW;
				cout << printCell(val, 0, false);
				cout << BG;
			}
			else
			{
				cout << printCell(val, 0, false);
			}
			col = col->next;
		}

		cout << RESET_FONT << "\n";

		// Avanzamos a la siguiente fila y nos posicionamos en la primera columna
		row = row->next;
		col = row->value;
	}

	cout << "\n\n\n";
}

bool showMainMenu()
{
	cout << RESET_FONT;
	bool salir = false;
	int option;
	cout << "Opciones para hoja de calculo" << endl;
	cout << "1) Nueva" << endl;
	cout << "2) Abrir" << endl;
	cout << "3) Salir" << endl;
	cout << " Escoge una opcion: ";
	cin >> option;
	cin.ignore();

	switch (option)
	{
	case 1:
		// Inicia la lista vacia
		initList();
		salir = true;

		break;

	case 2:
		// TODO: Funcion abrir desde json
		showFiles();
		initWithData(multilist);
		start_row = multilist;
		start_col = start_row->value;
		salir = true;
		break;

	case 3:
		return NULL;
		break;
	default:
		break;
	}

	cout << "\n\n\n";

	return salir;
}

// TODO: Implementar todas las funciones y darle estilo :|

// Funcion para seleccionar una celda a traves de la fila y columna ingresado por el usuario
void selectPositionCell(int n, int m, char colLetter)
{	
	// Definimos los punteros de la fila y columna
	ROW *row = start_row;
	COLUMN *col = start_col;

	// Verificamos que la celda seleccionado por el usuario se encuentre dentro del rango de la hoja de calculo
	if(checkNotOutBound(n) || checkNotOutBound(m)){
		cout << "La celda " << colLetter << n << " seleccionada no existe \n";
		return;
	}

	// Verificamos que no se pueda seleccionar una celda de tipo cabecera 
	if (n == 0)
	{
		cout << "La celda " << colLetter << n << " seleccionada no existe \n";
		cout << "------------------------------------------------------------ \n";
		return;
	}

	// Recorremos las filas guardando el valor de la columna 
	for (int i = 1; i < n; i++)
	{
		row = row->next;
		col = row->value;
	}
	// Recorremos ahora las columnas hasta la que el usuario ingreso
	for (int i = 1; i < m; i++)
	{
		col = col->next;
	}

	// Mostramos por consola la cela seleccionado y su valor actual
	cout << "Celda seleccionada: " << colLetter << n << " Valor: " << *(col->value) << "\n";
	cout << "------------------------------------------------------------\n";
	// Asignamos la celda seleccionada a la variable global selected_cell 
	selected_cell = col;
}

// creamos la funcion para que el usuario ingrese la fila y columna a seleccionar
void selectionCellPosition()
{	
	// definimos las variables para guardar la fila y columna ingresado por el usuario en este caso un char y un int
	char colLetter;
	int row;

	cout << "-------------------------------------------------- \n";

	// validamos a traves de un ciclo do while que el usuario ingrese una letra mayuscula que representa la columna que quiere seleccionar
	do
	{
		cout << "Ingrese la columna que quiere seleccionar: ";
		cin >> colLetter;
		if (colLetter < 65 || colLetter > 90)
		{
			cout << "-------------------------------------------------- \n";
			cout << "Error! Ingrese una letra mayuscula\n";
			cout << "-------------------------------------------------- \n";
		}
	} while (colLetter < 65 || colLetter > 90);
	
	// Verificamos que el usuario ingrese una fila positiva 
	do{
		cout << "Ingrese la fila que quiere seleccionar: ";
		cin >> row;
		cout << "-------------------------------------------------- \n";
		if(row <0 ){
			cout << "Error! Ingrese un numero positivo \n";
			cout << "-------------------------------------------------- \n";
		}
	}while(row < 0);

	// asignamos el valor de la fila a la varibale n
	int n = row;
	// convertimos el caracter a su respectivo valor ascii y le restamos 64 para obtener el valor de la columna
	int m = int(colLetter) - 64;

	// Finalmente pasamos los valores de la fila y columna a la funcion selectPositionCell 
	selectPositionCell(n, m, colLetter);
}


// Funcion para ingresar un valor a la celda que este seleccionado en ese momento
void insertIntoCell()
{	
	// Definimos un string para obtener el valor que quiere ingresar el usuario
	string value;

	// Verificamos que el usuario ingrese como maximo 8 caracteres
	cout << "-------------------------------------------------- \n";
	do{
		cout << "Ingrese el valor que quiere escribir en la celda: ";
		cin >> value;
		if(value.length() > 8){
			cout << "-------------------------------------------------- \n";
			cout << "Error! Ingrese como maximo 8 caracteres \n";
			cout << "-------------------------------------------------- \n";
		}
	}while(value.length() > 8);

	cout << "-------------------------------------------------- \n";
	// Asignamos el valor a la celda seleccionada a traves de la variable global selected_cell accediendo al puntero value 
	*(selected_cell->value) = value;
}

bool showMenu()
{

	cout << RESET_FONT;
	bool salir = false;
	int option;
	cout << "Opciones para hoja de calculo" << endl;
	cout << "1) Escribir en celda" << endl;
	cout << "2) Saltar a celda" << endl;
	cout << "3) Copiar" << endl;
	cout << "4) Cortar" << endl;
	cout << "5) Pegar" << endl;
	cout << "6) Celda izquierda" << endl;
	cout << "7) Celda derecha" << endl;
	cout << "8) Celda Arriba " << endl;
	cout << "9) Celda Abajo" << endl;
	cout << "10) Guardar" << endl;
	cout << "11) Salir" << endl;
	cout << " Escoge una opcion: ";
	cin >> option;
	cin.ignore();

	switch (option)
	{
	case 1:
		break;
		insertIntoCell();
	case 2:
		selectionCellPosition();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		save(multilist, LIMIT);
		break;
	case 11:
		salir = true;
		break;
	default:
		break;
	}

	return salir;
}

int main()
{
	// Por defecto las consolas de windows no muestran los colores
	enableColorsWindows();

	// Hay dos menus que se muestran de forma consecutiva
	bool salir = false;
	bool close = false;

	do
	{

		salir = showMainMenu();
		if (salir == NULL)
		{
			return 0;
		}

	} while (!salir);

	selected_cell = start_row->value;
	do
	{
		salir = showMenu();
		showSheet(start_col, start_row, ROW_POS, COL_POS);

	} while (!salir);

	return 0;
}