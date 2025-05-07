#include <cmath>
#include <iostream>

#include "domkrat3d/physics/kinematics.hpp"
#include "domkrat3d/graphics/core.hpp"

auto main() -> int {
	initializeWindow(800, 600, "hello");

	printf("domkrat3d");

	double speed = 10.0;
	double time = 5.0;

	double path = physics::kinematics::calculate_path(speed, time);
	speed = physics::kinematics::calculate_speed(path, time);
	time = physics::kinematics::calculate_time(path, speed);

	std::cout << "Data: speed=" << speed << "m/s" << "; time=" << time << "s"
			  << "; path=" << path << "m" << '\n';

	double const final_velocity = physics::kinematics::calculate_final_velocity(10.0, 10.0, 10.0);
	std::cout << "final velocity (10.0, 10.0, 10.0) = " << final_velocity
			  << '\n';

	double const final_position = physics::kinematics::calculate_final_position(10.0, 10.0, 10.0, 10.0);
	std::cout << "final position (10.0, 10.0, 10.0, 10.0) = " << final_velocity
			  << '\n';

	return 0;
}
