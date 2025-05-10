#include <iostream>
using namespace std;

const int COLS = 9;
const int ROWS = 9;

const string COLOR = "\033[30;47m";
const string RESET = "\033[0m";

bool canMark(int row, int col, bool marks[ROWS][COLS])
{
    int unmarkedInRow = 0;
    for (int j = 0; j < COLS; j++)
    {
        if(!marks[row][j] && j != col)
            unmarkedInRow++;
    }
    if(unmarkedInRow == 0)
        return false;

    int unmarkedInCol = 0;
    for (int i = 0; i < ROWS; i++)
    {
        if(!marks[i][col] && i != row)
            unmarkedInCol++;
    }
    if(unmarkedInCol == 0)
        return false;

    return true;
}

void finder(int matrix[ROWS][COLS],bool marks[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        bool visited[COLS] = {};

        for (int j = 0; j < COLS; j++)
        {
            if(visited[j])
                continue;

            int count = 0;
            int indices[COLS];

            for(int k = 0; k < COLS; k++)
            {
                if(matrix[i][j] == matrix [i][k])
                {
                    indices[count++] = k;
                    visited[k] = true;
                }
            }
            
            if(count > 1)
            {
                for (int x = 1; x < count; x++)
                {
                    if(canMark(i, indices[x], marks))
                        marks[i][indices[x]] = true;
                }
            }
        }
    }

    for (int j = 0; j < COLS; j++)
    {
        bool visited[ROWS] = {};

        for (int i = 0; i < ROWS; i++)
        {
            if(visited[i])
                continue;
            int count = 0;
            int indices[ROWS];

            for (int k = 0; k < ROWS; k++)
            {
                if(matrix[i][j] == matrix[k][j])
                {
                    indices[count++] = k;
                    visited[k] = true;
                }
            }

            if(count > 1)
            {
                for (int x = 0; x < count; x++)
                {
                    if(canMark(i, indices[x], marks))
                        marks[indices[x]][j] = true;
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

    bool marks[ROWS][COLS] = {};

    finder(matrix, marks);
                
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {   
            cout << (marks[i][j] ? RESET : COLOR) << matrix[i][j] << ' ';
        }
        cout << RESET << '\n';
    }
    return 0;
}