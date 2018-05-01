namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public interface ICgPooledObjectPayload
    {
        bool IsAllocated { get; set; }

        void Reset();
    }

    public abstract class CgPooledObjectPayload
    {
        private bool _IsAllocated;
        public bool IsAllocated
        {
            get { return _IsAllocated; }
            set { _IsAllocated = value; }
        }

        public abstract void Reset();
    }

    public interface ICgManager
    {

    }

    public class TCgManager<EnumType, ObjectType> : ICgManager 
        where ObjectType : TCgPooledObject<EnumType>
    {
        protected sealed class EnumTypeEqualityComparer : IEqualityComparer<EnumType>
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

        protected static int EMPTY = 0;
        protected static int FIRST = 0;

        private static TCgManager<EnumType, ObjectType> _Instance;
        public static TCgManager<EnumType, ObjectType> Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new TCgManager<EnumType, ObjectType>();
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

        protected List<ICgPooledObjectPayload> Payloads;
        protected int PayloadIndex;

        #endregion // Data Members

        public TCgManager()
        {
            PoolSizes = new Dictionary<EnumType, int>(new EnumTypeEqualityComparer());
            Pool = new List<ObjectType>();
            Pools = new Dictionary<EnumType, List<ObjectType>>(new EnumTypeEqualityComparer());
            PoolIndices = new Dictionary<EnumType, int>(new EnumTypeEqualityComparer());
            ActiveObjects = new Dictionary<EnumType, List<ObjectType>>(new EnumTypeEqualityComparer());

            Payloads = new List<ICgPooledObjectPayload>();
        }

        public void Clear()
        {
            PoolSizes.Clear();
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
                // Check for Unity GameObjects
            }
        }

        public virtual void CreatePool(EnumType e, int size)
        {
            PoolSizes.Add(e, size);
            PoolIndices.Add(e, 0);

            List<ObjectType> pool = new List<ObjectType>();

            for (int i = 0; i < size; ++i)
            {
                // Spawn Unity Object

                ObjectType o = Activator.CreateInstance<ObjectType>();
                o.Init(i, e);
                o.DeAllocate();
                Pool.Add(o);
                pool.Add(o);
            }
            Pools.Add(e, pool);
        }

        public virtual void AddToPool(ObjectType o, EnumType e)
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
            o.Cache.Init(0, null, 0.0f, 0.0f, 0, null, null, null);
        }

        public virtual void AddToActivePool(ObjectType o, EnumType e)
        {
            o.Cache.IsAllocated = true;

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
                    if (!o.Cache.IsAllocated)
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
                Debug.LogError("CsManager.Allocate: Pool: " + e.ToString() + " is exhausted.");
                return null;
            }

            for (int i = 0; i < size; ++i)
            {
                int index    = PoolIndices[e];
                index        = (index + 1) % size;
                ObjectType o = pool[index];

                if (!o.Cache.IsAllocated)
                {
                    o.Cache.IsAllocated = true;
                    return o;
                }
            }
            Debug.LogError("CsManager.Allocate: Pool: " + e.ToString() + " is exhausted.");
            return null;
        }

        public bool DeAllocate(EnumType e, int index)
        {
            List<ObjectType> pool = null;

            if (!ActiveObjects.TryGetValue(e, out pool))
            {
                Debug.LogError("CgManager.DeAllocate: Object of Type: " + e.ToString() + " at " + index + " is already deallocated.");
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
            Debug.LogError("CgManager.DeAllocate: Object of Type: " + e.ToString() + " at " + index + " is already deallocated.");
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

        public ICgPooledObjectPayload AllocatePayload()
        {
            int count = Payloads.Count;

            for (int i = 0; i < count; ++i)
            {
                int index = (PayloadIndex + i) % count;
                ICgPooledObjectPayload payload = Payloads[index];

                if (!payload.IsAllocated)
                {
                    payload.IsAllocated = true;
                    return payload;
                }
            }
            Debug.LogError("CgManager.AllocatePayload: Pool is exhausted");
            return null;
        }

        #endregion // Payload
    }
}