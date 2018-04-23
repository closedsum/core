// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;

    public struct CgDelegateHandle : IEquatable<CgDelegateHandle>
    {
        public object Object;
        public ulong Id;

        public CgDelegateHandle(object o, ulong id)
        {
            Object = o;
            Id = id;
        }

        public static bool operator ==(CgDelegateHandle lhs, CgDelegateHandle rhs)
        {
            return lhs.Object == rhs.Object && lhs.Id == rhs.Id;
        }

        public static bool operator !=(CgDelegateHandle lhs, CgDelegateHandle rhs)
        {
            return !(lhs == rhs);
        }

        public bool Equals(CgDelegateHandle rhs)
        {
            if (Object != rhs.Object) return false;
            if (Id != rhs.Id) return false;
            return true;
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CgDelegateHandle))
                return false;

            CgDelegateHandle rhs = (CgDelegateHandle)obj;

            if (Object != rhs.Object) return false;
            if (Id != rhs.Id) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }
    }

    #region "Single"

    public abstract class CgDelegate
    {
        public delegate void Event();

        private Event e;

        public void Bind(Event inEvent)
        {
            e = inEvent;
        }

        public void UnBind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public void Broacast()
        {
            if (e != null)
                e();
        }
    }

    public abstract class TCgDelegate_OneParam<T>
    {
        public delegate void Event(T t);

        private Event e;

        public void Bind(Event inEvent)
        {
            e = inEvent;
        }

        public void UnBind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public void Broacast(T t)
        {
            if (e != null)
                e(t);
        }
    }

    #endregion // Single

    #region "Multicast"

    public abstract class CgMulticastDelegate_Base
    {
        private static ulong IdIndex = 0;

        protected ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
        }
    }

    public abstract class CgMulticastDelegate : CgMulticastDelegate_Base
    {
        public delegate void Event();

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public CgMulticastDelegate()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public bool IsBound()
        {
            return InvocationMap.Values.Count > 0;
        }

        public void Broadcast()
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e();
            }
        }

        public void CopyTo(CgMulticastDelegate to)
        {
            to.Clear();

            Dictionary<CgDelegateHandle, Event>.KeyCollection keys     = InvocationMap.Keys;
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (CgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_OneParam<T> : CgMulticastDelegate_Base
    {
        public delegate void Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public bool IsBound()
        {
            return InvocationMap.Values.Count > 0;
        }

        public void Broadcast(T t)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t);
            }
        }
    }

    public abstract class TCgMulticastDelegate_TwoParams<T1, T2> : CgMulticastDelegate_Base
    {
        public delegate void Event(T1 t1, T2 t2);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_TwoParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public bool IsBound()
        {
            return InvocationMap.Values.Count > 0;
        }

        public void Broadcast(T1 t1, T2 t2)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t1, t2);
            }
        }
    }

    public abstract class TCgMulticastDelegate_ThreeParams<T1, T2, T3> : CgMulticastDelegate_Base
    {
        public delegate void Event(T1 t1, T2 t2, T3 t3);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_ThreeParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public void Broadcast(T1 t1, T2 t2, T3 t3)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t1, t2, t3);
            }
        }
    }

    public abstract class TCgMulticastDelegate_RetOrBool_OneParam<T> : CgMulticastDelegate_Base
    {
        public delegate bool Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_RetOrBool_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public bool IsBound()
        {
            return InvocationMap.Values.Count > 0;
        }

        public bool Broadcast(T t)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                if (e(t))
                    return true;
            }
            return false;
        }
    }

    public abstract class TCgMulticastDelegate_RetAndBool_OneParam<T> : CgMulticastDelegate_Base
    {
        public delegate bool Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_RetAndBool_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
        }

        public CgDelegateHandle AddObject(object o, Event e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public CgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(CgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public bool IsBound()
        {
            return InvocationMap.Values.Count > 0;
        }

        public bool Broadcast(T t)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            bool ret = true;

            foreach (Event e in events)
            {
                ret &= e(t);
            }
            return (events.Count > 0) & ret;
        }
    }

    #endregion // Multicast
}
