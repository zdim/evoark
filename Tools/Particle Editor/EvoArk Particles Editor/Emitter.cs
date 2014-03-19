using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace EvoArk_Particles_Editor
{
    class Emitter
    {
        
	   List<Particle>      m_lAliveParticles;
	   List<Particle>      m_lDeadParticles;
	   Flyweight           particleData;
	   Point               emitterSize;
	   Point               emitterPosition;
	   int                 m_nNumParticles;
	   float               m_fSpawnRate;
	   float               m_fTimeFromLastSpawn;
	   bool                m_bLoop;
	   float               m_fEmitTime;

       System.Random r = new System.Random();


       public List<Particle> AliveParticles
       {
           get { return m_lAliveParticles; }
           set { m_lAliveParticles = value; }
       }

       public List<Particle> DeadParticles
       {
           get { return m_lDeadParticles; }
           set { m_lDeadParticles = value; }
       }

       public Flyweight  ParticlesData
       {
           get { return particleData; }
           set { particleData = value; }
       }

       public Point EmitterSize
       {
           get { return emitterSize; }
           set { emitterSize = value; }
       }

       public Point EmitterPosition
       {
           get { return emitterPosition; }
           set { emitterPosition = value; }
       }

       public int EmitterNumOfParticles 
       {
           get { return m_nNumParticles; }
           set { m_nNumParticles = value; }
       }

       public float EmitterSpawnRate
       {
           get { return m_fSpawnRate; }
           set { m_fSpawnRate = value; }
       }

       public float EmitterTimeFromLastSpawn
       {
           get { return m_fTimeFromLastSpawn; }
           set { m_fSpawnRate = value; }
       }

       public bool EmitterLooping
       {
           get { return m_bLoop; }
           set { m_bLoop = value; }
       }

       public float EmitterTime
       {
           get { return m_fEmitTime; }
           set { m_fEmitTime = value; }
       }

       public Emitter( List<Particle>      AliveParticles,
	            List<Particle>      DeadParticles,
	            Flyweight           pData,
	            Point               eSize,
	            Point               ePosition,
	            int                 NumParticles,
	            float               SpawnRate,
	            float               TimeFromLastSpawn,
	            bool                bLoop,
	            float               EmitTime
              )
       {
               m_lAliveParticles    = AliveParticles;
               m_lDeadParticles     = DeadParticles;
               particleData         = pData;
               emitterSize          = eSize;
               emitterPosition      = ePosition;
               m_nNumParticles      = NumParticles;
               m_fSpawnRate         = SpawnRate;
               m_fTimeFromLastSpawn = TimeFromLastSpawn;
               m_bLoop              = bLoop;
               m_fEmitTime          = EmitTime; 
       }

       public void Initialize()
       {
           for (int i = 0; i < m_nNumParticles; i++)
           {
               Particle emptyParticle = new Particle();
               m_lDeadParticles.Add(emptyParticle);
           }
       }

       public void Update(float deltaTime)
       {
           m_fTimeFromLastSpawn += deltaTime;
           m_fEmitTime -= deltaTime;

           if (m_fTimeFromLastSpawn >= m_fSpawnRate)
           {
               if (m_fEmitTime <= 0 && m_bLoop == false)
			           ;
               else
		       {
			        m_fTimeFromLastSpawn -= m_fSpawnRate;
                    Particle p = m_lDeadParticles[0];
                    //p = CreateParticle();
                    //m_lDeadParticles.pop_front();
                    //m_lAliveParticles.push_front(p);
		       }
           }


       }

       public void Render()
       {

       }
       
       //public Particle CreateParticle()
       //{
       //    Color tempColor = Color.FromArgb(particleData.ParticleStartA,
       //        particleData.ParticleStartA,
       //        particleData.ParticleStartA,
       //        particleData.ParticleStartA);
       //    double maxLife = particleData.ParticleMaxLife;
       //    double minLife = particleData.ParticleMinLife;
       //    double randLife = rnd(maxLife, minLife);

       //    Point tempParticlePosition = new Point(emitterPosition.X + r.Next(EmitterSize.X), emitterPosition.Y + r.Next(EmitterSize.Y));
          
       //}


       double rnd(double a, double b)
       {
           return a + r.NextDouble() * (b - a);
       }

    }
}
