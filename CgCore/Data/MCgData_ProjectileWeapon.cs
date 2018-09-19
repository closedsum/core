namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgData_ProjectileWeapon : MCgData_Weapon
    {
        #region "Stats"

        public virtual FCgData_Weapon_FireMode GetFireModeClass(FECgWeaponFireMode fireMode) { return null; }

        public virtual float GetLocationDamageModifier(FECgWeaponFireMode fireMode, string bone) { return 0.0f; }

        public virtual bool UseFakeProjectile(FECgWeaponFireMode fireMode){ return false; }

        public virtual MCgData_Projectile GetData_Projectile(FECgWeaponFireMode fireMode, bool isCharged = false){ return null; }

        public virtual string GetMuzzleBone(ECgViewType viewType, FECgWeaponFireMode fireMode, int index = 0) { return ECgCached.Str.NAME_None; }
        public virtual string GetMuzzleBone(FECgWeaponFireMode fireMode, int index = 0) { return ECgCached.Str.NAME_None; }

        public virtual Vector3 GetMuzzleLocation(FCgSkeleton skeleton, ECgViewType viewType, FECgWeaponFireMode fireMode, int index = 0)
        {
            return skeleton.GetBoneLocation(GetMuzzleBone(viewType, fireMode, index));
        }

        public virtual Vector3 GetMuzzleLocation(FCgSkeleton skeleton, FECgWeaponFireMode fireMode, int index = 0)
        {
            return skeleton.GetBoneLocation(GetMuzzleBone(fireMode, index));
        }

        public virtual FECgWeaponGrip GetGripType() { return EMCgWeaponGrip.Get().GetMAX(); }

        public virtual string GetMaxAmmoMemberName() { return ECgCached.Str.NAME_None; }
        public virtual int GetMaxAmmo() { return 0; }

        public virtual string GetRechargeStartupDelayMemberName() { return ECgCached.Str.NAME_None; }
        public virtual float GetRechargeStartupDelay() { return 0.0f; }
        public virtual string GetRechargeSecondsPerAmmoMemberName() { return ECgCached.Str.NAME_None; }
        public virtual float GetRechargeSecondsPerAmmo() { return 0.0f; }
        public virtual string GetReloadTimeMemberName() { return ECgCached.Str.NAME_None; }
        public virtual float GetReloadTime() { return 0.0f; }

        #endregion // Stats

        #region "Anims"
        
        #endregion // Anims

        #region "FX"

        public virtual FCgFxElement GetMuzzleFX(ECgViewType viewType, FECgWeaponFireMode fireMode, int index = 0) { return null; }
        public virtual FCgFxElement GetMuzzleFX(FECgWeaponFireMode fireMode, int index = 0) { return null; }

        #endregion // FX

        #region "Sound"

        public virtual FCgSoundElement GetSound(ECgViewType viewType, FECgWeaponFireMode fireMode, FECgWeaponSound soundType){ return null; }
	    public virtual FCgSoundElement GetSound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType){ return null; }

	    public virtual void PlaySound(ECgViewType viewType, FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, MonoBehaviour parent)
        {
            FCgSoundElement soundElement = GetSound(viewType, fireMode, soundType);

            if (soundElement.Get() == null)
            {
                FCgDebug.LogWarning("MCsData_ProjectileWeapon.PlaySound: Attempting to Play a NULL Sound.");
                return;
            }
            
            ICgManager_Sound manager_sound = ICgManager_Sound.Get();
            /*
            FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
            Payload->Set(SoundElement);
            Payload->Owner = InOwner;
            Payload->Parent = InParent;

            Manager_Sound->Play(Payload);
            */
        }

	    public virtual void PlaySound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, MonoBehaviour parent)
        {
            FCgSoundElement soundElement = GetSound(fireMode, soundType);

            if (soundElement.Get() == null)
            {
                FCgDebug.LogWarning("MCsData_ProjectileWeapon.PlaySound: Attempting to Play a NULL Sound.");
                return;
            }
            
            ICgManager_Sound manager_sound = ICgManager_Sound.Get();
            /*
            FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
            Payload->Set(SoundElement);
            Payload->Owner = InOwner;
            Payload->Parent = InParent;

            Manager_Sound->Play(Payload);
            */
        }

	    public virtual void PlaySound(ECgViewType viewType, FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, Vector3 location)
        {
            FCgSoundElement soundElement = GetSound(viewType, fireMode, soundType);

            if (soundElement.Get() == null)
            {
                FCgDebug.LogWarning("MCsData_ProjectileWeapon.PlaySound: Attempting to Play a NULL Sound.");
                return;
            }

            ICgManager_Sound manager_sound = ICgManager_Sound.Get();
            /*
            FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
            Payload->Set(SoundElement);
            Payload->Owner = InOwner;
            Payload->Location = Location;

            Manager_Sound->Play(Payload);
            */
        }

	    public virtual void PlaySound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, Vector3 location)
        {
            FCgSoundElement soundElement = GetSound(fireMode, soundType);
	
	        if (soundElement.Get() == null)
	        {
		        FCgDebug.LogWarning("MCsData_ProjectileWeapon.PlaySound: Attempting to Play a NULL Sound.");
		        return;
	        }

            ICgManager_Sound manager_sound = ICgManager_Sound.Get();
            /*
            FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
            Payload->Set(SoundElement);
            Payload->Owner = InOwner;
	        Payload->Location = Location;

	        Manager_Sound->Play(Payload);
            */
        }

	    public virtual void StopSound(ECgViewType viewType, FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, MonoBehaviour parent)
        {
            FCgSoundElement soundElement    = GetSound(viewType, fireMode, soundType);
            ICgManager_Sound manager_sound  = ICgManager_Sound.Get();

            //manager_sound.Stop(soundElement, owner, parent);
        }
	    
        public virtual void StopSound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType, MonoBehaviour owner, MonoBehaviour parent)
        {
            FCgSoundElement soundElement    = GetSound(fireMode, soundType);
            ICgManager_Sound manager_sound  = ICgManager_Sound.Get();

            //manager_sound.Stop(soundElement, owner, parent);
        }

        #endregion // Sound
    }
}
