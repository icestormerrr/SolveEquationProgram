#include <clocale>
#include <iostream>
#include <cmath>


double f(double x) {
	return x * x * x + 3.4136 * x + 2;
}


double fPrime(double x) {
	return 3 * x * x + 3.4136;
}

double fPrimePrime(double x) {
	return 6 * x;
}


int main() {
	setlocale(LC_ALL, "Russian");

	double xStart = -1.0;
	double xEnd = -0.0;

	double epsilon = 0.001;


	if (f(xStart) * f(xEnd) > 0) {
		return -1;
	}

	double xCenter;
	double xCenterPrevious;
	double fCenter;

	int iteration = 1;

	int flag = 1;

	while (flag) {
		if (iteration >= 2) {
			xCenterPrevious = xCenter;
		}


		xCenter = (xStart + xEnd) / 2.0;
		fCenter = f(xCenter);


		if (f(xStart) * fCenter < 0) {
			xEnd = xCenter;
		}
		else if (fCenter * f(xEnd) < 0) {
			xStart = xCenter;
		}
		else {
			return -2;
		}

		if (fabs(fCenter) < epsilon) {
			flag = 0;
		}
		if (iteration >= 2) {
			if (fabs(xCenter - xCenterPrevious) < epsilon) {
				flag = 0;
			}
		}

		printf("Iteration number:   %.4d\n", iteration);
		printf("xCenter:   %.4f\n", xCenter);
		printf("fCenter: %.4f\n", fCenter);
		printf("\n");
		iteration++;
	}




	while (flag) {

		double x0;
		double x0Star;
		double x1;

		if (f(xStart) * fPrimePrime(xStart) > 0) {
			x0 = xStart;
			x0Star = xEnd;
		}
		else {
			x0 = xEnd;
			x0Star = xStart;
		}


		double x1Tangent;
		double x1Chord;

		x1Tangent = x0 - f(x0) / fPrime(x0);
		x1Chord = x0Star - (x0 - x0Star) * f(x0Star) / (f(x0) - f(x0Star));


		x1 = (x1Tangent + x1Chord) / 2.0;


		if (fabs(x1Tangent - x1Chord) < 2 * epsilon) {
			flag = 0;
		}
		if (fabs(f(x1)) < epsilon) {
			flag = 0;
		}


		printf("x1Tangent:  %.4f\n", x1Tangent);
		printf("x1Chord:    %.4f\n", x1Chord);
		printf("x1:         %.4f\n", x1);
		printf("f(x1):      %.4f\n", f(x1));
		printf("\n");

		xStart = x1Tangent;
		xEnd = x1Chord;
	}


	return 0;
}