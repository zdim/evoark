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
        int emittorShape = 1;
        Point emitterPos = new Point();



        Flyweight particleData = new Flyweight();
        Size startScale = new Size();
        Size endScale = new Size();
        Point SpeedMax = new Point();
        Point SpeedMin = new Point();


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

            startScale = new Size((float)StartMaxScale.Value, (float)StartMinScale.Value);
            endScale = new Size((float)EndMaxScale.Value, (float)EndMinScale.Value);







            Point RotationOffset = new Point ( m_TM.GetTextureWidth(m_nParticleImg)/2,m_TM.GetTextureHeight(m_nParticleImg)/2);
            SpeedMax = new Point((float)SpeedMinX.Value, (float)SpeedMinY.Value);
            SpeedMin = new Point((float)SpeedMaxX.Value, (float)SpeedMaxY.Value);
         

            particleData = new Flyweight(m_nParticleImg, startScale, endScale, RotationOffset, (int)StartColorA.Value, (int)StartColorR.Value, (int)StartColorG.Value, (int)StartColorB.Value,
                (int)EndColorA.Value, (int)EndColorR.Value, (int)EndColorG.Value, (int)EndColorB.Value,
                (float)LifeMax.Value, (float)LifeMin.Value, SpeedMax, SpeedMin, (float)Enertia.Value, (float)RotationSpeed.Value);


            emitterPos = new Point(200,200);


            emittor = new Emitter(particleData, emittorShape, emitterPos, (int)numericUpDown5.Value,
                (float)SpawnRate.Value, (float)EmissionRate.Value, BoolLoopBox.Checked, (float)EmissionTime.Value);

            UpdateControls();


           

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
                writer.WriteStartElement("ParticleEffect");

                writer.WriteStartElement("Emittor");
                writer.WriteAttributeString("NumOfParticles", emittor.EmitterNumOfParticles.ToString());
                writer.WriteAttributeString("SpawnRate", emittor.EmitterSpawnRate.ToString());
                writer.WriteAttributeString("TimeFromLastSpawn", emittor.EmitterTimeFromLastSpawn.ToString());
                writer.WriteAttributeString("Shape", emittor.NShape.ToString());
                writer.WriteAttributeString("Radius", emittor.FRadius.ToString());
                writer.WriteAttributeString("EmitBool", emittor.EmitterLooping.ToString());
                writer.WriteAttributeString("EmitTime", emittor.EmitterTime.ToString());
                writer.WriteEndElement();

                writer.WriteStartElement("Particle");
                writer.WriteStartAttribute("Image", m_nParticleImg.ToString());
                writer.WriteEndElement();

               

                writer.WriteEndElement();
            }
        }

        private void EmittorShapeButtonPoint_CheckedChanged(object sender, EventArgs e)
        {
           
            emittorShape = 1;
            ResetEmittor();
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
        }

        private void EmittorShapeButtonLine_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 2;
            ResetEmittor();
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
        }

        private void EmittorShapeButtonRect_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 3;
            ResetEmittor();
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
        }

        private void EmittorShapeButtonCircle_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 4;
            ResetEmittor();
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Visible = true;
            RadiusLabel.Visible = true;
            UpdateControls();
            
        }

        public void ResetEmittor()
        {
            emitterPos = new Point((float)EmittorPosX.Value, (float)EmittorPosY.Value);

            emittor = new Emitter(particleData, emittorShape, emitterPos, (int)numericUpDown5.Value,
                (float)SpawnRate.Value, (float)EmissionRate.Value, BoolLoopBox.Checked, (float)EmissionTime.Value);
            UpdateControls();
            emittor.Initialize();
        }

        public void ResetFlyweight()
        {
            
            Size endScale = new Size((float)EndMaxScale.Value, (float)EndMinScale.Value);

            Point RotationOffset = new Point(m_TM.GetTextureWidth(m_nParticleImg) / 2, m_TM.GetTextureHeight(m_nParticleImg) / 2);

            SpeedMax = new Point((float)SpeedMinX.Value, (float)SpeedMinY.Value);
            SpeedMin = new Point((float)SpeedMaxX.Value, (float)SpeedMaxY.Value);


            particleData = new Flyweight(m_nParticleImg, startScale, endScale, RotationOffset, (int)StartColorA.Value, (int)StartColorR.Value, (int)StartColorG.Value, (int)StartColorB.Value,
                (int)EndColorA.Value, (int)EndColorR.Value, (int)EndColorG.Value, (int)EndColorB.Value,
                (float)LifeMax.Value, (float)LifeMin.Value, SpeedMax, SpeedMin, (float)Enertia.Value, (float)RotationSpeed.Value);
        }


        private void numericUpDown5_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterNumOfParticles = (int)numericUpDown5.Value;
            ResetEmittor();
        }

        public void UpdateControls()
        {
            

            numericUpDown5.Value = emittor.EmitterNumOfParticles;
            SpawnRate.Value = (decimal)emittor.EmitterSpawnRate;
            EmissionRate.Value = (decimal)emittor.EmitterTimeFromLastSpawn;
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Value = (decimal)emittor.FRadius;
            EmissionTime.Value = (decimal)emittor.EmitterTime;
            EmittorPosX.Value = (int)emitterPos.X;
            EmittorPosY.Value = (int)emitterPos.Y;

            
        }

        private void SpawnRate_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterSpawnRate = (float)SpawnRate.Value;
            ResetEmittor();
        }

        private void EmissionRate_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterSpawnRate = (float)EmissionRate.Value;
            ResetEmittor();
        }

        private void EmittorWidth_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterSize.X = (int)EmittorWidth.Value;
            Point emitterSize = new Point((float)EmittorWidth.Value, emittor.EmitterSize.Y);
            emittor.EmitterSize = emitterSize;
        }

        private void EmittorHeight_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterSize.Y = (int)EmittorHeight.Value;
            Point emitterSize = new Point(emittor.EmitterSize.X, (float)EmittorHeight.Value);
            emittor.EmitterSize = emitterSize;
        }

        private void EmittorRadius_ValueChanged(object sender, EventArgs e)
        {
            emittor.FRadius = (float)EmittorRadius.Value;
        }

        private void BoolLoopBox_CheckedChanged(object sender, EventArgs e)
        {
            if (BoolLoopBox.Checked == true)
            {
                emittor.EmitterLooping = true;
                ResetEmittor();
            }    
            else if (BoolLoopBox.Checked == false )
            {
                emittor.EmitterLooping = false;
                ResetEmittor();
            }
        }

        private void EmissionTime_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterTime = (float)EmissionTime.Value;
            if(BoolLoopBox.Checked == false)
            ResetEmittor();
        }


        private void EmittorPosX_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterPosition.X = (int)EmittorPosX.Value;
            Point EmitterPosition = new Point((float)EmittorPosX.Value, emittor.EmitterPosition.Y);
            emittor.EmitterPosition = EmitterPosition;
        }

        private void EmittorPosY_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterPosition.Y = (int)EmittorPosY.Value;
            Point EmitterPosition = new Point(emittor.EmitterPosition.X, (float)EmittorPosY.Value);
            emittor.EmitterPosition = EmitterPosition;
        }

        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ResetEmittor();
            ResetFlyweight();
        }


        private void StartMaxScale_ValueChanged(object sender, EventArgs e)
        {
            startScale = new Size((float)StartMaxScale.Value, particleData.ParticleStartScale.Height);
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartMinScale_ValueChanged(object sender, EventArgs e)
        {
            startScale = new Size(particleData.ParticleStartScale.Width, (float)StartMinScale.Value);
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndMaxScale_ValueChanged(object sender, EventArgs e)
        {
            endScale = new Size((float)EndMaxScale.Value, particleData.ParticleEndScale.Height);
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndMinScale_ValueChanged(object sender, EventArgs e)
        {
            endScale = new Size(particleData.ParticleEndScale.Width, (float)StartMinScale.Value);
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartColorA_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleStartA = (int)StartColorA.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartColorR_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleStartR = (int)StartColorR.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartColorG_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleStartG = (int)StartColorG.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartColorB_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleStartB = (int)StartColorB.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndColorA_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleEndA = (int)EndColorA.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndColorR_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleEndR = (int)EndColorR.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndColorG_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleEndG = (int)EndColorG.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndColorB_ValueChanged(object sender, EventArgs e)
        {
            particleData.ParticleEndB = (int)EndColorB.Value;
            ResetFlyweight();
            ResetEmittor();
        }


        private void SpeedMinX_ValueChanged(object sender, EventArgs e)
        {
            particleData.PSpeedMin.X = (float)SpeedMinX.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void SpeedMinY_ValueChanged(object sender, EventArgs e)
        {
            particleData.PSpeedMin.Y = (float)SpeedMinY.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void SpeedMaxX_ValueChanged(object sender, EventArgs e)
        {
            particleData.PSpeedMax.X = (float)SpeedMaxX.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void SpeedMaxY_ValueChanged(object sender, EventArgs e)
        {
            particleData.PSpeedMax.Y = (float)SpeedMaxY.Value;
            ResetFlyweight();
            ResetEmittor();
        }

        private void LifeMax_ValueChanged(object sender, EventArgs e)
        {
            ResetFlyweight();
            ResetEmittor();
        }

        private void LifeMin_ValueChanged(object sender, EventArgs e)
        {
            ResetFlyweight();
            ResetEmittor();
        }

        private void RotationSpeed_ValueChanged(object sender, EventArgs e)
        {
            ResetFlyweight();
            ResetEmittor();
        }

        private void Enertia_ValueChanged(object sender, EventArgs e)
        {
            ResetFlyweight();
            ResetEmittor();
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            ResetFlyweight();
            ResetEmittor();
        }

  












    }
}
