#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <cstring>

#define RutaAsegurados "Asegurados.BAK"
#define RutaLote1 "Lote1"
using namespace std;

struct Poliza
{
    int NumeroPoliza, Dni, CantIncidentes;
    char Nombre[30], Apellido[30], Patente[8];
    bool CuotaAlDia, Activa;
};

struct Incidente
{
    int Codigo, Fecha, DniAsegurado, DniOtroConductor, NumeroPoliza, Altura;
    char Calle[50];
};

struct NodoIncidente
{
    Incidente Info;
    NodoIncidente *sgte;
};

struct NodoPoliza
{
    Poliza Info;
    NodoPoliza *sgte;
};

void InsertarSiguientePoliza(NodoPoliza *&nodo, Poliza poliza)
{
    NodoPoliza *nuevo = new NodoPoliza();
    nuevo->Info = poliza;

    if (nodo)
    {
        nuevo->sgte = nodo->sgte;
        nodo->sgte = nuevo;
    }
    else
    {
        nuevo->sgte = nodo;
        nodo = nuevo;
    }
    return;
}

void LevantarAsegurados(NodoPoliza *&raiz)
{

    FILE *archivo;
    Poliza aux;
    if(archivo = fopen(RutaAsegurados, "rb"))
    {
        fread(&aux,sizeof(Poliza),1,archivo);
        while(!feof(archivo))
        {
            InsertarSiguientePoliza(raiz, aux);
            fread(&aux,sizeof(Poliza),1,archivo);
        }
        fclose(archivo);
    }
    return;
}
int cantNodos(NodoPoliza *x)
{
    int cont;
    if (x)
    {
        while (x)
        {
            cont++;
            x = x->sgte;
        }
    }
    return cont;
}

void descactivarPoliza(NodoPoliza *&x, int num )
{
    NodoPoliza *aux = x;
    int i = 0;
    while(aux && aux->Info.NumeroPoliza != num && i<cantNodos(x))
    {
        i++;
        aux = aux->sgte;
    }
    if(aux == NULL)
        cout << "Lista vacia" << endl;
    else
    {
        aux->Info.Activa = false;
        cout << "Poliza "<<num<<" desactivada." << endl;
    }
    if(i>= cantNodos(x)){
         cout << "No existe poliza coincidente." << endl;
    }
    return;
}

void mostrarPoliza(Poliza x)
{
    cout << "Nombre: " << x.Nombre << endl;
    cout << "Apellido: " << x.Apellido << endl;
    cout << "Patente: " << x.Patente << endl;
    cout << "DNI: " << x.Dni << endl;
    cout << "Numero de poliza: " << x.NumeroPoliza << endl;
    cout << "Cantidad de incidentes: " << x.CantIncidentes << endl;
    cout << "--------------------------------------------------"<<endl;
}


