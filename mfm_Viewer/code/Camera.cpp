#include "Camera.h"

D3DXMATRIX Camera::mtxView;
D3DXVECTOR3 Camera::Pos;
D3DXVECTOR3 Camera::Vec;

D3DXVECTOR3 Camera::GetPos()
{
	return Pos;
}

D3DXVECTOR3 Camera::GetVec()
{
	return Vec;
}

void Camera::Updata()
{
	static float fRootX = 0.0f;
	static float fRootY = 0.0f;
	static float fCamPosX = 10.0f;
	static float fCamPosY = 5.0f;
	static float fCamPosZ = -5.0f;

	D3DXMATRIX rotAc;
	D3DXMATRIX rotY;

	static D3DXVECTOR3 ueVector(0.0f, 1.0f, 0.0f);
	static D3DXVECTOR3 maeVector(0.0f, 0.0f, 1.0f);
	static D3DXVECTOR3 migiVector(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 migiVectorRev(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 maeVectorRev(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 Vector;
	static D3DXVECTOR3 VectorRev;

	//カメラ座標
	static D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	//注視点
	static D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//カメラの向き
	static D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//カメラのベクトル
	//D3DXVECTOR3 Vector = (at - eye);
	//maeVector = (at - eye);
	Vector = (eye - at);
	VectorRev = (at - eye);
	maeVectorRev = (at - eye);
	maeVector = (eye - at);
	D3DXVec3Cross(&migiVector, &maeVector, &ueVector);
	D3DXVec3Normalize(&maeVector, &maeVector);
	D3DXVec3Normalize(&migiVector, &migiVector);
	D3DXVec3Cross(&migiVectorRev, &maeVectorRev, &ueVector);
	D3DXVec3Normalize(&maeVectorRev, &maeVectorRev);
	D3DXVec3Normalize(&migiVectorRev, &migiVectorRev);
	static bool PresShift = false;
	static bool PresControl = false;

	bool LockatUp = !(Vector.y > YHOLLD);
	bool LockatUnder = !(Vector.y < -YHOLLD);
	bool LockatRevUp = !(VectorRev.y > YHOLLD);
	bool LockatRevUnder = !(VectorRev.y < -YHOLLD);

	maeVector = maeVector * 0.1f;
	migiVector = migiVector * 0.1f;
	//始点までの長さ

	if (InputKeyboard::GetKeyboardPress(DIK_LSHIFT))
	{
		PresShift = true;
	}
	else
	{
		PresShift = false;
	}
	if (InputKeyboard::GetKeyboardPress(DIK_LCONTROL))
	{
		PresControl = true;
	}
	else
	{
		PresControl = false;
	}

	if (InputKeyboard::GetKeyboardPress(DIK_E))
	{
		eye.y += -0.1f;
		at.y += -0.1f;
	}
	if (InputKeyboard::GetKeyboardPress(DIK_Q))
	{
		eye.y += 0.1f;
		at.y += 0.1f;

	}
	if (InputKeyboard::GetKeyboardPress(DIK_D))
	{
		if (!PresShift && !PresControl)
		{
			at += migiVector;
			eye += migiVector;
		}
		if (PresShift && !PresControl)
		{
			D3DXMatrixRotationY(&rotY, D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&VectorRev, &VectorRev, &rotY);
			at = eye + VectorRev;
		}
		if (!PresShift && PresControl)
		{
			D3DXMatrixRotationY(&rotY, -D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&Vector, &Vector, &rotY);
			eye = at + Vector;
		}
	}
	if (InputKeyboard::GetKeyboardPress(DIK_A))
	{
		if (!PresShift && !PresControl)
		{
			at += -migiVector;
			eye += -migiVector;
		}
		if (PresShift && !PresControl)
		{
			D3DXMatrixRotationY(&rotY, -D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&VectorRev, &VectorRev, &rotY);
			at = eye + VectorRev;
		}
		if (!PresShift && PresControl)
		{
			D3DXMatrixRotationY(&rotY, D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&Vector, &Vector, &rotY);
			eye = at + Vector;
		}
	}
	if (InputKeyboard::GetKeyboardPress(DIK_W))
	{
		if (!PresShift && !PresControl)
		{
			eye += -maeVector;
			at += -maeVector;
		}
		if (PresShift && !PresControl)
		{
			if (LockatRevUp)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVectorRev, D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&VectorRev, &VectorRev, &rotAc);
				at = eye + VectorRev;
			}
		}
		if (!PresShift && PresControl)
		{
			if (LockatUnder)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVector, -D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&Vector, &Vector, &rotAc);
				eye = at + Vector;
			}
		}
	}
	if (InputKeyboard::GetKeyboardPress(DIK_S))
	{
		if (!PresShift && !PresControl)
		{
			eye += maeVector;
			at += maeVector;
		}
		if (PresShift && !PresControl)
		{
			if (LockatRevUnder)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVectorRev, -D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&VectorRev, &VectorRev, &rotAc);
				at = eye + VectorRev;
			}
		}
		if (!PresShift && PresControl)
		{
			if (LockatUp)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVector, D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&Vector, &Vector, &rotAc);
				eye = at + Vector;
			}
		}
	}
	Pos = eye;
	Vec = at - eye;
	//

	//eye = Pos + Vec;
	//ビュー変換行列
	D3DXMatrixLookAtLH(&mtxView, &eye, &at, &up);

};
