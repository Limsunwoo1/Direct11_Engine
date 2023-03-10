#pragma once
#include "CComponent.h"
#include "CAnimation.h"

using namespace std;
using namespace Math;

class Animator : public Component
{
public:
	struct Events
	{
		struct Event
		{
			void operator= (std::function<void()>func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};
		Event mStarteEvent;
		Event mCompleteEvent;
		Event mEndEvent;
	};

	Animator();
	virtual ~Animator();

	virtual void Initalize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

	bool Create(const wstring& name, shared_ptr<Texture2D> atlas, Vector2 leftTop
					, Vector2 size, Vector2 offset
					, UINT spriteLength, float duation);

	Animation* FindAnimation(const wstring& name);
	Events* FindEvents(const wstring& name);
	void Play(const wstring& name, bool loop = true);

	void Binds();
	void Clear();

	function<void()>& GetStartEvent(const wstring& name);
	function<void()>& GetCompleteEvent(const wstring& name);
	function<void()>& GetEndEvent(const wstring& name);
private:
	map<wstring, Animation*> mAnimations;
	map<wstring, Events*> mEvents;
	Animation* mActiveAnimation;
	bool mbLoop;
};