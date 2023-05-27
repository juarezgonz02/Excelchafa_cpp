#include <string>

// Declaracion de la estructura de nodo
template <typename T>
struct Node
{
	T *value;
	Node<T> *next;
	Node<T> *back;
};

// Le damos un alias a las estructuras para facilitar lectura
typedef Node<string> COLUMN;
typedef Node<COLUMN> ROW;

/*
	Se podria decir que estas posiciones desde cual se van a imprimir los datos
*/
ROW *start_row;
COLUMN *start_col;

// MODIFICAR ESTA POS DE MEMORIA PARA CAMBIAR LA CELDA SELECCIONADA
COLUMN *selected_cell;
ROW *selected_row;
int selected_col;

// Crea la lista con los datos
void initList(ROW *data)
{

	ROW *row = data;

	/*
		Crear el primer nodo
	*/
	row->back = nullptr;
	// row->value->back = nullptr;

	/*
		Crear cada nodo y avanzar
	*/
	for (int i = 0; i < LIMIT; i++)
	{

		// Inicializar los nodos
		row->value = new COLUMN();
		row->next = new ROW();
		row->next->back = row;

		COLUMN *col = row->value;

		// Inicializar las columnas y llenarlas
		for (int j = 0; j < LIMIT; j++)
		{

			// TEST: col->value = new string(to_string(i * 25 + j));
			// Se crea cada celda con el valor "'"
			col->value = new string("");

			if (j == 0)
			{
				col->back = nullptr;
			}

			if (j == LIMIT - 1)
			{
				col->next = nullptr;
			}
			else
			{
				col->next = new COLUMN();
				col->next->back = col;
				col = col->next;
			}
		}

		if (i == LIMIT - 1)
		{

			// El final de la lista debe guardarse con un nullptr
		}
		else
		{
		}
		
		row = row->next;
		col = row->value;
	}

	row->next = nullptr;

	/*
	Estas variables se encargan de dar seguimiento de donde
	se encuentra la celda seleccionada y cuales datos se estan
	mostrando
	*/
	start_row = data;
	start_col = start_row->value;
	selected_row = data;
	selected_col = 0;

	selected_cell = data->value;
}