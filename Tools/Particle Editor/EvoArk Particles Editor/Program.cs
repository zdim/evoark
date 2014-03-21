using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EvoArk_Particles_Editor
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);


            Form1 particleEditorForm = new Form1();
            particleEditorForm.Show();
            particleEditorForm.Initialize();

            float dt;
            long curTime = 0;
            long prevTime = 0;

       


            while (particleEditorForm.Looping )
            {
                curTime = System.DateTime.Now.Ticks;
                if (prevTime == 0)
                    prevTime = curTime;
                dt = (curTime - prevTime) * 0.0000001f;
                prevTime = System.DateTime.Now.Ticks;

                particleEditorForm.Update(dt);
                particleEditorForm.Render();
                Application.DoEvents();
            }




        }
    }
}
