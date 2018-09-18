namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using System.Reflection;

    using UnityEngine;

    public abstract class MCgData : MonoBehaviour
    {
        [SerializeField]
        public S_FECgAssetType S_AssetType;
        [NonSerialized]    
        public FECgAssetType AssetType;

        [SerializeField]
        public string ShortCode;

        public virtual void Init()
        {
            Dictionary<string, FieldInfo> serializedFields = new Dictionary<string, FieldInfo>();
            Dictionary<string, FieldInfo> nonSerializedFields = new Dictionary<string, FieldInfo>(); 

            Type type = this.GetType();

            FieldInfo[] fieldinfos = type.GetFields();

            foreach (FieldInfo f in fieldinfos)
            {
                object[] attributes = f.GetCustomAttributes(true);

                foreach (object a in attributes)
                {
                    // SerializeField
                    if (a.GetType() == typeof(SerializeField))
                        serializedFields.Add(f.Name, f);
                    // NonSerializedAttribute
                    else
                    if (a.GetType() == typeof(NonSerializedAttribute))
                        nonSerializedFields.Add(f.Name, f);
                }
            }

            Dictionary<string, FieldInfo>.KeyCollection fieldNames = serializedFields.Keys;

            foreach (string name in fieldNames)
            {
                // Prefix with S_
                if (name.StartsWith("S_"))
                {
                    string ns_name = name.Replace("S_", "");

                    FieldInfo sf  = serializedFields[name];
                    FieldInfo nsf = nonSerializedFields[ns_name];
                }
            }
        }

        public void StructToClassSerialization(object structObject, FieldInfo structFieldInfo, object classObject, FieldInfo classFieldInfo)
        {
            object sValue           = structFieldInfo.GetValue(structObject);
            Type sType              = sValue.GetType();
            FieldInfo[] sFieldInfos = sType.GetFields(BindingFlags.Public);

            object cValue = classFieldInfo.GetValue(classObject);
            Type cType = cValue.GetType();
            FieldInfo[] cFieldInfos = cType.GetFields(BindingFlags.Public);
        }
    }
}