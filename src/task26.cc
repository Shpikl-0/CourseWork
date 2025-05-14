#include <iostream>
using namespace std;

class MatrixMarker 
{
private:
    static const int ROWS = 9;
    static const int COLS = 9;
    static const string COLOR;
    static const string RESET;

    int matrix[ROWS][COLS];
    bool marks[ROWS][COLS];

    bool canMark(int row, int col) {
        int unmarkedInRow = 0;
        for (int j = 0; j < COLS; j++) {
            if (!marks[row][j] && j != col)
                unmarkedInRow++;
        }
        if (unmarkedInRow == 0)
            return false;

        int unmarkedInCol = 0;
        for (int i = 0; i < ROWS; i++) {
            if (!marks[i][col] && i != row)
                unmarkedInCol++;
        }
        if (unmarkedInCol == 0)
            return false;

        return true;
    }

    void findDuplicatesInRows() {
        for (int i = 0; i < ROWS; i++) {
            bool visited[COLS] = {};
            for (int j = 0; j < COLS; j++) {
                if (visited[j]) continue;

                int count = 0;
                int indices[COLS];

                for (int k = 0; k < COLS; k++) {
                    if (matrix[i][j] == matrix[i][k]) {
                        indices[count++] = k;
                        visited[k] = true;
                    }
                }

                if (count > 1) {
                    for (int x = 1; x < count; x++) {
                        if (canMark(i, indices[x]))
                            marks[i][indices[x]] = true;
                    }
                }
            }
        }
    }

    void findDuplicatesInCols() {
        for (int j = 0; j < COLS; j++) {
            bool visited[ROWS] = {};
            for (int i = 0; i < ROWS; i++) {
                if (visited[i]) continue;

                int count = 0;
                int indices[ROWS];

                for (int k = 0; k < ROWS; k++) {
                    if (matrix[i][j] == matrix[k][j]) {
                        indices[count++] = k;
                        visited[k] = true;
                    }
                }

                if (count > 1) {
                    for (int x = 1; x < count; x++) {
                        if (canMark(indices[x], j))
                            marks[indices[x]][j] = true;
                    }
                }
            }
        }
    }

public:
    MatrixMarker(int input[ROWS][COLS]) {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) {
                matrix[i][j] = input[i][j];
                marks[i][j] = false;
            }
    }

    void process() {
        findDuplicatesInRows();
        findDuplicatesInCols();
    }

    void print() const {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cout << (marks[i][j] ? RESET : COLOR) << matrix[i][j] << ' ';
            }
            cout << RESET << '\n';
        }
    }
};

const string MatrixMarker::COLOR = "\033[30;47m";
const string MatrixMarker::RESET = "\033[0m";

int main() {
    int input[9][9] = {
        {1,1,4,3,4,1,3,2,2},
        {1,1,2,3,2,1,3,2,2},
        {3,2,1,4,3,3,2,1,3},
        {4,3,4,2,3,1,1,2,4},
        {4,2,1,1,2,3,3,4,1},
        {2,2,3,3,4,4,4,1,2},
        {2,3,3,1,3,2,2,4,1},
        {4,4,2,1,3,1,2,3,3},
        {4,4,2,1,1,1,2,3,3}
    };

    MatrixMarker marker(input);

    cout << "Before:\n";
    marker.print();

    marker.process();

    cout << "\nAfter:\n";
    marker.print();

    return 0;
}