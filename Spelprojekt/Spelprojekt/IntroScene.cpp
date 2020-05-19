#include "IntroScene.h"



IntroScene::IntroScene(std::string name, Renderer* renderer, DX11Handler& dx11, Window& window, std::vector<Scene*>& scenes, bool& exitGame, SoundHandler* sound, SoundHandler* soundeffect) : Scene(name, renderer, dx11, window), scenes(scenes), exitGame(exitGame)
{
	sceneName = "IntroScene";
	this->camera = new Camera(90.0f, window.GetWidth(), window.GetHeight());
	this->controller = new CameraController(camera, window.GetInput(), CameraController::State::Follow);
	window.GetInput()->LockCursor(false);
	this->nextScene = nullptr;
	Lights& lights = renderer->GetLights();	
	lights.SetSunDirection({ 1, -2, 3 });
	lights.SetSunColor({ 0.98f, 0.96f, 0.73f, 1 });
	lights.SetSunIntensity(0.9f);

	// Music and soundeffects
	this->mainmenuMusic = sound;
	this->mainmenuMusic->SetGlobalVolume(0.5f);
	//this->mainmenuMusic->LoadSound("Cait", "SoundEffects/cait.wav");
	this->mainmenuMusic->LoadSound("Cait", "SoundEffects/MonstersInc.wav");			// mainmenu music??
	//this->mainmenuMusic->LoadSound("Cait", "SoundEffects/FluffingDuck.wav");		// mainmenu music??

	this->soundeffects = soundeffect;
	this->soundeffects->SetGlobalVolume(1.0f);
}

IntroScene::~IntroScene()
{
	delete controller;
}

void IntroScene::Load()
{	
	// Set music volume from beginning		
	mainmenuMusic->PlaySound("Cait", mainmenuMusic->GetGlobalVolume());
	
	GUI* gui = new GUI(dx11);
	introGUI = new IntroGUI(gui, dx11, controller, this, mainmenuMusic, soundeffects);
	renderer->SetGUI(gui);
		
	// save the shaders somewhere, remember to clean it up
	Shader* defaultShader = new Shader();
	defaultShader->LoadPixelShader(L"Shaders/Default_ps.hlsl", "main", dx11.GetDevice());
	defaultShader->LoadVertexShader(L"Shaders/Default_vs.hlsl", "main", dx11.GetDevice());

	Shader* toonshader = new Shader();
	toonshader->LoadPixelShader(L"Shaders/ToonShader_ps.hlsl", "main", dx11.GetDevice());
	toonshader->LoadVertexShader(L"Shaders/ToonShader_vs.hlsl", "main", dx11.GetDevice());

	// object = mesh + material
	Mesh* dev_monkey_mesh = ShittyOBJLoader::Load("Models/monkey.obj", dx11.GetDevice());

	Object* sphere = new Object(ObjectLayer::None, dev_monkey_mesh, new Material(defaultShader, dx11));
	Texture* monkey_texture = Texture::CreateTexture("Textures/rocks.jpg", dx11);
	Texture* monkey_normal = Texture::CreateTexture("Textures/rocks_normal.png", dx11);
	
	sphere->GetMaterial()->SetTexture(ALBEDO_MATERIAL_TYPE, monkey_texture, SHADER_BIND_TYPE::PIXEL);
	sphere->GetMaterial()->SetTexture(NORMAL_MATERIAL_TYPE, monkey_normal, SHADER_BIND_TYPE::PIXEL);
	sphere->GetMaterial()->SetSampler(0, dx11.GetDefaultSampler(), SHADER_BIND_TYPE::PIXEL);

	sphere->GetTransform().Translate(0, 0+9, -5);

	Object* glasse = new Object(ObjectLayer::Enviroment, AssimpHandler::loadFbxObject("Models/Glasse_intro_Pose.fbx", dx11, toonshader));
	glasse->GetTransform().Translate(0, 0.65+9, -3);
	glasse->GetTransform().Rotate(0, -0.6, 0);
	//glasse->GetMaterial()->GetTexture(1)->SetSampler(dx11.GetDevice());
	AddObject(glasse);
	
	Object* wagon = new Object(ObjectLayer::Enviroment, AssimpHandler::loadFbxObject("Models/Wagon.fbx", dx11, toonshader));
	wagon->GetTransform().Translate(7, -1.75+10, 1);
	wagon->GetTransform().Rotate(0, 0.1, 0);
	wagon->GetTransform().Scale(0.5f, 0.5f, 0.5f);
	//wagon->GetMaterial()->GetTexture(0)->SetSampler(dx11.GetDevice());
	AddObject(wagon);
	controller->SetFollow(&sphere->GetTransform(), { 0, 1, 0 });
	
	AddObject(sphere);
	sphere->SetVisible(false);

	//// ------- BACKGROUND

	Object* backGround = new Object(ObjectLayer::Enviroment, AssimpHandler::loadFbxObject("Models/Background_Plane.fbx", dx11, toonshader));
	backGround->GetTransform().Translate(5, 19, 15);
	backGround->GetTransform().Rotate(-1.5, 0, 0);
	backGround->GetTransform().Scale(100, 1, 24);
	//backGround->GetMaterial()->GetTexture(0)->SetSampler(dx11.GetDevice());
	AddObject(backGround);

	// ------- TERRAIN
	Shader* terrainShader = new Shader();
	terrainShader->LoadPixelShader(L"Shaders/Terrain_ps.hlsl", "main", dx11.GetDevice());
	terrainShader->LoadVertexShader(L"Shaders/Default_vs.hlsl", "main", dx11.GetDevice());

	Texture* grass_texture = Texture::CreateTexture("Textures/Grass_ColorTest.png", dx11);
	Texture* grass_normal = Texture::CreateTexture("Textures/Grass_Normal.png", dx11);
	Texture* sand_texture = Texture::CreateTexture("Textures/Sand_Color_Test.png", dx11);
	Texture* sand_normal = Texture::CreateTexture("Textures/Sand_Normal_2.png", dx11);

	Material* terrainMat = new Material(terrainShader, dx11);
	terrainMat->SetTexture(0, grass_texture, SHADER_BIND_TYPE::PIXEL);
	terrainMat->SetTexture(1, sand_texture, SHADER_BIND_TYPE::PIXEL);
	terrainMat->SetTexture(2, grass_normal, SHADER_BIND_TYPE::PIXEL);
	terrainMat->SetTexture(3, sand_normal, SHADER_BIND_TYPE::PIXEL);

	terrainMat->SetSampler(0, dx11.GetDefaultSampler(), SHADER_BIND_TYPE::PIXEL);
	terrainMat->GetMaterialData().hasNormalTexture = true;

	Terrain ground;
	ground.GenerateMesh("Textures/map_displacement_map_small.png", dx11.GetDevice(), false);
	
	Object* terrainObject = new Object(ObjectLayer::None, ground.GetMesh(), terrainMat);
	terrainObject->GetTransform().SetPosition({ -100, -2+8.5f, -10 });
	AddObject(terrainObject);
	
		
}

void IntroScene::Unload()
{
}

void IntroScene::Update(const float& deltaTime)
{
	this->cameraFocusPosition = { 0,0,5 };

	Scene::Update(deltaTime);
	controller->Update(deltaTime);
	introGUI->Update();
}

Scene* IntroScene::GetNextScene() const
{
	return nextScene;
}


void IntroScene::setNextScene()
{
	Input* input = this->window.GetInput();

	// Change scene logic
	for (int i = 0; i < scenes.size(); i++)
	{
		if (scenes[i]->GetName() == "DevScene")
			nextScene = scenes[i];
	}
}
