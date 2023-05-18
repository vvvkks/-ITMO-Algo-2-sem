#include <fstream>
#include <vector>
using namespace std;
 
vector<vector<int>> g;
vector<bool> used;
vector<int> result,cycle;
vector<string> color;
 
 
bool check(int v, int start, int finish) // проверка на циклы
{
    color[v] = "grey"; // помечаем вершину серой
    int temp;
    for (auto i: g[v]) // проходимся по всем связным вершинам
    {
        temp = i;
        if (color[temp] == "white") // если пришли в белую верщину
        {
            cycle[temp] = v;
            if (check(temp, start, finish)) // проверяем текущию вершину
                return true;
        }
        else if (color[temp] == "grey") // если пришли в серую вершину
        {
            start = temp;
            finish = v;
            return true;
        }
    }
    color[v] = "black"; // после прохода по вершине меняем цвет на чёрный
    return false;
}
void dfs(int v)
{
    used[v] = true;
    for (int i: g[v])
        if (!used[i])
            dfs(i);
    result.push_back(v);
}
 
 
int main()
{
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");
    int n, m, v1, v2, start = -1, finish = -1;
    fin >> n >> m;
    g.resize(n);
    used.assign(n, false);
    color.assign(n, "white");
    cycle.assign(n, -1);
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++)
    {
        if (check(i, start, finish))
        {
            fout << -1;
            return 0;
        }
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);
    vector<int> ansReverse(n);
    for (int i = 0; i < n; i++)
        ansReverse[i] = result[n - 1 - i];
    for (auto i : ansReverse)
        fout << i + 1 << " ";
    return 0;
}
