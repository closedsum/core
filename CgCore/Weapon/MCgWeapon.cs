namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public sealed class FECgWeaponMultiValueMember : FECgEnum_byte
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

    public class EMCgWeaponMultiValueMember : TCgEnumMap<FECgWeaponMultiValueMember, byte>
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

    public sealed class FECgWeaponRoutine : FECgEnum_byte
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

    public class EMCgWeaponRoutine : TCgEnumMap<FECgWeaponRoutine, byte>
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

    #region "Cache"

    namespace ECgWeaponCached
    {
        public static class Str
        {
            // Functions
            public static readonly string PlayAnimation_Reload_Internal = "PlayAnimation_Reload_Internal";
            public static readonly string StartChargeFire_Internal = "StartChargeFire_Internal";
            public static readonly string FireWeapon_Internal = "FireWeapon_Internal";
            // Stop Messages
            public static readonly string Stop_StartChargeFire_Internal = "Stop StartChargeFire_Internal";
            public static readonly string Stop_FireWeapon_Internal = "Stop FireWeapon_Internal";
        }
    }

    #endregion // Cache

    public class MCgWeapon : MonoBehaviour, ICgObject
    {
        #region "Property"

        // bool
        public sealed class FRef_bool : TCgProperty_TListRef_bool { }
        public sealed class FTMap_bool : TCgProperty_TMap_bool<FECgWeaponFireMode> { }
        public sealed class FTMapRef_bool : TCgProperty_TMapRef_bool<FECgWeaponFireMode> { }
        // byte
        public sealed class FTMap_byte : TCgIntegralType_TMap_byte<FECgWeaponFireMode> { }
        public sealed class FTMapRef_byte : TCgIntegralType_TMapRef_byte<FECgWeaponFireMode> { }
        // int
        public sealed class FRef_int : TCgIntegralType_TListRef_int { }
        public sealed class FTMapRef_int : TCgIntegralType_TMapRef_int<FECgWeaponFireMode> { }
        // float
        public sealed class FRef_float : TCgIntegralType_TListRef_float { }
        public sealed class FTMap_float : TCgIntegralType_TMap_float<FECgWeaponFireMode> { }
        public sealed class FTMapRef_float : TCgIntegralType_TMapRef_float<FECgWeaponFireMode> { }

        #endregion // Property

        #region "Constants"

        public static readonly int DATA_VALUE = 0;
        public static readonly int CUSTOM_VALUE = -1;
        public static readonly int PROJECTILE_FIRE_PAYLOAD_POOL_SIZE = 64;

        public static readonly int EMPTY = 0;
        public static readonly int FIRST = 0;

        public static readonly string NAME_None = "";

        #endregion // Constants

        #region "Data Members"

            #region "Interface"

        private ulong _UniqueObjectId;
        public ulong UniqueObjectId
        {
            get { return _UniqueObjectId; }
            set { _UniqueObjectId = value; }
        }

            #endregion // Interface

            #region "Data"

        public MCgData_Weapon MyData_Weapon;

        public sealed class FOnApplyDataWeapon : TCgMulticastDelegate_OneParam<byte> { }
        public FOnApplyDataWeapon OnApplyDataWeapon_Event;

            #endregion // Data

            #region "Owner"

        protected MonoBehaviour MyOwner;
        protected MCgPawn MyPawn;

        public FECgWeaponOwner MyOwnerType;
        public FECgWeaponOwner PawnWeaponOwner;

            #endregion // Owner

            #region "State"

        public byte WeaponIndex;

        public FECgWeaponSlot WeaponSlot;

        public FECgWeaponState CurrentState;
        public FECgWeaponState LastState;

        public FECgWeaponState IdleState;

        public FECgWeaponFireMode PrimaryFireMode;

        public sealed class FOnTick : TCgMulticastDelegate_TwoParams<FECgWeaponSlot, float> { }
        public FOnTick OnTick_Event;

            #endregion // State

            #region "Animation"

        public FECgWeaponAnim ReloadAnim;

        public FCgRoutine PlayAnimation_Reload_Internal_Routine;

            #endregion // Animation

            #region "Sound"

        public FECgWeaponSound FireSound;

            #endregion // Sound

            #region "Equip / UnEqup"

        public bool bEquipped;

        public sealed class FOnEquip : TCgMulticastDelegate_FourParams<FECgWeaponSlot, int, int, int> { }
        public FOnEquip OnEquip_Event;

        public sealed class FOnUnEquip : TCgMulticastDelegate_OneParam<FECgWeaponSlot> { }
        public FOnUnEquip OnUnEquip_Event;

        public bool bDoingEquipTransition;

            #endregion // Equip / UnEquip

            #region "Firing"

        public FECgData_Weapon_FireMode FiringDataFireMode;

        public FECgWeaponState FiringState;

                #region "Ammo"

        public FRef_int MaxAmmo;

        public int CurrentAmmo;

        public FRef_int CurrentAmmoHandle;

        public sealed class FOnChange_CurrentAmmo : TCgMulticastDelegate_FourParams<FECgWeaponSlot, int, int, int> { }
        public FOnChange_CurrentAmmo OnChange_CurrentAmmo_Event;

        public bool bUnlimitedAmmo;

        public sealed class FOnConsumeAmmo : TCgMulticastDelegate_OneParam<string> { }
        public FOnConsumeAmmo OnConsumeAmmo_Event;

        public sealed class FOnConsumeAmmoItem : TCgMulticastDelegate_TwoParams<string, List<FCgItem>> { }
        public FOnConsumeAmmoItem OnConsumeAmmoItem_Event;

                #endregion // Ammo

        public FTMapRef_byte ProjectilesPerShot;

        public FTMap_byte CurrentProjectilePerShotIndex;

        public FTMapRef_bool DoFireOnRelease;
        public FTMapRef_bool IsFullAuto;

        public FTMapRef_float TimeBetweenProjectilesPerShot;
        public FTMapRef_float TimeBetweenShots;
        public FTMapRef_float TimeBetweenAutoShots;

        public FTMap_bool IsFirePressed;
        public FTMap_bool Last_IsFirePressed;

        public FTMap_float IsFirePressed_StartTime;
        public FTMap_float IsFireReleased_StartTime;
        public FTMap_float Fire_StartTime;

                #region "Charge"
        
        public FECgWeaponAnim ChargeFireStartAnim;
        public FECgWeaponAnim ChargeFireLoopAnim;

        public FTMapRef_bool AllowChargeFire;

        public bool bPerformingChargeFire;

        public FTMapRef_float MaxChargeFireTime;

        public FCgRoutine StartChargeFire_Internal_Routine;

        public float ChargeFire_StartTime;

                #endregion // Charge

                #region "Spread"

        public FECgData_Weapon_FireMode AimingDataFireMode;

        FTMapRef_bool DoSpread;
        FTMapRef_float MinSpread;
        FTMapRef_float MaxSpread;
        FTMapRef_float SpreadAddedPerShot;
        FTMapRef_float SpreadRecoveryRate;
        FTMapRef_float FiringSpreadRecoveryDelay;
        FTMapRef_float MovingSpreadBonus;

        FTMap_float CurrentBaseSpread;
        FTMap_float CurrentSpread;
        FTMap_float LastSpreadFireTime;

                #endregion // Spread

                // Anim
        public FECgData_Weapon_FireMode AnimationDataFireMode;

        public FECgWeaponAnim FireAnim;

        public FTMapRef_bool LoopFireAnim;
        public FTMapRef_bool DoScaleFireAnim;

                // Sound
        public FECgData_Weapon_FireMode SoundsDataFireMode;

        public FTMapRef_bool LoopFireSound;

        public int FireCount;

        public FCgProjectileFirePayload[] ProjectileFirePayloads;

        public int ProjectileFirePayloadPoolIndex;

        public FCgRoutine FireWeapon_Internal_Routine;

                #region "Hitscan"

        public FTMapRef_bool IsHitscan;
        public FTMapRef_bool DoesHitscanUseRadius;
        public FTMapRef_bool DoesHitscanSimulateProjectileDuration;

        public FTMapRef_int ObstaclePenetrations;

        public FTMapRef_int PawnPenetrations;

                #endregion // Hitscan

            #endregion // Firing

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {
        }

        public virtual void Init()
        {
            MCgGameInstance.Get().RegisterUniqueObject(this);

            ProjectileFirePayloads = new FCgProjectileFirePayload[PROJECTILE_FIRE_PAYLOAD_POOL_SIZE];

            for (int i = 0; i < PROJECTILE_FIRE_PAYLOAD_POOL_SIZE; ++i)
            {
                ProjectileFirePayloads[i] = new FCgProjectileFirePayload();
            }
        }

        #region "Members"

        public void InitMultiValueMember<ValueType>(TCgProperty_TMap<FECgWeaponFireMode, ValueType> member, ValueType defaultValue) 
            where ValueType : struct, IConvertible
        {
            member.SetDefaultValue(defaultValue);

            int count = EMCgWeaponFireMode.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                member.Init(EMCgWeaponFireMode.Get().GetEnumAt(i));
            }
        }

        public void InitMultiRefValueMembers<ValueType>(TCgProperty_TMapRef<FECgWeaponFireMode, ValueType> member, ValueType defaultValue)
            where ValueType : struct, IConvertible
        {
            member.SetDefaultValue(defaultValue);

            int count = EMCgWeaponFireMode.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                member.Init(EMCgWeaponFireMode.Get().GetEnumAt(i));
            }
        }

        public virtual void InitMultiValueMembers() { }

            #region "Set"

        public void SetMemberRefValue<ValueType>(TCgProperty_TListRef<ValueType> member, string memberName)
            where ValueType : struct, IConvertible
        {
            /*
            ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

		    Member.ResetValues();

		    for (uint8 I = 0; I < Member.Num(); ++I)
		    {
			    T* DataMember = UCsCommon_Load::GetObjectMember<T>(Data_Weapon, Data_Weapon->GetClass(), MemberName, GetObjectMember_Internal);

			    if (I == 0)
				    Member.Set(*DataMember);
			    Member.Set(I, DataMember);
		    }
            */
        }

        public void SetMemberMultiValue<ValueType>(TCgProperty_TMap<FECgWeaponFireMode, ValueType> member, ValueType value)
            where ValueType : struct, IConvertible
        {
            member.ResetValues();

            int count = EMCgWeaponFireMode.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                if (i == 0)
                    member.Set(value);
                member.Set(EMCgWeaponFireMode.Get().GetEnumAt(i), value);
            }
        }

        public void SetMemberMultiRefValue<ValueType>(TCgProperty_TMapRef<FECgWeaponFireMode, ValueType> member, FECgData_Weapon_FireMode fireModeMember, string memberName)
            where ValueType : struct, IConvertible
        {
            /*
		    ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();

            Member.ResetValues();

		    const FString& StructName = FireModeMember.Name;

		    const int32& Count = EMCsWeaponFireMode::Get().Num();

		    for (int32 I = 0; I<Count; ++I)
		    {
			    const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

            void* Struct = UCsCommon_Load::GetStructMember<void>(Data_Weapon->GetFireModeStruct(FireMode), Data_Weapon->GetFireModeScriptStruct(), StructName, GetStructMember_Internal);
            UScriptStruct* ScriptStruct = UCsCommon_Load::GetScriptStructMember(Data_Weapon->GetFireModeStruct(FireMode), Data_Weapon->GetFireModeScriptStruct(), StructName, GetScriptStructMember_Internal);
            ValueType* StructMember = UCsCommon_Load::GetStructMember<ValueType>(Struct, ScriptStruct, MemberName, GetStructMember_Internal);

			    if (I == 0)
				    Member.Set(* StructMember);
			    Member.Set(FireMode, StructMember);
		    }
            */
        }

        #endregion // Set

        #endregion // Members

        #region "Data"

        public MCgData_Weapon GetMyData_Weapon()
        {
            return MyData_Weapon;
        }

        public T GetMyData_Weapon<T>()
            where T : MCgData_Weapon
        {
            return (T)GetMyData_Weapon();
        }

        public MCgData_Projectile GetMyData_Projectile(FECgWeaponFireMode fireMode, bool isCharged = false)
        {
            return GetMyData_Weapon<MCgData_ProjectileWeapon>().GetData_Projectile(fireMode, isCharged);
        }

        public T GetMyData_Projectile<T>(FECgWeaponFireMode fireMode, bool isCharged)
            where T : MCgData_Projectile
        {
            return (T)GetMyData_Projectile(fireMode, isCharged);
        }

        #endregion // Data

        #region "Managers"

        public FCgManager_Inventory GetMyManager_Inventory()
        {
            return null;
        }

        public T GetMyManager_Inventory<T>()
            where T : FCgManager_Inventory
        {
            return (T)GetMyManager_Inventory();
        }

        #endregion // Managers

        #region "Routines"

        public virtual bool AddRoutine(FCgRoutine routine)
        {
            return false;
        }

        public virtual bool RemoveRoutine(FCgRoutine routine)
        {
            return false;
        }

        #endregion // Routines

        #region "Owner"

        public virtual void SetMyOwner(MonoBehaviour myOwner)
        {
            MyOwner = myOwner;
        }

        public MonoBehaviour GetMyOwner()
        {
            return MyOwner;
        }

        /*
        public T GetMyOwner<T>()
            where T : GameObject
        {
            return (T)GetMyOwner();
        }
        */

        public virtual bool IsValidOwnerTypeInGame()
        {
            return false;
        }

        public virtual void SetMyPawn(MCgPawn myPawn)
        {
            SetMyOwner(myPawn);

            MyPawn = myPawn;
            //Instigator = myPawn;

            //SetOwner(myPawn);
        }

        public MCgPawn GetMyPawn()
        {
            return MyPawn;
        }

        public T GetMyPawn<T>()
            where T : MCgPawn
        {
            return (T)GetMyPawn();
        }

        public virtual ECgViewType GetCurrentViewType()
        {
            /*
#if WITH_EDITOR
	        // In Editor Preview Window
	        if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			        return AnimInstance->CurrentViewType;
	        }
	        // In Game
	        else
#endif // #if WITH_EDITOR
            {
                if (ACsPawn * Pawn = GetMyPawn())
                    return UCsCommon::IsLocalPawn(GetWorld(), Pawn) ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;
            }
            */
            return ECgViewType.MAX;
        }

        #endregion // Owner

        #region "State"

        public virtual void OnTick(float deltaTime)
        {
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
            /*
            {
                float timeElapsed = Time.timeSinceLevelLoad;
                int count         = EMCgWeaponFireMode.Get().Count;

                // Spread
                for (int i = 0; i < count; ++i)
                {
                    FECgWeaponFireMode fireMode = EMCgWeaponFireMode.Get().GetEnumAt(i);

                    if (DoSpread[fireMode])
                    {
                        // Firing
                        if (TimeSeconds - LastSpreadFireTime[FireMode] > FiringSpreadRecoveryDelay[FireMode])
                        {
                            CurrentBaseSpread.Set(FireMode, FMath::Max(CurrentBaseSpread[FireMode] - (SpreadRecoveryRate.GetEX(FireMode) * DeltaSeconds), MinSpread.GetEX(FireMode)));
                        }
                        CurrentSpread.Set(FireMode, FMath::Clamp(CurrentBaseSpread[FireMode], 0.f, MaxSpread.GetEX(FireMode)));
                    }
                }
            }

	        OnTick_Event.Broadcast(WeaponSlot, deltaTime);

            //OnTick_HandleStates();

            Last_IsFirePressed = IsFirePressed;
            */
        }

        public void OnTick_HandleStates()
        {

        }

        public bool CanFire(FECgWeaponFireMode fireMode)
        {
            return false;
        }

        public bool CanFire_Auto(FECgWeaponFireMode fireMode)
        {
            return false;
        }

        public void CheckState_Idle()
        {
        }

        public void OnEnable()
        {
        }

        public virtual void Disable()
        {

        }

        public void Reset()
        {
        }
        
        public virtual void Show()
        {

        }

        public virtual void Hide()
        {

        }

        #endregion // State

        #region "Animation"

        public virtual void PlayAnimation(FECgWeaponFireMode fireMode, FECgWeaponAnim animType, int index = 0)
        {

        }

        public virtual void PlayAnimation_Reload()
        {

        }

        public static IEnumerator PlayAnimation_Reload_Internal()
        {
            yield return null;
        }

        public bool PlayAnimation_Reload_StopCondition(FCgRoutine r)
        {
            MCgWeapon mw = (MCgWeapon)r.Owner.Get();

#if UNITY_EDITOR
            /*
            // In Editor Preview Window
            if (UCsCommon::IsPlayInEditorPreview(mw->GetWorld()) &&
                mw)
            {
                if (!mw->GetMyOwner())
                    r->End(ECsCoroutineEndReason::StopCondition);
            }
            // In Game
            else
            */
#endif // #if UNITY_EDITOR
            {
                if (mw == null)
                   return true;
            }
            return false;
        }

        public virtual float GetAnimationLength(FECgWeaponFireMode fireMode, FECgWeaponAnim animType, int index = 0)
        {
            return 0.0f;
        }

        public virtual void StopAnimation(FECgWeaponFireMode fireMode, FECgWeaponAnim AnimType, int index = 0)
        {
        }

        #endregion // Animation

        #region "Sound"

        public virtual MonoBehaviour GetSoundParent()
        {
            return null;
        }

        public virtual MCgSound GetSound(FECgWeaponSound soundType)
        {
            return null;
        }

        public virtual void PlaySound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType)
        {
            MCgData_ProjectileWeapon data = GetMyData_Weapon<MCgData_ProjectileWeapon>();
            ECgViewType viewType          = GetCurrentViewType();

            data.PlaySound(viewType, fireMode, soundType, GetMyOwner(), GetSoundParent());
        }

        public virtual void StopSound(FECgWeaponFireMode fireMode, FECgWeaponSound soundType)
        {
            MCgData_ProjectileWeapon data = GetMyData_Weapon<MCgData_ProjectileWeapon>();
            ECgViewType viewType          = GetCurrentViewType();

            data.StopSound(viewType, fireMode, soundType, GetMyOwner(), GetSoundParent());
        }

        #endregion // Sound

        #region "Equip / UnEquip"

        public virtual void Equip()
        {
            bEquipped = true;

            //OnEquip_Event.Broadcast(WeaponSlot);
        }

        public virtual void UnEquip()
        {
            bEquipped = false;

            OnUnEquip_Event.Broadcast(WeaponSlot);
        }

        public virtual bool CanUnEquip()
        {
            if (!bEquipped)
                return false;
            if (bDoingEquipTransition)
                return false;

            int count = EMCgWeaponFireMode.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                FECgWeaponFireMode fireMode = EMCgWeaponFireMode.Get().GetEnumAt(i);

                //if (CurrentProjectilePerShotIndex[fireMode] < ProjectilesPerShot[fireMode] - 1)
                //    return false;
            }
            return true;
        }

        #endregion // Equip / UnEquip

        #region "Firing"

            #region "Ammo"

        public virtual int GetMaxAmmo(int index)
        {
            return MaxAmmo.Get(index);
        }

        public virtual void OnChange_CurrentAmmo(int value)
        {
            OnChange_CurrentAmmo_Event.Broadcast(WeaponSlot, CurrentAmmo, GetMaxAmmo(DATA_VALUE), GetAmmoReserve(DATA_VALUE, PrimaryFireMode, false));
        }

        public virtual void IncrementCurrentAmmo(int index)
        {
#if UNITY_EDITOR
            /*
	        if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        if (CurrentAmmo < GetMaxAmmo(Index))
			        ++CurrentAmmo;
	        }
	        else
            */
#endif // #if UNITY_EDITOR
            if (GetMyData_Weapon().UseInventory())
            {
                // TODO: Later might need a way to store the LastFireMode used
                FCgManager_Inventory manager_inventory = GetMyManager_Inventory();

                string shortCode = GetAmmoShortCode(PrimaryFireMode, false);

                if (shortCode == "")
                {
                    MCgData_Projectile data_projectile = GetMyData_Projectile(PrimaryFireMode, false);

                    FCgDebug.LogWarning("MCsWeapon.IncrementCurrentAmmo: No ItemShortCode set for Projectile: " + data_projectile.ShortCode);
                }

                int ammoReserve = 0;// manager_inventory.GetItemCount(shortCode);

                if (CurrentAmmo < GetMaxAmmo(index) &&
                    CurrentAmmo < ammoReserve)
                {
                    ++CurrentAmmo;
                }
            }
            else
            {
                if (CurrentAmmo < GetMaxAmmo(index))
                    ++CurrentAmmo;
            }
            CurrentAmmoHandle.Resolve();
        }

        public virtual void ResetCurrentAmmo(int index)
        {
#if UNITY_EDITOR
            /*
            // In Editor Preview Window
            if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        CurrentAmmo = GetMaxAmmo(Index);
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            if (GetMyData_Weapon().UseInventory())
            {
                // TODO: Later might need a way to store the LastFireMode used
                FCgManager_Inventory manager_inventory = GetMyManager_Inventory();

                string shortCode = GetAmmoShortCode(PrimaryFireMode, false);

                if (shortCode == NAME_None)
                {
                    MCgData_Projectile data_projectile = GetMyData_Projectile(PrimaryFireMode, false);

                    FCgDebug.LogWarning("ACsWeapon::ResetCurrentAmmo: No ItemShortCode set for Projectile: " + data_projectile.ShortCode);
                }

                int ammoReserve = 0;// manager_inventory->GetItemCount(shortCode);
                int maxAmmo     = GetMaxAmmo(index);

                CurrentAmmo = ammoReserve > maxAmmo ? maxAmmo : ammoReserve;
            }
            else
            {
                CurrentAmmo = GetMaxAmmo(index);
            }
            CurrentAmmoHandle.Resolve();
        }

        public virtual string GetAmmoShortCode(FECgWeaponFireMode fireMode, bool isCharged)
        {
            return GetMyData_Projectile<MCgData_Projectile>(fireMode, isCharged).GetItemShortCode();
        }

        public virtual int GetAmmoReserve(int index, FECgWeaponFireMode fireMode, bool isCharged)
        {
#if UNITY_EDITOR
            /*
            if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        return GetMaxAmmo(Index);
	        }
            */
#endif // #if UNITY_EDITOR

            if (GetMyData_Weapon().UseInventory())
            {
                FCgManager_Inventory manager_inventory = GetMyManager_Inventory();

                string shortCode = GetAmmoShortCode(fireMode, isCharged);

                if (shortCode == NAME_None)
                {
                    MCgData_Projectile data_projectile = GetMyData_Projectile(fireMode, isCharged);

                    FCgDebug.LogWarning("MCsWeapon.GetAmmoReserve: No ItemShortCode set for Projectile: " + data_projectile.ShortCode);
                }
                return 0;// manager_inventory.GetItemCount(shortCode);
            }
            return GetMaxAmmo(index);
        }

        public virtual void ConsumeAmmo(FECgWeaponFireMode fireMode, bool isCharged)
        {
            --CurrentAmmo;
            CurrentAmmoHandle.Resolve();

            if (GetMyData_Weapon().UseInventory())
            {
                MCgData_Projectile data_projectile  = GetMyData_Projectile<MCgData_Projectile>(PrimaryFireMode, false);
                string shortCode                    = data_projectile.GetItemShortCode();

                OnConsumeAmmo_Event.Broadcast(shortCode);
            }
        }

        public void ConsumeAmmoItem(FECgWeaponFireMode fireMode, bool isCharged, ref List<FCgItem> outItems)
        {
#if UNITY_EDITOR
            /*
            if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
		        return;
                */
#endif // #if UNITY_EDITOR

            if (GetMyData_Weapon().UseInventory())
            {
                FCgManager_Inventory manager_inventory  = GetMyManager_Inventory();
                MCgData_Projectile data_projectile      = GetMyData_Projectile<MCgData_Projectile>(fireMode, isCharged);
                string shortCode                        = data_projectile.GetItemShortCode();

                if (shortCode == NAME_None)
                {
                    FCgDebug.LogWarning("MCsWeapon.ConsumeAmmoItem: No ItemShortCode set for Projectile: " + data_projectile.ShortCode);
                }

                // Consume Item
                if (data_projectile.GetOnAllocateConsumeItem())
                {
                    //manager_inventory.ConsumeFirstItem(shortCode, outItems);
                }
                // Drop Item
                else
                if (data_projectile.GetOnAllocateDropItem())
                {
                    //manager_inventory.DropFirstItem(shortCode);
                }
                OnConsumeAmmoItem_Event.Broadcast(shortCode, outItems);
            }
        }

            #endregion // Ammo

        public virtual byte GetProjectilePerShot(FECgWeaponFireMode fireMode) { return ProjectilesPerShot.Get(fireMode); }
        public virtual float GetTimeBetweenProjectilesPerShot(FECgWeaponFireMode fireMode) { return TimeBetweenProjectilesPerShot.Get(fireMode); }
        public virtual float GetTimeBetweenShots(FECgWeaponFireMode fireMode) { return TimeBetweenShots.Get(fireMode); }
        public virtual float GetTimeBetweenAutoShots(FECgWeaponFireMode fireMode) { return TimeBetweenAutoShots.Get(fireMode); }

        public void SetIsFirePressed(FECgWeaponFireMode fireMode, bool value, bool doOnTick = false)
        {
            IsFirePressed.Set(fireMode, value);

            float timeElapsed = Time.timeSinceLevelLoad;

            if (value)
            {
                IsFirePressed_StartTime.Set(fireMode, timeElapsed);
            }
            else
            {
                IsFireReleased_StartTime.Set(fireMode, timeElapsed);
            }

#if UNITY_EDITOR
            /*
            // In Editor Preview Window
            if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	        {
		        if (DoOnTick)
			        OnTick(0.0f);
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            {
                if (doOnTick)
                    OnTick(0.0f);
            }
        }

            #region "Charge"

        public virtual float GetMaxChargeFireTime(FECgWeaponFireMode fireMode){ return MaxChargeFireTime.Get(fireMode); }

        public void HandleChargeFire()
        {
            if (bPerformingChargeFire)
                return;

            int count = EMCgWeaponFireMode.Get().Count;

            for (int i = 0; i < count; ++i)
            {
                FECgWeaponFireMode fireMode = EMCgWeaponFireMode.Get().GetEnumAt(i);

                if (AllowChargeFire[fireMode] &&
                    IsFirePressed[fireMode])
                {
                    StartChargeFire(fireMode);
                    return;
                }
            }
        }

        public void StartChargeFire(FECgWeaponFireMode fireMode)
        {
            bPerformingChargeFire = true;
            ChargeFire_StartTime  = Time.timeSinceLevelLoad;

            if (StartChargeFire_Internal_Routine != null)
                StartChargeFire_Internal_Routine.End(ECgCoroutineEndReason.UniqueInstance);

            FCgCoroutineScheduler scheduler = FCgCoroutineScheduler.Get();
            FCgCoroutinePayload payload     = scheduler.AllocatePayload();

            FECgCoroutineSchedule schedule = ECgCoroutineSchedule.Update;

            payload.Schedule = schedule;
            payload.Fiber   = StartChargeFire_Internal(this, fireMode);
            payload.Owner   = this;
            payload.Stop.Add(StartChargeFire_StopCondition);
            payload.Add         = AddRoutine;
            payload.Remove      = RemoveRoutine;
            payload.RoutineType = ECgWeaponRoutine.StartChargeFire_Internal.Value;
            payload.Name        = ECgWeaponCached.Str.StartChargeFire_Internal;

            FCgRoutine r = scheduler.Allocate(payload);

            r.AddMessage(ECgCoroutineMessage.Stop, ECgWeaponCached.Str.Stop_StartChargeFire_Internal);

            r.Ints[0] = fireMode.Value;

            scheduler.Start(schedule, r);
        }

        public static IEnumerator StartChargeFire_Internal(MCgWeapon mw, FECgWeaponFireMode fireMode)
        {
            // ChargeFireStat
            mw.PlayAnimation(fireMode, mw.ChargeFireStartAnim);

            float waitTime                  = mw.GetAnimationLength(fireMode, mw.ChargeFireStartAnim);
            float START_TO_LOOP_BLEND_TIME  = 0.1f;
            float timer                     = waitTime - START_TO_LOOP_BLEND_TIME;

            yield return timer;

            // ChargeFireLoop
            mw.PlayAnimation(fireMode, mw.ChargeFireLoopAnim);

            timer = Math.Max(mw.TimeBetweenShots.Max(), mw.TimeBetweenAutoShots.Max());

            yield return timer;
        }

        public bool StartChargeFire_StopCondition(FCgRoutine r)
        {
            MCgWeapon mw = r.Owner.Get<MCgWeapon>();

            FECgWeaponFireMode fireMode = EMCgWeaponFireMode.Get().GetEnumAt(r.Ints[0]);

#if UNITY_EDITOR
            /*
            // In Editor Preview Window
            if (mw && UCsCommon::IsPlayInEditorPreview(mw->GetWorld()))
	        {
		        if (!mw->GetMyOwner())
		        {
			        mw->StopAnimation(FireMode, mw->ChargeFireStartAnim);
			        mw->StopAnimation(FireMode, mw->ChargeFireLoopAnim);
			        r->End(ECsCoroutineEndReason::StopMessage);
		        }
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            {
                if (mw != null && mw.GetMyOwner() == null)
                {
                    mw.StopAnimation(fireMode, mw.ChargeFireStartAnim);
                    mw.StopAnimation(fireMode, mw.ChargeFireLoopAnim);
                    return true;
                }
            }
            return false;
        }

        public float GetChargeFireHeldTime()
        {
            return Time.timeSinceLevelLoad - ChargeFire_StartTime;
        }

        public float GetChargeFireHeldPercent(FECgWeaponFireMode fireMode)
        {
            return Mathf.Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(fireMode) / MaxChargeFireTime.GetEX(fireMode));
        }

        public float GetCurrentChargeFireHeldTime()
        {
            return bPerformingChargeFire ? Time.timeSinceLevelLoad - ChargeFire_StartTime : 0.0f;
        }

        public float GetCurrentChargeFireHeldPercent(FECgWeaponFireMode fireMode)
        {
            return bPerformingChargeFire ? Mathf.Clamp(GetChargeFireHeldTime(), 0.0f, MaxChargeFireTime.GetEX(fireMode) / MaxChargeFireTime.GetEX(fireMode)) : 0.0f;
        }

        public void StopChargeFire(FECgWeaponFireMode fireMode)
        {
            if (!AllowChargeFire[fireMode])
                return;

            bPerformingChargeFire = false;

            FCgCoroutineScheduler scheduler = FCgCoroutineScheduler.Get();

            scheduler.BroadcastMessage(ECgCoroutineSchedule.Update, ECgCoroutineMessage.Stop, ECgWeaponCached.Str.Stop_StartChargeFire_Internal, this);

            if (StartChargeFire_Internal_Routine != null)
                StartChargeFire_Internal_Routine.End(ECgCoroutineEndReason.UniqueInstance);

            StopAnimation(fireMode, ChargeFireStartAnim);
            StopAnimation(fireMode, ChargeFireLoopAnim);
        }

            #endregion // Charge

            #region "Spread"

        public virtual float GetMinSpread(FECgWeaponFireMode fireMode){ return MinSpread.Get(fireMode); }
        public virtual float GetMaxSpread(FECgWeaponFireMode fireMode){ return MaxSpread.Get(fireMode); }
        public virtual float GetSpreadAddedPerShot(FECgWeaponFireMode fireMode){ return SpreadAddedPerShot.Get(fireMode); }
        public virtual float GetSpreadRecoveryRate(FECgWeaponFireMode fireMode){ return SpreadRecoveryRate.Get(fireMode); }
        public virtual float GetFiringSpreadRecoveryDelay(FECgWeaponFireMode fireMode){ return FiringSpreadRecoveryDelay.Get(fireMode); }
        public virtual float GetMovingSpreadBonus(FECgWeaponFireMode fireMode){ return MovingSpreadBonus.Get(fireMode); }

            #endregion // Spread

        public virtual Vector3 GetFireWeaponStartLocation(FECgWeaponFireMode fireMode)
        {
            return Vector3.zero;
        }

        public virtual Vector3 GetFireWeaponStartDirection(FECgWeaponFireMode fireMode)
        {
            return Vector3.zero;
        }

        public FCgProjectileFirePayload AllocateProjectileFirePayload(FECgWeaponFireMode fireMode)
        {
            int count = PROJECTILE_FIRE_PAYLOAD_POOL_SIZE;

            for (int i = 0; i < count; ++i)
            {
                FCgProjectileFirePayload payload = ProjectileFirePayloads[ProjectileFirePayloadPoolIndex];

                if (!payload.bAllocated)
                {
                    payload.bAllocated = true;

                    payload.Time     = Time.timeSinceLevelLoad;
                    payload.RealTime = Time.realtimeSinceStartup;
                    payload.Frame    = 0;// UCsCommon::GetCurrentFrame(GetWorld());

                    payload.Location      = GetFireWeaponStartLocation(fireMode);
                    payload.Direction     = GetFireWeaponStartDirection(fireMode);
                    payload.ChargePercent = GetCurrentChargeFireHeldPercent(fireMode);

                    /*
                    ACsGameState* GameState		   = GetWorld()->GetGameState<ACsGameState>();
                    ACsPlayerState* MyPlayerState	   = Cast<ACsPlayerState>(MyPawn->PlayerState);
                    const uint8 MappingId			   = MyPlayerState ? MyPlayerState->PlayerData.AimAssistTargetMappingId : CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
                    ACsPlayerState* TargetPlayerState = GameState->GetPlayerState(MappingId);
                    ACsCharacter* TargetPawn		   = TargetPlayerState ? TargetPlayerState->GetMyPawn() : nullptr;

                    Cache->HomingTarget				   = TargetPawn;
                    Cache->HomingAccelerationMagnitude = 100.0f;

                    const FName BoneName = TargetPawn ? TargetPawn->GetMesh()->GetBoneName(MyPlayerState->PlayerData.AimAssistBoneIndex) : NAME_Name;

                    Cache->HomingBoneName = BoneName;
                    */
                    return payload;
                }
                ProjectileFirePayloadPoolIndex = (ProjectileFirePayloadPoolIndex + i) % count;
            }

            FCgDebug.LogError("MCgWeapon.AllocateProjectileFirePayload: Warning. Pool is exhausted. Using Oldest Active Projectile Fire Payload.");
            return null;
        }

        public void FireWeapon(FECgWeaponFireMode fireMode)
        {
            if (FireWeapon_Internal_Routine != null)
                FireWeapon_Internal_Routine.End(ECgCoroutineEndReason.UniqueInstance);

            FCgCoroutineScheduler scheduler = FCgCoroutineScheduler.Get();
            FCgCoroutinePayload payload     = scheduler.AllocatePayload();

            FECgCoroutineSchedule schedule = ECgCoroutineSchedule.Update;

            payload.Schedule = schedule;
            payload.Fiber   = FireWeapon_Internal(this, fireMode);
            payload.Owner   = this;
            payload.Stop.Add(FirewWeapon_StopCondition);
            payload.Add         = AddRoutine;
            payload.Remove      = RemoveRoutine;
            payload.RoutineType = ECgWeaponRoutine.FireWeapon_Internal.Value;
            payload.Name        = ECgWeaponCached.Str.FireWeapon_Internal;

            FCgRoutine r = scheduler.Allocate(payload);

            r.AddMessage(ECgCoroutineMessage.Stop, ECgWeaponCached.Str.Stop_FireWeapon_Internal);

            r.Ints[0] = fireMode.Value;

            scheduler.Start(schedule, r);
        }

        public static IEnumerator FireWeapon_Internal(MCgWeapon mw, FECgWeaponFireMode fireMode)
        {
#if UNITY_EDITOR
            /*
            // In Editor Preview Window
            if (UCsCommon::IsPlayInEditorPreview(w))
	        {
	        }
	        // In Game
	        else
            */
#endif // #if UNITY_EDITOR
            {
            }

            mw.StopChargeFire(fireMode);

            do
            {
                {
                    // Set the StartTime

                    // Play Fire Sound
                    if (!mw.LoopFireSound.Get(fireMode))
                        mw.PlaySound(fireMode, mw.FireSound);
                    // Play Fire Animation
                    if (!mw.LoopFireAnim.Get(fireMode))
                        mw.PlayAnimation(fireMode, mw.FireAnim);

#if UNITY_EDITOR
                    /*
                    // In Editor Preview Window
                    if (UCsCommon::IsPlayInEditorPreview(w))
			        {
				        mw->ConsumeAmmo(FireMode, false);
			        }
			        // In Game
			        else
                    */
#endif // #if UNITY_EDITOR
                    {
                        FCgProjectileFirePayload payload = mw.AllocateProjectileFirePayload(fireMode);

                        mw.ConsumeAmmoItem(fireMode, payload.ChargePercent > 0.0f, ref payload.Items);
                        mw.ConsumeAmmo(fireMode, payload.ChargePercent > 0.0f);

                        if (mw.IsHitscan.Get(fireMode))
                            mw.FireHitscan(fireMode, payload);
                        else
                            mw.FireProjectile(fireMode, payload);
                        ++(mw.FireCount);
                        payload.Reset();
                    }
                    mw.PlayMuzzleFlash(fireMode);

                    mw.CurrentProjectilePerShotIndex.Add(fireMode, 1);
                }

                if (mw.CurrentProjectilePerShotIndex[fireMode] < mw.ProjectilesPerShot[fireMode])
                {
                    yield return mw.TimeBetweenProjectilesPerShot[fireMode];
                }
            } while (mw.CurrentProjectilePerShotIndex[fireMode] < mw.ProjectilesPerShot[fireMode]);

            mw.CurrentState = mw.IdleState;
        }

        public bool FirewWeapon_StopCondition(FCgRoutine r)
        {
            MCgWeapon mw                = r.Owner.Get<MCgWeapon>();
            FECgWeaponFireMode fireMode = EMCgWeaponFireMode.Get().GetEnumAt(r.Ints[0]);

            if (mw != null &&
                !mw.GetMyOwner())
            {
                mw.StopAnimation(fireMode, mw.FireAnim);
                return true;
            }
            return false;
        }

        public virtual Vector3 GetOwnerRightVector()
        {
            return GetMyOwner().transform.right;
        }

        public virtual Vector3 GetFireProjectileDestination()
        {
            return Vector3.zero;
        }

        public virtual void FireProjectile(FECgWeaponFireMode fireMode, FCgProjectileFirePayload firePayload)
        {
            Vector3 realStart = firePayload.Location;
            Vector3 realDir   = firePayload.Direction;

            MCgData_ProjectileWeapon data_weapon = GetMyData_Weapon<MCgData_ProjectileWeapon>();
            MCgData_Projectile data_projectile   = data_weapon.GetData_Projectile(fireMode, firePayload.ChargePercent > 0.0f);
            bool useFakeProjectile               = data_weapon.UseFakeProjectile(fireMode);

            Vector3 realEnd = realStart;

            if (useFakeProjectile)
            {
                realEnd = GetFireProjectileDestination();
            }
            else
            {
                float MAX_RANGE = 30000.0f;
                realEnd         = realStart + MAX_RANGE * realDir;
            }

            ECgViewType viewType = GetCurrentViewType();
            Vector3 fakeStart    = GetMuzzleLocation(viewType, fireMode);
            Vector3 fakeDir      = (realEnd - fakeStart).normalized;

            // Spread
            if (DoSpread.Get(fireMode))
            {
                if (CurrentSpread.Get(fireMode) > 0.0f)
                {
                    // Real
                    float spreadPitch = UnityEngine.Random.Range(0.0f, 1.0f) * CurrentSpread.Get(fireMode); //RandStream.FRand() * CurrentSpread.Get(FireMode);
                    Vector3 right     = GetOwnerRightVector();
                    Vector3 dir       = FCgMath.RotateAngleAxis(realDir, spreadPitch, right);
                    float spreadRoll  = UnityEngine.Random.Range(0.0f, 1.0f) * 360.0f;
                    dir               = FCgMath.RotateAngleAxis(dir, spreadRoll, realDir);

                    realDir = dir;

                    // Fake
                    dir = FCgMath.RotateAngleAxis(fakeDir, spreadPitch, right);
                    dir = FCgMath.RotateAngleAxis(dir, spreadRoll, fakeDir);

                    fakeDir = dir;
                }
                CurrentBaseSpread.Set(fireMode, Mathf.Min(CurrentBaseSpread[fireMode] + SpreadAddedPerShot.GetEX(fireMode), MaxSpread.GetEX(fireMode)));
                LastSpreadFireTime.Set(fireMode, Time.timeSinceLevelLoad);
            }
            FireProjectile_Internal(fireMode, firePayload);

            // Allocate Projectiles
            ICgManager_Projectile manager_projectile = ICgManager_Projectile.Get();

            // Real
            FCgProjectilePayload payload = manager_projectile.AllocatePayload();

            payload.Relevance   = useFakeProjectile ? ECgProjectileRelevance.RealInvisible : ECgProjectileRelevance.RealVisible;
            payload.Instigator  = GetMyOwner();
            payload.Owner       = this;
            payload.Data        = data_projectile;

            firePayload.Location  = realStart;
            firePayload.Direction = realDir;

            payload.Set(firePayload);

            MCgProjectile realProjectile = manager_projectile.Fire(data_projectile.GetProjectileType(), payload);

            /*
            const bool IsLocalPawn = UCsCommon::IsLocalPawn(GetWorld(), GetMyPawn());

            if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
                 IsLocalPawn) ||
                CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
            {
                DrawFireProjectile(RealProjectile, RealStart, RealEnd);
            }
            */

            // Fake
            if (useFakeProjectile)
            {
                FCgProjectilePayload fakePayload = manager_projectile.AllocatePayload();

                fakePayload.Relevance   = ECgProjectileRelevance.Fake;
                fakePayload.Instigator  = GetMyOwner();
                fakePayload.Owner       = this;
                fakePayload.Data        = data_projectile;

                FCgProjectileFirePayload fakeFirePayload = AllocateProjectileFirePayload(fireMode);
                fakeFirePayload.Location                 = fakeStart;
                fakeFirePayload.Direction                = fakeDir;

                fakePayload.Set(fakeFirePayload);

                MCgProjectile fakeProjectile = manager_projectile.Fire(data_projectile.GetProjectileType(), fakePayload);

                fakeFirePayload.Reset();

                //realProjectile.FakeProjectile = FakeProjectile;

                /*
                if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
                    IsLocalPawn) ||
                    CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
                {
                    DrawFireProjectile(FakeProjectile, FakeStart, RealEnd);
                }
                */
            }
        }

        public virtual void FireProjectile_Internal(FECgWeaponFireMode fireMode, FCgProjectileFirePayload payload)
        {
        }

            #region "Hitscan"

        public virtual int GetObstaclePenetractions(FECgWeaponFireMode fireMode) { return ObstaclePenetrations.Get(fireMode); }

        public virtual int GetPawnPenetrations(FECgWeaponFireMode fireMode) { return PawnPenetrations.Get(fireMode); }

        public void GetFireHitscanIgnoreActors(ref List<MonoBehaviour> outObjects)
        {
            outObjects.Add(this);

            MonoBehaviour o = GetMyOwner();

            if (o != null)
                outObjects.Add(o);
        }

        public void GetFireHitscanIgnoreComponents(ref List<Component> outComponents){}

        public void FireHitscan(FECgWeaponFireMode fireMode, FCgProjectileFirePayload payload)
        {
	        //ACsPawn* Pawn					 = GetMyPawn();
	        //ACsPlayerState* MyPlayerState	 = Cast<ACsPlayerState>(Pawn->PlayerState);
	        MCgData_ProjectileWeapon data_weapon	= GetMyData_Weapon<MCgData_ProjectileWeapon>();
	        MCgData_Projectile data_projectile		= data_weapon.GetData_Projectile(fireMode, payload.ChargePercent > 0.0f);
	        FCgManager_Trace manager_trace			= FCgManager_Trace.Get();

	        //ECollisionChannel ProjectileCollision = Data_Projectile->GetCollisionObjectType();

	        Vector3 start	   = payload.Location;
	        Vector3 dir		   = payload.Direction;
	        float maxTraceRange = data_projectile.GetMaxRange();
	        Vector3 end		   = start + maxTraceRange * dir;

            // Ignored Actors
            List<MonoBehaviour> IgnoredObjects = new List<MonoBehaviour>();
	        GetFireHitscanIgnoreActors(ref IgnoredObjects);
		        // Ignored Components
	        List<Component> IgnoredComponents = new List<Component>();
	        GetFireHitscanIgnoreComponents(ref IgnoredComponents);

	        // See which Pawns we can hit and which we should ignore
	        List<MonoBehaviour> hittablePawns = new List<MonoBehaviour>();
	
	        bool allowInfinitePawnPenetrations	    = PawnPenetrations.GetEX(fireMode) < 0;
	        bool allowInfiniteObstaclePenetrations  = ObstaclePenetrations.GetEX(fireMode) < 0;

	        int recordedPawnPenetrations     = 0;
	        int recordedObstaclePenetrations = 0;
	        bool hitFound					   = true;

            FCgHitResult hitResult = null;

	        // Hit trace/ Hit simulation
	        while ((allowInfinitePawnPenetrations || recordedPawnPenetrations <= PawnPenetrations.GetEX(fireMode)) &&
		           (allowInfiniteObstaclePenetrations || recordedObstaclePenetrations <= ObstaclePenetrations.GetEX(fireMode)) &&
		            hitFound)
	        {
		        hitFound = false;

		        // Hitscan with cylinder
		        if (DoesHitscanUseRadius[fireMode])
		        {
			        // See if this line is close enough to hit any enemy characters
			        int hitPawnCount = hittablePawns.Count;

			        for (int i = hitPawnCount - 1; i >= 0; --i)
			        {
				        MCgPawn hitPawn				     = (MCgPawn)hittablePawns[i];
				        MCgData_Character data_character = hitPawn.GetMyData_Character();

				        float projectileRadius = data_projectile.GetSphereRadius();

                        // Head
                        FCgHeadCollision headCollision = data_character.GetHeadCollision();

                        if (headCollision != null)
				        {
					        float headRadius	= headCollision.Radius;
					        string bone	        = headCollision.Bone;
					        Vector3 offset	    = headCollision.Offset;

                            Vector3 headLocation = Vector3.zero;// hitPawn.GetMesh()->GetBoneLocation(BoneName) + Offset;
                            Vector3 headPoint    = Vector3.zero;//Vector3.ClosestPointOnSegment(HeadLocation, Start, End);

					        float distanceToHead = Vector3.Distance(headPoint, headLocation);

					        // Head is close enough to potential trace. Try tracing directly to the Head
					        if (distanceToHead < headRadius + projectileRadius)
					        {
						        float traceDist	    = 1.5f * (headLocation - start).magnitude;
						        Vector3 targetPoint = headLocation + traceDist * (headLocation - start);

						        FCgTraceRequest request = manager_trace.AllocateRequest();
                                /*
						        Request->Caller		= this;
						        Request->CallerId	= UniqueObjectId;
						        Request->Start		= Start;
						        Request->End		= TargetPoint;
						        Request->bAsync		= false;
						        Request->Type		= ECsTraceType::Line;
						        Request->Method		= ECsTraceMethod::Single;
						        Request->Query		= ECsTraceQuery::Channel;
						        Request->Channel	= ProjectileCollision;
						        Request->Params.bReturnPhysicalMaterial = true;
						        Request->Params.AddIgnoredActors(IgnoredActors);
						        Request->Params.AddIgnoredComponents(IgnoredComponents);
                                */
						        FCgTraceResponse response = manager_trace.Trace(request);

						        hitFound = response.bResult;

                                if (response.OutHitCount > EMPTY)
                                    hitResult = response.OutHits[FIRST];

						        response.Reset();

						        hittablePawns.RemoveAt(i);
						        break;
					        }
				        }

                        // Body
                        Vector3 bodyLocation = Vector3.zero;// hitPawn->GetCapsuleComponent()->GetComponentLocation();

				        Vector3 bodyLocationXY = new Vector3(bodyLocation.x, bodyLocation.y, 0.0f);
				        float bodyLocationZ    = bodyLocation.z;

                        Vector3 bodyPoint = Vector3.zero;// FMath::ClosestPointOnSegment(BodyLocation, Start, End);

				        Vector3 bodyPointXY = new Vector3(bodyPoint.x, bodyPoint.y, 0.0f);
				        float bodyPointZ    = bodyPoint.z;

				        float bodyXYDistFromLine = Vector3.Distance(bodyPointXY, bodyLocationXY);
				        float bodyZDistFromLine  = Mathf.Abs(bodyLocationZ - bodyPointZ);

                        float characterRadius = 0.0f;//hittablePawns[i]->GetCapsuleComponent()->GetScaledCapsuleRadius();
                        float characterHeight = 0.0f;//hittablePawns[i]->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

				        // Body is close enough to potential trace. Try tracing directly to the body
				        if (bodyXYDistFromLine < characterRadius + projectileRadius && bodyZDistFromLine < characterHeight + projectileRadius)
				        {
					        float traceDist     = 1.5f * (bodyLocation - start).magnitude;
					        Vector3 targetPoint = bodyLocation + traceDist * (bodyLocation - start);
					
					        FCgTraceRequest request = manager_trace.AllocateRequest();
                            /*
					        Request->Caller		= this;
					        Request->CallerId	= UniqueObjectId;
					        Request->Start		= Start;
					        Request->End		= TargetPoint;
					        Request->bAsync		= false;
					        Request->Type		= ECsTraceType::Line;
					        Request->Method		= ECsTraceMethod::Single;
					        Request->Query		= ECsTraceQuery::Channel;
					        Request->Channel	= ProjectileCollision;
					        Request->Params.bReturnPhysicalMaterial = true;
					        Request->Params.AddIgnoredActors(IgnoredActors);
					        Request->Params.AddIgnoredComponents(IgnoredComponents);
                            */
					        FCgTraceResponse response = manager_trace.Trace(request);

					        hitFound = response.bResult;

                            if (response.OutHitCount > EMPTY)
                                hitResult = response.OutHits[FIRST];

					        response.Reset();

					        hittablePawns.RemoveAt(i);
					        break;
				        }
			        }
		        }
		        // Hit NOT Found and NO Hitscan with cylinder
		        if (!hitFound || 
			        !DoesHitscanUseRadius[fireMode])
		        {
			        FCgTraceRequest request = manager_trace.AllocateRequest();
                    /*
			        Request->Caller		= this;
			        Request->CallerId	= UniqueObjectId;
			        Request->Start		= Start;
			        Request->End		= End;
			        Request->bAsync		= false;
			        Request->Type		= ECsTraceType::Line;
			        Request->Method		= ECsTraceMethod::Single;
			        Request->Query		= ECsTraceQuery::Channel;
			        Request->Channel	= ProjectileCollision;
			        Request->Params.bReturnPhysicalMaterial = true;
			        Request->Params.AddIgnoredActors(IgnoredActors);
			        Request->Params.AddIgnoredComponents(IgnoredComponents);
                    */
			        FCgTraceResponse response = manager_trace.Trace(request);

			        hitFound = response.bResult;

                    if (response.OutHitCount > EMPTY)
                        hitResult = response.OutHits[FIRST];

			        response.Reset();
                    /*
			        if ((CsCVarDrawLocalPlayerWeaponFireProjectile->GetInt() == CS_CVAR_DRAW &&
				        UCsCommon::IsLocalPawn(GetWorld(), GetMyPawn())) ||
				        CsCVarDrawWeaponFireProjectile->GetInt() == CS_CVAR_DRAW)
			        {
				        const float DrawTime = FMath::Max(TimeBetweenAutoShots.GetEX(FireMode), TimeBetweenShots.GetEX(FireMode));

				        DrawDebugLine(GetWorld(), Start, HitFound ? HitResult.Location : End, FColor::Red, false, DrawTime, 0, 1.0f);
			        }
                    */
		        }
		        // Hit IS Found. Check penetrations and modifiers
		        if (hitFound)
		        {
			        FCgManager_Damage manager_damage = FCgManager_Damage.Get();
			        FCgDamageEvent e			     = manager_damage.AllocateEvent();

			        e.Damage	  = data_projectile.GetDamage();
			        e.Instigator  = GetMyOwner();
			        e.Causer	  = this;
                    //Event->SetDamageType();
                    //Event->SetHitType();

                    e.HitInfo = hitResult;
			
			        //if (PawnToHit && UShooterStatics::IsOnSameTeam(GetWorld(), PawnToHit, MyPawn))
			        //{
			        //	continue;
			        //}

			        MCgPawn hitPawn = hitResult.GetTransform().GetComponent<MCgPawn>();

			        if (hitPawn != null)
				        ++recordedPawnPenetrations;
			        else
				        ++recordedObstaclePenetrations;

			        // Pawn
			        if (hitPawn)
			        {
				        //if (HitPawn->Role == ROLE_Authority)
				        {
					        // Apply Damage Modifiers
					        float damage = e.Damage;

					        // Location based Damage
					        damage *= data_weapon.GetLocationDamageModifier(fireMode, hitResult.BoneName);

					        // Damage Falloff
					        if (data_projectile.CanDamageFalloff())
						        damage *= data_projectile.GetDamageFalloff(hitResult.Distance);
					        // Damage Radial
					        //else
					        //if (data_projectile.CanDamageRadial())
                             //   damage = data_projectile.GetDamageRadial(hitResult.Location, hitPawn.GetActorLocation());

					        hitPawn.ApplyDamage(e);
				        }
			        }
			        // World
			        else
			        {
			        }
                    /*
			        // Play Impact FX / Sound
			        UPhysicalMaterial* PhysicalMaterial = HitResult.PhysMaterial.IsValid() ? HitResult.PhysMaterial.Get() : nullptr;

			        if (PhysicalMaterial)
			        {
				        // FX
				        Data_Projectile->GetData_Impact()->PlayImpactFX(GetWorld(), PhysicalMaterial->SurfaceType, nullptr, HitResult.Location, HitResult.ImpactNormal);
				        // Sound
				        Data_Projectile->GetData_Impact()->PlayImpactSound(GetWorld(), PhysicalMaterial->SurfaceType, nullptr, HitResult.Location);
			        }
                    */

			        //float TimeUntilHit = HitResult.Distance / Data_Projectile->InitialSpeed;

			        //if (DoesHitscanSimulateProjectileDuration.Get(FireMode))
			        //{
			        //	FakeProjectile->Lifetime = TimeUntilHit;
			        //}
			        //else
			        //{
			        //	if (ProjectileData->LeaveTrail)
			        //	{
			        //		FakeProjectile->Lifetime = ProjectileData->TrailDurationAfterHit;
			        //		FakeProjectile->TeleportTo(CurHit.ImpactPoint, FakeProjectile->GetActorRotation());
			        //		FakeProjectile->SpawnLocation = Origin;
			        //		float Length = FMath::Max(ProjectileData->TrailMeshLength, FVector::Dist(CurHit.ImpactPoint, Origin) / ProjectileData->TrailMeshLength);
			        //		FVector Scale = ProjectileData->Scale;
			        //		Scale.X *= Length;
			        //		FakeProjectile->TracerMeshComp->SetWorldScale3D(Scale);
			        //		FakeProjectile->StopMovement();
			        //		FakeProjectile->MeshComp->SetVisibility(false);
			        //		//FakeProjectile->DeActivate();
			        //	}
			        //	else
			        //	{
			        //		FakeProjectile->Lifetime = ProjectileData->Lifetime;
			        //	}
			        //}
			
			        //FakeProjectile->PlayImpactFX(CurHit.Location, CurHit);
			        e.Reset();
		        }
	        }
        }
            
            #endregion // Hitscan

        public virtual MonoBehaviour GetMuzzleFlashParent(ECgViewType viewType)
        {
            return null;
        }

        public virtual Vector3 GetMuzzleLocation(ECgViewType viewType, FECgWeaponFireMode fireMode)
        {
            return Vector3.zero;
        }

        public virtual void PlayMuzzleFlash(FECgWeaponFireMode fireMode)
        {
            /*
             * 	AICsManager_FX* Manager_FX = nullptr;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = GetMyOwner<UCsAnimInstance>())
			Manager_FX = AnimInstance->GetManager_FX();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();
		Manager_FX				 = GameState->Manager_FX;
	}

	ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();
	const TCsViewType ViewType			  = GetCurrentViewType();
	FCsFxElement* FX					  = Data_Weapon->GetMuzzleFX(ViewType, FireMode, CurrentProjectilePerShotIndex.Get(FireMode));

	if (!FX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsWeapon::PlayMuzzleFlash: Attempting to Play a NULL ParticleSystem."));
		return;
	}

	FCsFxPayload* Payload = Manager_FX->AllocatePayload();
	Payload->Set(FX);
	Payload->Owner = GetMyPawn();
	Payload->Parent = GetMuzzleFlashParent(ViewType);

	Manager_FX->Play(Payload);
    */
        }

        #endregion // Firing
    }
}
