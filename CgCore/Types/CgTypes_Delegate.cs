// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;

    #region "Multicast"

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

    // TODO: Rename to CgMulticastDelegate
    // TODO: Add CgMulticastDelegate_Base

    public abstract class CgDelegate
    {
        public delegate void Event();

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public CgDelegate()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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

        public void Broadcast()
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e();
            }
        }
    }

    public abstract class TCgDelegate_OneParam<T>
    {
        public delegate void Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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

        public void Broadcast(T t)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t);
            }
        }
    }

    public abstract class TCgDelegate_TwoParams<T1, T2>
    {
        public delegate void Event(T1 t1, T2 t2);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_TwoParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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

        public void Broadcast(T1 t1, T2 t2)
        {
            Dictionary<CgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t1, t2);
            }
        }
    }

    public abstract class TCgDelegate_ThreeParams<T1, T2, T3>
    {
        public delegate void Event(T1 t1, T2 t2, T3 t3);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_ThreeParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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

    public abstract class TCgDelegate_RetOrBool_OneParam<T>
    {
        public delegate bool Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_RetOrBool_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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

    public abstract class TCgDelegate_RetAndBool_OneParam<T>
    {
        public delegate bool Event(T t);

        private Dictionary<CgDelegateHandle, Event> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_RetAndBool_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
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
