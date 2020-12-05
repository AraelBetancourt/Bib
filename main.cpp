#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
using namespace std;


/*Declaracion de Estructuras*/
struct Alumno{
	string Nombre;
	string Matricula;
};
struct Prestamos{
	string Matricula;
	string IdLibro;
	int DiasPrestados;
};

struct Libro{
	string Id;
	string Titulo;
	string Autor;
	string Editorial;
	int TotalLibros;
};

/*Declaracion de Variables*/
vector<Alumno> Alumnos;
vector<Libro> Libros;
vector<Prestamos> LibrosPrestados;
void menuAlumnos();
void menu();
void menuLibros();
void menuBusqueda();
void MostrarAlumnos();
void MostrarLibros();
void AgregarAlumno();
void AgregarLibro();
void GuardarAlumnos();
void EliminaAlumno();
void RespaldarDatos();
void RespaldoAlumnos();
void RespaldoLibros();
void MostrarLibrosPrestados();
void MostrarLibrosDisponibles();
int getLibrosDisponibles(string id);
Libro GetLibro(string id);
Alumno GetAlumno(string id);
string getTexto(string leyenda);

/*Este sirve para realizar el split y dividir una cadena de caracteres mediante caracteres*/
void tokenize(string &str, char delim, vector<string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}
/* Estas Funciones Guardan los archivos */
void GuardarAlumnos(){
    ofstream myfile;
    myfile.open ("Alumnos.txt");
    for(int i=0;i<Alumnos.size();i++){
        myfile<<Alumnos[i].Matricula+","+Alumnos[i].Nombre+"\n";
    }
    myfile.close();
}
void GuardaLibros(){
    ofstream myfile;
    myfile.open ("Libros.txt");
    for(int i=0;i<Libros.size();i++){
        myfile<<Libros[i].Id+","+Libros[i].Titulo+","+Libros[i].Autor+","+Libros[i].Editorial+"\n";
    }
    myfile.close();
}
void RespaldoAlumnos(){
    ofstream myfile;
    myfile.open ("Alumnos.txt");
    for(int i=0;i<Alumnos.size();i++){
        myfile<<Alumnos[i].Matricula+","+Alumnos[i].Nombre+"\n";
    }
    myfile.close();
}
void RespaldoLibros(){
    ofstream myfile;
    myfile.open ("Libros.txt");
    for(int i=0;i<Libros.size();i++){
        myfile<<Libros[i].Id+","+Libros[i].Titulo+","+Libros[i].Autor+","+Libros[i].Editorial+"\n";
    }
    myfile.close();
}

/*Funciones para la carga inicial de los archivos*/
vector<Libro> lecturaLibros() {
    vector<Libro> elementos;
	//cout<<"Cargando Libros\n";
	string myText;
	ifstream MyReadFile("Libros.txt");
	while (getline (MyReadFile, myText)) {
		if(myText!=""){
			//cout << myText+"\n";
			vector<string> a;
			tokenize(myText,',',a);
			Libro l;
			l.Id=a[0];
			l.Titulo=a[1];
			l.Autor=a[2];
			l.Editorial=a[3];
			l.TotalLibros=stoi(a[4]);
			elementos.push_back(l);
        }
	}
	MyReadFile.close();
	return elementos;
}

