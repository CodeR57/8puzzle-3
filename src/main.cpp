#include <iostream>
#include <vector>
#include<queue>
#include <math.h>
#include <algorithm>

using namespace std;

//TO DO:
//* make queueing functions
//* make seach function
//* figure out how to que all things

struct Matrix{
    vector < vector <int> > problem;
    vector < vector <int> > goal;
    int gn;
    int hn;
};

class Compare_Values    {
    public: 
        bool operator()(Matrix& M1, Matrix& M2){
                return(M1.hn + M1.gn > M2.hn + M2.gn);
        }
};

//A* Mattahatan Search Function
//calculates the hn value
void mat(Matrix& M){
    M.hn = 0;
    for(int i = 0; i < 3; i++){
        for(int j=0; j<3; j++){
            int val = M.problem[i][j];
            if(val != 0){
                int goal_row = (val - 1) / 3;
                int goal_column = (val - 1) % 3;
                M.hn = M.hn + abs(i - goal_row) + abs(j - goal_column);
            }
        }
    }
}


//A* Misplaced Tile function
//calculates the misplaced tile hn value
void misplaced_tile(Matrix& M){
    M.hn = 0;
    if(M.problem[0][0] != 1) M.hn++;
    if(M.problem[0][1] != 2) M.hn++;
    if(M.problem[0][2] != 3) M.hn++;
    if(M.problem[1][0] != 4) M.hn++;
    if(M.problem[1][1] != 5) M.hn++;
    if(M.problem[1][2] != 6) M.hn++;
    if(M.problem[2][0] != 7) M.hn++;
    if(M.problem[2][1] != 8) M.hn++;
    if(M.problem[2][2] != 0) M.hn++;
}

//OPERATORS: i and j are row and column values you want to move blank to
Matrix UP(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i+1][j]);
    M.gn= M.gn + 1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    return M;
}

Matrix DN(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j],M.problem[i-1][j]);
    M.gn = M.gn+1;
    if(choice == 1)
       M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    
    return M;
}

Matrix RT(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i][j-1]);
    M.gn = M.gn+1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    
    return M;
}

Matrix LF(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i][j+1]);
    M.gn = M.gn+1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    
    return M;
}

//function to expand nodes with operators (current node, operators)
//returns queue of matricies (all possible ways to move the blank)
void expand(Matrix M, priority_queue<Matrix, vector<Matrix>, Compare_Values> &nodes, int choice){
    
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
        nodes.push(LF(M1,row, column-1, choice));
        nodes.push(DN(M2,row+1,column, choice));
    }
    else if(column == 2 && row == 1){
        nodes.push(UP(M1,row-1,column, choice));
        nodes.push(LF(M2, row, column-1, choice));
        nodes.push(DN(M3, row+1, column, choice));
    }
    else if(column ==2 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(LF(M2, row, column -1,choice));
    }
    else if(column == 0 && row == 0){
        nodes.push(RT(M1,row, column+1,choice));
        nodes.push(DN(M2,row+1,column, choice));
    }
    else if(column == 0 && row == 1){
        nodes.push(UP(M1,row-1,column,choice));
        nodes.push(RT(M2, row, column+1, choice));
        nodes.push(DN(M3, row+1, column, choice));
    }
    else if(column ==0 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(RT(M2, row, column+1, choice));
    }
    else if(column == 1 && row == 0){
        nodes.push(LF(M1,row, column-1, choice));
        nodes.push(DN(M2,row+1,column, choice));
        nodes.push(RT(M3, row, column+1, choice));
    }
    else if(column == 1 && row == 1){
        nodes.push(UP(M1,row-1,column, choice));
        nodes.push(LF(M2, row, column-1, choice));
        nodes.push(DN(M3, row+1, column, choice));
        nodes.push(RT(M4, row, column+1, choice));
    }
    else if(column ==1 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(LF(M2, row, column -1, choice));
        nodes.push(RT(M3, row, column + 1, choice));
    }

    //return the vector queue
} 

//Uniform Cost Search function (nodes(queue), expand)
//returns a node in order of g(n)
priority_queue<Matrix, vector<Matrix>, Compare_Values> UC(priority_queue <Matrix, vector<Matrix>, Compare_Values>  &pq, vector<Matrix> expand){
    for(int i = 0; i < expand.size(); i++)
        pq.push(expand[i]);

    return pq;
}

