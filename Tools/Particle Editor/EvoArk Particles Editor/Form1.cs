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
        string ImgPath;

        Emitter emittor = new Emitter();
        int emittorShape = 1;
        Point emitterPos = new Point();
        Point emitterSize = new Point();


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


        public void Initialize()
        {
            // Access the SGP Wrapper singletons
            m_D3D = SGP.CSGP_Direct3D.GetInstance();
            m_TM = SGP.CSGP_TextureManager.GetInstance();

            m_D3D.Initialize(panel1, false);
            m_TM.Initialize(m_D3D.Device, m_D3D.Sprite);

            m_nParticleImg = m_TM.LoadTexture("Particles/test.png");

            ImgPath = Path.GetFileName("Particles/test.png");

            startScale = new Size((float)StartXScale.Value, (float)StartYScale.Value);
            endScale = new Size((float)EndXScale.Value, (float)EndYScale.Value);







            Point RotationOffset = new Point(m_TM.GetTextureWidth(m_nParticleImg) / 2, m_TM.GetTextureHeight(m_nParticleImg) / 2);
            SpeedMax = new Point((float)SpeedMinX.Value, (float)SpeedMinY.Value);
            SpeedMin = new Point((float)SpeedMaxX.Value, (float)SpeedMaxY.Value);


            particleData = new Flyweight(m_nParticleImg, startScale, endScale, RotationOffset, (int)StartColorA.Value, (int)StartColorR.Value, (int)StartColorG.Value, (int)StartColorB.Value,
                (int)EndColorA.Value, (int)EndColorR.Value, (int)EndColorG.Value, (int)EndColorB.Value,
                (float)LifeMax.Value, (float)LifeMin.Value, SpeedMax, SpeedMin, (float)Enertia.Value, (float)RotationSpeed.Value);

            emitterPos = new Point(200, 200);
            emitterSize = new Point((float)EmittorWidth.Value, (float)EmittorHeight.Value);


            emittor = new Emitter(particleData, emittorShape, emitterSize, emitterPos, (int)NumParticles.Value,
                (float)SpawnRate.Value, (float)EmissionRate.Value, BoolLoopBox.Checked, (float)EmissionTime.Value);

            UpdateControls();




            emittor.Initialize();



            looping = true;

        }

        public void Update(float dt)
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

       


        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
                SaveFileDialog save = new SaveFileDialog();
                save.DefaultExt = "xml";
                save.Filter = "Xml Files (*.xml)|*.xml|All Files (*.*)|*.*";
                save.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\..\\Resources\\XML\\ParticleEffects");
                save.FilterIndex = 1;

                if (DialogResult.OK == save.ShowDialog())
                {
                    szFilePath = save.FileName;
                }
                else
                    return;
            

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
                writer.WriteAttributeString("NumOfParticles", NumParticles.Value.ToString());
                writer.WriteAttributeString("SpawnRate", SpawnRate.Value.ToString());
                writer.WriteAttributeString("TimeFromLastSpawn", EmissionRate.Value.ToString());
                writer.WriteAttributeString("Shape", emittor.NShape.ToString());
                writer.WriteAttributeString("Radius", EmittorRadius.Value.ToString());
                writer.WriteAttributeString("EmitBool", BoolLoopBox.Checked.ToString());
                writer.WriteAttributeString("EmitTime", EmissionTime.Value.ToString());
                writer.WriteAttributeString("PosX", emittor.EmitterPosition.X.ToString());
                writer.WriteAttributeString("PosY", emittor.EmitterPosition.Y.ToString());
                writer.WriteAttributeString("Width", EmittorWidth.Value.ToString());
                writer.WriteAttributeString("Height", EmittorHeight.Value.ToString());
                writer.WriteEndElement();

                writer.WriteStartElement("Particle");
                writer.WriteAttributeString("Image", ImgPath);
                writer.WriteAttributeString("StartScaleX", StartXScale.Value.ToString());
                writer.WriteAttributeString("StartYScale", StartYScale.Value.ToString());
                writer.WriteAttributeString("EndXScale", EndXScale.Value.ToString());
                writer.WriteAttributeString("EndYScale", EndYScale.Value.ToString());
                writer.WriteAttributeString("StartColorA", StartColorA.Value.ToString());
                writer.WriteAttributeString("StartColorR", StartColorR.Value.ToString());
                writer.WriteAttributeString("StartColorG", StartColorG.Value.ToString());
                writer.WriteAttributeString("StartColorB", StartColorB.Value.ToString());
                writer.WriteAttributeString("EndColorA", EndColorA.Value.ToString());
                writer.WriteAttributeString("EndColorR", EndColorR.Value.ToString());
                writer.WriteAttributeString("EndColorG", EndColorG.Value.ToString());
                writer.WriteAttributeString("EndColorB", EndColorB.Value.ToString());
                writer.WriteAttributeString("SpeedMinX", SpeedMinX.Value.ToString());
                writer.WriteAttributeString("SpeedMinY", SpeedMinY.Value.ToString());
                writer.WriteAttributeString("SpeedMaxX", SpeedMinX.Value.ToString());
                writer.WriteAttributeString("SpeedMaxY", SpeedMinY.Value.ToString());
                writer.WriteAttributeString("LifeMax", LifeMax.Value.ToString());
                writer.WriteAttributeString("LifeMin", LifeMin.Value.ToString());
                writer.WriteAttributeString("RotationSpeed", RotationSpeed.Value.ToString());
                writer.WriteAttributeString("Enertia", Enertia.Value.ToString());
                writer.WriteEndElement();



                writer.WriteEndElement();
            }
        }

           //switch (Shape)
           // {
           //     case 1:
           //         emitterSize = new Point(1, 1);
           //         break;
           //     case 2:
           //         emitterSize = new Point(100, 1);
           //         break;
           //     case 3:
           //         emitterSize = new Point(100, 100);
           //         break;
           //     case 4:
           //         emitterSize = new Point(100, 200);
           //         m_fRadius = emitterSize.X / 2;
           //         break; 
           // }

        private void EmittorShapeButtonPoint_CheckedChanged(object sender, EventArgs e)
        {

            emittorShape = 1;
            EmittorWidth.Value = 1;
            EmittorHeight.Value = 1;
            emitterSize = new Point(1, 1);
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
            ResetEmittor();
        }

        private void EmittorShapeButtonLine_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 2;
            EmittorWidth.Value = 100;
            EmittorHeight.Value = 1;
            emitterSize = new Point(100, 1);
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
            ResetEmittor();
        }

        private void EmittorShapeButtonRect_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 3;
            EmittorWidth.Value = 100;
            EmittorHeight.Value = 100;
            emitterSize = new Point(100, 100);
            EmittorRadius.Visible = false;
            RadiusLabel.Visible = false;
            ResetEmittor();
        }

        private void EmittorShapeButtonCircle_CheckedChanged(object sender, EventArgs e)
        {
            emittorShape = 4;

            EmittorWidth.Value = 100;
            EmittorHeight.Value = 200;
            emitterSize = new Point(100, 200);
            EmittorRadius.Value = (decimal)((float)EmittorWidth.Value / 2);
            EmittorRadius.Visible = true;
            RadiusLabel.Visible = true;
            ResetEmittor();

        }

        public void ResetEmittor()
        {
            emittor = new Emitter(particleData, emittorShape, emitterSize, emitterPos, (int)NumParticles.Value,
                (float)SpawnRate.Value, (float)EmissionRate.Value, BoolLoopBox.Checked, (float)EmissionTime.Value);
            emittor.FRadius = (float)EmittorRadius.Value;
            UpdateControls();
            emittor.Initialize();
        }

        public void ResetFlyweight()
        {

            Size endScale = new Size((float)EndXScale.Value, (float)EndYScale.Value);

            Point RotationOffset = new Point(m_TM.GetTextureWidth(m_nParticleImg) / 2, m_TM.GetTextureHeight(m_nParticleImg) / 2);

            SpeedMax = new Point((float)SpeedMinX.Value, (float)SpeedMinY.Value);
            SpeedMin = new Point((float)SpeedMaxX.Value, (float)SpeedMaxY.Value);


            particleData = new Flyweight(m_nParticleImg, startScale, endScale, RotationOffset, (int)StartColorA.Value, (int)StartColorR.Value, (int)StartColorG.Value, (int)StartColorB.Value,
                (int)EndColorA.Value, (int)EndColorR.Value, (int)EndColorG.Value, (int)EndColorB.Value,
                (float)LifeMax.Value, (float)LifeMin.Value, SpeedMax, SpeedMin, (float)Enertia.Value, (float)RotationSpeed.Value);
        }


        private void numericUpDown5_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterNumOfParticles = (int)NumParticles.Value;
            ResetEmittor();
        }

        public void UpdateControls()
        {


            NumParticles.Value = emittor.EmitterNumOfParticles;
            SpawnRate.Value = (decimal)emittor.EmitterSpawnRate;
            EmissionRate.Value = (decimal)emittor.EmitterTimeFromLastSpawn;
            EmittorWidth.Value = (int)emittor.EmitterSize.X;
            EmittorHeight.Value = (int)emittor.EmitterSize.Y;
            EmittorRadius.Value = (decimal)emittor.FRadius;
            EmissionTime.Value = (decimal)emittor.EmitterTime;
      


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
            else if (BoolLoopBox.Checked == false)
            {
                emittor.EmitterLooping = false;
                ResetEmittor();
            }
        }

        private void EmissionTime_ValueChanged(object sender, EventArgs e)
        {
            emittor.EmitterTime = (float)EmissionTime.Value;
            if (BoolLoopBox.Checked == false)
                ResetEmittor();
        }


   
        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ResetEmittor();
            ResetFlyweight();
        }


        private void StartMaxScale_ValueChanged(object sender, EventArgs e)
        {
            startScale = new Size((float)StartXScale.Value, particleData.ParticleStartScale.Height);
            ResetFlyweight();
            ResetEmittor();
        }

        private void StartMinScale_ValueChanged(object sender, EventArgs e)
        {
            startScale = new Size(particleData.ParticleStartScale.Width, (float)StartYScale.Value);
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndMaxScale_ValueChanged(object sender, EventArgs e)
        {
            endScale = new Size((float)EndXScale.Value, particleData.ParticleEndScale.Height);
            ResetFlyweight();
            ResetEmittor();
        }

        private void EndMinScale_ValueChanged(object sender, EventArgs e)
        {
            endScale = new Size(particleData.ParticleEndScale.Width, (float)StartYScale.Value);
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
            emitterPos.X = e.X;
            emitterPos.Y = e.Y;
            ResetFlyweight();
            ResetEmittor();
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "xml";
            dlg.Filter = "Xml Files (*.xml)|*.xml|All Files (*.*)|*.*";
            dlg.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\..\\Resources\\XML\\ParticleEffects");
            dlg.FilterIndex = 1;
            

            if (DialogResult.OK == dlg.ShowDialog())
            {
                szFilePath = dlg.FileName;
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.ConformanceLevel = ConformanceLevel.Document;
                settings.IgnoreComments = true;
                settings.IgnoreWhitespace = true;




                using (XmlReader reader = XmlReader.Create(dlg.FileName, settings))
                {
                    if (reader.IsStartElement("ParticleEffect"))
                    {
                        reader.ReadStartElement("ParticleEffect");
                        reader.MoveToFirstAttribute();
                        NumParticles.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        SpawnRate.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        EmissionRate.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        emittor.NShape = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        EmittorRadius.Value = (decimal)reader.ReadContentAsFloat();
                        reader.MoveToNextAttribute();

                        string Check  = reader.ReadContentAsString();
                        if (Check == "True")
                            BoolLoopBox.Checked = true;
                        else if (Check == "False")
                            BoolLoopBox.Checked = false; 

                        reader.MoveToNextAttribute();

                        EmissionTime.Value = (decimal)reader.ReadContentAsFloat();
                       
                        reader.MoveToNextAttribute();

                        emittor.EmitterPosition.X = reader.ReadContentAsInt();
                      
                        reader.MoveToNextAttribute();

                        emittor.EmitterPosition.Y = reader.ReadContentAsInt();

                        reader.MoveToNextAttribute();

                        EmittorWidth.Value = reader.ReadContentAsInt();

                        reader.MoveToNextAttribute();

                        EmittorHeight.Value = reader.ReadContentAsInt();

                        reader.ReadStartElement("Emittor");

                        reader.MoveToFirstAttribute();
                        ImgPath = reader.ReadContentAsString();
                        string path = "Particles/";
                        path += ImgPath;
                        m_TM.UnloadTexture(m_nParticleImg);
                        m_nParticleImg = m_TM.LoadTexture(path);

                        reader.MoveToNextAttribute();

                        StartXScale.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        StartYScale.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        EndXScale.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        EndYScale.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();

                        StartColorA.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        StartColorR.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        StartColorG.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        StartColorB.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        EndColorA.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        EndColorR.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        EndColorG.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();
                        EndColorB.Value = reader.ReadContentAsInt();
                        reader.MoveToNextAttribute();

                        SpeedMinX.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        SpeedMinY.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        SpeedMinX.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        SpeedMinY.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();

                        LifeMax.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        LifeMin.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();

                        RotationSpeed.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
                        Enertia.Value = (decimal)(reader.ReadContentAsFloat());
                        reader.MoveToNextAttribute();
             

                        ResetEmittor();
                        ResetFlyweight();
                    }
                }
            }
        }

        private void changeImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog opn = new OpenFileDialog();
            opn.DefaultExt = "png";
            opn.Filter = "Image files (*.png;*jpg;*bmp;)|*.png;*jpg;*bmp;";
            //opn.InitialDirectory = "../../../Resources/Graphics/";
            opn.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\..\\Resources\\Graphics\\Particles");
            
            

            if (DialogResult.OK == opn.ShowDialog())
            {
                m_TM.UnloadTexture(m_nParticleImg);
                m_nParticleImg = (m_TM.LoadTexture(opn.FileName));

                ImgPath = Path.GetFileName(opn.FileName);

                particleData.ParticleOffset = new Point(m_TM.GetTextureWidth(m_nParticleImg) / 2, m_TM.GetTextureHeight(m_nParticleImg) / 2);
                particleData.ParticleImage = m_nParticleImg;

            }
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            if(m_D3D != null )
            m_D3D.Resize(DirectXPanel, DirectXPanel.ClientSize.Width, DirectXPanel.ClientSize.Height, false);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog colorDlg = new ColorDialog();
            if (colorDlg.ShowDialog() == DialogResult.OK)
            {
               StartColorR.Value = colorDlg.Color.R ;
               StartColorG.Value = colorDlg.Color.G;
               StartColorB.Value = colorDlg.Color.B;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ColorDialog colorDlg = new ColorDialog();
            if (colorDlg.ShowDialog() == DialogResult.OK)
            {
               EndColorR.Value = colorDlg.Color.R;
               EndColorG.Value = colorDlg.Color.G;
               EndColorB.Value = colorDlg.Color.B;
            }
        }

      
       
        












    }
}
