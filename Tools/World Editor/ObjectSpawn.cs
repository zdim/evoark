using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class ObjectSpawn : Spawn
    {
        string objectType;

        public string ObjectType
        {
            get { return objectType; }
            set { objectType = value; }
        }

        int amount;

        public int Amount
        {
            get { return amount; }
            set { amount = value; }
        }

        bool randomized;

        public bool Randomized
        {
            get { return randomized; }
            set { randomized = value; }
        }

        public override string ToString()
        {
            if(!randomized)
                return amount.ToString() + " - " + objectType;
            return amount.ToString() + " - R - " + objectType;
        }
    }
}