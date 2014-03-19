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

            while (particleEditorForm.Looping )
            {
                particleEditorForm.Update();
                particleEditorForm.Render();
                Application.DoEvents();
            }




        }
    }
}
