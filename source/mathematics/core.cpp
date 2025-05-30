/**
 * @file
 * @brief Core utils for mathematics
 * @authors alxvdev
 */
#include <cmath>
#include <cstdlib>

#include "domkrat3d/mathematics/core.hpp"

#include "domkrat3d/tracelogger.hpp"

namespace mathematics {

	auto old_approximate_power(double base, double exponent) -> double {
		LOG_TRACE

		union
		{
			double d;
			long long i;
		} u = {base};

		long long const magic_num = 4606853616395542500L;

		u.i = static_cast<long long>(magic_num + (exponent * (u.i - magic_num)));

		return u.d;
	}

	auto binary_power(double base, unsigned long long exponent) -> double {
		LOG_TRACE

		double v = 1.0;

		while (exponent != 0) {
			if ((exponent & 1) != 0) {
				v *= base;
			}

			base *= base;
			exponent >>= 1;
		}

		return v;
	}

	auto fast_power_dividing(double base, double exponent) -> double {
		LOG_TRACE

		if (base == 1.0 || exponent == 0.0) {
			return 1.0;
		}

		double const e_abs = fabs(exponent);
		double const ceil_e = ceil(e_abs);
		double const base_part = old_approximate_power(base, e_abs / ceil_e);
		double const result = binary_power(base_part, static_cast<unsigned long long>(ceil_e));

		if (exponent < 0.0) {
			return 1.0 / result;
		}

		return result;
	}

	auto another_approximate_power(double base, double exponent) -> double {
		LOG_TRACE

		union
		{
			double d;
			int x[2];
		} u = {base};

		const int magic_num = 1072632447;

		u.x[1] = static_cast<int>((exponent * (u.x[1] - magic_num)) + magic_num);
		u.x[0] = 0;

		return u.d;
	}

	auto fast_power_fractional(double base, double exponent) -> double {
		LOG_TRACE

		if (base == 1.0 || exponent == 0.0) {
			return 1.0;
		}

		double const abs_exp = fabs(exponent);
		uint const e_int_part = static_cast<long long>(abs_exp);
		double const e_fract_part = abs_exp - e_int_part;
		double const result = old_approximate_power(base, e_fract_part) * binary_power(base, e_int_part);

		if (exponent < 0.0) {
			return 1.0 / result;
		}

		return result;
	}

	auto add_percent_to_number(double number, double percentage) -> double {
		LOG_TRACE

		double const oneperc = number / 100;
		double const result = number + (oneperc * percentage);

		return result;
	}

	auto square_it_up(double num) -> double {
		LOG_TRACE

		return num * num;
	}

	auto get_square_root(double num) -> double {
		LOG_TRACE

		if (num <= 0) {
			return 0;
		}

		int exp = 0;

		num = frexp(num, &exp);

		if ((exp & 1) != 0) {
			exp--;
			num *= 2;
		}

		double y = (1 + num) / 2;
		double z = 0;

		while (y != z) {
			z = y;
			y = (y + num / y) / 2;
		}

		return ldexp(y, exp / 2);
	}

	auto intabs(int base) -> int {
		LOG_TRACE

		int const minus_flag = base >> 0x1F;

		int result = minus_flag ^ base;

		result -= minus_flag;

		return result;
	}
}	 // namespace mathematics
