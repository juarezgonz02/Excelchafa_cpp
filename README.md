## Primera Tarea Práctica grupal

### **Integrantes**
- Oscar Alexander Juárez González 00126320 
- Andrea María Peña Hernandez 00075919
- Diego Alessandro Rodríguez Villalta 00101519
- Victor Rafael Valenzuela Cortez 00022120

**Aspectos a considerar*

### Requisitos para compilar
- Windows 10
- Compilador compatible con C++ 17 como GCC v9+
> La compilación en Linux requiere eliminar la dependecia <Windows.h> y la función asociada a esta en "utils/display.cpp"

### Distribución del proyecto
```

├───builds/
│   └───excelchafa_v1.exe/  || Windows Build
│
├───Docs/                   || Diagramas de flujo
│   └───Diagrama de flujo HojaDeCalculo.png
│
├───libs/                   || Librerias adicionales
│   └───rapidjson/          || - Libreria para el manejo de archivos JSON
│
├───saves/                  || Archivos de guardado JSON
│   ├───ej.json/
│   └───ac/
│   
├───utils/                  || Código para el funcionamiento del programa
│   ├───data.cpp
│   ├───display.cpp
│   ├───options.cpp
│   └───saves.cpp
│   
├───README.md
└───main.cpp                || Punto de inicio del programa

```

- main.cpp Tiene el código principal donde se muestra la multilista.
- Options.cpp Tiene el código de cada opción del menú mostrado en Main, basicamente llama a todas las funcionalidaes 
- display.cpp Tiene código para darle estilos a la consola (para la consola de windows, pues si tiene alguna distribución de Linux como Ubuntu, esta ya trae la paleta de colores.)
- data.cpp Tiene las definiciones de los tipos de datos para su uso en otros archivos., Ahí mismo se crean la multilist cuando no hay datos.
- saves.cpp Permite guardar, cargar archivos, y crear la multilist a partir de esta información.

El repositorio tiene un formato de 3 carpeta, la primera donde se encuentra el código fuente, es decir, todo lo relacionado al programa creado, la segunda carpeta donde se encontrará un documento de word, donde se explicará la estructura interna de nuestra aplicación y la última carpeta contiene una iamgen del DFD de como es el flujo de utilización de nuestra aplicación.
