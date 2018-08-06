// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

    public class FECgInputActionMap : ECgEnum_int
    {
        public FECgInputActionMap(int value, string name) : base(value, name) { }
    }

    public sealed class EMCgInputActionMap : TCgEnumMaskMap<FECgInputActionMap, int>
    {
        private static EMCgInputActionMap _Instance;
        public static EMCgInputActionMap Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgInputActionMap();
                }
                return _Instance;
            }
        }

        public static EMCgInputActionMap Get()
        {
            return Instance;
        }
    }

    public sealed class ECgInputActionMapEqualityComparer : IEqualityComparer<FECgInputActionMap>
    {
        public bool Equals(FECgInputActionMap lhs, FECgInputActionMap rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgInputActionMap x)
        {
            return x.GetHashCode();
        }
    }

    public sealed class FECgInputAction : FECgEnum_byte
    {
        public FECgInputAction(byte value, string name) : base(value, name) { }
    }

    public sealed class EMCgInputAction : TCgEnumMap<FECgInputAction, byte>
    {
        private static EMCgInputAction _Instance;
        public static EMCgInputAction Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgInputAction();
                }
                return _Instance;
            }
        }

        public static EMCgInputAction Get()
        {
            return Instance;
        }
    }

    public sealed class FECgInputActionEqualityComparer : IEqualityComparer<FECgInputAction>
    {
        public bool Equals(FECgInputAction lhs, FECgInputAction rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgInputAction x)
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
        // Action
        FirstPressed,
        Pressed,
        FirstReleased,
        Released,
        // Axis, Location, Rotation, Trigger
        FirstMoved,
        Moved,
        FirstStationary,
        Stationary,
        // Touch
        Began,
        //Moved,
        Ended,
        //Stationary,
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
        Void,
        Float,
        Vector,
        Rotator,
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

    public static class FCgKey
    {
        public static bool IsJoystickKey(KeyCode key)
        {
            if ((int)key >= (int)KeyCode.JoystickButton0 &&
                (int)key <= (int)KeyCode.Joystick8Button19)
                return true;
            return false;
        }

        public static bool IsGamepadKey(KeyCode key)
        {
            return IsJoystickKey(key);
        }
    }

    public sealed class FKeyCodeEqualityComparer : IEqualityComparer<KeyCode>
    {
        public bool Equals(KeyCode lhs, KeyCode rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(KeyCode x)
        {
            return x.GetHashCode();
        }
    }

    public class FCgKeyInputHandler
    {
        public class FCgKeyInputHandler_Event : FCgMulticastDelegate { }

        #region "Data Members"

        public FECgInputAction Action;

        public FCgKeyInputHandler_Event Event;

        #endregion // Data Members

        public FCgKeyInputHandler()
        {
            Action = null;
        }

        public FCgKeyInputHandler(FECgInputAction action)
        {
            Action = action;
            Event = new FCgKeyInputHandler_Event();
        }

        public static bool operator ==(FCgKeyInputHandler lhs, FCgKeyInputHandler rhs)
        {
            if (lhs.Action != rhs.Action) return false;
            if (lhs.Event != rhs.Event) return false;
            return true;
        }

        public static bool operator !=(FCgKeyInputHandler lhs, FCgKeyInputHandler rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgKeyInputHandler))
                return false;

            FCgKeyInputHandler rhs = (FCgKeyInputHandler)obj;

            if (Action != rhs.Action) return false;
            if (Event != rhs.Event) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public FCgDelegateHandle Add(FCgMulticastDelegate.Event e)
        {
            return Event.Add(e);
        }

        public bool Remove(FCgDelegateHandle handle)
        {
            return Event.Remove(handle);
        }

        public void Broadcast()
        {
            Event.Broadcast();
        }
    }

    public class FCgKeyInput
    {
        #region "Data Members"

        public KeyCode Key;
        public ECgInputEvent Event;
        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;

        private Dictionary<FECgInputAction, FCgKeyInputHandler>[] HandlerMap;

        #endregion // Data Members

        public FCgKeyInput()
        {
            Key = KeyCode.None;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerMap = new Dictionary<FECgInputAction, FCgKeyInputHandler>[(byte)ECgInputEvent.MAX];

            int len = (int)ECgInputEvent.MAX;

            for (int i = 0; i < len; ++i)
            {
                HandlerMap[i] = new Dictionary<FECgInputAction, FCgKeyInputHandler>(new FECgInputActionEqualityComparer());
            }
        }

        public FCgKeyInput(KeyCode key)
        {
            Key = key;
            Event = ECgInputEvent.MAX;
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;

            HandlerMap = new Dictionary<FECgInputAction, FCgKeyInputHandler>[(byte)ECgInputEvent.MAX];

            int len = (int)ECgInputEvent.MAX;

            for (int i = 0; i < len; ++i)
            {
                HandlerMap[i] = new Dictionary<FECgInputAction, FCgKeyInputHandler>(new FECgInputActionEqualityComparer());
            }
        }

        public FCgDelegateHandle Bind(FECgInputAction action, ECgInputEvent e, FCgMulticastDelegate.Event del)
        {
            Dictionary<FECgInputAction, FCgKeyInputHandler> map = HandlerMap[(byte)e];

            FCgKeyInputHandler handle = null;
            bool found               = map.TryGetValue(action, out handle);

            if (found)
            {
                return handle.Add(del);
            }
            else
            {
                handle = new FCgKeyInputHandler(action);
                
                map.Add(action, handle);
                return handle.Add(del);
            }
        }

        public bool UnBind(ECgInputEvent e, FCgDelegateHandle handle)
        {
            Dictionary<FECgInputAction, FCgKeyInputHandler> map = HandlerMap[(byte)e];

            Dictionary<FECgInputAction, FCgKeyInputHandler>.ValueCollection handles = map.Values;

            bool success = false;

            foreach (FCgKeyInputHandler h in handles)
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
            Dictionary<FECgInputAction, FCgKeyInputHandler> map = HandlerMap[(byte)e];

            Dictionary<FECgInputAction, FCgKeyInputHandler>.ValueCollection handles = map.Values;

            foreach (FCgKeyInputHandler h in handles)
            { 
                h.Broadcast();
            }
        }
    }

    public class FCgInput
    {
        #region "Data Members"

        public ushort PoolIndex;
        public bool IsAllocated;
        public bool IsConsumed;
        public FECgInputAction Action;
        public ECgInputEvent Event;
        public float Value;
        public Vector3 Location;
        public Vector3 Rotation;
        public float Duration;

        #endregion // Data Members

        public FCgInput()
        {
            PoolIndex = CgTypes_Input.INVALID_INPUT_POOL_INDEX;
            IsAllocated = false;
            IsConsumed = false;
            Action = null;
            Event = ECgInputEvent.MAX;
            Value = Mathf.Infinity;
            Location = Vector3.zero;
            Rotation = Vector3.zero;
            Duration = 0f;
        }

        public FCgInput(ushort poolIndex)
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

        public static bool operator ==(FCgInput lhs, FCgInput rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;

            if (lhs.Action != rhs.Action) return false;
            if (lhs.Event != rhs.Event) return false;
            if (lhs.Value != rhs.Value) return false;
            if (lhs.Location != rhs.Location) return false;
            if (lhs.Rotation != rhs.Rotation) return false;
            if (lhs.Duration != rhs.Duration) return false;
            return true;
        }

        public static bool operator !=(FCgInput lhs, FCgInput rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgInput))
                return false;

            FCgInput input = (FCgInput)obj;

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

        public void Set(FECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
        {
            Action = action;
            Event = e;
            Value = value;
            Location = location;
            Rotation = rotation;
        }

        public void Set(FECgInputAction action, ECgInputEvent e, Vector3 location, Vector3 rotation)
        {
            Set(action, e, 0f, location, rotation);
        }

        public void Set(FECgInputAction action, ECgInputEvent e, float time)
        {
            Set(action, e, time, Vector3.zero, Vector3.zero);
        }

        public void Set(FECgInputAction action, ECgInputEvent e)
        {
            Set(action, e, 0f, Vector3.zero, Vector3.zero);
        }

        public void Allocate(FECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
        {
            IsAllocated = true;
            Set(action, e, value, location, rotation);
        }

        public void Allocate(FECgInputAction action, ECgInputEvent e, Vector3 location, Vector3 rotation)
        {
            Allocate(action, e, 0f, location, rotation);
        }

        public void Allocate(FECgInputAction action, ECgInputEvent e, float value)
        {
            Allocate(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void Allocate(FECgInputAction action, ECgInputEvent e)
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

    public class FCgInputFrame
    {
        #region "Data Members"

        public float Time;
        public float RealTime;
        public float DeltaTime;
        public ulong Frame;
        public List<FCgInput> Inputs;

        #endregion // Data Members

        public FCgInputFrame()
        {
            Time = 0f;
            RealTime = 0f;
            DeltaTime = 0f;
            Frame = 0;
            Inputs = new List<FCgInput>();
        }

        public static bool operator ==(FCgInputFrame lhs, FCgInputFrame rhs)
        {
            if (lhs.Time != rhs.Time) return false;
            if (lhs.RealTime != rhs.RealTime) return false;
            if (lhs.DeltaTime != rhs.DeltaTime) return false;
            if (lhs.Frame != rhs.Frame) return false;

            if (lhs.Inputs.Count != rhs.Inputs.Count) return false;

            int count = lhs.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                if (lhs.Inputs[i] != rhs.Inputs[i])
                    return false;
            }
            return true;
        }

        public static bool operator !=(FCgInputFrame lhs, FCgInputFrame rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgInputFrame))
                return false;

            FCgInputFrame rhs = (FCgInputFrame)obj;

            if (Time != rhs.Time) return false;
            if (RealTime != rhs.RealTime) return false;
            if (DeltaTime != rhs.DeltaTime) return false;
            if (Frame != rhs.Frame) return false;

            if (Inputs.Count != rhs.Inputs.Count) return false;

            int count = Inputs.Count;

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

        public void Copy(FCgInputFrame rhs)
        {
            Time = rhs.Time;
            RealTime = rhs.RealTime;
            DeltaTime = rhs.DeltaTime;
            Frame = rhs.Frame;

            Inputs.Clear();

            int count = rhs.Inputs.Count;

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

            int count = Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                Inputs[i].Reset();
            }
            Inputs.Clear();
        }

        public FCgInput GetInput(FECgInputAction action)
        {
            int count = Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                if (Inputs[i].Action == action)
                    return Inputs[i];
            }
            return null;
        }

        public FCgInput GetInput(FECgInputAction action, ECgInputEvent e)
        {
            FCgInput input = GetInput(action);

            if (input != null)
                return input.Event == e ? input : null;
            return null;
        }

        public FCgInput GetInput(FECgInputAction action, List<ECgInputEvent> events)
        {
            FCgInput input = GetInput(action);

            if (input != null)
                return events.IndexOf(input.Event) != CgTypes.INDEX_NONE ? input : null;
            return null;
        }
    }

    public class FCgInputInfo
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

        public FCgInputInfo(ECgInputType type, ECgInputValue valueType)
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

        public static bool operator ==(FCgInputInfo lhs, FCgInputInfo rhs)
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

        public static bool operator !=(FCgInputInfo lhs, FCgInputInfo rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgInputInfo))
                return false;

            FCgInputInfo rhs = (FCgInputInfo)obj;

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

    public sealed class FCgInputWord
    {
        public bool Completed;
        public float CompletedTime;
        public bool Consume;
        public List<FCgInput> AndInputs;
        public List<FCgInput> OrInputs;

        public FCgInputWord()
        {
            Completed = false;
            CompletedTime = 0.0f;
            Consume = false;
            AndInputs = new List<FCgInput>();
            OrInputs = new List<FCgInput>();
        }

        public void AddAndInput(FECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
	    {
            AndInputs.Add(new FCgInput());
		    int index = AndInputs.Count - 1;
            AndInputs[index].Action = action;
		    AndInputs[index].Event = e;
		    AndInputs[index].Value = value;
		    AndInputs[index].Location = location;
		    AndInputs[index].Rotation = rotation;
	    }

        public void AddAndInput(FECgInputAction action, ECgInputEvent e)
        {
            AddAndInput(action, e, 0.0f, Vector3.zero, Vector3.zero);
        }

        public void AddAndInput(FECgInputAction action, ECgInputEvent e, float value)
        {
            AddAndInput(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void AddAndInput(FECgInputAction action, ECgInputEvent e, Vector3 location)
        {
            AddAndInput(action, e, 0.0f, location, Vector3.zero);
        }

        public void AddAndInput(FECgInputAction action, ECgInputEvent e, Quaternion rotation)
        {
            AddAndInput(action, e, 0.0f, Vector3.zero, rotation.eulerAngles);
        }

        public void AddOrInput(FECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
        {
            OrInputs.Add(new FCgInput());
            int index = OrInputs.Count - 1;
            OrInputs[index].Action = action;
            OrInputs[index].Event = e;
            OrInputs[index].Value = value;
            OrInputs[index].Location = location;
            OrInputs[index].Rotation = rotation;
        }

        public void AddOrInput(FECgInputAction action, ECgInputEvent e)
        {
            AddOrInput(action, e, 0.0f, Vector3.zero, Vector3.zero);
        }

        public void AddOrInput(FECgInputAction action, ECgInputEvent e, float value)
        {
            AddOrInput(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void AddOrInput(FECgInputAction action, ECgInputEvent e, Vector3 location)
        {
            AddOrInput(action, e, 0.0f, location, Vector3.zero);
        }

        public void AddOrInput(FECgInputAction action, ECgInputEvent e, Quaternion rotation)
        {
            AddOrInput(action, e, 0.0f, Vector3.zero, rotation.eulerAngles);
        }

        public void Reset()
        {
            Completed = false;
        }

        public void ProcessInput(FCgInputFrame inputFrame)
        {
            int and = 0;
            bool or = false;
            
            int count = inputFrame.Inputs.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                FCgInput input = inputFrame.Inputs[i];
                
                // Check And
                int andCount = AndInputs.Count;

                for (int j = and; j < andCount; ++j)
                {
                    if (input.Action == AndInputs[j].Action &&
                        input.Event == AndInputs[j].Event)
                    {
                        ++and;
                    }
                }
                // Check Or
                int orCount = OrInputs.Count;

                for (int j = 0; j < orCount; ++j)
                {
                    or |= input.Action == OrInputs[j].Action && input.Event == OrInputs[j].Event;
                    
                    if (or)
                        break;
                }

                Completed = (and > 0 && and == andCount) || or;

                if (Completed)
                {
                    if (Consume)
                        inputFrame.Inputs.RemoveAt(i);
                    CompletedTime = inputFrame.Time;
                    break;
                }
            }
        }
    }

    public sealed class FCgInputPhrase
    {
        public bool Completed;
        public float CompletedTime;
        public bool UseInterval;
        public float Interval;
        public bool UseFrames;
        public int Frames;
        public List<FCgInputWord> Words;

        public FCgInputPhrase()
        {
            Completed = false;
            CompletedTime = 0.0f;
            UseInterval = false;
            Interval = 0.0f;
            UseFrames = false;
            Frames = 0;
            Words = new List<FCgInputWord>();
        }

        public void AddAndInputToWord(int index, FECgInputAction action, ECgInputEvent e, float value = 0.0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
	    {
		    int count = Words.Count;

		    if (index >= count)
		    {
			    for (int i = 0; i < index - count + 1; ++i)
			    {
				    Words.Add(new FCgInputWord());
			    }
		    }
		    Words[index].AddAndInput(action, e, value, location, rotation);
	    }

	    public void AddOrInputToWord(int index, FECgInputAction action, ECgInputEvent e, float value = 0.0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new FCgInputWord());
                }
            }
            Words[index].AddOrInput(action, e, value, location, rotation);
        }

        public void Reset()
        {
            int count = Words.Count;

            for (int i = 0; i < count; ++i)
            {
                Words[i].Reset();
            }
            Completed = false;
            CompletedTime = 0.0f;
        }

        public void ProcessInput(FCgInputFrame inputFrame)
        {
            float currentTime = inputFrame.Time;

            // Check if ALL Words are Completed
            int count = Words.Count;
            int index = 0;

            if (UseInterval)
            {
                //float elapsedTime = 0.0f;
                float earliestCompletedTime = currentTime;

                for (index = 0; index < count; ++index)
                {
                    if (Words[index].Completed)
                    {
                        if (Words[index].CompletedTime < earliestCompletedTime)
                            earliestCompletedTime = Words[index].CompletedTime;

                        if (currentTime - earliestCompletedTime > Interval)
                        {
                            Reset();

                            index = 0;
                            break;
                        }
                    }

                    Words[index].ProcessInput(inputFrame);

                    if (index < count - 1 || !Words[index].Completed)
                        break;
                }
            }
            else
            {
                for (index = 0; index < count; ++index)
                {
                    if (Words[index].Completed)
                        continue;

                    Words[index].ProcessInput(inputFrame);

                    if (index < count - 1 || !Words[index].Completed)
                        break;
                }

                if (index != count)
                    Reset();
            }
            // Check if Completed
            if (index > 0 && index == count)
            {
                Completed     = true;
                CompletedTime = currentTime;
            }
        }
    }

    public sealed class FCgInputSentence
    {
        public bool Active;
        public bool Completed;
        public float CompletedTime;
        public float Cooldown;
        public bool UseInterval;
        public float Interval;
        public bool UseFrames;
        public int Frames;
        public List<FCgInputPhrase> Phrases;

        public FCgInputSentence()
        {
            Active = true;
            Completed = false;
            CompletedTime = 0.0f;
            Cooldown = 0.0f;
            UseInterval = false;
            Interval = 0.0f;
            UseFrames = false;
            Frames = 0;
            Phrases = new List<FCgInputPhrase>();
        }

        public void Reset()
        {
            Active = true;

            int count = Phrases.Count;

            for (int i = 0; i < count; ++i)
            {
                Phrases[i].Reset();
            }
            Completed = false;
        }

        public void ProcessInput(FCgInputFrame inputFrame)
        {
            float currentTime = inputFrame.Time;

            // Check if Cooldown has Expired
            if (!Active)
            {
                if (currentTime - CompletedTime >= Cooldown)
                    Reset();
                else
                    return;
            }
            // Check if ALL Phrases are Completed
            int count = Phrases.Count;
            int index = 0;

            if (UseInterval)
            {
                //float elapsedTime = 0.0f;
                float earliestCompletedTime = currentTime;

                for (index = 0; index < count; ++index)
                {
                    if (Phrases[index].Completed)
                    {
                        if (Phrases[index].CompletedTime < earliestCompletedTime)
                            earliestCompletedTime = Phrases[index].CompletedTime;

                        if (currentTime - earliestCompletedTime > Interval)
                        {
                            Reset();

                            index = 0;
                            break;
                        }
                    }

                    Phrases[index].ProcessInput(inputFrame);

                    if (index < count - 1 || !Phrases[index].Completed)
                        break;
                }
            }
            else
            {
                for (index = 0; index < count; ++index)
                {
                    if (Phrases[index].Completed)
                        continue;

                    Phrases[index].ProcessInput(inputFrame);

                    if (index < count - 1 || !Phrases[index].Completed)
                        break;
                }

                if (index != count)
                    Reset();
            }
            // Check if Completed
            if (index == count)
            {
                Completed     = true;
                CompletedTime = currentTime;
                Active        = false;
            }
        }
    }

    public class FCgInputActionMapping
    {
        public string ActionName;
        public FECgInputAction Action;
        public string KeyName;
        public KeyCode Key;
        public float Scale;

        public FCgInputActionMapping()
        {
            ActionName = "";
            Action = null;
            KeyName = "";
            Key = KeyCode.None;
            Scale = 1.0f;
        }

        public static bool operator ==(FCgInputActionMapping lhs, FCgInputActionMapping rhs)
        {
            if (lhs.ActionName != rhs.ActionName) return false;
            if (lhs.Action != rhs.Action) return false;
            if (lhs.KeyName != rhs.KeyName) return false;
            if (lhs.Key != rhs.Key) return false;
            if (lhs.Scale != rhs.Scale) return false;
            return true;
        }

        public static bool operator !=(FCgInputActionMapping lhs, FCgInputActionMapping rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgInputActionMapping))
                return false;

            FCgInputActionMapping rhs = (FCgInputActionMapping)obj;

            if (ActionName != rhs.ActionName) return false;
            if (Action != rhs.Action) return false;
            if (KeyName != rhs.KeyName) return false;
            if (Key != rhs.Key) return false;
            if (Scale != rhs.Scale) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return ActionName.GetHashCode() ^ Action.GetHashCode() ^ KeyName.GetHashCode() ^ Key.GetHashCode() ^ Scale.GetHashCode();
        }
    }

    public class FCgInputActionMappings
    {
        public List<FCgInputActionMapping> Mappings;

        public static bool operator ==(FCgInputActionMappings lhs, FCgInputActionMappings rhs)
        {
            if (lhs.Mappings.Count != rhs.Mappings.Count) return false;

            int count = lhs.Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                if (lhs.Mappings[i] != rhs.Mappings[i])
                    return false;
            }
            return true;
        }

        public static bool operator !=(FCgInputActionMappings lhs, FCgInputActionMappings rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgInputActionMappings))
                return false;

            FCgInputActionMappings rhs = (FCgInputActionMappings)obj;

            if (Mappings.Count != rhs.Mappings.Count) return false;

            int count = Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                if (Mappings[i] != rhs.Mappings[i])
                    return false;
            }
            return true;
        }

        public override int GetHashCode()
        {
            int count = Mappings.Count;
            int value = count > 0 ? Mappings[CgTypes.FIRST].GetHashCode() : base.GetHashCode();

            for (int i = 1; i < count; ++i)
            {
                value ^= Mappings[i].GetHashCode();
            }
            return value;
        }
    }

    public class FCgInputProfile
    {
        public byte Player;
        public FCgInputActionMappings[] DeviceMappings;

        FCgInputProfile()
        {
            Player = 0;
            DeviceMappings = new FCgInputActionMappings[(byte)ECgInputDevice.MAX];
        }

        public FCgInputActionMapping GetMapping(ECgInputDevice device, FECgInputAction action)
	    {
		    FCgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
		    List<FCgInputActionMapping> mappings = deviceMapping.Mappings;

		    int count = mappings.Count;

		    for (int i = 0; i < count; ++i)
		    {
			    FCgInputActionMapping mapping = mappings[i];

			    if (action == mapping.Action)
				    return deviceMapping.Mappings[i];
		    }
		    return mappings[CgTypes.FIRST];
	    }

	    public KeyCode GetKey(ECgInputDevice device, FECgInputAction action)
        {
            FCgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<FCgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInputActionMapping mapping = mappings[i];

                if (action == mapping.Action)
                    return mapping.Key;
            }
            return KeyCode.None;
        }

        public void SetKey(ECgInputDevice device, FECgInputAction action, KeyCode key)
        {
            FCgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<FCgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgInputActionMapping mapping = mappings[i];

                if (action == mapping.Action)
                {
                    mapping.KeyName = key == KeyCode.None ? "" : key.ToString();
                    mapping.Key     = key;
                    break;
                }
            }
        }

        public void AddMapping(ECgInputDevice device, string actionName, FECgInputAction action, string keyName, KeyCode key)
        {
            FCgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<FCgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;
            mappings.Add(new FCgInputActionMapping());
            FCgInputActionMapping mapping = mappings[count];
            mapping.ActionName          = actionName;
            mapping.Action              = action;
            mapping.KeyName             = keyName;
            mapping.Key                 = key;
        }

        public void Reset()
        {
            int count = (byte)ECgInputDevice.MAX;

            for (int i = 0; i < count; ++i)
            {
                DeviceMappings[i].Mappings.Clear();
            }
        }
    }

    public sealed class FECgGameEvent : FECgEnum_byte
    {
        public FECgGameEvent(byte value, string name) : base(value, name) { }
    }

    public sealed class EMCgGameEvent : TCgEnumMap<FECgGameEvent, byte>
    {
        private static EMCgGameEvent _Instance;
        public static EMCgGameEvent Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameEvent();
                }
                return _Instance;
            }
        }

        public static EMCgGameEvent Get()
        {
            return Instance;
        }
    }

    public sealed class FECgGameEventEqualityComparer : IEqualityComparer<FECgGameEvent>
    {
        public bool Equals(FECgGameEvent lhs, FECgGameEvent rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameEvent x)
        {
            return x.GetHashCode();
        }
    }

    public class FCgGameEventDefinition
    {
        public FCgInputSentence Sentence;
        public FECgGameEvent Event;

        public FCgGameEventDefinition()
        {
            Sentence = new FCgInputSentence();
        }
    }
}

