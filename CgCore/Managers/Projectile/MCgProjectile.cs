namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public sealed class FCgProjectileCache : TCgPooledMonoObjectCache<FECgProjectileType, MCgProjectile, FCgProjectilePayload>
    {
        #region "Data Members"

        public MCgData_Projectile Data;

        public ECgProjectileRelevance Relevance;

        public ECgProjectileMovement Movement;

        public Vector3 Position;
        public Vector3 Direction;
        public Vector3 Rotation;
        public FCgTransform _Transform;
        public float ChargePercent;
        public float Speed;
        public float DrawDistanceSq;

        #endregion // Data Members

        public FCgProjectileCache() : base() { }

        public override void Init(FCgProjectilePayload payload, float time, float realTime, ulong frame)
        {
            base.Init(payload, time, realTime, frame);

            Relevance = payload.Relevance;
            Data = payload.Data;

            Position = payload.Position;
            Direction = payload.Direction;
            Rotation = FCgMath.VectorToEuler(Direction);
            _Transform.Position = Position;
            _Transform.Rotation = Quaternion.Euler(Rotation);

            ChargePercent = payload.ChargePercent;
            Speed = Data.GetInitialSpeed() + payload.AdditionalSpeed;
        }

        public override void Reset()
        {
            base.Reset();

            Data = null;
            Relevance = ECgProjectileRelevance.MAX;
            Movement = ECgProjectileMovement.MAX;
            ElapsedTime = 0.0f;
            Position = Vector3.zero;
            Direction = Vector3.zero;
            Rotation = Vector3.zero;
            _Transform = FCgTransform.Identity;
            ChargePercent = 0.0f;
            Speed = 0.0f;
            DrawDistanceSq = 0.0f;
        }
    }

    public class MCgProjectile : MCgPooledMonoObject, ICgObject
    {
        #region "Constants"

        public static readonly Vector3 GRAVITY = new Vector3(0.0f, -9.80655f, 0.0f);

        #endregion // Constants

        #region "Data Members"

        public FCgProjectileCache Cache;

            #region "Renderer"

        public bool bMeshComponent;
        public MCgMeshComponent MeshComponent;

        public bool bSkinnedMeshComponent;
        public MCgSkinnedMeshComponent SkinnedMeshComponent;

            #endregion // Renderer

            #region "Collision"

        public bool bCollider;
        public ECgCollisionShape ColliderShape;

        public Collider MyCollider;

        public bool bRigidbody;
        public Rigidbody MyRigidbody;

        public List<Component> IgnoreComponents;
        public List<GameObject> IgnoreGameObjects;

            #endregion // Collision

            #region "Movement"

        public float InitialSpeed;
        public float MaxSpeed;
        public float GravityMultiplier;
        public float ForwardAcceleration;
        public Vector3 Velocity;

            #endregion // Movement

        #endregion // Data Members

        #region "Interface"

        protected override ICgPooledObjectCache GetCache_Internal()
        {
            return Cache;
        }

        public override void Init(int index, object e)
        {
            Cache = new FCgProjectileCache();

            base.Init(index, e);

            ColliderShape = ECgCollisionShape.MAX;
        }

        public override void OnCreatePool()
        {
            if (bMeshComponent)
                MeshComponent = gameObject.AddComponent<MCgMeshComponent>();

            if (bSkinnedMeshComponent)
                SkinnedMeshComponent = gameObject.AddComponent<MCgSkinnedMeshComponent>();

            if (bCollider)
            {
                // Box
                if (ColliderShape == ECgCollisionShape.Box)
                    MyCollider = gameObject.AddComponent<BoxCollider>();
                // Sphere
                else
                if (ColliderShape == ECgCollisionShape.Sphere)
                    MyCollider = gameObject.AddComponent<SphereCollider>();
                // Capsule
                else
                if (ColliderShape == ECgCollisionShape.Capsule)
                    MyCollider = gameObject.AddComponent<CapsuleCollider>();

                MyCollider.enabled = false;

                if (bRigidbody)
                    MyRigidbody = gameObject.AddComponent<Rigidbody>();
            }
        }

        public override void DeAllocate()
        {
            base.DeAllocate();

            if (bCollider)
                MyCollider.enabled = false;
        }

        #endregion // Interface

        #region "Collision"

        void OnCollisionEnter(Collision collision)
        {
            OnCollision_Enter(collision);
        }

        public virtual void OnCollision_Enter(Collision collision)
        {

        }

        #endregion // Collision
     }
}
