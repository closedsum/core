﻿namespace CgCore
{
    using System.Collections.Generic;

    public struct CgDelegateHandle
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

    public abstract class TCgDelegate_OneParam<T>
    {
        public delegate void Event_OneParam(T t);

        private Dictionary<CgDelegateHandle, Event_OneParam> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_OneParam()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event_OneParam>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
        }

        public void AddObject(object o, Event_OneParam e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
        }

        public void Remove(CgDelegateHandle handle)
        {
            InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public void Broadcast(T t)
        {
            Dictionary<CgDelegateHandle, Event_OneParam>.ValueCollection events = InvocationMap.Values;

            foreach (Event_OneParam e in events)
            {
                e(t);
            }
        }
    }

    public abstract class TCgDelegate_TwoParams<T1, T2>
    {
        public delegate void Event_TwoParams(T1 t1, T2 t2);

        private Dictionary<CgDelegateHandle, Event_TwoParams> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_TwoParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event_TwoParams>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
        }

        public void AddObject(object o, Event_TwoParams e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
        }

        public void Remove(CgDelegateHandle handle)
        {
            InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public void Broadcast(T1 t1, T2 t2)
        {
            Dictionary<CgDelegateHandle, Event_TwoParams>.ValueCollection events = InvocationMap.Values;

            foreach (Event_TwoParams e in events)
            {
                e(t1, t2);
            }
        }
    }

    public abstract class TCgDelegate_ThreeParams<T1, T2, T3>
    {
        public delegate void Event_ThreeParams(T1 t1, T2 t2, T3 t3);

        private Dictionary<CgDelegateHandle, Event_ThreeParams> InvocationMap;
        private ulong IdIndex;

        public TCgDelegate_ThreeParams()
        {
            InvocationMap = new Dictionary<CgDelegateHandle, Event_ThreeParams>();
            IdIndex = 0;
        }

        private ulong GetId()
        {
            ++IdIndex;
            return IdIndex;
        }

        public void AddObject(object o, Event_ThreeParams e)
        {
            CgDelegateHandle handle = new CgDelegateHandle(o, GetId());

            InvocationMap.Add(handle, e);
        }

        public void Remove(CgDelegateHandle handle)
        {
            InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public void Broadcast(T1 t1, T2 t2, T3 t3)
        {
            Dictionary<CgDelegateHandle, Event_ThreeParams>.ValueCollection events = InvocationMap.Values;

            foreach (Event_ThreeParams e in events)
            {
                e(t1, t2, t3);
            }
        }
    }
}
