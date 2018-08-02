namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgHitResult
    {
        public float Time;

        public float Distance;

        public Vector3 Location;

        public Vector3 ImpactPoint;

        public Vector3 Normal;

        public Vector3 ImpactNormal;

        public Vector3 TraceStart;

        public Vector3 TraceEnd;

        public MonoBehaviour Object;

        public MonoBehaviour Component;

        public string BoneName;

        public FCgHitResult()
        {
            Reset();
        }

        public void Reset()
        {

        }

        public void Copy(FCgHitResult From)
        {

        }

        public MonoBehaviour GetObject() { return Object; }
        public T GetObject<T>() where T : MonoBehaviour { return (T)GetObject(); }
    }

    public class FCgOverlapResult
    {
        public FCgOverlapResult()
        {
            Reset();
        }

        public void Reset()
        {

        }
    }
}
