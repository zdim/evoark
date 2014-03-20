using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class ObjectSpawn : Spawn
    {
        public enum Object { None, Player, Copperhead, Cobra, Mamba, Coral, Moccasin, Asteroid, Planet, }

        Object obj;

        public Object Obj
        {
            get { return obj; }
            set { obj = value; }
        }

        int amount;

        public int Amount
        {
            get { return amount; }
            set { amount = value; }
        }

        public override string ToString()
        {
            return amount.ToString() + " - " + obj.ToString();
        }
    }
}