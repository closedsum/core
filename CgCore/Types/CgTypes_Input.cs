namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Constants"

    public static class CgTypes_Input
    {
        public static ushort INVALID_INPUT_POOL_INDEX = 65535;
    }

    #endregion

    public abstract class ECgInputActionMap : ECgEnum_int
    {

    }

    public sealed class ECgInputActionMapEqualityComparer : IEqualityComparer<ECgInputActionMap>
    {
        public bool Equals(ECgInputActionMap lhs, ECgInputActionMap rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputActionMap x)
        {
            return x.GetHashCode();
        }
    }

    public abstract class ECgInputAction : ECgEnum_byte
    {
        #region "Delegates"

        public delegate ECgInputAction Getter(byte b);

        #endregion // Delegates

        #region "Data Members"

        public static Getter Get;

        #endregion // Data Members
    }

    public sealed class ECgInputActionEqualityComparer : IEqualityComparer<ECgInputAction>
    {
        public bool Equals(ECgInputAction lhs, ECgInputAction rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputAction x)
        {
            return x.GetHashCode();
        }
    }

    public enum ECgInputDevice : byte
    {
        MouseAndKeyboard,
        Gamepad,
        MotionController,
        MAX
    }

    public sealed class CgInputDeviceEqualityComparer : IEqualityComparer<ECgInputDevice>
    {
        public bool Equals(ECgInputDevice lhs, ECgInputDevice rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputDevice x)
        {
            return x.GetHashCode();
        }
    }

    public enum ECgInputType : byte
    {
        Action,
        Axis,
        Trigger,
        Location,
        Rotation,
        MAX
    }

    public sealed class ECgInputTypeEqualityComparer : IEqualityComparer<ECgInputType>
    {
        public bool Equals(ECgInputType lhs, ECgInputType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputType x)
        {
            return x.GetHashCode();
        }
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

    public sealed class ECgInputEventEqualityComparer : IEqualityComparer<ECgInputEvent>
    {
        public bool Equals(ECgInputEvent lhs, ECgInputEvent rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputEvent x)
        {
            return x.GetHashCode();
        }
    }

    public enum ECgInputValue : byte
    {
        Action,
		Axis,
		Trigger,
		Location,
		Rotation,
        MAX
    }

    public sealed class ECgInputValueEqualityComparer : IEqualityComparer<ECgInputValue>
    {
        public bool Equals(ECgInputValue lhs, ECgInputValue rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgInputValue x)
        {
            return x.GetHashCode();
        }
    }

    public abstract class ECgGameEvent : ECgEnum_byte
    {
        #region "Delegates"

        public delegate ECgGameEvent Getter(byte b);

        #endregion // Delegates

        #region "Data Members"

        public static Getter Get;

        #endregion // Data Members
    }

    public sealed class ECgGameEventEqualityComparer : IEqualityComparer<ECgGameEvent>
    {
        public bool Equals(ECgGameEvent lhs, ECgGameEvent rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgGameEvent x)
        {
            return x.GetHashCode();
        }
    }

    public class CgKeyInputHandler
    {
        public class CgKeyInputHandler_Event : CgDelegate { }

        #region "Data Members"

        public ECgInputAction Action;

        public CgKeyInputHandler_Event Event;

        #endregion // Data Members

        public CgKeyInputHandler()
        {
            Action = null;
        }

        public CgKeyInputHandler(ECgInputAction action)
        {
            Action = action;
            Event = new CgKeyInputHandler_Event();
        }

        public static bool operator ==(CgKeyInputHandler lhs, CgKeyInputHandler rhs)
        {
            if (lhs.Action != rhs.Action) return false;
            if (lhs.Event != rhs.Event) return false;
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

            CgKeyInputHandler rhs = (CgKeyInputHandler)obj;

            if (Action != rhs.Action) return false;
            if (Event != rhs.Event) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public CgDelegateHandle Add(CgDelegate.Event e)
        {
            return Event.Add(e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return Event.Remove(handle);
        }

        public void Broadcast()
        {
            Event.Broadcast();
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

        private Dictionary<ECgInputAction, CgKeyInputHandler>[] HandlerMap;

        #endregion // Data Members

        public CgKeyInput()
        {
            Key = KeyCode.None;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerMap = new Dictionary<ECgInputAction, CgKeyInputHandler>[(byte)ECgInputEvent.MAX];

            int len = (int)ECgInputEvent.MAX;

            for (int i = 0; i < len; ++i)
            {
                HandlerMap[i] = new Dictionary<ECgInputAction, CgKeyInputHandler>(new ECgInputActionEqualityComparer());
            }
        }

        public CgKeyInput(KeyCode key)
        {
            Key = key;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerMap = new Dictionary<ECgInputAction, CgKeyInputHandler>[(byte)ECgInputEvent.MAX];

            int len = (int)ECgInputEvent.MAX;

            for (int i = 0; i < len; ++i)
            {
                HandlerMap[i] = new Dictionary<ECgInputAction, CgKeyInputHandler>(new ECgInputActionEqualityComparer());
            }
        }

        public CgDelegateHandle Bind(ECgInputAction action, ECgInputEvent e, CgDelegate.Event del)
        {
            Dictionary<ECgInputAction, CgKeyInputHandler> map = HandlerMap[(byte)e];

            CgKeyInputHandler handle = null;
            bool found               = map.TryGetValue(action, out handle);

            if (found)
            {
                return handle.Add(del);
            }
            else
            {
                handle = new CgKeyInputHandler(action);
                
                map.Add(action, handle);

                return handle.Add(del);
            }
        }

        public bool UnBind(ECgInputEvent e, CgDelegateHandle handle)
        {
            Dictionary<ECgInputAction, CgKeyInputHandler> map = HandlerMap[(byte)e];

            Dictionary<ECgInputAction, CgKeyInputHandler>.ValueCollection handles = map.Values;

            bool success = false;

            foreach (CgKeyInputHandler h in handles)
            {
                success |= h.Remove(handle);
            }
            return success;
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
            Dictionary<ECgInputAction, CgKeyInputHandler> map = HandlerMap[(byte)e];

            Dictionary<ECgInputAction, CgKeyInputHandler>.ValueCollection handles = map.Values;

            foreach (CgKeyInputHandler h in handles)
            {
                h.Broadcast();
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

