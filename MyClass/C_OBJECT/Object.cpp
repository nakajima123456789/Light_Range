#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"

//---------------------------------------------
//���萔�w��
//---------------------------------------------
//
//----------------------------------------------
//��Transform
//----------------------------------------------
    //�X�V
	void Transform::Update() {
		if (parent == nullptr) return;

		//���񎞂̂�
		if (backupposition == Vector3_Zero) backupposition = parent->position;
		if (backuprotation == Vector3_Zero) backuprotation = parent->rotation;
		if (backupscale == -0.0f) backupscale = parent->scale;

		     //���[�J�����W���X�V
		     localposition = Vector3_Add(localposition, Vector3_Add(position,-backupposition));
		     localrotation = Vector3_Add(localrotation, Vector3_Add(rotation, -backuprotation));
		     localscale    = localscale * MathHelper_Max(scale / backupscale,1.0f);

			//���W���X�V
			position = Vector3_Add(localposition, parent->position);
			rotation = Vector3_Add(localrotation, parent->rotation);
			scale    = localscale*parent->scale;

			//�o�b�N�A�b�v�����
			backupposition = position;
			backuprotation = rotation;
			backupscale    = MathHelper_Max(scale, 1.0f);
		}

//---------------------------------------------
//���I�u�W�F�N�g
//---------------------------------------------

//�q�I�u�W�F�N�g���X�g�ɑ}��
void Object::ChildObj_AddList(ChildObjRef& c) {
	//�e�Ƃ��Ď������w��
	c->gameObject = this;
	//�e�����ɍ��W�X�V
	c->transform.parent = &this->transform;
	c->transform.position = Vector3_Add(c->transform.position ,c->transform.parent->position);
	c->transform.rotation = Vector3_Add(c->transform.rotation, c->transform.parent->rotation);
	c->transform.scale = c->transform.scale / c->transform.parent->scale;
	c->transform.Update();
	//���X�g�ɑ}��
	this->p_childObjects.push_back(c);	
	//�������֐����Ă�
	c->Init();
}

//�q�I�u�W�F�N�g�̍X�V
void Object::ChildUpdate() {
   //�����t���O��TRUE�Ȃ����
   auto it = p_childObjects.begin();
   while (it != p_childObjects.end()) {
	if (!(*it)->IsRemove()) {
	   it++;
	}
	else {
	   it = p_childObjects.erase(it);
	}
   }

	//Active�łȂ��ꍇ�X�V���Ȃ�
	if (!_isActive) return;

	//Transform�X�V
	transform.Update();

	//Update�Ăяo��
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {if (c->GetActive()) c->Update(); });
		
	//�q��Update�Ăяo��
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->ChildUpdate();});

	//�����t���O��TRUE�Ȃ����
	auto end = std::remove_if(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {return c->IsRemove(); });
	p_childObjects.erase(end, p_childObjects.end());
}

//�q�̕`��
void Object::ChildDraw2D() {
	//�`��
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->Draw2D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->ChildDraw2D();});
}
void Object::ChildDraw3D() {
	//�`��
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->Draw3D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef& c) {c->ChildDraw3D();});
}
void Object::ChildDrawAlpha3D() {
	//�`��
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->DrawAlpha3D();});
	std::for_each(p_childObjects.begin(), p_childObjects.end(), [](ChildObjRef & c) {c->ChildDrawAlpha3D();});
}

//����
void Object::Remove() {
   this->_isRemove = true;
   for (auto&& i : p_childObjects) { i->Remove(); }
   this->OnRemove();
   this->transform.Remove();
}

//�����t���O��Ԃ�
bool Object::IsRemove() {
	return _isRemove;
}

//Active��ύX
void Object::SetActive(bool istrue) {
	//���l�Ȃ牽�����Ȃ�
	if (_isActive == istrue) return;
	_isActive = istrue;
	//std::for_each(ChildObj_list.begin(), ChildObj_list.end(), [istrue](ChildObjRef& c) {c->SetActive(istrue);});
}
//---------------------------------------------
//���I�u�W�F�N�g�}�l�[�W���[
//---------------------------------------------
//������
void ObjectManager::Init() {}

//�X�V
void ObjectManager::Update() {
	_root.ChildUpdate();
}

//�`��
void ObjectManager::Draw2D() {
	_root.ChildDraw2D();
}
void ObjectManager::Draw3D() {
	_root.ChildDraw3D();
}
void ObjectManager::DrawAlpha3D() {
	_root.ChildDrawAlpha3D();
}

//�q�I�u�W�F�N�g���X�g�ɑ}��
void ObjectManager::AddList(ChildObjRef& c) {
	_root.ChildObj_AddList((ChildObjRef)c);
}
