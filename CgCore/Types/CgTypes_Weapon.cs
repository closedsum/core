namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    [Serializable]
    public struct S_FCgLocationDamageModifier
    {
        [SerializeField]
        public string Bone;
        [SerializeField]
        public float Multiplier;
    }

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

    #region "WeaponAnimBlueprint"

    public sealed class FECgWeaponAnimBlueprint : FECgEnum_byte
    {
        public FECgWeaponAnimBlueprint(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponAnimBlueprint : TCgEnumMap<FECgWeaponAnimBlueprint, byte>
    {
        private static EMCgWeaponAnimBlueprint _Instance;
        public static EMCgWeaponAnimBlueprint Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponAnimBlueprint();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponAnimBlueprint Get()
        {
            return Instance;
        }
    }

    public sealed class FECgWeaponAnimBlueprintEqualityComparer : IEqualityComparer<FECgWeaponAnimBlueprint>
    {
        public bool Equals(FECgWeaponAnimBlueprint lhs, FECgWeaponAnimBlueprint rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponAnimBlueprint x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponAnimBlueprint

    #region "WeaponSound"

    public sealed class FECgWeaponSound : FECgEnum_byte
    {
        public FECgWeaponSound(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponSound : TCgEnumMap<FECgWeaponSound, byte>
    {
        private static EMCgWeaponSound _Instance;
        public static EMCgWeaponSound Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponSound();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponSound Get()
        {
            return Instance;
        }
    }

    public sealed class FECgWeaponSoundEqualityComparer : IEqualityComparer<FECgWeaponSound>
    {
        public bool Equals(FECgWeaponSound lhs, FECgWeaponSound rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponSound x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponSound

    #region "WeaponOwner"

    public sealed class FECgWeaponOwner : FECgEnum_byte
    {
        public FECgWeaponOwner(byte value, string name) : base(value, name) { }
    }

    public class EMCgWeaponOwner : TCgEnumMap<FECgWeaponOwner, byte>
    {
        private static EMCgWeaponOwner _Instance;
        public static EMCgWeaponOwner Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponOwner();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponOwner Get()
        {
            return Instance;
        }
    }

    public sealed class FECgWeaponOwnerEqualityComparer : IEqualityComparer<FECgWeaponOwner>
    {
        public bool Equals(FECgWeaponOwner lhs, FECgWeaponOwner rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponOwner x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // WeaponOwner

    #region "Data FireMode"

    public class FCgData_Weapon_FireMode_Firing
    {
        /** Whether to do weapon fire on release of input */
        public bool DoFireOnRelease;
        public bool AllowChargeFire;
        public float MaxChargeFireTime;
        /** Time before force ending the charge fire. If 0, charge fire will NOT be forced to end. */
        public float ForceReleaseChargeFireTime;
        public float ChargeFireDamageMultiplier;
        public float ChargeFireSpeedMultiplier;
        /** Is the fully automatic weapon */
        public bool IsFullAuto;
        /** Number of projectiles to fire per shot */
        public byte ProjectilesPerShot;
        /** Time between each projectile fired per shot */
        public float TimeBetweenProjectilesPerShot;
        /** Time between two consecutive shots */
        public float TimeBetweenShots;
        /** Time between two consecutive shots in full auto */
        public float TimeBetweenAutoShots;
        public bool IsHitscan;
        public bool DoesHitscanUseRadius;
        public bool DoesHitscanSimulateProjectileDuration;
        public int ObstaclePenetrations;
        public int PawnPenetrations;
        //TArray<FCsLocationDamageModifier> LocationDamageModifiers;
        /* Whether to also use a Fake Projectile when firing a projectile */
        public bool UseFake;
        public FCgData_ProjectileRef Data;
        public FCgData_ProjectileRef ChargeData;

        public FCgData_Weapon_FireMode_Firing()
        {
            Data = new FCgData_ProjectileRef();
            ChargeData = new FCgData_ProjectileRef();
        }
    }

    public class CgData_Weapon_FireMode_Animation
    {
        public bool LoopFireAnim;
        //FCsAnimMontage FireAnim;
        public bool DoScaleFireAnim;

        public CgData_Weapon_FireMode_Animation() { }
    }

    public class CgData_FpsWeapon_FireMode_Animation
    {
        public bool LoopFireAnim;
        //FCsFpvAnimMontage FireAnims;
        public bool DoScaleFireAnim;
        public bool LoopAdsFireAnim;
        // FCsFpvAnimMontage AdsFireAnims;
        public bool DoScaleAdsFireAnim;

        public CgData_FpsWeapon_FireMode_Animation() { }
    }

    public class FCgData_Weapon_FireMode_Movement
    {
        public bool DoSlowWhileFiring;
        public float SlowWhileFiringRate;
        public bool DoKickback;
        public bool DoKickbackOnGround;
        public float KickbackStrength;

        public FCgData_Weapon_FireMode_Movement() { }
    }

    public class FCgData_Weapon_FireMode_Aiming
    {
        public bool IsHoming;
        public float HomingAccelerationMagnitude;
        public bool DoSpread;
        public float MinSpread;
        public float MaxSpread;
        public float SpreadAddedPerShot;
        public float SpreadRecoveryRate;
        public float FiringSpreadRecoveryDelay;
        public float MovingSpreadBonus;

        public FCgData_Weapon_FireMode_Aiming() { }
    }

    public class FCgData_FpsWeapon_FireMode_Aiming : FCgData_Weapon_FireMode_Aiming
    {
        public float JumpSpreadImpulse;
        public float ScopeAccuracyBonus;

        public FCgData_FpsWeapon_FireMode_Aiming() { }
    }

    public class FCgData_Weapon_FireMode_Scope
    {
        //TArray<FCsLocationDamageModifier> MinLocationDamageModifiers;
        //TArray<FCsLocationDamageModifier> MaxLocationDamageModifiers;
        //FCsCurveFloat LocationDamageModifierRamp;
        public bool DoScopePower;
        public float MaxScopePower;
        public float ScopePowerGrowthRate;

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
        public bool LoopFireSound;

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

        public bool LoopFireSound;

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
