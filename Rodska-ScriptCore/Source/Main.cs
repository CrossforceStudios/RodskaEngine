using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Rodska.Math;

namespace Rodska
{
  

    public class RodskaLogger
    {
        public static void Main()
        {
            LogMessage("Hello World!");
            LogMessage(new Vector3(2, 2, 2));
        }
        public static void LogMessage(string message)
        {
            LogToRodska(message);
        }

        public static void LogMessage(Vector3 vector)
        {
            LogVec3ToRodska(vector);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void LogToRodska(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void LogVec3ToRodska(Vector3 vector);

    }
}
