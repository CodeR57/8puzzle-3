#include <iostream>
#include <vector>
#include<queue>
#include <math.h>
//#include <algoritm.h>

using namespace std;

//TO DO:
//* make queueing function
//* make seach function
//* figure out how to que all things
//* make function to expand nodes with all different operators
//* make functions for operators to move the blank tile


struct Matrix{
    vector < vector <int> > problem;
    vector < vector <int> > goal;
    int fn;
    int gn;
    int hn;
};

class Compare_Values    {
    public: 
        bool operator()(Matrix& M1, Matrix& M2){
            if(M1.fn != 0){
                if(M1.fn < M2.fn) return true;
            }
            else{
                if(M1.gn < M2.gn) return true;
            }
            return false;
        }
};

//OPERATORS: i and j are row and column values you want to move blank to
Matrix UP(Matrix& M, int i, int j){
    int temp = M.problem[i][j];
    M.problem[i][j] = 0;//M.problem[i+1][j];
    M.problem[i+1][j] = temp;
    return M;
}

Matrix DN(Matrix& M, int i, int j){
    int temp = M.problem[i][j];
    M.problem[i][j] = 0;//M.problem[i-1][j];
    M.problem[i-1][j] = temp;
    return M;
}

Matrix RT(Matrix& M, int i, int j){
    int temp = M.problem[i][j];
    M.problem[i][j] = 0;//M.problem[i][j-1];
    M.problem[i][j-1] = temp;
    return M;
}

Matrix LF(Matrix& M, int i, int j){
    int temp = M.problem[i][j];
    M.problem[i][j] = 0;//M.problem[i][j+1];
    M.problem[i][j+1] = temp;
    return M;
}

//function to expand nodes with operators (current node, operators)
//returns queue of matricies (all possible ways to move the blank)
vector< Matrix >  expand(Matrix& M, Matrix& M1, Matrix& M2, Matrix& M3, Matrix& M4){
    vector< Matrix > vec;
        
    //Matrix M1; 
    //M1.problem.push_back(std::vector<int>(3, 1));
    //M1.problem.push_back(std::vector<int>(3, 2));
    //M1.problem.push_back(std::vector<int>(3, 3));

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            M1.problem[i][j]= M.problem[i][j];
            cout << M1.problem[i][j] << "\t"; 
        }
        cout << endl;
    }
    cout << endl;
    
    //Matrix M2;
     
    //M2.problem.push_back(std::vector<int>(3, 1));
    //M2.problem.push_back(std::vector<int>(3, 2));
    //M2.problem.push_back(std::vector<int>(3, 3));

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            M2.problem[i][j]= M.problem[i][j];
        }
    }
    
    //Matrix M3; 
    //M3.problem.push_back(std::vector<int>(3, 1));
    //M3.problem.push_back(std::vector<int>(3, 2));
    //M3.problem.push_back(std::vector<int>(3, 3));

    //Matrix M3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            M3.problem[i][j]= M.problem[i][j];
        }
    }
   
    //Matrix M4; 
    //M4.problem.push_back(std::vector<int>(3, 1));
    //M4.problem.push_back(std::vector<int>(3, 2));
    //M4.problem.push_back(std::vector<int>(3, 3));

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            M4.problem[i][j]= M.problem[i][j];
        }
    }

    int row,column;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(M.problem[i][j] == 0){
                row = i;
                column = j;
                break;
            }
        }
    }
    
    cout << "Blank is at row: " << row << " and column: " << column << endl;

    if(column == 2 && row == 0){
        vec.push_back(LF(M1,row, column-1));
        vec.push_back(DN(M2,row+1,column));
    }
    else if(column == 2 && row == 1){
        vec.push_back(UP(M,row-1,column));
        vec.push_back(LF(M2, row, column-1));
        vec.push_back(DN(M3, row+1, column));
    }
    else if(column ==2 && row ==2){
        vec.push_back(UP(M, row-1, column));
        vec.push_back(LF(M2, row, column -1));
    }
    else if(column == 0 && row == 0){
        vec.push_back(RT(M,row, column+1));
        vec.push_back(DN(M2,row+1,column));
    }
    else if(column == 0 && row == 1){
        vec.push_back(UP(M,row-1,column));
        vec.push_back(RT(M2, row, column+1));
        vec.push_back(DN(M3, row+1, column));
    }
    else if(column ==0 && row ==2){
        vec.push_back(UP(M, row-1, column));
        vec.push_back(RT(M2, row, column+1));
    }
    else if(column == 1 && row == 0){
        vec.push_back(LF(M,row, column-1));
        vec.push_back(DN(M2,row+1,column));
        vec.push_back(RT(M3, row, column+1));
    }
    else if(column == 1 && row == 1){
        vec.push_back(UP(M,row-1,column));
        vec.push_back(LF(M2, row, column-1));
        vec.push_back(DN(M3, row+1, column));
        vec.push_back(RT(M4, row, column+1));
    }
    else if(column ==1 && row ==2){
        vec.push_back(UP(M, row-1, column));
        vec.push_back(LF(M2, row, column -1));
        vec.push_back(RT(M3, row, column + 1));
    }

    return vec;
} 

