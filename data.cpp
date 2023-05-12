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
