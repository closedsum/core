namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public enum ECgCollisionShape : byte
    {
        Box,
        Sphere,
        Capsule,
        MAX
    }

    public class FCgCollisionBoxParams
    {
        public Vector3 Center;
        public Vector3 HalfExtents;
        public Quaternion Orientation;

        public FCgCollisionBoxParams() { }
        public FCgCollisionBoxParams(Vector3 center, Vector3 halfExtents, Quaternion orientation)
        {
            Set(center, halfExtents, orientation);
        }

        public void Set(Vector3 center, Vector3 halfExtents, Quaternion orientation)
        {
            Center = center;
            HalfExtents = halfExtents;
            Orientation = orientation;
        }

        public void Reset()
        {
            Center = Vector3.zero;
            HalfExtents = Vector3.zero;
            Orientation = Quaternion.identity;
        }
    }

    public class FCgCollisionSphereParams
    {
        public Vector3 Position;
        public float Radius;

        public FCgCollisionSphereParams() { }
        public FCgCollisionSphereParams(Vector3 position, float radius)
        {
            Set(position, radius);
        }

        public void Set(Vector3 position, float radius)
        {
            Position = position;
            Radius = radius;
        }

        public void Reset()
        {
            Position = Vector3.zero;
            Radius = 0.0f;
        }
    }

    public class FCgCollisionCapsuleParams
    {
        public Vector3 Start;
        public Vector3 End;
        public float Radius;

        public FCgCollisionCapsuleParams() { }
        public FCgCollisionCapsuleParams(Vector3 start, Vector3 end, float radius)
        {
            Set(start, end, radius);
        }

        public void Set(Vector3 start, Vector3 end, float radius)
        {
            Start = start;
            End = end;
            Radius = radius;
        }

        public void Reset()
        {
            Start = Vector3.zero;
            End = Vector3.zero;
            Radius = 0.0f;
        }
    }

    public sealed class ECgCollisionShapeEqualityComparer : IEqualityComparer<ECgCollisionShape>
    {
        public bool Equals(ECgCollisionShape lhs, ECgCollisionShape rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgCollisionShape x)
        {
            return x.GetHashCode();
        }
    }

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

        public Transform _Transform;
        public Collider _Collider;
        public Rigidbody _RigidBody;

        public string BoneName;

        public FCgHitResult()
        {
            Reset();
        }

        public void Reset()
        {
            Time = 0.0f;
            Distance = 0.0f;
            Location = Vector3.zero;
            ImpactPoint = Vector3.zero;
            Normal = Vector3.zero;
            ImpactNormal = Vector3.zero;
            TraceStart = Vector3.zero;
            TraceEnd = Vector3.zero;
            _Transform = null;
            _Collider = null;
            _RigidBody = null;
            BoneName = "";
        }

        public void Copy(FCgHitResult from)
        {
            Time = from.Time;
            Distance = from.Distance;
            Location = from.Location;
            ImpactPoint = from.ImpactPoint;
            Normal = from.Normal;
            ImpactNormal = from.ImpactNormal;
            TraceStart = from.TraceStart;
            TraceEnd = from.TraceEnd;
            _Transform = from._Transform;
            _Collider = from._Collider;
            _RigidBody = from._RigidBody;
            BoneName = from.BoneName;
        }

        public void Set(float time, ref RaycastHit hit)
        {
            Time = time;
            Distance = hit.distance;
            Location = hit.point;
            ImpactPoint = hit.point;
            Normal = hit.normal;
            ImpactNormal = hit.normal;
            _Transform = hit.transform;
            _Collider = hit.collider;
            _RigidBody = hit.rigidbody;
        }

        public Transform GetTransform() { return _Transform; }
        public Collider GetCollider() { return _Collider; }
        public Rigidbody GetRigidBody() { return _RigidBody; }
    }

    public class FCgOverlapResult
    {
        public float Time;

        public Transform _Transform;
        public Collider _Collider;

        public FCgOverlapResult()
        {
            Reset();
        }

        public void Reset()
        {
            Time = 0.0f;
            _Transform = null;
            _Collider = null;
        }

        public void Copy(FCgOverlapResult from)
        {
            Time = from.Time;
            _Transform = from._Transform;
            _Collider = from._Collider;
        }

        public void Set(float time, Collider collider)
        {
            Time = time;
            _Transform = collider.transform;
            _Collider = collider;
        }

        public Transform GetTransform() { return _Transform; }
        public Collider GetCollider() { return _Collider; }
    }
}
