// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class FighterCtrl;
class CollideBounds;
class Image;
class Rotate;
class DeAcceleration;
class Gun;
class ShowAtOpposieSide;
class DisableOnExit;
class FrameImage;
class Follow;
class Health;
class AsteroidManager;
class Generations;
class State;

#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	FighterCtrl,\
	CollideBounds,\
	Image,\
	Rotate,\
	DeAcceleration,\
	Gun,\
	ShowAtOpposieSide,\
	FrameImage,\
	DisableOnExit,\
	Follow,\
	AsteroidManager,\
	Generations,\
	Health,\
	State

// groups

struct Bullet_grp;
#define _GRPS_LIST_  Bullet_grp

// handlers
struct Player;
#define _HDLRS_LIST_ Player
