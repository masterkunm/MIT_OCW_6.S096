#include <stdio.h>
#include <math.h>

#define BYTE 32
#define FRACTION 23
#define FRAC_START 9
// in binary right is less
#define EXPO_START 8
#define EXPONENT 8
#define BASE 127

union float_bit {
    float f;
    unsigned int bits;
};

// (5.0f) print_hex output looks like "0x40a00000" in hex format
void print_hex(float inf) {
    union float_bit new;
    new.f = inf;
    printf("0x%x\n", new.bits);
}

void problem1_sol(float inf) {
    // new union
    union float_bit t;
    // store floating point number
    t.f = inf;

    // size 32 bits
    // C compiler not allows to use variable even const variable to statically initialise an array;
    // const int size = 32;
    unsigned int mask = 1;
    // array to store each bit of floating number
    int b[BYTE] = {0};
    for (int i = 0; i < BYTE; i++) {
        if ( (mask & t.bits) != 0 ) {
            b[i] = 1;
        }
        mask = mask << 1;
    }

    // output -> macOS -> x86 -> little endian -> reverse output
    for (int i = BYTE - 1; i >= 0; i--) {
        printf("%d", b[i]);
    } 

    // reverse
    int end = BYTE - 1;
    int start = 0;
    while (end > start) {
        int temp = b[end];
        b[end] = b[start];
        b[start] = temp;
        end--;
        start++;
    }

    // newline
    putchar('\n');

    // check sign bit
    if (b[0] == 1) {
        printf("-");
    }

    // fraction part: mantissa bits
    printf("1.");
    for (int i = 0; i < FRACTION; i++) {
        printf("%d", b[FRAC_START + i]);
    }

    printf(" * 2^");

    // exponent bits
    int exp = 0;
    for (int i = 0; i < EXPONENT; i++) {
        if (b[EXPO_START - i] > 0) {
            exp = exp + (int)pow( (double)2, (double)i );
        }
    }

    printf("%d\n", exp - BASE);
}

int main() {
    float fnum = -7.333;

    print_hex(fnum);

    problem1_sol(fnum);

    return 0;
}
