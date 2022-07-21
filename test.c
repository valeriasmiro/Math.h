#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(s21_abs_test) {
    ck_assert_int_eq(abs(-4), s21_abs(-4));
    ck_assert_int_eq(abs(0), s21_abs(0));
    ck_assert_int_eq(abs(-0), s21_abs(-0));
    ck_assert_int_eq(abs(INT32_MAX), s21_abs(INT32_MAX));
    ck_assert_int_eq(abs(INT32_MIN), s21_abs(INT32_MIN));
}
END_TEST


START_TEST(s21_fabs_test) {
    ck_assert_double_eq(fabs(-4.123456), s21_fabs(-4.123456));
    ck_assert_double_eq(fabs(0.0000001), s21_fabs(0.0000001));
    ck_assert_double_eq(fabs(-0.00001), s21_fabs(-0.00001));
    ck_assert_double_eq(fabs(-10), s21_fabs(-10));
    ck_assert_double_eq(fabs(12345678), s21_fabs(12345678));
    ck_assert_double_eq(fabs(-0.1), s21_fabs(-0.1));
}
END_TEST


START_TEST(s21_ceil_test) {
    ck_assert_double_eq(ceil(-4.123456), s21_ceil(-4.123456));
    ck_assert_double_eq(ceil(0.0000001), s21_ceil(0.0000001));
    ck_assert_double_eq(ceil(-0.00001), s21_ceil(-0.00001));
    ck_assert_double_eq(ceil(-10), s21_ceil(-10));
    ck_assert_double_eq(ceil(12345678), s21_ceil(12345678));
    ck_assert_double_eq(ceil(-0.1), s21_ceil(-0.1));
    ck_assert_double_eq(ceil(1234.000000001), s21_ceil(1234.000000001));
    ck_assert_double_eq(ceil(-115.0000001), s21_ceil(-115.0000001));
    ck_assert_double_eq(ceil(-10000000.2), s21_ceil(-10000000.2));
}
END_TEST


START_TEST(s21_floor_test) {
    ck_assert_double_eq(floor(-4.123456), s21_floor(-4.123456));
    ck_assert_double_eq(floor(0.0000001), s21_floor(0.0000001));
    ck_assert_double_eq(floor(-0.00001), s21_floor(-0.00001));
    ck_assert_double_eq(floor(-10), s21_floor(-10));
    ck_assert_double_eq(floor(12345678), s21_floor(12345678));
    ck_assert_double_eq(floor(-0.1), s21_floor(-0.1));
    ck_assert_double_eq(floor(1234.000000001), s21_floor(1234.000000001));
    ck_assert_double_eq(floor(-115.0000001), s21_floor(-115.0000001));
    ck_assert_double_eq(floor(-10000000.2), s21_floor(-10000000.2));
}
END_TEST


START_TEST(s21_sqrt_test) {
    ck_assert_ldouble_eq_tol(sqrt(1), s21_sqrt(1), 6);
    ck_assert_ldouble_eq_tol(sqrt(5.123), s21_sqrt(5.123), 6);
    ck_assert_ldouble_eq_tol(sqrt(0), s21_sqrt(0), 6);
    ck_assert_ldouble_eq_tol(sqrt(15.12345), s21_sqrt(15.12345), 6);
    ck_assert_ldouble_eq_tol(sqrt(123.12345), s21_sqrt(123.12345), 6);
    ck_assert_ldouble_eq_tol(sqrt(0.000002), s21_sqrt(0.000002), 6);

    for (double i = -100; i < 0; i += PI) {
        for (double j = 100; j >  0; j -= LN10) {
            double temp = floor(1E6 * (i + j)) / 1E6;
            if (temp > 0)
                ck_assert_ldouble_eq_tol(sqrt(temp), s21_sqrt(temp), 6);
        }
    }
}
END_TEST

START_TEST(s21_log_test) {
    ck_assert_ldouble_eq_tol(log(1), s21_log(1), 6);
    ck_assert_ldouble_eq_tol(log(5.123), s21_log(5.123), 6);
    ck_assert_ldouble_infinite(s21_log(0));
    ck_assert_ldouble_infinite(s21_log(-0));
    ck_assert_ldouble_eq_tol(log(INT32_MAX), s21_log(INT32_MAX), 6);
    ck_assert_ldouble_eq_tol(log(0.12345), s21_log(0.12345), 6);
    ck_assert_ldouble_eq_tol(log(5.5444444444), s21_log(5.5444444444), 6);
    ck_assert_ldouble_eq_tol(log(12345.98765), s21_log(12345.98765), 6);
}
END_TEST

