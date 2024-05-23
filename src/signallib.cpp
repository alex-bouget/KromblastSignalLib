#include "kromblast_compiler_utils.hpp"
#include "signallib.hpp"
#include "kromblast_api_dispatcher.hpp"
#include "kromblast_api_plugin_utils.hpp"
#include <functional>
#ifdef KROMBLAST_DEBUG
#include <fstream>
#include <sstream>
#else
#define STRINGIFY(x) #x
#endif

std::string SignalLib::get_version()
{
    return "0.2.0";
}

void SignalLib::at_start()
{
}

std::string SignalLib::send_signal(Kromblast::Core::kromblast_callback_called_t *parameters)
{
    kromblast().get_logger()->log("SignalLib", "Signal received");
    Kromblast::Api::Signal signal{"kromlib.core.signal_js." + parameters->args[0], parameters->args[1]};
    kromblast().get_dispatcher()->dispatch(signal);
    return R"({"ok": true})";
}

void SignalLib::load_functions()
{
    Kromblast::Core::kromblast_callback_t callback = {
        "kromblast_signal",
        2,
        std::bind(&SignalLib::send_signal, this, std::placeholders::_1)};
    kromblast().get_plugin()->claim_callback(
        "kromlib.core.signal_js",
        2,
        BIND_CALLBACK(SignalLib::send_signal),
        // Allow all urls
        std::vector<std::regex>{std::regex("^.*$")});
#ifdef KROMBLAST_DEBUG
    std::ifstream file("functions.js");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string inject = buffer.str();
    // Delete STRINGIFY() macro
    inject = inject.substr(10, inject.size() - 12);
#else
    std::string inject = 
    #include "functions.js"
    ;
#endif
    kromblast().get_logger()->log("SignalLib", inject);
    kromblast().get_window()->init_inject(inject);
}