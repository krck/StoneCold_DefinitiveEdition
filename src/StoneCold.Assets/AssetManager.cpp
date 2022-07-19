
#include "AssetManager.hpp"

using namespace StoneCold::Common;
using namespace StoneCold::Assets;

bool AssetManager::Initialize(const std::string& basePath) {
	try {
        _assetPath = (basePath + "\\assets");
        _configPath = (basePath + "\\config");

        // Read the Settings .json file and Assets .json file (easy ifstream >> syntax)
        (std::ifstream { _configPath + "\\sc_settings.json" }) >> _settingsJson;
		(std::ifstream { _configPath + "\\sc_sprites.json" }) >> _spritesJson;
        (std::ifstream { _configPath + "\\sc_assets.json" }) >> _assetsJson;

		// Load all Textures and Fonts (COULD DO THIS ASYNC)
		for(const auto& item : _assetsJson["textures"].items())
			AddTexture(item.value()["name"].get<std::string>(), item.value()["path"].get<std::string>());
		for(const auto& item : _assetsJson["fonts"].items())
			AddFont(item.value()["name"].get<std::string>(), item.value()["path"].get<std::string>());

		return true;
	}
	catch (const std::exception& ex) {
		throw ex;
	}
}

void AssetManager::AddFont(const std::string& assetName, const std::string& path) {
	if(_assets.find(assetName) != _assets.end())
		return;

	sf::Font tmpFont;
	if (!tmpFont.loadFromFile(_assetPath + path))
		throw GameException("Font could not be loaded: " + path);

	_assets[assetName] = std::make_shared<ScAssetFont>(ScAssetFont(assetName, std::move(tmpFont)));
}

void AssetManager::AddTexture(const std::string& assetName, const std::string& path) {
	if(_assets.find(assetName) != _assets.end())
		return;

	sf::Texture tmpTex;
	if (!tmpTex.loadFromFile(_assetPath + path))
		throw GameException("Texture could not be loaded: " + path);

	_assets[assetName] = std::make_shared<ScAssetTexture>(ScAssetTexture(assetName, std::move(tmpTex)));
}

void AssetManager::AddSpriteAnimated(const std::string& assetName, const std::string& sprite) {
	if(_assets.find(assetName) != _assets.end())
		return;

	auto animationIter = _spritesJson["animatedSprites"].find(sprite);
	if(animationIter == _spritesJson["animatedSprites"].end())
		throw GameException("Animation could not be loaded: " + sprite);

	auto animationConfig = _spritesJson["animatedSprites"][sprite];
	// Extract the animation values from the json config
	auto textureName = animationConfig["textureName"].get<std::string>();
	auto frameSize = sf::Vector2i(animationConfig["frameWidth"].get<int>(), animationConfig["frameHeight"].get<int>());
	auto defaultAnim = animationConfig["defaultAnimation"].get<std::string>();
	std::vector<AssetAnimation> animationData;
	for(const auto& item : animationConfig["animations"].items()) {
		AssetAnimation aTmp {
			item.value()["name"].get<std::string>(),
			item.value()["frameSpeed"].get<scUint16>(),
			item.value()["frameCount"].get<scUint16>(),
			item.value()["yOffset"].get<scUint16>()
		};
		animationData.push_back(aTmp);
	}

	// Add the Sprite to the cache
	auto tmpAsset = ScAssetSpriteAnimated(assetName, GetTexture(textureName), animationData, defaultAnim, frameSize);
	_assets.insert({ assetName, std::make_shared<ScAssetSpriteAnimated>(tmpAsset) });
}

void AssetManager::AddSpriteStatic(const std::string& assetName, const std::string& sprite) {
	if(_assets.find(assetName) != _assets.end())
		return;

	auto animationIter = _spritesJson["staticSprites"].find(sprite);
	if(animationIter == _spritesJson["staticSprites"].end())
		throw GameException("Animation could not be loaded: " + sprite);

	auto animationConfig = _spritesJson["staticSprites"][sprite];
	// Extract the animation values from the json config
	auto textureName = animationConfig["textureName"].get<std::string>();
	auto frameSize = sf::Vector2i(animationConfig["frameWidth"].get<int>(), animationConfig["frameHeight"].get<int>());

	// Add the Sprite to the cache
	auto tmpAsset = ScAssetSpriteStatic(assetName, GetTexture(textureName), frameSize);
	_assets.insert({ assetName, std::make_shared<ScAssetSpriteStatic>(tmpAsset) });
}

void AssetManager::AddSpriteStatic(const std::string& assetName, sf::Texture&& texture, const sf::Vector2i& frameSize) {
	// Hard overwrite any Sprite/Texture with the same name
	// (This is mostly going to be used for the Level Map, and that data can be discarted/overwritten as soon as the level ends anyway)
	_assets[assetName + "_TEX"] = std::make_shared<ScAssetTexture>(ScAssetTexture(assetName, std::move(texture)));
	_assets[assetName] = std::make_shared<ScAssetSpriteStatic>(ScAssetSpriteStatic(assetName, GetTexture(assetName + "_TEX"), frameSize));
}

bool AssetManager::RemoveAsset(const std::string& name) {
	return (_assets.find(name) != _assets.end())
		   ? _assets.erase(name)
		   : false;
}
