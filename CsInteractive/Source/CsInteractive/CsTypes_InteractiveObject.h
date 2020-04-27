// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_InteractiveObject.generated.h"
#pragma once

class UObject;

struct CSINTERACTIVE_API ICsInteractiveObjectInfo
{
	virtual UObject* GetInstigator() = 0;

	virtual FVector GetLocation() = 0;
};

USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FCsScriptInteractiveObjectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;

	FCsScriptInteractiveObjectInfo()
	{
		Reset();
	}
	virtual ~FCsScriptInteractiveObjectInfo() {}

	virtual void Reset()
	{
		Instigator.Reset();
		Location = FVector::ZeroVector;
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }
};

// ICsInteractiveObjectHoldParams
#pragma region

class UObject;
class USceneComponent;

struct CSINTERACTIVE_API ICsInteractiveObjectHoldParams
{
public:

	virtual ~ICsInteractiveObjectHoldParams() {}

	virtual UObject* GetInstigator() const = 0;
	
	virtual USceneComponent* GetHoldingObject() const = 0;

	virtual const FHitResult& GetHitResult() const = 0;
};

#pragma endregion ICsInteractiveObjectHoldParams

// FCsInteractiveObjectHoldParams
#pragma region

class UObject;
class USceneComponent;

struct CSINTERACTIVE_API FCsInteractiveObjectHoldParams : public ICsInteractiveObjectHoldParams
{
public:

	UObject* Instigator;

	USceneComponent* HoldingObject;

	FHitResult HitResult;

	FCsInteractiveObjectHoldParams() :
		Instigator(nullptr),
		HoldingObject(nullptr),
		HitResult()
	{
	}

// ICsInteractiveObjectHoldParams
#pragma region

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE USceneComponent* GetHoldingObject() const
	{
		return HoldingObject;
	}

	FORCEINLINE const FHitResult& GetHitResult() const
	{
		return HitResult;
	}
	
#pragma endregion ICsInteractiveObjectHoldParams
};

#pragma endregion FCsInteractiveObjectHoldParams

// FCsScriptInteractiveObjectHoldParams
#pragma region

class UObject;
class USceneComponent;

USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FCsScriptInteractiveObjectHoldParams
{
	GENERATED_USTRUCT_BODY()

	/** Object that is initiating the Hold interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/** The Object that will be physically performing the Hold interaction. 
	    i.e. This is usually the Object that the Interactive Object will attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* HoldingObject;

	/** HitResult when the Hold interaction takes place. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;

	FCsScriptInteractiveObjectHoldParams() :
		Instigator(nullptr),
		HoldingObject(nullptr),
		HitResult()
	{
	}

	FCsInteractiveObjectHoldParams ConvertToNonScriptContainer() const
	{
		FCsInteractiveObjectHoldParams Params;
		Params.Instigator = Instigator;
		Params.HoldingObject = HoldingObject;
		Params.HitResult = HitResult;
		return Params;
	}
};

#pragma endregion FCsScriptInteractiveObjectHoldParams