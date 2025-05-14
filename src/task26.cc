#include "../include/MatrixMarker.h"

int main() {
    int input[ROWS][COLS] = {
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

    std::cout << "Before:\n";
    marker.print();

    marker.process();

    std::cout << "\nAfter:\n";
    marker.print();

    return 0;
}
