namespace CgEditor
{
    using UnityEditor;

    using CgCore;

    [CustomPropertyDrawer(typeof(S_FECgWeaponState))]
    public class FCgEdDrawer_FECgWeaponState : FCgEdDrawer_EnumClass<EMCgWeaponState, FECgWeaponState, byte>
    {
    }
}