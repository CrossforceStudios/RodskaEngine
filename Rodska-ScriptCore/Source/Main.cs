using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Rodska
{
    public struct Vector3
    {
        public float X, Y, Z;

        public Vector3(float x, float y, float z)
        {
            X = x; Y = y; Z = z; 
        }
    }

    public class RodskaLogger
    {
        public static void Main()
        {
            LogMessage("Hello World!");
        }
        public static void LogMessage(string message)
        {
            LogToRodska(message);
        }

        public static  void LogVector3Message(Vector3 vector)
        {
            LogVec3ToRodska(vector);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void LogToRodska(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void LogVec3ToRodska(Vector3 vector);

    }
}
