#include <stdio.h>

int gcd(int a, int b);

int main () {
    int size = 0;
    scanf("%d", &size);
    int placeHolderA = 0;
    int placeHolderB = 0;
    int gcdResultArr[size];
    for(int i = 0; i < size; i++) {
        scanf("%d%d", &placeHolderA, &placeHolderB);
        gcdResultArr[i] = gcd(placeHolderA, placeHolderB);
    }
    for(int i = 0; i < size; i++) {
        printf("%d\n", gcdResultArr[i]);
    }
    return 0;
}

int gcd(int a, int b) {
    if(a == 0 || b == 0) return a+b; // base case
    return gcd(b, a % b);
}
