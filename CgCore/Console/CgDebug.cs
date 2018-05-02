namespace CgCore
{
    using UnityEngine;

    public static class CgDebug
    {
        public static void Log(object msg)
        {
            Debug.Log(msg);
        }

        public static void LogWarning(object msg)
        {
            Debug.LogWarning(msg);
        }

        public static void LogError(object msg)
        {
            Debug.LogError(msg);
        }
    }
}
