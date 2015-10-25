#include <iostream>
#include <vector>
#include <math.h>
//#include <algoritm.h>

using namespace std;

int main(){
    vector < vector <int> > matrix;
    
    matrix.push_back(std::vector<int>(3, 1));
    matrix.push_back(std::vector<int>(3, 2));
    matrix.push_back(std::vector<int>(3, 3));

    matrix[0][0]=1;
    matrix[0][1]=1;
    matrix[0][2]=1;
    matrix[1][0]=1;
    matrix[1][1]=1;
    matrix[1][2]=1;
    matrix[2][0]=1;
    matrix[2][1]=1;
    matrix[2][2]=1;

    int c,d;
    for(d = 0; d < 3; ++d)
    {
        for(c = 0; c < 3; ++c)
            cout << matrix[d][c] << "\t" ;
        cout<<endl;
    }
    return 0;
}