START_TEST(s21_exp_test) {
    ck_assert_ldouble_eq_tol(exp(1), s21_exp(1), 6);
    ck_assert_ldouble_eq_tol(exp(5.123), s21_exp(5.123), 6);
    ck_assert_ldouble_eq_tol(exp(0), s21_exp(0), 6);
    ck_assert_ldouble_eq_tol(exp(0.12345), s21_exp(0.12345), 6);
    ck_assert_ldouble_eq_tol(exp(5.5444444444), s21_exp(5.5444444444), 6);
    ck_assert_ldouble_eq_tol(exp(-5.54444444), s21_exp(-5.54444444), 6);
    ck_assert_ldouble_eq_tol(exp(-0.5), s21_exp(-0.5), 6);
    ck_assert_ldouble_eq_tol(exp(15), s21_exp(15), 6);
    ck_assert_ldouble_eq_tol(exp(-10.544), s21_exp(-10.544), 6);
    ck_assert_ldouble_eq_tol(exp(19), s21_exp(19), 6);
}
END_TEST


START_TEST(s21_fmod_test) {
    char buff0[50], buff1[50];
    double temp;
    for (double i = - 100; i < 100; i += PI) {
        for (double j = 100; j >  -100; j -= LN10) {
            if ((temp = fmod(i, j)) > EPS) {
                ck_assert_ldouble_eq_tol(fmod(i, j), s21_fmod(i, j), 6);
            }
        }
    }
}
END_TEST

START_TEST(s21_pow_test) {
    char buff0[50], buff1[50];
    for (double i = -100; i < 100; i += PI) {
        for (double j = -10; j > -10; j -= 0.03) {
            i = floor(1E6 * i) / 1E6;
            j = floor(1E6 * j) / 1E6;
            ck_assert_ldouble_eq_tol(pow(i, j), s21_pow(i, j), 6);
        }
    }
}
END_TEST

START_TEST(s21_sin_test) {
    ck_assert_ldouble_eq_tol(sin(0.000001), s21_sin(0.000001), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 13), s21_sin(PI / 13), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 12), s21_sin(PI / 12), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 11), s21_sin(PI / 11), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 6 + 0.000001), s21_sin(PI / 6 + 0.000001), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 4), s21_sin(PI / 4), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 3 + 0.001), s21_sin(PI / 3 + 0.001), 6);
    ck_assert_ldouble_eq_tol(sin(PI / 2 + 1), s21_sin(PI / 2  + 1), 6);
    ck_assert_ldouble_eq_tol(sin(2 * PI / 3 + 0.005), s21_sin(2 * PI / 3 + 0.005), 6);
    ck_assert_ldouble_eq_tol(sin(15 * PI / 12), s21_sin(15 * PI / 12), 6);
    ck_assert_ldouble_eq_tol(sin(18 * PI / 13), s21_sin(18 * PI / 13), 6);
    ck_assert_ldouble_eq_tol(sin(25 * PI / 16), s21_sin(25 * PI / 16), 6);
    ck_assert_ldouble_eq_tol(sin(27 * PI / 13), s21_sin(27 * PI / 13), 6);
    ck_assert_ldouble_eq_tol(sin(20 * PI / 3), s21_sin(20 * PI / 3), 6);
    ck_assert_ldouble_eq_tol(sin(-1.2 * PI), s21_sin(-1.2 * PI), 6);
    ck_assert_ldouble_eq_tol(sin(5005005 * PI), s21_sin(5005005 * PI), 6);
    ck_assert_ldouble_eq_tol(sin(-19388744 * PI), s21_sin(-19388744 * PI), 6);
    ck_assert_ldouble_eq_tol(sin(-PI), s21_sin(-PI), 6);
}
END_TEST

START_TEST(s21_cos_test) {
    ck_assert_ldouble_eq_tol(cos(0.000001), s21_cos(0.000001), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 13), s21_cos(PI / 13), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 12), s21_cos(PI / 12), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 11), s21_cos(PI / 11), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 6 + 0.000001), s21_cos(PI / 6 + 0.000001), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 4), s21_cos(PI / 4), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 3 + 0.001), s21_cos(PI / 3 + 0.001), 6);
    ck_assert_ldouble_eq_tol(cos(PI / 2 + 1), s21_cos(PI / 2  + 1), 6);
    ck_assert_ldouble_eq_tol(cos(2 * PI / 3 + 0.005), s21_cos(2 * PI / 3 + 0.005), 6);
    ck_assert_ldouble_eq_tol(cos(15 * PI / 12), s21_cos(15 * PI / 12), 6);
    ck_assert_ldouble_eq_tol(cos(18 * PI / 13), s21_cos(18 * PI / 13), 6);
    ck_assert_ldouble_eq_tol(cos(25 * PI / 16), s21_cos(25 * PI / 16), 6);
    ck_assert_ldouble_eq_tol(cos(27 * PI / 13), s21_cos(27 * PI / 13), 6);
    ck_assert_ldouble_eq_tol(cos(20 * PI / 3), s21_cos(20 * PI / 3), 6);
    ck_assert_ldouble_eq_tol(cos(-1.2 * PI), s21_cos(-1.2 * PI), 6);
    ck_assert_ldouble_eq_tol(cos(5005005 * PI), s21_cos(5005005 * PI), 6);
    ck_assert_ldouble_eq_tol(cos(-19388744 * PI), s21_cos(-19388744 * PI), 6);
}
END_TEST

