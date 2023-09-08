// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/Action/CsInputAction.h"
#include "InputCoreTypes.h"

#include "CsTypes_InputProfile.generated.h"

// FCsInputActionMapping
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	FKey Key;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	float Scale;

	FCsInputActionMapping() :
		Action(),
		Key(),
		Scale(0.0f)
	{
	}

	FCsInputActionMapping(const FECsInputAction& InAction, const FKey& InKey, const float& InScale = 0.0f)
	{
		Action = InAction;
		Key = InKey;
		Scale = InScale;
	}

	FORCEINLINE bool operator==(const FCsInputActionMapping& B) const
	{
		return Action == B.Action &&
			   Key == B.Key &&
			   Scale == B.Scale;
	}

	FORCEINLINE bool operator!=(const FCsInputActionMapping& B) const
	{
		return !(*this == B);
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = nullptr) const;
};

#pragma endregion FCsInputActionMapping

// FCsInputActionMappings
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionMappings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	TArray<FCsInputActionMapping> Mappings;

	FORCEINLINE FCsInputActionMappings& operator=(const FCsInputActionMappings& B)
	{
		Mappings.Reset();

		const int32 Count = B.Mappings.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Mappings.AddDefaulted();
			Mappings[I] = B.Mappings[I];
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputActionMappings& B) const
	{
		if (Mappings.Num() != B.Mappings.Num())
			return false;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Mappings[I] != B.Mappings[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInputActionMappings& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE const FECsInputAction& GetAction(const FKey& Key) const
	{
		for (const FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Key == Key)
				return Mapping.Action;
		}
		return EMCsInputAction::Get().GetMAX();
	}

	FORCEINLINE bool HasAction(const FECsInputAction& Action) const
	{
		for (const FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Action == Action)
				return true;
		}
		return false;
	}

	FORCEINLINE const FKey& GetKey(const FECsInputAction& Action) const 
	{
		for (const FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Action == Action)
				return Mapping.Key;
		}
		return EKeys::Invalid;
	}

	FORCEINLINE FCsInputActionMapping& GetOrAddMapping(const FECsInputAction& Action)
	{
		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Action == Action)
				return Mapping;
		}
		
		FCsInputActionMapping& Mapping = Mappings.AddDefaulted_GetRef();
		Mapping.Action = Action;
		return Mapping;
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = nullptr) const;

	FORCEINLINE bool IsActionAssociatedWithKey(const FECsInputAction& Action, const FKey& Key) const
	{
		for (const FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Action == Action &&
				Mapping.Key == Key)
			{
				return true;
			}
		}
		return false;
	}

	void ConditionalCopyMappingsByActionChecked(const FString& Context, const FCsInputActionMappings& OtherMappings)
	{
		for (const FCsInputActionMapping& Mapping : OtherMappings.Mappings)
		{
			CopyMappingByActionChecked(Context, Mapping);
		}
	}

	void CopyMappingByActionChecked(const FString& Context, const FCsInputActionMapping& Mapping)
	{
		for (FCsInputActionMapping& M : Mappings)
		{
			if (Mapping.Action == M.Action)
			{
				M = Mapping;
				return;
			}
		}
		checkf(0, TEXT("%s: Mappings does NOT contain Action: %s."), *Context, Mapping.Action.ToChar());
	}

	FORCEINLINE void SafeCopyMappingsByAction(const FCsInputActionMappings& OtherMappings)
	{
		for (const FCsInputActionMapping& Mapping : OtherMappings.Mappings)
		{
			SafeCopyMappingByAction(Mapping);
		}
	}

	FORCEINLINE void SafeCopyMappingByAction(const FCsInputActionMapping& Mapping)
	{
		for (FCsInputActionMapping& M : Mappings)
		{
			if (Mapping.Action == M.Action)
			{
				M = Mapping;
				return;
			}
		}
	}

	void ReplaceKey(const FECsInputAction& Action, const FKey& Key)
	{
		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Mapping.Action == Action)
			{
				Mapping.Key = Key;
			}
		}
	}

	void ReplaceActionsChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device) const;
};

#pragma endregion FCsInputActionMappings

// FCsInputProfile
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	uint8 Player;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Input")
	FCsInputActionMappings DeviceMappings[(uint8)ECsInputDevice::ECsInputDevice_MAX];

	FCsInputProfile()
	{
		Player = 0;
	}

	FORCEINLINE const FCsInputActionMappings& GetMappings(const ECsInputDevice& Device) const { return DeviceMappings[(uint8)Device]; }
	FORCEINLINE FCsInputActionMappings& GetMappings(const ECsInputDevice& Device) { return DeviceMappings[(uint8)Device]; }

	FORCEINLINE FCsInputActionMapping& GetMapping(const ECsInputDevice& Device, const FECsInputAction& Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
				return Mapping;
		}
		return Mappings[CS_FIRST];
	}

	FORCEINLINE FCsInputActionMappings* GetMappingsPtr(const ECsInputDevice& Device) { return &(DeviceMappings[(uint8)Device]); }

	FORCEINLINE FKey GetKey(const ECsInputDevice& Device, const FECsInputAction& Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
				return Mapping.Key;
		}
		return EKeys::Invalid;
	}

	FORCEINLINE void SetKey(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
			{
				Mapping.Key	= Key;
				break;
			}
		}
	}

	FORCEINLINE void AddMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FString& KeyName, const FKey& Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();
		Mappings.AddDefaulted();
		FCsInputActionMapping& Mapping = Mappings[Count];
		Mapping.Action	   = Action;
		Mapping.Key		   = Key;
	}

	FORCEINLINE void Reset()
	{
		for (int32 I = 0; I < ECS_INPUT_DEVICE_MAX; ++I)
		{
			DeviceMappings[I].Mappings.Reset();
		}
	}
};

#pragma endregion FCsInputProfile