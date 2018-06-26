// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Sense.h"
#include "CsPawn.generated.h"

// Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_Override_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);
	// Pre
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPreTick, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsPawn_OnPreTick, const uint8&, const float&);
	// Post
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPostTick, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsPawn_OnPostTick, const uint8&, const float&);
// Spawn
	// FirstSpawn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsPawn_OnFirstSpawn, const uint8&, MappingId);
	// Respawn
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsPawn_OnHandleRespawnTimerFinished, const uint8&);
// Setup
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsPawn_OnSetupFinished, const uint8&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsPawn_OnSetupFinished, const uint8&, MappingId);
// Health
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsPawn_OnChangeHealth, const uint8&, const float&, const float&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPawn_OnChangeHealth, const uint8&, MappingId, const float&, CurrentHealth, const float&, CurrentMaxHealth);
// Weapon
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsPawn_OnChangeCurrentWeaponSlot, const uint8&, const FECsWeaponSlot&, const FECsWeaponSlot&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPawn_OnChangeCurrentWeaponSlot, const uint8&, MappingId, const FECsWeaponSlot&, LastWeaponSlot, const FECsWeaponSlot&, CurrentWeaponSlot);
// Damage
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsPawn_OnApplyDamage_Result, const uint8&, FCsDamageResult*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnApplyDamage_Result, const uint8&, MappingId, const FCsDamageResult&, Result);

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsPawnRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsPawnRoutine() {}
	FECsPawnRoutine(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsPawnRoutine(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsPawnRoutine() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsPawnRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsPawnRoutine : public TCsEnumStructMap<FECsPawnRoutine, uint8>
{
protected:
	EMCsPawnRoutine() {}
	EMCsPawnRoutine(const EMCsPawnRoutine &) = delete;
	EMCsPawnRoutine(EMCsPawnRoutine &&) = delete;
public:
	~EMCsPawnRoutine() {}
private:
	static EMCsPawnRoutine* Instance;

public:
	static EMCsPawnRoutine& Get();
};

namespace ECsPawnRoutine
{
	extern CSCORE_API const FECsPawnRoutine CheckLinkedToPlayerState_Internal;
	extern CSCORE_API const FECsPawnRoutine HandleRespawnTimer_Internal;
}

#pragma endregion Enums

// Structs
#pragma region

#pragma endregion Structs

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
	bool IsPlacedInWorld;

	/** ONLY Call in the child class in which you want to implement this functionality */
	virtual void PreTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnPreTick OnPreTick_ScriptEvent;

	FBindableEvent_CsPawn_OnPreTick OnPreTick_Event;

	/** ONLY Call in the child class in which you want to implement this functionality */
	virtual void PostTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnPostTick OnPostTick_ScriptEvent;

	FBindableEvent_CsPawn_OnPostTick OnPostTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_Override_OnTick Override_OnTick_ScriptEvent;

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);



// Setup
#pragma region

	CS_COROUTINE_DECLARE(CheckLinkedToPlayerState)

	virtual bool IsOnBoardCompleted_Game();

	virtual void OnTick_HandleSetup();

	FBindableEvent_CsPawn_OnSetupFinished OnSetup_Finished_Event;

	UPROPERTY(BlueprintAssignable, Category = "Setup")
	FBindableDynEvent_CsPawn_OnSetupFinished OnSetup_Finished_ScriptEvent;

#pragma endregion Setup

// State
#pragma region
public:

	// Health
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Health;

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void SetHealth(const float& InHealth);

	TCsFloat_Ref HealthHandle;

	virtual void OnChange_Health(const float &Value);

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsPawn_OnChangeHealth OnChange_Health_ScriptEvent;

	FBindableEvent_CsPawn_OnChangeHealth OnChange_Health_Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bHealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UCsHealthBarComponent* HealthBarComponent;

	UPROPERTY()
	class UCsWidget_HealthBar* HealthBarWidget;

#pragma endregion Health

public:

	virtual void ApplyDamage(FCsDamageEvent* Event);
	virtual void OnApplyDamage_Result(FCsDamageResult* Result);

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsPawn_OnApplyDamage_Result OnApplyDamage_Result_ScriptEvent;

	FBindableEvent_CsPawn_OnApplyDamage_Result OnApplyDamage_Result_Event;

	virtual void Die();

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

	FBindableEvent_CsPawn_OnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

	/** Flag for whether pawn has been setup, active, and alive */
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bSpawnedAndActive;

#pragma endregion Spawn

#pragma endregion State

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routines

// View
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "View")
	TEnumAsByte<ECsViewType::Type> CurrentViewType;

	virtual TEnumAsByte<ECsViewType::Type> GetCurrentViewType();

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

	virtual void RecordView();

