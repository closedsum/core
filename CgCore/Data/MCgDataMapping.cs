namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgDataMapping : MonoBehaviour
    {
        #region "Constants"

        public static readonly string DATA_MAPPING_NAME = "d_data_mapping";

        #endregion // Constants

        #region "Data Members"

        private static MCgDataMapping _Instance;

        public Dictionary<FECgAssetType, Dictionary<string, MCgData>> Map;

        #endregion // Data Members

        public static MCgDataMapping Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : MCgDataMapping
        {
            return (T)_Instance;
        }

        public static void Init()
        {
            if (_Instance != null)
                return;

            GameObject go = GameObject.Find(DATA_MAPPING_NAME);

#if UNITY_EDITOR
            if (go == null)
            {
                FCgDebug.LogError("MCgDataMapping.Init: Failed to find GameObject with name: " + DATA_MAPPING_NAME);
            }
#endif // #if UNITY_EDITOR

            _Instance = go.GetComponent<MCgDataMapping>();

#if UNITY_EDITOR
            if (_Instance == null)
            {
                FCgDebug.LogError("MCgDataMapping.Init: GameObject: " + DATA_MAPPING_NAME + " does not have a component of type MCgDataMapping.");
            }
#endif // #if UNITY_EDITOR

            _Instance.Init_Internal();
        }

        protected virtual void Init_Internal()
        {
            Map = new Dictionary<FECgAssetType, Dictionary<string, MCgData>>(new FECgAssetTypeEqualityComparer());

            int count = EMCgAssetType.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                Map.Add(EMCgAssetType.Get().GetEnumAt(i), new Dictionary<string, MCgData>());
            }
        }

        public virtual void GenerateMaps(bool initialize = false){}

        public void GenerateMap<DataType>(FECgAssetType assetType, ref List<DataType> list, ref Dictionary<string, DataType> map, bool intialize = false)
            where DataType : MCgData
        {
            if (intialize)
            {
                if (list == null)
                    list = new List<DataType>();

                map = new Dictionary<string, DataType>();
            }

            foreach (DataType d in list)
            {
                map.Add(d.ShortCode, d);
                Map[assetType].Add(d.ShortCode, d);
            }
        }

        // TODO: Need to actually do Loading for cache "miss"
        public MCgData LoadData(FECgAssetType assetType, string shortCode)
        {
            if (Map[assetType].ContainsKey(shortCode))
                return Map[assetType][shortCode];

            FCgDebug.LogWarning("MCgDataMapping.LoadData: No " + assetType.Name + " with ShortCode: " + shortCode);
            return null;
        }

        // TODO: Need to actually do Loading for cache "miss"
        public T LoadData<T>(FECgAssetType assetType, string shortCode)
            where T : MCgData
        {
            return (T)LoadData(assetType, shortCode);
        }

        public MCgData GetData(FECgAssetType assetType, string shortCode)
        {
            if (Map[assetType].ContainsKey(shortCode))
                return Map[assetType][shortCode];

            FCgDebug.LogWarning("MCgDataMapping.GetData: No " + assetType.Name + " with ShortCode: " + shortCode);
            return null;
        }

        public T GetData<T>(FECgAssetType assetType, string shortCode)
            where T : MCgData
        {
            return (T)GetData(assetType, shortCode);
        }
    }
}