
#include "C_ENEMY_BASE.h"
Vector3 *C_ENEMY_BASE::player_pos;

/**
 * @file C_ENEMY_BASE.h
 * @brief�@�G�ŋ��L����郁�\�b�h�@�\
 * @date 
 */

 /**
  * @fn
  * �����Ɋ֐��̐���������
  * @�֐����@
  * @brief �v�����
  * @param (������) �����̐����@
  * @param (������) �����̐����@
  * @return �߂�l�̐����@
  * @detail �ڍׂȐ����@
  */
LPCTSTR  C_ENEMY_BASE::GetModelFileName(int _enemy_model)
{
	switch (_enemy_model)
	{
	case ENEMY_LARGE:
		return (LPCTSTR)_T("MODEL//enemy_motion//enemy_large.x");
		break;
	case ENEMY_WAMAN:
		return (LPCTSTR)_T("MODEL//woman_enemy//woman_enemy.X");
		break;
	}
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@
 * @brief �v�����
 * @param (������) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@
 */
LPCTSTR  C_ENEMY_BASE::GetModelTextureFileName(int _enemy_model)
{
	switch (_enemy_model)
	{
	case ENEMY_LARGE:
		return (LPCTSTR)_T("MODEL//enemy_motion//lambert1_2D_View.png");
		break;
	case ENEMY_WAMAN:
		return (LPCTSTR)_T("MODEL//woman_enemy//lambert1_2D_View.png");
		break;
	}
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@Lock_at_Target
 * @brief �v�����
 * @param (_position) �����̐����@�Ώۍ��W�i�v���C���[�j
 * @param (������) �����̐����@
 * @return �߂�l�̐����@�G�Ƒ���̕����擾����
 * @detail �ڍׂȐ����@�G���v���C���[�Ɍ����������Ƃ��Ɏg��
 */
float C_ENEMY_BASE::Lock_at_Target(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;
	float angle = MathHelper_Atan2(other_position.z - is_position.z, other_position.x - is_position.x);
	return angle;
}


/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@Distance_at_Traget
 * @brief �v�����
 * @param (_position) �����̐����@�Ώۍ��W�i�v���C���[�j
 * @param (������) �����̐����@
 * @return �߂�l�̐����@��̋������v�Z���Ԃ�
 * @detail �ڍׂȐ����@
 */
float C_ENEMY_BASE::Distance_at_Traget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	float distance = Vector3_Distance(is_position, other_position);

	return distance;
}


/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@skater_st_Traget
 * @brief �v�����
 * @param (_position) �����̐����@�߂Â���������̍��W
 * @param (������) �����̐����@
 * @return �߂�l�̐����@�m�[�}���C�Y�����ŋ߂Â������W��Ԃ�
 * @detail �ڍׂȐ����@
 */
Vector3 C_ENEMY_BASE::skater_st_Traget(Vector3 _position)
{
	Vector3 is_position = this->transform.position;
	Vector3 other_position = _position;

	is_position += Vector3_Normalize(other_position - is_position) * 0.02;

	return is_position;
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@SetPlayerState
 * @brief �v�����
 * @param (new_state) �����̐����@�A�j���[�V�����̔ԍ�����
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@�A�j���[�V�����؂�ւ��t���[���Đ����h�~
 */
bool C_ENEMY_BASE::SetPlayerState(int new_state)
{
	if (this_track_enable == new_state) { return FALSE; }
	else {
		animation_model->SetTrackEnable(this_track_enable, FALSE);
		animation_model->SetTrackEnable(new_state, TRUE);
		animation_model->SetTrackPosition(new_state, 0);
		this_track_enable = new_state;
	}
	return TRUE;
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@Set_Material
 * @brief �v�����
 * @param (color) �����̐����@�F�w��
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@
 */
Material C_ENEMY_BASE::Set_Material(Color color)
{
	Material mtrl;

	mtrl.Diffuse = color;
	mtrl.Ambient = color;
	mtrl.Specular = color;
	mtrl.Emissive = color;
	mtrl.Power = 1.0f;

	return mtrl;
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@wrap�@
 * @brief �v�����
 * @param (������) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@���b�v�A���E���h�@�������̒l��high�̒l�𒴂�����low�̒l�ɂ���܂��킻�̋t
 */
int C_ENEMY_BASE::wrap(int x, int low, int high)
{
	ASSERT(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@ShaderInit
 * @brief �v�����
 * @param (LPCTSTR _file_texcha) �����̐����@���f���̃t�@�C���l�[�������@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@SHADER���̓o�^�@
 */
void C_ENEMY_BASE::ShaderInit(LPCTSTR _file_texcha)
{
	c_shader_manager.reset(new CShaderAnimation);
	c_shader_manager->ShaderInitialize(_file_texcha, _T("FX/Light.hlsl"));
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@ShaderDrawGetEffct
 * @brief �v�����
 * @param (������) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@ShaderInit�œo�^��������K�p��������
 * @detail �ڍׂȐ����@
 */
EFFECT C_ENEMY_BASE::ShaderDrawGetEffct()
{
	c_shader_manager->IsModelPass(this->animation_model);

	EFFECT shader = c_shader_manager->ShaderDraw(alpha);

	return EFFECT(shader);
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@ShaderAlphaDraw
 * @brief �v�����
 * @param (������) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@�G�ƃv���C���[�̋����ɍ��킹�ĕs������ς���
 */
void C_ENEMY_BASE::ShaderAlphaDraw()
{
	Vector3 enemy_pos  = this->animation_model->GetPosition();
	Vector3 target_pos = (*player_pos);

	float v_dis = 1.8f;
	float add_alpha = 0.05f;

	if ((enemy_pos.x - target_pos.x) * (enemy_pos.x - target_pos.x) + (enemy_pos.z - target_pos.z) * (enemy_pos.z - target_pos.z) <= v_dis * v_dis)
	{
		alpha = min(alpha + add_alpha, 1);
	}
	else {
		alpha = max(alpha - add_alpha, 0);
	};
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@IsDistanceInit
 * @brief �v�����
 * @param (std::string _tags) �����̐����@�Ăяo�����̃^�O����
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@�^�O��list�ɓo�^����
 */
void  C_ENEMY_BASE::IsDistanceInit(std::string _tags)
{
	ASSERT(_tags != "defult" && "defult�ȊO�ɂ��Ă�������");
	c_dis.reset(new C_DIS);
	c_dis->Init();
	c_dis->IsTagSet(_tags);
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@IsDistanceUpdate
 * @brief �v�����
 * @param (_pos) �����̐����@�Ăяo�����̍��W����
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@
 */
void  C_ENEMY_BASE::IsDistanceUpdate(Vector3 _pos)
{
	c_dis->IsPosition(animation_model->GetPosition());
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@IsHitObjectsInit
 * @brief �v�����
 * @param (_tags) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@�q�b�g�{�b�N�X��list�ɓo�^����
 */
void  C_ENEMY_BASE::IsHitObjectsInit(std::string _tags)
{
	ASSERT(_tags != "defult" && "defult�ȊO�ɂ��Ă�������");
	hitbox.reset(new HitBox);
	hitbox->Init();
	hitbox->Settags(_tags);

	hitbox->SetHitBoxScale(1.1f);
	hitbox->SetHitBoxPosition(Vector3(2, 0, -2));
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐���
 * @brief �v�����
 * @param (������) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@
 * @detail �ڍׂȐ����@�@
 */
void  C_ENEMY_BASE::IsHitObjectsDraw(Vector3 _pos)
{
	hitbox->SetHitBoxPosition(_pos);
	hitbox->Draw3D();
}

/**
 * @fn
 * �����Ɋ֐��̐���������
 * @�֐����@IsHitObjects
 * @brief �v�����
 * @param (tags) �����̐����@
 * @param (������) �����̐����@
 * @return �߂�l�̐����@�w�肵���^�O�ɊY������q�b�g�{�b�N�X�ƏՓ˔�������������Ă���TRUE��Ԃ�
 * @detail �ڍׂȐ����@�q�b�g�{�b�N�X�͐ÓI�ϐ���list�^�ŊǗ�����Ă���A�O���ɂ���q�b�g�{�b�N�X�ƏՓ˔�������邱�Ƃ��\
 */
bool C_ENEMY_BASE::IsHitObjects(std::string tags) {
	ASSERT(hitbox->Tag_Sarch(tags) && "�w�肵��HITBOX�̃^�O�����݂��Ă��܂���B");
	bool result = false;
	std::list<HitBox*> HitList = hitbox->HitHitBoxlist();

	for (auto&& other : HitList) {
		if (other->tag == tags)
		{
			result = true;
		}
	}
	return result;
}