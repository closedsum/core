namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Constants"

    public static class CgTypes_Input
    {
        public static ushort CG_INVALID_INPUT_POOL_INDEX = 65535;
    }

    #endregion

    public abstract class ECgInputAction : ECgEnum_Byte
    {
        #region "Delegates"

        public delegate ECgInputAction Getter(byte b);

        #endregion // Delegates

        #region "Data Members"

        public static Getter Get;

        #endregion // Data Members
    }

    public enum ECgInputDevice : byte
    {

    }

    public enum ECgInputType : byte
    {

    }

    public enum ECgInputEvent : byte
    {
        FirstPressed,
        Pressed,
        FirstReleased,
        Released,
        FirstMoved,
        Moved,
        FirstStationary,
        Stationary,
        MAX
    }

    public enum ECgInputValue : byte
    {
    }

    public class CgKeyInputHandler
    {
        #region "Data Members"

        public ECgInputAction Action;

        public CgDelegate_Void[] Events;

        #endregion // Data Members

        public CgKeyInputHandler()
        {
            Action = null;
        }

        public CgKeyInputHandler(ECgInputAction action)
        {
            Action = action;
            Events = new CgDelegate_Void[(byte)ECgInputEvent.MAX];
        }

        public static bool operator ==(CgKeyInputHandler lhs, CgKeyInputHandler rhs)
        {
            if (lhs.Action != rhs.Action) return false;
            if (lhs.Events != rhs.Events) return false;
            return true;
        }

        public static bool operator !=(CgKeyInputHandler lhs, CgKeyInputHandler rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgKeyInputHandler))
                return false;

            CgKeyInputHandler input = (CgKeyInputHandler)obj;

            if (Action != input.Action) return false;
            if (Events != input.Events) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }

    public class CgKeyInput
    {
        #region "Data Members"

        public KeyCode Key;
        public ECgInputEvent Event;
        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;

        List<CgKeyInputHandler> HandlerList;

        #endregion // Data Members

        public CgKeyInput()
        {
            Key = KeyCode.None;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerList = new List<CgKeyInputHandler>();
        }

        public CgKeyInput(KeyCode key)
        {
            Key = key;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerList = new List<CgKeyInputHandler>();
        }

        public void Bind(ECgInputAction action, ECgInputEvent e, CgDelegate_Void handler)
        {
            bool found = false;
            
            // Check if Handler has been already created for the action
            int len = HandlerList.Capacity;

            for (int i = 0; i < len; ++i)
            {
                CgKeyInputHandler inputHandler = HandlerList[i];

                if (inputHandler.Action == action)
                {
                    found = true;

                    inputHandler.Events[(byte)e] += handler;
                    break;
                }
            }

            if (!found)
            {
                CgKeyInputHandler inputHandler = new CgKeyInputHandler(action);
                inputHandler.Events[(byte)e]  += handler;

                HandlerList.Add(inputHandler);
            }
        }

        public void Set(ECgInputEvent e, float time, float realTime, ulong frame)
        {
            Event = e;
            Time = time;
            RealTime = realTime;
            Frame = frame;
            Execute(e);
        }

        public void Execute(ECgInputEvent e)
        {
            int len = HandlerList.Capacity;

            for (int i = 0; i < len; ++i)
            {
                CgKeyInputHandler handler = HandlerList[i];

                if (handler == null)
                    continue;
                if (handler.Events[(byte)e] == null)
                    continue;

                handler.Events[(byte)e]();
            }
        }
    }

    public class CgInput
    {
        #region "Data Members"

        public ushort PoolIndex;
        public bool IsAllocated;
        public bool IsConsumed;
        public ECgInputAction Action;
        public ECgInputEvent Event;
        public float Value;
        public Vector3 Location;
        public Vector3 Rotation;
        public float Duration;

        #endregion // Data Members

        public CgInput(ushort poolIndex)
        {
            PoolIndex = poolIndex;
            IsAllocated = false;
            IsConsumed = false;
            Action = null;
            Event = ECgInputEvent.MAX;
            Value = Mathf.Infinity;
            Location = Vector3.zero;
            Rotation = Vector3.zero;
            Duration = 0f;
        }

        public static bool operator ==(CgInput lhs, CgInput rhs)
        {
            if (lhs.Action != rhs.Action) return false;
            if (lhs.Event != rhs.Event) return false;
            if (lhs.Value != rhs.Value) return false;
            if (lhs.Location != rhs.Location) return false;
            if (lhs.Rotation != rhs.Rotation) return false;
            if (lhs.Duration != rhs.Duration) return false;
            return true;
        }

        public static bool operator !=(CgInput lhs, CgInput rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgInput))
                return false;

            CgInput input = (CgInput)obj;

            if (Action != input.Action) return false;
            if (Event != input.Event) return false;
            if (Value != input.Value) return false;
            if (Location != input.Location) return false;
            if (Rotation != input.Rotation) return false;
            if (Duration != input.Duration) return false;
            return true;
        }

        public override int GetHashCode()
        {
            int hash = Event.GetHashCode() ^ Value.GetHashCode() ^ Location.GetHashCode() ^ Rotation.GetHashCode() ^ Duration.GetHashCode();
            return Action != null ? Action.GetHashCode() ^ hash : hash;
        }

        public void Init(ushort poolIndex)
        {
            PoolIndex = poolIndex;
            IsAllocated = false;
            IsConsumed = false;
            Action = null;
            Event = ECgInputEvent.MAX;
            Value = Mathf.Infinity;
            Location = Vector3.zero;
            Rotation = Vector3.zero;
            Duration = 0f;
        }

        public void Set(ECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
        {
            Action = action;
            Event = e;
            Value = value;
            Location = location;
            Rotation = rotation;
        }

        public void Set(ECgInputAction action, ECgInputEvent e, Vector3 location, Vector3 rotation)
        {
            Set(action, e, 0f, location, rotation);
        }

        public void Set(ECgInputAction action, ECgInputEvent e, float time)
        {
            Set(action, e, time, Vector3.zero, Vector3.zero);
        }

        public void Set(ECgInputAction action, ECgInputEvent e)
        {
            Set(action, e, 0f, Vector3.zero, Vector3.zero);
        }

        public void Allocate(ECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
	    {
		    IsAllocated = true;
		    Set(action, e, value, location, rotation);
        }

        public void Allocate(ECgInputAction action, ECgInputEvent e, Vector3 location, Vector3 rotation)
        {
            Allocate(action, e, 0f, location, rotation);
        }

        public void Allocate(ECgInputAction action, ECgInputEvent e, float value)
        {
            Allocate(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void Allocate(ECgInputAction action, ECgInputEvent e)
        {
            Allocate(action, e, 0f, Vector3.zero, Vector3.zero);
        }

        public void Reset()
        {
            IsAllocated = false;
            IsConsumed = false;
            Action = null;
            Event = ECgInputEvent.MAX;
            Value = Mathf.Infinity;
            Location = Vector3.zero;
            Rotation = Vector3.zero;
            Duration = 0f;
        }
}

    public class CgInputFrame
    {
        #region "Data Members"

        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;
        public List<CgInput> Inputs;

        #endregion // Data Members

        public CgInputFrame()
        {
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;
            Inputs = new List<CgInput>();
        }

        public static bool operator ==(CgInputFrame lhs, CgInputFrame rhs)
        {
            if (lhs.Time != rhs.Time) return false;
            if (lhs.RealTime != rhs.RealTime) return false;
            if (lhs.DeltaTime != rhs.DeltaTime) return false;
            if (lhs.Frame != rhs.Frame) return false;

            if (lhs.Inputs.Capacity != rhs.Inputs.Capacity) return false;

            int count = lhs.Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                if (lhs.Inputs[i] != rhs.Inputs[i])
                    return false;
            }
            return true;
        }

        public static bool operator !=(CgInputFrame lhs, CgInputFrame rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgInputFrame))
                return false;

            CgInputFrame rhs = (CgInputFrame)obj;

            if (Time != rhs.Time) return false;
            if (RealTime != rhs.RealTime) return false;
            if (DeltaTime != rhs.DeltaTime) return false;
            if (Frame != rhs.Frame) return false;

            if (Inputs.Capacity != rhs.Inputs.Capacity) return false;

            int count = Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                if (Inputs[i] != rhs.Inputs[i])
                    return false;
            }
            return true;
        }

        public override int GetHashCode()
        {
            return Time.GetHashCode() ^ RealTime.GetHashCode() ^ DeltaTime.GetHashCode() ^ Frame.GetHashCode();
        }

        public void Copy(CgInputFrame rhs)
        {
            Time = rhs.Time;
            RealTime = rhs.RealTime;
            DeltaTime = rhs.DeltaTime;
            Frame = rhs.Frame;

            Inputs.Clear();

            int count = rhs.Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                Inputs.Add(rhs.Inputs[i]);
            }
        }

        public void Init(float time, float realTime, float deltaTime, ulong frame)
        {
            Time = time;
            RealTime = realTime;
            DeltaTime = deltaTime;
            Frame = frame;

            int count = Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                Inputs[i].Reset();
            }
            Inputs.Clear();
        }

        public CgInput GetInput(ECgInputAction action)
        {
            int count = Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                if (Inputs[i].Action == action)
                    return Inputs[i];
            }
            return null;
        }

        public CgInput GetInput(ECgInputAction action, ECgInputEvent e)
        {
            CgInput input = GetInput(action);

            if (input != null)
                return input.Event == e ? input : null;
            return null;
        }
        
        public CgInput GetInput(ECgInputAction action, List<ECgInputEvent> events)
	    {
            CgInput input = GetInput(action);

            if (input != null)
                return events.IndexOf(input.Event) != CgTypes.INDEX_NONE ? input : null;
            return null;
        }
    }

    public class CgInputInfo
    {
        #region "Data Members"

        public ECgInputType Type;
        public ECgInputValue ValueType;
        public ECgInputEvent Event;
        public ECgInputEvent Last_Event;
        public float Value;
        public Vector3 Location;
        public Quaternion Rotation;
        public Vector3 Euler;
        public float Duration;

        #endregion // Data Members

        public CgInputInfo(ECgInputType type, ECgInputValue valueType)
        {
            Type = type;
            ValueType = valueType;
            Event = ECgInputEvent.MAX;
            Last_Event = ECgInputEvent.MAX;
            Value = 0f;
            Location = Vector3.zero;
            Rotation = Quaternion.identity;
            Euler = Vector3.zero;
            Duration = 0f;
        }

        public static bool operator ==(CgInputInfo lhs, CgInputInfo rhs)
        {
            if (lhs.Type != rhs.Type) return false;
            if (lhs.ValueType != rhs.ValueType) return false;
            if (lhs.Event != rhs.Event) return false;
            if (lhs.Last_Event != rhs.Last_Event) return false;
            if (lhs.Value != rhs.Value) return false;
            if (lhs.Location != rhs.Location) return false;
            if (lhs.Rotation != rhs.Rotation) return false;
            if (lhs.Euler != rhs.Euler) return false;
            if (lhs.Duration != rhs.Duration) return false;
            return true;
        }

        public static bool operator !=(CgInputInfo lhs, CgInputInfo rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgInputInfo))
                return false;

            CgInputInfo rhs = (CgInputInfo)obj;

            if (Type != rhs.Type) return false;
            if (ValueType != rhs.ValueType) return false;
            if (Event != rhs.Event) return false;
            if (Last_Event != rhs.Last_Event) return false;
            if (Value != rhs.Value) return false;
            if (Location != rhs.Location) return false;
            if (Rotation != rhs.Rotation) return false;
            if (Euler != rhs.Euler) return false;
            if (Duration != rhs.Duration) return false;
            return true;
        }

        public override int GetHashCode()
        {
            int a = Type.GetHashCode() ^ ValueType.GetHashCode() ^ Event.GetHashCode() ^ Last_Event.GetHashCode();
            int b = Value.GetHashCode() ^ Location.GetHashCode() ^ Rotation.GetHashCode() ^ Euler.GetHashCode() ^ Duration.GetHashCode();
            return a ^ b;
        }

        public void Set(ECgInputEvent e, float value)
        {
            Event = e;
            Value = value;
        }

        public void Set(ECgInputEvent e, Vector3 location)
        {
            Event = e;
            Location = location;
        }

        public void Set(ECgInputEvent e, Quaternion rotation)
        {
            Event = e;
            Rotation = rotation;
            Euler = Rotation.eulerAngles;
        }
    }
}

