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

namespace Editor
{
    public partial class Form1 : Form
    {
        CSGP_Direct3D D3D = CSGP_Direct3D.GetInstance();
        CSGP_TextureManager TM = CSGP_TextureManager.GetInstance();

        Random rand = new Random(100);

        Size worldSize = new Size(4, 4);
        Quad[,] world = new Quad[4, 4];
        Size quadSize = new Size(100, 100);
        Quad selected = new Quad(0, 0);


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

            comboBox1.DataSource = Enum.GetValues(typeof(Spawn.Object));
            //panel1.AutoScroll = true;

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    world[i, j] = new Quad();
                    world[i, j].X = i;
                    world[i, j].Y = j;
                    world[i, j].Spawns.Clear();
                }

                    panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                        worldSize.Height * quadSize.Height);
        }

        public new void Update()
        {

        }

        public void Render()
        {
            D3D.Clear(panel1, Color.Black);
            D3D.DeviceBegin();
            D3D.SpriteBegin();
            for (int x = 0; x < worldSize.Width; x++ )
            {
                for (int y = 0; y < worldSize.Height; y++)
                {
                    Rectangle rect = Rectangle.Empty;
                    rect.X = x * quadSize.Width;
                    rect.X += panel1.AutoScrollPosition.X;
                    rect.Y = y * quadSize.Height;
                    rect.Y += panel1.AutoScrollPosition.Y;
                    rect.Size = quadSize;

                    D3D.DrawHollowRect(rect, Color.White, 1);
                }
            }
            if (selected != null)
            {
                Rectangle s = new Rectangle(selected.X * quadSize.Width, selected.Y * quadSize.Height, quadSize.Width, quadSize.Height);
                D3D.DrawHollowRect(s, Color.Cyan, 2);
            }
            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void quadWidth_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(quadWidth.Value.ToString());
            quadSize = new Size(temp, quadSize.Height);
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
        }

        private void quadHeight_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(quadHeight.Value.ToString());
            quadSize = new Size(quadSize.Width, temp);
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
        }

        private void numRows_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numRows.Value.ToString());
            
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);

            Quad[,] newWorld = new Quad[worldSize.Width, temp];

            for(int i = 0; i < worldSize.Width; i++)
                for(int j = 0; j < worldSize.Height; j++)
                {
                    // TODO: FIX THIS
                    if(world[i,j] != null)
                    {
                        newWorld[i, j] = world[i, j];
                    }
                }

            worldSize = new Size(worldSize.Width, temp);
        }

        private void numCols_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numCols.Value.ToString());
            worldSize = new Size(temp, worldSize.Height);
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;
            // Calculate the tile in which the mouse click occured.
            selected.X = (e.X - offset.X) / quadSize.Width;
            selected.Y = (e.Y - offset.Y) / quadSize.Height;

            world[selected.X, selected.Y].X = selected.X;
            world[selected.X, selected.Y].Y = selected.Y;
            
            listBox1.Items.Clear();

            if (world[selected.X, selected.Y].Spawns.Count != 0)
            {
                for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    listBox1.Items.Add(world[selected.X, selected.Y].Spawns[i]);
                }
            }
        }

        private void addEntity_Click(object sender, EventArgs e)
        {
            Spawn spawn = new Spawn();
            spawn.Obj = (Spawn.Object)comboBox1.SelectedItem;
            spawn.Amount = (int)numericUpDown1.Value;
            if(randomizeCheck.Enabled)
            {
                spawn.X = rand.Next(0, quadSize.Width);
                spawn.Y = rand.Next(0, quadSize.Height);
            }
            else
            {
                
            }
            listBox1.Items.Add(spawn);
            //world[selected.X, selected.Y].Spawns.Add(spawn);
        }
    }
}
