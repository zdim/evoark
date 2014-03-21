using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;
using SGP;

namespace EvoArk_Particles_Editor
{
    class Emitter
    {

        CSGP_Direct3D D3D = CSGP_Direct3D.GetInstance();
        CSGP_TextureManager TM = CSGP_TextureManager.GetInstance();
        Form1 mainForm;

        List<Particle> m_lAliveParticles = new List<Particle>();
        List<Particle> m_lDeadParticles = new List<Particle>();

        Flyweight particleData = new Flyweight();

        Point emitterSize = new Point();
        Point emitterPosition = new Point();
        int m_nNumParticles = new int();
        float m_fSpawnRate = new float();
        float m_fTimeFromLastSpawn = new float();
        bool  m_bLoop = new bool();
        float m_fEmitTime = new float();
        int m_nShape = new int();
        float m_fRadius = new float();

        public float FRadius
        {
            get { return m_fRadius; }
            set { m_fRadius = value; }
        }


        public int NShape
        {
            get { return m_nShape; }
            set { m_nShape = value; }
        }

        System.Random r =  new Random(Guid.NewGuid().GetHashCode());


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

        public Flyweight ParticlesData
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


        public Emitter()
        {

        }

        public Emitter(
                 Flyweight pData,
                 int Shape,
                 Point ePosition,
                 int NumParticles,
                 float SpawnRate,
                 float TimeFromLastSpawn,
                 bool bLoop,
                 float EmitTime
               )
        {
            m_lAliveParticles = AliveParticles;
            m_lDeadParticles = DeadParticles;
            particleData = pData;
            m_nShape = Shape;

            switch (Shape)
            {
                case 1:
                    emitterSize = new Point(1, 1);
                    break;
                case 2:
                    emitterSize = new Point(100, 1);
                    break;
                case 3:
                    emitterSize = new Point(100, 100);
                    break;
                case 4:
                    emitterSize = new Point(100, 200);
                    break; 
                default:
                    emitterSize = new Point(1, 1);
                    break;
            }

            emitterPosition = ePosition;
            m_nNumParticles = NumParticles;
            m_fSpawnRate = SpawnRate;
            m_fTimeFromLastSpawn = TimeFromLastSpawn;
            m_bLoop = bLoop;
            m_fEmitTime = EmitTime;
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
                if (m_fEmitTime <= 0 && m_bLoop == false && m_lDeadParticles.Count == 0)
                    ;
                else if (m_lDeadParticles.Count == 0)
                    ;
                else
                {
                    m_fTimeFromLastSpawn -= m_fSpawnRate;
                    Particle p = m_lDeadParticles[0];
                    p = CreateParticle();
                    m_lDeadParticles.RemoveAt(0);
                    m_lAliveParticles.Insert(0, p);
                }
            }

            for (int i = 0; i < m_lAliveParticles.Count; ++i)
            {
                //Checking for the particle death 
                m_lAliveParticles[i].FCurLife = m_lAliveParticles[i].FCurLife - deltaTime;
                if (m_lAliveParticles[i].FCurLife < 0)
                    m_lAliveParticles[i].FCurLife = 0;

                // Inertia Change
                if (m_lAliveParticles[i].ParticleSpeed.X > 0)
                {
                    m_lAliveParticles[i].ParticleSpeed.X -= particleData.ParticleInertia;
                    if (m_lAliveParticles[i].ParticleSpeed.X < 0)
                        m_lAliveParticles[i].ParticleSpeed.X = 0;
                }
                else if (m_lAliveParticles[i].ParticleSpeed.X < 0)
                {
                    m_lAliveParticles[i].ParticleSpeed.X += particleData.ParticleInertia;
                    if (m_lAliveParticles[i].ParticleSpeed.X > 0)
                        m_lAliveParticles[i].ParticleSpeed.X = 0;
                }

                if (m_lAliveParticles[i].ParticleSpeed.Y > 0)
                {
                    m_lAliveParticles[i].ParticleSpeed.Y -= particleData.ParticleInertia;
                    if (m_lAliveParticles[i].ParticleSpeed.Y < 0)
                        m_lAliveParticles[i].ParticleSpeed.Y = 0;
                }
                else if (m_lAliveParticles[i].ParticleSpeed.Y < 0)
                {
                    m_lAliveParticles[i].ParticleSpeed.Y += particleData.ParticleInertia;
                    if (m_lAliveParticles[i].ParticleSpeed.Y > 0)
                        m_lAliveParticles[i].ParticleSpeed.Y = 0;
                }


                //Life of the particle 
                float fLifeCycle = m_lAliveParticles[i].FCurLife / particleData.ParticleMaxLife;
            
                //Speed Change 

                float ParticleSpeedX = m_lAliveParticles[i].ParticleSpeed.X;
                float ParticleSpeedY = m_lAliveParticles[i].ParticleSpeed.Y;

                ParticleSpeedX = (m_lAliveParticles[i].EndS.X - particleData.StartSMax.X) * fLifeCycle;
                ParticleSpeedY = (m_lAliveParticles[i].EndS.Y - particleData.StartSMax.Y) * fLifeCycle;

                m_lAliveParticles[i].ParticleSpeed = new Point(ParticleSpeedX, ParticleSpeedY);


                m_lAliveParticles[i].ParticlePositon = m_lAliveParticles[i].ParticlePositon + m_lAliveParticles[i].ParticleSpeed * deltaTime;



                // Color Change 
                float A = particleData.ParticleEndA + fLifeCycle * (particleData.ParticleStartA - particleData.ParticleEndA);
                float R = particleData.ParticleEndR + fLifeCycle * (particleData.ParticleStartR - particleData.ParticleEndR);
                float G = particleData.ParticleEndG + fLifeCycle * (particleData.ParticleStartG - particleData.ParticleEndG);
                float B = particleData.ParticleEndB + fLifeCycle * (particleData.ParticleStartB - particleData.ParticleEndB);

                if (A < 0) { A = 0; }
                else if (A > 255) { A = 255; }
                if (R > 255) { R = 255; }
                else if (R < 0) { R = 0; }
                if (G > 255) { G = 255; }
                else if (G < 0) { G = 0; }
                if (B > 255) { B = 255; }
                else if (B < 0) { B = 0; }

                m_lAliveParticles[i].ParticleColor = Color.FromArgb((int)A, (int)R, (int)G, (int)B);



                //Change Scale 
                if (particleData.ParticleStartScale != particleData.ParticleEndScale)
                    m_lAliveParticles[i].ParticleScale = particleData.ParticleEndScale + (particleData.ParticleStartScale - particleData.ParticleEndScale) * fLifeCycle;

                m_lAliveParticles[i].FRotation = m_lAliveParticles[i].FRotation + (particleData.ParticleRotationSpeed / 2 * deltaTime);

                // killing dead particles 
                if (m_lAliveParticles[i].FCurLife <= 0)
                {
                    m_lDeadParticles.Add(m_lAliveParticles[i]);
                    m_lAliveParticles.RemoveAt(i);
                }


            }


        }

