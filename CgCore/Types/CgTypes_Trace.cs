namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgTraceResponse
    {
        public bool bAllocated;

        public bool bResult;

        public float ElapsedTime;

        public List<FCgHitResult> OutHits;

	    public List<FCgOverlapResult> OutOverlaps;

	    public FCgTraceResponse()
        {
            OutHits = new List<FCgHitResult>();
            OutOverlaps = new List<FCgOverlapResult>();

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            bResult = false;
            ElapsedTime = 0.0f;

            OutHits.Clear();
            OutOverlaps.Clear();
        }
    }

    public class FCgTraceRequest
    {
        public FCgTraceRequest()
        {

        }
    }
}
