namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    using Unity.Collections;
    using Unity.Jobs;

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

    public class FCgTraceResponse
    {
        #region "Constants"

        public static readonly int HIT_BUFFER = 16;
        public static readonly int OVERLAP_BUFFER = 16;

        public static readonly int EMPTY = 0;

        #endregion // Constants

        #region "Data Members"

        public bool bAllocated;

        public bool bResult;

        public float ElapsedTime;

        public RaycastHit[] OutHitBuffer;
        public FCgHitResult[] OutHits;
        public int OutHitCount;

	    public Collider[] OutOverlapBuffer;
        public FCgOverlapResult[] OutOverlaps;
        public int OutOverlapCount;

        #endregion // Data Members

        public FCgTraceResponse()
        {
            OutHitBuffer = new RaycastHit[HIT_BUFFER];
            OutHits = new FCgHitResult[HIT_BUFFER];

            for (int i = 0; i < HIT_BUFFER; ++i)
            {
                OutHits[i] = new FCgHitResult();
            }

            OutOverlapBuffer = new Collider[OVERLAP_BUFFER];
            OutOverlaps = new FCgOverlapResult[OVERLAP_BUFFER];

            for (int i = 0; i < OVERLAP_BUFFER; ++i)
            {
                OutOverlaps[i] = new FCgOverlapResult();
            }

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            bResult = false;
            ElapsedTime = 0.0f;

            foreach (FCgHitResult r in OutHits)
            {
                r.Reset();
            }
            OutHitCount = 0;

            foreach (FCgOverlapResult r in OutOverlaps)
            {
                r.Reset();
            }
            OutOverlapCount = 0;
        }

        public void CopyHitResults(ref NativeArray<RaycastHit> results)
        {
            OutHitCount = 0;

            int len = results.Length;

            for (int i = 0; i < len; ++i)
            {
                if (results[i].distance <= 0.0f ||
                    results[i].distance == float.MaxValue)
                    continue;
                OutHitBuffer[i] = results[i];
                ++OutHitCount;
            }
        }

        public void ResolveHitBuffers(float time, Vector3 start, Vector3 end)
        {
            for (int i = 0; i < OutHitCount; ++i)
            {
                OutHits[i].Set(time, start, end, ref OutHitBuffer[i]);
            }
            bResult = OutHitCount > EMPTY;
        }

        public void ResolveOverlapBuffers(float time)
        {
            for (int i = 0; i < OutOverlapCount; ++i)
            {
                OutOverlaps[i].Set(time, OutOverlapBuffer[i]);
            }
            bResult = OutOverlapCount > EMPTY;
        }
    }

    public class FCgTraceRequest
    {
        #region "Constants"

        public static readonly int NO_LAYER = 0;
        public static readonly ulong INVALID_CALLER_ID = ulong.MaxValue;
        public static readonly byte INVALID_REQUEST_ID = byte.MaxValue;

        public static readonly int HIT_BUFFER = 16;

        public static readonly RaycastHit DEFAULT_RAYCAST_HIT = new RaycastHit();
        public static readonly RaycastCommand DEFAULT_RAYCAST_COMMAND = new RaycastCommand();

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

        public NativeArray<RaycastHit> Results;
        public NativeArray<RaycastCommand> Commands;

        public JobHandle Handle;

        public ECgTraceType Type;
        public ECgTraceMethod Method;

        public Vector3 Start;
        public Vector3 End;

        public Vector3 Rotation;

        public int LayerMask;

        public ECgCollisionShape Shape;

        public FCgCollisionBoxParams BoxParams;
        public FCgCollisionSphereParams SphereParams;
        public FCgCollisionCapsuleParams CapsuleParams;

        public bool bReplacePending;
        public byte PendingId;

        public LinkedListNode<FCgTraceRequest> Link;

        #endregion // Data Members

        public FCgTraceRequest()
        {
            Results = new NativeArray<RaycastHit>(HIT_BUFFER, Allocator.Persistent);
            Commands = new NativeArray<RaycastCommand>(1, Allocator.Persistent);

            BoxParams = new FCgCollisionBoxParams();
            SphereParams = new FCgCollisionSphereParams();
            CapsuleParams = new FCgCollisionCapsuleParams();

            Reset();
        }

        public FCgTraceRequest(byte id)
        {
            Id = id;

            Results = new NativeArray<RaycastHit>(HIT_BUFFER, Allocator.Persistent);
            Commands = new NativeArray<RaycastCommand>(1, Allocator.Persistent);

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

            for (int i = 0; i < HIT_BUFFER; ++i)
            {
                Results[i] = DEFAULT_RAYCAST_HIT;
            }

            Commands[0] = DEFAULT_RAYCAST_COMMAND;

            Type = ECgTraceType.MAX;
            Method = ECgTraceMethod.MAX;
            Start = Vector3.zero;
            End = Vector3.zero;
            Rotation = Vector3.zero;
            LayerMask = NO_LAYER;
            Shape = ECgCollisionShape.MAX;

            BoxParams.Reset();
            SphereParams.Reset();
            CapsuleParams.Reset();

            bReplacePending = false;
            PendingId = INVALID_REQUEST_ID;

            Link = null;
        }

        public void ScheduleCommand()
        {
            RaycastCommand command = new RaycastCommand();
            command.from        = Start;
            command.direction   = (End - Start).normalized;
            command.layerMask   = LayerMask;
            command.maxHits     = HIT_BUFFER;
            
            Commands[0] = command;

            Handle = RaycastCommand.ScheduleBatch(Commands, Results, 1);
        }

        public bool HasCommandCompleted()
        {
            return Handle.IsCompleted;
        }
    }
}
