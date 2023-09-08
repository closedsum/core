// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsGameEvent.generated.h"

// GameEvent
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameEvent)

struct CSCORE_API EMCsGameEvent : public TCsEnumStructMap<FECsGameEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameEvent, FECsGameEvent, uint8)
};

namespace NCsGameEvent
{
	typedef FECsGameEvent Type;
	typedef EMCsGameEvent EnumMapType;

	extern CSCORE_API const Type Default__MousePositionXY__;
	extern CSCORE_API const Type Default__MouseLeftButtonPressed__;
	extern CSCORE_API const Type Default__MouseLeftButtonReleased__;
	extern CSCORE_API const Type Default__MouseRightButtonPressed__;
	extern CSCORE_API const Type Default__MouseRightButtonReleased__;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);

	FORCEINLINE bool IsMousePosition(const FECsGameEvent& Event) { return Event == Default__MousePositionXY__; }
}

#pragma endregion GameEvent

// Rep_GameEvent
#pragma region

namespace ECsRep_GameEvent
{
	enum BitMask : int32;
}

#define CS_MAX_REP_GAME_EVENTS 32
typedef ECsRep_GameEvent::BitMask TCsRep_GameEvent;

#pragma endregion Rep_GameEvent

// FCsGameEventInfo
#pragma region

struct FCsGameEventDefinition;
struct FCsInputCompletedValue;

/**
*
*/
USTRUCT(BlueprintType)
struct FCsGameEventInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Game Event")
	FECsGameEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Game Event")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Game Event")
	FVector3f Location;

private:

	FCsGameEventDefinition* Definition;

public:

	FCsGameEventInfo() :
		Event(),
		Value(0.0f),
		Location(0.0f),
		Definition(nullptr)
	{
	}

	FCsGameEventInfo(const FECsGameEvent& InEvent, const float& InValue, const FVector3f& InLocation)
	{
		Event = InEvent;
		Value = InValue;
		Location = InLocation;
		Definition = nullptr;
	}

	FORCEINLINE FCsGameEventInfo& operator=(const FCsGameEventInfo& B)
	{
		Event = B.Event;
		Value = B.Value;
		Location = B.Location;
		return *this;
	}

	FORCEINLINE void SetDefinition(FCsGameEventDefinition* InDefinition){ Definition = InDefinition; }
	FORCEINLINE const FCsGameEventDefinition* GetDefinition() const { return Definition; }

	FORCEINLINE void Reset()
	{
		Event = EMCsGameEvent::Get().GetMAX();
		Value = 0.0f;
		Location = FVector3f::ZeroVector;
		Definition = nullptr;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = nullptr) const
	{
		if (!EMCsGameEvent::Get().IsValidEnum(Event))
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Event: %s is NOT Valid."), *Context, Event.ToChar()));
			return false;
		}
		return true;
	}

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(IsValid(Context, nullptr), TEXT("%s: Info is NOT Valid."), *Context);
		return true;
	}

	void ApplyInputCompletedValue(const FCsInputCompletedValue* CompletedValue);
};

#pragma endregion FCsGameEventInfo