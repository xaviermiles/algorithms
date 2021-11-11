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

bool is_coprime(int x, int y) {
    /*
     * Is the two integers coprime/relatively prime?
     */
    return euclids_gcd(x, y) == 1;
}

int lcm(int x, int y) {
    /*
     * Least common multiple of two integers
     */
    return x * y / euclids_gcd(x, y);
}

bool is_prime(int n) {
    /*
     * Is the integer a prime number? - Trial division technique
     */
    for (int x = 2; x <= ceil(sqrt(n)); x++) {
        if (euclids_gcd(n, x) > 1) return false;
    }
    return true;
}
