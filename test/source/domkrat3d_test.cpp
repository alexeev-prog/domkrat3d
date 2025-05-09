#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "domkrat3d/graphics/core.hpp"
#include "domkrat3d/informatics/core.hpp"
#include "domkrat3d/mathematics/core.hpp"
#include "domkrat3d/physics/kinematics.hpp"

auto main() -> int {
	initialize_window(800, 600, "hello");

	double speed = 10.0;
	double time = 5.0;

	double path = physics::kinematics::calculate_path(speed, time);
	speed = physics::kinematics::calculate_speed(path, time);
	time = physics::kinematics::calculate_time(path, speed);

	std::cout << "Data: speed=" << speed << "m/s" << "; time=" << time << "s"
			  << "; path=" << path << "m" << '\n';

	double const final_velocity = physics::kinematics::calculate_final_velocity(10.0, 10.0, 10.0);
	std::cout << "final velocity (10.0, 10.0, 10.0) = " << final_velocity << '\n';

	double const final_position = physics::kinematics::calculate_final_position(10.0, 10.0, 10.0, 10.0);
	std::cout << "final position (10.0, 10.0, 10.0, 10.0) = " << final_velocity << '\n';

	// POWER / Algorithms for fast exponentiation //

	double const best_pow_val = 100;
	std::array<double, 5> pow_results = {mathematics::old_approximate_power(10.0, 2.0),
										 mathematics::another_approximate_power(10.0, 2.0),
										 mathematics::binary_power(10.0, 2),
										 mathematics::fast_power_dividing(10.0, 2.0),
										 mathematics::fast_power_fractional(10.0, 2.0)};

	std::cout << "0 oldApproximatePower	   : base 10 exponent 2: " << pow_results[0] << '\n';
	std::cout << "1 anotherApproximatePower: base 10 exponent 2: " << pow_results[1] << '\n';
	std::cout << "2 binaryPower			   : base 10 exponent 2: " << pow_results[2] << '\n';
	std::cout << "3 fastPowerDividing	   : base 10 exponent 2: " << pow_results[3] << '\n';
	std::cout << "4 fastPowerFractional	   : base 10 exponent 2: " << pow_results[4] << '\n';

	for (int i = 0; i < sizeof(pow_results) / sizeof(pow_results[0]); i++) {
		double const error = best_pow_val - pow_results[i];

		std::cout << "POW Algorithm #" << i << ": error=" << error << '\n';
	}

	std::cout << '\n';

	std::cout << "-10 number module: " << mathematics::intabs(-10) << '\n';

	int const decimal_number = 777;
	std::string binary_number = computerscience::convert_decimal_to_binary(decimal_number);
	int const decimal_number2 = computerscience::convert_binary_to_decimal(binary_number);
	std::string hexadecimal_number = computerscience::convert_decimal_to_hexadecimal(decimal_number);
	int const decimal_number3 = computerscience::convert_hexadecimal_to_decimal(hexadecimal_number);
	std::string const hexadecimal_number2 = computerscience::convert_binary_to_hexadecimal(binary_number);
	std::string const binary_number2 = computerscience::convert_hexadecimal_to_binary(hexadecimal_number);
	long long const bytes = 1024 * 1024;

	std::cout << "Convert decimal " << decimal_number << " to binary: " << binary_number << '\n';
	std::cout << "Convert binary " << binary_number << " to decimal: " << decimal_number2 << '\n';
	std::cout << "Convert decimal " << decimal_number << " to hexadecimal: " << hexadecimal_number << '\n';
	std::cout << "Convert hexadecimal " << hexadecimal_number << " to decimal: " << decimal_number3 << '\n';
	std::cout << "Convert binary " << binary_number << " to hexadecimal: " << hexadecimal_number2 << '\n';
	std::cout << "Convert hexadecimal " << hexadecimal_number << " to binary: " << binary_number2 << '\n';
	std::cout << "Convert " << bytes << ": " << computerscience::humanize_bytes_size(bytes, "B") << '\n';

	return 0;
}
