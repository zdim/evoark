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

namespace EvoArk_Particles_Editor
{
    public partial class Form1 : Form
    {
        CSGP_Direct3D D3D = CSGP_Direct3D.GetInstance();
        CSGP_TextureManager TM = CSGP_TextureManager.GetInstance();



        bool looping = true;

        public bool Looping

        {
            get { return looping; }
            set { looping = value; }
        }

        public Form1()
        {
            InitializeComponent();

            D3D.Initialize(panel1, false);
            TM.Initialize(D3D.Device, D3D.Sprite);

        }

        public void Update()
        {
            
        }

        public void Render()
        {

            // use Color.FromArgb() specifiying colors 

            D3D.Clear(panel1, Color.Black);

           // D3D.DeviceBegin();


            D3D.Present();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }



        public Panel DirectXPanel { get { return panel1; } }


    }
}
