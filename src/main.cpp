#include <iostream>
#include <vector>
#include <math.h>
//#include <algoritm.h>

using namespace std;

//TO DO:
//* make queueing function
//* make seach function
//* figure out how to que all things

//general search function to use with search algorithms
vector < vector <int> > generalSearch( vector < vector<int> > problem /*queueing function*/ );

//function to check if the matrix matches the goal state
bool checkIfGoal(vector <vector <int> > M);

int main(){
    vector < vector <int> > matrix;
    vector < vector <int> > goal;
    
    //make goal matrix to visualize
    goal.push_back(std::vector<int>(3, 1));
    goal.push_back(std::vector<int>(3, 2));
    goal.push_back(std::vector<int>(3, 3));
    
    goal[0][0]=1;
    goal[0][1]=2;
    goal[0][2]=3;
    goal[1][0]=4;
    goal[1][1]=5;
    goal[1][2]=6;
    goal[2][0]=7;
    goal[2][1]=8;
    goal[2][2]=0;

    cout << "Outputting goal matrix: " << endl;
    int a,b;
    for(b = 0; b < 3; ++b)
    {
        for(a = 0; a < 3; ++a)
            cout << goal[b][a] << "\t" ;
        cout<<endl;
    }
    
    //make matrix for 8puzzle
    matrix.push_back(std::vector<int>(3, 1));
    matrix.push_back(std::vector<int>(3, 2));
    matrix.push_back(std::vector<int>(3, 3));

    matrix[0][0]=1;
    matrix[0][1]=2;
    matrix[0][2]=3;
    matrix[1][0]=4;
    matrix[1][1]=5;
    matrix[1][2]=6;
    matrix[2][0]=7;
    matrix[2][1]=8;
    matrix[2][2]=0;
    
    cout << "Outputting regular matrix: " << endl;
    int c,d;
    for(d = 0; d < 3; ++d)
    {
        for(c = 0; c < 3; ++c)
            cout << matrix[d][c] << "\t" ;
        cout<<endl;
    }
    
    //checking if goal matches matrix with function
    cout << "8 Tile matches goal state? " << checkIfGoal(matrix) << endl; 

    return 0;
}

bool checkIfGoal(vector <vector <int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}
    
