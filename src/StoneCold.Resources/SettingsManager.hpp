
#ifndef STONECOLD_RES_SETTINGSMANAGER_H
#define STONECOLD_RES_SETTINGSMANAGER_H

#include <string>
#include <unordered_map>
#include <SSARCandy_ini.h>
#include "Exception.hpp"

namespace StoneCold::Resources {

class SettingsManager {
public:
	SettingsManager() : _defaultSettings() { }
	SettingsManager(const SettingsManager&) = delete;
	SettingsManager& operator=(const SettingsManager&) = delete;

	bool Initialize(const std::string& basePath);

	inline std::string Get(const std::string& section, const std::string& key) const { return _defaultSettings.at(section + "-" + key); }
	inline int GetInt(const std::string& section, const std::string& key) const { return std::stoi(_defaultSettings.at(section + "-" + key)); }
	inline float GetFloat(const std::string& section, const std::string& key) const { return std::stof(_defaultSettings.at(section + "-" + key)); }
	bool GetBool(const std::string& section, const std::string& key) const 
	{ 
		auto res = _defaultSettings.at(section + "-" + key);
		return (res == "true" || res == "1"); 
	}

	~SettingsManager() = default;

private:
	std::unordered_map<std::string, std::string> _defaultSettings;
};

}

#endif
