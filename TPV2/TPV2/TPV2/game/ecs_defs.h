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
	Follow

// groups

struct Bullet_grp;
#define _GRPS_LIST_  Bullet_grp

// handlers
struct Hdlr_1;
#define _HDLRS_LIST_ Hdlr_1
