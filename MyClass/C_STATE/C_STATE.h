#pragma once

// �C���^�[�t�F�[�X�N���X
class State {
private:
   //�o�߃t���[��
   int _timef = 0;
   //���Ɉڍs������
   State* _nextState = nullptr;
public:
   // ���z�f�X�g���N�^ 
   // �X�V
   virtual void Update() {}; 

  void  State::AddTime() { _timef++; };
  int      State::GetTime() { return _timef; };

};
//�X�e�[�g�Ǘ��N���X
class StateProcessor {
private:
   State* _state=nullptr; //���݂̏��
public:
   StateProcessor::StateProcessor() : _state(nullptr) {
   }
   StateProcessor::~StateProcessor() {
	delete _state;
   }

   void StateProcessor::Update() {
	_state->AddTime();
	_state->Update();

   }

   void  StateProcessor::ChangeState(State* state) {
	delete _state;
	_state = state;
   }

   State* StateProcessor::NowState() {
	return _state;
   }  
};
