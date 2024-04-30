#pragma once

enum class SCENEID
{
//�I����ID
SCENE_ID_END = -1,	//�G���h�V�[����ID

//�^�C�g���V�[����ID
SCENE_ID_INIT_TITLE	= 100,	//�������V�[����ID
SCENE_ID_LOOP_TITLE,		//�J��Ԃ��V�[����ID
SCENE_ID_FIN_TITLE,			//�㏈���V�[����ID

//�v���C�V�[����ID
SCENE_ID_INIT_PLAY = 200,	//�������V�[����ID
SCENE_ID_LOOP_PLAY,			//�J��Ԃ��V�[����ID
SCENE_ID_FIN_PLAY,			//�㏈���V�[����ID

//���U���g�V�[����ID
SCENE_ID_INIT_RESULT = 300,		//�������V�[����ID
SCENE_ID_LOOP_RESULT,			//�J��Ԃ��V�[����ID
SCENE_ID_FIN_RESULT,			//�㏈���V�[����ID
};

class SceneBase
{
public:
	virtual void Init() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;
};

class SceneManager
{
private:
	bool RetryFlag;

	SceneBase* scene;

public:
	static SCENEID g_CurrenySceneID;	//���݂̃V�[��ID

	SceneManager();
	~SceneManager();

	void SceneInit();

	bool SceneLoop();

	void SceneFin();

};
