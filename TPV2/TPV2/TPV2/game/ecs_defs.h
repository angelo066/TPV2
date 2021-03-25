// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class ShowAtOpposieSide;
class AsteroidManager;
class DeAcceleration;
class CollideBounds;
class DisableOnExit;
class FighterCtrl;
class Generations;
class FrameImage;
class Transform;
class Rectangle;
class GameCtrl;
class Follow;
class Rotate;
class Health;
class State;
class Image;
class Gun;
class CollisionsManager;

#define _CMPS_LIST_  \
	ShowAtOpposieSide,\
	CollisionsManager,\
	AsteroidManager,\
	DeAcceleration,\
	CollideBounds,\
	DisableOnExit,\
	FighterCtrl,\
	FrameImage,\
	Generations,\
	Transform,\
	Rectangle,\
	GameCtrl,\
	Follow,\
	Rotate,\
	Health,\
	Image,\
	State,\
	Gun

// groups

struct Bullet_grp;
struct Asteroid_grp;
#define _GRPS_LIST_  Bullet_grp,\
Asteroid_grp

// handlers
struct Player;
#define _HDLRS_LIST_ Player
