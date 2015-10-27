#include <iostream>
#include <vector>
#include<queue>
#include <math.h>
//#include <algoritm.h>

using namespace std;

//TO DO:
//* make queueing functions
//* make seach function
//* figure out how to que all things

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
    swap(M.problem[i][j], M.problem[i+1][j]);
    M.gn= M.gn =1;
    return M;
}

Matrix DN(Matrix& M, int i, int j){
    swap(M.problem[i][j],M.problem[i-1][j]);
    M.gn = M.gn+1;
    return M;
}

Matrix RT(Matrix& M, int i, int j){
    swap(M.problem[i][j], M.problem[i][j-1]);
    M.gn = M.gn+1;
    return M;
}

Matrix LF(Matrix& M, int i, int j){
    swap(M.problem[i][j], M.problem[i][j+1]);
    M.gn = M.gn+1;
    return M;
}

//function to expand nodes with operators (current node, operators)
//returns queue of matricies (all possible ways to move the blank)
vector< Matrix >  expand(Matrix M/*, Matrix& M1, Matrix& M2, Matrix& M3, Matrix& M4*/){
    vector< Matrix > vec;
    
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


    //make 4 copies of matrix M that we can store in the que
    M1 = M;

    M2 = M;

    M3 = M;

    M4 = M; 

    //find which indicies the blank is at
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

    //for each indicie that the blank is at, swap with the values it can swap with
    if(column == 2 && row == 0){
        vec.push_back(LF(M1,row, column-1));
        vec.push_back(DN(M2,row+1,column));
    }
    else if(column == 2 && row == 1){
        vec.push_back(UP(M1,row-1,column));
        vec.push_back(LF(M2, row, column-1));
        vec.push_back(DN(M3, row+1, column));
    }
    else if(column ==2 && row ==2){
        vec.push_back(UP(M1, row-1, column));
        vec.push_back(LF(M2, row, column -1));
    }
    else if(column == 0 && row == 0){
        vec.push_back(RT(M1,row, column+1));
        vec.push_back(DN(M2,row+1,column));
    }
    else if(column == 0 && row == 1){
        vec.push_back(UP(M1,row-1,column));
        vec.push_back(RT(M2, row, column+1));
        vec.push_back(DN(M3, row+1, column));
    }
    else if(column ==0 && row ==2){
        vec.push_back(UP(M1, row-1, column));
        vec.push_back(RT(M2, row, column+1));
    }
    else if(column == 1 && row == 0){
        vec.push_back(LF(M1,row, column-1));
        vec.push_back(DN(M2,row+1,column));
        vec.push_back(RT(M3, row, column+1));
    }
    else if(column == 1 && row == 1){
        vec.push_back(UP(M1,row-1,column));
        vec.push_back(LF(M2, row, column-1));
        vec.push_back(DN(M3, row+1, column));
        vec.push_back(RT(M4, row, column+1));
    }
    else if(column ==1 && row ==2){
        vec.push_back(UP(M1, row-1, column));
        vec.push_back(LF(M2, row, column -1));
        vec.push_back(RT(M3, row, column + 1));
    }

    //return the vector queue
    return vec;
} 

//Uniform Cost Search function (nodes(queue), expand)
//returns a node in order of g(n)
priority_queue<Matrix, vector<Matrix>, Compare_Values> UC(priority_queue <Matrix, vector<Matrix>, Compare_Values>  &pq, vector<Matrix> expand){
    for(int i = 0; i < expand.size(); i++)
        pq.push(expand[i]);

    return pq;
}


//A* Mattahatan Search Function
//returns a queue in order of f(n) = g(n) + f(n)

//A* Misplaced Tile function
//returns a queue in order of f(n) = g(n) + f(n)

//general search function to use with search algorithms
Matrix generalSearch(Matrix M, priority_queue<Matrix, vector<Matrix>, Compare_Values> queueing(priority_queue <Matrix, vector<Matrix>, Compare_Values>),
                         vector<Matrix> expand( Matrix ));

//function to check if the matrix matches the goal state
bool checkIfGoal(vector < vector<int> >  M);

int main(){

    Matrix M;
    //make goal matrix to visualize
    M.goal.push_back(std::vector<int>(3, 1));
    M.goal.push_back(std::vector<int>(3, 2));
    M.goal.push_back(std::vector<int>(3, 3));

    //These are the copy matrices used in expand function
    /*Matrix M1; 
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
    */

    //create M's goal state
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
    M.problem[1][1]=0;
    M.problem[1][2]=6;
    M.problem[2][0]=7;
    M.problem[2][1]=5;
    M.problem[2][2]=8;

    cout << "Outputting regular matrix: " << endl;
    int c,d;
    for(d = 0; d < 3; ++d)
    {
        for(c = 0; c < 3; ++c)
            cout << M.problem[d][c] << "\t" ;
        cout<<endl;
    }

    //queue of all the possible expansions of M
    vector<Matrix> vec = expand(M/*, M1, M2, M3, M4*/);
    
    //cout << "Outputting gn values: " << M1.gn << ", " << M2.gn << ", " << M3.gn << ", " << M4.gn << endl;

    cout << "Outputting the queue: " << endl;
    int i,e,f;
    for(i = 0; i < vec.size(); i++)
    {
        for(f = 0; f < 3; ++f)
        {
            for(e = 0; e < 3; ++e)
                cout << vec.at(i).problem[f][e] << "\t" ;
            cout<<endl;
        }
        cout << endl;
    }
    //checking if goal matches matrix with function
    cout << "8 Tile matches goal state? " << checkIfGoal(M.problem) << endl; 
    
    Matrix UCS;
    
    UCS.problem.push_back(std::vector<int>(3, 1));
    UCS.problem.push_back(std::vector<int>(3, 2));
    UCS.problem.push_back(std::vector<int>(3, 3));
    
    UCS.goal.push_back(std::vector<int>(3, 1));
    UCS.goal.push_back(std::vector<int>(3, 2));
    UCS.goal.push_back(std::vector<int>(3, 3));
    
    priority_queue<Matrix, vector<Matrix>, Compare_Values> pq;

    UCS = generalSearch(M, UC, expand);
    //search.problem  = generalSearch(M).problem;
    //search.goal = M.goal;
    //search.fn = generalSearch(M).fn;


    return 0;
}

bool checkIfGoal(vector <vector<int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}

Matrix generalSearch(Matrix M, priority_queue<Matrix, vector<Matrix>, Compare_Values> queueing(priority_queue <Matrix, vector<Matrix>, Compare_Values>),
                         vector<Matrix> expand( Matrix )){
    priority_queue <Matrix, vector<Matrix>, Compare_Values> nodes;
    nodes.push(M);
    do{    
        if(nodes.empty()){
            cout <<  "Failure. There is no solution to this problem." << endl;
            break;
        }
        Matrix node;
        node.problem.push_back(std::vector<int>(3, 1));
        node.problem.push_back(std::vector<int>(3, 2));
        node.problem.push_back(std::vector<int>(3, 3));
        
        node.goal.push_back(std::vector<int>(3, 1));
        node.goal.push_back(std::vector<int>(3, 2));
        node.goal.push_back(std::vector<int>(3, 3));

        node = nodes.top();
         
        cout << "Nodes is now: " << endl;
        int e,f;
        for(f = 0; f < 3; ++f){
            for(e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout<<endl;
        }
        if(checkIfGoal(node.problem))
            return nodes.top();
        nodes = queueing(nodes, expand(node));
    }while(!nodes.empty());

}