#pragma endregion View

// Body / Root
#pragma region
public:

	UPROPERTY(BlueprintReadOnly, Category = "View")
	FRotator CurrentRootRotation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootLocation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootDir;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootRight;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootRightXY;

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
	float CurrentSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedZ;

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
	float CurrentCapsuleSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRightXY;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentMoveRightLeftValue;

	virtual void RecordVelocityAndSpeed();

#pragma endregion Movement

// Data
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	bool bCacheData;

	class ACsDataMapping* GetDataMapping();

	template<typename T>
	T* GetDataMapping()
	{
		return Cast<T>(GetDataMapping());
	}

	TWeakObjectPtr<class ACsData_Character> MyData_Character;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	class ACsData_Character* GetMyData_Character();

	template<typename T>
	T* GetMyData_Character()
	{
		return Cast<T>(GetMyData_Character());
	}

	TWeakObjectPtr<class ACsData_CharacterMeshSkin> MyData_CharacterMeshSkin;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	class ACsData_CharacterMeshSkin* GetMyData_CharacterMeshSkin();

	template<typename T>
	T* GetMyData_CharacterMeshSkin()
	{
		return Cast<T>(GetMyData_CharacterMeshSkin());
	}

	TWeakObjectPtr<class ACsData_CharacterMaterialSkin> MyData_CharacterMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Datas")
	class ACsData_CharacterMaterialSkin* GetMyData_CharacterMaterialSkin();

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

	FECsWeaponSlot CurrentWeaponSlot;

	TCsProperty_Ref<FECsWeaponSlot> CurrentWeaponSlotHandle;

	virtual void OnChange_CurrentWeaponSlot(const FECsWeaponSlot &Slot);

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnChangeCurrentWeaponSlot OnChange_CurrentWeaponSlot_ScriptEvent;

	FBindableEvent_CsPawn_OnChangeCurrentWeaponSlot OnChange_CurrentWeaponSlot_Event;

	uint8 CurrentWeaponIndex;
	FECsWeaponSlot LastWeaponSlot;
	uint8 LastWeaponIndex;
	uint8 CurrentWeaponCount;
	uint8 MaxWeaponCount;

	TSubclassOf<class ACsWeapon> WeaponClass;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapons")
	TArray<class ACsWeapon*> Weapons;

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
	TArray<TWeakObjectPtr<class ACsData_Weapon>> Data_Weapons;

	class ACsData_Weapon* GetData_Weapon(const FECsWeaponSlot &Slot);
	
	template<typename T>
	T* GetData_Weapon(const FECsWeaponSlot &Slot)
	{
		return Cast<T>(GetData_Weapon(Slot));
	}

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	class ACsData_Weapon* GetCurrentData_Weapon();

	template<typename T>
	T* GetCurrentData_Weapon()
	{
		return Cast<T>(GetCurrentData_Weapon());
	}

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<class ACsData_WeaponMaterialSkin>> Data_WeaponMaterialSkins;

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot);

	template<typename T>
	T* GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot)
	{
		return Cast<T>(GetData_WeaponMaterialSkin(Slot));
	}

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	class ACsData_WeaponMaterialSkin* GetCurrentData_WeaponMaterialSkin();

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

	TMap<FECsSenseActorType, TMap<uint8, FCsSenseInfo>> SenseMap;
	TMap<uint8, FCsSenseInfo*> SenseTraceRequestMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float SenseViewMinDot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float SenseViewMinAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SenseTraceToAIInterval;

	virtual void OnTick_CheckSenses(const float &DeltaSeconds);
	virtual void Sense_CheckMeToActorDot(FCsSenseInfo& Info);

#pragma endregion Sense

// Managers
#pragma region
public:

	virtual class ACsManager_Inventory* GetMyManager_Inventory();

#pragma endregion Managers
};