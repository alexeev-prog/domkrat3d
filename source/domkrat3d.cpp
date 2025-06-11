#include <string>

#include "domkrat3d/domkrat3d.hpp"

exported_class::exported_class()
	: m_name {"domkrat3d"} {}

auto exported_class::name() const -> char const* {
	return m_name.c_str();
}
