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
        }
    }
}