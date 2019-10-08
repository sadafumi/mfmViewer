#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "CreateData.h"
#include "Render.h"
#include "DrawData.h"

#define INCHARMAX (5)
#define KEYBOARDX (11)
#define KEYBOARDY (5)
#define KEYBOARDTYPE (3)
//#define BOARDTYPEHIRA (0)
//#define BOARDTYPEKATA (1)
//#define BOARDTYPEROMA (2)
//#define BOARDTYPEHIRAB (3)
//#define BOARDTYPEKATAB (4)
//#define BOARDTYPEROMAB (5)

class SystemKeyBoard
{
public:
	enum KeyBoradType
	{
		HIRAGANA_A,
		HIRAGANA_B,
		KATAKANA_A,
		KATAKANA_B,
		ROMAJI_A,
		ROMAJI_B,
		NONE
	};
	typedef struct
	{
		int x;
		int y;
		KeyBoradType type;
		bool Empty;
	}word;

	void InitKeyBorad(void);
	void UninitKeyBorad(void);
	void UpdateKeyBorad(void);
	void DrawKeyBorad(void);
	bool EneKeyBorad();
private:
	float KeyBFlash;
	word Newinchar[INCHARMAX];
	int BoardX, BoardY ,InCharCunt;
	KeyBoradType BoardType;
	bool EndInName;
	Render::Shader::Surface2D KeyBoradRender;
	//Render::Fixed::Surface2D KeyBoradOption1Render;
	//Render::Fixed::Surface2D KeyBoradOption2Render;
	//Render::Fixed::Surface2D KeyBoradSelectRender;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Hira_A;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Hira_B;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Kata_A;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Kata_B;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Roma_A;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Roma_B;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Option_1;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Option_2;
	DATA_TYPE::VERTEX2DDATA KeyBorad_Fade;
};

#endif //_KEYBOARD_H_
