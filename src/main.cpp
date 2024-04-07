#include <string>
#include "kromblast_lib_plugin.hpp"
#include "signallib.hpp"

extern "C" Kromblast::Class::KromLib *kromblast_lib_get_class()
{
    return (new SignalLib());
}