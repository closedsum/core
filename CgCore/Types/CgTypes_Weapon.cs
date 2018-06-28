namespace CgCore
{
    using System.Collections.Generic;

    public class FCgLocationDamageModifier
    {
        public string Bone;
        public float Multiplier;

        public FCgLocationDamageModifier()
        {
            Bone = "";
            Multiplier = 1.0f;
        }

        public static bool operator ==(FCgLocationDamageModifier lhs, FCgLocationDamageModifier rhs)
        {
            return lhs.Bone == rhs.Bone && lhs.Multiplier == rhs.Multiplier;
        }

        public static bool operator !=(FCgLocationDamageModifier lhs, FCgLocationDamageModifier rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is FCgLocationDamageModifier))
                return false;

            FCgLocationDamageModifier rhs = (FCgLocationDamageModifier)obj;

            if (Bone != rhs.Bone) return false;
            if (Multiplier != rhs.Multiplier) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Bone.GetHashCode() ^ Multiplier.GetHashCode();
        }
    }

    #region "WeaponState"

    public sealed class ECgWeaponState : ECgEnum_byte
    {
        public ECgWeaponState(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponState : ECgEnumMap<ECgWeaponState, byte>
    {
        private static EMCgWeaponState _Instance;
        public static EMCgWeaponState Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponState();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponState Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponStateEqualityComparer : IEqualityComparer<ECgWeaponState>
    {
        public bool Equals(ECgWeaponState lhs, ECgWeaponState rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponState x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponState

    #region "WeaponSlot"

    public sealed class ECgWeaponSlot : ECgEnum_byte
    {
        public ECgWeaponSlot(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponSlot : ECgEnumMap<ECgWeaponSlot, byte>
    {
        private static EMCgWeaponSlot _Instance;
        public static EMCgWeaponSlot Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponSlot();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponSlot Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponSlotEqualityComparer : IEqualityComparer<ECgWeaponSlot>
    {
        public bool Equals(ECgWeaponSlot lhs, ECgWeaponSlot rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponSlot x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponSlot

    #region "WeaponFireMode"

    public sealed class ECgWeaponFireMode : ECgEnum_byte
    {
        public ECgWeaponFireMode(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponFireMode : ECgEnumMap<ECgWeaponFireMode, byte>
    {
        private static EMCgWeaponFireMode _Instance;
        public static EMCgWeaponFireMode Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponFireMode();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponFireMode Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponFireModeEqualityComparer : IEqualityComparer<ECgWeaponFireMode>
    {
        public bool Equals(ECgWeaponFireMode lhs, ECgWeaponFireMode rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponFireMode x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponFireMode

    #region "WeaponGrip"

    public sealed class ECgWeaponGrip : ECgEnum_byte
    {
        public ECgWeaponGrip(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponGrip : ECgEnumMap<ECgWeaponGrip, byte>
    {
        private static EMCgWeaponGrip _Instance;
        public static EMCgWeaponGrip Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponGrip();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponGrip Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponGripEqualityComparer : IEqualityComparer<ECgWeaponGrip>
    {
        public bool Equals(ECgWeaponGrip lhs, ECgWeaponGrip rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponGrip x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponGrip

    #region "WeaponAnim"

    public sealed class ECgWeaponAnim : ECgEnum_byte
    {
        public ECgWeaponAnim(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponAnim : ECgEnumMap<ECgWeaponAnim, byte>
    {
        private static EMCgWeaponAnim _Instance;
        public static EMCgWeaponAnim Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponAnim();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponAnim Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponAnimEqualityComparer : IEqualityComparer<ECgWeaponAnim>
    {
        public bool Equals(ECgWeaponAnim lhs, ECgWeaponAnim rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponAnim x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponAnim

    #region "WeaponBlendSpace"

    public sealed class ECgWeaponBlendSpace : ECgEnum_byte
    {
        public ECgWeaponAnim(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponAnim : ECgEnumMap<ECgWeaponAnim, byte>
    {
        private static EMCgWeaponAnim _Instance;
        public static EMCgWeaponAnim Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponAnim();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponAnim Get()
        {
            return Instance;
        }
    }

    public sealed class ECgWeaponAnimEqualityComparer : IEqualityComparer<ECgWeaponAnim>
    {
        public bool Equals(ECgWeaponAnim lhs, ECgWeaponAnim rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgWeaponAnim x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponAnim

    public class CgData_Weapon_FireMode_Firing
    {
        /** Whether to do weapon fire on release of input */
        bool DoFireOnRelease;
        bool AllowChargeFire;
        float MaxChargeFireTime;
        /** Time before force ending the charge fire. If 0, charge fire will NOT be forced to end. */
        float ForceReleaseChargeFireTime;
        float ChargeFireDamageMultiplier;
        float ChargeFireSpeedMultiplier;
        /** Is the fully automatic weapon */
        bool IsFullAuto;
        /** Number of projectiles to fire per shot */
        byte ProjectilesPerShot;
        /** Time between each projectile fired per shot */
        float TimeBetweenProjectilesPerShot;
        /** Time between two consecutive shots */
        float TimeBetweenShots;
        /** Time between two consecutive shots in full auto */
        float TimeBetweenAutoShots;
        bool IsHitscan;
        bool DoesHitscanUseRadius;
        bool DoesHitscanSimulateProjectileDuration;
        int ObstaclePenetrations;
        int PawnPenetrations;
        //TArray<FCsLocationDamageModifier> LocationDamageModifiers;
        /* Whether to also use a Fake Projectile when firing a projectile */
        bool UseFake;
        CgData_ProjectileRef Data;
        CgData_ProjectileRef ChargeData;

        public CgData_Weapon_FireMode_Firing()
        {
            Data = new CgData_ProjectileRef();
            ChargeData = new CgData_ProjectileRef();
        }
    }

    public class CgData_Weapon_FireMode_Animation
    {

        bool LoopFireAnim;
        //FCsAnimMontage FireAnim;
        bool DoScaleFireAnim;

        public CgData_Weapon_FireMode_Animation() { }
    }

    public class CgData_FpsWeapon_FireMode_Animation
    {
        bool LoopFireAnim;
        //FCsFpvAnimMontage FireAnims;
        bool DoScaleFireAnim;
        bool LoopAdsFireAnim;
       // FCsFpvAnimMontage AdsFireAnims;
        bool DoScaleAdsFireAnim;

        public CgData_FpsWeapon_FireMode_Animation() { }
    }

    public class CgData_Weapon_FireMode_Movement
    {
        bool DoSlowWhileFiring;
        float SlowWhileFiringRate;
        bool DoKickback;
        bool DoKickbackOnGround;
        float KickbackStrength;

        public CgData_Weapon_FireMode_Movement() { }
    }

    public class CgData_Weapon_FireMode_Aiming
    {
        bool IsHoming;
        float HomingAccelerationMagnitude;
        bool DoSpread;
        float MinSpread;
        float MaxSpread;
        float SpreadAddedPerShot;
        float SpreadRecoveryRate;
        float FiringSpreadRecoveryDelay;
        float MovingSpreadBonus;

        public CgData_Weapon_FireMode_Aiming() { }
    }

    public class CgData_FpsWeapon_FireMode_Aiming : CgData_Weapon_FireMode_Aiming
    {
        float JumpSpreadImpulse;
        float ScopeAccuracyBonus;

        public CgData_FpsWeapon_FireMode_Aiming() { }
    }

    public class CgData_Weapon_FireMode_Scope
    {
        //TArray<FCsLocationDamageModifier> MinLocationDamageModifiers;
        //TArray<FCsLocationDamageModifier> MaxLocationDamageModifiers;
        //FCsCurveFloat LocationDamageModifierRamp;
        bool DoScopePower;
        float MaxScopePower;
        float ScopePowerGrowthRate;

	    public CgData_Weapon_FireMode_Scope() { }
    }

    public class CgData_Weapon_FireMode_FXs
    {
        //TArray<FCsFxElement> MuzzleFXs;

        public CgData_Weapon_FireMode_FXs() { }
        /*
        FCsFxElement* GetMuzzleFX(const int32 Index = 0)
	    {

            const int32 Count = MuzzleFXs.Num();

		    return Count > CS_EMPTY? &(MuzzleFXs[Index % Count]) : nullptr;
	    }

        FName GetMuzzleBone(const int32 Index = 0)
        {
            const int32 Count = MuzzleFXs.Num();

            return MuzzleFXs[Index % Count].Bone;
        }
        */
    }

    public class CgData_FpsWeapon_FireMode_FXs
    {
        //TArray<FCsFpsFxElement> MuzzleFXs;

        public CgData_FpsWeapon_FireMode_FXs() { }
        /*
        FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const int32 Index = 0)
	    {

            const int32 Count = MuzzleFXs.Num();

		    return MuzzleFXs[Index % Count].Get(ViewType);
        }

        FName GetMuzzleBone(const TCsViewType &ViewType, const int32 Index = 0)
        {
            const int32 Count = MuzzleFXs.Num();

            return MuzzleFXs[Index % Count].GetBone(ViewType);
        }
        */
    }

    public class CgData_Weapon_FireMode_Sounds
    {
        /** single fire sound (bLoopedFireSound not set) */
        //FCsSoundElement FireSound;
        bool LoopFireSound;

        /** looped fire sound (bLoopedFireSound set) */
        //FCsSoundElement FireLoopSound;
        /** finished burst sound (bLoopedFireSound set) */
        //FCsSoundElement FireFinishSound;

        public CgData_Weapon_FireMode_Sounds() { }
    }

    public class CgData_FpsWeapon_FireMode_Sounds
    {
        /** single fire sound (bLoopedFireSound not set) */
        //FCsFpsSoundElement FireSounds;

        bool LoopFireSound;

        /** looped fire sound (bLoopedFireSound set) */
        //FCsFpsSoundElement FireLoopSounds;
        /** finished burst sound (bLoopedFireSound set) */
        //FCsFpsSoundElement FireFinishSounds;

        public CgData_FpsWeapon_FireMode_Sounds() { }
    }
}
