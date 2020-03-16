#include<iostream>
#ifndef GRAF_PONDERAT_H
#define GRAF_PONDERAT_H
using namespace std;
class Graf_ponderat{
    int **mat,**mat2,n; /// mat = matrice de ponderi, mat2 = matrice de adiacenta, n = nr de muchii
    struct per{               /// strcutura pereche folosita pt determinarea nodurilor intermediare ale drumurilor de pondere minima
        int pond,parinte;
    };
public:
    Graf_ponderat();
    Graf_ponderat(int **a, int **b,int m);
    Graf_ponderat(Graf_ponderat &x);
    ~Graf_ponderat();
    friend istream & operator >> (istream &os, Graf_ponderat & G);
    friend ostream & operator << (ostream &os, Graf_ponderat & G);
    void Citire(int n);
    void DFSaux(int curent, int viz[]);
    void DFS(int start);
    void BFS(int start);
    void PonderiMinime();
    void NoduriInter(int x, int y);
    void Conex();
    Graf_ponderat operator *(const Graf_ponderat &G);
};
#endif // GRAF_PONDERAT_H
