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

    public sealed class FECgWeaponState : FECgEnum_byte
    {
        public FECgWeaponState(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponState : TCgEnumMap<FECgWeaponState, byte>
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

    public sealed class FECgWeaponStateEqualityComparer : IEqualityComparer<FECgWeaponState>
    {
        public bool Equals(FECgWeaponState lhs, FECgWeaponState rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponState x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponState

    #region "WeaponSlot"

    public sealed class FECgWeaponSlot : FECgEnum_byte
    {
        public FECgWeaponSlot(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponSlot : TCgEnumMap<FECgWeaponSlot, byte>
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

    public sealed class FECgWeaponSlotEqualityComparer : IEqualityComparer<FECgWeaponSlot>
    {
        public bool Equals(FECgWeaponSlot lhs, FECgWeaponSlot rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponSlot x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponSlot

    #region "WeaponFireMode"

    public sealed class FECgWeaponFireMode : FECgEnum_byte
    {
        public FECgWeaponFireMode(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponFireMode : TCgEnumMap<FECgWeaponFireMode, byte>
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

    public sealed class FECgWeaponFireModeEqualityComparer : IEqualityComparer<FECgWeaponFireMode>
    {
        public bool Equals(FECgWeaponFireMode lhs, FECgWeaponFireMode rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponFireMode x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponFireMode

    #region "WeaponGrip"

    public sealed class FECgWeaponGrip : FECgEnum_byte
    {
        public FECgWeaponGrip(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponGrip : TCgEnumMap<FECgWeaponGrip, byte>
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

    public sealed class FECgWeaponGripEqualityComparer : IEqualityComparer<FECgWeaponGrip>
    {
        public bool Equals(FECgWeaponGrip lhs, FECgWeaponGrip rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponGrip x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponGrip

    #region "WeaponAnim"

    public sealed class FECgWeaponAnim : FECgEnum_byte
    {
        public FECgWeaponAnim(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponAnim : TCgEnumMap<FECgWeaponAnim, byte>
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

    public sealed class FECgWeaponAnimEqualityComparer : IEqualityComparer<FECgWeaponAnim>
    {
        public bool Equals(FECgWeaponAnim lhs, FECgWeaponAnim rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponAnim x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponAnim

    #region "WeaponBlendSpace"

    public sealed class FECgWeaponBlendSpace : FECgEnum_byte
    {
        public FECgWeaponBlendSpace(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponBlendSpace : TCgEnumMap<FECgWeaponBlendSpace, byte>
    {
        private static EMCgWeaponBlendSpace _Instance;
        public static EMCgWeaponBlendSpace Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponBlendSpace();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponBlendSpace Get()
        {
            return Instance;
        }
    }

    public sealed class FECgWeaponBlendSpaceEqualityComparer : IEqualityComparer<FECgWeaponBlendSpace>
    {
        public bool Equals(FECgWeaponBlendSpace lhs, FECgWeaponBlendSpace rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponBlendSpace x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponBlendSpace

    #region "Data FireMode"

    public class FCgData_Weapon_FireMode_Firing
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

        public FCgData_Weapon_FireMode_Firing()
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

    public class FCgData_Weapon_FireMode_Movement
    {
        bool DoSlowWhileFiring;
        float SlowWhileFiringRate;
        bool DoKickback;
        bool DoKickbackOnGround;
        float KickbackStrength;

        public FCgData_Weapon_FireMode_Movement() { }
    }

    public class FCgData_Weapon_FireMode_Aiming
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

        public FCgData_Weapon_FireMode_Aiming() { }
    }

    public class FCgData_FpsWeapon_FireMode_Aiming : FCgData_Weapon_FireMode_Aiming
    {
        float JumpSpreadImpulse;
        float ScopeAccuracyBonus;

        public FCgData_FpsWeapon_FireMode_Aiming() { }
    }

    public class FCgData_Weapon_FireMode_Scope
    {
        //TArray<FCsLocationDamageModifier> MinLocationDamageModifiers;
        //TArray<FCsLocationDamageModifier> MaxLocationDamageModifiers;
        //FCsCurveFloat LocationDamageModifierRamp;
        bool DoScopePower;
        float MaxScopePower;
        float ScopePowerGrowthRate;

	    public FCgData_Weapon_FireMode_Scope() { }
    }

    public class FCgData_Weapon_FireMode_FXs
    {
        //TArray<FCsFxElement> MuzzleFXs;

        public FCgData_Weapon_FireMode_FXs() { }
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

    public class FCgData_FpsWeapon_FireMode_FXs
    {
        //TArray<FCsFpsFxElement> MuzzleFXs;

        public FCgData_FpsWeapon_FireMode_FXs() { }
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

    public class FCgData_Weapon_FireMode_Sounds
    {
        /** single fire sound (bLoopedFireSound not set) */
        //FCsSoundElement FireSound;
        bool LoopFireSound;

        /** looped fire sound (bLoopedFireSound set) */
        //FCsSoundElement FireLoopSound;
        /** finished burst sound (bLoopedFireSound set) */
        //FCsSoundElement FireFinishSound;

        public FCgData_Weapon_FireMode_Sounds() { }
    }

    public class FCgData_FpsWeapon_FireMode_Sounds
    {
        /** single fire sound (bLoopedFireSound not set) */
        //FCsFpsSoundElement FireSounds;

        bool LoopFireSound;

        /** looped fire sound (bLoopedFireSound set) */
        //FCsFpsSoundElement FireLoopSounds;
        /** finished burst sound (bLoopedFireSound set) */
        //FCsFpsSoundElement FireFinishSounds;

        public FCgData_FpsWeapon_FireMode_Sounds() { }
    }

    public sealed class FECgData_Weapon_FireMode : FECgEnum_byte
    {
        public FECgData_Weapon_FireMode(byte value, string name) : base(value, name) { }
    }

    public class EMCgData_Weapon_FireMode : TCgEnumMap<FECgData_Weapon_FireMode, byte>
    {
        private static EMCgData_Weapon_FireMode _Instance;
        public static EMCgData_Weapon_FireMode Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgData_Weapon_FireMode();
                }
                return _Instance;
            }
        }

        public static EMCgData_Weapon_FireMode Get()
        {
            return Instance;
        }
    }

    public sealed class FECgDataWeaponFireModeEqualityComparer : IEqualityComparer<FECgData_Weapon_FireMode>
    {
        public bool Equals(FECgData_Weapon_FireMode lhs, FECgData_Weapon_FireMode rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgData_Weapon_FireMode x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // Data FireMode
}
