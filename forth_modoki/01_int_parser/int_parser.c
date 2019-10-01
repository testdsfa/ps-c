#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static const char* const input = "123 456  1203";


int main() {
    int answer1 = 0;
    int answer2 = 0;
    int answer3 = 0;

    // write something here.
    /*
    char a[10];
    char b[10];
    char c[10];
    */
    /*
    int a, b, c;
    sscanf(input, "%d%d%d", &a, &b, &c);
    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    answer1 = a;
    answer2 = b;
    answer3 = c;
    */
    char *end;
    answer1 = strtol(input, &end, 10);
    answer2 = strtol(end, &end, 10);
    answer3 = strtol(end, &end, 10);

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);
    assert(answer3 == 1203);

    return 0;
}
