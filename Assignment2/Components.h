#pragma once

#include "Vec2.h"
#include "Render/Graphics.h"

class CTransform
{
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	float angle = 0;

	CTransform(const Vec2 & p, const Vec2 & v, float a)
		: pos(p), velocity(v), angle(a)
	{}
};

class CShape
{
public:
	std::unique_ptr<RenderEngine::Mesh> ptr_Mesh; //no default constructor, use this instead. Otherwise, fix this by create default constructor and assign operator
	CShape(float radius, int points, const Color & fill, const Color &outline, float thickness) 
	{
		ptr_Mesh = std::make_unique<RenderEngine::Mesh>(radius, points);
		ptr_Mesh->setColor(fill);
		ptr_Mesh->setBorderThick(thickness);
		ptr_Mesh->setBorderColor(outline);
	}
};

class CCollision
{
public:
	float radius = 0;
	CCollision(float r):radius(r){}
};

class CScore
{
public:
	int score = 0;
	CScore(int s):score(s){}
};

class CLifespan
{
public:
	int remaining = 0;
	int total = 0;
	CLifespan(int total):remaining(total), total(total){}
};

class CInput
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput(){}
};
