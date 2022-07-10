
#ifndef STONECOLD_ASSETS_ASSETMANAGER_H
#define STONECOLD_ASSETS_ASSETMANAGER_H

#include <string>
#include <memory>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <json.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"
#include "Types.hpp"
#include "Exception.hpp"
#include "AssetTexture.hpp"
#include "AssetSpriteAnimated.hpp"
#include "AssetSpriteStatic.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Core;

//
// ResorceManager to load and unlaod external Resources from the Filesystem
// - Ensures that only one copy of each unique resource exists
// - Manages four basic Assets: Textures, Animations, Sounds and Fonts
// - NO Specific Lifetime checking or Per-Scene-Loading!!
//	 (As long as its reasonable for a this small 2D Game,  ALL Assets will be loaded and kept in memory globally)
//
class AssetManager {
public:
	AssetManager() : _assets(std::unordered_map<std::string, scSptr<Asset>>()) { }
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	bool Initialize(const std::string& basePath);

	inline const nlohmann::json& GetAssetJson() const { return _assetsJson; }
	inline const nlohmann::json& GetSettingsJson() const { return _settingsJson; }

	void AddTexture(const std::string& name, const std::string& path);
	void AddSpriteAnimated(const std::string& assetName, const std::string& sprite);
	void AddSpriteStatic(const std::string& assetName, const std::string& sprite);
	// sf::Sound* LoadSound(const std::string& name);
	// sf::Font* LoadFont(const std::string& name);

	inline const sf::Texture& GetTexture(const std::string& name) const { return static_cast<AssetTexture*>(_assets.at(name).get())->GetTexture(); }
	inline AssetSpriteAnimated* GetSpriteAnimated(const std::string& name) { return  static_cast<AssetSpriteAnimated*>(_assets.at(name).get()); }
	inline AssetSpriteStatic* GetSpriteStatic(const std::string& name) { return  static_cast<AssetSpriteStatic*>(_assets.at(name).get()); }
	// sf::Sound* GetSound(const std::string& name);
	// sf::Font* GetFont(const std::string& name);

	bool RemoveAsset(const std::string& name);

	~AssetManager() = default;

private:
	std::string _assetPath;
	std::string _configPath;
	// Asset cache
	std::unordered_map<std::string, scSptr<Asset>> _assets;
	std::unordered_map<ResourceLifeTime, std::vector<std::string>> _resouceLifetimes;
	// Config files
	nlohmann::json _assetsJson;
	nlohmann::json _settingsJson;
};

}

#endif
