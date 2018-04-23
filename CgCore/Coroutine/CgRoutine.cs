namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public enum ECgRoutineState
    {
        Free,
        Running,
        End,
        MAX
    }

    public sealed class CgRoutine
    {
        public sealed class CoroutineStopCondition : TCgMulticastDelegate_RetOrBool_OneParam<CgRoutine> { }
        public sealed class AddRoutine : TCgDelegate_OneParam<CgRoutine> { }
        public sealed class RemoveRoutine : TCgDelegate_OneParam<CgRoutine> { }
        public delegate void SetScheduleTail(ECgCoroutineSchedule schedule, CgRoutine r);

        public static readonly byte INVALID_TYPE = 255;

        #region "Data Members"

        public readonly int Index;
        public readonly ECgCoroutineSchedule Schedule;

        public CgRoutine Prev;
        public CgRoutine Next;

        public ECgRoutineState State;

        public IEnumerator Fiber;
        public string Name;
        public byte RoutineType;

        public CgRoutine WaitingFor;
        public CgRoutine Blocking;

        public readonly SetScheduleTail SetTail;

        public CgRoutine Parent;
        public List<CgRoutine> Children;

        public CgAttribute Owner;
        public string OwnerName;
        public CoroutineStopCondition StopCondition;

        public List<string> StopMessages;
        public List<string> StopMessages_Recieved;

        public AddRoutine Add;
        public RemoveRoutine Remove;

        public float StartTime;
        public float ElapsedTime;
        public float DeltaTime;
        public int TickCount;
        public float Delay;

        public int WaitForFrame;
        public float WaitForTime;

        public ECgCoroutineEndReason EndReason;

        // Lock

        #endregion // Data Members

        // Constructor

        public CgRoutine(int index, ECgCoroutineSchedule schedule, SetScheduleTail setTail)
        {
            Index = index;
            Schedule = schedule;
            SetTail = setTail;
            State = ECgRoutineState.Free;

            StopCondition = new CoroutineStopCondition();

            StopMessages = new List<string>();
            StopMessages_Recieved = new List<string>();

            Add = new AddRoutine();
            Remove = new RemoveRoutine();
        }

        // Functions

        public void Start(CgCoroutinePayload payload, float currentType)
        {
            Fiber = payload.Fiber;
            Owner.Set(payload.Owner);
            OwnerName = payload.OwnerName;

            Add.Bind(payload.Add);
            Remove.Bind(payload.Remove);

            if (Owner.IsValid())
                Add.Broacast(this);
        }

        public void Run(float deltaTime)
        {
            // Check Stop Messages
            int count = StopMessages_Recieved.Count;

            for (int i = 0; i < count; ++i)
            {
                if (StopMessages.FindIndex(s => s == StopMessages_Recieved[i]) != CgTypes.INDEX_NONE)
                {
                    StopMessages.Clear();
                    End(ECgCoroutineEndReason.StopMessage);
                    break;
                }
            }
            StopMessages_Recieved.Clear();

            if (State == ECgRoutineState.End)
                return;
            // Check Stop Condition
            if (StopCondition.Broadcast(this))
                End(ECgCoroutineEndReason.StopCondition);

            if (State == ECgRoutineState.End)
                return;

            DeltaTime = deltaTime;
            ElapsedTime += deltaTime;
            ++TickCount;

            bool move = false;

            if (WaitForFrame > TickCount)
            {
                WaitForFrame = 0;
                move         = true;
            }

            if (WaitForTime > ElapsedTime)
            {
                WaitForTime = 0;
                move        = true;
            }

            if (WaitingFor == null)
                move = true;

            if (!move)
                return;

            if (Fiber.MoveNext())
            {
                object yieldCommand = Fiber.Current == null ? (object)1 : Fiber.Current;
                Type type           = yieldCommand.GetType();
                // WaitForFrame
                if (type == typeof(int))
                {
                    WaitForFrame = (int)yieldCommand;
                }
                // WaitForTime
                else
                if (type == typeof(float))
                {
                    WaitForTime = (float)yieldCommand;
                }
                // WaitingFor
                else
                if (type == typeof(CgRoutine))
                {
                    WaitingFor          = (CgRoutine)yieldCommand;
                    WaitingFor.Blocking = this;

                    // Fix linkage. Prev / Next
                    CgRoutine Tail = WaitingFor.Prev;

                    if (Prev != null)
                    {
                        Prev.Next       = WaitingFor;
                        WaitingFor.Prev = Prev;
                    }

                    WaitingFor.Next = this;
                    Prev            = WaitingFor;

                    SetTail(Schedule, Tail);
                }
                // INVALID Type
                else
                {
                    Debug.LogError("");
                }
            }
            // Finished
            else
            {
                End(ECgCoroutineEndReason.EndOfExecution);
            }
        }

        public void End(ECgCoroutineEndReason endReason)
        {
            if (Owner.IsValid())
                Remove.Broacast(this);
            // EndChildren();
            EndReason = endReason;
        }

        public void EndChildren()
        {
            int count = Children.Count;

            for (int i = 0; i < count; ++i)
            {
                Children[i].End(ECgCoroutineEndReason.Parent);
            }
            Children.Clear();
        }

        public void AddMessage(string msg)
        {
            StopMessages.Add(msg);
        }

        public void ReceiveMessage(string msg)
        {
            StopMessages_Recieved.Add(msg);
        }

        public void Reset()
        {
            Prev = null;
            Next = null;
            State = ECgRoutineState.Free;

            Fiber = null;
            Name = "";
            RoutineType = INVALID_TYPE;
            WaitingFor = null;
            Blocking = null;
            Parent = null;
            Children.Clear();
            Owner.UnSet();
            OwnerName = "";
            StopCondition = null;
            StopMessages.Clear();
            StopMessages_Recieved.Clear();
            Add.UnBind();
            Remove.UnBind();
            StartTime = 0.0f;
            ElapsedTime = 0.0f;
            DeltaTime = 0.0f;
            TickCount = 0;
            Delay = 0.0f;
            WaitForFrame = 0;
            WaitForTime = 0.0f;
        }
    }
}