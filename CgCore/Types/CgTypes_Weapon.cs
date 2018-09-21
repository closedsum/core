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

    [Serializable]
    public struct S_FECgWeaponState
    {
        [SerializeField]
        public string Name;
    }

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

    [Serializable]
    public struct S_FCgData_Weapon_FireMode_Firing
    {
        /** Whether to do weapon fire on release of input */
        [SerializeField]
        public bool bFireOnRelease;
        [SerializeField]
        public bool bChargeFire;
        [SerializeField]
        public float MaxChargeFireTime;
        /** Time before force ending the charge fire. If 0, charge fire will NOT be forced to end. */
        [SerializeField]
        public float ForceReleaseChargeFireTime;
        [SerializeField]
        public float ChargeFireDamageMultiplier;
        [SerializeField]
        public float ChargeFireSpeedMultiplier;
        /** Is the fully automatic weapon */
        [SerializeField]
        public bool bFullAuto;
        /** Number of projectiles to fire per shot */
        [SerializeField]
        public byte ProjectilesPerShot;
        /** Time between each projectile fired per shot */
        [SerializeField]
        public float TimeBetweenProjectilesPerShot;
        /** Time between two consecutive shots */
        [SerializeField]
        public float TimeBetweenShots;
        /** Time between two consecutive shots in full auto */
        [SerializeField]
        public float TimeBetweenAutoShots;
        [SerializeField]
        public bool bHitscan;
        [SerializeField]
        public bool bHitscanUseRadius;
        [SerializeField]
        public bool bHitscanSimulateProjectileDuration;
        [SerializeField]
        public int ObstaclePenetrations;
        [SerializeField]
        public int PawnPenetrations;
        [SerializeField]
        public List<FCgLocationDamageModifier> LocationDamageModifiers;
        /* Whether to also use a Fake Projectile when firing a projectile */
        [SerializeField]
        public bool bUseFake;
        [SerializeField]
        public S_FCgData_ProjectileRef Data;
        [SerializeField]
        public S_FCgData_ProjectileRef ChargeData;
    }

    public class FCgData_Weapon_FireMode_Firing
    {
        /** Whether to do weapon fire on release of input */
        public bool bFireOnRelease;
        public bool bChargeFire;
        public float MaxChargeFireTime;
        /** Time before force ending the charge fire. If 0, charge fire will NOT be forced to end. */
        public float ForceReleaseChargeFireTime;
        public float ChargeFireDamageMultiplier;
        public float ChargeFireSpeedMultiplier;
        /** Is the fully automatic weapon */
        public bool bFullAuto;
        /** Number of projectiles to fire per shot */
        public byte ProjectilesPerShot;
        /** Time between each projectile fired per shot */
        public float TimeBetweenProjectilesPerShot;
        /** Time between two consecutive shots */
        public float TimeBetweenShots;
        /** Time between two consecutive shots in full auto */
        public float TimeBetweenAutoShots;
        public bool bHitscan;
        public bool bHitscanUseRadius;
        public bool bHitscanSimulateProjectileDuration;
        public int ObstaclePenetrations;
        public int PawnPenetrations;
        public List<FCgLocationDamageModifier> LocationDamageModifiers;
        /* Whether to also use a Fake Projectile when firing a projectile */
        public bool bUseFake;
        public FCgData_ProjectileRef Data;
        public FCgData_ProjectileRef ChargeData;

        public FCgData_Weapon_FireMode_Firing()
        {
            LocationDamageModifiers = new List<FCgLocationDamageModifier>();

            Data = new FCgData_ProjectileRef();
            ChargeData = new FCgData_ProjectileRef();
        }
    }

    [Serializable]
    public struct S_FCgData_Weapon_FireMode_Animation
    {
        [SerializeField]
        public bool bLoopFireAnim;
        [SerializeField]
        public FCgAnimClip FireAnim;
        [SerializeField]
        public bool bScaleFireAnim;
    }

    public class FCgData_Weapon_FireMode_Animation
    {
        public bool bLoopFireAnim;
        public FCgAnimClip FireAnim;
        public bool bScaleFireAnim;

        public FCgData_Weapon_FireMode_Animation() { }
    }

    public class FCgData_FpsWeapon_FireMode_Animation
    {
        public bool bLoopFireAnim;
        public FCgFpvAnimClip FireAnims;
        public bool bScaleFireAnim;
        public bool bLoopAdsFireAnim;
        public FCgFpvAnimClip AdsFireAnims;
        public bool bScaleAdsFireAnim;

        public FCgData_FpsWeapon_FireMode_Animation() { }
    }

    public class FCgData_Weapon_FireMode_Movement
    {
        public bool bSlowWhileFiring;
        public float SlowWhileFiringRate;
        public bool bKickback;
        public bool bKickbackOnGround;
        public float KickbackStrength;

        public FCgData_Weapon_FireMode_Movement() { }
    }

    [Serializable]
    public struct S_FCgData_Weapon_FireMode_Aiming
    {
        [SerializeField]
        public bool bHoming;
        [SerializeField]
        public float HomingAccelerationMagnitude;
        [SerializeField]
        public bool bSpread;
        [SerializeField]
        public float MinSpread;
        [SerializeField]
        public float MaxSpread;
        [SerializeField]
        public float SpreadAddedPerShot;
        [SerializeField]
        public float SpreadRecoveryRate;
        [SerializeField]
        public float FiringSpreadRecoveryDelay;
        [SerializeField]
        public float MovingSpreadBonus;
    }

    public class FCgData_Weapon_FireMode_Aiming
    {
        public bool bHoming;
        public float HomingAccelerationMagnitude;
        public bool bSpread;
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
        public List<FCgLocationDamageModifier> MinLocationDamageModifiers;
        public List<FCgLocationDamageModifier> MaxLocationDamageModifiers;
        //FCsCurveFloat LocationDamageModifierRamp;
        public bool bScopePower;
        public float MaxScopePower;
        public float ScopePowerGrowthRate;

	    public FCgData_Weapon_FireMode_Scope()
        {
            MinLocationDamageModifiers = new List<FCgLocationDamageModifier>();
            MaxLocationDamageModifiers = new List<FCgLocationDamageModifier>();
        }
    }

    [Serializable]
    public struct S_FCgData_Weapon_FireMode_FXs
    {
        [SerializeField]
        public List<S_FCgFxElement> MuzzleFXs;
    }

    public class FCgData_Weapon_FireMode_FXs
    {
        #region "Constants"

        public static readonly byte EMPTY = 0;

        #endregion // Constants

        #region "Data Members"

        public List<FCgFxElement> MuzzleFXs;

        #endregion // Data Members

        public FCgData_Weapon_FireMode_FXs()
        {
            MuzzleFXs = new List<FCgFxElement>();
        }
        
        public FCgFxElement GetMuzzleFX(int index = 0)
        {
            int count = MuzzleFXs.Count;

		    return count > EMPTY ? MuzzleFXs[index % count] : null;
	    }

        public string GetMuzzleBone(int index = 0)
        {
            int count = MuzzleFXs.Count;

            return MuzzleFXs[index % count].Bone;
        }
    }

    public class FCgData_FpsWeapon_FireMode_FXs
    {
        #region "Constants"

        public static readonly byte EMPTY = 0;

        #endregion // Constants

        #region "Data Members"

        public List<FCgFpvFxElement> MuzzleFXs;

        #endregion // Data Members

        public FCgData_FpsWeapon_FireMode_FXs()
        {
            MuzzleFXs = new List<FCgFpvFxElement>();
        }
        
        FCgFxElement GetMuzzleFX(ECgViewType viewType, int index = 0)
	    {
            int count = MuzzleFXs.Count;

		    return count > EMPTY ? MuzzleFXs[index % count].Get(viewType) : null;
        }

        string GetMuzzleBone(ECgViewType viewType, int index = 0)
        {
            int count = MuzzleFXs.Count;

            return count > EMPTY ? MuzzleFXs[index % count].GetBone(viewType) : null;
        }
    }

    [Serializable]
    public struct S_FCgData_Weapon_FireMode_Sounds
    {
        /** Single fire sound (bLoopedFireSound not set) */
        [SerializeField]
        public S_FCgSoundElement FireSound;
        [SerializeField]
        public bool bLoopFireSound;

        /** Looped fire sound (bLoopedFireSound set) */
        [SerializeField]
        public S_FCgSoundElement FireLoopSound;
        /** Finished burst sound (bLoopedFireSound set) */
        [SerializeField]
        public S_FCgSoundElement FireFinishSound;
    }

    public class FCgData_Weapon_FireMode_Sounds
    {
        #region "Data Members"

        /** Single fire sound (bLoopedFireSound not set) */
        public FCgSoundElement FireSound;

        public bool bLoopFireSound;

        /** Looped fire sound (bLoopedFireSound set) */
        public FCgSoundElement FireLoopSound;
        /** Finished burst sound (bLoopedFireSound set) */
        public FCgSoundElement FireFinishSound;

        #endregion // Data Members

        public FCgData_Weapon_FireMode_Sounds() { }
    }

    public class FCgData_FpsWeapon_FireMode_Sounds
    {
        /** Single fire sound (bLoopedFireSound not set) */
        public FCgFpvSoundElement FireSounds;

        public bool LoopFireSound;

        /** Looped fire sound (bLoopedFireSound set) */
        public FCgFpvSoundElement FireLoopSounds;
        /** Finished burst sound (bLoopedFireSound set) */
        public FCgFpvSoundElement FireFinishSounds;

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

    public class FCgData_Weapon_FireMode
    {
    }

    #endregion // Data FireMode
    }
