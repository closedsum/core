// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsDataRootSetContainer.generated.h"

// FCsDataRootSetContainer
#pragma region

class UObject;
class UClass;
class ICsGetDataRootSet;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataRootSetContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Load", EditAnywhere, meta = (MustImplement = "/Script/CsCore.CsGetDataRootSet"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UClass* Data_Class;

	ICsGetDataRootSet* Interface;

	FCsDataRootSetContainer() :
		Data(nullptr),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Interface(nullptr)
	{
	}

	FORCEINLINE UObject* GetObject() const { return Data_Internal;}

	template<typename T>
	FORCEINLINE T* GetObject() const { return Cast<T>(GetObject()); }

	FORCEINLINE UObject* GetObjectChecked(const FString& Context) const
	{
		checkf(Data_Internal, TEXT("%s: Data_Internal is NULL."), *Context);
		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE UObject* GetObjectChecked(const FString& Context) const
	{
		UObject* O = GetObjectChecked(Context);
		T* Other   = Cast<T>(O);

		checkf(Other, TEXT("%s: Data_Internal is NOT of type: %s."), *Context, *(T::StaticClass()->GetName()));
		return Other;
	}

	FORCEINLINE UObject* GetSafeObject(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Data_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%: Data_Internal is NULL."), *Context));
			return nullptr;
		}
		return Data_Internal;
	}

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	FORCEINLINE ICsGetDataRootSet* Get() const { return Interface; }

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context) const
	{
		T* Slice = Cast<T>(Data_Internal);

		checkf(Slice, TEXT("%s: Failed to cast Data_Internal to type: T."), *Context);

		return Slice;
	}
};

#pragma endregion FCsDataRootSetContainer