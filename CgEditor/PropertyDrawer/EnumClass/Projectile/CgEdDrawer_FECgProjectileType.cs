namespace CgEditor
{
    using UnityEditor;

    using CgCore;

    [CustomPropertyDrawer(typeof(S_FECgProjectileType))]
    public class FCgEdDrawer_FECgProjectileType : FCgEdDrawer_EnumClass<EMCgProjectileType, FECgProjectileType, byte>
    {
    }
}