void CargarPoliza(Poliza &x)
{
    char Nombre[30], Apellido[30], Patente[10];
    int Dni, NroPoliza,CIncidentes;
    cout << "Ingrese el Nombre:" << endl;
    cin >> Nombre;
    while (strlen(Nombre) > sizeof(char[30]))
    {
        cout << "Nombre demasiado largo. Utilice una abreviacion:" << endl;
        cin >> Nombre;
    }
    strcpy(x.Nombre, Nombre);
    cout << "Ingrese el Apellido:" << endl;
    cin >> Apellido;
    while (strlen(Apellido) > sizeof(char[30]))
    {
        cout << "Nombre demasiado largo. Utilice una abreviacion:" << endl;
        cin >> Apellido;
    }
    strcpy(x.Apellido, Apellido);
    cout << "Ingrese la patente:" << endl;
    cin >> Patente;
    while (strlen(Patente) > sizeof(char[8]))
    {
        cout << "Por favor ingrese una patente valida:" << endl;
        cin >> Patente;
    }
    strcpy(x.Patente, Patente);
    cout << "Ingrese el DNI:" << endl;
    cin >> Dni;
    while (Dni>99999999 && Dni<10000000)
    {
        cout << "Por favor ingrese un DNI valido:" << endl;
        cin >> Dni;
    }
    x.Dni = Dni;
    cout << "Ingrese el numero de poliza:" << endl;
    cin >> NroPoliza;
    while (NroPoliza<0)
    {
        cout << "Por favor ingrese una poliza valida:" << endl;
        cin >> NroPoliza;
    }
    x.NumeroPoliza = NroPoliza;
    cout << "Ingrese la cantidad de incidentes:" << endl;
    cin >> CIncidentes;
    while (CIncidentes<0)
    {
        cout << "Por favor ingrese un numero valido:" << endl;
        cin >> CIncidentes;
    }
    x.CantIncidentes=CIncidentes;
    cout << "Ingrese si la poliza esta activa (1=Si/0=No):" << endl;
    cin >> x.Activa;
    while( x.Activa !=1 && x.Activa!=0)
    {
        cout << "Por favor ingrese un valor valido:" << endl;
        cin >> x.Activa;
    }
    cout << "Ingrese si tiene la cuota al dia (1=Si/0=No):" << endl;
    cin >> x.CuotaAlDia;
    while(x.CuotaAlDia !=1 && x.CuotaAlDia!=0)
    {
        cout << "Por favor ingrese un valor valido:" << endl;
        cin >> x.CuotaAlDia;
    }
    return;
}



NodoPoliza *encontrarUltimoPoliza(NodoPoliza *x)
{
    if (x)
    {
        while (x->sgte)
        {
            x = x->sgte;
        }
    }
    return x;
}
void CargarNuevaPoliza(NodoPoliza *&raiz)
{
    char opcion;
    Poliza asegurado;
    CargarPoliza(asegurado);
    NodoPoliza *aux = raiz;
    NodoPoliza *nuevo = new NodoPoliza();
    NodoPoliza *ultimo = NULL;
    while(aux && (asegurado.NumeroPoliza != aux->Info.NumeroPoliza))
    {
        aux = aux->sgte;
    }
    while(aux)
    {
        cout << "Esta poliza ya ha sido ingresada. ¿Desea reemplazarla? "<< endl;
        cout << " 1=SI / 0=NO :" << endl;
            do
                opcion = getch();
            while(opcion != '1' && opcion != '0');
            if (opcion == '1')
            {
                CargarPoliza(asegurado);
                while(aux && asegurado.NumeroPoliza != aux->Info.NumeroPoliza){
                aux = aux->sgte;
                }
            }
            else if (opcion == '0')
            {
                return;
            }

    }
        nuevo->Info = asegurado;
        nuevo->sgte = NULL;
    if (raiz)
    {

        ultimo = encontrarUltimoPoliza(raiz);
        ultimo->sgte = nuevo;
    }
    else
    {
        raiz = nuevo;
    }
    return;
}

NodoPoliza *buscarPolizaPorNumero(NodoPoliza *x, int Numero)
{
    NodoPoliza *aux=x;
    while (x && (x->Info.NumeroPoliza != Numero))
    {
        x = x->sgte;
    }
    return aux;
}
void buscarDNI(NodoPoliza *x, int DNI)
{
    /*Varias polizas pueden estar a nombre de una misma persona, por lo que se guardan temporalmente en un vector de structs*/
    Poliza *buscado;
    int c = cantNodos(x);
    int i=0;
    buscado = new Poliza[c];
    while(x)
    {
        if(x->Info.Dni == DNI)
        {
            buscado[i] = x->Info ;
            i++;
        }
        x = x->sgte;
    }
    if(i > 0)
    {
        cout << "Las polizas registradas con este DNI son: "<< endl;
        cout << "-------------------------------------------------"<< endl;
        for(int j=0; j<i; j++)
        {
            mostrarPoliza(buscado[j]);
            cout << "-------------------------------------------------"<< endl;
        }
    }
    else
    {
        cout<<"No hay polizas registradas a ese DNI."<< endl;
    }
    delete buscado;
    return;
}


