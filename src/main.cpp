
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "interpolation.h"

using namespace alglib;


int main(int argc, char **argv)
{
    //
    // In this example we demonstrate penalized spline fitting of noisy data
    //
    // We have:
    // * x - abscissas
    // * y - vector of experimental data, straight line with small noise
    //
    real_1d_array x = "[0.00,0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90]";
    real_1d_array y = "[0.10,0.00,0.30,0.40,0.30,0.40,0.62,0.68,0.75,0.95,2.10,0.00,1.30,2.40,2.30,2.40,2.62,2.68,2.75,2.95]";

    double v;
    spline1dinterpolant s;
    spline1dfitreport rep;
    double rho;
    //
    // Fit with VERY small amount of smoothing (rho = -5.0)
    // and large number of basis functions (M=50).
    //
    // With such small regularization penalized spline almost fully reproduces function values
    //
        printf("test0");
    rho = 0.001;
    spline1dfit(x, y, 50, rho, s, rep);
    
    printf("test1");

    //
    // Fit with VERY large amount of smoothing (rho = 10.0)
    // and large number of basis functions (M=50).
    //
    // With such regularization our spline should become close to the straight line fit.
    // We will compare its value in x=1.0 with results obtained from such fit.
    //
    //rho = .10;
    spline1dfit(x, y, 50, rho, s, rep);   
    printf("test2");
    v = spline1dcalc(s, 0.0);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.1);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.2);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.3);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.4);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.5);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.6);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.7);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.8);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 0.9);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.1);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.2);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.3);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.4);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.5);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.6);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.7);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.8);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 1.9);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10
    v = spline1dcalc(s, 2);
    printf("%.1f\n", double(v)); // EXPECTED: 0.10

    return 0;
}