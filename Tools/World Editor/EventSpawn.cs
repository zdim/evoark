using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Editor
{
    class EventSpawn : Spawn
    {
        string eventType;

        public string EventType
        {
            get { return eventType; }
            set { eventType = value; }
        }

        public EventSpawn(Rectangle r, string s)
        {
            this.X = r.X;
            this.Y = r.Y;
            this.Width = r.Width;
            this.Height = r.Height;
            this.EventType = s;
        }

        public override string ToString()
        {
            return eventType + " - " + this.X + ", " + this.Y;
        }
    }
}
