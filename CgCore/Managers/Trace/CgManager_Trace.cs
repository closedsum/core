namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public enum ECgTraceTransaction : byte
    {
        Add,
        Complete,
        MAX
    }

    #endregion // Enums

    public class FCgManager_Trace
    {
        #region "Constants"

        public static readonly int REQUEST_SIZE = 255;
        public static readonly int RESPONSE_SIZE = 255;

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

        public int RequestsProcessedPerTick;

        public ulong TraceCountLifetime;

        public Dictionary<ulong, ulong> TraceCountLifetimeByObjectId;
        //uint64 TraceCountLifetimeByType[ECS_TRACE_TYPE_MAX];
        //uint64 TraceCountLifetimeByMethod[ECS_TRACE_METHOD_MAX];
        //uint64 TraceCountLifetimeByQuery[ECS_TRACE_QUERY_MAX];

        public int TraceCountThisFrame;

        public Dictionary<ulong, ushort> TraceCountThisFrameByObjectId;
        //uint16 TraceCountThisFrameByType[ECS_TRACE_TYPE_MAX];
        //uint16 TraceCountThisFrameByMethod[ECS_TRACE_METHOD_MAX];
        //uint16 TraceCountThisFrameByQuery[ECS_TRACE_QUERY_MAX];

            #region "Request"

        public FCgTraceRequest[] Requests;

        public LinkedList<FCgTraceRequest> PendingRequests;

        public LinkedListNode<FCgTraceRequest> PendingRequestHead;
        public LinkedListNode<FCgTraceRequest> PendingRequestTail;

        public Dictionary<byte, FCgTraceRequest> PendingRequestMap;
        public Dictionary<ulong, FCgTraceRequest> PendingRequestsByTraceId;
        public Dictionary<ulong, Dictionary<byte, FCgTraceRequest>> PendingRequestsByObjectId;
        //TMap<TCsTraceType, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByType;
        //TMap<TCsTraceMethod, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByMethod;
        //TMap<TCsTraceQuery, TMap<TCsTraceRequestId, FCsTraceRequest*>> PendingRequestsByQuery;

            #endregion // Request

            #region "Response"

        public FCgTraceResponse[] Responses;

        public byte ResponseIndex;

            #endregion // Response

        #endregion // Data Members

        public FCgManager_Trace() { }

        public static FCgManager_Trace Get()
        {
            return Instance;
        }

        public static void Clear()
        {

        }

        public static void Shutdown()
        {

        }

        public void OnUpdate(float deltaTime)
        {

        }

        private void IncrementTraceCount(FCgTraceRequest request)
        {

        }

        #region "Request"

        public FCgTraceRequest AllocateRequest()
        {
            return null;
        }

        private void AddPendingRequest(FCgTraceRequest request)
        {

        }

        private void ReplacePendingRequest(FCgTraceRequest pendingRequest, FCgTraceRequest request)
        {

        }

        private void RemovePendingRequest(FCgTraceRequest request)
        {

        }

        private bool ProcessRequest(FCgTraceRequest request)
        {
            return false;
        }

        #endregion // Request

        #region "Response"

        public FCgTraceResponse AllocateResponse()
        {
            return null;
        }

        //public void OnTraceResponse()
        //public void OnOverlapResponse()

        #endregion // Response

        public FCgTraceResponse Trace(FCgTraceRequest request)
        {
            return null;
        }

        public virtual void LogTransaction(string functionName, ECgTraceTransaction transaction, FCgTraceRequest request, FCgTraceResponse response)
        {

        }
    }
}