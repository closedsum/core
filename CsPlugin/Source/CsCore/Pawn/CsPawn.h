// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
// Types
#include "Types/CsTypes_Weapon.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "Types/CsTypes_Damage.h"
#include "Managers/Sense/CsTypes_Sense.h"
#include "Types/CsTypes_Trace.h"
#include "Types/CsTypes_Character.h"
#include "Types/Property/Ref/CsProperty_Ref_float.h"
#include "CsPawn.generated.h"

// Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_Override_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);
	// Pre
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPreTick, const uint8&, MappingId, const float&, DeltaSeconds);
	// Post
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPostTick, const uint8&, MappingId, const float&, DeltaSeconds);
// Spawn
	// FirstSpawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsPawn_OnFirstSpawn, const uint8&, MappingId);
// Setup
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsPawn_OnSetupFinished, const uint8&, MappingId);
// Health
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPawn_OnChange_Health, const uint8&, MappingId, const float&, CurrentHealth, const float&, CurrentMaxHealth);
// Weapon
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPawn_OnChange_CurrentWeaponSlot, const uint8&, MappingId, const FECsWeaponSlot&, LastWeaponSlot, const FECsWeaponSlot&, CurrentWeaponSlot);
// Damage
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnApplyDamage_Result, const uint8&, MappingId, const FCsDamageResult&, Result);
// Movement
	// Jumping
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnChange_CurrentJumpMovementState, const ECsCharacterJumpMovementState&, From, const ECsCharacterJumpMovementState&, To);

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsPawnRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsPawnRoutine)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsPawnRoutine)

struct CSCORE_API EMCsPawnRoutine : public TCsEnumStructMap<FECsPawnRoutine, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsPawnRoutine)
};

namespace ECsPawnRoutine
{
	extern CSCORE_API const FECsPawnRoutine CheckLinkedToPlayerState_Internal;
	extern CSCORE_API const FECsPawnRoutine HandleRespawnTimer_Internal;
}

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsPawnViewTraceInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool bAsync;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool bForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	uint8 RequestId;

	FCollisionQueryParams QueryParams;

	TArray<TWeakObjectPtr<AActor>> IgnoredActors;

	FCollisionObjectQueryParams ObjectParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	float RangeSq;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FVector HitLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FHitResult HitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	TArray<FHitResult> OutHits;

	FCsPawnViewTraceInfo() :
		bAsync(false),
		bForce(false),
		QueryParams(),
		ObjectParams(),
		Range(0.0f),
		RangeSq(0.0f),
		HitLocation(0.0f),
		HitResult()
	{
		RequestId = CS_INVALID_TRACE_REQUEST_ID;
	}
	~FCsPawnViewTraceInfo(){}
};

USTRUCT(BlueprintType)
struct FCsPawnTraceToGroundWhileJumpingInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	uint8 RequestId;

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float Interval;

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float LastTime;

	FCsPawnTraceToGroundWhileJumpingInfo()
	{
		RequestId = CS_INVALID_TRACE_REQUEST_ID;
		Interval = 0.0f;
		LastTime = 0.0f;
	}
	~FCsPawnTraceToGroundWhileJumpingInfo() {}
};

USTRUCT(BlueprintType)
struct FCsPawnJumpingFallingInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float ElapsedTime_Jumping;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float ElapsedTime_Falling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float DistanceToGround;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float TimeTillGrounded;

	FCsPawnJumpingFallingInfo()
	{
		Reset();
	}

	~FCsPawnJumpingFallingInfo() {}

	void Reset()
	{
		ElapsedTime_Jumping = 0.0f;
		ElapsedTime_Falling = 0.0f;
		DistanceToGround = 0.0f;
		TimeTillGrounded = 0.0f;
	}
};

#pragma endregion Structs

class UCsDataMapping;
class UCsData_Character;
class UCsData_CharacterMeshSkin;
class UCsData_CharacterMaterialSkin;
class UCsData_Weapon;
class UCsData_WeaponMaterialSkin;

UCLASS()
class CSCORE_API ACsPawn : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** ONLY Call in the child class in which you want to implement this functionality */
	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);

	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY()
	uint64 UniqueObjectId;

	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	bool bPlacedInWorld;

	/** ONLY Call in the child class in which you want to implement this functionality */
	virtual void PreTick(const float &DeltaSeconds);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreTick, const uint8&, const float&);

	FOnPreTick OnPreTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnPreTick OnPreTick_ScriptEvent;

	/** ONLY Call in the child class in which you want to implement this functionality */
	virtual void PostTick(const float &DeltaSeconds);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostTick, const uint8&, const float&);

	FOnPostTick OnPostTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnPostTick OnPostTick_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_Override_OnTick Override_OnTick_ScriptEvent;

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