        public void Render()
        {
            for (int i = 0; i < m_lAliveParticles.Count; ++i)
            {
                TM.Draw(particleData.ParticleImage,
                    (int)m_lAliveParticles[i].ParticlePositon.X,
                    (int)m_lAliveParticles[i].ParticlePositon.Y,
                    m_lAliveParticles[i].ParticleScale.Width,
                    m_lAliveParticles[i].ParticleScale.Height,
                    Rectangle.Empty,
                    particleData.ParticleOffset.X * m_lAliveParticles[i].ParticleScale.Width ,
                    particleData.ParticleOffset.Y * m_lAliveParticles[i].ParticleScale.Height,
                    m_lAliveParticles[i].FRotation,
                    m_lAliveParticles[i].ParticleColor
                    );

            }
        }

        public Particle CreateParticle()
        {
            Color tempColor = Color.FromArgb(particleData.ParticleStartA,
                particleData.ParticleStartA,
                particleData.ParticleStartA,
                particleData.ParticleStartA);

            float maxLife = particleData.ParticleMaxLife;
            float minLife = particleData.ParticleMinLife;
            float randLife = RandomFloat(maxLife, minLife);        

            float startSMaxX = particleData.StartSMax.X;
            float startSMinX = ParticlesData.StartSMin.X;
            float startSX = 0;
            if( startSMinX != startSMaxX )
               startSX = RandomFloat(startSMaxX, startSMinX);

            float startSMaxY = particleData.StartSMax.Y;
            float startSMinY = ParticlesData.StartSMin.Y;
            float startSY = 0;
            if (startSMinY != startSMaxY)
                startSY = RandomFloat(startSMaxY, startSMinY);

            Point startSpeed = new Point(startSX,startSY);


            float endSMaxX = particleData.EndSMax.X;
            float endSMinX = ParticlesData.EndSMin.X;
            float endSX = 0;
            if (endSMinX != endSMaxX)
                endSX = RandomFloat(endSMaxX, endSMinX);

            float endSMaxY = particleData.EndSMax.Y;
            float endSMinY = ParticlesData.EndSMin.Y;
            float endSY = 0;
            if (endSMinY != endSMaxY)
                endSY = RandomFloat(endSMaxY, endSMinY);

            Point EndSpeed = new Point(endSX, endSY);

            Size tScale = particleData.ParticleStartScale;
            float rot = 0;

            Point tempParticlePosition = new Point();

            
            if(m_nShape == 1 || m_nShape == 2 || m_nShape == 3 )
            tempParticlePosition = new Point(emitterPosition.X + r.Next((int)EmitterSize.X/2), emitterPosition.Y + r.Next((int)EmitterSize.Y/2));

            if(m_nShape == 4 )
            {
                tempParticlePosition = new Point(emitterPosition.X + r.Next((int)EmitterSize.X/2), emitterPosition.Y + r.Next((int)EmitterSize.Y/2));
                m_fRadius = emitterSize.X / 2;
                Point EmitterCenter = new Point( EmitterPosition.X + emitterSize.X/2
                    , emitterPosition.X + emitterSize.X/2 );

                double Distance = Math.Sqrt((double)(EmitterCenter.X - tempParticlePosition.X) * (EmitterCenter.X - tempParticlePosition.X) +
                                                    (EmitterCenter.Y - tempParticlePosition.Y) * (EmitterCenter.Y - tempParticlePosition.Y));

                do
                {
                    tempParticlePosition = new Point(emitterPosition.X + r.Next((int)EmitterSize.X), emitterPosition.Y + r.Next((int)EmitterSize.Y));
                    Distance = Math.Sqrt((double)(EmitterCenter.X - tempParticlePosition.X) * (EmitterCenter.X - tempParticlePosition.X) +
                                                    (EmitterCenter.Y - tempParticlePosition.Y) * (EmitterCenter.Y - tempParticlePosition.Y));
                } while ((float)Distance >= m_fRadius);
            }

            Particle tempP = new Particle(tempColor, tempParticlePosition, startSpeed,EndSpeed, tScale, (float)randLife, rot);

            return tempP;
        }


        float RandomFloat(float max, float min)
        {
            return (max - min) * (float)r.NextDouble() + min;
        }

    }
}
