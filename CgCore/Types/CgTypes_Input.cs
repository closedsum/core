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

    public abstract class ECgInputAction : ECgEnum<byte>
    {
        public static readonly ECgInputAction NULL = null;
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

    public struct CgKeyInputHandler
    {
        public static readonly CgKeyInputHandler NULL = new CgKeyInputHandler(null);

        #region "Data Members"

        public ECgInputAction Action;

        public CgDelegate_Void[] Events;

        #endregion

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

    public struct CgKeyInput
    {
        #region "Data Members"

        public KeyCode Key;
        public ECgInputEvent Event;
        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;

        #endregion

        #region "Delegates"

        List<CgKeyInputHandler> HandlerList;

        #endregion

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

                if (handler == CgKeyInputHandler.NULL)
                    continue;

                if (handler.Events[(byte)e] == null)
                    continue;

                handler.Events[(byte)e]();
            }
        }
    }

    public struct CgInput
    {
        public static readonly CgInput NULL = new CgInput(0);

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

        #endregion

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
            return base.GetHashCode();
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

    public struct CgInputFrame
    {
        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;
        public List<CgInput> Inputs;

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
            return CgInput.NULL;
        }

        public CgInput GetInput(ECgInputAction action, ECgInputEvent e)
        {
            CgInput input = GetInput(action);

            if (input != CgInput.NULL)
                return input.Event == e ? input : CgInput.NULL;
            return CgInput.NULL;
        }
        
        public CgInput GetInput(ECgInputAction action, List<ECgInputEvent> events)
	    {
            CgInput input = GetInput(action);

            if (input != CgInput.NULL)
                return events.IndexOf(input.Event) != CgTypes.INDEX_NONE ? input : CgInput.NULL;
            return CgInput.NULL;
        }
    }

    public struct CgInputInfo
    {
        public ECgInputType Type;
        public ECgInputValue ValueType;
        public ECgInputEvent Event;
        public ECgInputEvent Last_Event;
        public float Value;
        public Vector3 Location;
        public Vector3 Rotation;
        public float Duration;

        public CgInputInfo(ECgInputType type, ECgInputValue valueType)
        {
            Type = type;
            ValueType = valueType;
            Event = ECgInputEvent.MAX;
            Last_Event = ECgInputEvent.MAX;
            Value = 0f;
            Location = Vector3.zero;
            Rotation = Vector3.zero;
            Duration = 0f;
        }
        /*
        CgInputInfo& operator=(const FCsInputInfo& B)
	    {
		    Type = B.Type;
		    ValueType = B.ValueType;
		    Event = B.Event;
		    Last_Event = B.Last_Event;
		    Value = B.Value;
		    Location = B.Location;
		    Rotation = B.Rotation;
		    Duration = B.Duration;
		    return *this;
	    }

        bool operator ==(const FCsInputInfo& B) const
	    {
		    return Type == B.Type && ValueType == B.ValueType && 
			       Event == B.Event && Last_Event == B.Last_Event &&
			       Value == B.Value && Location == B.Location && Rotation == B.Rotation &&
			       Duration == B.Duration;
	    }

        bool operator !=(const FCsInputInfo& B) const
	    {
		        return !(*this == B);
        }

        void Set(const TCsInputEvent &inEvent, const float &inValue)
        {
            Event = inEvent;
            Value = inValue;
        }

        void Set(const TCsInputEvent &inEvent, const FVector &inLocation)
        {
            Event = inEvent;
            Location = inLocation;
        }

        void Set(const TCsInputEvent &inEvent, const FRotator &inRotation)
        {
            Event = inEvent;
            Rotation = inRotation;
        }
        */
    }
}

