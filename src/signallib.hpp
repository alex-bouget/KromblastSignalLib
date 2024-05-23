#include "kromblast_api.hpp"
#include "kromblast_lib_plugin.hpp"
#include "kromblast_lib_plugin_callback.hpp"

class SignalLib : public Kromblast::Class::KromLib
{
public:
    std::string get_version() override;

    void at_start() override;

    std::string send_signal(Kromblast::Core::kromblast_callback_called_t *parameters);

    void load_functions() override;
};