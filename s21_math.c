// "Copyright [2022] <hhannema>"
#include "s21_math.h"

long double s21_sin(double x) {
    x = x_to_trigonometric_circle(x);
    double x0 = find_point_surrounding(x);
    long double sine = sine_via_taylor(x, x0);
    return sine;
}

long double s21_cos(double x) {
    x = x_to_trigonometric_circle(x);
    double x0 = find_point_surrounding(x);
    long double cosine = cosine_via_taylor(x, x0);
    return cosine;
}

long double s21_tan(double x) {
    long double res = 0;
    long double cosine = s21_cos(x);
    long double sine = s21_sin(x);
    if (cosine != 0) {
        res = sine / cosine;
    } else {
        res = s21_NAN;
    }
    return res;
}

double x_to_trigonometric_circle(double x) {
    if (x > 2 * PI) {
        while (x > 2 * PI) {
            x -= 2 * PI;
        }
    }
    if (x < 0) {
        while (x < 0) {
            x += 2 * PI;
        }
    }
    return x;
}

double find_point_surrounding(double x) {
    double points[20];
    for (int i = 0; i <= 12; i++) {
        points[i] = i * PI / 6;
    }
    double eps = (points[1] - points[0]) / 2;
    int i = 0;
    for (; i <= 12; i++) {
        if (x - points[i] <= eps)
            break;
    }
    double x0 = points[i];
    return x0;
}

