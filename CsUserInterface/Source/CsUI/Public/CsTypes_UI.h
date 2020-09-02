// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Engine/DataTable.h"

#include "CsTypes_UI.generated.h"
#pragma once

// FCsUserWidget
#pragma region

class UUserWidget;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UUserWidget> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UUserWidget* Widget_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Widget_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UUserWidget> Widget_SubclassOf;

	FCsUserWidget() :
		Widget(nullptr),
		Widget_LoadFlags(0),
		Widget_Internal(nullptr),
		Widget_Class(nullptr),
		Widget_SubclassOf(nullptr)
	{
	}

	FORCEINLINE UUserWidget* Get() const { return Widget_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Widget_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE TSubclassOf<UUserWidget> GetSubclassOf() const { return Widget_SubclassOf; }
};

#pragma endregion FCsUserWidget