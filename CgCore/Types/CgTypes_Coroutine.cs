namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;

    public enum ECgCoroutineSchedule : byte
    {
        Update,
        FixedUpdate,
        LateUpdate,
        PostRender,
        PreCull,
        PreRender,
        Manual,
        MAX
    }

    public sealed class ECgCoroutineScheduleEqualityComparer : IEqualityComparer<ECgCoroutineSchedule>
    {
        public bool Equals(ECgCoroutineSchedule lhs, ECgCoroutineSchedule rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgCoroutineSchedule x)
        {
            return x.GetHashCode();
        }
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
