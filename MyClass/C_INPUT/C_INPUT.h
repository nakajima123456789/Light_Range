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
	inline static GamePadState  GetGamePadState()  { return GamePad(0)->GetState();  }
	inline static GamePadBuffer GetGamePadBuffer() { return GamePad(0)->GetBuffer(); }

	inline static KeyboardState  GetKeyState()   { return Keyboard->GetState();  }
	inline static KeyboardBuffer GetKeyBuffer()  { return Keyboard->GetBuffer(); }

	static C_INPUT& GetInstance()
	{
		static C_INPUT c_input;
		return c_input;
	}
	Vector3 GetArrowkeyVector();
	Vector3 GetArrowpadVector();
	Vector3 GetArrowpadVectorNomalize();

	bool    GetPadInputDown(int KeyID);
	bool    GetPadInput(int KeyID);    
	bool    GetKeyInputDown(int keyID);

	double  AxisStateX();
	double  AxisStateY();

	bool    AxisFlag();

	void    BufferButtomSetInit(int button, int buttonid);
	void    BufferButtomInit();

	float   PadKeyAngle();

private:
	BYTE buttom_manager[BUTTON_MAX];
	float angle = 0;
};

#define Input C_INPUT::GetInstance()





