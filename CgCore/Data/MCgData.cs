namespace CgCore
{
    using System;

    using UnityEngine;

    public abstract class MCgData : MonoBehaviour
    {
        [SerializeField]
        public S_FECgAssetType S_AssetType;
        [NonSerialized]    
        public FECgAssetType AssetType;

        [SerializeField]
        public string ShortCode;

        public virtual void Init() { }
    }
}