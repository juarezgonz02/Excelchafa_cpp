#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "../libs/rapidjson/document.h"     // rapidjson's DOM-style API
#include "../libs/rapidjson/prettywriter.h" // for stringify JSON
#include "data.cpp"
#include <vector>
#include <algorithm>

using namespace rapidjson;
using namespace std;
#define BG_GREEN "\033[42m"
#define RESET_FONT "\033[0m"
#define BOLDBLACK "\033[1m\033[30m"

//
string ruta = "saves/";
string file_name = "";
string *json_str;

void initWithData(ROW *data);

void save(ROW *save_data, int n)
{
    try{

    COLUMN *data = save_data->value;

    filesystem::create_directory("saves/");

    if (file_name == "")
    {

        cout << "Nombre del libro: "
             << "\n";
        cin >> file_name;

        file_name += ".json";
    }

    Document document;

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);

    writer.StartObject();

    // TODO
    for (int i = 0; i < n; i++)
    {
        writer.Key(to_string(i).c_str());
        writer.StartArray();

        for (int j = 0; j < n; j++)
        {
            string val = *(data->value);
            writer.String(val.c_str());

            data = data->next;
        }

        if(save_data->next == nullptr){
            writer.EndArray();
            continue;
        }

        save_data = save_data->next;
        data = save_data->value;
        writer.EndArray();
    }

    writer.EndObject();

    ofstream ofs(ruta + file_name);
    ofs << buffer.GetString();
    ofs.close();

    cout << BG_GREEN << BOLDBLACK << "Se guardo correctamente" << RESET_FONT << "\n"
         << "\n";
    }
    catch(exception e){
        cout << e.what() << endl;
    }
}

void showFiles()
{
    string folderPath = ruta;
    vector<filesystem::directory_entry> files;

    // iterate over files in folder and add to vector
    for (const auto &entry : filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry);
        }
    }

    // sort files by date of last modification
    sort(files.begin(), files.end(), [](const auto &a, const auto &b)
         { return filesystem::last_write_time(a.path()) < filesystem::last_write_time(b.path()); });

    // print sorted list of file names and dates
    int i = 0;
    cout << "Escoge un archivo"
         << "\n";

    for (const auto &file : files)
    {

        cout << i << ") " << file.path().filename().string() << "\n";
        i++;
    }

    int fileOpt = 0;
    cout << "Ingresa el numero: ";
    cin >> fileOpt;

    file_name = files[fileOpt].path().filename().string();
}

void initWithData(ROW *data)
{

    ROW *row = data;

    /*
        Crear el primer nodo
    */
    row->back = NULL;

    /*
     *
     */
    ifstream ifs(ruta + file_name);

    if (!ifs.is_open())
    {
        cerr << "Error al abrir el archivo: " << file_name << endl;
        return;
    }

    string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    ifs.close();

    Document document;
    document.Parse(content.c_str());

/*
    Crear cada nodo y avanzar
*/
#define LIMIT 25

    for (int i = 0; i < LIMIT; i++)
    {

		// Inicializar los nodos
		row->value = new COLUMN();
		row->next = new ROW();
		row->next->back = row;

		COLUMN *col = row->value;

        const Value &numbers = document[to_string(i).c_str()];
        assert(numbers.IsArray());

        // Inicializar las columnas y llenarlas
        for (SizeType j = 0; j < LIMIT; j++)
        {

            // Se crear cada celda con el valor encontrado
            col->value = new string(numbers[j].GetString());

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
