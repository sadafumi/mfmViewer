#include "Xinput.h"

Controller::Controller()
{
	XInputEnable(true);
}
Controller::~Controller()
{
	XInputEnable(false);
}
void Controller::Updata()
{
	DWORD dwResult;
	memcpy(&this->Oldstate,&this->state,sizeof(XINPUT_STATE));
	dwResult = XInputGetState(this->nControllerNum, &this->state);

	if (dwResult == ERROR_SUCCESS)
	{
		this->bController = true;
	}
	else
	{
		this->bController = false;
	}
}
bool Controller::GetPressButton(int indef)
{
	bool KeyCheck = this->state.Gamepad.wButtons & indef;
	if (KeyCheck && this->bController)
	{
		return true;
	}
	return false;
}
bool Controller::GetTriggerButton(int indef)
{
	bool KeyCheck = this->state.Gamepad.wButtons & indef;
	bool OldKeyCheck = this->Oldstate.Gamepad.wButtons & indef;
	if (KeyCheck && !OldKeyCheck && this->bController)
	{
		return true;
	}
	return false;
}
bool Controller::GetReleaseButton(int indef)
{
	bool KeyCheck = this->state.Gamepad.wButtons & indef;
	bool OldKeyCheck = this->Oldstate.Gamepad.wButtons & indef;
	if (!KeyCheck && OldKeyCheck && this->bController)
	{
		return true;
	}
	return false;
}
D3DXVECTOR2 Controller::GetAnalogStickR()
{
	D3DXVECTOR2 returntrigger;
	returntrigger.x = this->state.Gamepad.sThumbRX;
	returntrigger.y = this->state.Gamepad.sThumbRY;
	if (this->bController)
	{
		return returntrigger;
	}
	returntrigger = D3DXVECTOR2(0.0f, 0.0f);
	return returntrigger;
}
D3DXVECTOR2 Controller::GetAnalogStickL()
{
	D3DXVECTOR2 returntrigger;
	returntrigger.x = this->state.Gamepad.sThumbLX;
	returntrigger.y = this->state.Gamepad.sThumbLY;
	if (this->bController)
	{
		return returntrigger;
	}
	returntrigger = D3DXVECTOR2(0.0f,0.0f);
	return returntrigger; 
}
int Controller::GetTriggerR()
{
	if(this->bController)
	{
		return this->state.Gamepad.bRightTrigger;
	}
	return 0;
}
int Controller::GetTriggerL()
{
	if (this->bController)
	{
		return this->state.Gamepad.bLeftTrigger;
	}
	return 0;
}
int Controller::GetControlNumber()
{
	if (this->bController)
	{
		return this->state.dwPacketNumber;
	}
	return 0;
}
void Controller::ChangeControllerActive(bool In)
{
	this->bController = In;
}