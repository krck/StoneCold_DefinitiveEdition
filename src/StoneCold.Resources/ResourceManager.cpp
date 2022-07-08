
#include "ResourceManager.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Resources;

ResourceManager::ResourceManager()
	: _resources(std::unordered_map<std::string, std::shared_ptr<Resource>>())
	, _resouceLifetimes(std::unordered_map<ResourceLifeTime, std::vector<std::string>>()) { }

bool ResourceManager::Initialize(const std::string& basePath) {
	try {
		_basePath = basePath;
		return true;
	}
	catch (const std::exception& ex) {
		throw ex;
	}
}

template<typename T>
T* ResourceManager::LoadExternalResource(ResourceLifeTime resourceLifeTime, const std::string& name) {
	try {
		if(_resouceLifetimes.find(resourceLifeTime) == _resources.end())
			_resouceLifetimes.insert({ resourceLifeTime, std::vector<std::string>() });

		// Load each ressource only once
		if (!IsResourceLoaded(name)) {
			if (std::is_same<T, TextureResource>::value) {
				// Create a Texture Resource, loaded from a File (.png or .jpg)
				_resources.insert({ name, std::make_shared<TextureResource>(CreateTexture(name)) });
				_resouceLifetimes[resourceLifeTime].push_back(name);
			}
			else if (std::is_same<T, FontResource>::value) {
				// Create a Font Resource loaded from a File (.ttf)
				_resources.insert({ name, std::make_shared<FontResource>(CreateFont(name)) });
				_resouceLifetimes[resourceLifeTime].push_back(name);
			}
		}
		return static_cast<T*>(_resources[name].get());
	}
	catch (const std::exception& ex) {
		throw ex;
	}
}

void ResourceManager::UnloadExternalResources(ResourceLifeTime resourceLifeTime) {
	// Remove all Resources that are mapped to the specific lifetime
	const auto& keys = _resouceLifetimes[resourceLifeTime];
	for (const auto& key : keys) {
		_resources.erase(key);
	}

	// Clear all ResourceLifeTime keys
	_resouceLifetimes[resourceLifeTime] = std::vector<std::string>();
}

//
// Explicitly instanciate every form of LoadExternalResource
// This has two upsides:
// - .hpp will not get cluttered with function definitions
// - There are not many Resource-Types so its easy to provide a concrete interface
//
//template TextureResource* ResourceManager::LoadExternalResource<TextureResource>(ResourceLifeTime resourceLifeTime, const std::string& name);
//template FontResource* ResourceManager::LoadExternalResource<FontResource>(ResourceLifeTime resourceLifeTime, const std::string& name);
