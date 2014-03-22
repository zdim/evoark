#include "ParticleSystem.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_HandleManager.h"
#include "../../TinyXML/tinyxml.h"
#include <string>

CParticleSystem::CParticleSystem()
{
	numEmitters = 1;
}


CParticleSystem::~CParticleSystem()
{
}

void CParticleSystem::Init()
{
	LoadEffect();	

	particleEffect[1]->Initialize();
}

void CParticleSystem::Update(float dt)
{

	particleEffect[1]->Update(dt);
}

void CParticleSystem::Render()
{

	particleEffect[1]->Render();
}


void CParticleSystem::LoadEffect()
{
	TiXmlDocument doc;
	doc.LoadFile("Resources/XML/ParticleEffects/3.xml");
	TiXmlElement* pRoot = doc.RootElement();
	

	TiXmlElement* pEmittor = pRoot->FirstChildElement();
	pEmittor->Attribute("Emittor", &numEmitters);

	int m_nNumParticles;
	pEmittor->Attribute("NumOfParticles", &m_nNumParticles);
	double m_fSpawnRate;
	pEmittor->Attribute("SpawnRate", &m_fSpawnRate);
	double m_fTimeFromLastSpawn;
	pEmittor->Attribute("TimeFromLastSpawn", &m_fTimeFromLastSpawn);
	int m_nShape;
	pEmittor->Attribute("Shape", &m_nShape);
	double m_fRadius;
	pEmittor->Attribute("Radius", &m_fRadius);

	
	std::string m_sEmitStr = pEmittor->Attribute("EmitBool");
	bool m_bEmitWay;
 
	if (m_sEmitStr == "True")
		m_bEmitWay = true;
	else if (m_sEmitStr == "False")
		m_bEmitWay = false; 

	double  m_fEmitTime;
	pEmittor->Attribute("EmitTime", &m_fEmitTime);

	double m_fPosX;
	pEmittor->Attribute("PosX", &m_fPosX);

	double m_fPosY;
	pEmittor->Attribute("PosY", &m_fPosY);

	double m_fWidth;
	pEmittor->Attribute("Width", &m_fWidth);

	double m_fHeight;
	pEmittor->Attribute("Height", &m_fHeight);

	SGD::Size emitterSize{ (float)m_fWidth, (float)m_fHeight };
	SGD::Point emitterPosition{ (float)m_fPosX, (float)m_fPosY };




	TiXmlElement* pFlyweight = pEmittor->NextSiblingElement();

	std::string   imageFilePath = "Resources/Graphics/Particles/";
	imageFilePath += pFlyweight->Attribute("Image");

	double m_fStartScaleX;
	double m_fStartScaleY;
	double m_fEndScaleX;
	double m_fEndScaleY;
	pFlyweight->Attribute("StartScaleX", &m_fStartScaleX);
	pFlyweight->Attribute("StartYScale", &m_fStartScaleY);
	pFlyweight->Attribute("EndXScale", &m_fEndScaleX);
	pFlyweight->Attribute("EndYScale", &m_fEndScaleY);

	SGD::Size m_sStartScale{ (float)m_fStartScaleX, (float)m_fStartScaleY };
	SGD::Size m_sEndScale{ (float)m_fEndScaleX, (float)m_fEndScaleY };

	int    startA;
	int    startR;
	int    startG;
	int    startB;
	int    endA;
	int    endR;
	int    endG;
	int    endB;

	pFlyweight->Attribute("StartColorA", &startA);
	pFlyweight->Attribute("StartColorR", &startR);
	pFlyweight->Attribute("StartColorG", &startG);
	pFlyweight->Attribute("StartColorB", &startB);
	pFlyweight->Attribute("EndColorA", &endA);
	pFlyweight->Attribute("EndColorR", &endR);
	pFlyweight->Attribute("EndColorG", &endG);
	pFlyweight->Attribute("EndColorB", &endB);

	double m_fSpeedMinX;
	double m_fSpeedMinY;
	double m_fSpeedMaxX;
	double m_fSpeedMaxY;
	pFlyweight->Attribute("SpeedMinX", &m_fSpeedMinX);
	pFlyweight->Attribute("SpeedMinY", &m_fSpeedMinY);
	pFlyweight->Attribute("SpeedMaxX", &m_fSpeedMaxX);
	pFlyweight->Attribute("SpeedMaxY", &m_fSpeedMaxY);

	SGD::Vector m_vSpeedMin{ (float)m_fSpeedMinX,(float)m_fSpeedMinY };
	SGD::Vector m_vSpeedMax{ (float)m_fSpeedMaxX, (float)m_fSpeedMaxY };

	double m_fMaxLife;
	double m_fMinLife;
	pFlyweight->Attribute("LifeMax", &m_fMaxLife);
	pFlyweight->Attribute("LifeMin", &m_fMinLife);

	double m_fRotationSpeed;
	pFlyweight->Attribute("RotationSpeed", &m_fRotationSpeed);

	double m_fInertia;
	pFlyweight->Attribute("Enertia", &m_fInertia);


	char * imageFile = new char[imageFilePath.size() + 1];

	std::copy(imageFilePath.begin(), imageFilePath.end(), imageFile);
	imageFile[imageFilePath.size()] = '\0';

	SGD::HTexture ParticleImage = SGD::GraphicsManager::GetInstance()->LoadTexture(imageFile);
	
	SGD::Vector ParticleImageOffset = SGD::GraphicsManager::GetInstance()->GetTextureData(ParticleImage)/2;

	delete[] imageFile;

	CFlyweight* eData = new CFlyweight(ParticleImage, m_sStartScale, m_sEndScale,
		ParticleImageOffset,
	startA, startR, startG, startB,
	endA, endR, endG, endB,
	(float)m_fMaxLife, (float)m_fMinLife,
	m_vSpeedMax,
	m_vSpeedMin,
	m_fInertia,
	m_fRotationSpeed);


	
	particleEffect[1] = new CEmitter(eData, emitterSize, m_nShape, emitterPosition, m_nNumParticles, m_fSpawnRate, m_fTimeFromLastSpawn, m_bEmitWay, m_fEmitTime);
	

}
