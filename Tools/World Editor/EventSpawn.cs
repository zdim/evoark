using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class EventSpawn : Spawn
    {
        public enum Event { Example, Stargate, }

        Event evnt;

        public Event Evnt
        {
            get { return evnt; }
            set { evnt = value; }
        }

        int width;

        public int Width
        {
            get { return width; }
            set { width = value; }
        }

        int height;

        public int Height
        {
            get { return height; }
            set { height = value; }
        }

        public override string ToString()
        {
            return evnt.ToString();
        }
    }
}
