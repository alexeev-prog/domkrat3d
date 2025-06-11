#include <cstdlib>
#include <ctime>

#include "domkrat3d/utils/random.hpp"

#include "domkrat3d/tracelogger.hpp"

auto generate_random_float() -> float {
    LOG_TRACE
    std::srand(static_cast<unsigned int>(std::time(0)));
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
