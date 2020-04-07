// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_AnimInstance_Character.generated.h"
#pragma once

// FCsDataAnimInstance_CharacterPtr
#pragma region

class UCsData_Character;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataAnimInstance_CharacterPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCsData_Character> Data;

	TSoftClassPtr<UCsData_Character> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<UCsData_Character> Data_Internal;

public:
	FCsDataAnimInstance_CharacterPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterPtr& operator=(const FCsDataAnimInstance_CharacterPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_Character* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}
	
	FORCEINLINE bool HasChanged() { return Data != Last_Data; }
	FORCEINLINE void Update() { Last_Data = Data; }
};

#pragma endregion FCsDataAnimInstance_CharacterPtr

// FCsDataAnimInstance_CharacterMeshSkinPtr
#pragma region

class UCsData_CharacterMeshSkin;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataAnimInstance_CharacterMeshSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCsData_CharacterMeshSkin> Data;

	TSoftClassPtr<UCsData_CharacterMeshSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<UCsData_CharacterMeshSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMeshSkinPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterMeshSkinPtr& operator=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_CharacterMeshSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE bool HasChanged() { return Data != Last_Data; }
	FORCEINLINE void Update() { Last_Data = Data; }
};

#pragma endregion FCsDataAnimInstance_CharacterMeshSkinPtr

// FCsDataAnimInstance_CharacterMaterialSkinPtr
#pragma region

class UCsData_CharacterMaterialSkin;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataAnimInstance_CharacterMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCsData_CharacterMaterialSkin> Data;

	TSoftClassPtr<UCsData_CharacterMaterialSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<UCsData_CharacterMaterialSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMaterialSkinPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterMaterialSkinPtr& operator=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_CharacterMaterialSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE bool HasChanged() { return Data != Last_Data; }
	FORCEINLINE void Update() { Last_Data = Data; }
};

#pragma endregion FCsDataAnimInstance_CharacterMaterialSkinPtr