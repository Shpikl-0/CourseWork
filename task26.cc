#include <iostream>
using namespace std;

const int COLS = 9;
const int ROWS = 9;

const string COLOR = "\033[30;47m";
const string RESET = "\033[0m";

void finder(int matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int value = matrix[i][j];

            for(int k = 0; k < COLS; k++)
            {
                if(k != j && matrix[i][k] == value)
                {
                    matrix[i][k] +=10;
                }
            }
        }
    }
}


int main()
{
    int matrix[ROWS][COLS] = {{1,1,4,3,4,1,3,2,2},
                              {1,1,2,3,2,1,3,2,2},
                              {3,2,1,4,3,3,2,1,3},
                              {4,3,4,2,3,1,1,2,4},
                              {4,2,1,1,2,3,3,4,1},
                              {2,2,3,3,4,4,4,1,2},
                              {2,3,3,1,3,2,2,4,1},
                              {4,4,2,1,3,1,2,3,3},
                              {4,4,2,1,1,1,2,3,3}};

    finder(matrix);
                
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {   
            if(matrix[i][j] > 10)
                cout << COLOR << matrix[i][j] << RESET <<'\t';
            else
                cout << matrix[i][j] <<'\t';
        }
        cout << '\n';
    }
    return 0;
}