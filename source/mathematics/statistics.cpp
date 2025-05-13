#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

#include "domkrat3d/mathematics/statistics.hpp"
#include "domkrat3d/tracelogger.hpp"

namespace mathematics::statistics {
	auto get_average(const double numbers[], int length) -> double {
		LOG_TRACE
		double sum = 0;

		for (int i = 0; i < length; i++) {
			sum += numbers[i];
		}

		return sum / length;
	}

	auto factorial(size_t n) -> size_t {
		LOG_TRACE

		if (n == 0) {
			return 1;
		}
		return n * factorial(n - 1);
	}

	auto combinations(size_t n, size_t k) -> size_t {
		LOG_TRACE

		return factorial(n) / (factorial(k) * factorial(n - k));
	}

	auto median(std::vector<double> data) -> double {
		LOG_TRACE

		std::sort(data.begin(), data.end());
		const size_t size = data.size();
		if (size % 2 == 0) {
			return (data[size / 2 - 1] + data[size / 2]) / 2.0;
		}
		return data[size / 2];
	}

	auto probability(size_t favorable_outcomes, size_t total_outcomes) -> double {
		LOG_TRACE

		return static_cast<double>(favorable_outcomes) / total_outcomes;
	}

	auto conditional_probability(size_t a_and_b, size_t b) -> double {
		LOG_TRACE
		
		return static_cast<double>(a_and_b) / b;
	}
}	 // namespace mathematics::statistics
