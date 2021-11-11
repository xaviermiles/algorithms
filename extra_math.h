#include <math.h>

int euclids_gcd(int x, int y) {
    /*
     * Returns the greatest common divisor of two integers
     *
     * https://en.wikipedia.org/wiki/Algorithm#Euclid's_algorithm
     */
    int r;
    if (x == 0 | y == 0) return 0;

    if (y > x) { // swap so x is biggest
        r = x;
        x = y;
        y = r;
    }

    while (true) {
        r = x % y;
        if (r == 0) return abs(y);
        x = y;
        y = r;
    }
}
