#include "Graf_ponderat.h"
#define Inf 100000
/// Initializare fara parametrii
Graf_ponderat:: Graf_ponderat(){
    n=0;
}
/// Initializare cu parametrii
Graf_ponderat::Graf_ponderat(int **a, int **b,int m){
        n=m;
        mat=new int*[n];
        mat2=new int*[n];
        for (int i=0;i<n;i++)
            {mat[i]=new int[n];
             mat2[i]=new int[n];}
        for (int i=0;i<n;i++)
            for (int j=0;j<=n;j++){
                mat[i][j]=a[i][j];
                mat2[i][j]=b[i][j];
                }
        }
/// Copiere
Graf_ponderat::Graf_ponderat(Graf_ponderat &x){
        mat=new int*[x.n];
        mat2=new int*[x.n];
        n=x.n;
        for (int i=0;i<n;i++)
            {mat[i]=new int[n];
             mat2[i]=new int[n];}
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++){
                mat[i][j]=x.mat[i][j];
                mat2[i][j]=x.mat2[i][j];
            }
    }
/// Citire
istream & operator >> (istream &os, Graf_ponderat & G){
    cout<<"n= ";
    os>>G.n;
    G.mat=new int*[G.n];
    G.mat2=new int*[G.n];
    for (int i=0;i<G.n;i++){
        G.mat[i]=new int[G.n];
        G.mat2[i]=new int[G.n];
    }
    cout<<"Matrice muchii= \n";
    for(int i=0;i<G.n;i++)
        for(int j=0;j<G.n;j++){
            cout<<i<<" "<<j<<" ";
            os>>G.mat2[i][j];
        }
    cout<<"Matrice ponderi= \n";
    for(int i=0;i<G.n;i++)
        for(int j=0;j<G.n;j++){
            cout<<i<<" "<<j<<" ";
            os>>G.mat[i][j];
        }
    return os;
}
/// Afisare prin toate tipurile de afisare
ostream & operator << (ostream &os, Graf_ponderat & G){
    cout<<"\n Matrice de ponderi= \n";
    for(int i=0;i<G.n;i++){
        for(int j=0;j<G.n;j++)
            os<<G.mat[i][j]<<"\t";
        os<<'\n';
    }
    cout<<"Matrice de muchii= \n";
    for(int i=0;i<G.n;i++){
        for(int j=0;j<G.n;j++)
            os<<G.mat2[i][j]<<"\t";
        os<<'\n';
    }
    cout<<"Lista de vecini= \n";
    for(int i=0;i<G.n;i++){
        cout<<"Vecinii lui "<<i<<" sunt: ";
        for(int j=0;j<G.n;j++)
            if(G.mat2[i][j]!=0)
                os<<j<<"\t";
        cout<<'\n';
        }
    return os;
}
/// Destructor
Graf_ponderat::~Graf_ponderat(){
    for(int i=0;i<n;i++){
        delete[] mat[i];
        delete[] mat2[i];
    }
    delete[] mat;
    delete[] mat2;
    n=0;
}
/// Citire a n obiecte, memorarea si afisarea acestora
void Graf_ponderat:: Citire(int n){
    Graf_ponderat G3[100];
    for(int i=0;i<n;i++)
        cin>>G3[i];
    for(int i=0;i<n;i++)
        cout<<G3[i]<<'\n';
}
/// DFS
void Graf_ponderat:: DFSaux(int curent, int *viz){
    viz[curent]=1;
    for(int i=0;i<n;i++)
        if(mat2[curent][i]&&!viz[i])
            DFSaux(i,viz);
}
void Graf_ponderat:: DFS(int start){
    int *viz;
    viz= new int[n];
    for(int i=0;i<n;i++)
        viz[i]=0;
    cout<<"\n DFS= ";
    DFSaux(start,viz);
    cout<<'\n';
}
/// BFS
void Graf_ponderat:: BFS(int start){
    int *coada,*viz,ic=0,fc=0,curent;
    coada = new int[n];
    viz = new int[n];
    for (int i = 0; i < n; i++)
        viz[i] = 0;
    coada[ic]=start;
    viz[start]=1;
    cout<<"\n BFS= ";
    while(ic<=fc){
        curent=coada[ic];
        cout<<curent<<" ";
        for(int i=0;i<=n;i++)
            if(mat2[curent][i]&&!viz[i]){
                fc++;
                coada[fc]=i;
                viz[i]=1;
            }
        ic++;
    }
}
/// Determinarea matricii ponderilor drumurilor cu ponderi minime
void Graf_ponderat:: PonderiMinime(){
    int i,k,j;
    int **a;
    a=new int*[n];
    for(i=0;i<n;i++)
        a[i]=new int[n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(mat2[i][j]==0)
                a[i][j]=Inf;
            else
                a[i][j]=mat[i][j];
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(i==j)
                    a[i][j]=0;
                else
                    if(a[i][j]>a[i][k]+a[k][j])
                        a[i][j]=a[i][k]+a[k][j];
    cout<<"\n Matrice de drumuri de ponderi minime= \n";
    for (i=0;i<n;i++){
        for (j=0;j<n;j++)
            cout<<a[i][j]<<'\t';
        cout<<'\n';
    }
}
/// Determinarea nodurilor intermediare de pe drumul de pondere minima intre doua noduri
void Graf_ponderat:: NoduriInter(int x, int y){
    int i,k,j;
    per **a;
    a=new per*[n];
    for(i=0;i<n;i++)
        a[i]=new per[n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(mat2[i][j]==0){
                a[i][j].pond=Inf;
                a[i][j].parinte=-1;
            }
            else{
                a[i][j].pond=mat[i][j];
                a[i][j].parinte=i;
            }
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(i==j){
                    a[i][j].pond=0;
                    a[i][j].parinte=-1;
                }
                else
                    if(a[i][j].pond>a[i][k].pond+a[k][j].pond){
                        a[i][j].pond=a[i][k].pond+a[k][j].pond;
                        a[i][j].parinte=k;
                    }
    cout<<"Noduri Intermediare= ";
    int curent=a[y][x].parinte;
    while(curent!=y&&curent!=-1){
        cout<<curent<<" ";
        curent=a[y][curent].parinte;
    cout<<'\n';
    }
}
/// Graf Conex
void Graf_ponderat::Conex(){
    int *viz;
    viz= new int[n];
    for(int i=0;i<n;i++)
        viz[i]=0;
    DFSaux(0 ,viz);
    int OK=1;
    for(int i=0;i<n;i++)
        if(viz[i]==0)
            OK=0;
    if(OK)
        cout<<"\n Conex \n";
    else
        cout<<"\n Neconex \n";
}
/// Supraincarcarea operatorului *
Graf_ponderat Graf_ponderat:: operator *(const Graf_ponderat &G1){
    int i,j;
    int **a,**b;
    a=new int*[n];
    b=new int*[n];
    for (i=0;i<n;i++){
        a[i]=new int[n];
        b[i]=new int[n];
        }
    Graf_ponderat G2(a,b,n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            G2.mat[i][j]=G2.mat2[i][j]=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(mat2[i][j]&&G1.mat2[i][j]){
                G2.mat2[i][j]=1;
                if(mat[i][j]>G1.mat[i][j])
                    G2.mat[i][j]=G1.mat[i][j];
                else
                    G2.mat[i][j]=mat[i][j];
            }
    return G2;
}
