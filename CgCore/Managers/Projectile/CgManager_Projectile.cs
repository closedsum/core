namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManager_Projectile : TCgManager_PooledMonoObjects_Map<FECgProjectileType, MCgProjectile, FCgProjectilePayload, FCgProjectileCache>
    {
        private static readonly int PAYLOAD_COUNT = 8;

        public FCgManager_Projectile() : base()
        {
            for (int i = 0; i < PAYLOAD_COUNT; ++i)
            {
                Payloads.Add(new FCgProjectilePayload());
            }
        }
    }

    public class ICgManager_Projectile : MonoBehaviour
    {
        #region "Data Members"

        private static ICgManager_Projectile _Instance;

        protected FCgManager_Projectile Internal;

        public Dictionary<FECgProjectileType, Type> TypeMap;

        #endregion // Data Members

        public ICgManager_Projectile()
        {
            TypeMap = new Dictionary<FECgProjectileType, Type>(new FECgProjectileTypeEqualityComparer());
        }

        public static ICgManager_Projectile Get()
        {
            return _Instance;
        }

        public static T Get<T>()
            where T : ICgManager_Projectile
        {
            return (T)_Instance;
        }

        public static void Init(Type type)
        {
            if (_Instance != null)
                return;

            if (!type.IsSubclassOf(typeof(TCgManager_PooledMonoObjects_Map<FECgProjectileType, MCgProjectile, FCgProjectilePayload, FCgProjectileCache>)))
            {
                FCgDebug.Log("ICgManager_Projectile.Init: Passed in Type of " + type.GetType().Name + " is NOT a SubclassOf TCgManager_PooledMonoObjects_Map<FECgProjectileType, MCgProjectile, FCgProjectilePayload, FCgProjectileCache>");
                return;
            }

            GameObject go = MonoBehaviour.Instantiate(FCgManager_Prefab.Get().EmptyGameObject);
            _Instance     = go.AddComponent<ICgManager_Projectile>();
            go.name       = "ICgManager_Projectile";

            _Instance.Internal = (FCgManager_Projectile)type.GetConstructor(Type.EmptyTypes).Invoke(Type.EmptyTypes);
            _Instance.Internal.OnAddToPool_Event.Add(_Instance.OnAddToPool);
            _Instance.Internal.ConstructObject.Unbind();
            _Instance.Internal.ConstructObject.Bind(_Instance.ConstructObject);
        }

        #region "Internal"

        public virtual void Clear()
        {
            Internal.Clear();
        }

        public static void Shutdown()
        {
            if (_Instance != null)
                _Instance.Internal.Shutdown();
        }

        public virtual MCgProjectile ConstructObject(FECgProjectileType type)
        {
            GameObject go   = MonoBehaviour.Instantiate(FCgManager_Prefab.Get().EmptyGameObject);
            go.name         = type.Name;
            MCgProjectile o = (MCgProjectile)go.AddComponent(TypeMap[type]);

            return o;
        }

        public virtual void CreatePool(FECgProjectileType e, int size)
        {
            Internal.CreatePool(e, size);
        }

        public virtual void AddToPool(FECgProjectileType e, MCgProjectile o)
        {
            Internal.AddToPool(e, o);
        }

        public virtual void AddToActivePool(FECgProjectileType e, MCgProjectile o)
        {
            Internal.AddToActivePool(e, o);
        }

        public void OnUpdate(float deltaTime)
        {
            Internal.OnUpdate(deltaTime);
        }

        public int GetActivePoolSize(FECgProjectileType e)
        {
            return Internal.GetActivePoolSize(e);
        }

        public bool IsExhausted(FECgProjectileType e)
        {
            return Internal.IsExhausted(e);
        }

            #region "Allocate / DeAllocate"

        public bool DeAllocate(FECgProjectileType e, int index)
        {
            return Internal.DeAllocate(e, index);
        }

        public bool DeAllocate(MCgProjectile o)
        {
            return Internal.DeAllocate(o);
        }

        public void DeAllocateAll()
        {
            Internal.DeAllocateAll();
        }

            #endregion // Allocate / DeAllocate

        public FCgProjectilePayload AllocatePayload()
        {
            return Internal.AllocatePayload();
        }

        public MCgProjectile Fire(FECgProjectileType projectileType, FCgProjectilePayload payload)
        {
            return null;
        }

        #endregion // Internal

        public void OnAddToPool(FECgProjectileType e, MCgProjectile o)
        {
            o.transform.parent = transform;
        }
    }
}
