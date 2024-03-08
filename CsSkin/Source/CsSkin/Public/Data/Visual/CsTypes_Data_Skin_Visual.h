// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"

#include "CsTypes_Data_Skin_Visual.generated.h"

// FCsData_Skin_Visual
#pragma region

class UObject;
class ICsData;

// NCsSkin::NData::NVisual::IVisual
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkin, NData, NVisual, IVisual)

USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skin|Data|Visual", meta = (MustImplement = "/Script/CsCore.CsData_Skin_Visual"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skin|Data|Visual")
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Skin|Data|Visual")
	UObject* Data_Internal;

	FCsData_Skin_VisualPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	T* Get() { return Cast<T>(Get()); }

	FORCEINLINE UObject* GetChecked(const FString& Context) const
	{
		checkf(Data_Internal, TEXT("%s: Data_Internal is NULL."), *Context);

		return Data_Internal;
	}

#define SkinDataType NCsSkin::NData::NVisual::IVisual
	SkinDataType* Load(const FString& Context, const int32& LoadFlags);
#undef SkinDataType

private:

	FORCEINLINE void __Nothing() const {}
};

#pragma endregion FCData_CharacterPtr