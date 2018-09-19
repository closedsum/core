namespace CgEditor
{
    using UnityEditor;
    using UnityEngine;

    using CgEditor;
    using CgCore;

    [CustomPropertyDrawer(typeof(S_FECgAssetType))]
    public class FCgEdDrawer_FECgAssetType : FCgEdDrawer_EnumClass<EMCgAssetType, FECgAssetType, byte>
    {
    }
}