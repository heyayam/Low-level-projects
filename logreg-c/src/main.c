#include <stdio.h>
#include "logistic_regression.h"

int main() {
    double x[] = {1,2,3,4,5,6};
    double y[] = {0,0,0,1,1,1};
    int n = 6;

    LogisticRegression model = {0.0, 0.0};

    train(&model, x, y, n, 0.1, 1000);

    printf("Weight: %f\n", model.weight);
    printf("Bias: %f\n", model.bias);

    for (int i = 0; i < n; i++) {
        printf("x=%.1f -> pred=%d\n", x[i], predict(&model, x[i]));
    }

    return 0;
}
