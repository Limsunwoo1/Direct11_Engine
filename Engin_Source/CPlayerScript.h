#pragma once
#include "CScript.h"

using namespace Math;
class PlayerScript : public Script
{
public:
	PlayerScript();
	virtual ~PlayerScript();

	virtual void Initalize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

	
private:
	Vector3 mArrivePos;
	bool mbRun;
};