long double sine_via_taylor(double x, double x0) {
    double sine = 0;
    double y0 = 1;
    int i = 0;
    while (s21_fabs(y0) > EPS || i < 50) {
        if (i % 4 == 0) {
            y0 = simple_sin(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 1) {
            y0 = simple_cos(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 2) {
            y0 = -simple_sin(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 3) {
            y0 = -simple_cos(x0) * simple_pow(x - x0, i) / factorial(i);
        }
        sine += y0;
        i++;
    }
    return (long double)sine;
}

long double cosine_via_taylor(double x, double x0) {
    double cosine = 0;
    double y0 = 1;
    int i = 0;
    while (s21_fabs(y0) > EPS || i < 50) {
        if (i % 4 == 0) {
            y0 = simple_cos(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 1) {
            y0 = -simple_sin(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 2) {
            y0 = -simple_cos(x0) * simple_pow(x - x0, i) / factorial(i);
        } else if (i % 4 == 3) {
            y0 = simple_sin(x0) * simple_pow(x - x0, i) / factorial(i);
        }
        cosine += y0;
        i++;
    }
    return (long double)cosine;
}

double simple_sin(double x0) {
    double sin = 0;
    if ((x0) < EPS || s21_fabs(x0 - PI) < EPS || s21_fabs(x0 - 2 * PI) < EPS) {
        sin = 0;
    } else if (s21_fabs(x0 - PI / 6) < EPS || s21_fabs(x0 - 5 * PI / 6) < EPS) {
        sin = 0.5;
    } else if (s21_fabs(x0 - PI / 3) < EPS || s21_fabs(x0 - 2 * PI / 3) < EPS) {
        sin = 0.866025403;
    } else if (s21_fabs(x0 - PI / 2) < EPS) {
        sin = 1;
    } else if (s21_fabs(x0 - 3 * PI / 2) < EPS) {
        sin = -1;
    } else if (s21_fabs(x0 - 7 * PI / 6) < EPS || s21_fabs(x0 - 11 * PI / 6) < EPS) {
        sin = -0.5;
    } else if (s21_fabs(x0 - 4 * PI / 3) < EPS || s21_fabs(x0 - 5 * PI / 3) < EPS) {
        sin = -0.866025403;
    }
    return sin;
}

double simple_cos(double x0) {
    double cos = 0;
    if (x0 < EPS || s21_fabs(x0 - 2.0 * PI) < EPS) {
        cos = 1.0;
    } else if (s21_fabs(x0 - PI / 6.0) < EPS || s21_fabs(x0 - 11 * PI / 6.0) < EPS) {
        cos = 0.86602540378;
    } else if (s21_fabs(x0 - PI / 3.0) < EPS || s21_fabs(x0 - 5.0 * PI / 3.0) < EPS) {
        cos = 0.5;
    } else if (s21_fabs(x0 - PI / 2.0) < EPS || s21_fabs(x0 - 3.0 * PI / 2.0) < EPS) {
        cos = 0;
    } else if (s21_fabs(x0 - 2.0 * PI / 3.0) < EPS || s21_fabs(x0 - 4.0 * PI / 3.0) < EPS) {
        cos = -0.5;
    } else if (s21_fabs(x0 - 5.0 * PI / 6.0) < EPS || s21_fabs(x0 - 7.0 * PI / 6.0) < EPS) {
        cos = -0.86602540378;
    } else if (s21_fabs(x0 - PI) < EPS) {
        cos = -1.0;
    }
    return cos;
}

long long factorial(int n) {
    long long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

long double simple_pow(double base, int exp) {
    long double res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

long double s21_asin(double x) {
    long double arcsin;
    if (x <= 0.5 && x >= 0) {
        arcsin = asin_via_taylor(x);
    } else if (x > 0.5 && x <= 1) {
        arcsin = PI_2 - 2.0 * s21_asin(s21_sqrt((1.0 - x) / 2.0));
    } else if (x < 0 && x >= -1) {
        x = s21_fabs(x);
        arcsin = -s21_asin(x);
    } else {
        arcsin = s21_NAN;
    }
    return arcsin;
}

long int s21_abs(int x) { return (x < 0) ? -x : x; }

long double s21_fabs(double x) {
    return  x < -EPS ? -x : x;
}

long double asin_via_taylor(double x) {
    long double arcsin = 0;
    long double y0 = 1;
    int i = 0;
    while (i < 20) {
        y0 = (factorial(2 * i) * simple_pow(x, 2 * i + 1)) /
            ((simple_pow(2, 2 * i) * factorial(i) * factorial(i) * (2 * i + 1)));
        arcsin += y0;
        i++;
    }
    return arcsin;
}

long double s21_acos(double x) {
    long double arccos;
    if (x >= -1 && x <= 1) {
        arccos = PI / 2.0 - s21_asin(x);
    } else {
        arccos = s21_NAN;
    }
    return arccos;
}

long double s21_atan(double x) {
    long double res = 0;
    if (x != x) {
        res = x;
    } else {
        int sign = x >= 0 ? 0 : 1;
        x = s21_fabs(x);
        if (x >= 0 && x < 0.98) {
            res = atan_via_taylor(x);
        } else if (x >= 0.98 && x <= 1) {
            res = x / s21_sqrt(s21_pow(x, 2) + 1);
            res = s21_asin(res);
        } else {
            res = PI_2 - s21_atan(1.0 / x);
        }
        res *= sign ? -1 : 1;
    }
    return res;
}

long double atan_via_taylor(double x) {
    long double arctan = 0;
    long double y0 = 1;
    int i = 1;
    while (i < 100) {
        y0 = simple_pow(-1, i - 1) * simple_pow(x, 2 * i - 1) / (2 * i - 1);
        arctan += y0;
        i++;
    }
    return arctan;
}

long double pow_2(int power) {
    long double res = 1;
    for (size_t i = 0; i < power; i++) {
        res *= 2;
    }
    return res;
}

void d_ecvt(long double* res) {
    if (res[0] < EPS) {
        res[1] = 0;
    } else {
        while ((long long int)res[0] >= 10) {
            res[1] += 1;
            res[0] /= 10;
        }
    }
}

void get_f(long double* res) {
    if (res[0] < EPS) {
        res[1] = 0;
    } else if (res[0] < 1.0L) {
        while (res[0] < 1.0L) {
            res[0] *= 2L;
            res[1]--;
        }
    } else {
        while (res[0] >= 2.0L) {
            res[0] *= 0.5L;
            res[1]++;
        }
    }
}

long double s21_log(double x) {
    long double res = 0, f;
    long double exp[2] = { x, 0 }, f_k[2] = { x, 0 };
    if (x == s21_POS_INF || x == s21_NEG_INF) {
        res = s21_POS_INF;
    } else {
        d_ecvt(exp);
        f_k[0] = exp[0];
        get_f(f_k);

        x = f_k[0] - 1.0L;
        f = x;
        long double sign = -1;
        for (int i = 1; i < 300; i++) {
            f += (long double)sign * (simple_pow(x, i + 1) / (long double)(i + 1));
            sign = -sign;
        }
        if (exp[0] == 0) {
            res = s21_NEG_INF;
        } else if (exp[0] < 0) {
            res = s21_NAN;
        } else {
            res = (exp[1]) * LN10 + f_k[1] * LN2 + f;
        }
    }
    return res;
}

long double s21_exp(double x) {
    long double res = 1.0L;
    long double x_0 = s21_fabs(x);
    long long k = s21_ceil(x_0 / LN2 - LN2 / 2.0);
    long double tk = 1.0L;
    long double r = (long double)x_0 - ((long double)k * LN2);
    for (int i = 1; i < 300; i++) {
        tk *= r / i;
        res += tk;
    }
    if (x < 0) {
        res = 1 / (res * pow_2(k));
    } else {
        res *= pow_2(k);
    }
    return res;
}

long double s21_pow(double base, double exp) {
    long double res = 0;
    short sign = 1;
    if (base < 0 && s21_abs((int)exp) % 2 == 1)
        sign = -sign;
    if (base == -1 && (exp == s21_NEG_INF || exp == s21_POS_INF))
        res = 1.0;
    else
        res = sign * s21_exp(exp * s21_log(s21_fabs(base)));
    return res;
}

long double s21_sqrt(double x) {
    double x0 = x, res = 0;
    int count = 0;
    if (x < 0) {
        res = -s21_NAN;
    } else if (x > EPS) {
        while (1) {
            count++;
            res = 0.5 * (x0 + (x / x0));
            if (s21_fabs(res - x0) < 1E-7)
                break;
            x0 = res;
        }
    }
    return res;
}

long double s21_trunc(double x) {
    return (long long)x;
}

long double s21_fmod(double x, double y) {
    return x - s21_trunc(x / y) * y;
}

long double s21_ceil(double x) {
    long double res = x;

    if (x >= LLONG_MAX || x <= LLONG_MIN || x != x) {
        res = x;
    } else {
        long long n = (long long)x;
        if ((double)n == x || x <= 0) {
            res = n;
        } else {
            res = n + 1;
        }
    }
    return res;
}

long double s21_floor(double x) {
    long double res = x;
    if (x >= LLONG_MAX || x <= LLONG_MIN || x != x) {
        res = x;
    } else {
        long long n = (long long)x;
        if ((double)n == x || x >= 0) {
            res = n;
        } else {
            res = n - 1;
        }
    }
    return res;
}
