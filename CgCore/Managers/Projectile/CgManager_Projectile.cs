namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class ICgManager_Projectile
    {
        #region "Data Members"

        private static ICgManager_Projectile _Instance;
        public static ICgManager_Projectile Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new ICgManager_Projectile();
                }
                return _Instance;
            }
        }

        #endregion // Data Members

        public ICgManager_Projectile() { }

        public static ICgManager_Projectile Get()
        {
            return Instance;
        }

        public FCgProjectilePayload AllocatePayload()
        {
            return null;// Internal.AllocatePayload();
        }

        public MCgProjectile Fire(FECgProjectileType projectileType, FCgProjectilePayload payload)
        {
            return null;
        }
    }
}
