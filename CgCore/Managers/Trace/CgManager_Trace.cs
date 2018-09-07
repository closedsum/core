namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    using Unity.Collections;

    #region "Enums"

    public enum ECgTraceTransaction : byte
    {
        Add,
        Complete,
        MAX
    }

    #endregion // Enums

    #region "Cache"

    public static class ECgManagerTraceCached
    {
        public static readonly string OnAsyncRequestCompleted = "FCgManager_Trace.OnAsyncRequestCompleted";
    }

    #endregion // Cache

    public class FCgManager_Trace
    {
        #region "Constants"

        public static readonly byte TRACE_TYPE_MAX = (byte)ECgTraceType.MAX;
        public static readonly byte TRACE_METHOD_MAX = (byte)ECgTraceMethod.MAX;

        public static readonly byte REQUEST_SIZE = 255;
        public static readonly byte RESPONSE_SIZE = 255;

        public static readonly byte SINGLETON = 1;
        public static readonly int EMPTY = 0;

        #endregion // Constants

        #region "Data Members"

        private static FCgManager_Trace _Instance;
        public static FCgManager_Trace Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Trace();
                }
                return _Instance;
            }
        }

        public FECgTime TimeType;

        public int RequestsProcessedPerTick;

        public ulong TraceCountLifetime;

        public Dictionary<ulong, ulong> TraceCountLifetimeByObjectId;
        public ulong[] TraceCountLifetimeByType;
        public ulong[] TraceCountLifetimeByMethod;

        public int TraceCountThisFrame;

        public Dictionary<ulong, ushort> TraceCountThisFrameByObjectId;
        public ushort[] TraceCountThisFrameByType;
        public ushort[] TraceCountThisFrameByMethod;

            #region "Request"

        public FCgTraceRequest[] Requests;

        public byte RequestIndex;

        public LinkedList<FCgTraceRequest> PendingRequests;

        public LinkedListNode<FCgTraceRequest> PendingRequestHead;
        public LinkedListNode<FCgTraceRequest> PendingRequestTail;

        public Dictionary<byte, FCgTraceRequest> PendingRequestMap;
        public Dictionary<ulong, FCgTraceRequest> PendingRequestsByTraceId;
        public Dictionary<ulong, Dictionary<byte, FCgTraceRequest>> PendingRequestsByObjectId;
        public Dictionary<ECgTraceType, Dictionary<byte, FCgTraceRequest>> PendingRequestsByType;
        public Dictionary<ECgTraceMethod, Dictionary<byte, FCgTraceRequest>> PendingRequestsByMethod;

            #endregion // Request

            #region "Response"

        public FCgTraceResponse[] Responses;

        public byte ResponseIndex;

            #endregion // Response

        #endregion // Data Members

        public FCgManager_Trace()
        {
            TimeType = ECgTime.Update;

            TraceCountLifetimeByObjectId = new Dictionary<ulong, ulong>();

            TraceCountLifetimeByType = new ulong[TRACE_TYPE_MAX];

            for (byte i = 0; i < TRACE_TYPE_MAX; ++i)
            {
                TraceCountLifetimeByType[i] = 0;
            }

            TraceCountLifetimeByMethod = new ulong[TRACE_METHOD_MAX];

            for (byte i = 0; i < TRACE_METHOD_MAX; ++i)
            {
                TraceCountLifetimeByMethod[i] = 0;
            }

            TraceCountLifetimeByObjectId = new Dictionary<ulong, ulong>();

            TraceCountThisFrameByType = new ushort[TRACE_TYPE_MAX];

            for (byte i = 0; i < TRACE_TYPE_MAX; ++i)
            {
                TraceCountThisFrameByType[i] = 0;
            }

            TraceCountThisFrameByMethod = new ushort[TRACE_METHOD_MAX];

            for (byte i = 0; i < TRACE_METHOD_MAX; ++i)
            {
                TraceCountThisFrameByMethod[i] = 0;
            }

            Requests = new FCgTraceRequest[REQUEST_SIZE];

            for (byte i = 0; i < REQUEST_SIZE; ++i)
            {
                Requests[i] = new FCgTraceRequest(i);
            }

            RequestIndex = 0;

            PendingRequests = new LinkedList<FCgTraceRequest>();

            PendingRequestMap = new Dictionary<byte, FCgTraceRequest>();
            PendingRequestsByTraceId = new Dictionary<ulong, FCgTraceRequest>();
            PendingRequestsByObjectId = new Dictionary<ulong, Dictionary<byte, FCgTraceRequest>>();
            PendingRequestsByType = new Dictionary<ECgTraceType, Dictionary<byte, FCgTraceRequest>>(new ECgTraceTypeEqualityComparer());

            for (byte i = 0; i < TRACE_TYPE_MAX; ++i)
            {
                Dictionary<byte, FCgTraceRequest> addMap = new Dictionary<byte, FCgTraceRequest>();
                PendingRequestsByType.Add((ECgTraceType)i, addMap);
            }

            PendingRequestsByMethod = new Dictionary<ECgTraceMethod, Dictionary<byte, FCgTraceRequest>>(new ECgTraceMethodEqualityComparer());

            for (byte i = 0; i < TRACE_METHOD_MAX; ++i)
            {
                Dictionary<byte, FCgTraceRequest> addMap = new Dictionary<byte, FCgTraceRequest>();
                PendingRequestsByMethod.Add((ECgTraceMethod)i, addMap);
            }

            Responses = new FCgTraceResponse[RESPONSE_SIZE];

            for (int i = 0; i < RESPONSE_SIZE; ++i)
            {
                Responses[i] = new FCgTraceResponse();
            }

            ResponseIndex = 0;
        }

        public static FCgManager_Trace Get()
        {
            return Instance;
        }

        public void Clear()
        {
            TraceCountLifetime = 0;
            TraceCountThisFrame = 0;

            for (byte i = 0; i < TRACE_TYPE_MAX; ++i)
            {
                TraceCountLifetimeByType[i] = 0;
                TraceCountThisFrameByType[i] = 0;
            }

            for (byte i = 0; i < TRACE_METHOD_MAX; ++i)
            {
                TraceCountLifetimeByMethod[i] = 0;
                TraceCountThisFrameByMethod[i] = 0;
            }

            for (byte i = 0; i < REQUEST_SIZE; ++i)
            {
                Requests[i].Reset();
            }

            PendingRequestHead = null;
            PendingRequestTail = null;

            PendingRequests.Clear();
            PendingRequestMap.Clear();
            PendingRequestsByObjectId.Clear();
            PendingRequestsByType.Clear();
            PendingRequestsByMethod.Clear();
        }

        public void Shutdown()
        {
            Clear();
        }

        public void SetTimeType(FECgTime timeType)
        {
            TimeType = timeType;
        }

        public void OnUpdate(float deltaTime)
        {
            // Reset TraceCountThisFrame
            TraceCountThisFrame = 0;

            for (byte i = 0; i < TRACE_TYPE_MAX; ++i)
            {
                TraceCountThisFrameByType[i] = 0;
            }

            for (byte i = 0; i < TRACE_METHOD_MAX; ++i)
            {
                TraceCountThisFrameByMethod[i] = 0;
            }

            // Process Requests
            int processCountMax = Mathf.Max(0, RequestsProcessedPerTick - TraceCountThisFrame);

            Dictionary<byte, FCgTraceRequest>.KeyCollection keys = PendingRequestMap.Keys;

            int keyCount = keys.Count;
            int count = Mathf.Min(keyCount, processCountMax);

            float currentTime = FCgManager_Time.Get().GetTimeSinceStart(TimeType);

            int index = 0;

            LinkedListNode<FCgTraceRequest> current = PendingRequestHead;

            while (current != null)
            {
                FCgTraceRequest request = current.Value;
                current                 = PendingRequestHead.Next;

                // If Processing, SKIP
                if (request.bProcessing)
                {
                    if (request.HasCommandCompleted())
                        OnAsyncRequestCompleted(request);
                    else
                       continue;
                }
                // If COMPLETED, Remove
                if (request.bCompleted)
                {
                    RemovePendingRequest(request);
                    continue;
                }
                // Check to remove STALE Request
                if (request.StaleTime > 0.0f &&
                    currentTime - request.StartTime >= request.StaleTime)
                {
                    RemovePendingRequest(request);
                    continue;
                }
                // PROCESS Request
                if (index < count)
                {
                    ProcessRequest(request);
                    IncrementTraceCount(request);
                }
                ++index;
            }
        }

        private void IncrementTraceCount(FCgTraceRequest request)
        {
            // Lifetime
            ++TraceCountLifetime;

            {
                ulong countById = ulong.MaxValue;

                if (TraceCountLifetimeByObjectId.TryGetValue(request.CallerId, out countById))
                {
                    ++(TraceCountLifetimeByObjectId[countById]);
                }
                else
                {
                    TraceCountLifetimeByObjectId.Add(request.CallerId, 1);
                }
            }

            ++(TraceCountLifetimeByType[(byte)request.Type]);
            ++(TraceCountLifetimeByMethod[(byte)request.Method]);
            // Frame
            ++TraceCountThisFrame;

            {
                ushort countById = ushort.MaxValue;

                if (TraceCountThisFrameByObjectId.TryGetValue(request.CallerId, out countById))
                {
                    ++(TraceCountThisFrameByObjectId[countById]);
                }
                else
                {
                    TraceCountThisFrameByObjectId.Add(request.CallerId, 1);
                }
            }

            ++(TraceCountThisFrameByType[(byte)request.Type]);
            ++(TraceCountThisFrameByMethod[(byte)request.Method]);
        }

        #region "Request"

        public FCgTraceRequest AllocateRequest()
        {
            for (byte i = 0; i < REQUEST_SIZE; ++i)
            {
                byte index              = (byte)((RequestIndex + i) % REQUEST_SIZE);
                FCgTraceRequest request = Requests[index];

                if (!request.bAllocated)
                {
                    request.bAllocated = true;
                    return request;
                }
            }
            FCgDebug.LogError("FCsManager_Trace.AllocateRequest: Pool is exhausted");
            return null;
        }

        private void AddPendingRequest(FCgTraceRequest request)
        {
            if (PendingRequestTail != null)
            {
                PendingRequests.AddAfter(request.Link, PendingRequestTail);
                PendingRequestTail = request.Link;
            }
            else
            {
                PendingRequestHead = request.Link;
                PendingRequestTail = PendingRequestHead;
            }

            byte requestId = request.Id;

            PendingRequestMap.Add(requestId, request);

            // TraceId
            /*
            const TCsTraceHandleId&HandleId = Request->Handle._Handle;

            if (HandleId != 0)
            {
                PendingRequestsByTraceId.Add(HandleId, Request);
            }
            */

            // ObjectId
            Dictionary<byte, FCgTraceRequest> map = null;

            if (PendingRequestsByObjectId.TryGetValue(request.CallerId, out map))
	        {
                map.Add(requestId, request);
            }
	        else
	        {
                Dictionary<byte, FCgTraceRequest> newMap = new Dictionary<byte, FCgTraceRequest>();
                newMap.Add(requestId, request);
                PendingRequestsByObjectId.Add(request.CallerId, newMap);
            }
            // Type
            Dictionary<byte, FCgTraceRequest> mapType = PendingRequestsByType[request.Type];
            mapType.Add(requestId, request);
            // Method
            Dictionary<byte, FCgTraceRequest> mapMethod = PendingRequestsByMethod[request.Method];
            mapMethod.Add(requestId, request);

            // Check if an EXISTING Request should be REPLACED
            if (!request.bProcessing && request.bReplacePending)
            {
                byte pendingRequestId          = request.PendingId;
                FCgTraceRequest pendingRequest = null;

                if (PendingRequestMap.TryGetValue(pendingRequestId, out pendingRequest))
                {
                    ReplacePendingRequest(pendingRequest, request);
                }
            }

            // LOG TRANSACTION
        }

        private void ReplacePendingRequest(FCgTraceRequest pendingRequest, FCgTraceRequest request)
        {
            // Update Maps
            byte pendingRequestId = pendingRequest.Id;

            PendingRequestMap.Remove(pendingRequestId);
            // TraceId
            //byte pendingHandleId = PendingRequest->Handle._Handle;

            //PendingRequestsByTraceId.Remove(PendingHandleId);
            // ObjectId
            Dictionary<byte, FCgTraceRequest> mapId = PendingRequestsByObjectId[pendingRequest.CallerId];
            mapId.Remove(pendingRequestId);
            // Type
            Dictionary<byte, FCgTraceRequest> mapType = PendingRequestsByType[pendingRequest.Type];
            mapType.Remove(pendingRequestId);
            // Method
            Dictionary<byte, FCgTraceRequest> mapMethod = PendingRequestsByMethod[pendingRequest.Method];
            mapMethod.Remove(pendingRequestId);

            LinkedListNode<FCgTraceRequest> pendingLink = pendingRequest.Link;

            PendingRequests.AddBefore(request.Link, pendingLink);
            PendingRequests.Remove(request.Link);

            // Check if Pending Link was the HEAD
            if (pendingLink == PendingRequestHead)
            {
                PendingRequestHead = request.Link;

                if (PendingRequests.Count == SINGLETON)
                {
                    PendingRequestTail = request.Link;
                }
            }

            // LOG

            pendingRequest.Reset();
        }

        private void RemovePendingRequest(FCgTraceRequest request)
        {
            // Update Maps
            byte requestId = request.Id;

            PendingRequestMap.Remove(requestId);
            // TraceId
            //const TCsTraceHandleId&HandleId = Request->Handle._Handle;

            //PendingRequestsByTraceId.Remove(HandleId);
            // ObjectId
            Dictionary<byte, FCgTraceRequest> mapId = PendingRequestsByObjectId[request.CallerId];
            mapId.Remove(requestId);
            // Type
            Dictionary<byte, FCgTraceRequest> mapType = PendingRequestsByType[request.Type];
            mapType.Remove(requestId);
            // Method
            Dictionary<byte, FCgTraceRequest> mapMethod = PendingRequestsByMethod[request.Method];
            mapMethod.Remove(requestId);

            // LOG TRANSACTION

            // Update HEAD of Queue
            LinkedListNode<FCgTraceRequest> link = request.Link;

            if (link == PendingRequestHead)
            {
                if (PendingRequests.Count > EMPTY)
                {
                    PendingRequestHead = link.Next;
                }
                else
                {
                    PendingRequestHead = null;
                    PendingRequestTail = null;
                }
            }
            request.Reset();
        }

        private bool ProcessRequest(FCgTraceRequest request)
        {
            /*
            if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
            {
                // Sphere around Start
                DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
                // Line from Start to End
                DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
            }
            */
            request.bProcessing = true;

            // Test (Check)
            if (request.Method == ECgTraceMethod.Test)
            {
                FCgDebug.LogWarning("FCsManager_Trace.ProcessRequest: There is NO Async Trace " + request.Method.ToString() + " Method. Use TraceMethod: Single or Multi.");
                request.Reset();
                return false;
            }

            // Line
            if (request.Type == ECgTraceType.Line)
            {
                request.ScheduleCommand();
                return true;
            }
            // Sweep (Cast)
            else
            if (request.Type == ECgTraceType.Sweep)
            {
                FCgDebug.LogWarning("FCsManager_Trace.ProcessRequest: There is NO Async Sweep (Cast) Trace Method. Use TraceType: Line.");
                request.Reset();
                return false;
            }
            // Overlap
            else
            if (request.Type == ECgTraceType.Overlap)
            {
                FCgDebug.LogWarning("FCsManager_Trace.ProcessRequest: There is NO Async Overlap (Cast) Trace Method. Use TraceType: Overlap.");
                request.Reset();
                return false;
            }
            return true;
        }

        #endregion // Request

        #region "Response"

        public FCgTraceResponse AllocateResponse()
        {
            for (byte i = 0; i < RESPONSE_SIZE; ++i)
            {
                byte index                = (byte)((ResponseIndex + i) % RESPONSE_SIZE);
                FCgTraceResponse response = Responses[index];

                if (!response.bAllocated)
                {
                    response.bAllocated = true;
                    return response;
                }
            }
            FCgDebug.LogError("FCsManager_Trace::AllocateResponse: Pool is exhausted");
            return null;
        }

        public void OnAsyncRequestCompleted(FCgTraceRequest request)
        {
            // Setup Response
            FCgTraceResponse response = AllocateResponse();

            response.CopyHitResults(ref request.Results);

            float currentTime = FCgManager_Time.Get().GetTimeSinceStart(TimeType);

            response.ResolveBuffers(currentTime);

            response.ElapsedTime = currentTime - request.StartTime;

            /*
            if (CsCVarDrawManagerTraceResponses->GetInt() == CS_CVAR_DRAW)
            {
                if (Response->bResult)
                {
                    // Sphere around Start
                    DrawDebugSphere(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
                    // Line from Start to End
                    DrawDebugLine(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, Response->OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
                }
            }
            */
            LogTransaction(ECgManagerTraceCached.OnAsyncRequestCompleted, ECgTraceTransaction.Complete, request, response);

            // Broadcast Response
            request.OnResponse_Event.Broadcast(request.Id, response);
            response.Reset();

            request.bProcessing = false;
            request.bCompleted = true;
        }

        #endregion // Response

        public FCgTraceResponse Trace(FCgTraceRequest request)
        {
            request.StartTime = FCgManager_Time.Get().GetTimeSinceStart(TimeType);

            bool addPending = !request.bForce && TraceCountThisFrame >= RequestsProcessedPerTick;

            // TODO: Print warning for a normal trace moved to Async
            if (addPending && !request.bAsync)
            {
                request.Reset();
                FCgDebug.LogWarning("FCsManager_Trace.Trace: Reached maximum RequestsProcessedPerTick: " + RequestsProcessedPerTick + "and Request is NOT Async. Abandoning Request.");
                return null;
            }

            // Async
            if (request.bAsync ||
                addPending)
            {
                // if NOT Pending, Start Async
                if (!addPending)
                {
                    // if Successful in processing Request, EXIT
                    if (ProcessRequest(request))
                    {
                        AddPendingRequest(request);
                        IncrementTraceCount(request);
                        return null;
                    }
                }

                // ADD Pending Request
                AddPendingRequest(request);
                return null;
            }
            // Normal
            else
            {
                /*
                if (CsCVarDrawManagerTraceRequests->GetInt() == CS_CVAR_DRAW)
                {
                    // Sphere around Start
                    DrawDebugSphere(GetWorld(), Request->Start, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
                    // Line from Start to End
                    DrawDebugLine(GetWorld(), Request->Start, Request->End, FColor::Red, false, 0.1f, 0, 1.0f);
                }
                */
                FCgTraceResponse response = AllocateResponse();

                response.ElapsedTime = 0.0f;

                // Line
                if (request.Type == ECgTraceType.Line)
                {
                    // Test
                    if (request.Method == ECgTraceMethod.Test)
                    {
                        // Linecast
                        response.bResult = Physics.Linecast(request.Start, request.End, request.LayerMask);
                    }
                    // Single
                    else
                    if (request.Method == ECgTraceMethod.Single)
                    {
                        FCgDebug.LogWarning("FCsManager_Trace.Trace: Line Trace Single is NOT supported. Use TraceMethod: Test or Multi. Abandoning Request.");
                    }
                    // Multi
                    else
                    if (request.Method == ECgTraceMethod.Multi)
                    {
                        // RaycastNonAlloc
                        Vector3 v       = request.End - request.Start;
                        float distance  = v.magnitude;
                        Vector3 dir     = distance > 0.0f ? v / distance : Vector3.zero;

                        float EXTEND = 0.1f;

                        response.OutHitCount = Physics.RaycastNonAlloc(request.Start, dir, response.OutHitBuffer, distance + EXTEND, request.LayerMask);
                        response.ResolveBuffers(request.StartTime);
                    }
                }
                // Sweep
                else
                if (request.Type == ECgTraceType.Sweep)
                {
                    // Test
                    if (request.Method == ECgTraceMethod.Test)
                    {
                        // Box
                        if (request.Shape == ECgCollisionShape.Box)
                        {
                            // CheckBox
                            response.bResult = Physics.CheckBox(request.BoxParams.Center, request.BoxParams.HalfExtents, request.BoxParams.Orientation, request.LayerMask);
                        }
                        // Sphere
                        else
                        if (request.Shape == ECgCollisionShape.Sphere)
                        {
                            // CheckSphere
                            response.bResult = Physics.CheckSphere(request.SphereParams.Position, request.SphereParams.Radius, request.LayerMask);
                        }
                        // Capsule
                        else
                        if (request.Shape == ECgCollisionShape.Capsule)
                        {
                            // CheckCapsule
                            response.bResult = Physics.CheckCapsule(request.CapsuleParams.Start, request.CapsuleParams.End, request.CapsuleParams.Radius, request.LayerMask);
                        }
                    }
                    // Single
                    else
                    if (request.Method == ECgTraceMethod.Single)
                    {
                        FCgDebug.LogWarning("FCsManager_Trace.Trace: Sweep Trace Single is NOT supported. Use TraceMethod: Test or Multi. Abandoning Request.");
                    }
                    // Multi
                    else
                    if (request.Method == ECgTraceMethod.Multi)
                    {
                        // Box
                        if (request.Shape == ECgCollisionShape.Box)
                        {
                            // BoxCastNonAlloc
                            Vector3 v      = request.End - request.Start;
                            float distance = v.magnitude;
                            Vector3 dir    = distance > 0.0f ? v / distance : Vector3.zero;

                            float EXTEND = 0.1f;

                            response.OutHitCount = Physics.BoxCastNonAlloc(request.BoxParams.Center, request.BoxParams.HalfExtents, dir, response.OutHitBuffer, request.BoxParams.Orientation, distance + EXTEND, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                        // Sphere
                        else
                        if (request.Shape == ECgCollisionShape.Sphere)
                        {
                            // SphereCastNonAlloc
                            Vector3 v       = request.End - request.Start;
                            float distance  = v.magnitude;
                            Vector3 dir     = distance > 0.0f ? v / distance : Vector3.zero;

                            float EXTEND = 0.1f;

                            response.OutHitCount = Physics.SphereCastNonAlloc(request.Start, request.SphereParams.Radius, dir, response.OutHitBuffer, distance + EXTEND, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                        // Capsule
                        else
                        if (request.Shape == ECgCollisionShape.Capsule)
                        {
                            // CapsuleCastNonAlloc
                            Vector3 v       = request.End - request.Start;
                            float distance  = v.magnitude;
                            Vector3 dir     = distance > 0.0f ? v / distance : Vector3.zero;

                            float EXTEND = 0.1f;

                            response.OutHitCount = Physics.CapsuleCastNonAlloc(request.CapsuleParams.Start, request.CapsuleParams.End, request.CapsuleParams.Radius, dir, response.OutHitBuffer, distance + EXTEND, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                    }
                }
                // Overlap
                else
                if (request.Type == ECgTraceType.Overlap)
                {
                    // Test
                    if (request.Method == ECgTraceMethod.Test)
                    {
                        FCgDebug.LogWarning("FCsManager_Trace.Trace: Overlap Trace Test is NOT supported. Use TraceMethod: Multi. Abandoning Request.");
                    }
                    // Single
                    else
                    if (request.Method == ECgTraceMethod.Single)
                    {
                        FCgDebug.LogWarning("FCsManager_Trace.Trace: Overlap Trace Single is NOT supported. Use TraceMethod: Multi. Abandoning Request.");
                    }
                    // Multi
                    else
                    if (request.Method == ECgTraceMethod.Multi)
                    {
                        // Box
                        if (request.Shape == ECgCollisionShape.Box)
                        {
                            // OverlapBoxNonAlloc
                            response.OutOverlapCount = Physics.OverlapBoxNonAlloc(request.BoxParams.Center, request.BoxParams.HalfExtents, response.OutOverlapBuffer, request.BoxParams.Orientation, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                        // Sphere
                        else
                        if (request.Shape == ECgCollisionShape.Sphere)
                        {
                            // OverlapSphereNonAlloc
                            response.OutOverlapCount = Physics.OverlapSphereNonAlloc(request.SphereParams.Position, request.SphereParams.Radius, response.OutOverlapBuffer, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                        // Capsule
                        else
                        if (request.Shape == ECgCollisionShape.Capsule)
                        {
                            // CapsuleCastNonAlloc
                            response.OutOverlapCount = Physics.OverlapCapsuleNonAlloc(request.CapsuleParams.Start, request.CapsuleParams.End, request.CapsuleParams.Radius, response.OutOverlapBuffer, request.LayerMask);
                            response.ResolveBuffers(request.StartTime);
                        }
                    }
                }
                IncrementTraceCount(request);
                request.Reset();

                /*
                if (CsCVarDrawManagerTraceResponses->GetInt() == CS_CVAR_DRAW)
                {
                    if (Response->bResult)
                    {
                        // Sphere around Start
                        DrawDebugSphere(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, 16.0f, 16, FColor::Green, false, 0.1f, 0, 1.0f);
                        // Line from Start to End
                        DrawDebugLine(GetWorld(), Response->OutHits[CS_FIRST].TraceStart, Response->OutHits[CS_FIRST].Location, FColor::Red, false, 0.1f, 0, 1.0f);
                    }
                }
                */
                return response;
            }
        }

        public virtual void LogTransaction(string functionName, ECgTraceTransaction transaction, FCgTraceRequest request, FCgTraceResponse response)
        {

        }
    }
}