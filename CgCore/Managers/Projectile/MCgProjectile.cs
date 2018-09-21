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
        public Quaternion Rotation;
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

            Position = payload.Position;
            Direction = payload.Direction;
            //Rotation = Direction.

            ChargePercent = payload.ChargePercent;
            Speed = Data.GetInitialSpeed() + payload.AdditionalSpeed;
        }

        public override void Reset()
        {
            base.Reset();
        }
    }

    public class MCgProjectile : MCgPooledMonoObject, ICgObject
    {
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

        public Rigidbody MyRigidBody;

        public List<Component> IgnoreComponents;
        public List<GameObject> IgnoreGameObjects;

            #endregion // Collision

            #region "Movement"

        public float InitialSpeed;
        public float MaxSpeed;
        public float GravityScale;
        public float AccelerationXY;
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

                MyRigidBody = gameObject.AddComponent<Rigidbody>();
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
            OnCollision(ECgColliderState.Enter, collision);
        }

        public virtual void OnCollision(ECgColliderState state, Collision collision)
        {

        }

        #endregion // Collision
     }
}
