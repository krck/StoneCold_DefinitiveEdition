
#ifndef STONECOLD_SDLMANAGER_H
#define STONECOLD_SDLMANAGER_H

#include "SDL_Base.hpp"
#include "Settings.hpp"
#include "Types.hpp"
#include "Exception.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace StoneCold::Game {

using namespace StoneCold::Base;

class SDLManager {
public:
	SDLManager() : _window(nullptr), _renderer(nullptr) {}
	SDLManager(const SDLManager&) = delete;
	SDLManager& operator=(const SDLManager&) = delete;

	bool InitializeSDL(const std::string& windowName);
	inline SDL_Window* GetSDLWindow() { return _window.get(); }
	inline SDL_Renderer* GetSDLRenderer() { return _renderer.get(); }

	~SDLManager();

private:
	void CreateWindow();
	void SetupSDL();
	void SetupSubsystems();

private:
	std::string _windowName;
	std::unique_ptr<SDL_Window, SDL_WindowDeleter> _window;
	std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> _renderer;
};

}

#endif
