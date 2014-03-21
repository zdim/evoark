using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace EvoArk_Particles_Editor
{

    class Size
    {
        public float Width { get; set; }
        public float Height { get; set; }

        public Size()
        {
        }

        public Size(float w, float h)
        {
            this.Width = w;
            this.Height = h;
        }

       
        public static Size operator *(Size s, float n)
        {
            return new Size(s.Width * n, s.Height * n);
        }

        public static Size operator +(Size s, float n)
        {
            return new Size(s.Width + n, s.Height + n);
        }

        //public static Size operator -(Size s, float n)
        //{
        //    return new Size(s.Width - n, s.Height - n);
        //}

        public static Size operator -(Size s, Size n)
        {
            Size tS = new Size(s.Width, s.Height);
            Size tN = new Size(n.Width, n.Height);
            return new Size(s.Width - n.Width, s.Height - n.Height);
           
        }

        public static Size operator +(Size s, Size n)
        {
            Size tS = new Size(s.Width, s.Height);
            Size tN = new Size(n.Width, n.Height);
            return new Size(s.Width + n.Width, s.Height + n.Height);

        }


    }

    class Point
    {
        public float X { get; set; }
        public float Y { get; set; }

        public Point()
        {
        }

        public Point(float x, float y)
        {
            this.X = x;
            this.Y = y;
        }


        public static Point operator *(Point p, float n)
        {
            return new Point(p.X * n, p.Y * n);
        }

        public static Point operator +(Point s, Point n)
        {
            Point tS = new Point(s.X, s.Y);
            Point tN = new Point(n.X, n.Y);
            return new Point(s.X + n.X, s.Y + n.Y);
        }

    }


    class Flyweight
    {
        int   m_nParticleImageID;
        Size StartScale;
        Size EndScale;
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
        Point StartSpeedMin;
        Point StartSpeedMax;
        Point EndSpeedMin;
        Point EndSppedMax;
		float Inertia;
        float RotationSpeed;


        public Point StartSMin
        {
            get { return StartSpeedMin; }
            set { StartSpeedMin = value; }
        }

        internal Point StartSMax
        {
            get { return StartSpeedMax; }
            set { StartSpeedMax = value; }
        }

        internal Point EndSMin
        {
            get { return EndSpeedMin; }
            set { EndSpeedMin = value; }
        }

        internal Point EndSMax
        {
            get { return EndSppedMax; }
            set { EndSppedMax = value; }
        }

        public int ParticleImage
        {
            get { return m_nParticleImageID; }
            set { m_nParticleImageID = value; }
        }

        public Size ParticleStartScale
        {
            get { return StartScale; }
            set { StartScale = value; }
        }

        public Size ParticleEndScale
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

        public Flyweight()
        { 
        }

        public Flyweight(

        int ParticleImageID,
        Size SScale,
        Size EScale,
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
		Point StartSMin,
        Point StartSMax,
        Point EndSMin,
        Point EndSMax,
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
            StartSpeedMin    = StartSMin;
            StartSpeedMax    = StartSMax;
            EndSpeedMin      = EndSMin;
            EndSppedMax      = EndSMax;
            Inertia          = inertia;
            RotationSpeed    = rotationSpeed; 
        }


    }
}
