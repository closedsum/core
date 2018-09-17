namespace CgCore
{
    using System;

    using UnityEngine;

    public enum ECgViewType : byte
    {
        FirstPerson,
        ThirdPerson,
        VR,
        MAX
    }

    public class FCgDrawDistance
    {
        public float Distance;

        public float DistanceSq;

        public FCgDrawDistance()
        {
            Reset();
        }

        public void Square()
        {
            DistanceSq = Distance * Distance;
        }

        public string ToStr()
	    {
		    return "Distance=" + Distance;
	    }

	    public bool InitFromString(string sourceString)
        {
            Distance = 0.0f;

            // The initialization is only successful if the Distance values can all be parsed from the string
            bool bSuccessful = false;// FParse::Value(*InSourceString, TEXT("Distance="), Distance);

            Square();

            return bSuccessful;
        }

        public void Reset()
        {
            Distance = 3000.0f;
            Square();
        }
    }

    [Serializable]
    public struct S_FCgFpvDrawDistance
    {
        [SerializeField]
        public float Distance1P;
        [SerializeField]
        public float Distance1PSq;
        [SerializeField]
        public float Distance3P;
        [SerializeField]
        public float Distance3PSq;
    }

    public class FCgFpvDrawDistance
    {
        public float Distance1P;

        public float Distance1PSq;

        public float Distance3P;

        public float Distance3PSq;

        public FCgFpvDrawDistance()
        {
            Reset();
        }

        public void Square()
        {
            Distance1PSq = Distance1P * Distance1P;
            Distance3PSq = Distance3P * Distance3P;
        }

        public float Get(ECgViewType viewType)
	    {
		    if (viewType == ECgViewType.FirstPerson || viewType == ECgViewType.VR)
			    return Distance1P;
		    if (viewType == ECgViewType.ThirdPerson)
			    return Distance3P;
		    return 0.0f;
	    }

	    public float GetSquared(ECgViewType viewType)
	    {
		    if (viewType == ECgViewType.FirstPerson || viewType == ECgViewType.VR)
			    return Distance1PSq;
		    if (viewType == ECgViewType.ThirdPerson)
			    return Distance3PSq;
            return 0.0f;
	    }

	    public string ToStr()
	    {
		    return "1P=" + Distance1P + " 3P=" + Distance3P;
	    }

	    public bool InitFromString(string sourceString)
        {
            Distance1P = Distance3P = 0.0f;

            // The initialization is only successful if the Distance1P and Distance3P values can all be parsed from the string
            bool bSuccessful = false;// FParse::Value(*InSourceString, TEXT("1P="), Distance1P) && FParse::Value(*InSourceString, TEXT("3P="), Distance3P);

            Square();

            return bSuccessful;
        }

        public void Reset()
        {
            Distance1P = 3000.0f;
            Distance3P = 3000.0f;
            Square();
        }
    }
}