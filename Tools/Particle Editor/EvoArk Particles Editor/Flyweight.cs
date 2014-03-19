using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace EvoArk_Particles_Editor
{
    class Flyweight
    {
        int   m_nParticleImageID;
		Point StartScale;
        Point EndScale;
		Point rOffset;
		int sA;
		int sR;
		int sG;
		int sB;
		int eA;
		int eR;
		int eG;
		int eB;
		float MaxLife; 
        float MinLife;
		Point s;
		float Inertia;
        float RotationSpeed;

        public int ParticleImage
        {
            get { return m_nParticleImageID; }
            set { m_nParticleImageID = value; }
        }

        public Point ParticleStartScale
        {
            get { return StartScale; }
            set { StartScale = value; }
        }

        public Point ParticleEndScale
        {
            get { return EndScale; }
            set { EndScale = value; }
        }

        public Point ParticleOffset
        {
            get { return rOffset; }
            set { rOffset = value; }
        }

        public int ParticleStartA
        {
            get { return sA; }
            set { sA = value; }
        }

        public int ParticleStartR
        {
            get { return sR; }
            set { sR = value; }
        }

        public int ParticleStartG
        {
            get { return sG; }
            set { sG = value; }
        }

        public int ParticleStartB
        {
            get { return sB; }
            set { sB = value; }
        }

        public int ParticleEndA
        {
            get { return eA; }
            set { eA = value; }
        }

        public int ParticleEndR
        {
            get { return eR; }
            set { eR = value; }
        }

        public int ParticleEndG
        {
            get { return eG; }
            set { eG = value; }
        }

        public int ParticleEndB
        {
            get { return eB; }
            set { eB = value; }
        }

        public float ParticleMaxLife
        {
            get { return MaxLife; }
            set { MaxLife = value; }
        }

        int x;

    
        public float ParticleMinLife
        {
            get { return MinLife; }
            set { MinLife = value; }
        }

        public Point ParticleSpeed
        {
            get { return s; }
            set { s = value; }
        }

        public float ParticleInertia
        {
            get { return Inertia; }
            set { Inertia = value; }
        }

        public float ParticleRotationSpeed
        {
            get { return RotationSpeed; }
            set { RotationSpeed = value; }
        }


        public Flyweight(

        int ParticleImageID,
		Point SScale,
        Point EScale,
		Point Offset,
		int A,
		int R,
		int G,
		int B,
		int eAc,
		int eRc,
		int eGc,
		int eBc,
		float maxLife, 
        float minLife,
		Point speed,
		float inertia,
        float rotationSpeed
        )
        {
            m_nParticleImageID = ParticleImageID;
            StartScale       = SScale;
            EndScale         = EScale;
            rOffset          = Offset;
            sA                 =A;
            sR                 =R;
            sG                 =G;
            sB                 =B;
            eA                 =eAc;
            eR                 =eRc;
            eG                 =eGc;
            eB                 =eBc;
            MaxLife          = maxLife;
            MinLife          = minLife;
            s                = speed;
            Inertia          = inertia;
            RotationSpeed    = rotationSpeed; 
        }


    }
}
