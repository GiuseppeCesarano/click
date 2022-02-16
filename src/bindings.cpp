#include <emscripten/bind.h>
#include <grinders/grinders.hpp>

EMSCRIPTEN_BINDINGS(clicks)
{
  emscripten::function("convert_setting", &convert_setting_id);
  emscripten::function("default_setting", &default_setting_id);
}
