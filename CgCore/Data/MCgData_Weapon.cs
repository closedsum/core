namespace CgCore
{
    using UnityEngine;

    public class MCgData_Weapon : MCgData
    {
        #region "Stats"

        string ItemShortCode;

        public virtual string GetItemShortCode() { return ECgCached.Str.NAME_None; }
        public virtual bool UseInventory() { return false; }

        #endregion // Stats

        #region "Mesh"

        public virtual Mesh GetMesh(ECgViewType viewType, bool isLow = false) { return null; }
        public virtual Mesh GetMesh() { return null; }

        //public virtual void SetMesh()

        //public virtual void GetDefaultMaterials()

        #endregion // Mesh

        #region "Anims"

        // public virtual void SetAnimBlueprint()

        #endregion // Anims
    }
}