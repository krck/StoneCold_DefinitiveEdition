
#ifndef STONECOLD_DATAOBJECTS_H
#define STONECOLD_DATAOBJECTS_H

#include "Types.hpp"
#include "Settings.hpp"
#include "Vec4.hpp"
#include "Vec2.hpp"

//
// OBJECT DATA
//
namespace StoneCold::Resources::Raw {

using namespace StoneCold::Base;

struct _FullscreenBackground {
	const Vec4i SrcRect = Vec4i(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	const Vec4 DestRect = Vec4(0.f, 0.f, FWINDOW_WIDTH, FWINDOW_HEIGHT);
	const SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE;
};
static const _FullscreenBackground FullscreenBackground;

struct _GUI_Objects {
	const std::string Name;
	const std::string Text;
	// ...
};

}

#endif