void OrdenarPolizas(NodoPoliza *nodo)
{
    NodoPoliza *aux;
    NodoPoliza *proximo;
    Poliza x;
    aux = nodo;
    while(aux->sgte)
    {
        proximo = aux->sgte;
        while(proximo)
        {
            if(aux->Info.CantIncidentes < proximo->Info.CantIncidentes){
            x = proximo->Info;
            proximo->Info = aux->Info;
            aux->Info = x;
            }
            proximo = proximo->sgte;
        }
        aux = aux->sgte;
        proximo = aux->sgte;
    }
}

void MostrarPolizasActivas(NodoPoliza *nodo)
{
    int cont=0;
    NodoPoliza *aux=nodo;
    OrdenarPolizas(aux);
    cout << "--------------------------------------------------"<<endl;
    while (aux)
    {
        if (aux->Info.Activa==true)
        {
            cont++;
            mostrarPoliza(aux->Info);
            cout << endl;
        }
        aux = aux->sgte;
    }
    if (cont == 0)
        cout << "No hay polizas activas";
}

void escribirReporteHTML(NodoPoliza *raiz)
{
    FILE *f;
    NodoPoliza *aux=raiz;
    f = fopen("ReporteHTML.html", "wt");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Reporte de Poliza</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Patente</th><th>Apellidos</th><th>Nombres</th><th>NumeroDePoliza</th><th>Dni</th><th>CantIncidentes</th>\n");
    while (aux)
    {
        if((aux->Info.CuotaAlDia==false) && (aux->Info.Activa==true))
        {
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%d</td>\n",aux->Info.Patente,aux->Info.Apellido,aux->Info.Nombre,aux->Info.NumeroPoliza,aux->Info.Dni,aux->Info.CantIncidentes);
            fprintf(f,"</tr>\n");
        }
        aux=aux->sgte;
    }
    fprintf(f, "</table>");
    fprintf(f, "</body>");
    fprintf(f, "</html>");
    fclose(f);
    return;
}


void escribirReporteCSV(NodoPoliza *raiz)
{
    FILE *f;
    NodoPoliza *aux=raiz;
    f = fopen("ReporteExcel.csv", "wt");
    fprintf(f,"Patente;Apellido;Nombre;NumeroDePoliza;DNI;CantIncidentes\n");
    int i= 0;
    while (aux)
    {
        if ((aux->Info.CuotaAlDia==false) && (aux->Info.Activa==true))
        {
            fprintf(f,"%s;%s;%s;%d;%d;%d\n",aux->Info.Patente,aux->Info.Apellido,aux->Info.Nombre,aux->Info.NumeroPoliza,aux->Info.Dni,aux->Info.CantIncidentes);
        }
        aux=aux->sgte;
    }
    fclose(f);
    return;
}
void ProcesarAsegurados(NodoPoliza *&raiz)
{
    FILE *archivo;
    NodoPoliza *aux = raiz;
    Poliza asegurado;
    if(archivo = fopen(RutaAsegurados, "wb"))
    {
        while (aux)
        {
            if(aux->Info.Activa)
            {
                asegurado = aux ->Info;
                fwrite(&aux->Info,sizeof(Poliza),1,archivo);
            }
            aux = aux->sgte;
        }
        fclose(archivo);
    }

}
void borrarListaPoliza(NodoPoliza *&lista)
{
    NodoPoliza *anterior;
    NodoPoliza *paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux= lista;
        while (paux && paux->sgte)
        {
            anterior = paux;
            paux= paux->sgte;
        }
        if (paux)
        {
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista =NULL;
        }
    }
    return;
}

////////PUNTO 6
NodoIncidente *ObtenerUltimoIn(NodoIncidente * p)
{
    if (p)
    {
        while (p->sgte)
        {
            p = p->sgte;
        }
    }
    return p;
}
void InsertarSiguienteIncidente(NodoIncidente *&nodo, Incidente x)
{
    NodoIncidente *nuevo = new NodoIncidente();
    nuevo->Info = x;
    if (nodo)
    {
        nuevo->sgte = nodo->sgte;
        nodo->sgte = nuevo;
    }
    else
    {
        nuevo->sgte = NULL;
        nodo = nuevo;
    }
    return;
}

