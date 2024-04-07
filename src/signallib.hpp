#include "kromblast_api.hpp"
#include "kromblast_lib_plugin.hpp"
#include "kromblast_lib_plugin_callback.hpp"

class SignalLib : public Kromblast::Class::KromLib
{
private:
    Kromblast::Api::KromblastInterface *kromblast;

public:
    std::string get_version();

    void set_kromblast(void *kromblast);

    std::string send_signal(Kromblast::Core::kromblast_callback_called_t *parameters);

    void load_functions();
};