//function to check if the matrix matches the goal state
bool checkIfGoal(vector < vector<int> >  M);

//general search function to use with search algorithms
void generalSearch(Matrix M, int choice){
    if(choice == 1)
        M.hn = 0;
    else if(choice == 2)
        misplaced_tile(M);
    else if(choice == 3)
        mat(M);
    priority_queue <Matrix, vector<Matrix>, Compare_Values> nodes;
    nodes.push(M);
    
    cout << "Expanding state:" << endl;
        int e,f;
        for(f = 0; f < 3; ++f){
            for(e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout<<endl;
        }
   int max_queue=0;
   int notEmpty = 0; 
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
        nodes.pop(); 
        /*cout << "Here is what we are expanding:" << endl;
        int e,f;
        for(f = 0; f < 3; ++f){
            for(e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout<<endl;
        }
        */
        if(checkIfGoal(node.problem)){
            cout << "Goal node reached!" << endl;
            for(int f = 0; f < 3; ++f)
            {
                for(int e = 0; e < 3; ++e)
                    cout << node.problem[f][e] << "\t" ;
                cout<<endl;
            }
            cout << endl;
            cout << "To solve this problem, the algorithm expanded a total of _____ nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time was " << max_queue << "." << endl;
            cout << "Depth of goal node was " << node.gn << "." << endl;
            notEmpty = 1;
            return;
        }
        
        expand(node,nodes,choice);
        cout << "Size of queue is " << nodes.size() << "." << endl;
        int curr_queue = nodes.size();
        max_queue = max(max_queue, curr_queue);

        cout << "The best state to expand with a g(n)=" << nodes.top().gn << " and h(n)=" << nodes.top().hn << "is..." << endl;
        for(int f = 0; f < 3; ++f){
            for(int e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout<<endl;
        }
        cout << endl;

    }while(!nodes.empty() && !notEmpty);
    return;

}

int main(){

    Matrix M;
    //make goal matrix to visualize
    M.goal.push_back(std::vector<int>(3, 1));
    M.goal.push_back(std::vector<int>(3, 2));
    M.goal.push_back(std::vector<int>(3, 3));

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
    M.problem[0][1]=2;
    M.problem[0][2]=3;
    M.problem[1][0]=4;
    M.problem[1][1]=8;
    M.problem[1][2]=0;
    M.problem[2][0]=7;
    M.problem[2][1]=6;
    M.problem[2][2]=5;

    cout << "Outputting regular matrix: " << endl;
    int c,d;
    for(d = 0; d < 3; ++d)
    {
        for(c = 0; c < 3; ++c)
            cout << M.problem[d][c] << "\t" ;
        cout<<endl;
    }

    //queue of all the possible expansions of M
    //vector<Matrix> vec = expand(M/*, M1, M2, M3, M4*/);
    
    //cout << "Outputting gn values: " << M1.gn << ", " << M2.gn << ", " << M3.gn << ", " << M4.gn << endl;

    /*cout << "Outputting the queue: " << endl;
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
    */
    //checking if goal matches matrix with function
    //cout << "8 Tile matches goal state? " << checkIfGoal(M.problem) << endl; 
    
    //Matrix UCS;
    
    //UCS.problem.push_back(std::vector<int>(3, 1));
    //UCS.problem.push_back(std::vector<int>(3, 2));
    //UCS.problem.push_back(std::vector<int>(3, 3));
    
    //UCS.goal.push_back(std::vector<int>(3, 1));
    //UCS.goal.push_back(std::vector<int>(3, 2));
    //UCS.goal.push_back(std::vector<int>(3, 3));
    
    //priority_queue<Matrix, vector<Matrix>, Compare_Values> pq;
    

    //UCS = generalSearch(M, UC, expand);
    //search.problem  = generalSearch(M).problem;
    //search.goal = M.goal;
    //search.fn = generalSearch(M).fn;
    
    int choice = 0;
    cout << "Enter your choice of algorithm:" << endl;
    cout << "1, Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile Heuristic" << endl;
    cout << "3. A* eith the Manhattan Distance Heuristic" << endl;
    cin >> choice;
    cout << endl;
    
    generalSearch(M, choice);
    
    return 0;
}

bool checkIfGoal(vector <vector<int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}

