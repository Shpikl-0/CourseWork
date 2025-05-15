#ifndef MATRIX_MARKER_H
#define MATRIX_MARKER_H

#include "Config.h"
#include <iostream>

class MatrixMarker {
private:
    int matrix[ROWS][COLS];
    bool marked[ROWS][COLS];

    bool isMarkAllowed(int row, int col);
    void markRowDuplictes();
    void markColumnDuplicates();

public:
    MatrixMarker(int input[ROWS][COLS]);
    void run();
    void print() const;
};

#endif
