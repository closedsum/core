#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Weapon.h"
#include "Common/CsCommon_Load.h"
#include "Data/CsData_Weapon.h"
#include "CsWeapon.generated.h"

// Data
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsWeapon_OnApplyDataWeapon, const uint8&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_OnApplyDataWeapon, const uint8&, WeaponIndex);

// State
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWeapon_OnTick, const uint8&, WeaponIndex, const float&, DeltaSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsWeapon_Override_CheckStateIdle, const uint8&, WeaponIndex);

// Firing
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsWeapon_Override_FireWeapon, const uint8&, WeaponIndex, const uint8&, FireType);
// Reloading

// Enums
#pragma region

namespace ECsWeaponState
{
	enum Type : uint8;
}

typedef ECsWeaponState::Type TCsWeaponState;

UENUM(BlueprintType)
namespace ECsWeaponRoutine
{
	enum Type
	{
		PlayAnimation_Reload_Internal		UMETA(DisplayName = "PlayAnimation_Reload_Internal"),
		StartChargeFire_Internal			UMETA(DisplayName = "StartChargeFire_Internal"),
		FireWeapon_Internal					UMETA(DisplayName = "FireWeapon_Internal"),
		ECsWeaponRoutine_MAX				UMETA(Hidden),
	};
}

namespace ECsWeaponRoutine
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString PlayAnimation_Reload_Internal = TCsString(TEXT("PlayAnimation_Reload_Internal"), TEXT("playanimation_reload_internal"), TEXT("play animation reload internal"));
		const TCsString StartChargeFire_Internal = TCsString(TEXT("StartChargeFire_Internal"), TEXT("startchargefire_internal"), TEXT("start charge fire internal"));
		const TCsString FireWeapon_Internal = TCsString(TEXT("FireWeapon_Internal"), TEXT("fireweapon_internal"), TEXT("fire weapon internal"));
	}

	inline FString ToString(const Type &EType)
	{
		if (EType == Type::PlayAnimation_Reload_Internal) { return Str::PlayAnimation_Reload_Internal.Value; }
		if (EType == Type::StartChargeFire_Internal) { return Str::StartChargeFire_Internal.Value; }
		if (EType == Type::FireWeapon_Internal) { return Str::FireWeapon_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	inline Type ToType(const FString &String)
	{
		if (String == Str::PlayAnimation_Reload_Internal) { return Type::PlayAnimation_Reload_Internal; }
		if (String == Str::StartChargeFire_Internal) { return Type::StartChargeFire_Internal; }
		if (String == Str::FireWeapon_Internal) { return Type::FireWeapon_Internal; }
		return Type::ECsWeaponRoutine_MAX;
	}
}

#define ECS_ROUTINE_WEAPON_MAX (uint8)ECsWeaponRoutine::ECsWeaponRoutine_MAX
typedef TEnumAsByte<ECsWeaponRoutine::Type> TCsWeaponRoutine;

UENUM(BlueprintType)
namespace ECsWeaponCacheMultiValueMember
{
	enum Type
	{
		// Firing
		MaxAmmo									UMETA(DisplayName = "MaxAmmo"),
		ProjectilesPerShot						UMETA(DisplayName = "ProjectilesPerShot"),
		CurrentProjectilePerShotIndex			UMETA(DisplayName = "CurrentProjectilePerShotIndex"),
		DoFireOnRelease							UMETA(DisplayName = "DoFireOnRelease"),
		IsFullAuto								UMETA(DisplayName = "IsFullAuto"),
		TimeBetweenProjectilesPerShot			UMETA(DisplayName = "TimeBetweenProjectilesPerShot"),
		TimeBetweenShots						UMETA(DisplayName = "TimeBetweenShots"),
		TimeBetweenAutoShots					UMETA(DisplayName = "TimeBetweenAutoShots"),
		IsFirePressed							UMETA(DisplayName = "IsFirePressed"),
		Last_IsFirePressed						UMETA(DisplayName = "Last_IsFirePressed"),
		IsFirePressed_StartTime					UMETA(DisplayName = "IsFirePressed_StartTime"),
		IsFireReleased_StartTime				UMETA(DisplayName = "IsFireReleased_StartTime"),
		Fire_StartTime							UMETA(DisplayName = "Fire_StartTime"),
		// Charge
		AllowChargeFire							UMETA(DisplayName = "AllowChargeFire"),
		MaxChargeFireTime						UMETA(DisplayName = "MaxChargeFireTime"),
		// Spread
		DoSpread								UMETA(DisplayName = "DoSpread"),
		MinSpread								UMETA(DisplayName = "MinSpread"),
		MaxSpread								UMETA(DisplayName = "MaxSpread"),
		SpreadAddedPerShot						UMETA(DisplayName = "SpreadAddedPerShot"),
		SpreadRecoveryRate						UMETA(DisplayName = "SpreadRecoveryRate"),
		FiringSpreadRecoveryDelay				UMETA(DisplayName = "FiringSpreadRecoveryDelay"),
		CurrentBaseSpread						UMETA(DisplayName = "CurrentBaseSpread"),
		CurrentSpread							UMETA(DisplayName = "CurrentSpread"),
		LastSpreadFireTime						UMETA(DisplayName = "LastSpreadFireTime"),
		// Anim
		LoopFireAnim							UMETA(DisplayName = "LoopFireAnim"),
		DoScaleFireAnim							UMETA(DisplayName = "DoScaleFireAnim"),
		// Sound
		LoopFireSound							UMETA(DisplayName = "LoopFireSound"),
		// Hitscan
		IsHitscan								UMETA(DisplayName = "IsHitscan"),
		DoesHitscanUseRadius					UMETA(DisplayName = "DoesHitscanUseRadius"),
		DoesHitscanSimulateProjectileDuration	UMETA(DisplayName = "DoesHitscanSimulateProjectileDuration"),
		ObstaclePenetrations					UMETA(DisplayName = "ObstaclePenetrations"),
		PawnPenetrations						UMETA(DisplayName = "PawnPenetrations"),
		// Reload
		ReloadTime								UMETA(DisplayName = "ReloadTime"),
		AllowRechargeAmmo						UMETA(DisplayName = "AllowRechargeAmmo"),
		AllowRechargeAmmoDuringFire				UMETA(DisplayName = "AllowRechargeAmmoDuringFire"),
		RechargeSecondsPerAmmo					UMETA(DisplayName = "RechargeSecondsPerAmmo"),
		RechargeStartupDelay					UMETA(DisplayName = "RechargeStartupDelay"),

		ECsWeaponCacheMultiValueMember_MAX		UMETA(Hidden),
	};
}

namespace ECsWeaponCacheMultiValueMember
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		// Firing
		const TCsString MaxAmmo = TCsString(TEXT("MaxAmmo"), TEXT("maxammo"), TEXT("maxammo"));
		const TCsString ProjectilesPerShot = TCsString(TEXT("ProjectilesPerShot"), TEXT("projectilespershot"), TEXT("projectiles per shot"));
		const TCsString CurrentProjectilePerShotIndex = TCsString(TEXT("CurrentProjectilePerShotIndex"), TEXT("currentprojectilepershotindex"), TEXT("current projectile per shot index"));
		const TCsString DoFireOnRelease = TCsString(TEXT("DoFireOnRelease"), TEXT("dofireonrelease"), TEXT("do fire on release"));
		const TCsString IsFullAuto = TCsString(TEXT("IsFullAuto"), TEXT("isfullauto"), TEXT("is full auto"));
		const TCsString TimeBetweenProjectilesPerShot = TCsString(TEXT("TimeBetweenProjectilesPerShot"), TEXT("timebetweenprojectilespershot"), TEXT("time between projectiles per shot"));
		const TCsString TimeBetweenShots = TCsString(TEXT("TimeBetweenShots"), TEXT("timebetweenshots"), TEXT("time between shots"));
		const TCsString TimeBetweenAutoShots = TCsString(TEXT("TimeBetweenAutoShots"), TEXT("timebetweenautoshots"), TEXT("time between auto shots"));
		const TCsString IsFirePressed = TCsString(TEXT("IsFirePressed"), TEXT("isfirepressed"), TEXT("is fire pressed"));
		const TCsString Last_IsFirePressed = TCsString(TEXT("Last_IsFirePressed"), TEXT("last_isfirepressed"), TEXT("last is fire pressed"));
		const TCsString IsFirePressed_StartTime = TCsString(TEXT("IsFirePressed_StartTime"), TEXT("isfirepressed_starttime"), TEXT("is fire pressed start time"));
		const TCsString IsFireReleased_StartTime = TCsString(TEXT("IsFireReleased_StartTime"), TEXT("isfirereleased_starttime"), TEXT("is fire released start time"));
		const TCsString Fire_StartTime = TCsString(TEXT("Fire_StartTime"), TEXT("fire_starttime"), TEXT("fire start time"));
		// Charge
		const TCsString AllowChargeFire = TCsString(TEXT("AllowChargeFire"), TEXT("allowchargefire"), TEXT("allow charge fire"));
		const TCsString MaxChargeFireTime = TCsString(TEXT("MaxChargeFireTime"), TEXT("maxchargefiretime"), TEXT("max charge fire time"));
		// Spread
		const TCsString DoSpread = TCsString(TEXT("DoSpread"), TEXT("dospread"), TEXT("do spread"));
		const TCsString MinSpread = TCsString(TEXT("MinSpread"), TEXT("minspread"), TEXT("min spread"));
		const TCsString MaxSpread = TCsString(TEXT("MaxSpread"), TEXT("maxspread"), TEXT("max spread"));
		const TCsString SpreadAddedPerShot = TCsString(TEXT("SpreadAddedPerShot"), TEXT("spreadaddedpershot"), TEXT("spread added per shot"));
		const TCsString SpreadRecoveryRate = TCsString(TEXT("SpreadRecoveryRate"), TEXT("spreadrecoveryrate"), TEXT("spread recovery rate"));
		const TCsString FiringSpreadRecoveryDelay = TCsString(TEXT("FiringSpreadRecoveryDelay"), TEXT("firingspreadrecoverydelay"), TEXT("firing spread recovery delay"));
		const TCsString CurrentBaseSpread = TCsString(TEXT("CurrentBaseSpread"), TEXT("currentbasespread"), TEXT("current bases pread"));
		const TCsString CurrentSpread = TCsString(TEXT("CurrentSpread"), TEXT("currentspread"), TEXT("current spread"));
		const TCsString LastSpreadFireTime = TCsString(TEXT("LastSpreadFireTime"), TEXT("lastspreadfiretime"), TEXT("last spread fire time"));
		// Anim
		const TCsString LoopFireAnim = TCsString(TEXT("LoopFireAnim"), TEXT("loopfireanim"), TEXT("loop fire anim"));
		const TCsString DoScaleFireAnim = TCsString(TEXT("DoScaleFireAnim"), TEXT("doscalefireanim"), TEXT("do scale fire anim"));
		// Sound
		const TCsString LoopFireSound = TCsString(TEXT("LoopFireSound"), TEXT("loopfiresound"), TEXT("loop fire sound"));
		// Hitscan
		const TCsString IsHitscan = TCsString(TEXT("IsHitscan"), TEXT("ishitscan"), TEXT("ishitscan"));
		const TCsString DoesHitscanUseRadius = TCsString(TEXT("DoesHitscanUseRadius"), TEXT("doeshitscanuseradius"), TEXT("doeshitscanuseradius"));
		const TCsString DoesHitscanSimulateProjectileDuration = TCsString(TEXT("DoesHitscanSimulateProjectileDuration"), TEXT("doeshitscansimulateprojectileduration"), TEXT("doeshitscansimulateprojectileduration"));
		const TCsString ObstaclePenetrations = TCsString(TEXT("ObstaclePenetrations"), TEXT("obstaclepenetrations"), TEXT("obstaclepenetrations"));
		const TCsString PawnPenetrations = TCsString(TEXT("PawnPenetrations"), TEXT("pawnpenetrations"), TEXT("pawnpenetrations"));
		// Reload
		const TCsString ReloadTime = TCsString(TEXT("ReloadTime"), TEXT("reloadtime"), TEXT("reload time"));
		const TCsString AllowRechargeAmmo = TCsString(TEXT("AllowRechargeAmmo"), TEXT("allowrechargeammo"), TEXT("allow recharg eammo"));
		const TCsString AllowRechargeAmmoDuringFire = TCsString(TEXT("AllowRechargeAmmoDuringFire"), TEXT("allowrechargeammoduringfire"), TEXT("allow recharge ammo during fire"));
		const TCsString RechargeSecondsPerAmmo = TCsString(TEXT("RechargeSecondsPerAmmo"), TEXT("rechargesecondsperammo"), TEXT("recharge seconds per ammo"));
		const TCsString RechargeStartupDelay = TCsString(TEXT("RechargeStartupDelay"), TEXT("rechargestartupdelay"), TEXT("recharge start up delay"));
	}

	inline FString ToString(const Type &EType)
	{
		// Firing
		if (EType == Type::MaxAmmo) { return Str::MaxAmmo.Value; }
		if (EType == Type::ProjectilesPerShot) { return Str::ProjectilesPerShot.Value; }
		if (EType == Type::CurrentProjectilePerShotIndex) { return Str::CurrentProjectilePerShotIndex.Value; }
		if (EType == Type::DoFireOnRelease) { return Str::DoFireOnRelease.Value; }
		if (EType == Type::IsFullAuto) { return Str::IsFullAuto.Value; }
		if (EType == Type::TimeBetweenProjectilesPerShot) { return Str::TimeBetweenProjectilesPerShot.Value; }
		if (EType == Type::TimeBetweenShots) { return Str::TimeBetweenShots.Value; }
		if (EType == Type::TimeBetweenAutoShots) { return Str::TimeBetweenAutoShots.Value; }
		if (EType == Type::IsFirePressed) { return Str::IsFirePressed.Value; }
		if (EType == Type::Last_IsFirePressed) { return Str::Last_IsFirePressed.Value; }
		if (EType == Type::IsFirePressed_StartTime) { return Str::IsFirePressed_StartTime.Value; }
		if (EType == Type::IsFireReleased_StartTime) { return Str::IsFireReleased_StartTime.Value; }
		if (EType == Type::Fire_StartTime) { return Str::Fire_StartTime.Value; }
		// Charge
		if (EType == Type::AllowChargeFire) { return Str::AllowChargeFire.Value; }
		if (EType == Type::MaxChargeFireTime) { return Str::MaxChargeFireTime.Value; }
		// Spread
		if (EType == Type::DoSpread) { return Str::DoSpread.Value; }
		if (EType == Type::MinSpread) { return Str::MinSpread.Value; }
		if (EType == Type::MaxSpread) { return Str::MaxSpread.Value; }
		if (EType == Type::SpreadAddedPerShot) { return Str::SpreadAddedPerShot.Value; }
		if (EType == Type::SpreadRecoveryRate) { return Str::SpreadRecoveryRate.Value; }
		if (EType == Type::FiringSpreadRecoveryDelay) { return Str::FiringSpreadRecoveryDelay.Value; }
		if (EType == Type::CurrentBaseSpread) { return Str::CurrentBaseSpread.Value; }
		if (EType == Type::CurrentSpread) { return Str::CurrentSpread.Value; }
		if (EType == Type::LastSpreadFireTime) { return Str::LastSpreadFireTime.Value; }
		// Anim
		if (EType == Type::LoopFireAnim) { return Str::LoopFireAnim.Value; }
		if (EType == Type::DoScaleFireAnim) { return Str::DoScaleFireAnim.Value; }
		// Sound
		if (EType == Type::LoopFireSound) { return Str::LoopFireSound.Value; }
		// Hitscan
		if (EType == Type::IsHitscan) { return Str::IsHitscan.Value; }
		if (EType == Type::DoesHitscanUseRadius) { return Str::DoesHitscanUseRadius.Value; }
		if (EType == Type::DoesHitscanSimulateProjectileDuration) { return Str::DoesHitscanSimulateProjectileDuration.Value; }
		if (EType == Type::ObstaclePenetrations) { return Str::ObstaclePenetrations.Value; }
		if (EType == Type::PawnPenetrations) { return Str::PawnPenetrations.Value; }
		// Reload
		if (EType == Type::ReloadTime) { return Str::ReloadTime.Value; }
		if (EType == Type::AllowRechargeAmmo) { return Str::AllowRechargeAmmo.Value; }
		if (EType == Type::AllowRechargeAmmoDuringFire) { return Str::AllowRechargeAmmoDuringFire.Value; }
		if (EType == Type::RechargeSecondsPerAmmo) { return Str::RechargeSecondsPerAmmo.Value; }
		if (EType == Type::RechargeStartupDelay) { return Str::RechargeStartupDelay.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	inline Type ToType(const FString &String)
	{
		// Firing
		if (String == Str::MaxAmmo) { return Type::MaxAmmo; }
		if (String == Str::ProjectilesPerShot) { return Type::ProjectilesPerShot; }
		if (String == Str::CurrentProjectilePerShotIndex) { return Type::CurrentProjectilePerShotIndex; }
		if (String == Str::DoFireOnRelease) { return Type::DoFireOnRelease; }
		if (String == Str::IsFullAuto) { return Type::IsFullAuto; }
		if (String == Str::TimeBetweenProjectilesPerShot) { return Type::TimeBetweenProjectilesPerShot; }
		if (String == Str::TimeBetweenShots) { return Type::TimeBetweenShots; }
		if (String == Str::TimeBetweenAutoShots) { return Type::TimeBetweenAutoShots; }
		if (String == Str::IsFirePressed) { return Type::IsFirePressed; }
		if (String == Str::Last_IsFirePressed) { return Type::Last_IsFirePressed; }
		if (String == Str::IsFirePressed_StartTime) { return Type::IsFirePressed_StartTime; }
		if (String == Str::IsFireReleased_StartTime) { return Type::IsFireReleased_StartTime; }
		if (String == Str::Fire_StartTime) { return Type::Fire_StartTime; }
		// Charge
		if (String == Str::AllowChargeFire) { return Type::AllowChargeFire; }
		if (String == Str::MaxChargeFireTime) { return Type::MaxChargeFireTime; }
		// Spread
		if (String == Str::DoSpread) { return Type::DoSpread; }
		if (String == Str::MinSpread) { return Type::MinSpread; }
		if (String == Str::MaxSpread) { return Type::MaxSpread; }
		if (String == Str::SpreadAddedPerShot) { return Type::SpreadAddedPerShot; }
		if (String == Str::SpreadRecoveryRate) { return Type::SpreadRecoveryRate; }
		if (String == Str::FiringSpreadRecoveryDelay) { return Type::FiringSpreadRecoveryDelay; }
		if (String == Str::CurrentBaseSpread) { return Type::CurrentBaseSpread; }
		if (String == Str::CurrentSpread) { return Type::CurrentSpread; }
		if (String == Str::LastSpreadFireTime) { return Type::LastSpreadFireTime; }
		// Anim
		if (String == Str::LoopFireAnim) { return Type::LoopFireAnim; }
		if (String == Str::DoScaleFireAnim) { return Type::DoScaleFireAnim; }
		// Sound
		if (String == Str::LoopFireSound) { return Type::LoopFireSound; }
		// Hitscan
		if (String == Str::IsHitscan) { return Type::IsHitscan; }
		if (String == Str::DoesHitscanUseRadius) { return Type::DoesHitscanUseRadius; }
		if (String == Str::DoesHitscanSimulateProjectileDuration) { return Type::DoesHitscanSimulateProjectileDuration; }
		if (String == Str::ObstaclePenetrations) { return Type::ObstaclePenetrations; }
		if (String == Str::PawnPenetrations) { return Type::PawnPenetrations; }
		// Reload
		if (String == Str::ReloadTime) { return Type::ReloadTime; }
		if (String == Str::AllowRechargeAmmo) { return Type::AllowRechargeAmmo; }
		if (String == Str::AllowRechargeAmmoDuringFire) { return Type::AllowRechargeAmmoDuringFire; }
		if (String == Str::RechargeSecondsPerAmmo) { return Type::RechargeSecondsPerAmmo; }
		if (String == Str::RechargeStartupDelay) { return Type::RechargeStartupDelay; }
		return Type::ECsWeaponCacheMultiValueMember_MAX;
	}
}

#define ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX (uint8)ECsWeaponCacheMultiValueMember::ECsWeaponCacheMultiValueMember_MAX
typedef TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> TCsWeaponCacheMultiValueMember;

#pragma endregion Enums

// Structs
#pragma region

// bool
struct FCsWeapon_Ref_bool : public FCsIntegralType_TArrayRefValue<bool, int32>
{
	DECLARE_DELEGATE_RetVal_OneParam(bool, CsGetDelegate, const int32&);

	CsGetDelegate GetDelegate;

	FCsWeapon_Ref_bool() {}
	~FCsWeapon_Ref_bool() {}

	bool GetEX(const int32 &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArray_bool : public FCsIntegralType_TArrayValue<bool, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(bool, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArray_bool() {}
	~FCsWeapon_TArray_bool() {}

	bool GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArrayRef_bool : public FCsIntegralType_TArrayRefValue<bool, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(bool, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArrayRef_bool() {}
	~FCsWeapon_TArrayRef_bool() {}

	bool GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

// uint8
struct FCsWeapon_TArray_uint8 : public FCsIntegralType_TArrayValue<uint8, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(uint8, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArray_uint8() {}
	~FCsWeapon_TArray_uint8() {}

	uint8 GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArrayRef_uint8 : public FCsIntegralType_TArrayRefValue<uint8, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(uint8, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArrayRef_uint8() {}
	~FCsWeapon_TArrayRef_uint8() {}

	uint8 GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

// int32
struct FCsWeapon_Ref_int32 : public FCsIntegralType_TArrayRefValue<int32, int32>
{
	DECLARE_DELEGATE_RetVal_OneParam(int32, CsGetDelegate, const int32&);

	CsGetDelegate GetDelegate;

	FCsWeapon_Ref_int32() {}
	~FCsWeapon_Ref_int32() {}

	int32 GetEX(const int32 &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArrayRef_int32 : public FCsIntegralType_TArrayRefValue<int32, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(int32, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArrayRef_int32() {}
	~FCsWeapon_TArrayRef_int32() {}

	int32 GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

// float
struct FCsWeapon_Ref_float : public FCsIntegralType_TArrayRefValue<float, int32>
{
	DECLARE_DELEGATE_RetVal_OneParam(float, CsGetDelegate, const int32&);

	CsGetDelegate GetDelegate;

	FCsWeapon_Ref_float() {}
	~FCsWeapon_Ref_float() {}

	float GetEX(const int32 &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArray_float : public FCsIntegralType_TArrayValue<float, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(float, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArray_float() {}
	~FCsWeapon_TArray_float() {}

	float GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

struct FCsWeapon_TArrayRef_float : public FCsIntegralType_TArrayRefValue<float, TCsWeaponFire>
{
	DECLARE_DELEGATE_RetVal_OneParam(float, CsGetDelegate, const TCsWeaponFire&);

	CsGetDelegate GetDelegate;

	FCsWeapon_TArrayRef_float() {}
	~FCsWeapon_TArrayRef_float() {}

	float GetEX(const TCsWeaponFire &Index) { return GetDelegate.Execute(Index); }
};

#pragma endregion

#define CS_WEAPON_DATA_VALUE 0
#define CS_WEAPON_CUSTOM_VALUE -1
#define CS_PROJECTILE_FIRE_CACHE_POOL_SIZE 16

UCLASS()
class CSCORE_API ACsWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void OutsideWorldBounds() override;

// Members
#pragma region

	TCsWeaponFire FireType_MAX;
	uint8 FIRE_TYPE_MAX;

	TCsGetObjectMember_Internal GetObjectMember_Internal;
	TCsGetStructMember_Internal GetStructMember_Internal;
	TCsGetScriptStructMember_Internal GetScriptStructMember_Internal;

	virtual void InitMultiValueMembers();

	// Set
#pragma region

	template<typename T>
	void SetMemberRefValue(struct FCsPrimitiveType_TArrayRefValue<T, int32> &Member, const FString &MemberName)
	{
		ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

		Member.Reset();

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			T* DataMember = UCsCommon_Load::GetObjectMember<T>(Data_Weapon, Data_Weapon->GetClass(), MemberName, GetObjectMember_Internal);

			if (I == 0)
				Member.Set(*DataMember);
			Member.Set(I, DataMember);
		}
	}

	template<typename T>
	void SetMemberMultiValue(struct FCsPrimitiveType_TArrayValue<T, TCsWeaponFire> &Member, const T &Value)
	{
		Member.Reset();

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			if (I == 0)
				Member.Set(Value);
			Member.Set(I, Value);
		}
	}

	template<typename T>
	void SetMemberMultiRefValue(struct FCsPrimitiveType_TArrayRefValue<T, TCsWeaponFire> &Member, const TCsData_Weapon_FireType &FireTypeMember, const FString &MemberName)
	{
		ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

		Member.Reset();

		const FString StructName = ECsData_Weapon_FireType::ToString(FireTypeMember);

		for (uint8 I = 0; I < FIRE_TYPE_MAX; I++)
		{
			void* Struct				= UCsCommon_Load::GetStructMember<void>(Data_Weapon->GetFireTypeStruct(I), Data_Weapon->GetFireTypeScriptStruct(), StructName, GetStructMember_Internal);
			UScriptStruct* ScriptStruct = UCsCommon_Load::GetScriptStructMember(Data_Weapon->GetFireTypeStruct(I), Data_Weapon->GetFireTypeScriptStruct(), StructName, GetScriptStructMember_Internal);
			T* StructMember				= UCsCommon_Load::GetStructMember<T>(Struct, ScriptStruct, MemberName, GetStructMember_Internal);

			if (I == 0)
				Member.Set(*StructMember);
			Member.Set(I, StructMember);
		}
	}

	void SetMemberValue_bool(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const bool &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_Script_bool(const FString &MemberName, const int32 &Index, const bool &Value);

	void SetMemberValue_int32(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const int32 &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_Script_int32(const FString &MemberName, const int32 &Index, const int32 &Value);

	void SetMemberValue_uint8(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const uint8 &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_Script_uint8(const FString &MemberName, const int32 &Index, const uint8 &Value);

	void SetMemberValue_float(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index, const float &Value);
	UFUNCTION(BlueprintCallable, Category = "Member")
	virtual void SetMemberValue_Script_float(const FString &MemberName, const int32 &Index, const float &Value);

#pragma endregion Set

	// Get
#pragma region

	bool GetMemberValue_bool(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Member")
	bool GetMemberValue_Script_bool(const FString &MemberName, const int32 &Index);

	uint8 GetMemberValue_uint8(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Member")
	uint8 GetMemberValue_Script_uint8(const FString &MemberName, const int32 &Index);

	int32 GetMemberValue_int32(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Member")
	int32 GetMemberValue_Script_int32(const FString &MemberName, const int32 &Index);

	float GetMemberValue_float(const TEnumAsByte<ECsWeaponCacheMultiValueMember::Type> &Member, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Member")
	float GetMemberValue_Script_float(const FString &MemberName, const int32 &Index);

#pragma endregion Get

	// Add
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Member")
	void AddMemberValue_uint8(const int32 &Index, const FString &MemberName, const uint8 &Value);

#pragma endregion Add

#pragma endregion Members

// Data
#pragma region

	TWeakObjectPtr<class ACsData_Weapon> MyData_Weapon;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_Weapon* GetMyData_Weapon();

	/* Declare / Implement in Child class */
	// ApplyData_Weapon

	FBindableEvent_CsWeapon_OnApplyDataWeapon OnApplyData_Weapon_Event;

	UPROPERTY(BlueprintAssignable, Category = "Data")
	FBindableDynEvent_CsWeapon_OnApplyDataWeapon OnApplyData_Weapon_ScriptEvent;

#pragma endregion Data

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

private:
	TWeakObjectPtr<class UObject> MyOwner;
	TWeakObjectPtr<class ACsPawn> MyPawn;

public:
	virtual void SetMyOwner(UObject* InMyOwner);

	UFUNCTION(BlueprintCallable, Category = "Owner")
	UObject* GetMyOwner();

	TCsWeaponOwner MyOwnerType;

	virtual void SetMyPawn(class ACsPawn* InMyPawn);

	UFUNCTION(BlueprintCallable, Category = "Owner")
	class ACsPawn* GetMyPawn();

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual TEnumAsByte<ECsViewType::Type> GetCurrentViewType();

#pragma endregion Owner

// State
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	uint8 WeaponIndex;

	TCsWeaponSlot WeaponSlot;

	TCsWeaponState CurrentState;
	TCsWeaponState LastState;

	TCsWeaponState IdleState;

	void OnTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWeapon_OnTick OnTick_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsWeapon_OnTick Override_OnTick_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnTick_HandleStates();

	bool CanFire(const TCsWeaponFire &FireType);
	bool CanFire_Auto(const TCsWeaponFire &FireType);

	void CheckState_Idle();

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsWeapon_Override_CheckStateIdle Override_CheckState_Idle_ScriptEvent;

	void HandleState_Firing(const TCsWeaponFire &FireType);

	void Enable();
	void Disable();
	void Reset();
	virtual void Show();
	virtual void Hide();

#pragma endregion State

	void OnCalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult);

// Animation
#pragma region
public:

	virtual void PlayAnimation(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index = 0);

	TCsWeaponAnim ReloadAnim;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void PlayAnimation_Reload();
	static char PlayAnimation_Reload_Internal(struct FCsRoutine* r);
	struct FCsRoutine* PlayAnimation_Reload_Internal_Routine;
	static void PlayAnimation_Reload_StopCondition(struct FCsRoutine* r);

	virtual float GetAnimationLength(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index = 0);
	virtual void StopAnimation(const TCsWeaponFire &FireType, const TCsWeaponAnim &AnimType, const int32 &Index = 0);

#pragma endregion Animation

// Sound
#pragma region

	TCsWeaponSound FireSound;

	virtual UObject* GetSoundParent();
	virtual class ACsSound* GetSound(const TCsWeaponSound &SoundType);

	virtual void PlaySound(const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType);
	virtual void StopSound(const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType);

#pragma endregion Sound

// Equip / UnEquip
#pragma region
public:

	bool IsEquipped;
	bool DoingEquipTransition;

	//bool CanUnEquip();

#pragma endregion Equip / UnEquip

// Firing
#pragma region
public:

	TCsWeaponState FiringState;

	FCsWeapon_Ref_int32 MaxAmmo;
	virtual int32 GetMaxAmmo(const int32 &Index);

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	uint8 CurrentAmmo;

	bool HasUnlimitedAmmo;

	FCsWeapon_TArrayRef_uint8 ProjectilesPerShot;
	virtual uint8 GetProjectilesPerShot(const TCsWeaponFire &FireType);

	FCsWeapon_TArray_uint8 CurrentProjectilePerShotIndex;

	FCsWeapon_TArrayRef_bool DoFireOnRelease;
	FCsWeapon_TArrayRef_bool IsFullAuto;

	FCsWeapon_TArrayRef_float TimeBetweenProjectilesPerShot;
	virtual float GetTimeBetweenProjectilesPerShot(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float TimeBetweenShots;
	virtual float GetTimeBetweenShots(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float TimeBetweenAutoShots;
	virtual float GetTimeBetweenAutoShots(const TCsWeaponFire &FireType);

	int32 Seed;

	bool bSeedInitialized;

	UPROPERTY()
	struct FRandomStream RandStream;

	FCsWeapon_TArray_bool IsFirePressed;
	FCsWeapon_TArray_bool Last_IsFirePressed;

	void SetIsFirePressed(const TCsWeaponFire &FireType, const bool &Value, const bool &DoOnTick = true);

	FCsWeapon_TArray_float IsFirePressed_StartTime;
	FCsWeapon_TArray_float IsFireReleased_StartTime;
	FCsWeapon_TArray_float Fire_StartTime;

	// Charge
#pragma region

	TCsWeaponAnim ChargeFireStartAnim;
	TCsWeaponAnim ChargeFireLoopAnim;

	FCsWeapon_TArrayRef_bool AllowChargeFire;

	bool PerformingChargeFire;

	FCsWeapon_TArrayRef_float MaxChargeFireTime;
	virtual float GetMaxChargeFireTime(const TCsWeaponFire &FireType);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void HandleChargeFire();

	void StartChargeFire(const TCsWeaponFire &FireType);
	static char StartChargeFire_Internal(struct FCsRoutine* r);
	struct FCsRoutine* StartChargeFire_Internal_Routine;

	static void StartChargeFire_StopCondition(struct FCsRoutine* r);

	float ChargeFire_StartTime;

	float GetChargeFireHeldTime();
	float GetChargeFireHeldPercent(const TCsWeaponFire &FireType);
	float GetCurrentChargeFireHeldTime();
	float GetCurrentChargeFireHeldPercent(const TCsWeaponFire &FireType);

	void StopChargeFire(const TCsWeaponFire &FireType);

#pragma endregion Charge

	// Spread
#pragma region

	FCsWeapon_TArrayRef_bool DoSpread;
	FCsWeapon_TArrayRef_float MinSpread;
	virtual float GetMinSpread(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float MaxSpread;
	virtual float GetMaxSpread(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float SpreadAddedPerShot;
	virtual float GetSpreadAddedPerShot(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float SpreadRecoveryRate;
	virtual float GetSpreadRecoveryRate(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float FiringSpreadRecoveryDelay;
	virtual float GetFiringSpreadRecoveryDelay(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_float MovingSpreadBonus;
	virtual float GetMovingSpreadBonus(const TCsWeaponFire &FireType);

	FCsWeapon_TArray_float CurrentBaseSpread;
	FCsWeapon_TArray_float CurrentSpread;
	FCsWeapon_TArray_float LastSpreadFireTime;

#pragma endregion Spread

	// Anim
	TCsWeaponAnim FireAnim;

	FCsWeapon_TArrayRef_bool LoopFireAnim;
	FCsWeapon_TArrayRef_bool DoScaleFireAnim;

	// Sound

	FCsWeapon_TArrayRef_bool LoopFireSound;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetFireWeaponStartLocation();
	UFUNCTION(BlueprintCallable, Category = "Firing")
	virtual FVector GetFireWeaponStartDirection();

	struct FCsProjectileFireCache ProjectileFireCaches[CS_PROJECTILE_FIRE_CACHE_POOL_SIZE];

	uint8 ProjectileFireCachePoolIndex;

	struct FCsProjectileFireCache* AllocateProjectileFireCache(const TCsWeaponFire &FireType);

	void FireWeapon(const TCsWeaponFire &FireType);
	static char FireWeapon_Internal(struct FCsRoutine* r);
	struct FCsRoutine* FireWeapon_Internal_Routine;

	static void FireWeapon_StopCondition(struct FCsRoutine* r);

	UPROPERTY(BlueprintAssignable, Category = "Firing")
	FBindableDynEvent_CsWeapon_Override_FireWeapon Override_FireWeapon_ScriptEvent;

	virtual FVector GetOwnerRightVector();

	bool UseFakeProjectile;

	virtual void FireProjectile(const TCsWeaponFire &FireType, FCsProjectileFireCache* Cache);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireProjectile_Script(const uint8 &FireType, FCsProjectileFireCache &Cache);

	// Hitscan
#pragma region

	FCsWeapon_TArrayRef_bool IsHitscan;
	FCsWeapon_TArrayRef_bool DoesHitscanUseRadius;
	FCsWeapon_TArrayRef_bool DoesHitscanSimulateProjectileDuration;

	FCsWeapon_TArrayRef_int32 ObstaclePenetrations;
	virtual int32 GetObstaclePenetractions(const TCsWeaponFire &FireType);
	FCsWeapon_TArrayRef_int32 PawnPenetrations;
	virtual int32 GetPawnPenetrations(const TCsWeaponFire &FireType);

	void FireHitscan(const TCsWeaponFire &FireType, const FCsProjectileFireCache* Cache);

#pragma endregion Hitscan

	virtual UObject* GetMuzzleFlashParent();

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFire &FireType);

	virtual void PlayMuzzleFlash(const TCsWeaponFire &FireType);

#pragma endregion Firing

// Reload
#pragma region
public:

	TCsWeaponState ReloadingState;

	UPROPERTY(BlueprintReadWrite, Category = "Reload")
	bool IsReloading;

	FCsWeapon_Ref_float ReloadTime;
	virtual float GetReloadTime(const int32 &Index);

	UPROPERTY(BlueprintReadWrite, Category = "Reload")
	float ReloadStartTime;

	FCsWeapon_Ref_bool AllowRechargeAmmo;
	FCsWeapon_Ref_bool AllowRechargeAmmoDuringFire;

	FCsWeapon_Ref_float RechargeSecondsPerAmmo;
	virtual float GetRechargeSecondsPerAmmo(const int32 &Index);
	FCsWeapon_Ref_float RechargeStartupDelay;
	virtual float GetRechargeStartupDelay(const int32 &Index);

	float RechargeAmmo_StartTime;
	float NextRechargeAmmoTime;

	UPROPERTY(BlueprintReadWrite, Category = "Reload")
	bool IsRechargingAmmo;

	void Reload();

#pragma endregion Reload
};
