#include <iostream>
#include <string>
#include "utils/options.cpp"

using namespace std;

bool showMenu();
bool showMainMenu();
void showSheet(COLUMN *col_mem, ROW *row_mem, int n, int m);

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

bool showMenu()
{
    bool saved = false;

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
        saved = false;
        break;
    case 2:
        selectionCellPosition();
        break;
    case 3:
        copyCell();
        break;
    case 4:
        cutCell();
        saved = false;
        break;
    case 5:
        pageCell();
        saved = false;
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
        saved = true;
        break;

    case 11:
        if (!saved)
        {
            char ans;
            cout << "Desea salir sin guardar los cambios? (Y/N) "
                 << "\n";
            cin >> ans;

            if (ans == 'Y' || ans == 'y')
            {
                salir = true;
            }
            else if (ans == 'N' || ans == 'n')
            {
                save(multilist, LIMIT);
                salir = true;
            }
            else
            {
                cout << "Opción incorrecta "
                     << "\n";
            }
        }
        else
        {
            salir = true;
        }
        break;
    default:
        break;
    }

    return salir;
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