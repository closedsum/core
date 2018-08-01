namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgData_ProjectileWeapon : MCgData_Weapon
    {
        #region "Stats"

        public virtual bool UseFakeProjectile(FECgWeaponFireMode fireMode){ return false; }

        public virtual MCgData_Projectile GetData_Projectile(FECgWeaponFireMode fireMode, bool isCharged = false){ return null; }

        #endregion // Stats

        #region "Sound"

        public virtual FCgSoundElement GetSound(ECgViewType viewType, FECgWeaponFireMode fireMode, FECgWeaponSound soundType)
        {
            return null;
        }

	    public virtual FCgSoundElement GetSound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType)
        {
            return null;
        }

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
