// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPawn_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);

UCLASS()
class CSCORE_API ACsPawn : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	bool IsPlacedInWorld;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPawn_OnTick OnTick_ScriptEvent;

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

	virtual bool IsOnBoardCompleted_Game();
	virtual void OnTick_HandleSetup();

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

	virtual void ApplyData_Character();

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

#pragma endregion Weapons

// Managers
#pragma region
public:

	virtual class ACsManager_Inventory* GetMyManager_Inventory();

#pragma endregion Managers
};