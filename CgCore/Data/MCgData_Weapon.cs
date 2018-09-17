namespace CgCore
{
    using System.Collections.Generic;

    using UnityEngine;

    public class MCgData_Weapon : MCgData
    {
        #region "Stats"

        public virtual string GetItemShortCode() { return ECgCached.Str.NAME_None; }
        public virtual bool UseInventory() { return false; }

        #endregion // Stats

        #region "Mesh"

        public bool UseMesh() { return false; }

        public virtual Mesh GetMesh(ECgViewType viewType, bool isLow = false) { return null; }
        public virtual Mesh GetMesh() { return null; }

        public virtual void SetMesh(SkinnedMeshRenderer meshRenderer, ECgViewType viewType, bool isLow = false) { }
        public virtual void SetMesh(MeshRenderer meshRenderer, ECgViewType viewType, bool isLow = false) { }
        public virtual void SetMesh(Transform transform, ECgViewType viewType, bool isLow = false) { }

        public virtual void SetMesh(SkinnedMeshRenderer meshRenderer) { }
        public virtual void SetMesh(MeshRenderer meshRenderer) { }
        public virtual void SetMesh(Transform transform) { }

        public virtual void GetDefaultMaterials(ref List<Material> outMaterials, ECgViewType viewType, bool isLow = false) { }
        public virtual void GetDefaultMaterials(ref List<Material> outMaterials) { }

        #endregion // Mesh

        #region "Anims"

        // public virtual void SetAnimBlueprint()

        #endregion // Anims
    }
}