namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;

    public sealed class FECgCoroutineSchedule : FECgEnum_byte
    {
        public FECgCoroutineSchedule(byte value, string name) : base(value, name) { }
    }

    public sealed class EMCgCoroutineSchedule : TCgEnumMap<FECgCoroutineSchedule, byte>
    {
        private static EMCgCoroutineSchedule _Instance;
        public static EMCgCoroutineSchedule Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCoroutineSchedule();
                }
                return _Instance;
            }
        }

        public static EMCgCoroutineSchedule Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCoroutineScheduleEqualityComparer : IEqualityComparer<FECgCoroutineSchedule>
    {
        public bool Equals(FECgCoroutineSchedule lhs, FECgCoroutineSchedule rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCoroutineSchedule x)
        {
            return x.GetHashCode();
        }
    }


    public static class ECgCoroutineSchedule
    {
        public static readonly FECgCoroutineSchedule Update = EMCgCoroutineSchedule.Get().Create("Update");
        public static readonly FECgCoroutineSchedule FixedUpdate = EMCgCoroutineSchedule.Get().Create("FixedUpdate");
        public static readonly FECgCoroutineSchedule  LateUpdate = EMCgCoroutineSchedule.Get().Create("LateUpdate");
        public static readonly FECgCoroutineSchedule PostRender = EMCgCoroutineSchedule.Get().Create("PostRender");
        public static readonly FECgCoroutineSchedule PreCull = EMCgCoroutineSchedule.Get().Create("PreCull");
        public static readonly FECgCoroutineSchedule PreRender = EMCgCoroutineSchedule.Get().Create("PreRender");
        public static readonly FECgCoroutineSchedule Manual = EMCgCoroutineSchedule.Get().Create("Manual");
    }

    public enum ECgCoroutineTransaction : byte
    {
        Allocate,
        Start,
        End,
        MAX
    }

    public enum ECgCoroutineEndReason : byte
    {
        EndOfExecution,
        StopMessage,
        StopCondition,
        Parent,
        UniqueInstance,
        Shutdown,
        Manual,
        MAX
    }
}
