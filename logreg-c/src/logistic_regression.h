#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

typedef struct {
    double weight;
    double bias;
} LogisticRegression;

void train(LogisticRegression *model, double *x, double *y, int n, double lr, int epochs);
double predict_proba(LogisticRegression *model, double x);
int predict(LogisticRegression *model, double x);

#endif
