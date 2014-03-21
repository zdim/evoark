using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Microsoft.DirectX.Direct3D;


namespace EvoArk_Particles_Editor
{
    class Particle
    {
        Color curColor;
        Point curPosition;
        Point curSpeed;
        Point EndSpeed;
        Size curScale;
        float m_fCurLife;


        internal Point EndS
        {
            get { return EndSpeed; }
            set { EndSpeed = value; }
        }

        public float FCurLife
        {
            get { return m_fCurLife; }
            set { m_fCurLife = value; }
        }
        float m_fRotation;

        public float FRotation
        {
            get { return m_fRotation; }
            set { m_fRotation = value; }
        }


        public Color ParticleColor
        {
            get { return curColor; }
            set { curColor = value; }
        }

        public Point ParticlePositon
        {
            get { return curPosition; }
            set { curPosition = value; }
        }

        public Point ParticleSpeed
        {
            get { return curSpeed; }
            set { curSpeed = value; }
        }

        public Size ParticleScale
        {
            get { return  curScale; }
            set { curScale = value; }
        }




        public Particle()
        { }

        public Particle (
            Color cColor,
            Point cPosition,
            Point cSpeed,
            Point ESpeed,
            Size cScale,
            float curLife,
            float Rotation 
            )
    {
        curColor    = cColor;
        curPosition = cPosition;  
        curSpeed    = cSpeed;
        EndSpeed    = ESpeed;
        curScale    = cScale;
        m_fCurLife  = curLife;
        m_fRotation = Rotation;
    }


    }
}
