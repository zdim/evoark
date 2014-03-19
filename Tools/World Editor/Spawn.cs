using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class Spawn
    {
        public enum Object { None, Player, Copperhead, Cobra, Mamba, Coral, Moccasin, Asteroid, Planet, }

        Object obj;

        public Object Obj
        {
            get { return obj; }
            set { obj = value; }
        }

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

        int amount;

        public int Amount
        {
            get { return amount; }
            set { amount = value; }
        }

        public override string ToString()
        {
            string name = amount.ToString() + " - " + obj.ToString();
            return name;
        }
    }
}
