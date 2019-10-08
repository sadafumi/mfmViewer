#ifndef _INPUTX_H_
#define _INPUTX_H_

#include "DrawData.h"


//‚±‚Ì’è‹`‚ð”»’è‚·‚é
//XINPUT_GAMEPAD_DPAD_UP
//XINPUT_GAMEPAD_DPAD_DOWN
//XINPUT_GAMEPAD_DPAD_LEFT
//XINPUT_GAMEPAD_DPAD_RIGHT
//XINPUT_GAMEPAD_START
//XINPUT_GAMEPAD_BACK
//XINPUT_GAMEPAD_LEFT_THUMB
//XINPUT_GAMEPAD_RIGHT_THUMB
//XINPUT_GAMEPAD_LEFT_SHOULDER
//XINPUT_GAMEPAD_RIGHT_SHOULDER
//XINPUT_GAMEPAD_A
//XINPUT_GAMEPAD_B
//XINPUT_GAMEPAD_X
//XINPUT_GAMEPAD_Y

class Controller
{
public:
	Controller();
	~Controller();
	void Updata();
	bool GetPressButton(int indef);
	bool GetTriggerButton(int indef);
	bool GetReleaseButton(int indef);
	D3DXVECTOR2 GetAnalogStickR();
	D3DXVECTOR2 GetAnalogStickL();
	int GetTriggerR();
	int GetTriggerL();
	int GetControlNumber();
	void ChangeControllerActive(bool);
private:
	XINPUT_STATE	state;
	XINPUT_STATE	Oldstate;
	bool			bController;
	int				nControllerNum;
};

#endif // _INPUTX_H_
