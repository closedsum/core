namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgGunWeapon : MCgWeapon
    {
        #region "Data Members"

        #region "Data"

        public MCgData_WeaponMaterialSkin MyData_WeaponMaterialSkin;

        #endregion // Data

        #region "State"

        public FECgWeaponGrip GripType;

        #endregion // State

        #endregion // Data Members

        #region "Data"

        public virtual void ApplyData_Weapon(FECgWeaponSlot slot, MCgData_Weapon data, MCgData_WeaponMaterialSkin skin, bool isEquipped = true)
        {
            _Reset();

            WeaponSlot = slot;
            WeaponIndex = slot.Value;

            MyData_Weapon = data;

            MCgData_ProjectileWeapon data_weapon = (MCgData_ProjectileWeapon)data;
            GripType = data_weapon.GetGripType();

            MyData_WeaponMaterialSkin = skin;
            bEquipped = isEquipped;

            CurrentState = IdleState;
            LastState = CurrentState;

            // UseMeshLow
#if UNITY_EDITOR
            /*
	        // In Editor Preview Window
	        if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            {
                //UseMesh3PLow = false;// Pawn->UseMesh3PLow && InData->HasMesh3PLow;
            }

            SetMesh();
            AttachMeshToPawn();
            //SetMultiValueMembers();

            OnApplyData_Weapon_Event.Broadcast(WeaponSlot);
        }

        public MCgData_WeaponMaterialSkin GetMyData_WeaponMaterialSkin()
        {
            return MyData_WeaponMaterialSkin;
        }

        public T GetMyData_WeaponMaterialSkin<T>()
            where T : MCgData_WeaponMaterialSkin
        {
            return (T)GetMyData_WeaponMaterialSkin();
        }

        public MCgData_Character GetMyData_Character()
        {
#if UNITY_EDITOR
            /*
	        // In Editor Preview Window
	        if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        // Character
		        if (UCsAnimInstance_Character* AnimInstance = Cast<UCsAnimInstance_Character>(GetMyOwner()))
			        return AnimInstance->GetData();
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            {
                if (MyOwnerType == PawnWeaponOwner)
                    return GetMyPawn().GetMyData_Character();
            }
            return null;
        }

        public T GetMyData_Character<T>()
            where T : MCgData_Character
        {
            return (T)GetMyData_Character();
        }

        #endregion // Data

        #region "Owner"

        public virtual void AttachMeshToPawn() { }

        #endregion // Owner

        #region "State"

        public virtual void OnPawnDeActivate()
        {
            Hide();
            Disable();

            bReloadingHandle.Set(false);
            ReloadStartTime = FCgManager_Time.Get().GetTimeSinceStart(TimeType) + ReloadTime.Get(DATA_VALUE) + 1.0f;
        }

        #endregion // State

        #region "Mesh"

        public virtual void SetMesh(){}

        #endregion // Mesh

        #region "Animation"

        public virtual FECgCharacterAnim GetCharacterAnimType(FECgWeaponAnim animType)
        {
            return EMCgCharacterAnim.Get().GetMAX();
        }

        #endregion // Animation
    }
}
