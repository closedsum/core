namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class TCgPooledMonoObjectCache<EnumType, ObjectType> : ICgPooledObjectCache
        where ObjectType : MCgPooledMonoObject
    {
        public class FOnDeAllocate : TCgMulticastDelegate_ThreeParams<int, int, EnumType> { }

        #region "Data Members"

            #region "Interface"

        private int _Index;
        public int Index
        {
            get { return _Index; }
            set { _Index = value; }
        }
        private int _ActiveIndex;
        public int ActiveIndex
        {
            get { return _ActiveIndex; }
            set { _ActiveIndex = value; }
        }
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

        private float _WarmUpTime;
        public float WarmUpTime
        {
            get { return _WarmUpTime; }
            set { _WarmUpTime = value; }
        }
        private bool _bLifeTime;
        public bool bLifeTime
        {
            get { return _bLifeTime; }
            set { _bLifeTime = value; }
        }
        private float _LifeTime;
        public float LifeTime
        {
            get { return _LifeTime; }
            set { _LifeTime = value; }
        }
        private float _Time;
        public float Time
        {
            get { return _Time; }
            set { _Time = value; }
        }
        private float _RealTime;
        public float RealTime
        {
            get { return _RealTime; }
            set { _RealTime = value; }
        }
        private ulong _Frame;
        public ulong Frame
        {
            get { return _Frame; }
            set { _Frame = value; }
        }
        private float _ElapsedTime;
        public float ElapsedTime
        {
            get { return _ElapsedTime; }
            set { _ElapsedTime = value; }
        }

            #endregion // Interface

        public ObjectType PooledObject;

        public EnumType Type;

        public FOnDeAllocate OnDeAllocate_Event;

        #endregion // Data Members

        public TCgPooledMonoObjectCache()
        {
            OnDeAllocate_Event = new FOnDeAllocate();
        }

        public void Set(int index, object o)
        {
            Index = index;
            PooledObject = (ObjectType)o;
        }

        public void SetType(object e)
        {
            Type = (EnumType)e;
        }

        public virtual void Init(int activeIndex, ICgPooledObjectPayload payload, float time, float realTime, ulong frame)
        {
            ActiveIndex = activeIndex;
            Instigator = payload.Instigator;
            Owner = payload.Owner;
            Parent = payload.Parent;

            Time = time;
            RealTime = realTime;
            Frame = frame;
        }

        public virtual void Reset()
        {
            ActiveIndex = 0;
            bAllocated = false;
            //Type =
            OnDeAllocate_Event.Clear();

            Instigator = null;
            Owner = null;
            Parent = null;
            WarmUpTime = 0.0f;
            bLifeTime = false;
            LifeTime = 0.0f;
            Time = 0.0f;
            RealTime = 0.0f;
            Frame = 0;
            ElapsedTime = 0.0f;
        }

        public virtual void DeAllocate()
        {
            Reset();
        }
    }

    public class MCgPooledMonoObject : MonoBehaviour
    {
        public ICgPooledObjectCache GetCache()
        {
            return GetCache_Internal();
        }

        public T GetCache<T>() 
            where T : ICgPooledObjectCache
        {
            return (T)GetCache();
        }

        public CacheType GetCache<CacheType, EnumType, ObjectType>()
            where CacheType : TCgPooledMonoObjectCache<EnumType, ObjectType>
            where ObjectType : MCgPooledMonoObject
        {
            return (CacheType)GetCache();
        }

        protected virtual ICgPooledObjectCache GetCache_Internal()
        {
            return null;
        }

        public virtual void Init(int index, object e)
        {
            GetCache().Set(index, this);
            GetCache().SetType(e);
        }

        public virtual void OnCreatePool()
        {

        }

        public virtual void Allocate(int activeIndex, ICgPooledObjectPayload payload)
        {
            GetCache().Init(activeIndex, payload, 0.0f, 0.0f, 0);
            gameObject.SetActive(true);
            gameObject.transform.parent = null;
        }

        public virtual void DeAllocate()
        {
            gameObject.SetActive(false);

            GetCache().Reset();
        }
    }
}
