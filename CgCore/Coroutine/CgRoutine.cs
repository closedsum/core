namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public enum ECgRoutineState : byte
    {
        Free,
        Running,
        End,
        MAX
    }

    public enum ECgCoroutineMessage : byte
    {
        Notify,
        Listen,
        Stop,
        MAX
    }

    public sealed class ECgCoroutineMessageEqualityComparer : IEqualityComparer<ECgCoroutineMessage>
    {
        public bool Equals(ECgCoroutineMessage lhs, ECgCoroutineMessage rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgCoroutineMessage x)
        {
            return x.GetHashCode();
        }
    }

    public sealed class CgRoutine
    {
        public sealed class CoroutineStopCondition : TCgMulticastDelegate_RetOrBool_OneParam<CgRoutine> { }
        public sealed class AddRoutine : TCgDelegate_OneParam<CgRoutine> { }
        public sealed class RemoveRoutine : TCgDelegate_OneParam<CgRoutine> { }
        public sealed class Flag : TCgPrimitiveType<bool> { }

        public delegate void InsertRoutineAheadOf(ECgCoroutineSchedule schedule, CgRoutine pivot, CgRoutine insert);

        #region "Constants"

        public static readonly byte INVALID_TYPE = 255;
        public static readonly string INVALID_LISTEN_MESSAGE = "";

        #endregion // Constants

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

        public readonly InsertRoutineAheadOf InsertRoutine;

        public CgRoutine Parent;
        public List<CgRoutine> Children;

        public CgAttribute Owner;
        public string OwnerName;
        public CoroutineStopCondition StopCondition;

        public List<string> StopMessages;
        public Dictionary<ECgCoroutineMessage, List<string>> Messages_Recieved;

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
        public bool bWaitForFlag;
        public Flag WaitForFlag;
        public bool bWaitForListenMessage;
        public string WaitForListenMessage;

        public ECgCoroutineEndReason EndReason;

        // Lock

        #endregion // Data Members

        // Constructor

        public CgRoutine(int index, ECgCoroutineSchedule schedule, InsertRoutineAheadOf insertRoutine)
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

            InsertRoutine = insertRoutine;

            Parent = null;
            Children = new List<CgRoutine>();

            Owner = new CgAttribute();
            OwnerName = "";
            StopCondition = new CoroutineStopCondition();

            StopMessages = new List<string>();
            Messages_Recieved = new Dictionary<ECgCoroutineMessage, List<string>>(new ECgCoroutineMessageEqualityComparer());

            for (byte i = 0; i < (byte)ECgCoroutineMessage.MAX; ++i)
            {
                Messages_Recieved[(ECgCoroutineMessage)i] = new List<string>();
            }

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
            bWaitForFlag = false;
            WaitForFlag = null;
            bWaitForListenMessage = false;
            WaitForListenMessage = INVALID_LISTEN_MESSAGE;

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
            int count = Messages_Recieved[ECgCoroutineMessage.Stop].Count;

            for (int i = 0; i < count; ++i)
            {
                if (StopMessages.FindIndex(s => s == Messages_Recieved[ECgCoroutineMessage.Stop][i]) != CgTypes.INDEX_NONE)
                {
                    StopMessages.Clear();
                    End(ECgCoroutineEndReason.StopMessage);
                    break;
                }
            }
            Messages_Recieved[ECgCoroutineMessage.Stop].Clear();

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
                move = WaitingFor.State != ECgRoutineState.Running;

                if (move)
                {
                    WaitingFor.Blocking = null;
                    WaitingFor  = null;
                    bWaitingFor = false;
                }
            }
            // Check WaitForFlag
            if (bWaitForFlag)
            {
                move         = WaitForFlag.Get();
                bWaitForFlag = !move;
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

                    if (WaitForFrame < 0)
                    {
                        WaitForFrame = 0;

                        Debug.LogWarning("CgRoutine.Run: yield return value of type 'int' is used for WaitForFrame. yield return value must be >= 0.");
                    }
                    else
                    {
                        bWaitForFrame = true;
                    }
                }
                // WaitForTime
                else
                if (type == typeof(float))
                {
                    WaitForTime = (float)yieldCommand;

                    if (WaitForTime < 0.0f)
                    {
                        WaitForTime = 0.0f;

                        Debug.LogWarning("CgRoutine.Run: yield return value of type 'float' is used for WaitForTime. yield return value must be >= 0.0f.");
                    }
                    else
                    {
                        bWaitForTime = true;
                    }
                }
                // WaitingFor
                else
                if (type == typeof(CgRoutine))
                {
                    WaitingFor          = (CgRoutine)yieldCommand;
                    WaitingFor.Blocking = this;
                    bWaitingFor         = true;

                    // Fix linkage. Prev / Next
                    InsertRoutine(Schedule, this, WaitingFor);
                }
                // WaitForFlag
                else
                if (type == typeof(Flag))
                {
                    WaitForFlag = (Flag)yieldCommand;
                    bWaitForFlag = true;
                }
                // WaitForListenMessage
                else
                if (type == typeof(string))
                {
                    WaitForListenMessage = (string)yieldCommand;

                    if (WaitForListenMessage == INVALID_LISTEN_MESSAGE)
                    {
                        Debug.LogWarning("CgRoutine.Run: yield return value of type 'string' is used for WaitForListenMessage. yield return value must NOT be empty.");
                    }
                    else
                    {
                        bWaitForListenMessage = true;
                    }
                }
                // INVALID Type
                else
                {
                    Debug.LogError("CgRoutine.Run: Invalid type for yield. yield return value must be of type: int, float, CgRoutine, CgRoutine.Flag, or string.");
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

        public void ReceiveMessage(ECgCoroutineMessage msgType, string msg)
        {
            Messages_Recieved[msgType].Add(msg);
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

            for (byte i = 0; i < (byte)ECgCoroutineMessage.MAX; ++i)
            {
                Messages_Recieved[(ECgCoroutineMessage)i].Clear();
            }

            Add.UnBind();
            Remove.UnBind();
            StartTime = 0.0f;
            ElapsedTime = 0.0f;
            DeltaTime = 0.0f;
            TickCount = 0;
            Delay = 0.0f;
            bWaitForFrame = false;
            WaitForFrame = 0;
            bWaitForTime = false;
            WaitForTime = 0.0f;
            bWaitForFlag = false;
            WaitForFlag = null;
            bWaitForListenMessage = false;
            WaitForListenMessage = INVALID_LISTEN_MESSAGE;
        }
    }
}