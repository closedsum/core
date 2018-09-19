namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgFpsPawn : MCgPlayerPawn
    {
        #region "Data Members"

        public Transform Eye;

        public SkinnedMeshRenderer Mesh1P;

            #region "Camera"

        public float EyeHeight;

        #endregion // Camera

        #endregion // Data Members

        #region "Camera"

        public virtual Vector3 GetPawnViewLocation()
        {
            return Vector3.zero;
        }

        public virtual Vector3 GetFeetLocation()
        {
            return Vector3.zero;
        }

        #endregion // Camera

        #region "Mesh"

        public virtual SkinnedMeshRenderer GetCurrentMesh()
        {
            return null;
        }

        #endregion // Mesh

        #region "Weapons"

        public virtual void ApplyData_Weapon()
        {

        }

        #endregion // Weapons
    }
}