#pragma once

#include "../../ESGLib.h"
#include <algorithm>

class Transform;
class Object;
class ObjectManager;

//----------------------------------------------
//��Transform
//----------------------------------------------
class Transform {
public:
	//���W
      Vector3 position = Vector3_Zero;
	Vector3 localposition= Vector3_Zero;
	
	//��]
	Vector3 rotation= Vector3_Zero;;
	Vector3  localrotation= Vector3_Zero;;

	//�X�P�[��
	float scale= 0.0254f;;
	float localscale= 0.0254f;;

	//Transform�̐e
	Transform * parent = NULL;

	//�X�V
	void Transform::Update();

	//�g�p����Ă��Ȃ���
	bool Transform::IsRemove() {
	   return _isremove;
	}
	void Transform::Remove() {
	   _isremove = true;
	}

private:
	//�O�t���[���̃o�b�N�A�b�v
	Vector3 backupposition = Vector3_Zero;
	Vector3 backuprotation = Vector3_Zero;
	float backupscale = 0.0f;

	//�g�p����Ă��Ȃ���
	bool _isremove = false;
};

//---------------------------------------------
//���I�u�W�F�N�g
//---------------------------------------------
typedef std::shared_ptr<Object> ChildObjRef;
class Object {
protected:
   //���X�g
   std::list<ChildObjRef> p_childObjects;

private:
   //�����t���O
   //false�ōX�V���s��Ȃ�
   bool _isActive = true;
   	
   bool _isRemove = false;
public:
	//�e�I�u�W�F�N�g
	Object * gameObject = nullptr;
	//���W
	Transform transform;
	//�^�O
	std::string tag = "Default";

	//�R���X�g���N�^
	Object() {};

	//�f�X�g���N�^
	virtual ~Object() { this->Remove(); };

	//������
	virtual void Init() {};

	//�X�V
	virtual void Update() {};

	//�q�I�u�W�F�N�g���X�g�ɑ}��
	void ChildObj_AddList(ChildObjRef& c);

	//�q�I�u�W�F�N�g�̍X�V
	virtual void ChildUpdate();

	//�`��
	virtual void Draw2D() {};
	virtual void Draw3D() {};
	virtual void DrawAlpha3D() {};
	virtual void DrawEnd() {};

	
	//�q�̕`��
	virtual void ChildDraw2D();
	virtual void ChildDraw3D();
	virtual void ChildDrawAlpha3D();
	virtual void ChildDrawEnd();

	//����
	virtual void Remove();

	//�����^�O
	virtual void IsRemove_flag(bool _flag) { _isRemove = _flag; };

	//�����̍ۂɌĂ΂�鏈��
	virtual void OnRemove() {};

	//�����t���O��Ԃ�
	bool IsRemove();

	//�q�̐���Ԃ�
	int ChildListSize() { return p_childObjects.size(); };

	//Active��ύX
	void SetActive(bool i);
	bool GetActive() {
	   return _isActive;
	};
};

//---------------------------------------------
//���I�u�W�F�N�g�}�l�[�W���[
//---------------------------------------------
class ObjectManager {
private:
	//���[�g�I�u�W�F�N�g(�S�I�u�W�F�N�g�̐e�ƂȂ�)
public:
	Object _root;
	//�R���X�g���N�^
     ObjectManager() {};

   //�f�X�g���N�^
   virtual ~ObjectManager() {};

    //������
	void Init();

	//�X�V
	void Update();

	//�`��
	virtual void Draw2D();
	virtual void Draw3D();
	virtual void DrawAlpha3D();

	virtual void DrawEnd();

	//�q�I�u�W�F�N�g���X�g�ɑ}��
	void AddList(ChildObjRef& c);
};