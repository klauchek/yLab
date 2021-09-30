
#include <fstream>

using namespace std;

int main()
{
    ofstream fout("test8.txt");
    
    for (int i = 0; i < 1000; i++)
            fout << 1 << ' ';
    fout.close();
    return 0;
}