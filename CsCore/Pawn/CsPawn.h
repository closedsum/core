// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Damage.h"
#include "CsPawn.generated.h"

// Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_Override_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);
	// Pre
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPreTick, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsPawn_OnPreTick, const uint8&, const float&);
	// Post
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnPostTick, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsPawn_OnPostTick, const uint8&, const float&);
// Respawn
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsAIPawn_OnHandleRespawnTimerFinished, const uint8&);

// Enums
#pragma region

namespace ECsPawnRoutine
{
	enum Type
	{
		HandleRespawnTimer_Internal,
		ECsPawnRoutine_MAX,
	};
}

namespace ECsPawnRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString HandleRespawnTimer_Internal = TCsString(TEXT("HandleRespawnTimer_Internal"), TEXT("handlerespawntimer_internal"), TEXT("handle respawn timer internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::HandleRespawnTimer_Internal) { return Str::HandleRespawnTimer_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::HandleRespawnTimer_Internal) { return Type::HandleRespawnTimer_Internal; }
		return Type::ECsPawnRoutine_MAX;
	}
}

#define ECS_PAWN_ROUTINE_MAX (uint8)ECsPawnRoutine::ECsPawnRoutine_MAX
typedef ECsPawnRoutine::Type TCsPawnRoutine;

#pragma endregion Enums

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

	virtual bool IsOnBoardCompleted_Game();
	virtual void OnTick_HandleSetup();

// State
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bHealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	class UCsWidgetComponent* HealthBarComponent;

	virtual void OnTick_Handle_HealthBar();

	virtual void ApplyDamage(FCsDamageEvent* Event);

	virtual void Die();

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bFirstSpawn;

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

	FBindableEvent_CsAIPawn_OnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

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

	TCsWeaponSlot CurrentWeaponSlot;
	uint8 CurrentWeaponIndex;
	TCsWeaponSlot LastWeaponSlot;
	uint8 LastWeaponIndex;
	uint8 CurrentWeaponCount;
	uint8 MaxWeaponCount;

	TSubclassOf<class ACsWeapon> WeaponClass;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapons")
	TArray<class ACsWeapon*> Weapons;

	class ACsWeapon* GetWeapon(const TCsWeaponSlot &Slot);

	template<typename T>
	T* GetWeapon(const TCsWeaponSlot &Slot)
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

	class ACsData_Weapon* GetData_Weapon(const TCsWeaponSlot &Slot);
	
	template<typename T>
	T* GetData_Weapon(const TCsWeaponSlot &Slot)
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

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin(const TCsWeaponSlot &Slot);

	template<typename T>
	T* GetData_WeaponMaterialSkin(const TCsWeaponSlot &Slot)
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

// Managers
#pragma region
public:

	virtual class ACsManager_Inventory* GetMyManager_Inventory();

#pragma endregion Managers
};