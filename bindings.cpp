#include "libs/grinders/grinders.hpp"
#include "libs/utility/utility.hpp"

#include <sstream>
#include <string>

#include <emscripten/bind.h>
using namespace emscripten;

std::string grinders_string()
{
  std::stringstream ss;
  for (auto i : supported_grinders()) {
    ss << i << ',';
  }
  auto ret = ss.str();
  return { ret.begin(), ret.end() - 1 };
}

EMSCRIPTEN_BINDINGS(clicks)
{
  function("coma_separated_grinders", &grinders_string);
  function("convert_setting", &convert_setting_id);
}
