#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
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
        save_data = save_data->next;
        data = save_data->value;
        writer.EndArray();
    }

    writer.EndObject();

    ofstream ofs(ruta + file_name);
    ofs << buffer.GetString();
    ofs.close();


    cout << BG_GREEN << BOLDBLACK << "Se guardo correctamente" << RESET_FONT << "\n" << "\n" ;
}



void showFiles() {
    string folderPath = ruta;
    vector<filesystem::directory_entry> files;

    // iterate over files in folder and add to vector
    for (const auto& entry : filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry);
        }
    }

    // sort files by date of last modification
    sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
        return filesystem::last_write_time(a.path()) < filesystem::last_write_time(b.path());
    });

    // print sorted list of file names and dates
    int i = 0; 
    cout << "Escoge un archivo" << "\n";

    for (const auto& file : files) {

        cout << i << ") " << file.path().filename().string() << "\n";
        i++; 
    }

    int fileOpt = 0;
    cout << "Ingresa el numero: "; 
    cin >> fileOpt;

    file_name = files[fileOpt].path().filename().string();
}

void initWithData(ROW* data){

	ROW *row = data;

	/*
		Crear el primer nodo
	*/
	row->back = NULL;
	row->value = new COLUMN();


    ifstream ifs(ruta+file_name);

    if (!ifs.is_open()) {
        cerr << "Failed to open file: " << file_name <<endl;
        return;
    }

    string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    ifs.close();

    Document document;
    document.Parse(content.c_str());

	/*
		Crear el cada nodo y avanzar
	*/
    #define LIMIT 25
    
	for (int i = 0; i < LIMIT; i++)
	{

		// Inicializar los nodos
		row->value = new COLUMN();
		row->next = new ROW();
		row->back = row;
		COLUMN *col = row->value;


        const Value& numbers = document[to_string(i).c_str()];
        assert(numbers.IsArray());


		// Inicializar las columnas y llenarlas
		for (SizeType j = 0; j < LIMIT; j++)
		{

			// TODO: AQUI EL VALOR DE LA
			//col->value = new string(to_string(i * 25 + j));
			//col->value = new string("");

			col->value = new string(numbers[j].GetString());
			
            col->back = col;
			col->next = new COLUMN();
			col = col->next;
		}
		row = row->next;
		col = row->value;
	}

}