//Uniform Cost Search function (nodes(queue), expand)
//returns a queue in order of g(n)
//queue<Matrix> UC(

//A* Mattahatan Search Function
//returns a queue in order of f(n) = g(n) + f(n)

//A* Misplaced Tile function
//returns a queue in order of f(n) = g(n) + f(n)

//general search function to use with search algorithms
void/*Matrix*/ generalSearch( Matrix m /*queueing function*/ );

//function to check if the matrix matches the goal state
bool checkIfGoal(vector < vector<int> >  M);

int main(){

    Matrix M;
    //make goal matrix to visualize
    M.goal.push_back(std::vector<int>(3, 1));
    M.goal.push_back(std::vector<int>(3, 2));
    M.goal.push_back(std::vector<int>(3, 3));

    Matrix M1; 
    M1.problem.push_back(std::vector<int>(3, 1));
    M1.problem.push_back(std::vector<int>(3, 2));
    M1.problem.push_back(std::vector<int>(3, 3));
    
    Matrix M2;
    M2.problem.push_back(std::vector<int>(3, 1));
    M2.problem.push_back(std::vector<int>(3, 2));
    M2.problem.push_back(std::vector<int>(3, 3));
    
    Matrix M3;
    M3.problem.push_back(std::vector<int>(3, 1));
    M3.problem.push_back(std::vector<int>(3, 2));
    M3.problem.push_back(std::vector<int>(3, 3));

    Matrix M4;
    M4.problem.push_back(std::vector<int>(3, 1));
    M4.problem.push_back(std::vector<int>(3, 2));
    M4.problem.push_back(std::vector<int>(3, 3));

    M.goal[0][0]=1;
    M.goal[0][1]=2;
    M.goal[0][2]=3;
    M.goal[1][0]=4;
    M.goal[1][1]=5;
    M.goal[1][2]=6;
    M.goal[2][0]=7;
    M.goal[2][1]=8;
    M.goal[2][2]=0;

    cout << "Outputting goal matrix: " << endl;
    int a,b;
    for(b = 0; b < 3; ++b)
    {
        for(a = 0; a < 3; ++a)
            cout << M.goal[b][a] << "\t" ;
        cout<<endl;
    }

    //make matrix for 8puzzle
    M.problem.push_back(std::vector<int>(3, 1));
    M.problem.push_back(std::vector<int>(3, 2));
    M.problem.push_back(std::vector<int>(3, 3));

    M.problem[0][0]=1;
    M.problem[0][1]=3;
    M.problem[0][2]=2;
    M.problem[1][0]=4;
    M.problem[1][1]=5;
    M.problem[1][2]=6;
    M.problem[2][0]=7;
    M.problem[2][1]=0;
    M.problem[2][2]=8;
    
    cout << "Outputting regular matrix: " << endl;
    int c,d;
    for(d = 0; d < 3; ++d)
    {
        for(c = 0; c < 3; ++c)
            cout << M.problem[d][c] << "\t" ;
        cout<<endl;
    }

    vector<Matrix> vec = expand(M, M1, M2, M3, M4);


    cout << "Outputting the que: " << endl;
    int i,e,f;
    for(i = 0; i < vec.size(); i++)
    {
        for(f = 0; f < 3; ++f)
        {
            for(e = 0; e < 3; ++e)
                cout << M.problem[f][e] << "\t" ;
            cout<<endl;
        }
        cout << endl;
    }
    //checking if goal matches matrix with function
    cout << "8 Tile matches goal state? " << checkIfGoal(M.problem) << endl; 

    //generalSearch(M);

    /*cout << "Outputting search problem matrix: " << endl;
      int e,f;
      for(f = 0; f < 3; ++f)
      {
      for(e = 0; e < 3; ++e)
      cout << M1.problem[f][e] << "\t" ;
      cout<<endl;
      }*/

    return 0;
}

bool checkIfGoal(vector <vector<int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}
//void Matrix generalSearch( Matrix& m /*queueing function*/ ){
/*    priority_queue <Matrix, vector<Matrix>, Compare_Values> nodes;

      nodes.push(m);
      if(nodes.empty())
      return "failure";
      do{
      cout << "Nodes is now: " << endl;
      int e,f;
      for(f = 0; f < 3; ++f)
      {
      for(e = 0; e < 3; ++e)
      cout << nodes.top().problem[f][e] << "\t" ;
      cout<<endl;
      }

      if(nodes.empty()) return failure;



//return nodes.top();
}while(!nodes.empty);
}*/


