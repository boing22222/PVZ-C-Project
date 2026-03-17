#pragma once
#include <graphics.h>
class Scene//³¡¾°»ùÀà
{
public:
	Scene() = default;
	~Scene() = default;
	virtual void OnEnter()=0;
	virtual void OnExit()=0;
	virtual void Update(int delta)=0;
	virtual void Draw()=0;
	virtual void Input(const ExMessage& msg)=0;
};

