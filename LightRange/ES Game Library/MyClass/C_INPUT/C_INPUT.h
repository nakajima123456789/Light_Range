#pragma once
#include "../../ESGLib.h"
#include "../C_INPUT/C_INPUT.h"

int const BUTTON_MAX = 31;

class C_INPUT
{
private:
	C_INPUT();
	virtual ~C_INPUT();

	C_INPUT(const C_INPUT&) = delete;
	C_INPUT& operator=(const C_INPUT&) = delete;
	C_INPUT(C_INPUT&&) = delete;
	C_INPUT& operator=(C_INPUT&&) = delete;

public:
	inline static GamePadState  GetGamePadState()  { return GamePad(0)->GetState(); }
	inline static GamePadBuffer GetGamePadBuffer() { return GamePad(0)->GetBuffer(); }

	inline static KeyboardState GetKeyState()   { return Keyboard->GetState(); }
	inline static KeyboardBuffer GetKeyBuffer() { return Keyboard->GetBuffer(); }

public:
	static C_INPUT& GetInstance()
	{
		static C_INPUT c_input;
		return c_input;
	}
	Vector3 C_INPUT::GetArrowkeyVector();

	Vector3 C_INPUT::GetArrowpadVector();
	Vector3 C_INPUT::GetArrowpadVectorNomalize();

	bool    C_INPUT::GetPadInputDown(int KeyID);//buffertype

	bool    C_INPUT::GetPadInput(int KeyID);//state

	bool    C_INPUT::GetKeyInputDown(int keyID);//buffer

	double  C_INPUT::AxisStateX();
	 
	double  C_INPUT::AxisStateY();

	bool    C_INPUT::AxisFlag();//ステック動かしてない時FALSE 動かしている時TRUE

	void    C_INPUT::BufferButtomSetInit(int button, int buttonid);

	void    C_INPUT::BufferButtomInit();

	float   C_INPUT::PadKeyAngle();

private:
	BYTE buttom_manager[BUTTON_MAX];

	float angle = 0;

};
#define Input C_INPUT::GetInstance()





