#include <iostream>
#include <string>
#include "utils/display.cpp"
#include "utils/saves.cpp"

using namespace std;

bool showMenu();
bool showMainMenu();
void changeSelectedCell(COLUMN *col, int n, int m);
void selectPositionCell(int row_move, int col_move, char colLetter);

// Aqui empieza la lista, la posicion 0,0
ROW *multilist = new ROW();

// variables utilizadas para copiar, cortar y pegar
string clipboard = "";

/*
Imprime la multilist en formato hoja de calculo
*/
void showSheet(COLUMN *col_mem, ROW *row_mem, int n, int m)
{

	string BG;

	if (checkNotOutShowingRightBound(n))
	{
		n = LIMIT - SHOWLIMIT;
	}

	if (checkNotOutShowingRightBound(m))
	{
		m = LIMIT - SHOWLIMIT;
	}

	ROW *row = row_mem;
	COLUMN *col = row_mem->value;

	drawColumnsHeader(n, m);

	for (int i = 0; i < SHOWLIMIT; i++)
	{

		for (int k = 0; k < SHOW_FROM_COL; k++)
		{
			col = col->next;
		}

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
				cout << printCell(val, 0, false, true);
				cout << BG;
			}
			else
			{
				cout << printCell(val, 0, false, false);
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
		initList(multilist);
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
	do
	{
		cout << "Ingrese la fila que quiere seleccionar: ";
		cin >> row;
		cout << "-------------------------------------------------- \n";
		if (row < 0)
		{
			cout << "Error! Ingrese un numero positivo \n";
			cout << "-------------------------------------------------- \n";
		}
	} while (row < 0);

	// asignamos el valor de la fila a la varibale n
	int n = row;
	// convertimos el caracter a su respectivo valor ascii y le restamos 64 para obtener el valor de la columna
	int col = int(colLetter) - 64;

	// Finalmente pasamos los valores de la fila y columna a la funcion selectPositionCell
	selectPositionCell(row, col, colLetter);
}

// Funcion para seleccionar una celda a traves de la fila y columna ingresado por el usuario
void selectPositionCell(int row_move, int col_move, char colLetter)
{
	// Definimos los punteros de la fila y columna
	ROW *row = multilist;
	COLUMN *col = row->value;

	// Verificamos que la celda seleccionado por el usuario se encuentre dentro del rango de la hoja de calculo
	if (row_move > 25 || col_move > 25)
	{
		// cout << row_move << "  " << col_move << "\n";
		cout << "La celda " << colLetter << row_move << " seleccionada no existe \n";
		return;
	}

	// Verificamos que no se pueda seleccionar una celda de tipo cabecera
	if (row_move == 0)
	{
		cout << "La celda " << colLetter << row_move << " seleccionada no existe \n";
		cout << "------------------------------------------------------------ \n";
		return;
	}

	// Recorremos las filas guardando el valor de la columna
	for (int i = 1; i < row_move; i++)
	{
		row = row->next;
	}

	// La row actual
	selected_row = row;

	col = row->value;
	// Recorremos ahora las columnas hasta la que el usuario ingreso
	for (int i = 1; i < col_move; i++)
	{
		col = col->next;
	}

	selected_col = col_move - 1;

	// Mostramos por consola la cela seleccionado y su valor actual
	cout << "Celda seleccionada: " << colLetter << row_move << " Valor: " << *(col->value) << "\n";
	cout << "------------------------------------------------------------\n";

	// Asignamos la celda seleccionada a la variable global selected_cell con la funcion, changeSelectedCell()
	changeSelectedCell(col, row_move - 1, col_move - 1);
}
void changeSelectedCell(COLUMN *col, int row_move, int col_move)
{
	// checkIfIsVisible()
	bool ROWVISIBLE = SHOW_FROM_ROW < row_move && row_move < SHOW_FROM_ROW + SHOWLIMIT;
	bool COLVISIBLE = SHOW_FROM_COL < col_move && col_move < SHOW_FROM_COL + SHOWLIMIT;
	selected_cell = col;

	if (!(ROWVISIBLE && COLVISIBLE))
	{
		if (checkNotOutShowingRightBound(row_move))
		{
			row_move = LIMIT - SHOWLIMIT;
		}

		if (checkNotOutShowingLeftBound(row_move))
		{
			row_move = 0;
		}

		if (SHOW_FROM_ROW < row_move)
		{
			for (int i = 0; i < row_move - SHOW_FROM_ROW; i++)
			{
				start_row = start_row->next;
			}
		}
		else
		{
			for (int i = 0; i < SHOW_FROM_ROW - row_move; i++)
			{
				start_row = start_row->back;
			}
		}

		if (checkNotOutShowingRightBound(col_move))
		{
			col_move = LIMIT - SHOWLIMIT;
			start_col = start_row->value;
		}
		else
		{
			start_col = col;
		}

		if (checkNotOutShowingLeftBound(col_move))
		{
			col_move = 0;
			start_col = start_row->value;
		}
		else
		{
			start_col = col;
		}

		SHOW_FROM_ROW = row_move;
		SHOW_FROM_COL = col_move;
	}
}

// Funcion para ingresar un valor a la celda que este seleccionado en ese momento
void insertIntoCell()
{
	// Definimos un string para obtener el valor que quiere ingresar el usuario
	string value = "";

	// Verificamos que el usuario ingrese como maximo 8 caracteres
	cout << "-------------------------------------------------- \n";

	do
	{
		cout << "Ingrese el valor que quiere ingresar a la celda: ";
		getline(cin, value);
		if (value.length() > 8)
		{
			cout << "-------------------------------------------------- \n";
			cout << "Error! Ingrese un valor de maximo 8 caracteres \n";
			cout << "-------------------------------------------------- \n";
		}
	} while (value.length() > 8);

	cout << "-------------------------------------------------- \n";
	// Asignamos el valor a la celda seleccionada a traves de la variable global selected_cell accediendo al puntero value
	*(selected_cell->value) = value;
}

// Funcion para copiar una celda
void copyCell()
{
	// Se guarda el portapapeles el valor seleccionado
	clipboard = *(selected_cell->value);

	cout << "COPIADO !"
		 << "\n\n";
}

// Funcion para pegar datos en una celda
void pageCell()
{
	// Asignamos el valor del portapapeles en la celda
	*(selected_cell->value) = clipboard;
}

// Funcionar para cortar datos de una celda
void cutCell()
{
	// Cortamos el valor de la celda y se guarda en portapapeles
	copyCell();
	*(selected_cell->value) = "";

	cout << "CORTADO !"
		 << "\n\n";
}

void moveCellUp()
{
	// Verificar si la celda actual está en la primera fila
	if (selected_row->back != nullptr)
	{

		// Mover la fila mostrada hacia arriba
		selected_row = selected_row->back;

		selected_cell = selected_row->value;

		// Actualizar la celda seleccionada
		for (int i = 0; i < selected_col; i++)
		{

			selected_cell = selected_cell->next;
		}

		changeSelectedCell(selected_cell, SHOW_FROM_ROW - 1, SHOW_FROM_COL);
	}
}

void moveCellRight()
{
	// Verificar si la celda actual tiene una siguiente fila
	if (selected_cell->next != nullptr)
	{
		// Mover a la siguiente fila
		selected_cell = selected_cell->next;
		selected_col++;
		changeSelectedCell(selected_cell, SHOW_FROM_ROW, SHOW_FROM_COL + 1);
	}
}

void moveCellLeft()
{

	if (selected_cell->back != nullptr)
	{
		// Mover a la columna anterior
		selected_cell = selected_cell->back;
		selected_col--;
		changeSelectedCell(selected_cell, SHOW_FROM_ROW, SHOW_FROM_COL - 1);
	}
}

void moveCellDown()
{
	// Verificar si la celda actual está en la primera fila
	if (selected_row->next->next != nullptr)
	{

		// Mover la fila mostrada hacia abajo
		selected_row = selected_row->next;

		selected_cell = selected_row->value;

		// Actualizar la celda seleccionada
		for (int i = 0; i < selected_col; i++)
		{

			selected_cell = selected_cell->next;
		}

		changeSelectedCell(selected_cell, SHOW_FROM_ROW + 1, SHOW_FROM_COL);
	}
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
		insertIntoCell();
		break;
	case 2:
		selectionCellPosition();
		break;
	case 3:
		copyCell();
		break;
	case 4:
		cutCell();
		break;
	case 5:
		pageCell();
		break;
	case 6:
		moveCellLeft();
		break;
	case 7:
		moveCellRight();
		break;
	case 8:
		moveCellUp();
		break;
	case 9:
		moveCellDown();
		break;
	case 10:
		save(multilist, LIMIT);
		break;
	case 11:
		// TODO: SALIR SIN GUARDAR CAMBIOS
		salir = true;
		break;
	default:
		break;
	}

	return salir;
}

int main()
{
	// Por defecto las consolas de windows no muestran los colores ANSI
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
		showSheet(start_col, start_row, SHOW_FROM_ROW, SHOW_FROM_COL);
		salir = showMenu();

	} while (!salir);

	return 0;
}