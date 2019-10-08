
#ifndef _FIAG_H_
#define _FIAG_H_

#include "Object.h"
#include "Render.h"
#include "CreateData.h"


class Flag : public Object
{
public:
	enum FlghAttribute
	{
		DefaultState,
		AirState,
		SecureState,
		Max_State
	};
	enum FlagBelong
	{
		TeamA,
		TeamB,
		TeamC,
		TeamNone,
		TeamMax
	};

	void Create(FlagBelong in,D3DXVECTOR3 Pos);
	void Destroy();
	void Updata();
	void Draw();
	void SetState(FlghAttribute in);
	void SetCamera(D3DXMATRIX in);
	int GetState();
private:
	RenderMesh *pRendModel;
	MESHDATA dataFlag;
	FlghAttribute Atteribute;
	FlagBelong Belong;
};

#endif//_FIAG_H_