// Setup
#pragma region

	CS_COROUTINE_DECLARE(CheckLinkedToPlayerState)

	virtual bool IsOnBoardCompleted_Game();

	virtual void OnTick_HandleSetup();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupFinished, const uint8&);

	FOnSetupFinished OnSetup_Finished_Event;

	UPROPERTY(BlueprintAssignable, Category = "Setup")
	FBindableDynEvent_CsPawn_OnSetupFinished OnSetup_Finished_ScriptEvent;

#pragma endregion Setup

// State
#pragma region
public:

	// Spawn
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bFirstSpawn;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFirstSpawn, ACsPawn*);

	FOnFirstSpawn OnFirstSpawn_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsPawn_OnFirstSpawn OnFirstSpawn_ScriptEvent;

	virtual void OnFirstSpawn();

	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float RespawnTime;

	CS_COROUTINE_DECLARE(HandleRespawnTimer)

	virtual void OnHandleRespawnTimerFinished(const uint8 &MappingId);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRespawnTimerFinished, const uint8&);

	FOnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

	/** Flag for whether pawn has been setup, active, and alive */
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bSpawnedAndActive;

#pragma endregion Spawn

	// Health
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Health;

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void SetHealth(const float& InHealth);

	TCsFloat_Ref HealthHandle;

	virtual void OnChange_Health(const float &Value);

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChange_Health, const uint8&, const float&, const float&);

	FOnChange_Health OnChange_Health_Event;

#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsPawn_OnChange_Health OnChange_Health_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bHealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UCsHealthBarComponent* HealthBarComponent;

	UPROPERTY()
	class UCsWidget_HealthBar* HealthBarWidget;

#pragma endregion Health

	// Damage
#pragma region
public:

	virtual void ApplyDamage(FCsDamageEvent* Event);
	virtual void OnApplyDamage_Result(FCsDamageResult* Result);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnApplyDamage_Result, const uint8&, FCsDamageResult*);

	FOnApplyDamage_Result OnApplyDamage_Result_Event;

#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsPawn_OnApplyDamage_Result OnApplyDamage_Result_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

#pragma endregion Damage

public:

	virtual void Die();

#pragma endregion State

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	static void RemoveRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

#pragma endregion Routines

// View
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "View")
	ECsViewType CurrentViewType;

	virtual ECsViewType GetCurrentViewType();

	UPROPERTY(BlueprintReadOnly, Category = "View")
	FRotator CurrentViewRotation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FRotator CurrentViewRotationDelta;

	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewLocation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewDir;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewRight;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewRightXY;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewUp;

	UPROPERTY(BlueprintReadWrite, Category = "View")
	bool bPerformViewTrace;

	UPROPERTY(BlueprintReadWrite, Category = "View")
	FCsPawnViewTraceInfo ViewTraceInfo;

	virtual void PerformViewTrace();
	virtual void PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response);
	virtual void RecordView();

#pragma endregion View

// Body / Root
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FRotator CurrentRootRotation;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentRootLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentBodyLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentFeetLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentRootDir;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentRootDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentRootRight;
	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentRootRightXY;

	UPROPERTY(BlueprintReadOnly, Category = "Body")
	FVector CurrentCapsuleBaseLocation;

	virtual void RecordRoot();

#pragma endregion Body / Root

// Movement
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDir;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDirZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedSq;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedXYSq;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedZSq;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityRightXY;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDir;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDirZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedSq;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedXYSq;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedZSq;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRightXY;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentMoveRightLeftValue;

	virtual void RecordVelocityAndSpeed();

	virtual FVector GetFeetLocation() const;

	// Jumping
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bJumpFinished;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ECsCharacterJumpMovementState CurrentJumpMovementState;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChange_CurrentJumpMovementState, const ECsCharacterJumpMovementState&, const ECsCharacterJumpMovementState&);
	FOnChange_CurrentJumpMovementState OnChange_CurrentJumpMovementState_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Movement")
	FBindableDynEvent_CsPawn_OnChange_CurrentJumpMovementState OnChange_CurrentJumpMovementState_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bTraceToGroundWhileJumping;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FCsPawnTraceToGroundWhileJumpingInfo TraceToGroundWhileJumpingInfo;

	void TraceToGroundWhileJumping();
	void Async_TraceToGroundWhileJumping_Response(const uint8 &RequestId, FCsTraceResponse* Response);

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FCsPawnJumpingFallingInfo JumpingFallingInfo;

#pragma endregion Jumping

#pragma endregion Movement

