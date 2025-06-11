#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "domkrat3d/informatics/core.hpp"
#include "domkrat3d/mathematics/core.hpp"
#include "domkrat3d/physics/kinematics.hpp"

auto main() -> int {
    double speed = 10.0;
    double time = 5.0;

    double path = physics::kinematics::calculate_path(speed, time);
    speed = physics::kinematics::calculate_speed(path, time);
    time = physics::kinematics::calculate_time(path, speed);

    std::cout << "Data: speed=" << speed << "m/s" << "; time=" << time << "s"
              << "; path=" << path << "m" << '\n';

    double const final_velocity = physics::kinematics::calculate_final_velocity(10.0, 10.0, 10.0);
    std::cout << "final velocity (10.0, 10.0, 10.0) = " << final_velocity << '\n';

    assert(final_velocity == 110);

    double const final_position = physics::kinematics::calculate_final_position(10.0, 10.0, 10.0, 10.0);
    std::cout << "final position (10.0, 10.0, 10.0, 10.0) = " << final_velocity << '\n';

    assert(final_position == 110);

    std::cout << "-10 number module: " << mathematics::intabs(-10) << '\n';

    assert(mathematics::intabs(-10) == 10);

    int const decimal_number = 777;

    std::string binary_number = computerscience::convert_decimal_to_binary(decimal_number);
    assert(computerscience::convert_decimal_to_binary(decimal_number) == "1100001001");

    int const decimal_number2 = computerscience::convert_binary_to_decimal(binary_number);
    assert(computerscience::convert_binary_to_decimal(binary_number) == decimal_number);

    std::string hexadecimal_number = computerscience::convert_decimal_to_hexadecimal(decimal_number);
    assert(hexadecimal_number == "309");

    int const decimal_number3 = computerscience::convert_hexadecimal_to_decimal(hexadecimal_number);
    assert(decimal_number2 == 777);

    std::string const hexadecimal_number2 = computerscience::convert_binary_to_hexadecimal(binary_number);
    assert(hexadecimal_number2 == "309");

    std::string const binary_number2 = computerscience::convert_hexadecimal_to_binary(hexadecimal_number);
    assert(binary_number2 == "1100001001");

    const int bytes = 1024 * 1024;
    assert(computerscience::humanize_bytes_size(bytes, "B") == "1.0MB");

    std::cout << "Convert decimal " << decimal_number << " to binary: " << binary_number << '\n';
    std::cout << "Convert binary " << binary_number << " to decimal: " << decimal_number2 << '\n';
    std::cout << "Convert decimal " << decimal_number << " to hexadecimal: " << hexadecimal_number << '\n';
    std::cout << "Convert hexadecimal " << hexadecimal_number << " to decimal: " << decimal_number3 << '\n';
    std::cout << "Convert binary " << binary_number << " to hexadecimal: " << hexadecimal_number2 << '\n';
    std::cout << "Convert hexadecimal " << hexadecimal_number << " to binary: " << binary_number2 << '\n';
    std::cout << "Convert " << bytes << ": " << computerscience::humanize_bytes_size(bytes, "B") << '\n';

    return 0;
}
