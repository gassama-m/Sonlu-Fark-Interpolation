#ifndef DC_PROJECT
#define DC_PROJECT

void Inputpar(double **, double **, double *, int *);
double CenterInterp(double, double *, double *, int);
double delta(double *, double *, int, int);
double Ileri_Interp(double, double *, double *, int *);
double nabla(double *, double *, int, int);
double Geri_Interp(double, double *, double *, int *);
void menu();
#endif