namespace CgCore
{
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
    }
}
