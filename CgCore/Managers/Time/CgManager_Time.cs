namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public sealed class FECgTime : FECgEnum_byte
    {
        public FECgTime(byte value, string name) : base(value, name) { }
    }

    public sealed class EMCgTime : TCgEnumMap<FECgTime, byte>
    {
        private static EMCgTime _Instance;
        public static EMCgTime Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgTime();
                }
                return _Instance;
            }
        }

        public static EMCgTime Get()
        {
            return Instance;
        }
    }

    public sealed class FECgTimeEqualityComparer : IEqualityComparer<FECgTime>
    {
        public bool Equals(FECgTime lhs, FECgTime rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgTime x)
        {
            return x.GetHashCode();
        }
    }

    public static class ECgTime
    {
        public static readonly FECgTime Update = EMCgTime.Get().Create("Update");
    }

    #endregion // Enums

    public class FCgManager_Time
    {
        #region "Data Members"

        private static FCgManager_Time _Instance;
        public static FCgManager_Time Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Time();
                }
                return _Instance;
            }
        }

        private Dictionary<FECgTime, float> LastRealtimeSinceStartup;
        private Dictionary<FECgTime, float> TimeSinceStart;
        private Dictionary<FECgTime, float> DeltaTime;
        private Dictionary<FECgTime, bool> bPaused;

        #endregion // Data Members

        public FCgManager_Time()
        {
            LastRealtimeSinceStartup = new Dictionary<FECgTime, float>(new FECgTimeEqualityComparer());
            TimeSinceStart = new Dictionary<FECgTime, float>(new FECgTimeEqualityComparer());
            DeltaTime = new Dictionary<FECgTime, float>(new FECgTimeEqualityComparer());
            bPaused = new Dictionary<FECgTime, bool>(new FECgTimeEqualityComparer());

            int count = EMCgTime.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                FECgTime e = EMCgTime.Get().GetEnumAt(i);

                TimeSinceStart.Add(e, 0.0f);
                DeltaTime.Add(e, 0.0f);
                bPaused.Add(e, false);
            }
        }

        public static FCgManager_Time Get()
        {
            return Instance;
        }

        public void Update(FECgTime time)
        {
            float deltaTime = Time.realtimeSinceStartup - LastRealtimeSinceStartup[time];

            if (!bPaused[time])
            {
                TimeSinceStart[time] += deltaTime;
                DeltaTime[time]       = deltaTime;
            }
            else
            {
                DeltaTime[time] = 0.0f;
            }
        }

        public float GetDeltaTime(FECgTime timeType)
        {
            return DeltaTime[timeType];
        }

        public float GetTimeSinceStart(FECgTime timeType)
        {
            return TimeSinceStart[timeType];
        }

        public void Pause(FECgTime timeType)
        {
            bPaused[timeType] = true;
        }

        public void UnPause(FECgTime timeType)
        {
            bPaused[timeType] = false;
        }

        public void Reset(FECgTime timeType)
        {
            TimeSinceStart[timeType] = 0.0f;
            DeltaTime[timeType] = 0.0f;
            bPaused[timeType] = false;
        }
    }
}
