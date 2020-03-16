#include <iostream>
#include <fstream>
#include "Graf_ponderat.h"
using namespace std;
ifstream f("f.in");
int i,j,n;
int main()
{int **a,**b;
n=5;
a=new int*[n];
b=new int*[n];
for (i=0;i<n;i++){
    a[i]=new int[n];
    b[i]=new int[n];
    }
for (i=0;i<n;i++)
    for (j=0;j<n;j++)
        f>>a[i][j];
for (i=0;i<n;i++)
    for (j=0;j<n;j++)
        f>>b[i][j]; /// Citirea din fisierul f.in a matricilor de ponderi si de adiacenta a unui graf neorientat
Graf_ponderat G(a,b,n);
cout<<G; /// Afisarea Grafului
G.PonderiMinime(); /// Afisarea matricii ponderilor drumurilor cu ponderi minime
G.NoduriInter(1,3); /// Afisarea nodurilor intermediare de pe drumul de pondere minima intre doua noduri
G.Conex(); /// Afisarea Conexitatii Grafului
for (i=0;i<n;i++)
    for (j=0;j<n;j++)
        f>>a[i][j];
for (i=0;i<n;i++)
    for (j=0;j<n;j++)
        f>>b[i][j];
Graf_ponderat G1(a,b,n); /// Citirea din fisierul f.in si initializarea altui graf
Graf_ponderat G2;
G2=G*G1; /// Efectuarea operatiei definita in clasa
cout<<G2;
}
