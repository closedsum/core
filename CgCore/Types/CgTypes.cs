// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;

    using UnityEngine;
#if UNITY_EDITOR
    using UnityEditor;
#endif // #if UNITY_EDITOR

    public static class CgTypes
    {
        public static readonly int INDEX_NONE = -1;
        public static readonly int FIRST = 0;
    }

    namespace ECgCached
    {
        public static class Str
        {
            public static readonly string NAME_None = "";
        }
    }

    public interface ICgAssetRef
    {
        string Path { get; set; }

        string GetFullPath();
        void SetAsset(object asset);
        void Load();
    }

    public abstract class FCgAssetRef
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

    public class TCgAssetRef<AssetClass> : FCgAssetRef
        where AssetClass : UnityEngine.Object
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
#if UNITY_EDITOR
            Path = AssetDatabase.GetAssetPath(Asset);
#endif // UNITY_EDITOR
        }

        public void SetAsset(AssetClass asset)
        {
            Asset = asset;
#if UNITY_EDITOR
            Path = AssetDatabase.GetAssetPath(Asset);
#endif // UNITY_EDITOR
        }

        public override void Load()
        {
            Asset = (AssetClass)Resources.Load(GetFullPath());
        }
    }

    [Serializable]
    public struct S_FCgAssetRef_Mesh
    {
        [SerializeField]
        public string Path;
    }

    [Serializable]
    public struct S_FCgMesh
    {
        [SerializeField]
        public S_FCgAssetRef_Mesh _Mesh;
        [SerializeField]
        public int _Mesh_LoadFlags;
    }

    public class FCgMesh
    {
        #region "Data Members"

        public TCgAssetRef<Mesh> _Mesh;

        public int _Mesh_LoadFlags;

        private Mesh _Mesh_Internal;

        #endregion // Data Members

        public FCgMesh()
        {
            _Mesh = new TCgAssetRef<Mesh>();
        }

        public Mesh Get()
        {
            return _Mesh_Internal;
        }

        // TODO: HACK: used to temporarily stop warnings
        public void TempAssign()
        {
            _Mesh_Internal = _Mesh.Get();
        }
    }

    #region "Materials"

    [Serializable]
    public struct S_FCgAssetRef_Materials
    {
        [SerializeField]
        public List<string> Paths;
    }

    [Serializable]
    public struct S_FCgListMaterial
    {
        [SerializeField]
        public S_FCgAssetRef_Materials Materials;
        [SerializeField]
        public int Materials_LoadFlags;
    }

    public class FCgListMaterial
    {
        #region "Data Members"

        public List<TCgAssetRef<Material>> Materials;

        public int Materials_LoadFlags;

        private List<Material> Materials_Internal;

        #endregion // Data Members

        public FCgListMaterial()
        {
            Materials = new List<TCgAssetRef<Material>>();
        }

        public List<Material> Get()
        {
            return Materials_Internal;
        }

        public Material Get(int index)
        {
            return index < Materials_Internal.Count ? Materials_Internal[index] : null;
        }

        // TODO: HACK: used to temporarily stop warnings
        public void TempAssign()
        {
            foreach (TCgAssetRef<Material> assetRef in Materials)
            {
                Materials_Internal.Add(assetRef.Get());
            }
        }
    }

    #endregion // Materials
}