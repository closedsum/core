// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using UnityEngine;

    public static class CgTypes
    {
        public static readonly int INDEX_NONE = -1;
        public static readonly int FIRST = 0;
    }

    public interface ICgAssetRef
    {
        string Path { get; set; }

        string GetFullPath();
        void SetAsset(object asset);
        void Load();
    }

    public abstract class CgAssetRef
    {
        private string _Path;
        public string Path
        {
            get { return _Path; }
            set { _Path = value; }
        }

        public abstract string GetFullPath();
        public abstract void SetAsset(object asset);
        public abstract void Load();
    }

    public class TCgAssetRef<AssetClass> : CgAssetRef
        where AssetClass : MonoBehaviour
    {
        private AssetClass Asset;

        public TCgAssetRef()
        {
        }

        public AssetClass Get() { return Asset; }

        public override string GetFullPath()
        {
            return Application.dataPath + "/" + Path;
        }

        public override void SetAsset(object asset)
        {
            Asset = (AssetClass)asset;
        }

        public override void Load()
        {
            Asset = (AssetClass)Resources.Load(GetFullPath());
        }
    }
}