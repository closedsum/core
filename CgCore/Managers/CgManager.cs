﻿namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using System.Reflection;
    using UnityEngine;

    public interface ICgPooledObjectPayload
    {
        bool bAllocated { get; set; }

        object Instigator { get; set; }
        object Owner { get; set; }
        object Parent { get; set; }

        void Reset();
    }

    public abstract class FCgPooledObjectPayload : ICgPooledObjectPayload
    {
        private bool _bAllocated;
        public bool bAllocated
        {
            get { return _bAllocated; }
            set { _bAllocated = value; }
        }

        private object _Instigator;
        public object Instigator
        {
            get { return _Instigator; }
            set { _Instigator = value; }
        }

        private object _Owner;
        public object Owner
        {
            get { return _Owner; }
            set { _Owner = value; }
        }

        private object _Parent;
        public object Parent
        {
            get { return _Parent; }
            set { _Parent = value; }
        }

        public virtual void Reset()
        {
            Instigator = null;
            Owner = null;
            Parent = null;
        }
    }

    public interface ICgManager
    {

    }

    public class TCgManager_PooledObjects<EnumType, ObjectType, PayloadType> : ICgManager 
        where ObjectType : TCgPooledObject<EnumType>
        where PayloadType : ICgPooledObjectPayload
    {
        protected sealed class FEnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        public sealed class FExecute_ConstructObject : TCgDelegate_Ret_OneParam<ObjectType, EnumType> { }
        public sealed class FOnAddToPool : TCgMulticastDelegate_TwoParams<EnumType, ObjectType> { }

        protected static int EMPTY = 0;
        protected static int FIRST = 0;

        private static TCgManager_PooledObjects<EnumType, ObjectType, PayloadType> _Instance;
        public static TCgManager_PooledObjects<EnumType, ObjectType, PayloadType> Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new TCgManager_PooledObjects<EnumType, ObjectType, PayloadType>();
                }
                return _Instance;
            }
        }

        #region "Data Members

        protected Dictionary<EnumType, int> PoolSizes;
        protected List<ObjectType> Pool;
        protected Dictionary<EnumType, List<ObjectType>> Pools;
        protected Dictionary<EnumType, int> PoolIndices;
        protected Dictionary<EnumType, List<ObjectType>> ActiveObjects;

        protected List<PayloadType> Payloads;
        protected int PayloadIndex;

        public FExecute_ConstructObject ConstructObject;
        public FOnAddToPool OnAddToPool_Event;

        #endregion // Data Members

        public TCgManager_PooledObjects()
        {
            PoolSizes = new Dictionary<EnumType, int>(new FEnumTypeEqualityComparer());
            Pool = new List<ObjectType>();
            Pools = new Dictionary<EnumType, List<ObjectType>>(new FEnumTypeEqualityComparer());
            PoolIndices = new Dictionary<EnumType, int>(new FEnumTypeEqualityComparer());
            ActiveObjects = new Dictionary<EnumType, List<ObjectType>>(new FEnumTypeEqualityComparer());

            Payloads = new List<PayloadType>();

            ConstructObject = new FExecute_ConstructObject();
            ConstructObject.Bind(ConstructObject_Internal);

            OnAddToPool_Event = new FOnAddToPool();
        }

        public void Clear()
        {
            PoolSizes.Clear();

            int count = Pool.Count;

            for (int i = 0; i < count; ++i)
            {
                Pool[i].DeAllocate();
            }

            Pool.Clear();

            Pools.Clear();
            PoolIndices.Clear();
            ActiveObjects.Clear();
            Payloads.Clear();
        }

        public void Shutdown()
        {
            Clear();
        }

        public virtual ObjectType ConstructObject_Internal(EnumType e)
        {
            Type type                   = typeof(ObjectType);
            ConstructorInfo constructor = type.GetConstructor(Type.EmptyTypes);

            return (ObjectType)constructor.Invoke(Type.EmptyTypes);
        }

        public virtual void CreatePool(EnumType e, int size)
        {
            PoolSizes.Add(e, size);
            PoolIndices.Add(e, 0);

            List<ObjectType> pool = new List<ObjectType>();

            for (int i = 0; i < size; ++i)
            {
                ObjectType o = ConstructObject.Execute(e);
                o.Init(i, e);
                o.OnCreatePool();
                o.DeAllocate();
                Pool.Add(o);
                pool.Add(o);
                OnAddToPool_Event.Broadcast(e, o);
            }
            Pools.Add(e, pool);
        }

        public virtual void AddToPool(EnumType e, ObjectType o)
        {
            int size;

            if (PoolSizes.TryGetValue(e, out size))
            {
                PoolSizes[e] = size + 1;
            }
            else
            {
                PoolSizes.Add(e, 1);
            }

            int index;

            if (!PoolIndices.TryGetValue(e, out index))
            {
                PoolIndices.Add(e, 0);
            }

            Pool.Add(o);

            List<ObjectType> pool = null;

            if (Pools.TryGetValue(e, out pool))
            {
                Pools[e].Add(o);
            }
            else
            {
                pool = new List<ObjectType>();
                pool.Add(o);
                Pools.Add(e, pool);
            }

            o.Init(pool.Count - 1, e);
            o.Cache.Init(0, null, 0.0f, 0.0f, 0);
            OnAddToPool_Event.Broadcast(e, o);
        }

        public virtual void AddToActivePool(EnumType e, ObjectType o)
        {
            o.Cache.bAllocated = true;

            List<ObjectType> pool = null;

            if (ActiveObjects.TryGetValue(e, out pool))
            {
                ActiveObjects[e].Add(o);
            }
            else
            {
                pool = new List<ObjectType>();
                pool.Add(o);
                ActiveObjects.Add(e, pool);
            }
            //
        }

        public void OnUpdate(float deltaTime)
        {
            Dictionary<EnumType, List<ObjectType>>.KeyCollection keys = ActiveObjects.Keys;

            foreach (EnumType e in keys)
            {
                List<ObjectType> pool = ActiveObjects[e];
                int count             = pool.Count;
                int earliestIndex     = count;

                for (int j = count - 1; j >= 0; --j)
                {
                    ObjectType o = pool[j];

                    // Check if Object was DeAllocated NOT in a normal way
                    if (!o.Cache.bAllocated)
                    {
                        ActiveObjects[e].RemoveAt(j);

                        if (j < earliestIndex)
                            earliestIndex = j;
                        continue;
                    }

                    if (!o.Cache.bLifeTime)
                        continue;

                    //
                    {
                        o.DeAllocate();
                        ActiveObjects[e].RemoveAt(j);

                        if (j < earliestIndex)
                            earliestIndex = j;
                    }
                }

                // Update ActiveIndex
                if (earliestIndex != count)
                {
                    int max = pool.Count;

                    for (int j = earliestIndex; j < max; ++j)
                    {
                        ObjectType o        = pool[j];
                        o.Cache.ActiveIndex = j;
                    }
                }
            }
            //ActiveObjects.key
        }

        public int GetActivePoolSize(EnumType e)
        {
            List<ObjectType> pool = null;

            if (!ActiveObjects.TryGetValue(e, out pool))
                return EMPTY;
            return pool.Count;
        }

        public bool IsExhausted(EnumType e)
        {
            List<ObjectType> pool = null;

            if (!Pools.TryGetValue(e, out pool))
                return true;

            return GetActivePoolSize(e) >= pool.Count;
        }

        protected void LogTransaction()
        {
        }

        #region "Allocate / DeAllocate"

        protected ObjectType Allocate(EnumType e)
        {
            List<ObjectType> pool = null;

            Pools.TryGetValue(e, out pool);

            int size = EMPTY;

            PoolSizes.TryGetValue(e, out size);

            if (!PoolSizes.TryGetValue(e, out size))
            {
                FCgDebug.LogError(this.GetType().Name + ".Allocate: Pool: " + EnumTypeToString(e) + " is exhausted.");
                return null;
            }

            for (int i = 0; i < size; ++i)
            {
                int index      = PoolIndices[e];
                index          = (index + 1) % size;
                PoolIndices[e] = index;
                ObjectType o   = pool[index];

                if (!o.Cache.bAllocated)
                {
                    o.Cache.bAllocated = true;
                    return o;
                }
            }
            FCgDebug.LogError(this.GetType().Name + ".Allocate: Pool: " + EnumTypeToString(e) + " is exhausted.");
            return null;
        }

        public bool DeAllocate(EnumType e, int index)
        {
            List<ObjectType> pool = null;

            if (!ActiveObjects.TryGetValue(e, out pool))
            {
                FCgDebug.LogError(this.GetType().Name + ".DeAllocate: Object of Type: " + EnumTypeToString(e) + " at " + index + " is already deallocated.");
                return false;
            }

            int count = pool.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                ObjectType o = pool[i];

                // Update ActiveIndex
                if (i > FIRST)
                    --o.Cache.ActiveIndex;

                if (o.Cache.Index == index)
                {
                    LogTransaction();

                    o.DeAllocate();
                    ActiveObjects[e].RemoveAt(i);

                    // OnDeAllocate+Event
                    return true;
                }
            }

            // Correct on Cache "Miss"
            for (int i = 0; i < count; ++i)
            {
                ObjectType o        = pool[i];
                o.Cache.ActiveIndex = i;
            }

            FCgDebug.LogError(this.GetType().Name + ".DeAllocate: Object of Type: " + EnumTypeToString(e) + " at " + index + " is already deallocated.");
            return false;
        }

        public void DeAllocateAll()
        {
            Dictionary<EnumType, List<ObjectType>>.KeyCollection keys = ActiveObjects.Keys;

            foreach (EnumType e in keys)
            {
                List<ObjectType> pool = ActiveObjects[e];

                int count = pool.Count;

                for (int i = count - 1; i >= 0; --i)
                {
                    ObjectType o = pool[i];

                    LogTransaction();

                    o.DeAllocate();
                    ActiveObjects[e].RemoveAt(i);
                }
            }
        }

        #endregion // Allocate / DeAllocate

        #region "Payload"

        public PayloadType AllocatePayload()
        {
            int count = Payloads.Count;

            for (int i = 0; i < count; ++i)
            {
                int index           = (PayloadIndex + i) % count;
                PayloadType payload = Payloads[index];

                if (!payload.bAllocated)
                {
                    payload.bAllocated = true;
                    return payload;
                }
            }
            FCgDebug.LogError(this.GetType().Name + ".AllocatePayload: Pool is exhausted.");
            return default(PayloadType);
        }

        #endregion // Payload

        public ObjectType Spawn(EnumType e, PayloadType payload)
        {
            ObjectType o = Allocate(e);

            o.Allocate(GetActivePoolSize(e), payload);
            payload.Reset();
            AddToActivePool(e, o);
            return o;
        }

        protected string EnumTypeToString(EnumType e)
        {
            // Enum
            if (typeof(EnumType).IsEnum)
                return Enum.GetName(typeof(EnumType), e);
            // EnumClass
            else
            if (e is ICgEnum)
                return ((ICgEnum)e).GetName();
            return e.ToString();
        }
    }

    public class TCgManager_PooledMonoObjects<EnumType, ObjectType, PayloadType> : ICgManager
    where ObjectType : MCgPooledMonoObject
    where PayloadType : ICgPooledObjectPayload
    {
        protected sealed class FEnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        public sealed class FExecute_ConstructObject : TCgDelegate_Ret_OneParam<ObjectType, EnumType> { }
        public sealed class FOnAddToPool : TCgMulticastDelegate_TwoParams<EnumType, ObjectType> { }

        protected static int EMPTY = 0;
        protected static int FIRST = 0;

        private static TCgManager_PooledMonoObjects<EnumType, ObjectType, PayloadType> _Instance;
        public static TCgManager_PooledMonoObjects<EnumType, ObjectType, PayloadType> Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new TCgManager_PooledMonoObjects<EnumType, ObjectType, PayloadType>();
                }
                return _Instance;
            }
        }

        #region "Data Members

        protected Dictionary<EnumType, int> PoolSizes;
        protected List<ObjectType> Pool;
        protected Dictionary<EnumType, List<ObjectType>> Pools;
        protected Dictionary<EnumType, int> PoolIndices;
        protected Dictionary<EnumType, List<ObjectType>> ActiveObjects;

        protected List<PayloadType> Payloads;
        protected int PayloadIndex;

        public FExecute_ConstructObject ConstructObject;
        public FOnAddToPool OnAddToPool_Event;

        #endregion // Data Members

        public TCgManager_PooledMonoObjects()
        {
            PoolSizes = new Dictionary<EnumType, int>(new FEnumTypeEqualityComparer());
            Pool = new List<ObjectType>();
            Pools = new Dictionary<EnumType, List<ObjectType>>(new FEnumTypeEqualityComparer());
            PoolIndices = new Dictionary<EnumType, int>(new FEnumTypeEqualityComparer());
            ActiveObjects = new Dictionary<EnumType, List<ObjectType>>(new FEnumTypeEqualityComparer());

            Payloads = new List<PayloadType>();

            ConstructObject = new FExecute_ConstructObject();
            ConstructObject.Bind(ConstructObject_Internal);

            OnAddToPool_Event = new FOnAddToPool();
        }

        public void Clear()
        {
            PoolSizes.Clear();

            int count = Pool.Count;

            for (int i = 0; i < count; ++i)
            {
                Pool[i].DeAllocate();
            }

            Pool.Clear();

            Pools.Clear();
            PoolIndices.Clear();
            ActiveObjects.Clear();
            Payloads.Clear();
        }

        public void Shutdown()
        {
            int count = Pool.Count;

            for (int i = 0; i < count; ++i)
            {
                MonoBehaviour mb = (MonoBehaviour)(object)Pool[i];
                MonoBehaviour.Destroy(mb.gameObject);
            }
            Clear();
        }

        public virtual ObjectType ConstructObject_Internal(EnumType e)
        {
            Type type     = typeof(ObjectType);
            GameObject go = MonoBehaviour.Instantiate(FCgManager_Prefab.Get().EmptyGameObject);
            go.name       = type.ToString();
            return (ObjectType)(object)go.AddComponent(type);
        }

        public virtual void CreatePool(EnumType e, int size)
        {
            PoolSizes.Add(e, size);
            PoolIndices.Add(e, 0);

            List<ObjectType> pool = new List<ObjectType>();

            for (int i = 0; i < size; ++i)
            {
                ObjectType o = ConstructObject.Execute(e);
                o.Init(i, e);
                o.OnCreatePool();
                o.DeAllocate();
                Pool.Add(o);
                pool.Add(o);
                OnAddToPool_Event.Broadcast(e, o);
            }
            Pools.Add(e, pool);
        }

        public virtual void AddToPool(EnumType e, ObjectType o)
        {
            int size;

            if (PoolSizes.TryGetValue(e, out size))
            {
                PoolSizes[e] = size + 1;
            }
            else
            {
                PoolSizes.Add(e, 1);
            }

            int index;

            if (!PoolIndices.TryGetValue(e, out index))
            {
                PoolIndices.Add(e, 0);
            }

            Pool.Add(o);

            List<ObjectType> pool = null;

            if (Pools.TryGetValue(e, out pool))
            {
                Pools[e].Add(o);
            }
            else
            {
                pool = new List<ObjectType>();
                pool.Add(o);
                Pools.Add(e, pool);
            }

            o.Init(pool.Count - 1, e);
            o.GetCache().Init(0, null, 0.0f, 0.0f, 0);
            OnAddToPool_Event.Broadcast(e, o);
        }

        public virtual void AddToActivePool(EnumType e, ObjectType o)
        {
            o.GetCache().bAllocated = true;

            List<ObjectType> pool = null;

            if (ActiveObjects.TryGetValue(e, out pool))
            {
                ActiveObjects[e].Add(o);
            }
            else
            {
                pool = new List<ObjectType>();
                pool.Add(o);
                ActiveObjects.Add(e, pool);
            }
            //
        }

        public void OnUpdate(float deltaTime)
        {
            Dictionary<EnumType, List<ObjectType>>.KeyCollection keys = ActiveObjects.Keys;

            foreach (EnumType e in keys)
            {
                List<ObjectType> pool = ActiveObjects[e];
                int count = pool.Count;
                int earliestIndex = count;

                for (int j = count - 1; j >= 0; --j)
                {
                    ObjectType o = pool[j];

                    // Check if Object was DeAllocated NOT in a normal way
                    if (!o.GetCache().bAllocated)
                    {
                        ActiveObjects[e].RemoveAt(j);

                        if (j < earliestIndex)
                            earliestIndex = j;
                        continue;
                    }

                    if (!o.GetCache().bLifeTime)
                        continue;

                    //
                    {
                        o.DeAllocate();
                        ActiveObjects[e].RemoveAt(j);

                        if (j < earliestIndex)
                            earliestIndex = j;
                    }
                }

                // Update ActiveIndex
                if (earliestIndex != count)
                {
                    int max = pool.Count;

                    for (int j = earliestIndex; j < max; ++j)
                    {
                        ObjectType o = pool[j];
                        o.GetCache().ActiveIndex = j;
                    }
                }
            }
            //ActiveObjects.key
        }

        public int GetActivePoolSize(EnumType e)
        {
            List<ObjectType> pool = null;

            if (!ActiveObjects.TryGetValue(e, out pool))
                return EMPTY;
            return pool.Count;
        }

        public bool IsExhausted(EnumType e)
        {
            List<ObjectType> pool = null;

            if (!Pools.TryGetValue(e, out pool))
                return true;

            return GetActivePoolSize(e) >= pool.Count;
        }

        protected void LogTransaction()
        {
        }

        #region "Allocate / DeAllocate"

        protected ObjectType Allocate(EnumType e)
        {
            List<ObjectType> pool = null;

            Pools.TryGetValue(e, out pool);

            int size = EMPTY;

            PoolSizes.TryGetValue(e, out size);

            if (!PoolSizes.TryGetValue(e, out size))
            {
                FCgDebug.LogError(this.GetType().Name + ".Allocate: Pool: " + EnumTypeToString(e) + " is exhausted.");
                return null;
            }

            for (int i = 0; i < size; ++i)
            {
                int index = PoolIndices[e];
                index = (index + 1) % size;
                PoolIndices[e] = index;
                ObjectType o = pool[index];

                if (!o.GetCache().bAllocated)
                {
                    o.GetCache().bAllocated = true;
                    return o;
                }
            }
            FCgDebug.LogError(this.GetType().Name + ".Allocate: Pool: " + EnumTypeToString(e) + " is exhausted.");
            return null;
        }

        public bool DeAllocate(EnumType e, int index)
        {
            List<ObjectType> pool = null;

            if (!ActiveObjects.TryGetValue(e, out pool))
            {
                FCgDebug.LogError(this.GetType().Name + ".DeAllocate: Object of Type: " + EnumTypeToString(e) + " at " + index + " is already deallocated.");
                return false;
            }

            int count = pool.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                ObjectType o = pool[i];

                // Update ActiveIndex
                if (i > FIRST)
                    --o.GetCache().ActiveIndex;

                if (o.GetCache().Index == index)
                {
                    LogTransaction();

                    o.DeAllocate();
                    ActiveObjects[e].RemoveAt(i);

                    // OnDeAllocate+Event
                    return true;
                }
            }

            // Correct on Cache "Miss"
            for (int i = 0; i < count; ++i)
            {
                ObjectType o = pool[i];
                o.GetCache().ActiveIndex = i;
            }

            FCgDebug.LogError(this.GetType().Name + ".DeAllocate: Object of Type: " + EnumTypeToString(e) + " at " + index + " is already deallocated.");
            return false;
        }

        public void DeAllocateAll()
        {
            Dictionary<EnumType, List<ObjectType>>.KeyCollection keys = ActiveObjects.Keys;

            foreach (EnumType e in keys)
            {
                List<ObjectType> pool = ActiveObjects[e];

                int count = pool.Count;

                for (int i = count - 1; i >= 0; --i)
                {
                    ObjectType o = pool[i];

                    LogTransaction();

                    o.DeAllocate();
                    ActiveObjects[e].RemoveAt(i);
                }
            }
        }

        #endregion // Allocate / DeAllocate

        #region "Payload"

        public PayloadType AllocatePayload()
        {
            int count = Payloads.Count;

            for (int i = 0; i < count; ++i)
            {
                int index = (PayloadIndex + i) % count;
                PayloadType payload = Payloads[index];

                if (!payload.bAllocated)
                {
                    payload.bAllocated = true;
                    return payload;
                }
            }
            FCgDebug.LogError(this.GetType().Name + ".AllocatePayload: Pool is exhausted.");
            return default(PayloadType);
        }

        #endregion // Payload

        public ObjectType Spawn(EnumType e, PayloadType payload)
        {
            ObjectType o = Allocate(e);

            o.Allocate(GetActivePoolSize(e), payload);
            payload.Reset();
            AddToActivePool(e, o);
            return o;
        }

        protected string EnumTypeToString(EnumType e)
        {
            // Enum
            if (typeof(EnumType).IsEnum)
                return Enum.GetName(typeof(EnumType), e);
            // EnumClass
            else
            if (e is ICgEnum)
                return ((ICgEnum)e).GetName();
            return e.ToString();
        }
    }
}