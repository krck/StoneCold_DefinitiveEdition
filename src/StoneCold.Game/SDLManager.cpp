
#include "SDLManager.hpp"

using namespace StoneCold::Base;
using namespace StoneCold::Game;

//
// Initializes the SDL Ressources and 
// creats/show the application Window
//
bool SDLManager::InitializeSDL(const std::string& windowName) {
	try {
		_windowName = windowName;

		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw GameException("SDL Error on init: " + std::string(SDL_GetError()));

		// Set SDL Hint for Texture filtering
		// 0 = Nearest, 1 = Linear, 2 = Anisotropic
		// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

		CreateWindow();
		SetupSDL();
		SetupSubsystems();

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}


//
// Create and Show the application Window
//
void SDLManager::CreateWindow() {
	// Create and Show the main Window
	const uint32 pos = SDL_WINDOWPOS_CENTERED;
	const uint32 flags = 0;

	auto tmpWin = std::unique_ptr<SDL_Window, SDL_WindowDeleter>(SDL_CreateWindow(_windowName.c_str(), pos, pos, WINDOW_WIDTH, WINDOW_HEIGHT, flags));
	_window.swap(tmpWin);

	// Set the min. Window size, if creation was successful 
	if (_window != nullptr)
		SDL_SetWindowMinimumSize(_window.get(), WINDOW_WIDTH, WINDOW_HEIGHT);
	else
		throw GameException("SDL Error on window creation: " + std::string(SDL_GetError()));
}


//
// Create the SDL2 Renderer
//
void SDLManager::SetupSDL() {
	// Create the Renderer to draw within the Window (-1 for default Window driver)
	auto flags = (SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	auto tmpRend = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>(SDL_CreateRenderer(_window.get(), -1, flags));
	_renderer.swap(tmpRend);

	if (_renderer == nullptr)
		throw GameException("SDL Error on renderer creation: " + std::string(SDL_GetError()));
}


//
// Initialize the SDL_image and SDL_ttf Subsystems
//
void SDLManager::SetupSubsystems() {
	// Initialize SDL_image with support for the JPG and PNG image formats
	int flags = (IMG_INIT_JPG | IMG_INIT_PNG);
	if ((IMG_Init(flags) & flags) != flags)
		throw GameException("SDL_Image Error on init: " + std::string(IMG_GetError()));

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
		throw GameException("SDL_ttf Error on init: " + std::string(TTF_GetError()));
}


//
// Cleanup all the SDL2 Ressources
// (even smart-pointers, because the order is important)
// 
SDLManager::~SDLManager() {
	_renderer.reset();
	_window.reset();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
