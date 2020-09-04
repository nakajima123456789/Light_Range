#include "C_INPUT.h"

C_INPUT::C_INPUT()
{ 
	InputDevice.CreateGamePad(1), BufferButtomInit();
}
C_INPUT::~C_INPUT() {  }

Vector3 C_INPUT::GetArrowkeyVector()
{
	Vector3 result = Vector3_Zero;
	if (GetKeyState().IsKeyDown(Keys_Left)) 
	{ result += Vector3_Left; }
	else { if (GetKeyState().IsKeyDown(Keys_Right)) 
	{ result += Vector3_Right; } }

	if (GetKeyState().IsKeyDown(Keys_Up)) 
	{ result += Vector3_Up; }
	else { if (GetKeyState().IsKeyDown(Keys_Down))
	{ result += Vector3_Down; } }
	return result;
}

Vector3 C_INPUT::GetArrowpadVector()
{
	Vector3 result = Vector3_Zero;

	result.x = AxisStateX();
	result.z = AxisStateY();

	float circle_x, circle_z;

	circle_x = result.x * Math_Sqrt(1.0f - 0.5f * result.z * result.z);
	circle_z = result.z * Math_Sqrt(1.0f - 0.5f * result.x * result.x);

	result.x = circle_x;
	result.z = circle_z;

	return result;
}

Vector3 C_INPUT::GetArrowpadVectorNomalize()
{
	Vector3 result = Vector3_Zero;

    result.x = AxisStateX();
	result.z = AxisStateY();

	Vector3 result_nomalize = Vector3_Normalize(result);

	return result_nomalize;
}

bool C_INPUT::GetPadInputDown(int KeyID)
{
	return (BOOL)GetGamePadBuffer().IsPressed(buttom_manager[KeyID]);
}

bool C_INPUT::GetPadInput(int KeyID)
{
	return (BOOL)GetGamePadState().Buttons[KeyID] != 0;
}

bool C_INPUT::GetKeyInputDown(int keyID)//buffer
{
	return (BOOL)GetKeyBuffer().IsPressed(keyID);
}

double C_INPUT::AxisStateX()
{
	double axis_x = (double)GetGamePadState().X / (double)Axis_Max;
	return axis_x != 0 ? axis_x : FALSE;
}

double  C_INPUT::AxisStateY()
{
	double axis_y = (double)GetGamePadState().Y / (double)Axis_Min;
	return axis_y != 0 ? axis_y : FALSE;
}

bool C_INPUT::AxisFlag()
{
	return AxisStateX() == 0 && AxisStateY() == 0 ? FALSE : TRUE;
}

float C_INPUT::PadKeyAngle()
{
	angle = MathHelper_Atan2(AxisStateX(), AxisStateY());
	return angle;
}

void C_INPUT::BufferButtomSetInit(int button, int buttonid)
{
	buttom_manager[button] = buttonid;
}

void C_INPUT::BufferButtomInit()
{
	BufferButtomSetInit(0,  GamePad_Button1);
	BufferButtomSetInit(1,  GamePad_Button2);
	BufferButtomSetInit(2,  GamePad_Button3);
	BufferButtomSetInit(3,  GamePad_Button4);
	BufferButtomSetInit(4,  GamePad_Button5);
	BufferButtomSetInit(5,  GamePad_Button6);
	BufferButtomSetInit(6,  GamePad_Button7);
	BufferButtomSetInit(7,  GamePad_Button8);
	BufferButtomSetInit(8,  GamePad_Button9);
	BufferButtomSetInit(9,  GamePad_Button10);
	BufferButtomSetInit(10, GamePad_Button11);
	BufferButtomSetInit(11, GamePad_Button12);
	BufferButtomSetInit(12, GamePad_Button13);
	BufferButtomSetInit(13, GamePad_Button14);
	BufferButtomSetInit(14, GamePad_Button15);
	BufferButtomSetInit(15, GamePad_Button16);
	BufferButtomSetInit(16, GamePad_Button17);
	BufferButtomSetInit(17, GamePad_Button18);
	BufferButtomSetInit(18, GamePad_Button19);
	BufferButtomSetInit(19, GamePad_Button20);
	BufferButtomSetInit(20, GamePad_Button21);
	BufferButtomSetInit(21, GamePad_Button22);
	BufferButtomSetInit(22, GamePad_Button23);
	BufferButtomSetInit(23, GamePad_Button24);
	BufferButtomSetInit(24, GamePad_Button25);
	BufferButtomSetInit(25, GamePad_Button26);
	BufferButtomSetInit(26, GamePad_Button27);
	BufferButtomSetInit(27, GamePad_Button28);
	BufferButtomSetInit(28, GamePad_Button29);
	BufferButtomSetInit(29, GamePad_Button30);
	BufferButtomSetInit(30, GamePad_Button31);
}