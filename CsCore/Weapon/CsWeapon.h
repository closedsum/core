// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Item.h"
#include "Common/CsCommon_Load.h"
#include "Data/CsData_ProjectileWeapon.h"
#include "CsWeapon.generated.h"

// Data
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_OnApplyDataWeapon, const FECsWeaponSlot&, WeaponSlot);
// State
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWeapon_OnTick, const FECsWeaponSlot&, WeaponSlot, const float&, DeltaSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_Override_CheckStateIdle, const FECsWeaponSlot&, WeaponSlot);
// Ammo

	// OnChangeCurrentAmmo
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBindableDynEvent_CsWeapon_OnChange_CurrentAmmo, const FECsWeaponSlot&, WeaponSlot, const int32&, Ammo, const int32&, MaxAmmo, const int32&, AmmoReserve);
	// OnConsumeAmmo
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_OnConsumeAmmo, const FName&, ShortCode);
	// OnConsumeAmmoItem
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsWeapon_OnConsumeAmmoItem, const FName&, const TArray<FCsItem*>&);
// Firing
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWeapon_Override_FireWeapon, const FECsWeaponSlot&, WeaponSlot, const FECsWeaponFireMode&, FireMode);
// Reload
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWeapon_OnChange_bReloading, const FECsWeaponSlot&, WeaponSlot, bool, Value);
// Equip
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBindableDynEvent_CsWeapon_OnEquip, const FECsWeaponSlot&, WeaponSlot, const int32&, Ammo, const int32&, MaxAmmo, const int32&, AmmoReserve);
// UnEquip
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_OnUnEquip, const FECsWeaponSlot&, WeaponSlot);

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponMultiValueMember : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponMultiValueMember() {}
	FECsWeaponMultiValueMember(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponMultiValueMember(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponMultiValueMember() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponMultiValueMember& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponMultiValueMember : public TCsEnumStructMap<FECsWeaponMultiValueMember, uint8>
{
protected:
	EMCsWeaponMultiValueMember() {}
	EMCsWeaponMultiValueMember(const EMCsWeaponMultiValueMember &) = delete;
	EMCsWeaponMultiValueMember(EMCsWeaponMultiValueMember &&) = delete;
public:
	~EMCsWeaponMultiValueMember() {}
private:
	static EMCsWeaponMultiValueMember* Instance;

public:
	static EMCsWeaponMultiValueMember& Get();
};

namespace ECsWeaponMultiValueMember
{
	// Scope
	extern CSCORE_API const FECsWeaponMultiValueMember MaxAmmo;
	extern CSCORE_API const FECsWeaponMultiValueMember ProjectilesPerShot;
	extern CSCORE_API const FECsWeaponMultiValueMember CurrentProjectilePerShotIndex;
	extern CSCORE_API const FECsWeaponMultiValueMember DoFireOnRelease;
	extern CSCORE_API const FECsWeaponMultiValueMember IsFullAuto;
	extern CSCORE_API const FECsWeaponMultiValueMember TimeBetweenProjectilesPerShot;
	extern CSCORE_API const FECsWeaponMultiValueMember TimeBetweenShots;
	extern CSCORE_API const FECsWeaponMultiValueMember TimeBetweenAutoShots;
	extern CSCORE_API const FECsWeaponMultiValueMember IsFirePressed;
	extern CSCORE_API const FECsWeaponMultiValueMember Last_IsFirePressed;
	extern CSCORE_API const FECsWeaponMultiValueMember IsFirePressed_StartTime;
	extern CSCORE_API const FECsWeaponMultiValueMember IsFireReleased_StartTime;
	extern CSCORE_API const FECsWeaponMultiValueMember Fire_StartTime;
	// Charge
	extern CSCORE_API const FECsWeaponMultiValueMember AllowChargeFire;
	extern CSCORE_API const FECsWeaponMultiValueMember MaxChargeFireTime;
	// Spread
	extern CSCORE_API const FECsWeaponMultiValueMember DoSpread;
	extern CSCORE_API const FECsWeaponMultiValueMember MinSpread;
	extern CSCORE_API const FECsWeaponMultiValueMember MaxSpread;
	extern CSCORE_API const FECsWeaponMultiValueMember SpreadAddedPerShot;
	extern CSCORE_API const FECsWeaponMultiValueMember SpreadRecoveryRate;
	extern CSCORE_API const FECsWeaponMultiValueMember FiringSpreadRecoveryDelay;
	extern CSCORE_API const FECsWeaponMultiValueMember CurrentBaseSpread;
	extern CSCORE_API const FECsWeaponMultiValueMember CurrentSpread;
	extern CSCORE_API const FECsWeaponMultiValueMember LastSpreadFireTime;
	// Anim
	extern CSCORE_API const FECsWeaponMultiValueMember LoopFireAnim;
	extern CSCORE_API const FECsWeaponMultiValueMember DoScaleFireAnim;
	// Sound
	extern CSCORE_API const FECsWeaponMultiValueMember LoopFireSound;
	// Hitscan
	extern CSCORE_API const FECsWeaponMultiValueMember IsHitscan;
	extern CSCORE_API const FECsWeaponMultiValueMember DoesHitscanUseRadius;
	extern CSCORE_API const FECsWeaponMultiValueMember DoesHitscanSimulateProjectileDuration;
	extern CSCORE_API const FECsWeaponMultiValueMember ObstaclePenetrations;
	extern CSCORE_API const FECsWeaponMultiValueMember PawnPenetrations;
	// Reload
	extern CSCORE_API const FECsWeaponMultiValueMember ReloadTime;
	extern CSCORE_API const FECsWeaponMultiValueMember AllowRechargeAmmo;
	extern CSCORE_API const FECsWeaponMultiValueMember AllowRechargeAmmoDuringFire;
	extern CSCORE_API const FECsWeaponMultiValueMember RechargeSecondsPerAmmo;
	extern CSCORE_API const FECsWeaponMultiValueMember RechargeStartupDelay;
}

USTRUCT(BlueprintType)
struct CSCORE_API FECsWeaponRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsWeaponRoutine() {}
	FECsWeaponRoutine(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsWeaponRoutine(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsWeaponRoutine() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsWeaponRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsWeaponRoutine : public TCsEnumStructMap<FECsWeaponRoutine, uint8>
{
protected:
	EMCsWeaponRoutine() {}
	EMCsWeaponRoutine(const EMCsWeaponRoutine &) = delete;
	EMCsWeaponRoutine(EMCsWeaponRoutine &&) = delete;
public:
	~EMCsWeaponRoutine() {}
private:
	static EMCsWeaponRoutine* Instance;

public:
	static EMCsWeaponRoutine& Get();
};

namespace ECsWeaponRoutine
{
	extern CSCORE_API const FECsWeaponRoutine PlayAnimation_Reload_Internal;
	extern CSCORE_API const FECsWeaponRoutine StartChargeFire_Internal;
	extern CSCORE_API const FECsWeaponRoutine FireWeapon_Internal;
}

#pragma endregion Enums

// Structs
#pragma region

// bool
struct FCsWeapon_Ref_bool : public TCsProperty_TArrayRef_bool
{
	FCsWeapon_Ref_bool() : TCsProperty_TArrayRef_bool(){}
	~FCsWeapon_Ref_bool() {}
};

struct FCsWeapon_TMap_bool : public TCsProperty_TMap_bool<FECsWeaponFireMode>
{
	FCsWeapon_TMap_bool() : TCsProperty_TMap_bool<FECsWeaponFireMode>(){}
	~FCsWeapon_TMap_bool() {}
};

struct FCsWeapon_TMapRef_bool : public TCsProperty_TMapRef_bool<FECsWeaponFireMode>
{
	FCsWeapon_TMapRef_bool() : TCsProperty_TMapRef_bool<FECsWeaponFireMode>(){}
	~FCsWeapon_TMapRef_bool() {}
};

// uint8
struct FCsWeapon_TMap_uint8 : public TCsIntegralType_TMap_uint8<FECsWeaponFireMode>
{
	FCsWeapon_TMap_uint8() : TCsIntegralType_TMap_uint8<FECsWeaponFireMode>(){}
	~FCsWeapon_TMap_uint8() {}
};

struct FCsWeapon_TMapRef_uint8 : public TCsIntegralType_TMapRef_uint8<FECsWeaponFireMode>
{
	FCsWeapon_TMapRef_uint8() : TCsIntegralType_TMapRef_uint8<FECsWeaponFireMode>(){}
	~FCsWeapon_TMapRef_uint8() {}
};

// int32
struct FCsWeapon_Ref_int32 : public TCsIntegralType_TArrayRef_int32
{
	FCsWeapon_Ref_int32() : TCsIntegralType_TArrayRef_int32(){}
	~FCsWeapon_Ref_int32() {}
};

struct FCsWeapon_TMapRef_int32 : public TCsIntegralType_TMapRef_int32<FECsWeaponFireMode>
{
	FCsWeapon_TMapRef_int32() : TCsIntegralType_TMapRef_int32<FECsWeaponFireMode>(){}
	~FCsWeapon_TMapRef_int32() {}
};

// float
struct FCsWeapon_Ref_float : public TCsIntegralType_TArrayRef_float
{
	FCsWeapon_Ref_float() : TCsIntegralType_TArrayRef_float(){}
	~FCsWeapon_Ref_float() {}
};

struct FCsWeapon_TMap_float : public TCsIntegralType_TMap_float<FECsWeaponFireMode>
{
	FCsWeapon_TMap_float() : TCsIntegralType_TMap_float<FECsWeaponFireMode>(){}
	~FCsWeapon_TMap_float() {}
};

struct FCsWeapon_TMapRef_float : public TCsIntegralType_TMapRef_float<FECsWeaponFireMode>
{
	FCsWeapon_TMapRef_float() : TCsIntegralType_TMapRef_float<FECsWeaponFireMode>(){}
	~FCsWeapon_TMapRef_float() {}
};

#pragma endregion Structs

#define CS_WEAPON_DATA_VALUE 0
#define CS_WEAPON_CUSTOM_VALUE -1
#define CS_PROJECTILE_FIRE_PAYLOAD_POOL_SIZE 64

UCLASS()
class CSCORE_API ACsWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void OutsideWorldBounds() override;
	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	UPROPERTY()
	uint64 UniqueObjectId;

// Members
#pragma region
public:

	TCsGetObjectMember_Internal GetObjectMember_Internal;
	TCsGetStructMember_Internal GetStructMember_Internal;
	TCsGetScriptStructMember_Internal GetScriptStructMember_Internal;

	template<typename ValueType>
	void InitMultiValueMember(struct TCsProperty_TMap<FECsWeaponFireMode, ValueType> &Member, const ValueType &DefaultValue)
	{
		Member.SetDefaultValue(DefaultValue);

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Member.Init(EMCsWeaponFireMode::Get().GetEnumAt(I));
		}
	}

	template<typename ValueType>
	void InitMultiRefValueMember(struct TCsProperty_TMapRef<FECsWeaponFireMode, ValueType> &Member, const ValueType &DefaultValue)
	{
		Member.SetDefaultValue(DefaultValue);

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Member.Init(EMCsWeaponFireMode::Get().GetEnumAt(I));
		}
	}

	virtual void InitMultiValueMembers();

	// Set
#pragma region
public:

	template<typename T>
	void SetMemberRefValue(struct TCsProperty_TArrayRef<T> &Member, const FString &MemberName)
	{
		ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

		Member.ResetValues();

		for (uint8 I = 0; I < Member.Num(); ++I)
		{
			T* DataMember = UCsCommon_Load::GetObjectMember<T>(Data_Weapon, Data_Weapon->GetClass(), MemberName, GetObjectMember_Internal);

			if (I == 0)
				Member.Set(*DataMember);
			Member.Set(I, DataMember);
		}
	}

	template<typename ValueType>
	void SetMemberMultiValue(struct TCsProperty_TMap<FECsWeaponFireMode, ValueType> &Member, const ValueType &Value)
	{
		Member.ResetValues();

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (I == 0)
				Member.Set(Value);
			Member.Set(EMCsWeaponFireMode::Get().GetEnumAt(I), Value);
		}
	}

	template<typename ValueType>
	void SetMemberMultiRefValue(struct TCsProperty_TMapRef<FECsWeaponFireMode, ValueType> &Member, const FECsData_Weapon_FireMode &FireModeMember, const FString &MemberName)
	{
		ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();

		Member.ResetValues();

		const FString& StructName = FireModeMember.Name;

		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			void* Struct				= UCsCommon_Load::GetStructMember<void>(Data_Weapon->GetFireModeStruct(FireMode), Data_Weapon->GetFireModeScriptStruct(), StructName, GetStructMember_Internal);
			UScriptStruct* ScriptStruct = UCsCommon_Load::GetScriptStructMember(Data_Weapon->GetFireModeStruct(FireMode), Data_Weapon->GetFireModeScriptStruct(), StructName, GetScriptStructMember_Internal);
			ValueType* StructMember		= UCsCommon_Load::GetStructMember<ValueType>(Struct, ScriptStruct, MemberName, GetStructMember_Internal);

			if (I == 0)
				Member.Set(*StructMember);
			Member.Set(FireMode, StructMember);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_bool(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const bool &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_uint8(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const uint8 &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_int32(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const int32 &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_float(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const float &Value);

	virtual void SetMultiValueMembers();

#pragma endregion Set

	// Get
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual bool GetMemberValue_bool(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual uint8 GetMemberValue_uint8(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual int32 GetMemberValue_int32(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual float GetMemberValue_float(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode);

#pragma endregion Get

	// Add
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Member")
	void AddMemberValue_uint8(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const uint8 &Value);

#pragma endregion Add

#pragma endregion Members

// Data
#pragma region
public:

	TWeakObjectPtr<class ACsData_Weapon> MyData_Weapon;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_Weapon* GetMyData_Weapon();

	template<typename T>
	T* GetMyData_Weapon()
	{
		return Cast<T>(GetMyData_Weapon());
	}

	/* Declare / Implement in Child class */
	// ApplyData_Weapon

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnApplyDataWeapon, const uint8&);

	FOnApplyDataWeapon OnApplyData_Weapon_Event;

	UPROPERTY(BlueprintAssignable, Category = "Data")
	FBindableDynEvent_CsWeapon_OnApplyDataWeapon OnApplyData_Weapon_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_Projectile* GetMyData_Projectile(const FECsWeaponFireMode &FireMode, const bool &IsCharged);

	template<typename T>
	T* GetMyData_Projectile(const FECsWeaponFireMode &FireMode, const bool &IsCharged)
	{
		return Cast<T>(GetMyData_Projectile(FireMode, IsCharged));
	}

#pragma endregion Data

// Managers
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Manager")
	class ACsManager_Inventory* GetMyManager_Inventory();

	template<typename T>
	T* GetMyManager_Inventory()
	{
		return Cast<T>(GetMyManager_Inventory());
	}

#pragma endregion Managers

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InWeapon, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	virtual void ClearRoutines();

	//static void Coroutine_StopCondition(struct FCsRoutine* r);

#pragma endregion Routines

// Owner
#pragma region
public:

protected:
	TWeakObjectPtr<class UObject> MyOwner;
	TWeakObjectPtr<class ACsPawn> MyPawn;

public:
	virtual void SetMyOwner(UObject* InMyOwner);

	UFUNCTION(BlueprintCallable, Category = "Owner")
	UObject* GetMyOwner();

	template<typename T>
	T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	FECsWeaponOwner MyOwnerType;

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual bool IsValidOwnerTypeInGame();

	virtual void SetMyPawn(class ACsPawn* InMyPawn);

	UFUNCTION(BlueprintCallable, Category = "Owner")
	class ACsPawn* GetMyPawn();

	template<typename T>
	T* GetMyPawn()
	{
		return Cast<T>(GetMyPawn());
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	FECsWeaponOwner PawnWeaponOwner;

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual TEnumAsByte<ECsViewType::Type> GetCurrentViewType();

#pragma endregion Owner

// State
#pragma region
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	uint8 WeaponIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FECsWeaponSlot WeaponSlot;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	FECsWeaponState CurrentState;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	FECsWeaponState LastState;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FECsWeaponFireMode PrimaryFireMode;

	virtual void OnTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWeapon_OnTick OnTick_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWeapon_OnTick Override_OnTick_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnTick_HandleStates();

	UFUNCTION(BlueprintCallable, Category = "State")
	bool CanFire(const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "State")
	bool CanFire_Auto(const FECsWeaponFireMode &FireMode);

	void CheckState_Idle();

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsWeapon_Override_CheckStateIdle Override_CheckState_Idle_ScriptEvent;

	void HandleState_Firing(const FECsWeaponFireMode &FireMode);

	void Enable();
	virtual void Disable();
	void Reset();
	virtual void Show();
	virtual void Hide();

#pragma endregion State

	void OnCalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult);

// Animation
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void PlayAnimation(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	FECsWeaponAnim ReloadAnim;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void PlayAnimation_Reload();
	static char PlayAnimation_Reload_Internal(struct FCsRoutine* r);
	struct FCsRoutine* PlayAnimation_Reload_Internal_Routine;
	static bool PlayAnimation_Reload_StopCondition(struct FCsRoutine* r);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual float GetAnimationLength(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0);
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void StopAnimation(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0);

#pragma endregion Animation

// Sound
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Sound")
	FECsWeaponSound FireSound;

	UFUNCTION(BlueprintCallable, Category = "Sound")
	virtual UObject* GetSoundParent();

	UFUNCTION(BlueprintCallable, Category = "Sound")
	virtual class ACsSound* GetSound(const FECsWeaponSound &SoundType);

	virtual void PlaySound(const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType);
	virtual void StopSound(const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType);

#pragma endregion Sound

// Equip / UnEquip
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Equip / UnEquip")
	bool IsEquipped;

	virtual void Equip();

	DECLARE_MULTICAST_DELEGATE_FourParams(FOnEquip, const FECsWeaponSlot&, const int32&, const int32&, const int32&);

	FOnEquip OnEquip_Event;

	UPROPERTY(BlueprintAssignable, Category = "Equip / UnEquip")
	FBindableDynEvent_CsWeapon_OnEquip OnEquip_ScriptEvent;

	virtual void UnEquip();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnEquip, const FECsWeaponSlot&);

	FOnUnEquip OnUnEquip_Event;

	UPROPERTY(BlueprintAssignable, Category = "Equip / UnEquip")
	FBindableDynEvent_CsWeapon_OnUnEquip OnUnEquip_ScriptEvent;

	UPROPERTY(BlueprintReadOnly, Category = "Equip / UnEquip")
	bool DoingEquipTransition;

	virtual bool CanUnEquip();

#pragma endregion Equip / UnEquip

// Firing
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode FiringDataFireMode;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsWeaponState FiringState;

	// Ammo
#pragma region
public:

	FCsWeapon_Ref_int32 MaxAmmo;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual int32 GetMaxAmmo(const int32 &Index);

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	int32 CurrentAmmo;

	TCsInt32_Ref CurrentAmmoHandle;

	virtual void OnChange_CurrentAmmo(const int32 &Value);
															 // WeaponSlot, CurrentAmmo, MaxAmmo, AmmoReserve
	DECLARE_MULTICAST_DELEGATE_FourParams(FOnChange_CurrentAmmo, const FECsWeaponSlot&, const int32&, const int32&, const int32&);

	FOnChange_CurrentAmmo OnChange_CurrentAmmo_Event;

	UPROPERTY(BlueprintAssignable, Category = "Firing")
	FBindableDynEvent_CsWeapon_OnChange_CurrentAmmo OnChange_CurrentAmmo_ScriptEvent;

	virtual void IncrementCurrentAmmo(const int32 &Index);
	virtual void ResetCurrentAmmo(const int32 &Index);

	// TODO: May need distinguish between MaxAmmo (ClipSize) and a Weapon's Ammo Capacity

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	bool bUnlimitedAmmo;

	virtual const FName& GetAmmoShortCode(const FECsWeaponFireMode &FireMode, const bool &IsCharged);
	virtual int32 GetAmmoReserve(const int32 &Index, const FECsWeaponFireMode &FireMode, const bool &IsCharged);

	virtual void ConsumeAmmo(const FECsWeaponFireMode &FireMode, const bool &IsCharged);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConsumeAmmo, const FName&);

	FOnConsumeAmmo OnConsumeAmmo_Event;

	UPROPERTY(BlueprintAssignable, Category = "Firing")
	FBindableDynEvent_CsWeapon_OnConsumeAmmo OnConsumeAmmo_ScriptEvent;

	void ConsumeAmmoItem(const FECsWeaponFireMode &FireMode, const bool &IsCharged, TArray<FCsItem*> &OutItems);

	FBindableEvent_CsWeapon_OnConsumeAmmoItem OnConsumeAmmoItem_Event;

#pragma endregion Ammo

	FCsWeapon_TMapRef_uint8 ProjectilesPerShot;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual uint8 GetProjectilesPerShot(const FECsWeaponFireMode &FireMode);

	FCsWeapon_TMap_uint8 CurrentProjectilePerShotIndex;

	FCsWeapon_TMapRef_bool DoFireOnRelease;
	FCsWeapon_TMapRef_bool IsFullAuto;

	FCsWeapon_TMapRef_float TimeBetweenProjectilesPerShot;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetTimeBetweenProjectilesPerShot(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float TimeBetweenShots;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetTimeBetweenShots(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float TimeBetweenAutoShots;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetTimeBetweenAutoShots(const FECsWeaponFireMode &FireMode);

	int32 Seed;

	bool bSeedInitialized;

	UPROPERTY()
	struct FRandomStream RandStream;

	FCsWeapon_TMap_bool IsFirePressed;
	FCsWeapon_TMap_bool Last_IsFirePressed;

	void SetIsFirePressed(const FECsWeaponFireMode &FireMode, const bool &Value, const bool &DoOnTick = true);

	FCsWeapon_TMap_float IsFirePressed_StartTime;
	FCsWeapon_TMap_float IsFireReleased_StartTime;
	FCsWeapon_TMap_float Fire_StartTime;

	// Charge
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsWeaponAnim ChargeFireStartAnim;
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsWeaponAnim ChargeFireLoopAnim;

	FCsWeapon_TMapRef_bool AllowChargeFire;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	bool PerformingChargeFire;

	FCsWeapon_TMapRef_float MaxChargeFireTime;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetMaxChargeFireTime(const FECsWeaponFireMode &FireMode);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void HandleChargeFire();

	void StartChargeFire(const FECsWeaponFireMode &FireMode);
	static char StartChargeFire_Internal(struct FCsRoutine* r);
	struct FCsRoutine* StartChargeFire_Internal_Routine;

	static bool StartChargeFire_StopCondition(struct FCsRoutine* r);

	float ChargeFire_StartTime;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetChargeFireHeldTime();
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetChargeFireHeldPercent(const FECsWeaponFireMode &FireMoe);
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetCurrentChargeFireHeldTime();
	UFUNCTION(BlueprintCallable, Category = "Firing")
	float GetCurrentChargeFireHeldPercent(const FECsWeaponFireMode &FireMode);

	void StopChargeFire(const FECsWeaponFireMode &FireMode);

#pragma endregion Charge

	// Spread
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode AimingDataFireMode;

	FCsWeapon_TMapRef_bool DoSpread;
	FCsWeapon_TMapRef_float MinSpread;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetMinSpread(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float MaxSpread;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetMaxSpread(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float SpreadAddedPerShot;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetSpreadAddedPerShot(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float SpreadRecoveryRate;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetSpreadRecoveryRate(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float FiringSpreadRecoveryDelay;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetFiringSpreadRecoveryDelay(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float MovingSpreadBonus;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual float GetMovingSpreadBonus(const FECsWeaponFireMode &FireMode);

	FCsWeapon_TMap_float CurrentBaseSpread;
	FCsWeapon_TMap_float CurrentSpread;
	FCsWeapon_TMap_float LastSpreadFireTime;

#pragma endregion Spread

public:

	// Anim
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode AnimationDataFireMode;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsWeaponAnim FireAnim;

	FCsWeapon_TMapRef_bool LoopFireAnim;
	FCsWeapon_TMapRef_bool DoScaleFireAnim;

	// Sound
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode SoundsDataFireMode;

	FCsWeapon_TMapRef_bool LoopFireSound;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int32 FireCount;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetFireWeaponStartLocation(const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetFireWeaponStartDirection(const FECsWeaponFireMode &FireMode);

	struct FCsProjectileFirePayload ProjectileFirePayloads[CS_PROJECTILE_FIRE_PAYLOAD_POOL_SIZE];

	uint8 ProjectileFirePayloadPoolIndex;

	struct FCsProjectileFirePayload* AllocateProjectileFirePayload(const FECsWeaponFireMode &FireMode);

	void FireWeapon(const FECsWeaponFireMode &FireMode);
	static char FireWeapon_Internal(struct FCsRoutine* r);
	struct FCsRoutine* FireWeapon_Internal_Routine;

	static bool FireWeapon_StopCondition(struct FCsRoutine* r);

	UPROPERTY(BlueprintAssignable, Category = "Firing")
	FBindableDynEvent_CsWeapon_Override_FireWeapon Override_FireWeapon_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetOwnerRightVector();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetFireProjectileDestination();

	virtual void FireProjectile(const FECsWeaponFireMode &FireMode, FCsProjectileFirePayload* FirePayload);
	virtual void FireProjectile_Internal(const FECsWeaponFireMode &FireMode, FCsProjectileFirePayload* Payload);

	void DrawFireProjectile(class ACsProjectile* Projectile, const FVector &Start, const FVector &End);
	static char DrawFireProjectile_Internal(struct FCsRoutine* r);

	// Hitscan
#pragma region
public:

	FCsWeapon_TMapRef_bool IsHitscan;
	FCsWeapon_TMapRef_bool DoesHitscanUseRadius;
	FCsWeapon_TMapRef_bool DoesHitscanSimulateProjectileDuration;

	FCsWeapon_TMapRef_int32 ObstaclePenetrations;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual int32 GetObstaclePenetractions(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_int32 PawnPenetrations;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual int32 GetPawnPenetrations(const FECsWeaponFireMode &FireMode);

	virtual void GetFireHitscanIgnoreActors(TArray<AActor*> &OutActors);
	virtual void GetFireHitscanIgnoreComponents(TArray<UPrimitiveComponent*> &OutComponents);

	void FireHitscan(const FECsWeaponFireMode &FireMode, const FCsProjectileFirePayload* Payload);

#pragma endregion Hitscan

	virtual UObject* GetMuzzleFlashParent(const TCsViewType &ViewType);

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual void PlayMuzzleFlash(const FECsWeaponFireMode &FireMode);

#pragma endregion Firing

// Reload
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Reload")
	FECsWeaponState ReloadingState;

	UPROPERTY(BlueprintReadOnly, Category = "Reload")
	bool bReloading;
	TCsBool_Ref bReloadingHandle;
private:
	void OnChange_bReloading(const bool &Value);
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChange_bReloading, const FECsWeaponSlot&, const bool&);
	FOnChange_bReloading OnChange_bReloading_Event;
	UPROPERTY(BlueprintAssignable, Category = "Reload")
	FBindableDynEvent_CsWeapon_OnChange_bReloading OnChange_bReloading_ScriptEvent;

	FCsWeapon_Ref_float ReloadTime;
	virtual float GetReloadTime(const int32 &Index);

	UPROPERTY(BlueprintReadWrite, Category = "Reload")
	float ReloadStartTime;

	FCsWeapon_Ref_bool AllowRechargeAmmo;
	FCsWeapon_Ref_bool AllowRechargeAmmoDuringFire;

	FCsWeapon_Ref_float RechargeSecondsPerAmmo;
	UFUNCTION(BlueprintCallable, Category = "Reload")
	virtual float GetRechargeSecondsPerAmmo(const int32 &Index);
	FCsWeapon_Ref_float RechargeStartupDelay;
	UFUNCTION(BlueprintCallable, Category = "Reload")
	virtual float GetRechargeStartupDelay(const int32 &Index);

	float RechargeAmmo_StartTime;
	float NextRechargeAmmoTime;

	UPROPERTY(BlueprintReadWrite, Category = "Reload")
	bool bRechargingAmmo;

	UFUNCTION(BlueprintCallable, Category = "Reload")
	bool CanReload();
	UFUNCTION(BlueprintCallable, Category = "Reload")
	bool CanAutoReload(const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Reload")
	bool ShouldAutoReload(const FECsWeaponFireMode &FireMode);

	void Reload();

#pragma endregion Reload
};
