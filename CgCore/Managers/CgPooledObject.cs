namespace CgCore
{
    using System;

    public interface ICgPooledObjectCache
    {
        #region "Data Members"

        int Index { get; set; }
        int ActiveIndex { get; set; }
        bool IsAllocated { get; set; }

        object Instigator { get; set; }
        object Owner { get; set; }
        object Parent { get; set; }

        float WarmUpTime { get; set; }
        bool bLifeTime { get; set; }
        float LifeTime { get; set; }
        float Time { get; set; }
        float RealTime { get; set; }
        ulong Frame { get; set; }
        float ElapsedTime { get; set; }

        #endregion // Data Members

        void Reset();
        void DeAllocate();
    }

    public class CgPooledObjectCache<EnumType, ObjectType> : ICgPooledObjectCache
        where ObjectType : ICgPooledObject
    {
        public class OnDeAllocate : TCgMulticastDelegate_ThreeParams<int, int, EnumType> { }

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
        private bool _IsAllocated;
        public bool IsAllocated
        {
            get { return _IsAllocated; }
            set { _IsAllocated = value; }
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

        public OnDeAllocate OnDeAllocate_Event;

        #endregion // Data Members

        public CgPooledObjectCache()
        {
            OnDeAllocate_Event = new OnDeAllocate();
        }
        
        public void Set(int index, ObjectType o)
        {
            Index        = index;
            PooledObject = o;
        }

        public virtual void Init(int activeIndex, ICgPooledObjectPayload payload, float time, float realTime, ulong frame, OnDeAllocate.Event e = null)
        {
            ActiveIndex = activeIndex;
            Instigator = payload.Instigator;
            Owner = payload.Owner;
            Parent = payload.Parent;

            Time = time;
            RealTime = realTime;
            Frame = frame;

            if (e != null)
                OnDeAllocate_Event.Add(e);
        }

        public virtual void Reset()
        {
            ActiveIndex = 0;
            IsAllocated = false;
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

    public interface ICgPooledObject
    {
        void OnCreatePool();
        void Allocate(int activeIndex, ICgPooledObjectPayload payload);
        void DeAllocate();
    }

    public abstract class TCgPooledObject<EnumType> : ICgPooledObject
    {
        public CgPooledObjectCache<EnumType, TCgPooledObject<EnumType>> Cache;

        public TCgPooledObject()
        {
            // Create Cache in Child Class
            //Cache = new CgPooledObjectCache<EnumType, TCgPooledObject<EnumType>>();
        }

        #region "Interface"

        public virtual void OnCreatePool()
        {

        }

        public virtual void Allocate(int activeIndex, ICgPooledObjectPayload payload)
        {
            Cache.Init(activeIndex, payload, 0.0f, 0.0f, 0, null);
        }

        public virtual void DeAllocate()
        {
            Cache.Reset();
        }

        #endregion // Interface

        public virtual void Init(int index, EnumType e)
        {
            Cache.Set(index, this);
            Cache.Type = e;
        }
    }
}
