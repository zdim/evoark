#include "ParticleSystem.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../TinyXML/tinyxml.h"
#include <string>

CParticleSystem::CParticleSystem()
{
}


CParticleSystem::~CParticleSystem()
{
}

void CParticleSystem::Init()
{
	LoadEffect();	
	for (int i = 0; i < numEmitters ; i++ )
	particleEffect[i]->Initialize();
}

void CParticleSystem::Update(float dt)
{
	for (int i = 0; i < numEmitters; i++)
	particleEffect[i]->Update(dt);
}

void CParticleSystem::Render()
{
	for (int i = 0; i < numEmitters; i++)
	particleEffect[i]->Render();
}


void CParticleSystem::LoadEffect()
{
	TiXmlDocument doc;
	doc.LoadFile("test_save.xml");
	TiXmlElement* pRoot = doc.RootElement();
	

	TiXmlElement* pNumEmittors = pRoot->FirstChildElement();
	pNumEmittors->Attribute("Emittors", &numEmitters);

	//Possible loop creation here for multiple emittors 


	TiXmlElement* pEmittor = pNumEmittors->NextSiblingElement();

	//Temp variables for loading
	double emitW;
	double emitH;
	double emitX;
	double emitY;
	int m_nNumParticles;
	double m_fSpawnRate;
	double m_fTimeFromLastSpawn;
	int    m_nLoop;
	double  m_fEmitTime;


	pEmittor->Attribute("Width", &emitW);
	pEmittor->Attribute("Height", &emitH);
	pEmittor->Attribute("X", &emitX);
	pEmittor->Attribute("Y", &emitY);
	pEmittor->Attribute("NumParticals", &m_nNumParticles);
	pEmittor->Attribute("SpawnRate", &m_fSpawnRate);
	pEmittor->Attribute("TimeFromLastSpawn", &m_fTimeFromLastSpawn);
	pEmittor->Attribute("IsLoooping", &m_nLoop);
	pEmittor->Attribute("EmitTime", &m_fEmitTime);


	SGD::Size emitterSize { (float)emitW, (float)emitH };
	SGD::Point emitterPosition { (float)emitX, (float)emitY };


	//Temp variables for loading

	std::string   imageFilePath;
	double startScaleX;
	double startScaleY;
	double endScaleX;
	double endScaleY;
	int    widthOffset;
	int    heightOffset;
	int    startA;
	int    startR;
	int    startG;
	int    startB;
	int    endA;
	int    endR;
	int    endG;
	int    endB;
	double MaxLife;
	double MinLife;
	double SpeedX;
	double SpeedY;
	double Inertia;
	double RotationSpeed;


	TiXmlElement* pFlyweight = pEmittor->NextSiblingElement();
	imageFilePath = pFlyweight->Attribute("image");
	pFlyweight->Attribute("m_fStartScaleX", &startScaleX);
	pFlyweight->Attribute("m_fStartScaleY", &startScaleY);
	pFlyweight->Attribute("m_fEndScaleX", &endScaleX);
	pFlyweight->Attribute("m_fEndScaleY", &endScaleY);
	pFlyweight->Attribute("VectorOffsetWidth", &widthOffset);
	pFlyweight->Attribute("VectorOffsetHeight", &heightOffset);
	pFlyweight->Attribute("startA", &startA);
	pFlyweight->Attribute("startR", &startR);
	pFlyweight->Attribute("startG", &startG);
	pFlyweight->Attribute("startB", &startB);
	pFlyweight->Attribute("endA", &endA);
	pFlyweight->Attribute("endR", &endR);
	pFlyweight->Attribute("endG", &endG);
	pFlyweight->Attribute("endB", &endB);
	pFlyweight->Attribute("MaxLife", &MaxLife);
	pFlyweight->Attribute("MinLife", &MinLife);
	pFlyweight->Attribute("SpeedX", &SpeedX);
	pFlyweight->Attribute("SpeedY", &SpeedY);
	pFlyweight->Attribute("Inertia", &Inertia);
	pFlyweight->Attribute("RotationSpeed", &RotationSpeed);




	char * imageFile = new char[imageFilePath.size() + 1];
	std::copy(imageFilePath.begin(), imageFilePath.end(), imageFile);
	imageFile[imageFilePath.size()] = '\0';
	SGD::HTexture TestParticle = SGD::GraphicsManager::GetInstance()->LoadTexture(imageFile);
	delete[] imageFile;

	SGD::Size startScale { (float)startScaleX, (float)startScaleY };
	SGD::Size endScale{ (float)endScaleX, (float)endScaleY };
	SGD::Vector offsetImage{ widthOffset, heightOffset };
	SGD::Vector speed    { SpeedX, SpeedY };

	CFlyweight* eData = new CFlyweight(TestParticle, startScale, endScale,
	offsetImage,
	startA, startR, startG, startB,
	endA, endR, endG, endB,
	MaxLife, MinLife,
	speed,
	Inertia,
	RotationSpeed);


	for (int i = 0; i < numEmitters; i++)
		particleEffect[i] = new CEmitter(eData, emitterSize, emitterPosition, m_nNumParticles, m_fSpawnRate, m_fTimeFromLastSpawn, m_nLoop, m_fEmitTime);

}
void CParticleSystem::SaveEffect()
{
	TiXmlDocument doc;
	TiXmlElement* root = new TiXmlElement("root");
	doc.LinkEndChild(root);
	
	TiXmlElement* element1 = new TiXmlElement("NumParticals");
	root->LinkEndChild(element1);
	element1->SetAttribute("Emittors", "1");
	
	
	TiXmlElement* element2 = new TiXmlElement("Emittor");
	root->LinkEndChild(element2);
	element2->SetAttribute("Width", "270");
	element2->SetAttribute("Height", "155");
	element2->SetAttribute("X", "400");
	element2->SetAttribute("Y", "400");
	element2->SetAttribute("NumParticals", "400");
	element2->SetAttribute("SpawnRate", "0.5");
	element2->SetAttribute("TimeFromLastSpawn", "1,0");
	element2->SetAttribute("IsLoooping", "1");
	element2->SetAttribute("EmitTime", "0");
	
	TiXmlElement* element3 = new TiXmlElement("Flyweight");
	root->LinkEndChild(element3);
	element3->SetAttribute("image", "Resources/Graphics/test.png");
	element3->SetAttribute("m_fStartScaleX", "0.7");
	element3->SetAttribute("m_fStartScaleY", "0.7");
	element3->SetAttribute("m_fEndScaleX", "0.7");
	element3->SetAttribute("m_fEndScaleY", "0.7");
	element3->SetAttribute("VectorOffsetWidth", "128");
	element3->SetAttribute("VectorOffsetHeight", "128");
	element3->SetAttribute("startA", "255");
	element3->SetAttribute("startR", "255");
	element3->SetAttribute("startG", "0");
	element3->SetAttribute("startB", "0");
	element3->SetAttribute("endA", "255");
	element3->SetAttribute("endR", "127");
	element3->SetAttribute("endG", "0");
	element3->SetAttribute("endB", "0");
	element3->SetAttribute("MaxLife", "4");
	element3->SetAttribute("MinLife", "2");
	element3->SetAttribute("SpeedX", "0");
	element3->SetAttribute("SpeedY", "0");
	element3->SetAttribute("Inertia", "0");
	element3->SetAttribute("RotationSpeed", "3.14");

	doc.SaveFile("test_save.xml");
	doc.Clear();
	
}