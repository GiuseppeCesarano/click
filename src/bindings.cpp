#include <grinders/grinders.hpp>
#include <utility/utility.hpp>

#include <sstream>
#include <string>

#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(clicks)
{
  function("convert_setting", &convert_setting_id);
}
