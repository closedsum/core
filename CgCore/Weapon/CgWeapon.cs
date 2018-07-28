namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public sealed class FECgWeaponMultiValueMember : ECgEnum_byte
    {
        public FECgWeaponMultiValueMember(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgWeaponMultiValueMemberEqualityComparer : IEqualityComparer<FECgWeaponMultiValueMember>
    {
        public bool Equals(FECgWeaponMultiValueMember lhs, FECgWeaponMultiValueMember rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponMultiValueMember x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgWeaponMultiValueMember : ECgEnumMap<FECgWeaponMultiValueMember, byte>
    {
        private static EMCgWeaponMultiValueMember _Instance;
        public static EMCgWeaponMultiValueMember Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponMultiValueMember();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponMultiValueMember Get()
        {
            return Instance;
        }
    }

    public static class ECgWeaponMultiValueMember
    {
        public static readonly FECgWeaponMultiValueMember MaxAmmo = EMCgWeaponMultiValueMember.Get().Create("MaxAmmo");
        public static readonly FECgWeaponMultiValueMember ProjectilesPerShot = EMCgWeaponMultiValueMember.Get().Create("ProjectilesPerShot");
        public static readonly FECgWeaponMultiValueMember CurrentProjectilePerShotIndex = EMCgWeaponMultiValueMember.Get().Create("CurrentProjectilePerShotIndex");
        public static readonly FECgWeaponMultiValueMember DoFireOnRelease = EMCgWeaponMultiValueMember.Get().Create("DoFireOnRelease");
        public static readonly FECgWeaponMultiValueMember IsFullAuto = EMCgWeaponMultiValueMember.Get().Create("IsFullAuto");
        public static readonly FECgWeaponMultiValueMember TimeBetweenProjectilesPerShot = EMCgWeaponMultiValueMember.Get().Create("TimeBetweenProjectilesPerShot");
        public static readonly FECgWeaponMultiValueMember TimeBetweenShots = EMCgWeaponMultiValueMember.Get().Create("TimeBetweenShots");
        public static readonly FECgWeaponMultiValueMember TimeBetweenAutoShots = EMCgWeaponMultiValueMember.Get().Create("TimeBetweenAutoShots");
        public static readonly FECgWeaponMultiValueMember IsFirePressed = EMCgWeaponMultiValueMember.Get().Create("IsFirePressed");
        public static readonly FECgWeaponMultiValueMember Last_IsFirePressed = EMCgWeaponMultiValueMember.Get().Create("Last_IsFirePressed");
        public static readonly FECgWeaponMultiValueMember IsFirePressed_StartTime = EMCgWeaponMultiValueMember.Get().Create("IsFirePressed_StartTime");
        public static readonly FECgWeaponMultiValueMember IsFireReleased_StartTime = EMCgWeaponMultiValueMember.Get().Create("IsFireReleased_StartTime");
        public static readonly FECgWeaponMultiValueMember Fire_StartTime = EMCgWeaponMultiValueMember.Get().Create("Fire_StartTime");
        // Charge
        public static readonly FECgWeaponMultiValueMember AllowChargeFire = EMCgWeaponMultiValueMember.Get().Create("AllowChargeFire");
        public static readonly FECgWeaponMultiValueMember MaxChargeFireTime = EMCgWeaponMultiValueMember.Get().Create("MaxChargeFireTime");
        // Spread
        public static readonly FECgWeaponMultiValueMember DoSpread = EMCgWeaponMultiValueMember.Get().Create("DoSpread");
        public static readonly FECgWeaponMultiValueMember MinSpread = EMCgWeaponMultiValueMember.Get().Create("MinSpread");
        public static readonly FECgWeaponMultiValueMember MaxSpread = EMCgWeaponMultiValueMember.Get().Create("MaxSpread");
        public static readonly FECgWeaponMultiValueMember SpreadAddedPerShot = EMCgWeaponMultiValueMember.Get().Create("SpreadAddedPerShot");
        public static readonly FECgWeaponMultiValueMember SpreadRecoveryRate = EMCgWeaponMultiValueMember.Get().Create("SpreadRecoveryRate");
        public static readonly FECgWeaponMultiValueMember FiringSpreadRecoveryDelay = EMCgWeaponMultiValueMember.Get().Create("FiringSpreadRecoveryDelay");
        public static readonly FECgWeaponMultiValueMember CurrentBaseSpread = EMCgWeaponMultiValueMember.Get().Create("CurrentBaseSpread");
        public static readonly FECgWeaponMultiValueMember CurrentSpread = EMCgWeaponMultiValueMember.Get().Create("CurrentSpread");
        public static readonly FECgWeaponMultiValueMember LastSpreadFireTime = EMCgWeaponMultiValueMember.Get().Create("LastSpreadFireTime");
        // Anim
        public static readonly FECgWeaponMultiValueMember LoopFireAnim = EMCgWeaponMultiValueMember.Get().Create("LoopFireAnim");
        public static readonly FECgWeaponMultiValueMember DoScaleFireAnim = EMCgWeaponMultiValueMember.Get().Create("DoScaleFireAnim");
        // Sound
        public static readonly FECgWeaponMultiValueMember LoopFireSound = EMCgWeaponMultiValueMember.Get().Create("LoopFireSound");
        // Hitscan
        public static readonly FECgWeaponMultiValueMember IsHitscan = EMCgWeaponMultiValueMember.Get().Create("IsHitscan");
        public static readonly FECgWeaponMultiValueMember DoesHitscanUseRadius = EMCgWeaponMultiValueMember.Get().Create("DoesHitscanUseRadius");
        public static readonly FECgWeaponMultiValueMember DoesHitscanSimulateProjectileDuration = EMCgWeaponMultiValueMember.Get().Create("DoesHitscanSimulateProjectileDuration");
        public static readonly FECgWeaponMultiValueMember ObstaclePenetrations = EMCgWeaponMultiValueMember.Get().Create("ObstaclePenetrations");
        public static readonly FECgWeaponMultiValueMember PawnPenetrations = EMCgWeaponMultiValueMember.Get().Create("PawnPenetrations");
        // Reload
        public static readonly FECgWeaponMultiValueMember ReloadTime = EMCgWeaponMultiValueMember.Get().Create("ReloadTime");
        public static readonly FECgWeaponMultiValueMember AllowRechargeAmmo = EMCgWeaponMultiValueMember.Get().Create("AllowRechargeAmmo");
        public static readonly FECgWeaponMultiValueMember AllowRechargeAmmoDuringFire = EMCgWeaponMultiValueMember.Get().Create("AllowRechargeAmmoDuringFire");
        public static readonly FECgWeaponMultiValueMember RechargeSecondsPerAmmo = EMCgWeaponMultiValueMember.Get().Create("RechargeSecondsPerAmmo");
        public static readonly FECgWeaponMultiValueMember RechargeStartupDelay = EMCgWeaponMultiValueMember.Get().Create("RechargeStartupDelay");
    }

    public sealed class FECgWeaponRoutine : ECgEnum_byte
    {
        public FECgWeaponRoutine(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgWeaponRoutineEqualityComparer : IEqualityComparer<FECgWeaponRoutine>
    {
        public bool Equals(FECgWeaponRoutine lhs, FECgWeaponRoutine rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgWeaponRoutine x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgWeaponRoutine : ECgEnumMap<FECgWeaponRoutine, byte>
    {
        private static EMCgWeaponRoutine _Instance;
        public static EMCgWeaponRoutine Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgWeaponRoutine();
                }
                return _Instance;
            }
        }

        public static EMCgWeaponRoutine Get()
        {
            return Instance;
        }
    }

    public static class ECgWeaponRoutine
    {
        public static readonly FECgWeaponRoutine PlayAnimation_Reload_Internal = EMCgWeaponRoutine.Get().Create("PlayAnimation_Reload_Internal");
        public static readonly FECgWeaponRoutine StartChargeFire_Internal = EMCgWeaponRoutine.Get().Create("StartChargeFire_Internal");
        public static readonly FECgWeaponRoutine FireWeapon_Internal = EMCgWeaponRoutine.Get().Create("FireWeapon_Internal");
    }

    #endregion // Enums

    public class CgWeapon : MonoBehaviour
    {
        #region "Property"

        #endregion // Property

        // Use this for initialization
        void Start()
        {

        }
    }
}
