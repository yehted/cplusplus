#include "myRandom.h"
#include <stdexcept>
#include <float.h>

myRandom::myRandom() {}

std::mt19937 myRandom::mt_ = myRandom::init();

double myRandom::uniform() {
	std::uniform_real_distribution<double> distribution(0, 1);
	return distribution(mt_);
}

int myRandom::uniform(int N) {
	if (N <= 0) throw std::invalid_argument("Parameter N must be positive");
	std::uniform_int_distribution<int> distribution(0, N - 1);
	return distribution(mt_);
}

// Returns a number from a discrete distribution: i with probability a[i].
int myRandom::discrete(std::vector<double> a) {
	double sum = 0.0;
	for (int i = 0; i < a.size(); i++) {
		if (!(a[i] >= 0.0)) throw std::invalid_argument("array entry must be non-negative");
		sum += a[i];
	}
	if (sum > 1.0 + DBL_EPSILON || sum < 1.0 - DBL_EPSILON)
		throw std::invalid_argument("sum of array entries does not approximately equal 1.0");

	// the for loop may not return a value when both r is (nearly) 1.0 and when the
	// cumulative sum is less than 1.0 (as a result of floating-point roundoff error)
	while (true) {
		double r = uniform();
		sum = 0.0;
		for (int i = 0; i < a.size(); i++) {
			sum += a[i];
			if (sum > r) return i;
		}
	}
}