START_TEST(s21_asin_test) {
    ck_assert_ldouble_eq_tol(asin(-1), s21_asin(-1), 6);
    ck_assert_ldouble_eq_tol(asin(1), s21_asin(1), 6);
    ck_assert_ldouble_eq_tol(asin(0.999999), s21_asin(0.999999), 6);
    ck_assert_ldouble_eq_tol(asin(0.788911), s21_asin(0.788911), 6);
    ck_assert_ldouble_eq_tol(asin(-0.999999), s21_asin(-0.999999), 6);
    ck_assert_ldouble_eq_tol(asin(0.412345), s21_asin(0.412345), 6);
    ck_assert_ldouble_eq_tol(asin(0.65), s21_asin(0.65), 6);
    ck_assert_ldouble_eq_tol(asin(0.833333), s21_asin(0.833333), 6);
    ck_assert_ldouble_eq_tol(asin(0.222222), s21_asin(0.222222), 6);
    ck_assert_ldouble_eq_tol(asin(-0.00001), s21_asin(-0.00001), 6);
    ck_assert_ldouble_eq_tol(asin(-0.000001), s21_asin(-0.000001), 6);
    ck_assert_ldouble_nan(s21_asin(1.000001));
    ck_assert_ldouble_nan(s21_asin(-1.000001));
    ck_assert_ldouble_eq_tol(asin(0.000000), s21_asin(0.000000), 6);
}
END_TEST

START_TEST(s21_acos_test) {
    ck_assert_ldouble_eq_tol(acos(-1), s21_acos(-1), 6);
    ck_assert_ldouble_eq_tol(acos(1), s21_acos(1), 6);
    ck_assert_ldouble_eq_tol(acos(0.999999), s21_acos(0.999999), 6);
    ck_assert_ldouble_eq_tol(acos(0.788911), s21_acos(0.788911), 6);
    ck_assert_ldouble_eq_tol(acos(-0.999999), s21_acos(-0.999999), 6);
    ck_assert_ldouble_eq_tol(acos(0.412345), s21_acos(0.412345), 6);
    ck_assert_ldouble_eq_tol(acos(0.65), s21_acos(0.65), 6);
    ck_assert_ldouble_eq_tol(acos(0.833333), s21_acos(0.833333), 6);
    ck_assert_ldouble_eq_tol(acos(0.222222), s21_acos(0.222222), 6);
    ck_assert_ldouble_eq_tol(acos(0.000001), s21_acos(0.000001), 6);
    ck_assert_ldouble_eq_tol(acos(-0.000001), s21_acos(-0.000001), 6);
    ck_assert_ldouble_nan(s21_acos(1.000001));
    ck_assert_ldouble_nan(s21_acos(-1.000001));
    ck_assert_ldouble_eq_tol(acos(0.000000), s21_acos(0.000000), 6);
}
END_TEST

START_TEST(s21_atan_test) {
    char buff0[50], buff1[50];
    for (double i = -10; i <= 10; i += 0.5) {
        i = floor(1E6 * i) / 1E6;
        ck_assert_ldouble_eq_tol(atan(i), s21_atan(i), 6);
    }
    ck_assert_ldouble_eq_tol(atan(50.00000), s21_atan(50.00000), 6);
    ck_assert_ldouble_eq_tol(atan(-50.00000), s21_atan(-50.00000), 6);
    ck_assert_ldouble_eq_tol(atan(100000000000), s21_atan(100000000000), 6);
}
END_TEST

START_TEST(s21_tan_test) {
    char buff0[50], buff1[50];
    for (double i = -2 * PI; i <= 2 * PI; i += 0.02) {
        i = floor(1E5 * i) / 1E5;
        ck_assert_ldouble_eq_tol(tan(i), s21_tan(i), 6);
    }
    ck_assert_ldouble_eq_tol(tan(50.00000), s21_tan(50.00000), 6);
    ck_assert_ldouble_eq_tol(tan(-50.00000), s21_tan(-50.00000), 6);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, s21_fabs_test);
    tcase_add_test(tc1_1, s21_abs_test);
    tcase_add_test(tc1_1, s21_log_test);
    tcase_add_test(tc1_1, s21_exp_test);
    tcase_add_test(tc1_1, s21_ceil_test);
    tcase_add_test(tc1_1, s21_floor_test);
    tcase_add_test(tc1_1, s21_sqrt_test);
    tcase_add_test(tc1_1, s21_sin_test);
    tcase_add_test(tc1_1, s21_cos_test);
    tcase_add_test(tc1_1, s21_tan_test);
    tcase_add_test(tc1_1, s21_asin_test);
    tcase_add_test(tc1_1, s21_acos_test);
    tcase_add_test(tc1_1, s21_atan_test);
    tcase_add_test(tc1_1, s21_fmod_test);
    tcase_add_test(tc1_1, s21_pow_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
