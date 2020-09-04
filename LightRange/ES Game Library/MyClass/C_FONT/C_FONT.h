#pragma once
#include "../../ESGLib.h"

enum { x, y, max };

class C_FONT
{
public:
	C_FONT(const C_FONT&) = delete;
	C_FONT& operator=(const C_FONT&) = delete;
	C_FONT(C_FONT&&) = delete;
	C_FONT& operator=(C_FONT&&) = delete;

	C_FONT::C_FONT() { font = GraphicsDevice.CreateSpriteFont(_T("Comic Sans MS"), 35); };
	C_FONT::~C_FONT() { font_vector.clear(); font = nullptr; };

private:
	enum { x, y, max };
public:

	// シングルトンインスタンスの取得
	static C_FONT& GetInstance()
	{
		static C_FONT c_font_instance;
		return c_font_instance;
	}

	void C_FONT::Draw2D()
	{
		int Σ = 0;
		std::for_each(font_vector.begin(), font_vector.end(), [&](double& font_vector){	
			Σ += 30;
			SpriteBatch.DrawString(font, Vector2(0.0f, Σ), Color(255, 255, 255), _T("G-> %f"), font_vector);
		});
		for (int i = 0; i < max; ++i)
		{
			SpriteBatch.DrawString(font, Vector2(0.0f, (i * 30) + 200 ), Color(255, 255, 255), _T("MAX-> %f"), index[i]);
		}
	}

	void C_FONT::add_index(int& _tag, ...) {
		va_list arguments;
		va_start(arguments, _tag);

		for (int x = 0; x < _tag; x++)
		{
			font_vector.push_back(va_arg(arguments, int));
		}
		va_end(arguments);
		return;
	};

	void C_FONT::add_frame_index(float index1, float index2)
	{
		index[x] = index1;
		index[y] = index2;
	}

private:

	FONT font = NULL;
	std::vector<double> font_vector;

	float index[max];

};
#define C_FONT_MANAGER C_FONT::GetInstance()

