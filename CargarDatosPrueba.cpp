#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <cstring>

#define RutaAsegurados "Asegurados.BAK"
#define RutaLote1 "Lote1"



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


void CargarPruebaIncidentes()
{
    FILE *f;
    f=fopen(RutaLote1,"wb");
    Incidente x;
    x.Altura=345;
    x.Codigo=1221;
    x.DniAsegurado=44713236;
    x.DniOtroConductor=33444666;
    x.Fecha=20202410;
    x.NumeroPoliza=1234;
    strcpy(x.Calle, "Gral. Fructuoso Rivera");
    fwrite(&x,sizeof(Incidente),1,f);

    x.Altura=1945;
    x.Codigo=1222;
    x.DniAsegurado=44713236;
    x.DniOtroConductor=45678901;
    x.Fecha=20202411;
    x.NumeroPoliza=1234;
    strcpy(x.Calle, "Medrano");
    fwrite(&x,sizeof(Incidente),1,f);

    x.Altura=6455;
    x.Codigo=9704;
    x.DniAsegurado=41893253;
    x.DniOtroConductor=11666111;
    x.Fecha=20202411;
    x.NumeroPoliza=3333;
    strcpy(x.Calle, "Gorriti");
    fwrite(&x,sizeof(Incidente),1,f);

    fclose(f);
    return;
}
void CargarPruebaPoliza()
{
    FILE *f;
    Poliza poliza;
    f=fopen(RutaAsegurados,"wb");
    strcpy(poliza.Nombre, "Agustin");
    strcpy(poliza.Apellido, "Trossero");
    strcpy(poliza.Patente, "RIB157");
    poliza.Dni = 44713236;
    poliza.NumeroPoliza = 1234;
    poliza.CantIncidentes = 2;
    poliza.Activa = true;
    poliza.CuotaAlDia = true;

    fwrite(&poliza,sizeof(Poliza),1,f);

    strcpy(poliza.Nombre, "Juan Jose");
    strcpy(poliza.Apellido, "De los Palotes");
    strcpy(poliza.Patente, "AE144II");
    poliza.Dni = 43456231;
    poliza.NumeroPoliza = 2233;
    poliza.CantIncidentes = 4;
    poliza.Activa = true;
    poliza.CuotaAlDia = false;

    fwrite(&poliza,sizeof(Poliza),1,f);

    strcpy(poliza.Nombre, "Aaron");
    strcpy(poliza.Apellido, "Gonzalez");
    strcpy(poliza.Patente, "AB352EF");
    poliza.Dni = 41893253;
    poliza.NumeroPoliza = 3333;
    poliza.CantIncidentes = 6;
    poliza.Activa = true;
    poliza.CuotaAlDia = true;

    fwrite(&poliza,sizeof(Poliza),1,f);

    strcpy(poliza.Nombre, "NoTengo");
    strcpy(poliza.Apellido, "QueAparecer");
    strcpy(poliza.Patente, "WA444RN");
    poliza.Dni = 11666111;
    poliza.NumeroPoliza = 666;
    poliza.CantIncidentes = 6;
    poliza.Activa = false;
    poliza.CuotaAlDia = false;

    fwrite(&poliza,sizeof(Poliza),1,f);

    fclose(f);
    return;
}

using namespace std;

int main()
{
    CargarPruebaIncidentes();
    CargarPruebaPoliza();
    return 0;
}
