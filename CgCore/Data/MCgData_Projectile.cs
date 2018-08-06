namespace CgCore
{
    using UnityEngine;

    public class MCgData_Projectile : MCgData
    {
        public virtual FECgProjectileType GetProjectileType()
        {
            return EMCgProjectileType.Get().GetMAX();
        }

        #region "Stats"

        public virtual string GetItemShortCode() { return ""; }

        public virtual bool GetOnAllocateDropItem() { return false; }

        public virtual bool GetOnAllocateConsumeItem() { return false; }

        public virtual float GetLifeTime() { return 0.0f; }

        public virtual float GetMaxRange() { return 0.0f; }

        #endregion // Stats

        #region "Movement"

        public virtual Vector3 EvaluateMovementFunction(float time, Vector3 location, Transform transform)
        {
            return Vector3.zero;
        }

        public virtual float GetInitialSpeed()
        {
            return 0.0f;
        }

        public virtual float GetMaxSpeed()
        {
            return 0.0f;
        }

        public virtual float GetGravityMultiplier()
        {
            return 0.0f;
        }

        #endregion // Movement

        #region "Damage"

        public virtual int GetDamage()
        {
            return 0;
        }

        public virtual bool CanDamageFalloff()
        {
            return false;
        }

        public virtual float GetDamageFalloff(float distance)
        {
            return 0.0f;
        }

        public virtual bool CanDamageRadial()
        {
            return false;
        }

        public virtual float GetDamageRadial(Vector3 origin, Vector3 location)
        {
            return 0.0f;
        }

        #endregion // Damage

        #region "Mesh"

        public virtual Mesh GetMesh(ECgViewType viewType)
        {
            return null;
        }

        public virtual float GetDrawDistance(ECgViewType viewType)
        {
            return 0.0f;
        }

        public virtual float GetDrawDistanceSq(ECgViewType viewType)
        {
            return 0.0f;
        }

        #endregion // Mesh

        #region "Transform"

        public virtual Transform GetTransform()
        {
            return null;
        }

        #endregion // Transform

        #region "Collision"

        public virtual float GetSphereRadius()
        {
            return 0.0f;
        }

        #endregion // Collision

        #region "FX"
        
        public virtual bool GetUseTrailFX()
        {
            return false;
        }

        #endregion // FX
    }
}
