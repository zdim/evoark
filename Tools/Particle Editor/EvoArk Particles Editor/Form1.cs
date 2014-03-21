using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SGP;
using System.IO;
using System.Xml;

namespace EvoArk_Particles_Editor
{
    public partial class Form1 : Form
    {
        SGP.CSGP_Direct3D m_D3D = null;
        SGP.CSGP_TextureManager m_TM = null;
        string szFilePath;
        bool looping = false;

        //Particle Image ID
        int m_nParticleImg;

        Emitter emittor = new Emitter();
        Flyweight particleData = new Flyweight();

        

        public bool Looping

        {
            get { return looping; }
            set { looping = value; }
        }

        public Form1()
        {
            InitializeComponent();

           

        }


        public void Initialize ( )
        {
            // Access the SGP Wrapper singletons
            m_D3D = SGP.CSGP_Direct3D.GetInstance();
            m_TM = SGP.CSGP_TextureManager.GetInstance();

            m_D3D.Initialize(panel1, false);
            m_TM.Initialize(m_D3D.Device, m_D3D.Sprite);

            m_nParticleImg = m_TM.LoadTexture("Particles/test.png");

            Size startScale = new Size(1.0f,1.0f);
            Size endScale = new Size(1.0f,1.0f);
            Point RotationOffset = new Point ( m_TM.GetTextureWidth(m_nParticleImg)/2,m_TM.GetTextureHeight(m_nParticleImg)/2);

            Point StartSpeedMax  = new Point (0.0f,0.0f);
            Point StartSpeedMin  = new Point( 0.0f,  0.0f);
            Point StartEndMax    = new Point( 0.0f,  0.0f);
            Point StartEndMin    = new Point( 0.0f,  0.0f);

            particleData = new Flyweight(m_nParticleImg, startScale, endScale, RotationOffset, 255, 0, 255, 0, 255, 127, 0, 0,
                10, 8,StartSpeedMin,StartSpeedMax,StartEndMin,StartEndMax, 0, 1);

            Point emitterSize = new Point(1,1);
            Point emitterPos = new Point(DirectXPanel.Width / 3, DirectXPanel.Height / 3);

            emittor = new Emitter(particleData, 1, emitterPos, 300, 1, 1.0f, true, 0);

            emittor.Initialize();
            


           looping = true;

        }

        public void Update (float dt)
        {
            emittor.Update(dt);
        }

        public void Render()
        {

            m_D3D.Clear(panel1, Color.White);

            m_D3D.DeviceBegin();
            m_D3D.SpriteBegin();

            emittor.Render();

            m_D3D.SpriteEnd();
            m_D3D.DeviceEnd();  
            m_D3D.Present();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }



        public Panel DirectXPanel { get { return panel1; } }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog opn = new OpenFileDialog();
            opn.DefaultExt = "png";
            opn.Filter = "Image files (*.png;*jpg;*bmp;)|*.png;*jpg;*bmp;";
            //opn.InitialDirectory = "../../../Resources/Graphics/";
            opn.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\..\\Resources\\Graphics");

            if (DialogResult.OK == opn.ShowDialog())
            {
                m_TM.UnloadTexture(m_nParticleImg);
                m_nParticleImg = (m_TM.LoadTexture(opn.FileName));
                particleData.ParticleOffset =  new Point ( m_TM.GetTextureWidth(m_nParticleImg)/2,m_TM.GetTextureHeight(m_nParticleImg)/2);
                particleData.ParticleImage = m_nParticleImg;
               
            }
        }



        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (null == szFilePath)
            {
                SaveFileDialog save = new SaveFileDialog();
                save.DefaultExt = "xml";
                save.Filter = "Xml Files (*.xml)|*.xml|All Files (*.*)|*.*";
                save.FilterIndex = 1;

                if (DialogResult.OK == save.ShowDialog())
                {
                    szFilePath = save.FileName;
                }
                else
                    return;
            }

            SaveXML();
        }


        private void SaveXML()
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.ConformanceLevel = ConformanceLevel.Document;
            settings.Indent = true;

            using (XmlWriter writer = XmlWriter.Create(szFilePath, settings))
            {
                writer.WriteStartElement("Emitter");

                writer.WriteStartElement("Dimensions");
                writer.WriteAttributeString("Width", emittor.EmitterSize.X.ToString());
                writer.WriteAttributeString("Height", emittor.EmitterSize.X.ToString());
                writer.WriteEndElement();

                writer.WriteStartElement("Particles");
                writer.WriteAttributeString("Amount", emittor.EmitterNumOfParticles.ToString());
                writer.WriteAttributeString("SpawnRate", emittor.EmitterSpawnRate.ToString());

                writer.WriteEndElement();
            }
        }


    }
}
