// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;

    public struct FCgDelegateHandle : IEquatable<FCgDelegateHandle>
    {
        public object Object;
        public string Name;
        public Guid Id;

        public FCgDelegateHandle(object o, string name, Guid id)
        {
            Object = o;
            Name = name;
            Id = id;
        }
               
        public static bool operator ==(FCgDelegateHandle lhs, FCgDelegateHandle rhs)
        {
            return lhs.Object == rhs.Object && lhs.Name == rhs.Name && lhs.Id == rhs.Id;
        }

        public static bool operator !=(FCgDelegateHandle lhs, FCgDelegateHandle rhs)
        {
            return !(lhs == rhs);
        }

        public bool Equals(FCgDelegateHandle rhs)
        {
            if (Object != rhs.Object) return false;
            if (Name != rhs.Name) return false;
            if (Id != rhs.Id) return false;
            return true;
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgDelegateHandle))
                return false;

            FCgDelegateHandle rhs = (FCgDelegateHandle)obj;

            if (Object != rhs.Object) return false;
            if (Name != rhs.Name) return false;
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

        public void Unbind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public void Execute()
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

        public void Unbind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public void Execute(T t)
        {
            if (e != null)
                e(t);
        }
    }

    public abstract class TCgDelegate_Ret_OneParam<Ret, T>
    {
        public delegate Ret Event(T t);

        private Event e;

        public void Bind(Event inEvent)
        {
            e = inEvent;
        }

        public void Unbind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public Ret Execute(T t)
        {
            if (e != null)
                return e(t);
            return default(Ret);
        }
    }

    public abstract class TCgDelegate_TwoParams<T1, T2>
    {
        public delegate void Event(T1 t1, T2 t2);

        private Event e;

        public void Bind(Event inEvent)
        {
            e = inEvent;
        }

        public void Unbind()
        {
            e = null;
        }

        public bool IsBound()
        {
            return e != null;
        }

        public void Execute(T1 t1, T2 t2)
        {
            if (e != null)
                e(t1, t2);
        }
    }

    #endregion // Single

    #region "Multicast"

    public interface ICgMulticastDelegate
    {
    }

    public abstract class CgMulticastDelegate : ICgMulticastDelegate
    {
        public delegate void Event();

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public CgMulticastDelegate()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
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
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e();
            }
        }

        public void CopyTo(CgMulticastDelegate to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys     = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_OneParam<T> : ICgMulticastDelegate
    {
        public delegate void Event(T t);

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_OneParam()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
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
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t);
            }
        }

        public void CopyTo(TCgMulticastDelegate_OneParam<T> to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_TwoParams<T1, T2> : ICgMulticastDelegate
    {
        public delegate void Event(T1 t1, T2 t2);

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_TwoParams()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
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
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t1, t2);
            }
        }

        public void CopyTo(TCgMulticastDelegate_TwoParams<T1, T2> to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_ThreeParams<T1, T2, T3> : ICgMulticastDelegate
    {
        public delegate void Event(T1 t1, T2 t2, T3 t3);

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_ThreeParams()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
        {
            return InvocationMap.Remove(handle);
        }

        public void Clear()
        {
            InvocationMap.Clear();
        }

        public void Broadcast(T1 t1, T2 t2, T3 t3)
        {
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                e(t1, t2, t3);
            }
        }

        public void CopyTo(TCgMulticastDelegate_ThreeParams<T1, T2, T3> to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_RetOrBool_OneParam<T> : ICgMulticastDelegate
    {
        public delegate bool Event(T t);

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_RetOrBool_OneParam()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
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
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (Event e in events)
            {
                if (e(t))
                    return true;
            }
            return false;
        }

        public void CopyTo(TCgMulticastDelegate_RetOrBool_OneParam<T> to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    public abstract class TCgMulticastDelegate_RetAndBool_OneParam<T> : ICgMulticastDelegate
    {
        public delegate bool Event(T t);

        private Dictionary<FCgDelegateHandle, Event> InvocationMap;

        public TCgMulticastDelegate_RetAndBool_OneParam()
        {
            InvocationMap = new Dictionary<FCgDelegateHandle, Event>();
        }

        public FCgDelegateHandle AddObject(object o, Event e)
        {
            FCgDelegateHandle handle = new FCgDelegateHandle(o, "", Guid.NewGuid());

            InvocationMap.Add(handle, e);
            return handle;
        }

        public FCgDelegateHandle Add(Event e)
        {
            return AddObject(null, e);
        }

        public bool Remove(FCgDelegateHandle handle)
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
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            bool ret = true;

            foreach (Event e in events)
            {
                ret &= e(t);
            }
            return (events.Count > 0) & ret;
        }

        public void CopyTo(TCgMulticastDelegate_RetAndBool_OneParam<T> to)
        {
            to.Clear();

            Dictionary<FCgDelegateHandle, Event>.KeyCollection keys = InvocationMap.Keys;
            Dictionary<FCgDelegateHandle, Event>.ValueCollection events = InvocationMap.Values;

            foreach (FCgDelegateHandle key in keys)
            {
                to.AddObject(key.Object, InvocationMap[key]);
            }
        }
    }

    #endregion // Multicast
}
