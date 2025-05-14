#ifndef MATRIX_MARKER_H
#define MATRIX_MARKER_H

#include "Config.h"
#include <iostream>

class MatrixMarker {
private:
    int matrix[ROWS][COLS];
    bool marks[ROWS][COLS];

    bool canMark(int row, int col);
    void findDuplicatesInRows();
    void findDuplicatesInCols();

public:
    MatrixMarker(int input[ROWS][COLS]);
    void process();
    void print() const;
};

#endif // MATRIX_MARKER_H
