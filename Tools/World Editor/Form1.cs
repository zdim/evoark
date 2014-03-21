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

        Spawn selectedSpawn = new Spawn();

        // initial list of events
        List<string> worldEvents = new List<string>();
        // initial list of objects
        List<string> worldObjects = new List<string>();

        //List<string> events = new List<string>();
        List<EventSpawn> events = new List<EventSpawn>();

        // drawing collision rects
        Point startPos;
        Point newPos;
        bool drawing = false;
        List<Rectangle> collisionRects = new List<Rectangle>();
        Rectangle selectedCollisionRect = new Rectangle();
        private Rectangle getRectangle()
        {
            return new Rectangle(
                Math.Min(startPos.X, newPos.X),
                Math.Min(startPos.Y, newPos.Y),
                Math.Abs(startPos.X - newPos.X),
                Math.Abs(startPos.Y - newPos.Y));
        }

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

            //comboBox1.DataSource = Enum.GetValues(typeof(ObjectSpawn.Object));
            
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
            //panel1.AutoScroll = true;

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    world[i, j] = new Quad();
                    world[i, j].X = i;
                    world[i, j].Y = j;
                    world[i, j].Spawns.Clear();
                }

            // add initial objects
            worldObjects.Add("None");
            worldObjects.Add("Player");
            worldObjects.Add("Copperhead");
            worldObjects.Add("Cobra");
            worldObjects.Add("Mamba");
            worldObjects.Add("Coral");
            worldObjects.Add("Moccasin");
            worldObjects.Add("Asteroid");
            worldObjects.Add("Planet");
            worldObjects.Add("Human");

            // add initial events
            worldEvents.Add("Stargate");
            worldEvents.Add("Tutorial.Movement");
            worldEvents.Add("Tutorial.Lasers");
            worldEvents.Add("Tutorial.Missiles");
            worldEvents.Add("Tutorial.Warp");
            worldEvents.Add("Tutorial.Well");
            worldEvents.Add("Tutorial.Push");
            worldEvents.Add("Tutorial.Coordinator");
            worldEvents.Add("Tutorial.Ally");
            worldEvents.Add("Tutorial.Boss");

            comboBox1.DataSource = worldObjects;
            comboBox2.DataSource = worldEvents;

            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
        }

        public new void Update()
        {

        }

        public void Render()
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            D3D.Clear(panel1, Color.Black);
            D3D.DeviceBegin();
            D3D.SpriteBegin();
            for (int x = 0; x < worldSize.Width; x++)
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

                    for (int z = 0; z < world[x, y].Spawns.Count; z++)
                    {
                        if (world[x, y].Spawns[z] is ObjectSpawn)
                        {
                            ObjectSpawn oSpawn = (ObjectSpawn)world[x, y].Spawns[z];
                            Rectangle spawnRect = Rectangle.Empty;
                            spawnRect.Width = 20;
                            spawnRect.Height = 20;
                            spawnRect.X = world[x, y].Spawns[z].X + panel1.AutoScrollPosition.X;
                            spawnRect.Y = world[x, y].Spawns[z].Y + panel1.AutoScrollPosition.Y;
                            switch (oSpawn.ObjectType)
                            {
                                case "None":
                                    break;
                                case "Player":
                                    D3D.DrawRect(spawnRect, Color.White);
                                    break;
                                case "Copperhead":
                                    D3D.DrawRect(spawnRect, Color.Orange);
                                    break;
                                case "Cobra":
                                    D3D.DrawRect(spawnRect, Color.Yellow);
                                    break;
                                case "Mamba":
                                    D3D.DrawRect(spawnRect, Color.Red);
                                    break;
                                case "Coral":
                                    D3D.DrawRect(spawnRect, Color.Green);
                                    break;
                                case "Moccasin":
                                    D3D.DrawRect(spawnRect, Color.Cyan);
                                    break;
                                case "Asteroid":
                                    D3D.DrawRect(spawnRect, Color.Gray);
                                    break;
                                case "Planet":
                                    D3D.DrawRect(spawnRect, Color.Brown);
                                    break;
                                case "Human":
                                    D3D.DrawRect(spawnRect, Color.CornflowerBlue);
                                    break;
                                default:
                                    D3D.DrawRect(spawnRect, Color.Pink);
                                    break;
                            }
                        }
                        //if (world[x, y].Spawns[z] is EventSpawn)
                        //{
                        //    EventSpawn eSpawn = (EventSpawn)world[x, y].Spawns[z];
                        //    Rectangle spawnRect = Rectangle.Empty;
                        //    spawnRect.Width = world[x, y].Spawns[z].Width;
                        //    spawnRect.Height = world[x, y].Spawns[z].Height;
                        //    spawnRect.X = world[x, y].Spawns[z].X + panel1.AutoScrollPosition.X;
                        //    spawnRect.Y = world[x, y].Spawns[z].Y + panel1.AutoScrollPosition.Y;
                        //    switch (eSpawn.EventType)
                        //    {
                        //        case "Example":
                        //            D3D.DrawHollowRect(spawnRect, Color.Yellow, 2);
                        //            break;
                        //        case "Stargate":
                        //            D3D.DrawHollowRect(spawnRect, Color.Purple, 2);
                        //            break;
                        //        default:
                        //            D3D.DrawHollowRect(spawnRect, Color.Pink, 2);
                        //            break;
                        //    }
                        //}
                    }
                }
            }
            if(events.Count > 0)
            {
                foreach(EventSpawn ev in events)
                {
                    Rectangle spawnRect = Rectangle.Empty;
                    spawnRect.Width = ev.Width;
                    spawnRect.Height = ev.Height;
                    spawnRect.X = ev.X + panel1.AutoScrollPosition.X;
                    spawnRect.Y = ev.Y + panel1.AutoScrollPosition.Y;
                    switch(ev.EventType)
                    {
                        case "Example":
                            D3D.DrawHollowRect(spawnRect, Color.Yellow, 2);
                            break;
                        case "Stargate":
                            D3D.DrawHollowRect(spawnRect, Color.Purple, 2);
                            break;
                        default:
                            D3D.DrawHollowRect(spawnRect, Color.Pink, 2);
                            break;
                    }
                }
            }

            if (collisionRects.Count > 0)
            {
                for (int i = 0; i < collisionRects.Count; i++)
                {
                    D3D.DrawHollowRect(collisionRects[i], Color.Red, 1);
                }

                if (selectedCollisionRect != Rectangle.Empty)
                {
                    D3D.DrawHollowRect(selectedCollisionRect, Color.Pink, 2);
                }
            }

            if (drawing)
            {
                if (collisionCheck.Checked == true)
                    D3D.DrawRect(getRectangle(), Color.Pink);
                else if (radioButtonEvent.Checked == true)
                    D3D.DrawRect(getRectangle(), Color.PaleVioletRed);

            }

            if (selected != null && collisionCheck.Checked == false)
            {
                Rectangle s = new Rectangle(selected.X * quadSize.Width + panel1.AutoScrollPosition.X,
                    selected.Y * quadSize.Height + panel1.AutoScrollPosition.Y, quadSize.Width, quadSize.Height);
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
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            labelWorldSize.Text = "World Size: " + (worldSize.Width * quadSize.Width).ToString() + ", " + (worldSize.Height * quadSize.Height).ToString();
        }

        private void quadHeight_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(quadHeight.Value.ToString());
            quadSize = new Size(quadSize.Width, temp);
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            labelWorldSize.Text = "World Size: " + (worldSize.Width * quadSize.Width).ToString() + ", " + (worldSize.Height * quadSize.Height).ToString();
        }

        private void numRows_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numRows.Value.ToString());

            Quad[,] newWorld = new Quad[worldSize.Width, temp];

            for (int i = 0; i < worldSize.Width; i++)
                for (int j = 0; j < temp; j++)
                {
                    if (j < worldSize.Height)
                    {
                        newWorld[i, j] = world[i, j];
                    }
                    else
                        newWorld[i, j] = new Quad(i, j);
                }

            worldSize = new Size(worldSize.Width, temp);
            world = newWorld;
            numericUpDownY.Maximum = quadSize.Height * temp;

            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            labelWorldSize.Text = "World Size: " + (worldSize.Width * quadSize.Width).ToString() + ", " + (worldSize.Height * quadSize.Height).ToString();
        }

        private void numCols_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numCols.Value.ToString());

            Quad[,] newWorld = new Quad[temp, worldSize.Height];

            for (int i = 0; i < temp; i++)
                for (int j = 0; j < worldSize.Height; j++)
                {
                    if (i < worldSize.Width)
                    {
                        newWorld[i, j] = world[i, j];
                    }
                    else
                        newWorld[i, j] = new Quad(i, j);
                }
            worldSize = new Size(temp, worldSize.Height);
            world = newWorld;
            numericUpDownX.Maximum = quadSize.Width * temp;
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            labelWorldSize.Text = "World Size: " + (worldSize.Width * quadSize.Width).ToString() + ", " + (worldSize.Height * quadSize.Height).ToString();
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
                offset.X += panel1.AutoScrollPosition.X;
                offset.Y += panel1.AutoScrollPosition.Y;

            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;
            // Calculate the quad in which the mouse click occured.
            selected.X = (e.X - offset.X) / quadSize.Width;
            selected.Y = (e.Y - offset.Y) / quadSize.Height;

            world[selected.X, selected.Y].X = selected.X;
            world[selected.X, selected.Y].Y = selected.Y;

            //numericUpDownX.Value = e.X - offset.X;
            //numericUpDownY.Value = e.Y - offset.Y;

            listBox1.Items.Clear();

            if (world[selected.X, selected.Y].Spawns.Count != 0)
            {
                for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    listBox1.Items.Add(world[selected.X, selected.Y].Spawns[i]);
                }
            }
            if (e.Button == MouseButtons.Left)
            {
                if (collisionCheck.Checked == false)
                {
                    for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        Rectangle r = new Rectangle(
                            world[selected.X, selected.Y].Spawns[i].X,
                            world[selected.X, selected.Y].Spawns[i].Y,
                            world[selected.X, selected.Y].Spawns[i].Width,
                            world[selected.X, selected.Y].Spawns[i].Height);
                        if (r.Contains(e.Location))
                        {
                            listBox1.SelectedIndex = i;
                            numericUpDownX.Value = world[selected.X, selected.Y].Spawns[i].X;
                            numericUpDownY.Value = world[selected.X, selected.Y].Spawns[i].Y;
                            numericUpDownWidth.Value = world[selected.X, selected.Y].Spawns[i].Width;
                            numericUpDownHeight.Value = world[selected.X, selected.Y].Spawns[i].Height;
                            if (world[selected.X, selected.Y].Spawns[i] is ObjectSpawn)
                            {
                                ObjectSpawn oSpawn = (ObjectSpawn)world[selected.X, selected.Y].Spawns[i];
                                radioButtonObject.Checked = true;
                                radioButtonEvent.Checked = false;
                                groupBoxPosition.Enabled = true;
                                randomizeCheck.Enabled = true;
                                //comboBox1.DataSource = Enum.GetValues(typeof(ObjectSpawn.Object));
                                groupBoxSize.Enabled = false;
                                numericUpDown1.Enabled = true;
                                label1.Text = "Object Type";
                                numericUpDown1.Value = oSpawn.Amount;
                                comboBox1.SelectedItem = oSpawn.ObjectType;
                            }
                            else if (world[selected.X, selected.Y].Spawns[i] is EventSpawn)
                            {
                                EventSpawn eSpawn = (EventSpawn)world[selected.X, selected.Y].Spawns[i];
                                radioButtonEvent.Checked = true;
                                radioButtonObject.Checked = false;
                                groupBoxPosition.Enabled = false;
                                randomizeCheck.Enabled = false;
                                //comboBox1.DataSource = Enum.GetValues(typeof(EventSpawn.Event));
                                groupBoxSize.Enabled = true;
                                numericUpDown1.Enabled = false;
                                //label1.Text = "Event Type";
                                //comboBox1.SelectedItem = eSpawn.EventType;
                            }
                        }
                    }
                }
                else if (collisionCheck.Checked == true)
                {
                    bool success = false;
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i].Contains(e.Location))
                        {
                            selectedCollisionRect = collisionRects[i];
                            numericUpDownX.Value = collisionRects[i].X;
                            numericUpDownY.Value = collisionRects[i].Y;
                            numericUpDownWidth.Value = collisionRects[i].Width;
                            numericUpDownHeight.Value = collisionRects[i].Height;
                            success = true;
                        }
                    }
                    if (!success)
                    {
                        selectedCollisionRect = Rectangle.Empty;

                    }
                }
            }
            // add right click to add objects to grid
            if (e.Button == MouseButtons.Right && drawing == false)
            {
                if (radioButtonObject.Checked == true && collisionCheck.Checked == false)
                {
                    Spawn spawn = new ObjectSpawn();
                    if (spawn is ObjectSpawn)
                    {
                        ObjectSpawn oSpawn = new ObjectSpawn();
                        oSpawn.ObjectType = comboBox1.SelectedItem.ToString();
                        oSpawn.Amount = (int)numericUpDown1.Value;
                        spawn = oSpawn;
                    }
                    spawn.X = e.X - offset.X;
                    spawn.Y = e.Y - offset.Y;
                    spawn.Width = 20;
                    spawn.Height = 20;
                    listBox1.Items.Add(spawn);
                    listBox1.SelectedIndex = world[selected.X, selected.Y].Spawns.Count - 1;
                    world[selected.X, selected.Y].Spawns.Add(spawn);
                }
                else if (radioButtonEvent.Checked == true && collisionCheck.Checked == false)
                {
                    Rectangle r = Rectangle.Empty;
                    r.X = e.X - offset.X;
                    r.Y = e.Y - offset.Y;
                    r.Width = (int)numericUpDownEventWidth.Value;
                    r.Height = (int)numericUpDownEventHeight.Value;
                    EventSpawn eSpawn = new EventSpawn(r, comboBox2.SelectedItem.ToString());
                    //eSpawn.EventType = comboBox2.SelectedItem.ToString();
                    //eSpawn.Width = (int)numericUpDownWidth.Value;
                    //eSpawn.Height = (int)numericUpDownHeight.Value;
                    //eSpawn.X = e.X - offset.X;
                    //eSpawn.Y = e.Y - offset.Y;
                    events.Add(eSpawn);
                    listBox2.DataSource = null;
                    listBox2.DataSource = events; // FIX: NOT WORKING ON RIGHT CLICK SINCE DRAWING IS FLAGGED
                    //listBox2.SelectedIndex = events.Count - 1;
                    // FIX EVENT ADDING

                    //world[selected.X, selected.Y].Spawns.Add(spawn);
                }
            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;

            if (e.Button == MouseButtons.Left)
            {

            }
            else if (e.Button == MouseButtons.Right)
            {
                if (collisionCheck.Checked == true || radioButtonEvent.Checked == true)
                {
                    newPos.X = startPos.X = e.X - offset.X;
                    newPos.Y = startPos.Y = e.Y - offset.Y;

                    drawing = true;
                }
            }
        }
        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;

            newPos.X = e.X - offset.X;
            newPos.Y = e.Y - offset.Y;
            if (drawing)
            {
                panel1.Invalidate();
            }
        }
        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;
           
            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;

            if (drawing)
            {
                drawing = false;
                var r = getRectangle();
                if (r.Width > 0 && r.Height > 0)
                {
                    if (collisionCheck.Checked == true) collisionRects.Add(r);
                    else if (radioButtonEvent.Checked == true)
                    {
                        EventSpawn ev = new EventSpawn(r, comboBox2.SelectedItem.ToString());
                        events.Add(ev);
                        listBox2.DataSource = null;
                        listBox2.DataSource = events;
                    }
                    panel1.Invalidate();
                }
            }
        }

        private void addEntity_Click(object sender, EventArgs e)
        {
            //Spawn spawn = new Spawn();
            if (radioButtonObject.Checked == true)
            {
                Spawn spawn = new ObjectSpawn();
                if (spawn is ObjectSpawn)
                {
                    ObjectSpawn oSpawn = new ObjectSpawn();
                    oSpawn.ObjectType = comboBox1.SelectedItem.ToString();
                    oSpawn.Amount = (int)numericUpDown1.Value;
                    spawn = oSpawn;
                    // for now - needs to be updated with object sprites.
                    spawn.Width = 20;
                    spawn.Height = 20;
                }
                if (randomizeCheck.Checked == true)
                {
                    spawn.X = -1;
                    spawn.Y = -1;
                }
                else
                {
                    spawn.X = (int)numericUpDownX.Value;
                    spawn.Y = (int)numericUpDownY.Value;
                }
                listBox1.Items.Add(spawn);
                world[selected.X, selected.Y].Spawns.Add(spawn);
            }

        }

        private void removeEntity_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex != -1)
            {
                world[selected.X, selected.Y].Spawns.RemoveAt(listBox1.SelectedIndex);
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);
                listBox1.Update();
            }
        }

        private void radioButtonEvent_Click(object sender, EventArgs e)
        {
            radioButtonObject.Checked = false;
        }

        private void radioButtonObject_Click(object sender, EventArgs e)
        {
            radioButtonEvent.Checked = false;
        }

        private void randomizeCheck_CheckedChanged(object sender, EventArgs e)
        {
            if (randomizeCheck.Checked == true)
            {
                groupBoxPosition.Enabled = false;
            }
            else
                groupBoxPosition.Enabled = true;
        }

        private void radioButtonGenerated_Click(object sender, EventArgs e)
        {
            radioButtonStatic.Checked = false;
        }

        private void radioButtonStatic_Click(object sender, EventArgs e)
        {
            radioButtonGenerated.Checked = false;
        }

        private void collisionCheck_Click(object sender, EventArgs e)
        {
            // possible.
            // make collision rectangles similar to selection boxes.
            if (collisionCheck.Checked == true)
            {
                comboBox1.Enabled = false;
                numericUpDown1.Enabled = false;
                addEntity.Enabled = false;
                removeEntity.Enabled = false;
                radioButtonEvent.Enabled = false;
                radioButtonObject.Enabled = false;
                numericUpDownWidth.Maximum = 1000;
                numericUpDownHeight.Maximum = 1000;
                groupBoxSize.Enabled = true;
            }
            else
            {
                comboBox1.Enabled = true;
                numericUpDown1.Enabled = true;
                addEntity.Enabled = true;
                removeEntity.Enabled = true;
                radioButtonEvent.Enabled = true;
                radioButtonObject.Enabled = true;

                if (radioButtonObject.Enabled == true)
                {
                    groupBoxSize.Enabled = false;
                }
            }
        }

        private void numericUpDownX_ValueChanged(object sender, EventArgs e)
        {
            if (collisionCheck.Checked == true)
            {
                if (selectedCollisionRect != Rectangle.Empty)
                {
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i] == selectedCollisionRect)
                        {
                            selectedCollisionRect.X = (int)numericUpDownX.Value;
                            collisionRects[i] = selectedCollisionRect;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownY_ValueChanged(object sender, EventArgs e)
        {
            if (collisionCheck.Checked == true)
            {
                if (selectedCollisionRect != Rectangle.Empty)
                {
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i] == selectedCollisionRect)
                        {
                            selectedCollisionRect.Y = (int)numericUpDownY.Value;
                            collisionRects[i] = selectedCollisionRect;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownWidth_ValueChanged(object sender, EventArgs e)
        {
            if (collisionCheck.Checked == true)
            {
                if (selectedCollisionRect != Rectangle.Empty)
                {
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i] == selectedCollisionRect)
                        {
                            selectedCollisionRect.Width = (int)numericUpDownWidth.Value;
                            collisionRects[i] = selectedCollisionRect;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownHeight_ValueChanged(object sender, EventArgs e)
        {
            if (collisionCheck.Checked == true)
            {
                if (selectedCollisionRect != Rectangle.Empty)
                {
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i] == selectedCollisionRect)
                        {
                            selectedCollisionRect.Height = (int)numericUpDownHeight.Value;
                            collisionRects[i] = selectedCollisionRect;
                            break;
                        }
                    }
                }
            }
        }

        private void comboBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar == (char)System.Windows.Forms.Keys.Enter)
            {
                bool success = false;
                foreach(string str in worldObjects)
                {
                    if(comboBox1.Text.ToUpper() == str.ToUpper())
                    {
                        success = true;
                        break;
                    }
                }
                if(!success)
                {
                    worldObjects.Add(comboBox1.Text);
                    comboBox1.DataSource = null;
                    comboBox1.DataSource = worldObjects;
                }
            }
        }

        private void comboBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)System.Windows.Forms.Keys.Enter)
            {
                bool success = false;
                foreach (string str in worldEvents)
                {
                    if (comboBox2.Text.ToUpper() == str.ToUpper())
                    {
                        success = true;
                        break;
                    }
                }
                if (!success)
                {
                    worldEvents.Add(comboBox2.Text);
                    comboBox2.DataSource = null;
                    comboBox2.DataSource = worldEvents;
                }
            }
        }


    }
}
