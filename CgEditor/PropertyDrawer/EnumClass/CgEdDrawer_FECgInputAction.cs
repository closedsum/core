namespace CgEditor
{
    using UnityEditor;
    using UnityEngine;

    using CgEditor;
    using CgCore;

    [CustomPropertyDrawer(typeof(S_FECgInputAction))]
    public class FCgEdDrawer_FECgInputAction : FCgEdDrawer_EnumClass<EMCgInputAction, FECgInputAction, byte>
    {
    }
}