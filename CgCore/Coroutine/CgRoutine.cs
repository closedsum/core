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

        public bool bWaitingFor;
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

        public bool bWaitForFrame;
        public int WaitForFrame;
        public bool bWaitForTime;
        public float WaitForTime;

        public ECgCoroutineEndReason EndReason;

        // Lock

        #endregion // Data Members

        // Constructor

        public CgRoutine(int index, ECgCoroutineSchedule schedule, SetScheduleTail setTail)
        {
            Index = index;
            Schedule = schedule;

            Prev = null;
            Next = null;
        
            State = ECgRoutineState.Free;

            Fiber = null;
            Name = "";
            RoutineType = INVALID_TYPE;

            bWaitingFor = false;
            WaitingFor = null;
            Blocking = null;

            SetTail = setTail;

            Parent = null;
            Children = new List<CgRoutine>();

            Owner = new CgAttribute();
            OwnerName = "";
            StopCondition = new CoroutineStopCondition();

            StopMessages = new List<string>();
            StopMessages_Recieved = new List<string>();

            Add = new AddRoutine();
            Remove = new RemoveRoutine();

            StartTime = 0.0f;
            ElapsedTime = 0.0f;
            DeltaTime = 0.0f;
            TickCount = 0;
            Delay = 0.0f;

            bWaitForFrame = false;
            WaitForFrame = 0;
            bWaitForTime = false;
            WaitForTime = 0.0f;

            EndReason = ECgCoroutineEndReason.MAX;
        }

        // Functions

        public void Start(IEnumerator fiber, CoroutineStopCondition stopCondition, object owner, string ownerName, float startTime, AddRoutine.Event add, RemoveRoutine.Event remove, byte routineType)
        {
            Fiber = fiber;
            Owner.Set(owner);
            OwnerName = ownerName;

            StartTime = startTime;

            Add.Bind(add);
            Remove.Bind(remove);

            if (Owner.IsValid())
                Add.Broacast(this);
        }

        public void Start(IEnumerator fiber, CoroutineStopCondition stopCondition, object owner, string ownerName, float startTime)
        {
            Start(fiber, stopCondition, owner, ownerName, startTime, null, null, INVALID_TYPE);
        }

        public void Start(IEnumerator fiber, object owner, string ownerName, float startTime)
        {
            Start(fiber, null, owner, ownerName, startTime, null, null, INVALID_TYPE);
        }

        public void Start(IEnumerator fiber, float startTime)
        {
            Start(fiber, null, null, "", startTime, null, null, INVALID_TYPE);
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

            bool move = true;
            // Check WaitForFrame
            if (bWaitForFrame)
            {
                move = TickCount >= WaitForFrame;

                if (move)
                {
                    WaitForFrame = 0;
                    bWaitForFrame = false;
                }
            }
            // Check WaitForTime
            if (bWaitForTime)
            {
                move = ElapsedTime >= WaitForTime;

                if (move)
                {
                    WaitForTime = 0;
                    bWaitForTime = false;
                }
            }
            // Check WaitingFor
            if (bWaitingFor)
            {
                move        = WaitingFor == null;
                bWaitingFor = !move;
            }

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
                    bWaitForFrame = true;
                }
                // WaitForTime
                else
                if (type == typeof(float))
                {
                    WaitForTime = (float)yieldCommand;
                    bWaitForTime = true;
                }
                // WaitingFor
                else
                if (type == typeof(CgRoutine))
                {
                    WaitingFor          = (CgRoutine)yieldCommand;
                    WaitingFor.Blocking = this;
                    bWaitingFor         = true;

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
            State = ECgRoutineState.End;
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