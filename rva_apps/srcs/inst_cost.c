#include "rva-fwk.h"
#include <stdlib.h>

int breakpoint(int x, int y) {
    return x+y;
}

int main () {
    breakpoint(1,2);
    ROCC_INSTRUCTION_R_R_R(1, 0, 0, 0, 0, 10, 11, 12);
    breakpoint(2,3);
    exit(0);
}
