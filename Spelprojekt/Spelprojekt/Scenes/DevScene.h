#pragma once
#include "../Scene.h"
#include "../Logger.h"
#include "../Camera.h"
#include <vector>
#include "../Object.h"
#include "../ShittyOBJLoader.h"
#include "../Input.h"
#include "../CameraController.h"
#include "../HeightMapGenerator.h"
#include "../assimpHandler.h"
#include "../Projectile.h"
#include "../Timer.h"
#include "../GUI.h"
#include "../AABB.h"

class DevScene : public Scene
{
	const char DEBUG_CAMERA_KEY = 'f';

public:
	
	DevScene(Renderer* renderer, DX11Handler& dx11, Window& window);
	virtual ~DevScene();

	void Load() override;
	void Unload() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& fixedDeltaTime) override;
		
	// update time function?

	Scene* GetNextScene() const override;


private:

	float testFloat = 0.f;

	Camera* camera;
	
	CameraController* controller;

	GUIText* gametimerText;
	GUISprite* healthFrame;
	GUISprite* healthbar;
	GUIActionbar* actionbarLeft;

	Player* player;
	Object* coconutPickUp;
	
	TerrainGenerator test;
	Timer gametimer;
};