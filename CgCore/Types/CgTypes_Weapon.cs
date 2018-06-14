﻿namespace CgCore
{
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
