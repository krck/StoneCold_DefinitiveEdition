
#ifndef STONECOLD_DATAANIMATIONS_H
#define STONECOLD_DATAANIMATIONS_H

#include "Types.hpp"
#include "AnimationResource.hpp"

//
// ANIMATIONS DATA
//
// Data that corresponds to a specific Texture
// to define all the frames within that Image
//
namespace StoneCold::Resources::Raw {

using namespace StoneCold::Base;
using namespace StoneCold::Resources;

//
// Player Animations
// Names and "src rect" frames within the Player Texture
//
static const auto PLAYER_ANIMATION_FRAMES = std::unordered_map<std::string, Animation>({
	{"idle", Animation({ {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32} }, 180) },
	{"walk", Animation({ {0,32,32,32}, {32,32,32,32}, {64,32,32,32}, {96,32,32,32}, {128,32,32,32}, {160,32,32,32}, {192,32,32,32}, {224,32,32,32} }, 80) },
	{"atk2", Animation({ {0,64,32,32}, {32,64,32,32}, {64,64,32,32}, {96,64,32,32}, {128,64,32,32}, {160,64,32,32}, {192,64,32,32} }, 100) },
	{"atk1", Animation({ {0,96,32,32}, {32,96,32,32}, {64,96,32,32}, {96,96,32,32}, {128,96,32,32}, {160,96,32,32} }, 100) },
	{"atk3", Animation({ {0,128,32,32}, {32,128,32,32} }, 100) },
	{"jump", Animation({ {0,160,32,32}, {32,160,32,32}, {64,160,32,32}, {96,160,32,32}, {128,160,32,32} }, 100) },
	{"hurt", Animation({ {0,192,32,32}, {32,192,32,32}, {64,192,32,32}, {96,192,32,32} }, 100) },
	{"dead", Animation({ {0,224,32,32}, {32,224,32,32}, {64,224,32,32}, {96,224,32,32}, {128,224,32,32}, {160,224,32,32}, {192,224,32,32} }, 100) }
	});

//
// Skeleton Animations
// Names and "src rect" frames within the Skeleton Texture
//
static const auto SKELETON_ANIMATION_FRAMES = std::unordered_map<std::string, Animation>({
	{"idle", Animation({ {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32}, {160,0,32,32}, {192,0,32,32}, {224,0,32,32}, {256,0,32,32}, {288,0,32,32}, {320,0,32,32} }, 180) },
	{"walk", Animation({ {0,32,32,32}, }, 80) },
	{"atk1", Animation({ {0,64,32,32}, }, 100) },
	{"hurt", Animation({ {0,192,32,32}, }, 100) },
	{"reac", Animation({ {0,128,32,32}, }, 100) },
	{"dead", Animation({ {0,224,32,32}, }, 100) }
	});

//
// Button Animations
// Names and "src rect" frames within the GUI Texture
//
static const auto BUTTON_ANIMATION_FRAMES = std::unordered_map<std::string, Animation>({
	{"idle", Animation({ {0,0,200,50} }, 0) },
	{"hover", Animation({ {0,50,200,50} }, 0) }
	});

//
// Map Frames
// TileType mapping and "src rect" frames within any of the Map Textures (some need to be flipped as well)
//
static const auto MAP_TILE_FRAMES = std::unordered_map<MapTileTypes, std::pair<SDL_Rect, SDL_RendererFlip>>({
	{ MapTileTypes::Wall_Top,				{ {0,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Corner_Top_Left,		{ {32,0,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{ MapTileTypes::Corner_Top_Right,		{ {32,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Middle_Block_Vertical,	{ {64,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Endblock_Top,			{ {96,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Portal,					{ {128,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Top_Special,			{ {0,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Wall_Left,				{ {32,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Wall_Right,				{ {32,32,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{ MapTileTypes::Middle_Block_Horizontal,{ {64,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Endblock_Bottom,		{ {96,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Special_3,		{ {128,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Wall_Bottom,			{ {0,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Corner_Bottom_Left,		{ {32,64,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{ MapTileTypes::Corner_Bottom_Right,	{ {32,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Special_2,		{ {64,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Endblock_Left,			{ {96,64,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{ MapTileTypes::Endblock_Right,			{ {96,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Top_Default,			{ {128,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Shadow,			{ {0,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Special_4,		{ {32,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Default,			{ {64,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{ MapTileTypes::Floor_Special_1,		{ {96,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } }
	});

}

#endif
