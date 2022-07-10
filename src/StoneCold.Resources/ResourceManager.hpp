
#ifndef STONECOLD_RES_RESOURCEMANAGER_H
#define STONECOLD_RES_RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Enums.hpp"
#include "Resource.hpp"
#include "Exception.hpp"

namespace StoneCold::Resources {

using namespace StoneCold::Core;

//
// ResorceManager to load and unlaod external Resources from the Filesystem
// - Ensures that only one copy of each unique resource exists
// - Manages the lifetime of each resource (loading / unloading)
// - !NOT YET! Handles loading of composite resources (resource dependencies)
//
class ResourceManager {
public:
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	bool Initialize(const std::string& basePath);

	//
	// Load any Resource based on its Type
	// Ensures that Resources are loaded only once
	//
	template<typename T>
	T* LoadExternalResource(ResourceLifeTime resourceLifeTime, const std::string& name);

	//
	// Unload (cleanup) all Resources of a specific LifeTime
	//
	void UnloadExternalResources(ResourceLifeTime resourceLifeTime);

	template<typename T>
	inline T* GetResource(const std::string& name) { return static_cast<T*>(_resources[name].get()); }

	inline bool IsResourceLoaded(const std::string& name) const { return (_resources.find(name) != _resources.end()); }

	~ResourceManager() = default;

private:
	//TextureResource CreateTexture(const std::string& name);
	//AnimationResource CreateAnimation(const std::string& name);
	//FontResource CreateFont(const std::string& name);

private:
	std::string _basePath;
	std::unordered_map<std::string, std::shared_ptr<Resource>> _resources;
	std::unordered_map<ResourceLifeTime, std::vector<std::string>> _resouceLifetimes;
};

}

#endif
