using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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

        public override string ToString()
        {
            return eventType + " - " + this.X + ", " + this.Y;
        }
    }
}