// Data
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bCacheData;

	UCsDataMapping* GetDataMapping();

	template<typename T>
	T* GetDataMapping()
	{
		return Cast<T>(GetDataMapping());
	}

	TWeakObjectPtr<UCsData_Character> MyData_Character;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	UCsData_Character* GetMyData_Character();

	template<typename T>
	T* GetMyData_Character()
	{
		return Cast<T>(GetMyData_Character());
	}

	TWeakObjectPtr<UCsData_CharacterMeshSkin> MyData_CharacterMeshSkin;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	UCsData_CharacterMeshSkin* GetMyData_CharacterMeshSkin();

	template<typename T>
	T* GetMyData_CharacterMeshSkin()
	{
		return Cast<T>(GetMyData_CharacterMeshSkin());
	}

	TWeakObjectPtr<UCsData_CharacterMaterialSkin> MyData_CharacterMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	UCsData_CharacterMaterialSkin* GetMyData_CharacterMaterialSkin();

	template<typename T>
	T* GetMyData_CharacterMaterialSkin()
	{
		return Cast<T>(GetMyData_CharacterMaterialSkin());
	}

	virtual void SetDatas();
	virtual void ApplyData_Character();
	virtual void OnRespawn_ApplyData_Character();

#pragma endregion Data

// Weapons
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
	FECsWeaponSlot CurrentWeaponSlot;
	TCsProperty_Ref<FECsWeaponSlot> CurrentWeaponSlotHandle;
	virtual void OnChange_CurrentWeaponSlot(const FECsWeaponSlot &Slot);

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChange_CurrentWeaponSlot, const uint8&, const FECsWeaponSlot&, const FECsWeaponSlot&);

	FOnChange_CurrentWeaponSlot OnChange_CurrentWeaponSlot_Event;

	UPROPERTY(BlueprintAssignable, Category = "Weapons")
	FBindableDynEvent_CsPawn_OnChange_CurrentWeaponSlot OnChange_CurrentWeaponSlot_ScriptEvent;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
	uint8 CurrentWeaponIndex;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
	FECsWeaponSlot LastWeaponSlot;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
	uint8 LastWeaponIndex;
	UPROPERTY(BlueprintReadOnly, Category = "Weapons")
	uint8 CurrentWeaponCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	uint8 MaxWeaponCount;

	TSubclassOf<class ACsWeapon> WeaponClass;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapons")
	TArray<class ACsWeapon*> Weapons;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	class ACsWeapon* GetWeapon(const FECsWeaponSlot &Slot);

	template<typename T>
	T* GetWeapon(const FECsWeaponSlot &Slot)
	{
		return Cast<T>(GetWeapon(Slot));
	}

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	class ACsWeapon* GetCurrentWeapon();

	template<typename T>
	T* GetCurrentWeapon()
	{
		return Cast<T>(GetCurrentWeapon());
	}

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UCsData_Weapon>> Data_Weapons;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	UCsData_Weapon* GetData_Weapon(const FECsWeaponSlot &Slot);
	
	template<typename T>
	T* GetData_Weapon(const FECsWeaponSlot &Slot)
	{
		return Cast<T>(GetData_Weapon(Slot));
	}

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	UCsData_Weapon* GetCurrentData_Weapon();

	template<typename T>
	T* GetCurrentData_Weapon()
	{
		return Cast<T>(GetCurrentData_Weapon());
	}

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UCsData_WeaponMaterialSkin>> Data_WeaponMaterialSkins;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	UCsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot);

	template<typename T>
	T* GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot)
	{
		return Cast<T>(GetData_WeaponMaterialSkin(Slot));
	}

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	UCsData_WeaponMaterialSkin* GetCurrentData_WeaponMaterialSkin();

	template<typename T>
	T* GetCurrentData_WeaponMaterialSkin()
	{
		return Cast<T>(GetCurrentData_WeaponMaterialSkin());
	}

	virtual void ApplyData_Weapon();
	virtual void OnRespawn_Setup_Weapon();

#pragma endregion Weapons

// Sense
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	FCsSenseData_Override_DEPRECATED SenseData;

	virtual void ApplySenseData();

#pragma endregion Sense

// Managers
#pragma region
public:

	virtual class ACsManager_Inventory* GetMyManager_Inventory();

	UPROPERTY(BlueprintReadOnly, Category = "Managers")
	class ACsManager_Sense_DEPRECATED* Manager_Sense;

#pragma endregion Managers

// Play In Preview Toggles
#pragma region
public:

#if WITH_EDITORONLY_DATA

	virtual void SetupInGameSimulation();

	UPROPERTY(Transient, EditDefaultsOnly, BlueprintReadWrite, Category = "Play In Preview Toggle")
	bool bSetupInGameSimulation;

#endif // #if WITH_EDITORONLY_DATA

#pragma endregion Play In Preview Toggles

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};