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
using System.Xml;

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

        int backgroundID;
        string backgroundPath = "";

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
            worldObjects.Add("NONE");
            worldObjects.Add("PLAYER");
            worldObjects.Add("COPPERHEAD");
            worldObjects.Add("COBRA");
            worldObjects.Add("MAMBA");
            worldObjects.Add("CORAL");
            worldObjects.Add("MOCCASIN");
            worldObjects.Add("ASTEROID");
            worldObjects.Add("PLANET");
            worldObjects.Add("HUMAN");

            // add initial events
            worldEvents.Add("STARGATE");
            worldEvents.Add("TUTORIAL.MOVEMENT");
            worldEvents.Add("TUTORIAL.LASERS");
            worldEvents.Add("TUTORIAL.MISSILES");
            worldEvents.Add("TUTORIAL.WARP");
            worldEvents.Add("TUTORIAL.WELL");
            worldEvents.Add("TUTORIAL.PUSH");
            worldEvents.Add("TUTORIAL.COORDINATOR");
            worldEvents.Add("TUTORIAL.ALLY");
            worldEvents.Add("TUTORIAL.BOSS");

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
            if(backgroundPath.Length > 0)
            {
                TM.Draw(backgroundID, offset.X, offset.Y);
            }

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
                                case "NONE":
                                    break;
                                case "PLAYER":
                                    D3D.DrawRect(spawnRect, Color.White);
                                    break;
                                case "COPPERHEAD":
                                    D3D.DrawRect(spawnRect, Color.Orange);
                                    break;
                                case "COBRA":
                                    D3D.DrawRect(spawnRect, Color.Yellow);
                                    break;
                                case "MAMBA":
                                    D3D.DrawRect(spawnRect, Color.Red);
                                    break;
                                case "CORAL":
                                    D3D.DrawRect(spawnRect, Color.Green);
                                    break;
                                case "MOCCASIN":
                                    D3D.DrawRect(spawnRect, Color.Cyan);
                                    break;
                                case "ASTEROID":
                                    D3D.DrawRect(spawnRect, Color.Gray);
                                    break;
                                case "PLANET":
                                    D3D.DrawRect(spawnRect, Color.Brown);
                                    break;
                                case "HUMAN":
                                    D3D.DrawRect(spawnRect, Color.CornflowerBlue);
                                    break;
                                default:
                                    D3D.DrawRect(spawnRect, Color.Pink);
                                    break;
                            }
                        }
                    }
                    Rectangle r = new Rectangle(selectedSpawn.X + panel1.AutoScrollPosition.X, selectedSpawn.Y + panel1.AutoScrollPosition.Y,
                                                selectedSpawn.Width, selectedSpawn.Height);
                    D3D.DrawHollowRect(r, Color.White, 1);
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
                        case "EXAMPLE":
                            D3D.DrawHollowRect(spawnRect, Color.Yellow, 3);
                            break;
                        case "STARGATE":
                            D3D.DrawHollowRect(spawnRect, Color.Purple, 3);
                            break;
                        default:
                            D3D.DrawHollowRect(spawnRect, Color.Pink, 3);
                            break;
                    }
                }
                Rectangle r = new Rectangle(selectedSpawn.X + panel1.AutoScrollPosition.X, selectedSpawn.Y + panel1.AutoScrollPosition.Y,
                                            selectedSpawn.Width, selectedSpawn.Height);
                D3D.DrawHollowRect(r, Color.White, 1);
            }

            if (collisionRects.Count > 0)
            {
                for (int i = 0; i < collisionRects.Count; i++)
                {
                    Rectangle r = collisionRects[i];
                    r.X += panel1.AutoScrollPosition.X;
                    r.Y += panel1.AutoScrollPosition.Y;
                    D3D.DrawHollowRect(r, Color.Red, 1);
                }

                if (selectedCollisionRect != Rectangle.Empty)
                {
                    D3D.DrawHollowRect(selectedCollisionRect, Color.Pink, 2);
                }
            }

            if (drawing)
            {
                if (collisionCheck.Checked == true)
                {
                    Rectangle r = getRectangle();
                    r.X += panel1.AutoScrollPosition.X;
                    r.Y += panel1.AutoScrollPosition.Y;
                    D3D.DrawRect(r, Color.Pink);
                }
                else if (radioButtonEvent.Checked == true)
                {
                    Rectangle r = getRectangle();
                    r.X += panel1.AutoScrollPosition.X;
                    r.Y += panel1.AutoScrollPosition.Y;
                    D3D.DrawRect(r, Color.PaleVioletRed);
                }
            }

            if (selected != null && collisionCheck.Checked == false && radioButtonObject.Checked == true)
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
            numericUpDownEventX.Maximum = quadSize.Width * worldSize.Width;
            numericUpDownEventY.Maximum = quadSize.Height * worldSize.Height;
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
            numericUpDownEventX.Maximum = quadSize.Width * worldSize.Width;
            numericUpDownEventY.Maximum = quadSize.Height * worldSize.Height; panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
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
            numericUpDownEventY.Maximum = quadSize.Height * temp;

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
            numericUpDownEventX.Maximum = quadSize.Width * temp;
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

            Point mouse = new Point(0, 0);
            mouse.X = e.X - offset.X;
            mouse.Y = e.Y - offset.Y;

            world[selected.X, selected.Y].X = selected.X;
            world[selected.X, selected.Y].Y = selected.Y;

            listBox1.DataSource = null;
            listBox1.DataSource = world[selected.X, selected.Y].Spawns;

            if (e.Button == MouseButtons.Left)
            {
                if (collisionCheck.Checked == false)
                {
                    if (radioButtonObject.Checked == true)
                    {
                        bool success = false;
                        for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                        {
                            Rectangle r = new Rectangle(
                                world[selected.X, selected.Y].Spawns[i].X,
                                world[selected.X, selected.Y].Spawns[i].Y,
                                world[selected.X, selected.Y].Spawns[i].Width,
                                world[selected.X, selected.Y].Spawns[i].Height);
                            
                            if (r.Contains(mouse))
                            {
                                listBox1.SelectedIndex = i;
                                numericUpDownX.Value = world[selected.X, selected.Y].Spawns[i].X;
                                numericUpDownY.Value = world[selected.X, selected.Y].Spawns[i].Y;
                                numericUpDownWidth.Value = world[selected.X, selected.Y].Spawns[i].Width;
                                numericUpDownHeight.Value = world[selected.X, selected.Y].Spawns[i].Height;
                                if (world[selected.X, selected.Y].Spawns[i] is ObjectSpawn)
                                {
                                    ObjectSpawn oSpawn = (ObjectSpawn)world[selected.X, selected.Y].Spawns[i];
                                    numericUpDown1.Value = oSpawn.Amount;
                                    comboBox1.SelectedItem = oSpawn.ObjectType;
                                    randomizeCheck.Checked = oSpawn.Randomized;
                                }
                                selectedSpawn = world[selected.X, selected.Y].Spawns[i];
                                success = true;
                            }
                        }
                        if(!success)
                        {
                            selectedSpawn = new Spawn();
                            numericUpDownX.Value = e.X - offset.X;
                            numericUpDownY.Value = e.Y - offset.Y;
                            listBox1.SelectedIndex = -1;
                        }
                    }

                    else if(radioButtonEvent.Checked == true)
                    {
                        bool success = false;
                        for(int i = 0; i < events.Count; i++)
                        {
                            Rectangle r = new Rectangle(
                                events[i].X, events[i].Y,
                                events[i].Width, events[i].Height);
                            if(r.Contains(mouse))
                            {
                                listBox2.SelectedIndex = i;
                                numericUpDownEventX.Value = r.X;
                                numericUpDownEventY.Value = r.Y;
                                numericUpDownEventWidth.Value = r.Width;
                                numericUpDownEventHeight.Value = r.Height;
                                selectedSpawn = events[i];
                                comboBox2.SelectedItem = events[i].EventType;
                                success = true;
                                break;
                            }
                        }
                        if(!success)
                        {
                            selectedSpawn = new EventSpawn(Rectangle.Empty, "");
                            listBox2.SelectedIndex = -1;
                        }
                    }
                }
                else if (collisionCheck.Checked == true)
                {
                    bool success = false;
                    for (int i = 0; i < collisionRects.Count; i++)
                    {
                        if (collisionRects[i].Contains(mouse))
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
                        listBox1.SelectedIndex = -1;

                    }
                }
            }
            // add right click to add objects to grid
            if (e.Button == MouseButtons.Right && drawing == false)
            {
                if (radioButtonObject.Checked == true && collisionCheck.Checked == false)
                {
                    ObjectSpawn spawn = new ObjectSpawn();
                    spawn.ObjectType = comboBox1.SelectedItem.ToString();
                    spawn.Amount = (int)numericUpDown1.Value;
                    spawn.Randomized = randomizeCheck.Checked;
                    spawn.X = e.X - offset.X;
                    spawn.Y = e.Y - offset.Y;
                    spawn.Width = 20;
                    spawn.Height = 20;
                    world[selected.X, selected.Y].Spawns.Add(spawn);
                    listBox1.DataSource = null;
                    listBox1.DataSource = world[selected.X, selected.Y].Spawns;
                    listBox1.SelectedIndex = world[selected.X, selected.Y].Spawns.Count - 1;
                }
                else if (radioButtonEvent.Checked == true && collisionCheck.Checked == false)
                {
                    Rectangle r = Rectangle.Empty;
                    r.X = e.X - offset.X;
                    r.Y = e.Y - offset.Y;
                    r.Width = (int)numericUpDownEventWidth.Value;
                    r.Height = (int)numericUpDownEventHeight.Value;
                    EventSpawn eSpawn = new EventSpawn(r, comboBox2.SelectedItem.ToString());
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
                ObjectSpawn spawn = new ObjectSpawn();
                spawn.ObjectType = comboBox1.SelectedItem.ToString();
                spawn.Amount = (int)numericUpDown1.Value;
                spawn.Randomized = randomizeCheck.Checked;
                // for now - needs to be updated with object sprites.
                spawn.Width = 20;
                spawn.Height = 20;

                
                spawn.X = (int)numericUpDownX.Value;
                spawn.Y = (int)numericUpDownY.Value;
                
                world[selected.X, selected.Y].Spawns.Add(spawn);
                listBox1.DataSource = null;
                listBox1.DataSource = world[selected.X, selected.Y].Spawns;
            }

        }

        private void removeEntity_Click(object sender, EventArgs e)
        {
            if(collisionCheck.Checked == true)
            {
                if(selectedCollisionRect != Rectangle.Empty)
                {
                    for(int i = 0; i < collisionRects.Count; i++)
                    {
                        if(selectedCollisionRect == collisionRects[i])
                        {
                            collisionRects.RemoveAt(i);
                            selectedCollisionRect = Rectangle.Empty;
                            return;
                        }
                    }
                }
            }
            if (listBox1.SelectedIndex != -1)
            {
                world[selected.X, selected.Y].Spawns.RemoveAt(listBox1.SelectedIndex);
                listBox1.DataSource = null;
                listBox1.DataSource = world[selected.X, selected.Y].Spawns;
                selectedSpawn = new Spawn();
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
            if(radioButtonObject.Checked && selectedSpawn != null)
            {
                for(int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    if(selectedSpawn == world[selected.X, selected.Y].Spawns[i])
                    {
                        ObjectSpawn oSpawn = new ObjectSpawn();
                        oSpawn.Amount = (int)numericUpDown1.Value;
                        oSpawn.X = selectedSpawn.X;
                        oSpawn.Y = selectedSpawn.Y;
                        oSpawn.Width = selectedSpawn.Width;
                        oSpawn.Height = selectedSpawn.Height;
                        oSpawn.ObjectType = comboBox1.SelectedItem.ToString();
                        oSpawn.Randomized = randomizeCheck.Checked;
                        selectedSpawn = oSpawn;
                        world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
                        listBox1.DataSource = null;
                        listBox1.DataSource = world[selected.X, selected.Y].Spawns;
                        listBox1.SelectedIndex = i;
                        break;
                    }
                }
            }
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
                //removeEntity.Enabled = false;
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

            else
            {
                if(selectedSpawn != null)
                {
                    for(int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        if(selectedSpawn == world[selected.X, selected.Y].Spawns[i])
                        {
                            selectedSpawn.X = (int)numericUpDownX.Value;
                            world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
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
            else
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        if (selectedSpawn == world[selected.X, selected.Y].Spawns[i])
                        {
                            selectedSpawn.Y = (int)numericUpDownY.Value;
                            world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
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
            else
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        if (selectedSpawn == world[selected.X, selected.Y].Spawns[i])
                        {
                            selectedSpawn.Width = (int)numericUpDownWidth.Value;
                            world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
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
            else
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        if (selectedSpawn == world[selected.X, selected.Y].Spawns[i])
                        {
                            selectedSpawn.Height = (int)numericUpDownHeight.Value;
                            world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
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

        private void numericUpDownEventX_ValueChanged(object sender, EventArgs e)
        {
            if (radioButtonEvent.Checked == true)
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < events.Count; i++)
                    {
                        if (events[i] == selectedSpawn)
                        {
                            selectedSpawn.X = (int)numericUpDownEventX.Value;
                            events[i] = (EventSpawn)selectedSpawn;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownEventY_ValueChanged(object sender, EventArgs e)
        {
            if (radioButtonEvent.Checked == true)
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < events.Count; i++)
                    {
                        if (events[i] == selectedSpawn)
                        {
                            selectedSpawn.Y = (int)numericUpDownEventY.Value;
                            events[i] = (EventSpawn)selectedSpawn;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownEventWidth_ValueChanged(object sender, EventArgs e)
        {
            if (radioButtonEvent.Checked == true)
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < events.Count; i++)
                    {
                        if (events[i] == selectedSpawn)
                        {
                            selectedSpawn.Width = (int)numericUpDownEventWidth.Value;
                            events[i] = (EventSpawn)selectedSpawn;
                            break;
                        }
                    }
                }
            }
        }

        private void numericUpDownEventHeight_ValueChanged(object sender, EventArgs e)
        {
            if (radioButtonEvent.Checked == true)
            {
                if (selectedSpawn != null)
                {
                    for (int i = 0; i < events.Count; i++)
                    {
                        if (events[i] == selectedSpawn)
                        {
                            selectedSpawn.Height = (int)numericUpDownEventHeight.Value;
                            events[i] = (EventSpawn)selectedSpawn;
                            break;
                        }
                    }
                }
            }
        }

        private void eventRemove_Click(object sender, EventArgs e)
        {
            if(listBox2.SelectedIndex != -1)
            {
                events.RemoveAt(listBox2.SelectedIndex);
                listBox2.DataSource = null;
                listBox2.DataSource = events;
                selectedSpawn = new Spawn();
            }
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if(radioButtonObject.Checked == true)
            {
                if(selectedSpawn != null)
                {
                    for(int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                    {
                        if(world[selected.X, selected.Y].Spawns[i] == selectedSpawn)
                        {
                            ObjectSpawn oSpawn = new ObjectSpawn();
                            oSpawn.Amount = (int)numericUpDown1.Value;
                            oSpawn.X = selectedSpawn.X;
                            oSpawn.Y = selectedSpawn.Y;
                            oSpawn.Width = selectedSpawn.Width;
                            oSpawn.Height = selectedSpawn.Height;
                            oSpawn.ObjectType = comboBox1.SelectedItem.ToString();
                            oSpawn.Randomized = randomizeCheck.Checked;
                            selectedSpawn = oSpawn;
                            world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
                            listBox1.DataSource = null;
                            listBox1.DataSource = world[selected.X, selected.Y].Spawns;
                            listBox1.SelectedIndex = i;
                            break;
                        }
                    }
                }
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex != -1)
            {
                selectedSpawn = world[selected.X, selected.Y].Spawns[listBox1.SelectedIndex];
            }
        }

        private void comboBox1_SelectedValueChanged(object sender, EventArgs e)
        {
            if(selectedSpawn != null)
            {
                for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    if (world[selected.X, selected.Y].Spawns[i] == selectedSpawn)
                    {
                        ObjectSpawn oSpawn = new ObjectSpawn();
                        oSpawn.Amount = (int)numericUpDown1.Value;
                        oSpawn.X = selectedSpawn.X;
                        oSpawn.Y = selectedSpawn.Y;
                        oSpawn.Width = selectedSpawn.Width;
                        oSpawn.Height = selectedSpawn.Height;
                        oSpawn.ObjectType = comboBox1.SelectedItem.ToString();
                        oSpawn.Randomized = randomizeCheck.Checked;
                        selectedSpawn = oSpawn;
                        world[selected.X, selected.Y].Spawns[i] = (ObjectSpawn)selectedSpawn;
                        listBox1.DataSource = null;
                        listBox1.DataSource = world[selected.X, selected.Y].Spawns;
                        listBox1.SelectedIndex = i;
                        break;
                    }
                }
            }
        }

        public void newWorldToolStripMenuItem_Click(object sender, EventArgs e)
        {

            

            // reset controls
            quadWidth.Value = quadSize.Width;
            quadHeight.Value = quadSize.Height;
            numRows.Value = worldSize.Height;
            numCols.Value = worldSize.Width;
            listBox1.DataSource = null;
            numericUpDown1.Value = 1;
            numericUpDownX.Value = 0;
            numericUpDownY.Value = 0;
            numericUpDownWidth.Value = 20;
            numericUpDownHeight.Value = 20;
            randomizeCheck.Checked = false;
            listBox2.DataSource = null;
            numericUpDownEventX.Value = 0;
            numericUpDownEventY.Value = 0;
            numericUpDownEventWidth.Value = 20;
            numericUpDownEventHeight.Value = 20;

            worldSize = new Size(4, 4);
            world = new Quad[4, 4];
            quadSize = new Size(100, 100);
            selected = new Quad(0, 0);

            backgroundPath = "";
            backgroundID = new int();

            selectedSpawn = new Spawn();
            selectedCollisionRect = new Rectangle();
            collisionRects = new List<Rectangle>();

            events = new List<EventSpawn>();

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    world[i, j] = new Quad();
                    world[i, j].X = i;
                    world[i, j].Y = j;
                    world[i, j].Spawns.Clear();
                }
        }

        public void saveWorldToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.DefaultExt = "xml";
            dlg.Filter = "XML File (*.xml)|*.xml";
            dlg.FilterIndex = 0;
            dlg.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "//..//..//Resources//XML//World");
            if (DialogResult.OK == dlg.ShowDialog())
            {
                XmlWriterSettings settings = new XmlWriterSettings();
                settings.ConformanceLevel = ConformanceLevel.Document;
                settings.Indent = true;

                using (XmlWriter writer = XmlWriter.Create(dlg.FileName, settings))
                {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("Level");
                    writer.WriteStartElement("Details");
                    writer.WriteAttributeString("width", worldSize.Width.ToString());
                    writer.WriteAttributeString("height", worldSize.Height.ToString());
                    writer.WriteAttributeString("quadWidth", quadSize.Width.ToString());
                    writer.WriteAttributeString("quadHeight", quadSize.Height.ToString());
                    writer.WriteAttributeString("events", events.Count.ToString());
                    writer.WriteAttributeString("collision", collisionRects.Count.ToString());
                    writer.WriteAttributeString("background", backgroundPath);

                    // loop through all the quads
                    for (int i = 0; i < worldSize.Width; i++)
                        for (int j = 0; j < worldSize.Height; j++)
                        {
                            writer.WriteStartElement("Quad");
                            writer.WriteAttributeString("x", world[i, j].X.ToString());
                            writer.WriteAttributeString("y", world[i, j].Y.ToString());
                            writer.WriteAttributeString("possibleTypes", world[i, j].Spawns.Count.ToString());

                            // loop through all the spawns
                            for (int k = 0; k < world[i, j].Spawns.Count; k++)
                            {
                                writer.WriteStartElement("Type");
                                writer.WriteAttributeString("type", world[i, j].Spawns[k].ObjectType.ToUpper());
                                writer.WriteAttributeString("amount", world[i, j].Spawns[k].Amount.ToString());
                                writer.WriteAttributeString("randomized", world[i, j].Spawns[k].Randomized.ToString());
                                writer.WriteAttributeString("x", world[i, j].Spawns[k].X.ToString());
                                writer.WriteAttributeString("y", world[i, j].Spawns[k].Y.ToString());
                                writer.WriteEndElement();
                            }

                            writer.WriteEndElement();
                        }
                    
                    // loops through all the events
                    for (int i = 0; i < events.Count; i++)
                    {
                        writer.WriteStartElement("Event");
                        writer.WriteAttributeString("type", events[i].EventType.ToUpper());
                        writer.WriteAttributeString("x", events[i].X.ToString());
                        writer.WriteAttributeString("y", events[i].Y.ToString());
                        writer.WriteAttributeString("width", events[i].Width.ToString());
                        writer.WriteAttributeString("height", events[i].Height.ToString());
                        writer.WriteEndElement();
                    }

                    // loop through all the collision rects
                    for (int i = 0; i < collisionRects.Count; i++ )
                    {
                        writer.WriteStartElement("Collision");
                        writer.WriteAttributeString("x", collisionRects[i].X.ToString());
                        writer.WriteAttributeString("y", collisionRects[i].Y.ToString());
                        writer.WriteAttributeString("width", collisionRects[i].Width.ToString());
                        writer.WriteAttributeString("height", collisionRects[i].Height.ToString());
                        writer.WriteEndElement();
                    }

                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }
            }
        }

        public void openWorldToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "xml";
            dlg.Filter = "XML Files (*.xml) | *.xml";
            dlg.FilterIndex = 0;
            dlg.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "//..//..//Resources//XML//World");
            if(DialogResult.OK == dlg.ShowDialog())
            {
                selected = new Quad(0, 0);
                selectedSpawn = new Spawn();
                selectedCollisionRect = new Rectangle();
                collisionRects = new List<Rectangle>();
                events = new List<EventSpawn>();

                XmlReaderSettings settings = new XmlReaderSettings();
                settings.ConformanceLevel = ConformanceLevel.Document;
                settings.IgnoreComments = true;
                settings.IgnoreWhitespace = true;

                using (XmlReader read = XmlReader.Create(dlg.FileName, settings))
                {
                    if(read.IsStartElement("Level"))
                    {
                        read.ReadStartElement("Level");
                        read.MoveToFirstAttribute();
                        worldSize.Width = read.ReadContentAsInt();
                        read.MoveToNextAttribute();
                        worldSize.Height = read.ReadContentAsInt();
                        read.MoveToNextAttribute();
                        quadSize.Width = read.ReadContentAsInt();
                        read.MoveToNextAttribute();
                        quadSize.Height = read.ReadContentAsInt();
                        read.MoveToNextAttribute();

                        // store amount of events
                        int numEvents = read.ReadContentAsInt();
                        read.MoveToNextAttribute();
                        // store amount of collision rects
                        int numCollision = read.ReadContentAsInt();
                        read.MoveToNextAttribute();

                        if(backgroundPath.Length > 0)
                        {
                            TM.UnloadTexture(backgroundID);
                        }
                        string p = "..//..//Resources//Graphics//";
                        backgroundPath = read.ReadContentAsString();
                        p += backgroundPath;
                        if(backgroundPath.Length > 0)
                            backgroundID = TM.LoadTexture(p);

                        world = new Quad[worldSize.Width, worldSize.Height];
                        read.ReadStartElement("Details");
                        for(int i = 0; i < worldSize.Width; i++)
                            for(int j = 0; j < worldSize.Height; j++)
                            {
                                world[i, j] = new Quad();
                                read.MoveToFirstAttribute();
                                world[i, j].X = read.ReadContentAsInt();
                                read.MoveToNextAttribute();
                                world[i, j].Y = read.ReadContentAsInt();
                                read.MoveToNextAttribute();

                                // store amount of possible types
                                int numTypes = read.ReadContentAsInt();
                                read.ReadStartElement("Quad");

                                for(int k = 0; k < numTypes; k++)
                                {
                                    read.MoveToFirstAttribute();
                                    ObjectSpawn oSpawn = new ObjectSpawn();
                                    oSpawn.ObjectType = read.ReadContentAsString();
                                    read.MoveToNextAttribute();
                                    oSpawn.Amount = read.ReadContentAsInt();
                                    read.MoveToNextAttribute();
                                    string b = read.ReadContentAsString();
                                    oSpawn.Randomized = false;
                                    if (b == "True") oSpawn.Randomized = true;
                                    read.MoveToNextAttribute();
                                    oSpawn.X = read.ReadContentAsInt();
                                    read.MoveToNextAttribute();
                                    oSpawn.Y = read.ReadContentAsInt();
                                    oSpawn.Width = 20;
                                    oSpawn.Height = 20;
                                    world[i, j].Spawns.Add(oSpawn);
                                    //worldObjects.
                                    bool success = false;
                                    foreach(string n in worldObjects)
                                    {
                                        if(n == oSpawn.ObjectType)
                                        {
                                            success = true;
                                            break;
                                        }
                                    }
                                    if(!success)
                                    {
                                        worldObjects.Add(oSpawn.ObjectType);
                                    }
                                    read.ReadStartElement("Type");
                                    
                                }
                                if(numTypes > 0)
                                    read.ReadEndElement();
                            }

                        for(int i = 0; i < numEvents; i++)
                        {
                            read.MoveToFirstAttribute();
                            EventSpawn eSpawn = new EventSpawn(Rectangle.Empty, "");
                            eSpawn.EventType = read.ReadContentAsString();
                            read.MoveToNextAttribute();
                            eSpawn.X = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            eSpawn.Y = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            eSpawn.Width = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            eSpawn.Height = read.ReadContentAsInt();
                            events.Add(eSpawn);
                            bool success = false;
                            foreach (string n in worldEvents)
                            {
                                if (n == eSpawn.EventType)
                                {
                                    success = true;
                                    break;
                                }
                            }
                            if (!success)
                            {
                                worldEvents.Add(eSpawn.EventType);
                            }
                            read.ReadStartElement();
                        }

                        for(int i = 0; i < numCollision; i++)
                        {
                            read.MoveToFirstAttribute();
                            Rectangle r = Rectangle.Empty;
                            r.X = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            r.Y = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            r.Width = read.ReadContentAsInt();
                            read.MoveToNextAttribute();
                            r.Height = read.ReadContentAsInt();
                            collisionRects.Add(r);
                            read.ReadStartElement();
                        }
                        read.ReadEndElement();
                        read.ReadEndElement();
                        numericUpDownX.Maximum = quadSize.Width * worldSize.Width;
                        numericUpDownY.Maximum = quadSize.Height * worldSize.Height;
                        listBox2.DataSource = null;
                        listBox2.DataSource = events;
                        comboBox1.DataSource = null;
                        comboBox1.DataSource = worldObjects;
                        comboBox2.DataSource = null;
                        comboBox2.DataSource = worldEvents;

                        panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                            worldSize.Height * quadSize.Height);
                    }
                }
            }
        }

        public void importBackgroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "png";
            //dlg.Filter = ".PNG (*.png) | *.png | .JPG (*.jpg) | *.jpg | .BMP (*.bmp) | *.bmp";
            dlg.Filter = "Image files (*.png;*jpg;*bmp;)|*.png;*jpg;*bmp;";

            dlg.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Directory.GetCurrentDirectory() + "//..//..//Resources//Graphics");

            if(DialogResult.OK == dlg.ShowDialog())
            {
                if(backgroundPath.Length > 0)
                {
                    TM.UnloadTexture(backgroundID);
                }
                backgroundID = TM.LoadTexture(dlg.FileName);
                backgroundPath = System.IO.Path.GetFileName(dlg.FileName);
            }
        }



    }
}