vector<Prestamos> lecturaPrestamos() {
	vector<Prestamos> elementos;
	//cout<<"Cargando Alumnos\n";
	string myText;
	ifstream MyReadFile("Prestamos.txt");
	while (getline (MyReadFile, myText)) {
		if(myText!=""){
			//cout << myText+"\n";
			vector<string> a;
			tokenize(myText,',',a);
			Prestamos p;
			p.Matricula=a[0];
			p.IdLibro=a[1];
			p.DiasPrestados=stoi(a[2]);
			elementos.push_back(p);
        }
	}
	MyReadFile.close();
	return elementos;
}
vector<Alumno> lecturaAlumnos() {
	vector<Alumno> elementos;
	//cout<<"Cargando Alumnos\n";
	string myText;
	ifstream MyReadFile("Alumnos.txt");
	while (getline (MyReadFile, myText)) {
		if(myText!=""){
			//cout << myText+"\n";
			vector<string> a;
			tokenize(myText,',',a);
			Alumno o;
			o.Matricula=a[0];
			o.Nombre=a[1];
			elementos.push_back(o);
        }
	}
	MyReadFile.close();
	return elementos;
}
/*funciones de validaciones*/
bool ValidaMatricula(string mattemp){
    for(int i=0;i<Alumnos.size();i++){
        if(mattemp==Alumnos[i].Matricula){
            return true;
        }
    }
    return false;
}
bool ValidaIdLibro(string idtemp){
    for(int i=0;i<Libros.size();i++){
        if(idtemp==Libros[i].Id){
            return true;
        }
    }
    return false;
}
/*Funciones para agergar datos */
void AgregarAlumno(){
    system("CLS");
    Alumno alum;
    cout<<"Matricula: ";
    cin>>alum.Matricula;
    if(ValidaMatricula(alum.Matricula)){
        cout<<"Matricula repetida\n";
        system("pause");
    }else{
        cout<<"\n";
        alum.Nombre=getTexto("Nombre");
        Alumnos.push_back(alum);
        GuardarAlumnos();
    }
}
void AgregarLibro(){
    system("CLS");
    Libro lib;
    cout<<"Id: ";
    cin>>lib.Id;
    if(ValidaIdLibro(lib.Id)){
        cout<<"Id Libro repetido\n";
        system("pause");
    }else{
        cout<<"\n";
        lib.Titulo =getTexto("Titulo");
        lib.Autor=getTexto("Autor");
        lib.Editorial=getTexto("Editoriar");
        Libros.push_back(lib);
        GuardaLibros();
    }
}
void EliminaAlumno(){
    system("CLS");
    string Matricula;
    cout<<"Matricula: ";
    cin>>Matricula;
    if(!ValidaMatricula(Matricula)){
        cout<<"El Alumno no se encuentra en la lista\n";
        system("pause");
    }else{
        vector<Alumno> AlumnosTemp;
        for(int i=0;i<Alumnos.size();i++){
            if(Matricula==Alumnos[i].Matricula){
                cout<<"Se eliminio al alumno "+Matricula+"\n";
                system("pause");
            }else{
                AlumnosTemp.push_back(Alumnos[i]);
            }
        }
        Alumnos=AlumnosTemp;
        GuardarAlumnos();
    }
}
void menuAlumnos() {
	while(true){
        system("CLS");
        int respuesta=0;
	    cout<<"1.- Mostrar Alumnos\n";
	    cout<<"2.- Agregar Alumno\n";
	    cout<<"3.- Baja Alumno\n";
	    cout<<"4.- Menu Anterior\n";
	    cin>>respuesta;
	    switch(respuesta){
			case 1:
				MostrarAlumnos();
				break;
			case 2:
				AgregarAlumno();
				break;
            case 3:
				EliminaAlumno();
				break;
            case 4:
				menu();
				break;
			default:
                cout<<"Opcion no Valida\n";
                system("pause");
				break;
		}
	}
}
void menuBusqueda() {
	while(true){
        system("CLS");
        int respuesta=0;
	    cout<<"1.- Libros Disponibles\n";
        cout<<"1.- Libros Prestados\n";
	    cout<<"3.- Menu Anterior\n";
	    cin>>respuesta;
	    switch(respuesta){
			case 1:
				MostrarLibrosDisponibles();
				break;
			case 2:
				MostrarLibrosPrestados();
				break;
            case 3:
				menu();
				break;
			default:
                cout<<"Opcion no Valida\n";
                system("pause");
				break;
		}
	}
}
void menuLibros() {
	while(true){
        int respuesta=0;
        system("CLS");
	    cout<<"1.- Mostrar Libros\n";
	    cout<<"2.- Agregar Libro\n";
	    cout<<"3.- Menu Anterior\n";
	    cin>>respuesta;
	    switch(respuesta){
			case 1:
				MostrarLibros();
				break;
			case 2:
				AgregarLibro();
				respuesta=0;
				break;
            case 3:
				menu();
				break;
			default:
                cout<<"Opcion no Valida\n";
                system("pause");
				break;
		}
	}
}

