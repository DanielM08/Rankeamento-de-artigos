#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

#define SIZE 100000

void propagacaoInfluencias(vector<pair<int,double>> G[], double pesosV[], double somatorioA[], int s, int fR)
{
    //Vetor de visitados
    bool vis[SIZE];   
    for(int i = 0; i < SIZE; i++)
    {
        vis[i] = false;
    }

    //Cria fila e adiciona raiz
    std::queue<int> F;
    F.push(s);

    vis[s] = true;

    while(!F.empty())
    {
        auto v = F.front();
        F.pop();
        
        double valorArestas = 0;
    
        if(G[v].size() > 0)
            valorArestas = ((somatorioA[v] * pesosV[v]) * (1 - fR))/G[v].size(); 

        pesosV[v] = (somatorioA[v] + pesosV[v]) * fR;
        
        for(size_t i = 0; i < G[v].size(); i++)
        {
           G[v][i].second = valorArestas;

           int b = G[v][i].first;

           if(!vis[b])
           {
                vis[b] = true;
                F.push(b);
           } 
           
           somatorioA[b] += valorArestas;       
        }   
    } 
}

int main()
{
    int N, M; //Número de vértices e arestas
    
    cout << "Digite o valor de N: ";
    cin >> N;
    
    cout << "Digite o valor de M: ";
    cin >> M;
    
    //Par 1: Peso do vértice e soma dos pesos das arestas que entram no vértice
    //Par 2: Vértice ao qual se liga e peso da aresta entre eles
    vector<pair<int,double>> v[SIZE]; 

    double pesosV[SIZE];
    double somatorioA[SIZE];
     
    for(int i = 0; i < N; i++)
    {
        cout << "Digite o " << i << " valor : ";
        cin >> pesosV[i];

        somatorioA[i] = 0;
    }
    
    cout << "Digite as conexoes: " << endl;    

    for(int i = 0; i < M; i++)
    {
        int a, b;  
        
        cin >> a >> b;
        
        v[a].push_back(make_pair(b,0));
    }

    propagacaoInfluencias(v, pesosV, somatorioA, 0, 0.6); 
}
