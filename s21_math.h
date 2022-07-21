#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>


#define EPS 1E-8
static double const s21_NAN = 0.0 / 0.0;
static double const s21_POS_INF = 1.0 /0.0;
static double const s21_NEG_INF = -1.0/0.0;

static long double PI = 3.14159265358979323846;
static long double const LN10 = 2.302585092994045684;
static long double const LN2 = 0.693147180559945309417232121458;
static long double const E = 2.718281828459;
static long double const PI_2 = 1.57079632679489661923132169163975144;


long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);

double x_to_trigonometric_circle(double x);
double find_point_surrounding(double x);
long double sine_via_taylor(double x, double x0);
long double cosine_via_taylor(double x, double x0);
double simple_sin(double x0);
double simple_cos(double x0);
long long factorial(int n);
long double simple_pow(double base, int exp);
long double asin_via_taylor(double x);
long double atan_via_taylor(double x);


long double s21_log(double x);
long double s21_exp(double x);
long double s21_pow(double base, double exp);
long double s21_sqrt(double x);
long int s21_abs(int x);
long double s21_fabs(double x);
long double s21_trunc(double x);
long double s21_fmod(double x, double y);
long double s21_ceil(double x);
long double s21_floor(double x);


long double pow_2(int power);
void d_ecvt(long double* res);
void get_f(long double* res);
#endif  // SRC_S21_MATH_H_
