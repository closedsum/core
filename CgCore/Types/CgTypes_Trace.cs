namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public enum ECgTraceType : byte
    {
        Line,
        Sweep,
        Overlap,
        MAX
    }

    public sealed class ECgTraceTypeEqualityComparer : IEqualityComparer<ECgTraceType>
    {
        public bool Equals(ECgTraceType lhs, ECgTraceType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgTraceType x)
        {
            return x.GetHashCode();
        }
    }

    public enum ECgTraceMethod : byte
    {
        Test,
        Single,
        Multi,
        MAX
    }

    public sealed class ECgTraceMethodEqualityComparer : IEqualityComparer<ECgTraceMethod>
    {
        public bool Equals(ECgTraceMethod lhs, ECgTraceMethod rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgTraceMethod x)
        {
            return x.GetHashCode();
        }
    }

    public enum ECgCollisionShape : byte
    {
        Box,
        Sphere,
        Capsule,
        MAX
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

    public class FCgTraceResponse
    {
        #region "Constants"

        public static readonly int HIT_BUFFER = 16;
        public static readonly int OVERLAP_BUFFER = 16;

        #endregion // Constants

        #region "Data Members"

        public bool bAllocated;

        public bool bResult;

        public float ElapsedTime;

        public RaycastHit[] OutHits;
        public int OutHitCount;

	    public Collider[] OutOverlaps;
        public int OutOverlapCount;

        #endregion // Data Members

        public FCgTraceResponse()
        {
            OutHits = new RaycastHit[HIT_BUFFER];
            OutOverlaps = new Collider[OVERLAP_BUFFER];

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            bResult = false;
            ElapsedTime = 0.0f;

            OutHitCount = 0;
            OutOverlapCount = 0;
        }
    }

    public class FCgTraceRequest
    {
        #region "Constants"

        public static readonly int NO_LAYER = 0;
        public static readonly ulong INVALID_CALLER_ID = ulong.MaxValue;
        public static readonly byte INVALID_REQUEST_ID = byte.MaxValue;

        #endregion // Constants

        #region "Data Members"

        public byte Id;
        public bool bAllocated;
        public bool bForce;
        public bool bProcessing;
        public bool bCompleted;
        public float StartTime;
        public float StaleTime;

        public object Caller;
        public ulong CallerId;
       
        public class FOnRespone : TCgMulticastDelegate_TwoParams<byte, FCgTraceResponse> { }
        public FOnRespone OnResponse_Event;

        public bool bAsync;

        public ECgTraceType Type;
        public ECgTraceMethod Method;

        public Vector3 Start;
        public Vector3 End;

        public Vector3 Rotation;

        public int LayerMask;

        public ECgCollisionShape Shape;

        public bool bReplacePending;
        public byte PendingId;

        public LinkedListNode<FCgTraceRequest> Link;

        #endregion // Data Members

        public FCgTraceRequest()
        {
            Reset();
        }

        public FCgTraceRequest(byte id)
        {
            Id = id;

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            bForce = false;
            bProcessing = false;
            bCompleted = false;
            StartTime = 0.0f;
            StaleTime = 1.0f;
            Caller = null;
            CallerId = INVALID_CALLER_ID;

            OnResponse_Event.Clear();

            bAsync = false;
            Type = ECgTraceType.MAX;
            Method = ECgTraceMethod.MAX;
            Start = Vector3.zero;
            End = Vector3.zero;
            Rotation = Vector3.zero;
            LayerMask = NO_LAYER;
            Shape = ECgCollisionShape.MAX;
            bReplacePending = false;
            PendingId = INVALID_REQUEST_ID;

            Link = null;
        }
    }
}