void LevantarIncidentes(NodoIncidente *&raiz)
{

    FILE *archivo;
    Incidente aux;
    if(archivo = fopen(RutaLote1, "rb"))
    {
        fread(&aux,sizeof(Incidente),1,archivo);
        while(!feof(archivo))
        {
            InsertarSiguienteIncidente(raiz, aux);
            fread(&aux,sizeof(Incidente),1,archivo);
        }
        fclose(archivo);
    }
    return;
}

void cargarIncidente(Incidente &x)
{
    char Calle[50];
    int Codigo,Fecha,DniAsegurado,DniOtroConductor,NroPoliza,Altura;
    cout << "Ingrese la calle donde ocurrio el incidente:" << endl;
    cin >> Calle;
    while (strlen(Calle) > sizeof(char[50]))
    {
        cout << "Nombre demasiado largo. Utilice una abreviacion:" << endl;
        cin >> Calle;
    }
    strcpy(x.Calle, Calle);
    cout << "Ingrese la altura de la calle:" << endl;
    cin >> Altura;
    while (Altura>99999 && Altura<0)
    {
        cout << "Por favor ingrese una altura valida:" << endl;
        cin >> Altura;
    }
    x.Altura = Altura;
    cout << "Ingrese el numero de poliza:" << endl;
    cin >> NroPoliza;
    while (NroPoliza<0)
    {
        cout << "Por favor ingrese una poliza valida:" << endl;
        cin >> NroPoliza;
    }
    x.NumeroPoliza = NroPoliza;
    cout << "Ingrese el DNI del asegurado:" << endl;
    cin >> DniAsegurado;
    while (DniAsegurado>99999999 && DniAsegurado<10000000)
    {
        cout << "Por favor ingrese un DNI valido:" << endl;
        cin >> DniAsegurado;
    }
    x.DniAsegurado=DniAsegurado;
    cout << "Ingrese el DNI del otro conductor:" << endl;
    cin >> DniOtroConductor;
    while (DniOtroConductor>99999999 && DniOtroConductor<10000000)
    {
        cout << "Por favor ingrese un DNI valido:" << endl;
        cin >> DniOtroConductor;
    }
    x.DniOtroConductor=DniOtroConductor;
    cout << "Ingrese la fecha(AAAAMMDD):" << endl;
    cin>>Fecha;
    while (Fecha>20300000 && Fecha<19801122)
    {
        cout << "Por favor ingrese una fecha valida:" << endl;
        cin >> Fecha;
    }
    x.Fecha=Fecha;
    return;
}