void menu() {
	int respuesta=0;
	while(true){
        system("CLS");
	    cout<<"1.- Prestamo de Libro(s)\n";
	    cout<<"2.- entrega de Libro(s)\n";
	    cout<<"3.- Busqueda\n";
	    cout<<"4.- Alumnos\n";
	    cout<<"5.- Libros\n";
	    cout<<"6.- Respaldar Datos\n";
	    cout<<"7.- Salir del Sistema\n";
	    cin>>respuesta;
	    switch(respuesta){
			case 1:
				cout<<"1.- Prestamo de Libro(s)\n";
				break;
			case 2:
				cout<<"2.- entrega de Libro(s)\n";
				break;
			case 3:
				menuBusqueda();
				break;
			case 4:
				menuAlumnos();
				break;
            case 5:
				menuLibros();
				break;
            case 6:
				RespaldarDatos();
				break;
            case 7:
				exit(EXIT_SUCCESS);
				break;
            default:
                cout<<"Opcion no Valida\n";
                system("pause");
                break;
		}
		respuesta=0;
	}
}

void RespaldarDatos(){

}
/*Funciones para mostrar datos*/
void MostrarAlumnos(){
    system("CLS");
    cout<<"Lista de todos los ALumnos\n";
    for(int i=0;i<Alumnos.size();i++){
        cout<<Alumnos[i].Nombre+" Matricula: "+Alumnos[i].Matricula+"\n";
    }
    system("pause");
}

void MostrarLibrosDisponibles(){
    system("CLS");
    cout<<"Relacion de todos los Libros disponibles\n";
    for(int i=0;i<Libros.size();i++){
        int LibrosDisponibles=getLibrosDisponibles(Libros[i].Id);
        int TotalLibros = Libros[i].TotalLibros-LibrosDisponibles;
        if(TotalLibros>0){
            cout<<" El Libro "+Libros[i].Titulo+" Tiene Disponibilidad de "+std::to_string(TotalLibros)+"\n";
        }
    }
    system("pause");
}

void MostrarLibrosPrestados(){
    system("CLS");
    cout<<"Relacion de todos los Libros Prestados\n";
    for(int i=0;i<LibrosPrestados.size();i++){
        Alumno a = GetAlumno(LibrosPrestados[i].Matricula);
        Libro l = GetLibro(LibrosPrestados[i].IdLibro);
        cout<<l.Titulo+" Esta prestado al Alumno "+a.Nombre+"\n";
    }
    system("pause");
}
void MostrarLibros(){
    system("CLS");
    cout<<"Lista de todos los ALumnos \n";
    for(int i=0;i<Libros.size();i++){
        cout<<"Id: "+Libros[i].Id+" Titulo: "+Libros[i].Titulo+" Total Libros "+std::to_string(Libros[i].TotalLibros)+"\n";
    }
    system("pause");
}
/*Funciones para obtener un dato en espesifico*/
Libro GetLibro(string id){
    for(int i=0;i<Libros.size();i++){
        if(Libros[i].Id==id){
            return Libros[i];
        }
    }
}

int getLibrosDisponibles(string id){
    int Disponible=0;
    for(int i=0;i<LibrosPrestados.size();i++){
        if(LibrosPrestados[i].IdLibro==id){
            Disponible=Disponible+1;
        }
    }
    return Disponible;
}

Alumno GetAlumno(string id){
    for(int i=0;i<Alumnos.size();i++){
        if(Alumnos[i].Matricula==id){
            return Alumnos[i];
        }
    }
}

/*Funcio que ayuda a obtener el texto de concola*/
string getTexto(string leyenda){
    string texto;
    cout<<leyenda+": ";
    cin.ignore();
    getline(cin, texto);
    return texto;
}

/*Funciones principales*/
int main(int argc, char** argv) {
    Alumnos = lecturaAlumnos();
    Libros = lecturaLibros();
    LibrosPrestados=lecturaPrestamos();
	menu();
	return 0;
}

