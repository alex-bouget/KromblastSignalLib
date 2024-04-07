#include "kromblast_compiler_utils.hpp"
#include "signallib.hpp"
#include "kromblast_api_dispatcher.hpp"
#include <functional>
#ifdef KROMBLAST_DEBUG
#include <fstream>
#include <sstream>
#else
#define STRINGIFY(x) #x
#endif

std::string SignalLib::get_version()
{
    return "0.1.0";
}

void SignalLib::set_kromblast(void *kromblast)
{
    this->kromblast = (Kromblast::Api::KromblastInterface *)kromblast;
}

std::string SignalLib::send_signal(Kromblast::Core::kromblast_callback_called_t *parameters)
{
    kromblast->log("SignalLib", "Signal received");
    Kromblast::Api::Signal signal = {parameters->args[0], parameters->args[1]};
    kromblast->get_dispatcher()->dispatch(signal);
    return "{\"ok\": true}";
}

void SignalLib::load_functions()
{
    Kromblast::Core::kromblast_callback_t callback = {
        "kromblast_signal",
        2,
        std::bind(&SignalLib::send_signal, this, std::placeholders::_1)};
    kromblast->get_plugin()->claim_callback(callback);
#ifdef KROMBLAST_DEBUG
    std::ifstream file("functions.js");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string inject = buffer.str();
#else
    std::string inject = 
    #include "functions.js"
    ;
#endif
    kromblast->log("SignalLib", inject);
    kromblast->get_window()->init_inject(inject);
}