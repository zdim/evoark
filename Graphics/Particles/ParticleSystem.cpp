#include "ParticleSystem.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_HandleManager.h"
#include "../../TinyXML/tinyxml.h"
#include <string>

CParticleSystem::CParticleSystem()
{
	numEmitters = 2;
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

	std::string   imageFilePath = "Resources/Graphics/";
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
	imageFilePath += pFlyweight->Attribute("image");
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
	
	//TestParticle

	delete[] imageFile;

	SGD::Size startScale { (float)startScaleX, (float)startScaleY };
	SGD::Size endScale{ (float)endScaleX, (float)endScaleY };
	SGD::Vector offsetImage = SGD::GraphicsManager::GetInstance()->GetTextureData(TestParticle)/2;
	SGD::Vector speed    { SpeedX, SpeedY };
	SGD::Vector speedend    { 0, 0 };

	CFlyweight* eData = new CFlyweight(TestParticle, startScale, endScale,
	offsetImage,
	startA, startR, startG, startB,
	endA, endR, endG, endB,
	MaxLife, MinLife,
	speed,
	speedend,
	Inertia,
	RotationSpeed);




	TiXmlDocument doc2;
	doc.LoadFile("test_save2.xml");
	TiXmlElement* pRoot2 = doc.RootElement();


	TiXmlElement* pNumEmittors2 = pRoot2->FirstChildElement();
	pNumEmittors2->Attribute("Emittors", &numEmitters);

	//Possible loop creation here for multiple emittors 


	TiXmlElement* pEmittor2 = pNumEmittors2->NextSiblingElement();

	//Temp variables for loading
	double emitW2;
	double emitH2;
	double emitX2;
	double emitY2;
	int m_nNumParticles2;
	double m_fSpawnRate2;
	double m_fTimeFromLastSpawn2;
	int    m_nLoop2;
	double  m_fEmitTime2;


	pEmittor2->Attribute("Width", &emitW2);
	pEmittor2->Attribute("Height", &emitH2);
	pEmittor2->Attribute("X", &emitX2);
	pEmittor2->Attribute("Y", &emitY2);
	pEmittor2->Attribute("NumParticals", &m_nNumParticles2);
	pEmittor2->Attribute("SpawnRate", &m_fSpawnRate2);
	pEmittor2->Attribute("TimeFromLastSpawn", &m_fTimeFromLastSpawn2);
	pEmittor2->Attribute("IsLoooping", &m_nLoop2);
	pEmittor2->Attribute("EmitTime", &m_fEmitTime2);


	SGD::Size emitterSize2{ (float)emitW2, (float)emitH2 };
	SGD::Point emitterPosition2{ (float)emitX2, (float)emitY2 };


	//Temp variables for loading

	std::string   imageFilePath2 = "Resources/Graphics/";
	double startScaleX2;
	double startScaleY2;
	double endScaleX2;
	double endScaleY2;
	int    widthOffset2;
	int    heightOffset2;
	int    startA2;
	int    startR2;
	int    startG2;
	int    startB2;
	int    endA2;
	int    endR2;
	int    endG2;
	int    endB2;
	double MaxLife2;
	double MinLife2;
	double SpeedX2;
	double SpeedY2;
	double Inertia2;
	double RotationSpeed2;


	TiXmlElement* pFlyweight2 = pEmittor2->NextSiblingElement();
	imageFilePath2 += pFlyweight2->Attribute("image");
	pFlyweight2->Attribute("m_fStartScaleX", &startScaleX2);
	pFlyweight2->Attribute("m_fStartScaleY", &startScaleY2);
	pFlyweight2->Attribute("m_fEndScaleX", &endScaleX2);
	pFlyweight2->Attribute("m_fEndScaleY", &endScaleY2);
	pFlyweight2->Attribute("VectorOffsetWidth", &widthOffset2);
	pFlyweight2->Attribute("VectorOffsetHeight", &heightOffset2);
	pFlyweight2->Attribute("startA", &startA2);
	pFlyweight2->Attribute("startR", &startR2);
	pFlyweight2->Attribute("startG", &startG2);
	pFlyweight2->Attribute("startB", &startB2);
	pFlyweight2->Attribute("endA", &endA2);
	pFlyweight2->Attribute("endR", &endR2);
	pFlyweight2->Attribute("endG", &endG2);
	pFlyweight2->Attribute("endB", &endB2);
	pFlyweight2->Attribute("MaxLife", &MaxLife2);
	pFlyweight2->Attribute("MinLife", &MinLife2);
	pFlyweight2->Attribute("SpeedX", &SpeedX2);
	pFlyweight2->Attribute("SpeedY", &SpeedY2);
	pFlyweight2->Attribute("Inertia", &Inertia2);
	pFlyweight2->Attribute("RotationSpeed", &RotationSpeed2);




	char * imageFile2 = new char[imageFilePath.size() + 1];

	std::copy(imageFilePath.begin(), imageFilePath.end(), imageFile2);
	imageFile2[imageFilePath.size()] = '\0';

	SGD::HTexture TestParticle2 = SGD::GraphicsManager::GetInstance()->LoadTexture(imageFile2);

	//TestParticle

	delete[] imageFile2;

	SGD::Size startScale2{ (float)startScaleX2, (float)startScaleY2 };
	SGD::Size endScale2{ (float)endScaleX2, (float)endScaleY2 };
	SGD::Vector offsetImage2 = SGD::GraphicsManager::GetInstance()->GetTextureData(TestParticle2) / 2;
	SGD::Vector speed2{ SpeedX2, SpeedY2 };
	SGD::Vector speedend2{ 0, 0 };

	CFlyweight* eData2 = new CFlyweight(TestParticle2, startScale2, endScale2,
		offsetImage2,
		startA2, startR2, startG2, startB2,
		endA2, endR2, endG2, endB2,
		MaxLife2, MinLife2,
		speed2,
		speedend2,
		Inertia2,
		RotationSpeed2);

	
		particleEffect[0] = new CEmitter(eData, emitterSize, emitterPosition, m_nNumParticles, m_fSpawnRate, m_fTimeFromLastSpawn, m_nLoop, m_fEmitTime);
		particleEffect[1] = new CEmitter(eData2, emitterSize2, emitterPosition2, m_nNumParticles2, m_fSpawnRate2, m_fTimeFromLastSpawn2, m_nLoop2, m_fEmitTime2);

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