#include <stdio.h>
#include <math.h>
#include "logistic_regression.h"

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

double predict_proba(LogisticRegression *model, double x) {
    return sigmoid(model->weight * x + model->bias);
}

int predict(LogisticRegression *model, double x) {
    return predict_proba(model, x) >= 0.5 ? 1 : 0;
}

void train(LogisticRegression *model, double *x, double *y, int n, double lr, int epochs) {
    for (int e = 0; e < epochs; e++) {
        double dw = 0.0;
        double db = 0.0;

        for (int i = 0; i < n; i++) {
            double y_pred = predict_proba(model, x[i]);
            double error = y_pred - y[i];

            dw += error * x[i];
            db += error;
        }

        dw /= n;
        db /= n;

        model->weight -= lr * dw;
        model->bias -= lr * db;

        if (e % 100 == 0) {
            printf("Epoch %d\n", e);
        }
    }
}