void CargarNuevoIncidente(NodoIncidente *&raiz)
{
    char opcion;
    Incidente x;
    cargarIncidente(x);
    NodoIncidente *aux = raiz;
    NodoIncidente *nuevo = new NodoIncidente();
    NodoIncidente *ultimo = NULL;
    while(aux && (x.Codigo != aux->Info.Codigo))
    {
        aux = aux->sgte;
    }
    while(aux)
    {
        cout << "Esta incidente ya ha sido ingresado. ¿Desea reemplazarlo? "<< endl;
        cout << " 1=SI / 0=NO :" << endl;
            do
                opcion = getch();
            while(opcion != '1' && opcion != '0');
            if (opcion == '1')
            {
                cargarIncidente(x);
                while(aux && ((aux->Info.Codigo) != (x.Codigo)))
                    aux = aux->sgte;
            }
            else if (opcion == '0')
            {
                return;
            }

    }
        nuevo->Info = x;
        nuevo->sgte = NULL;
    if (raiz)
    {

        ultimo = ObtenerUltimoIn(raiz);
        ultimo->sgte = nuevo;
    }
    else
    {
        raiz = nuevo;
    }
    return;
}
void borrarListaIncidente (NodoIncidente *&lista)
{
    NodoIncidente *anterior;
    NodoIncidente *paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux= lista;
        while (paux && paux->sgte)
        {
            anterior = paux;
            paux= paux->sgte;
        }
        if (paux)
        {
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista =NULL;
        }
    }
    return;
}
void procesarIncidentes (NodoIncidente *i, NodoPoliza *& raiz)
{
    FILE *f;
    NodoPoliza *aux=raiz;
    Incidente x;
    f=fopen("Procesados.BAK","wb");
    while (i)
    {
        while(aux)
        {
            if((i->Info.NumeroPoliza) == (aux->Info.NumeroPoliza))
            {
                aux->Info.CantIncidentes++;
                x=i->Info;
                fwrite(&x,sizeof(Incidente),1,f);
            }
            aux=aux->sgte;
        }
        aux=raiz;
        i=i->sgte;
    }
    fclose(f);
    return;
}
char mostrarmenu()
{
    cout << "1. Cargar una nueva poliza" << endl;
    cout << "2. Desactivar poliza existente" << endl;
    cout << "3. Buscar poliza por DNI" << endl;
    cout << "4. Buscar poliza por numero de poliza" << endl;
    cout << "5. Listar polizas activas" << endl;
    cout << "6. Procesar lotes de incidentes" << endl;
    cout << "7. Cargar nuevo incidente" << endl;
    cout << "8. Mostrar polizas que no tengan la cuota al dia (HTML)" << endl;
    cout << "9. Mostrar polizas que no tengan la cuota al dia (CSV)" << endl;
    cout << "0. Finalizar jornada" << endl;
    cout << "Esc. Salir" << endl;
    char opcion;
    do
    {
        opcion = getch();
    } while ((opcion != '1') && (opcion != '2') && (opcion != '3') && (opcion != '4') && (opcion != '5') && (opcion != '6') && (opcion != '7') && (opcion != '8') &&(opcion != '9') &&(opcion != '0')&&(opcion != 27));
    return opcion;
}

int main()
{

    NodoPoliza *ListaAsegurados = NULL;
    NodoPoliza *x=NULL;
    NodoIncidente *ListaIncidentes=NULL;
    int Numero;
    char opcion,nombreArchivo[50], OpcionBusqueda;
    //Se levantan asegurados automaticamente para poder hacer todas las operaciones en memoria*/
    LevantarAsegurados(ListaAsegurados);
    LevantarIncidentes(ListaIncidentes);

    do
    {
        do
        {
            opcion = mostrarmenu();
        }while((opcion>='0' && opcion<=9) && opcion !=27);
            switch (opcion)
            {
                case '1':
                    CargarNuevaPoliza(ListaAsegurados);
                    break;
                case '2':
                    cout << "Ingrese el numero de poliza a desactivar:" << endl;
                    cin >> Numero;
                    descactivarPoliza(ListaAsegurados, Numero);
                    break;
                case '3':
                    cout << "Indique el DNI a buscar:" << endl;
                    cin >> Numero;
                    buscarDNI(ListaAsegurados, Numero);
                    break;
                case '4':
                    cout << "Indique el numero de poliza a buscar:" << endl;
                    cin >> Numero;
                    x= buscarPolizaPorNumero(ListaAsegurados,Numero);
                    if (x)
                        mostrarPoliza(x->Info);
                case '5':
                    MostrarPolizasActivas(ListaAsegurados);
                    break;
                case '6':
                    procesarIncidentes(ListaIncidentes,ListaAsegurados);
                    borrarListaIncidente(ListaIncidentes);
                    break;
                case '7':
                    CargarNuevoIncidente(ListaIncidentes);
                    break;
                case '8':
                    escribirReporteHTML(ListaAsegurados);
                    cout<<"Reporte escrito."<<endl;
                    break;
                case '9':
                    escribirReporteCSV(ListaAsegurados);
                    cout<<"Reporte escrito."<<endl;
                    break;
                case '0':
                    ProcesarAsegurados(ListaAsegurados);
                    break;
            }
            cout << "Presione cualquier tecla para continuar" << endl;
            getch();
            system("cls");
    } while (opcion != 27);
    borrarListaPoliza(ListaAsegurados);
    borrarListaIncidente(ListaIncidentes);
    return 0;
}
