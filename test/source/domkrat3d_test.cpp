#include <string>

#include "domkrat3d/domkrat3d.hpp"

auto main() -> int
{
  auto const exported = exported_class {};

  return std::string("domkrat3d") == exported.name() ? 0 : 1;
}
