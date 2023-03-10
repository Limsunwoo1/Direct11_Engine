#include "CInput.h"
#include "CApplication.h"


	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'K',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		//		//Special Key
		//ENTER, ESC, LSHIFT, LALT, LCTRL,
		//SPACE, LEFT, RIGHT, UP, DOWN,
		//LBTN, RBTN,

		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		////Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,


		////Num Line
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	};

	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	void Input::Initialize()
	{
		for (int i = 0; i < (UINT)eKeyCode::End; i++)
		{
			// 나의 키 종류
			// eKeyCode KeyCode;
			// 키보드 상태
			// eKeyState state;
			// bool bPressed;

			Key key;
			key.keyCode = (eKeyCode)i;
			key.state = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		// 마우스가 현재 window 창을 선택하였는지 체크
		if (GetFocus()) 
		{
			// 키보드
			for (UINT i = 0; i < (UINT)eKeyCode::End; i++)
			{
				// 해당키가 현재 눌려져 있는경우
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에 눌려져 있었다
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::PRESSED;
					else
						mKeys[i].state = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				// 해당키가 눌려져 있지 않은 경우
				else
				{
					// 이전 프레임에 눌려져 있었다
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::UP;
					else
						mKeys[i].state = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}
		}

		POINT mousePos = {};

		// 현재 마우스 좌표를 받아옴
		GetCursorPos(&mousePos);

		// 마우스 포지션을 클라이언트 창에 맞춤
		/*HWND hwnd = Application::GetInstance().GetWindowData().hWnd;
		ScreenToClient(hwnd, &mousePos);*/


		mMousePos.x = (float)mousePos.x;
		mMousePos.y = (float)mousePos.y;
	}

	void Input::Render(HDC hdc)
	{

	}

	eKeyState Input::GetkeyState(eKeyCode keyCode)
	{
		return mKeys[(UINT)keyCode].state;
	}
	Math::Vector2 Input::GetMousePos(HWND hWnd)
	{
		Math::Vector2 vMousePos(-1.0f, -1.0f);
		if (GetFocus())
		{
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);
			vMousePos.x = (float)mousePos.x;
			vMousePos.y = (float)mousePos.y;

			return vMousePos;
		}

		return vMousePos;
	}

