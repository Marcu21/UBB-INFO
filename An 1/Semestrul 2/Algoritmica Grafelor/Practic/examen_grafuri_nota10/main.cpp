#include <iostream>
#include <fstream>
using namespace std;

#define MAX 100
#define INF 1000000

void BellmanFord(int distanta[MAX][MAX], int v, int sursa)
{
    for(int i=1;i<v;i++)
        for(int j=1;j<=v;j++)
            for(int k=1;k<=v;k++) {
                if(distanta[j][k]!=INF && distanta[sursa][j]+distanta[j][k]<distanta[sursa][k])
                {
                    distanta[sursa][k] = distanta[sursa][j] + distanta[j][k];
                }
            }
    for(int j = 1; j <= v; j++)
        for(int k = 1; k <= v; k++) {
            if (distanta[j][k] != INF && distanta[sursa][j] + distanta[j][k] < distanta[sursa][k]) {
                cout << "Graful contine un ciclu negativ" << endl;
                return;
            }
        }
}

int main()
{
    int distanta[MAX][MAX];
    int v, start = 1;
    ifstream f("C:\\Users\\emanu\\CLionProjects\\examen_grafuri_nota10\\Inputfile.txt");
    f>>v;
    for(int i=1;i<=v;i++) {
        for(int j=1;j<=v;j++)
            if(i==j) distanta[i][j]=0;
            else distanta[i][j]=INF;
    }
    int sursa, destinatie, lungime;
    while(f>>sursa>>destinatie>>lungime)
    {
        distanta[sursa][destinatie] = lungime;
    }
    BellmanFord(distanta, v, start);

    for(int i=1;i<=v;i++)
        if(i!=start)
        {
            if(distanta[start][i]==INF)
                cout<<"Nu exista drum de la "<<start<<" la "<<i<<endl;
            else
                cout<<"Distanta minima de la "<<start<<" la "<<i<<" = "<<distanta[start][i]<<endl;
        }
}