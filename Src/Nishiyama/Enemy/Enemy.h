#include "../Scene//Scene.h"
#include<math.h>
#include "../../Common.h"

const int CHARACTER_MAX_NUM = 3;

class Enemy {

protected:

	const float DISTANCE = 300;

	//�v���C���[�ϐ�
	int EnemyHan[11] = { 0 };				//�v���C���[�摜
	const int Enemy_Animation = 11;			//�v���C���[�̃A�j���[�V������
	const int EnemySize = 64;					//�v���C���[�摜�T�C�Y

	float BaseEnemySpeed = 0.5f;				//�v���C���[��{�ړ����x
	float MaxEnemySpeed = 5.0f;				//�v���C���[�ő�ړ����x
	//	float accelerationFactor = 0.0001f;			//�����x

	int animState = 0;						//�E��������������
	int animFlag = 0;						//�A�j���[�V�����̎��
	int animIndex = 0;						//�A�j���[�V�����̓Y����
	int changeAnimFlame = 0;				//�A�j���[�V�����؂�ւ�����

	int animFlameCount = 0;				//�؂�ւ����ԃJ�E���g
	bool EnemyOnSwitch = false;			//�v���C���[�ƃX�C�b�`���d�Ȃ��Ă��邩
	bool EnemyGoalFlag = false;			//�v���C���[���S�[���ɂ��邩

	//float BasePlayerSpeed = 0.2f;				//�v���C���[��{�ړ����x
	//float MaxPlayerSpeed = 4.0f;				//�v���C���[�ő�ړ����x

	VECTOR m_pos;//�v���C���[�̍��W
	VECTOR m_next_pos;//���̃t���[���̍��W
	float speed;

	VECTOR m_move_vec;

	bool enemyStopFlag = false;

	bool MouseOrPlayer = false;//�}�E�X�ɔ�����false�A�v���C���[�ɔ�����true;

	float grav;//�d�͂̑傫��

	bool isJump;
	float jumpPower;
	///////////////////////////////////////////////////////////////////////

	//�����̃v���C���[�̍��W
	VECTOR dvd[CHARACTER_MAX_NUM];

	//�����̃v���C���[�̎��̃t���[���̍��W
	VECTOR next_dvd[CHARACTER_MAX_NUM];

	//�����̃v���C���[���a
	float radius;

	//���ݑΉ����Ă���G
	int currentRivalIndex;

	//���ꂩ��Ή�����G
	int nearestRivalIndex;

	//�v���C���[�̎Q���l��
	int PlayerToParticipate;

	VECTOR Rival[CHARACTER_MAX_NUM];//�v���C���[��CP�̍��W������ϐ�
	///////////////////////////////////////////////////////////////////////


	// �m�[�h��`
	struct Node {
		int x, y;
		int cost; // �ړ��R�X�g
		int heuristic; // �q���[���X�e�B�b�N�i����R�X�g�j
		Node* parent; // �e�m�[�h

		// �R�X�g�̍��v���v�Z����֐�
		int GetScore() const {
			return cost + heuristic;
		}

		// �m�[�h�̔�r�֐�
		bool operator<(const Node& other) const {
			return GetScore() > other.GetScore();
		}
	};


	// �q���[���X�e�B�b�N�֐��i�}���n�b�^�������j
	int Heuristic(int x1, int y1, int x2, int y2) {
		return abs(x1 - x2) + abs(y1 - y2);
	}

public:
	int Walk_Sound[13] = { 0 };

	Enemy();
	~Enemy();

	//������
	void Init(int num);

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�I������
	void Fin();

	//�v���C���[

	//�v���C���[�̂����W�𓾂�
	float GetEnemyPosX() { return m_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetEnemyPosY() { return m_pos.y; }

	//�v���C���[�̂w�T�C�Y�𓾂�
	int GetEnemySizeX() { return EnemySize; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetEnemySizeY() { return EnemySize; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);

	//�v���C���[�̂����W�𓾂�
	float GetNextEnemyPosX() { return m_next_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetNextEnemyPosY() { return m_next_pos.y; }

	//�v���C���[��x���W���Z�b�g
	void SetEnemyNextPosX(float new_pos_x) { m_next_pos.x = new_pos_x; }

	//�v���C���[�̂����W���Z�b�g
	void SetEnemyNextPosY(float new_pos_y) { m_next_pos.y = new_pos_y; }

	//���`�⊮�֐�
	float lerp(float start, float end, float t);

	void SetEnemyOnSwitchTrue();

	void SetEnemyOnSwitchFalse();

	bool GetEnemyOnSwitch() { return EnemyOnSwitch; };

	///////////////////////////////////////////////////////////////////////

	double CalculateDistance(int x1, int y1, int x2, int y2)
	{
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	}

	//��ԋ߂��G��T��
	void ConnectToNearestRival();
	//��ԋ߂��G�ɋ߂Â�
	void NearsRival();
	//�����̃v���C���[�̈ړ�
	void Update();
	//�v���C���[��CP�̍��W�����ʂ̔z��ɓ��ꂷ��
	void Participate(VECTOR Player[CHARACTER_MAX_NUM]);
	//�W�����v����
	void Jump();
	//�W�����v�ł��邩
	bool GetJump() { return isJump; };
	//�W�����v�ł���悤�ɂ���
	void SetJump() { isJump = false; };
	bool IsBlockBetween(float x1, float y1, float x2, float y2);
	///////////////////////////////////////////////////////////////////////
};