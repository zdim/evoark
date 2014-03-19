using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class Quad
    {
        int x;

        public int X
        {
            get { return x; }
            set { x = value; }
        }

        int y;

        public int Y
        {
            get { return y; }
            set { y = value; }
        }

        public Quad(int x, int y)
        {
            this.x = x;
            this.y = y;
            spawns.Clear();
        }

        public Quad()
        {
            x = -1;
            y = -1;
            spawns.Clear();
        }

        List<Spawn> spawns = new List<Spawn>();

        public List<Spawn> Spawns
        {
            get { return spawns; }
            set { spawns = value; }
        }
    }
}
