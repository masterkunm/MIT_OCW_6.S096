/*
 * this is diagnostic Test before start of class 6.S096
 * Effective programming of C/C++
 * open course in MIT
 * by Mr Max Zhong
 * 30/4/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
 * problem 8
 */
bool is_prime(int num) {
    // prime number is natural number greater than 1
    if (num <= 1) {
        fprintf(stderr, "argument: natural number greater than 1\n");
        return false;
    }

    // check if num can be divide by another num which is smaller than sqrt(num)
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

/*
 * problem 10
 * 
 * 1. linear search
 * 
 * 2. binary search
 * 
 */

int search(int arr[], int length, int target) {
    if (arr == NULL || length <= 0) return -1;
    
    for (int i = 0; i < length; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    // no match
    return -1;
}

// assume that the arr is sorted
int binarySearch(int arr[], int length, int target) {
    if (arr == NULL || length <= 0) return -1;

    int lo = 0, hi = length - 1;
    
    while (lo < hi) {
        int mid = lo + ( (hi - lo) >> 1 );

        if (arr[mid] < target) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }

    return (lo == hi && arr[lo] == target) ? lo : -1;
}

void swap( int *a, int *b ) {
  int t = *a;
  *a = *b;
  *b = t;
}
 
void permute( int *digits, int n, int p ) {
  printf("%d%d%d\n", digits[0], digits[1], digits[2]);
  if( p == n ) {
    for( int i = 0; i < n; ++i ) {
      printf( "%d ", digits[i] );
    }
    printf( "\n" );
  } else {
    for( int i = p; i < n; ++i ) {
      swap( &digits[p], &digits[i] );
      permute( digits, n, p + 1 );
      swap( &digits[p], &digits[i] );
    }
  }
}
 
void print_permutations( int n ) {
  int *digits = malloc( n * sizeof( int ) );
  for( int i = 0; i < n; ++i ) {
    digits[i] = i + 1;
  }
  permute( digits, n, 0 );
  free( digits );
}

/*
 * test
 */

void test_print_permutations(void) {
  print_permutations( 3 );
}

void test_search() {
    int linearLength = 6, binaryLength = 8;
    int ls[] = { 4, 2, 6, 5, 10, 14 };
    int bs[] = { 3, 5, 6, 9, 11, 15, 16, 20 };

    assert( search(ls, linearLength, 6) == 2 );
    assert( search(ls, linearLength, 10) == 4 );    
    assert( search(ls, linearLength, 4) == 0 );
    assert( search(ls, linearLength, 14) == 5 );

    assert( binarySearch(bs, binaryLength, 3) == 0 );
    assert( binarySearch(bs, binaryLength, 6) == 2 );
    assert( binarySearch(bs, binaryLength, 20) == 7 );
    assert( binarySearch(bs, binaryLength, 11) == 4 );

    printf("pass test_search tests\n");
}


void test_isPrime() {
    int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int composite[] = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26};

    for (int i = 0; i < sizeof(prime) / sizeof(prime[0]); i++) {
        assert(is_prime(prime[i]));
        fprintf(stdout, "pass test prime number: %d\n", prime[i]);
    }

    for (int i = 0; i < sizeof(composite) / sizeof(composite[0]); i++) {
        assert(!is_prime(composite[i]));
        fprintf(stdout, "pass test composite number: %d\n", composite[i]);
    }
}

int main() {
    test_isPrime();
    test_search();
    test_print_permutations();
    return 0;
}