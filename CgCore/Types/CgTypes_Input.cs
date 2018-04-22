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

    public class ECgInputActionMap : ECgEnum_int
    {
        public static readonly ECgInputActionMap NONE = new ECgInputActionMap(0, "None");

        public ECgInputActionMap(int value, string name) : base(value, name) { }
    }

    public sealed class ECgInputActionMapHelper
    {
        public ECgInputActionMap.Get Get;
        public ECgInputActionMap.ToType ToType;
        public ECgInputActionMap.ToStr ToStr;

        public ECgInputActionMap.ToMask ToMask;
        public ECgInputActionMap.MaskToStr MaskToStr;
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

    public sealed class ECgInputAction : ECgEnum_byte
    {
        public ECgInputAction(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgInputActionHelper
    {
        public ECgInputAction.Get Get;
        public ECgInputAction.GetMAX GetMAX;
        public ECgInputAction.ToType ToType;
        public ECgInputAction.ToStr ToStr;

        public ECgInputAction MAX;
        public byte Max;
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

    public static class CgKey
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

    public sealed class KeyCodeEqualityComparer : IEqualityComparer<KeyCode>
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

        public CgInput()
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

            if (lhs.Inputs.Count != rhs.Inputs.Count) return false;

            int count = lhs.Inputs.Count;

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

        public void Copy(CgInputFrame rhs)
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

        public CgInput GetInput(ECgInputAction action)
        {
            int count = Inputs.Count;

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

    public class CgInputWord
    {
        public bool Completed;
        public float CompletedTime;
        public bool Consume;
        public List<CgInput> AndInputs;
        public List<CgInput> OrInputs;

        public CgInputWord()
        {
            Completed = false;
            CompletedTime = 0.0f;
            Consume = false;
            AndInputs = new List<CgInput>();
            OrInputs = new List<CgInput>();
        }

        public void AddAndInput(ECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
	    {
            AndInputs.Add(new CgInput());
		    int index = AndInputs.Count - 1;
            AndInputs[index].Action = action;
		    AndInputs[index].Event = e;
		    AndInputs[index].Value = value;
		    AndInputs[index].Location = location;
		    AndInputs[index].Rotation = rotation;
	    }

        public void AddAndInput(ECgInputAction action, ECgInputEvent e)
        {
            AddAndInput(action, e, 0.0f, Vector3.zero, Vector3.zero);
        }

        public void AddAndInput(ECgInputAction action, ECgInputEvent e, float value)
        {
            AddAndInput(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void AddAndInput(ECgInputAction action, ECgInputEvent e, Vector3 location)
        {
            AddAndInput(action, e, 0.0f, location, Vector3.zero);
        }

        public void AddAndInput(ECgInputAction action, ECgInputEvent e, Quaternion rotation)
        {
            AddAndInput(action, e, 0.0f, Vector3.zero, rotation.eulerAngles);
        }

        public void AddOrInput(ECgInputAction action, ECgInputEvent e, float value, Vector3 location, Vector3 rotation)
        {
            OrInputs.Add(new CgInput());
            int index = OrInputs.Count - 1;
            OrInputs[index].Action = action;
            OrInputs[index].Event = e;
            OrInputs[index].Value = value;
            OrInputs[index].Location = location;
            OrInputs[index].Rotation = rotation;
        }

        public void AddOrInput(ECgInputAction action, ECgInputEvent e)
        {
            AddOrInput(action, e, 0.0f, Vector3.zero, Vector3.zero);
        }

        public void AddOrInput(ECgInputAction action, ECgInputEvent e, float value)
        {
            AddOrInput(action, e, value, Vector3.zero, Vector3.zero);
        }

        public void AddOrInput(ECgInputAction action, ECgInputEvent e, Vector3 location)
        {
            AddOrInput(action, e, 0.0f, location, Vector3.zero);
        }

        public void AddOrInput(ECgInputAction action, ECgInputEvent e, Quaternion rotation)
        {
            AddOrInput(action, e, 0.0f, Vector3.zero, rotation.eulerAngles);
        }

        public void Reset()
        {
            Completed = false;
        }

        public void ProcessInput(CgInputFrame inputFrame)
        {
            int and = 0;
            bool or = false;
            
            int count = inputFrame.Inputs.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                CgInput input = inputFrame.Inputs[i];
                
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

    public class CgInputPhrase
    {
        public bool Completed;
        public float CompletedTime;
        public bool UseInterval;
        public float Interval;
        public bool UseFrames;
        public int Frames;
        public List<CgInputWord> Words;

        public CgInputPhrase()
        {
            Completed = false;
            CompletedTime = 0.0f;
            UseInterval = false;
            Interval = 0.0f;
            UseFrames = false;
            Frames = 0;
            Words = new List<CgInputWord>();
        }

        public void AddAndInputToWord(int index, ECgInputAction action, ECgInputEvent e, float value = 0.0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
	    {
		    int count = Words.Count;

		    if (index >= count)
		    {
			    for (int i = 0; i < index - count + 1; ++i)
			    {
				    Words.Add(new CgInputWord());
			    }
		    }
		    Words[index].AddAndInput(action, e, value, location, rotation);
	    }

	    public void AddOrInputToWord(int index, ECgInputAction action, ECgInputEvent e, float value = 0.0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            int count = Words.Count;

            if (index >= count)
            {
                for (int i = 0; i < index - count + 1; ++i)
                {
                    Words.Add(new CgInputWord());
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

        public void ProcessInput(CgInputFrame inputFrame)
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

    public class CgInputSentence
    {
        public bool Active;
        public bool Completed;
        public float CompletedTime;
        public float Cooldown;
        public bool UseInterval;
        public float Interval;
        public bool UseFrames;
        public int Frames;
        public List<CgInputPhrase> Phrases;

        public CgInputSentence()
        {
            Active = true;
            Completed = false;
            CompletedTime = 0.0f;
            Cooldown = 0.0f;
            UseInterval = false;
            Interval = 0.0f;
            UseFrames = false;
            Frames = 0;
            Phrases = new List<CgInputPhrase>();
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

        public void ProcessInput(CgInputFrame inputFrame)
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

    public class CgInputActionMapping
    {
        public string ActionName;
        public ECgInputAction Action;
        public string KeyName;
        public KeyCode Key;
        public float Scale;

        public CgInputActionMapping()
        {
            ActionName = "";
            Action = null;
            KeyName = "";
            Key = KeyCode.None;
            Scale = 1.0f;
        }

        public static bool operator ==(CgInputActionMapping lhs, CgInputActionMapping rhs)
        {
            if (lhs.ActionName != rhs.ActionName) return false;
            if (lhs.Action != rhs.Action) return false;
            if (lhs.KeyName != rhs.KeyName) return false;
            if (lhs.Key != rhs.Key) return false;
            if (lhs.Scale != rhs.Scale) return false;
            return true;
        }

        public static bool operator !=(CgInputActionMapping lhs, CgInputActionMapping rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgInputActionMapping))
                return false;

            CgInputActionMapping rhs = (CgInputActionMapping)obj;

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

    public class CgInputActionMappings
    {
        public List<CgInputActionMapping> Mappings;

        public static bool operator ==(CgInputActionMappings lhs, CgInputActionMappings rhs)
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

        public static bool operator !=(CgInputActionMappings lhs, CgInputActionMappings rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgInputActionMappings))
                return false;

            CgInputActionMappings rhs = (CgInputActionMappings)obj;

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

    public class CgInputProfile
    {
        public byte Player;
        public CgInputActionMappings[] DeviceMappings;

        CgInputProfile()
        {
            Player = 0;
            DeviceMappings = new CgInputActionMappings[(byte)ECgInputDevice.MAX];
        }

        public CgInputActionMapping GetMapping(ECgInputDevice device, ECgInputAction action)
	    {
		    CgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
		    List<CgInputActionMapping> mappings = deviceMapping.Mappings;

		    int count = mappings.Count;

		    for (int i = 0; i < count; ++i)
		    {
			    CgInputActionMapping mapping = mappings[i];

			    if (action == mapping.Action)
				    return deviceMapping.Mappings[i];
		    }
		    return mappings[CgTypes.FIRST];
	    }

	    public KeyCode GetKey(ECgInputDevice device, ECgInputAction action)
        {
            CgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<CgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInputActionMapping mapping = mappings[i];

                if (action == mapping.Action)
                    return mapping.Key;
            }
            return KeyCode.None;
        }

        public void SetKey(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            CgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<CgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInputActionMapping mapping = mappings[i];

                if (action == mapping.Action)
                {
                    mapping.KeyName = key == KeyCode.None ? "" : key.ToString();
                    mapping.Key     = key;
                    break;
                }
            }
        }

        public void AddMapping(ECgInputDevice device, string actionName, ECgInputAction action, string keyName, KeyCode key)
        {
            CgInputActionMappings deviceMapping = DeviceMappings[(byte)device];
            List<CgInputActionMapping> mappings = deviceMapping.Mappings;

            int count = mappings.Count;
            mappings.Add(new CgInputActionMapping());
            CgInputActionMapping mapping = mappings[count];
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

    public sealed class ECgGameEvent : ECgEnum_byte
    {
        public ECgGameEvent(byte value, string name) : base(value, name) { }
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

    public sealed class ECgGameEventHelper
    {
        public ECgGameEvent.Get Get;
        public ECgGameEvent.GetMAX GetMAX;
        public ECgGameEvent.ToType ToType;
        public ECgGameEvent.ToStr ToStr;
    }

    public class CgGameEventDefinition
    {
        public CgInputSentence Sentence;
        public ECgGameEvent Event;

        public CgGameEventDefinition()
        {
            Sentence = new CgInputSentence();
        }
    }
}

