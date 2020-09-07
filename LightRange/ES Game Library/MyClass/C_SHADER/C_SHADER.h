#pragma once
#include "../../ESGLib.h"
#include "../C_CAMERA/C_CAMERA.h"

class CShaderManager//譲渡関係
{
public:
	//shared登録関数　モデルテキストファイルネームと　HLSLのファイルネーム
	virtual void ShaderInitialize(LPCTSTR _tex_path, LPCTSTR _shader_filename) = 0;

	virtual EFFECT ShaderDraw(float& alpha)                                    = 0;

	virtual void IsModelPass(ANIMATIONMODEL _animation_model) {};
	virtual void IsModelPass(MODEL _model)                    {};

	virtual void SetAttenuation(float _set_attenuation)                        = 0;

	static void CameraSetting(CCamera_& _get_camera_manager) { camera = &_get_camera_manager; };
protected:

	static CCamera_* camera;
	const Vector3 light_pos_correction = Vector3(0, 1, 0);
	EFFECT  shader = nullptr;

};

class CShaderAnimation : public CShaderManager
{
private:
	ANIMATIONMODEL animation_model = nullptr;
	static Vector3 animation_attenuation;// 減衰
public:

	virtual void   ShaderInitialize(LPCTSTR _tex_path, LPCTSTR _shader_filename) override;
	virtual EFFECT ShaderDraw(float& alpha)                        override;
	virtual void   IsModelPass(ANIMATIONMODEL _animation_model)    override;
	virtual void   SetAttenuation(float _set_attenuation)          override;

};

class CShaderModel : public CShaderManager
{
private:
	MODEL model = nullptr;
	static Vector3 model_attenuation; // 減衰
public:

	virtual void   ShaderInitialize(LPCTSTR _tex_path, LPCTSTR _shader_filename) override;
	virtual EFFECT ShaderDraw(float& alpha)                         override;
	virtual void   IsModelPass(MODEL _model)                        override;
	virtual void   SetAttenuation(float _set_attenuation)           override;
};