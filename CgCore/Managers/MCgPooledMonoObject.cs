﻿namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class TCgPooledMonoObjectCache<EnumType, ObjectType, PayloadType> : ICgPooledObjectCache<EnumType, ObjectType, PayloadType>
        where ObjectType : MCgPooledMonoObject
        where PayloadType : ICgPooledObjectPayload
    {
        public class FOnDeAllocate : TCgMulticastDelegate_ThreeParams<int, int, EnumType> { }

        #region "Constants"

        public static readonly int INDEX_NONE = -1;

        #endregion // Constants

        #region "Data Members"

        #region "Interface"

        private int _Index;
        public int Index
        {
            get { return _Index; }
            set { _Index = value; }
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

        public EnumType MyType;

        public FOnDeAllocate OnDeAllocate_Event;

        #endregion // Data Members

        public TCgPooledMonoObjectCache()
        {
            Index = INDEX_NONE;

            OnDeAllocate_Event = new FOnDeAllocate();
        }

        public void Set(int index, ObjectType o)
        {
            Index = index;
            PooledObject = o;
        }

        public void SetMyType(EnumType e)
        {
            MyType = e;
        }

        public EnumType GetMyType()
        {
            return MyType;
        }
        
        public virtual void Init(PayloadType payload, float time, float realTime, ulong frame)
        {
            Instigator = payload.Instigator;
            Owner = payload.Owner;
            Parent = payload.Parent;

            Time = time;
            RealTime = realTime;
            Frame = frame;
        }

        public virtual void Reset()
        {
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

    public class MCgPooledMonoObject : MonoBehaviour, ICgObject
    {
        #region "Data Members"

            #region "Interface"

        private ulong _UniqueObjectId;
        public ulong UniqueObjectId
        {
            get { return _UniqueObjectId; }
            set { _UniqueObjectId = value; }
        }

            #endregion // Interface

        #endregion // Data Members

        public virtual CacheType GetCache<EnumType, ObjectType, PayloadType, CacheType>()
            where ObjectType : MCgPooledMonoObject
            where PayloadType : ICgPooledObjectPayload
            where CacheType : TCgPooledMonoObjectCache<EnumType, ObjectType, PayloadType>
        {
            return null;
        }

        public virtual void Init<EnumType, ObjectType, PayloadType, CacheType>(int index, EnumType e)
            where ObjectType : MCgPooledMonoObject
            where PayloadType : ICgPooledObjectPayload
            where CacheType : TCgPooledMonoObjectCache<EnumType, ObjectType, PayloadType>
        {
            MCgGameInstance.Get().RegisterUniqueObject(this);

            GetCache<EnumType, ObjectType, PayloadType, CacheType>().Set(index, (ObjectType)this);
            GetCache<EnumType, ObjectType, PayloadType, CacheType>().SetMyType(e);
        }

        public virtual void OnCreatePool() { }

        public virtual void OnUpdate(float deltaTime) { }

        public virtual void Allocate<EnumType, ObjectType, PayloadType, CacheType>(PayloadType payload)
            where ObjectType : MCgPooledMonoObject
            where PayloadType : ICgPooledObjectPayload
            where CacheType : TCgPooledMonoObjectCache<EnumType, ObjectType, PayloadType>
        {
            GetCache<EnumType, ObjectType, PayloadType, CacheType>().Init(payload, 0.0f, 0.0f, 0);
            gameObject.SetActive(true);
            gameObject.transform.parent = null;
        }

        public virtual void DeAllocate<EnumType, ObjectType, PayloadType, CacheType>()
            where ObjectType : MCgPooledMonoObject
            where PayloadType : ICgPooledObjectPayload
            where CacheType : TCgPooledMonoObjectCache<EnumType, ObjectType, PayloadType>
        {
            gameObject.SetActive(false);

            GetCache<EnumType, ObjectType, PayloadType, CacheType>().Reset();
        }
    }
}
