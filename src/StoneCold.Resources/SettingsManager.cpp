
#include "SettingsManager.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Resources;

//
// Initializes the SettingsManager and 
// load the default "sc_settings.ini" file
//
bool SettingsManager::Initialize(const std::string& basePath) {
	try {
        // Read the default "sc_settings.ini" file (and try-get the "window_name" as a test)
        inih::INIReader settingsIni {(basePath + "\\config\\sc_settings.ini")};
        const auto& windowName = settingsIni.Get<std::string>("window", "window_name");
        if(windowName.empty() || windowName == "")
            throw GameException("settings .ini not loaded or invalid");

        // Transform all .ini settings into one, flat map
        for(const auto& section : settingsIni.Sections()) {
            for(const auto& key : settingsIni.Keys(section)) {
                _defaultSettings.insert({ (section + "-" + key), settingsIni.Get<std::string>(section, key) });
            }
        }

		return true;
	}
	catch (const std::exception& ex) {
		throw ex;
	}
}
