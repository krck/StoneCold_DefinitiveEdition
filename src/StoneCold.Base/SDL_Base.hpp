
#ifndef STONECOLD_SDLBASE_H
#define STONECOLD_SDLBASE_H

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <memory>

namespace StoneCold::Base {

// Custom deleter functions (struct) for unique pointers to cleanup the SDL Resources 
struct SDL_WindowDeleter { void operator()(SDL_Window* p) { if (p != nullptr) SDL_DestroyWindow(p); } };
struct SDL_RendererDeleter { void operator()(SDL_Renderer* p) { if (p != nullptr) SDL_DestroyRenderer(p); } };
struct SDL_TextureDeleter { void operator()(SDL_Texture* p) { if (p != nullptr) SDL_DestroyTexture(p); } };
struct SDL_FontDeleter { void operator()(TTF_Font* p) { if (p != nullptr) TTF_CloseFont(p); } };

// Custom deleter functions (static) for shared pointers to cleanup the SDL Resources 
static void SDL_Deleter(SDL_Texture* p) { if (p != nullptr) SDL_DestroyTexture(p); }

template <typename T>
std::shared_ptr<T> sdl_make_shared(T* t) { return std::shared_ptr<T>(t, [](T* t) { SDL_Deleter(t); }); }

}

#endif
