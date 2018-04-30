// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public sealed class CgCoroutinePayload
    {
        public bool IsAllocated;

        public ECgCoroutineSchedule Schedule;

        public IEnumerator Fiber;
        public object Owner;
        public string OwnerName;
        public byte RoutineType;
        public CgRoutine.CoroutineStopCondition StopCondition;

        public CgRoutine.AddRoutine.Event Add;
        public CgRoutine.RemoveRoutine.Event Remove;

        public CgCoroutinePayload()
        {
            StopCondition = new CgRoutine.CoroutineStopCondition();
        }

        public void Reset()
        {
            IsAllocated = false;
            Schedule = ECgCoroutineSchedule.MAX;
            Fiber = null;
            Owner = null;
            OwnerName = "";
            RoutineType = CgRoutine.INVALID_TYPE;
            StopCondition.Clear();
            Add = null;
            Remove = null;
        }
    }

    public class CgCoroutineScheduler
    {
        #region "Constants"

        private const int EMPTY = 0;
        private const ushort POOL_SIZE = 2048;

        #endregion // Constants

        #region "Data Members"

        private static CgCoroutineScheduler instance;
        public static CgCoroutineScheduler Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new CgCoroutineScheduler();
                }
                return instance;
            }
        }

        private int currentFrame;
        private float currentTime;

        public Dictionary<ECgCoroutineSchedule, List<CgRoutine>> Pools;
        public Dictionary<ECgCoroutineSchedule, int> PoolIndicies;
        public Dictionary<ECgCoroutineSchedule, List<CgRoutine>> RoutinesRunning;

        public Dictionary<ECgCoroutineSchedule, CgRoutine> Heads;
        public Dictionary<ECgCoroutineSchedule, CgRoutine> Tails;

            #region "Payload"

        private List<CgCoroutinePayload> Payloads;

        private int PayloadIndex;

            #endregion // Payload

        #endregion // Data Members

        // Constructor

        public CgCoroutineScheduler()
        {
            Pools = new Dictionary<ECgCoroutineSchedule, List<CgRoutine>>(new ECgCoroutineScheduleEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                List<CgRoutine> routines = new List<CgRoutine>();
                ECgCoroutineSchedule schedule = (ECgCoroutineSchedule)i;

                for (ushort j = 0; j < POOL_SIZE; ++j)
                {
                    routines.Add(new CgRoutine(j, schedule, SetTail));
                }
                Pools[(ECgCoroutineSchedule)i] = routines;
            }

            PoolIndicies = new Dictionary<ECgCoroutineSchedule, int>(new ECgCoroutineScheduleEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                PoolIndicies[(ECgCoroutineSchedule)i] = 0;
            }

            RoutinesRunning = new Dictionary<ECgCoroutineSchedule, List<CgRoutine>>(new ECgCoroutineScheduleEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                RoutinesRunning[(ECgCoroutineSchedule)i] = new List<CgRoutine>();
            }

            Heads = new Dictionary<ECgCoroutineSchedule, CgRoutine>(new ECgCoroutineScheduleEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                Heads[(ECgCoroutineSchedule)i] = null;
            }

            Tails = new Dictionary<ECgCoroutineSchedule, CgRoutine>(new ECgCoroutineScheduleEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                Tails[(ECgCoroutineSchedule)i] = null;
            }

            Payloads = new List<CgCoroutinePayload>();

            for (byte i = 0; i < (byte)ECgCoroutineSchedule.MAX; ++i)
            {
                Payloads.Add(new CgCoroutinePayload());
            }
        }

        public static CgCoroutineScheduler Get()
        {
            return Instance;
        }

        public CgRoutine Allocate(ECgCoroutineSchedule schedule)
        {
            for (ushort i = 0; i < POOL_SIZE; ++i)
            {
                PoolIndicies[schedule] = (PoolIndicies[schedule] + i) % POOL_SIZE;

                CgRoutine r = Pools[schedule][PoolIndicies[schedule]];

                if (r.State != ECgRoutineState.Free)
                    continue;

                return r;
            }
            Debug.LogError("CgRoutine.Allocate: No free Routines. Pools[" + schedule.ToString() + "] is exhausted. Look for runaway Coroutines or consider raising the pool size.");
            return null;
        }

        public void SetTail(ECgCoroutineSchedule schedule, CgRoutine r)
        {
            Tails[schedule] = r;
        }

        public CgRoutine Start(CgCoroutinePayload payload)
        {
            ECgCoroutineSchedule schedule = payload.Schedule;

            CgRoutine r = Allocate(schedule);

            if (r == null)
                return null;

            // If NO Head, Make r the Head
            if (Heads[schedule] == null)
            {
                Heads[schedule] = r;
                Tails[schedule] = r;
            }
            // Add r end of the list, Make r the Tail
            else
            {
                CgRoutine tail = Tails[schedule];
                tail.Next = r;
                r.Prev = tail;
                Tails[schedule] = r;
            }

            RoutinesRunning[schedule].Add(r);

            LogTransaction("CgRoutine.Start", ECgCoroutineTransaction.Start, r);

            // TODO: get Time from Manager_Time
            r.Start(payload.Fiber, payload.StopCondition, payload.Owner, payload.OwnerName, Time.timeSinceLevelLoad, payload.Add, payload.Remove, payload.RoutineType);
            r.State = ECgRoutineState.Running;
            payload.Reset();
            r.Run(0.0f);
            return r;
        }

        public CgRoutine Start(ECgCoroutineSchedule schedule, IEnumerator fiber)
        {
            CgCoroutinePayload payload = AllocatePayload();

            payload.Schedule = schedule;
            payload.Fiber = fiber;

            return Start(payload);
        }

        public void EndAll()
        {
        }

        public bool HasCoroutines(ECgCoroutineSchedule schedule)
        {
            return Heads[schedule] != null;
        }

        private void UpdateEndingRoutineLinkage(string functionName, ECgCoroutineSchedule schedule, CgRoutine current)
        {
            if (current.State == ECgRoutineState.End)
            {
                // Remove from List, Update Linkage. Prev / Next
                if (current.Prev != null)
                {
                    current.Prev.Next = current.Next;

                    if (current.Next != null)
                        current.Next.Prev = current.Prev;
                    // Update Tail
                    else
                        Tails[schedule] = current.Prev;
                }
                // Update Head
                else
                {
                    if (current.Next != null)
                    {
                        current.Next.Prev = null;
                        Heads[schedule] = current.Next;
                    }
                    // Last node in List
                    else
                    {
                        Heads[schedule] = null;
                        Tails[schedule] = null;
                    }
                }
                LogTransaction("CgRoutine.Update", ECgCoroutineTransaction.End, current);
                current.Reset();
            }
        }

        public void Update(ECgCoroutineSchedule schedule, float deltaTime)
        {
            // Iterate through List
            CgRoutine current = Heads[schedule];

            while (current != null)
            {
                if (current.State == ECgRoutineState.Running)
                {
                    current.Run(deltaTime);
                }

                if (current.State == ECgRoutineState.End)
                {
                    // Remove from List, Update Linkage. Prev / Next
                    if (current.Prev != null)
                    {
                        current.Prev.Next = current.Next;

                        if (current.Next != null)
                            current.Next.Prev = current.Prev;
                        // Update Tail
                        else
                            Tails[schedule] = current.Prev;
                    }
                    // Update Head
                    else
                    {
                        if (current.Next != null)
                        {
                            current.Next.Prev = null;
                            Heads[schedule] = current.Next;
                        }
                        // Last node in List
                        else
                        {
                            Heads[schedule] = null;
                            Tails[schedule] = null;
                        }
                    }
                    LogTransaction("CgRoutine.Update", ECgCoroutineTransaction.End, current);
                    current.Reset();
                }
                current = current.Next;
            }

            // Check RoutinesRunning for any Routines that have Ended
            int count = RoutinesRunning[schedule].Count;

            for (int i = count - 1; i >= 0; --i)
            {
                CgRoutine r = RoutinesRunning[schedule][i];

                if (r.State == ECgRoutineState.Free)
                {
                    RoutinesRunning[schedule].RemoveAt(i);
                }
                else
                if (r.State == ECgRoutineState.End)
                {
                    Debug.LogError("CgCoroutineSchedule.Update: Dangling Routine. Check iteration through List or if Routine was tampered with.");
                    r.Reset();
                    RoutinesRunning[schedule].RemoveAt(i);
                }
            }
        }

        public void OnUpdate(float deltaTime)
        {
            Update(ECgCoroutineSchedule.Update, deltaTime);
        }

        public void LogTransaction(string functionName, ECgCoroutineTransaction transaction, CgRoutine r)
        {
            if (!CgCVars.LogCoroutineTransactions.Log())
                return;

            string transactionAsString = transaction.ToString() + "ing (Reason=" + r.EndReason.ToString() + ")";
            string schedule            = r.Schedule.ToString();

            float currentTime = Time.time;

            string elapsed = "";

            if (transaction == ECgCoroutineTransaction.End)
            {
                float duration = currentTime - r.StartTime;
                elapsed        = "Ran for " + r.TickCount + " Ticks and " + duration + " Seconds.";
            }

            if (r.Owner != null)
                Debug.Log(functionName + ": On" + schedule + " " + transactionAsString + " Routine with Coroutine: " + r.Name + " at " + currentTime + ". Using Owner: " + r.OwnerName + ". " + elapsed);
            else
                Debug.Log(functionName + ": On" + schedule + " " + transactionAsString + " Routine with Coroutine: " + r.Name + " at " + currentTime + ". " + elapsed);
        }

        public CgCoroutinePayload AllocatePayload()
        {
            for (int i = 0; i < POOL_SIZE; ++i)
            {
                PayloadIndex = (PayloadIndex + 1) % POOL_SIZE;

                CgCoroutinePayload p = Payloads[PayloadIndex];

                if (!p.IsAllocated)
                {
                    return p;
                }
            }
            Debug.LogWarning("CgCoroutineScheduler.AllocatePayload: No free Payloads. Look for Runaway Coroutines or consider raising the pool size.");
            return null;
        }
    }
}
