#include <emscripten/bind.h>
#include <grinders/grinders.hpp>

EMSCRIPTEN_BINDINGS(clicks)
{
  emscripten::function("convert_setting", &convert_setting_id);
}
