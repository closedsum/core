// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
#include "Types/CsTypes_AttachDetach.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_FX.generated.h"

// FX
#pragma region

/**
* Enum for FX types
*/
USTRUCT(BlueprintType)
struct CSCORE_API FECsFX : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsFX)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsFX)

struct CSCORE_API EMCsFX final : public TCsEnumStructMap<FECsFX, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsFX, FECsFX, uint8)
};

class UObject;

namespace NCsFX
{
	typedef FECsFX Type;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion FX

// FCsParticleSystem
#pragma region

class UParticleSystem;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsParticleSystem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX")
	TSoftObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "CsCore|FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Particle_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|FX")
	UParticleSystem* Particle_Internal;

public:
	FCsParticleSystem() :
		Particle(nullptr),
		Particle_LoadFlags(0),
		Particle_Internal(nullptr)
	{
	}

	FORCEINLINE UParticleSystem* Get() const
	{
		return Particle_Internal;
	}
};

#pragma endregion FCsParticleSystem

// FXPriority
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsFXPriority : uint8
{
	Low				  UMETA(DisplayName = "Low"),
	Medium			  UMETA(DisplayName = "Medium"),
	High			  UMETA(DisplayName = "High"),
	ECsFXPriority_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsFXPriority final : public TCsEnumMap<ECsFXPriority>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXPriority, ECsFXPriority)
};

namespace NCsFXPriority
{
	typedef ECsFXPriority Type;

	namespace Ref
	{
		extern CSCORE_API const Type Low;
		extern CSCORE_API const Type Medium;
		extern CSCORE_API const Type High;
		extern CSCORE_API const Type ECsFXPriority_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FXPriority

// FXDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate an FX.
*/
UENUM(BlueprintType)
enum class ECsFXDeallocateMethod : uint8
{
	/** If an FX is attached to a parent object,
		  LifeTime == 0.of means the FX object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the FX object.
		If an FX is NOT attached to a parent object,
		  LifeTime == 0.0f means the FX object will stay active forever.
		  LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
		   the FX object has been allocated. */
	LifeTime				  UMETA(DisplayName = "LifeTime"),
	/** */
	Complete				  UMETA(DisplayName = "Complete"),
	ECsFXDeallocateMethod_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsFXDeallocateMethod final : public TCsEnumMap<ECsFXDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXDeallocateMethod, ECsFXDeallocateMethod)
};

namespace NCsFXDeallocateMethod
{
	typedef ECsFXDeallocateMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type LifeTime;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsFXDeallocateMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsFX
{
	enum class EDeallocateMethod : uint8
	{
		/** If an FX is attached to a parent object,
		  LifeTime == 0.of means the FX object will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the FX object.
		If an FX is NOT attached to a parent object,
		  LifeTime == 0.0f means the FX object will stay active forever.
		  LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
		   the FX object has been allocated. */
		LifeTime,
		/** */
		Complete
	};

	struct CSCORE_API EMDeallocateMethod final : public TCsEnumMap<EDeallocateMethod>
	{
		CS_ENUM_MAP_BODY(EMDeallocateMethod, EDeallocateMethod)
	};

	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EDeallocateMethod Type;

			extern CSCORE_API const Type LifeTime;
			extern CSCORE_API const Type Complete;
		}
	}
}

#pragma endregion FXDeallocateMethod

// FCsNiagaraSystem
#pragma region

class UNiagaraSystem;

/**
* Container for holding a soft and hard reference to an FX System.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsNiagaraSystem
{
	GENERATED_USTRUCT_BODY()

public:

	/** Soft reference to an FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|FX")
	TSoftObjectPtr<UNiagaraSystem> FX;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "CsCore|FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 FX_LoadFlags;

	/** Hard reference to an FX System. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|FX")
	UNiagaraSystem* FX_Internal;

	FCsNiagaraSystem() :
		FX(nullptr),
		FX_LoadFlags(0),
		FX_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UNiagaraSystem.
	*
	* return System
	*/
	FORCEINLINE UNiagaraSystem* Get() const { return FX_Internal; }

	/**
	* Get the pointer to the Hard reference to the UNiagaraSystem asset.
	*
	* return System
	*/
	FORCEINLINE UNiagaraSystem** GetPtr() { return &FX_Internal; }

	/**
	* Get the Hard reference to the UNiagaraSystem asset.
	*
	* @param Context	The calling context.
	* return			System
	*/
	FORCEINLINE UNiagaraSystem* GetChecked(const FString& Context) const
	{
		checkf(FX.ToSoftObjectPath().IsValid(), TEXT("%s: FX is NULL."), *Context);

		checkf(FX_Internal, TEXT("%s: FX has NOT been loaded from Path @ %s."), *Context, *(FX.ToSoftObjectPath().ToString()));

		return FX_Internal;
	}

	/**
	* Get the Hard reference to the UNiagaraSystem asset.
	*
	* return System
	*/
	FORCEINLINE UNiagaraSystem* GetChecked() const
	{
		checkf(FX.ToSoftObjectPath().IsValid(), TEXT("FCsNiagaraSystem::GetChecked: FX is NULL."));

		checkf(FX_Internal, TEXT("FCsNiagaraSystem::GetChecked: FX has NOT been loaded from Path @ %s."), *(FX.ToSoftObjectPath().ToString()));

		return FX_Internal;
	}

	/**
	* Safely get the Hard reference to the UNiagaraSystem asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			System
	*/
	UNiagaraSystem* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!FX.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: FX is NULL."), *Context));
			return nullptr;
		}

		if (!FX_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: FX has NOT been loaded from Path @ %s."), *Context, *(FX.ToSoftObjectPath().ToString())));
		}
		return FX_Internal;
	}

	/**
	* Safely get the Hard reference to the UNiagaraSystem asset.
	*
	* return Material
	*/
	UNiagaraSystem* GetSafe()
	{
		if (!FX.ToSoftObjectPath().IsValid())
			return nullptr;
		return FX_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsNiagaraSystem

// FXAttachPoint
#pragma region

/**
* Type for where the FX object should be attached to on a Parent object.
*/
UENUM(BlueprintType)
enum class ECsFXAttachPoint : uint8
{
	/** If the Parent object is of type: USkeletalMeshComponent then attach to the 
		root bone, otherwise attach to the object normally. */
	None				UMETA(DisplayName = "None"),
	/** Valid only when the Parent object to attach to is of type: USkeletalMeshComponent. */
	Bone				UMETA(DisplayName = "Bone"),
	/** Valid only when the Parent object to attach to is of type: USkeletalMeshComponent. */
	Socket				UMETA(DisplayName = "Socket"),
	ECsFXAttachPoint_MAX UMETA(Hidden),
};

struct CSCORE_API EMCsFXAttachPoint final : public TCsEnumMap<ECsFXAttachPoint>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXAttachPoint, ECsFXAttachPoint)
};

namespace NCsFXAttachPoint
{
	typedef ECsFXAttachPoint Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Bone;
		extern CSCORE_API const Type Socket;
		extern CSCORE_API const Type ECsFXAttachPoint_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FXAttachPoint

// FXParameterValue
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsFXParameterValue : uint8
{
	Int						UMETA(DisplayName = "Int"),
	Float					UMETA(DisplayName = "Float"),
	Vector					UMETA(DisplayName = "Vector"),
	ECsFXParameterValue_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsFXParameterValue final : public TCsEnumMap<ECsFXParameterValue>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXParameterValue, ECsFXParameterValue)
};

namespace NCsFXParameterValue
{
	typedef ECsFXParameterValue Type;

	namespace Ref
	{
		extern CSCORE_API const Type Int;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type Vector;
		extern CSCORE_API const Type ECsFXParameterValue_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion FXParameterValue

// FCsFXParameterInt
#pragma region

// NCsFX::NParameter::NInt::FIntType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NInt, FIntType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFXParameterInt
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Niagara Int Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	/** Value to set for the Niagara Int Parameter with Name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	int32 Value;

	FCsFXParameterInt() :
		Name(NAME_None),
		Value(0)
	{
	}

#define ParameterType NCsFX::NParameter::NInt::FIntType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
		return true;
	}
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFXParameterInt

// FCsFXParameterFloat
#pragma region

// NCsFX::NParameter::NFloat::FFloatType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NFloat, FFloatType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFXParameterFloat
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Niagara Int Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	/** Value to set for the Niagara Float Parameter with Name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Value;

	FCsFXParameterFloat() :
		Name(NAME_None),
		Value(0)
	{
	}

#define ParameterType NCsFX::NParameter::NFloat::FFloatType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
		return true;
	}
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFXParameterFloat

// FCsFXParameterVector
#pragma region

// NCsFX::NParameter::NVector::FVectorType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NVector, FVectorType)

/**
* Container holding information for Niagara Vector Parameter
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFXParameterVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FVector Value;

public:

	FCsFXParameterVector() :
		Name(NAME_None),
		Value(0.0f)
	{
	}

#define ParameterType NCsFX::NParameter::NVector::FVectorType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
		return true;
	}
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFXParameterVector

// FCsFX_Parameter_Scaled_Int
#pragma region

// NCsFX::NParameter::NScaled::NInt::FIntType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NScaled, NInt, FIntType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Parameter_Scaled_Int
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Niagara Int Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	/** Whether Value should be used for applying any scaling or just
		use the default Value from the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_bValue"))
	bool bValue;

	/** Value to set for the Niagara Int Parameter with Name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_Value"))
	int32 Value;

	/** Whether to apply the FX scale inversely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool bInverse;

	/** Additional scale to apply to Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Scale;

	FCsFX_Parameter_Scaled_Int() :
		Name(NAME_None),
		bValue(true),
		Value(0),
		bInverse(false),
		Scale(1.0f)
	{
	}

#define ParameterType NCsFX::NParameter::NScaled::NInt::FIntType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFX_Parameter_Scaled_Int

// FCsFX_Parameter_Scaled_Float
#pragma region

// NCsFX::NParameter::NScaled::NFloat::FFloatType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NScaled, NFloat, FFloatType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Parameter_Scaled_Float
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Niagara Float Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	/** Whether Value should be used for applying any scaling or just
		use the default Value from the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_bValue"))
	bool bValue;

	/** Value to set for the Niagara Float Parameter with Name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_Value"))
	float Value;

	/** Whether to apply the FX scale inversely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool bInverse;

	/** Additional scale to apply to Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Scale;

	FCsFX_Parameter_Scaled_Float() :
		Name(NAME_None),
		bValue(false),
		Value(0.0f),
		bInverse(false),
		Scale(1.0f)
	{
	}

#define ParameterType NCsFX::NParameter::NScaled::NFloat::FFloatType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFX_Parameter_Scaled_Float

// FCsFX_Parameter_Scaled_Vector
#pragma region

// NCsFX::NParameter::NScaled::NFloat::FFloatType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NScaled, NVector, FVectorType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Parameter_Scaled_Vector
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Niagara Vector Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Name;

	/** Whether Value should be used for applying any scaling or just
		use the default Value from the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_bValue"))
	bool bValue;

	/** Value to set for the Niagara Vector Parameter with Name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ScriptName = "m_Value"))
	FVector Value;

	/** Whether to apply the FX scale inversely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool bInverse;

	/** Additional scale to apply to Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Scale;

	FCsFX_Parameter_Scaled_Vector() :
		Name(NAME_None),
		bValue(false),
		Value(0.0f),
		bInverse(false),
		Scale(1.0f)
	{
	}

#define ParameterType NCsFX::NParameter::NScaled::NVector::FVectorType
	void CopyToParams(ParameterType* Params);
	void CopyToParamsAsValue(ParameterType* Params) const;
#undef ParameterType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFX_Parameter_Scaled_Vector

// FCsFX_Parameters_Scaled
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Parameters_Scaled
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFX_Parameter_Scaled_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFX_Parameter_Scaled_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFX_Parameter_Scaled_Vector> Vectors;

	FCsFX_Parameters_Scaled() :
		Ints(),
		Floats(),
		Vectors()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE void Reset()
	{
		Ints.Reset(Ints.Max());
		Floats.Reset(Floats.Max());
		Vectors.Reset(Vectors.Max());
	}
};

#pragma endregion FCsFX_Parameters_Scaled

// FCsFX
#pragma region

class UNiagaraSystem;

/**
* Container holding general information for an FX System.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFX
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsFX Invalid;

public:

	/** Soft reference to an FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TSoftObjectPtr<UNiagaraSystem> FX;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 FX_LoadFlags;

	/** Hard reference to an FX System. */
	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|FX")
	UNiagaraSystem* FX_Internal;

	/** The FX Type. This is used to group FX into different categories 
	    and can be used by a Manager pooling FX objects to Spawn the correct
		FX object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FECsFX Type;
	
	/** Condition to determine when to deallocate the FX object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	ECsFXDeallocateMethod DeallocateMethod;

private:

	NCsFX::EDeallocateMethod* DeallocateMethod_Internal;

public:

	/** Valid if the DeallocateMethod == ECsFXDeallocateMethod::LifeTime.
		- If an FX IS attached to a Parent object, 
		   LifeTime == 0.of means the FX object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the FX object.
	    - If an FX is NOT attached to a Parent object,
		   LifeTime == 0.0f means the FX object will stay active forever.
		   LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
	        the FX object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** The time to wait after LifeTime or Complete (completion of the FX) before gracefully
		deallocating the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DeathTime;

	/** Whether to Hide the FX when FX->GetCache()->QueueDeallocate() is called.
		The main purpose of this is for FX that should be deallocated "immediately" after
		QueueDeallocate() is called. Normally, the FX is allowed to "complete" / deactivate
		gracefully. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool bHideOnQueueDeallocate;

	/** Valid if the FX is attached to a Parent object or when an FX object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the FX will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the FX is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FName Bone;

	/** Which of the components of Transform to apply to the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX", meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the FX.
		If the FX is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FTransform Transform;

	/** Whether the Transform's Scale should be applied to the FX.
		If NOT, the object defaults to FVector::OneVector or just the scale of the object the FX
		is attached to.
		NOTE: Usually when scaling parameters, this should be FALSE. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	bool bApplyTransformScale;

// TODO: Eventually deprecate and combine into 1 struct

	/** List of all Niagara Int Parameters to change on the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFXParameterInt> IntParameters;

	/** List of all Niagara Float Parameters to change on the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFXParameterFloat> FloatParameters;

	/** List of all Niagara Vector Parameters to change on the FX System. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	TArray<FCsFXParameterVector> VectorParameters;

	/** List of all Niagara Parameters that will get scaled with the FX scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FCsFX_Parameters_Scaled ScaledParameters;

public:

	FCsFX() :
		FX(nullptr),
		FX_LoadFlags(0),
		FX_Internal(nullptr),
		Type(),
		DeallocateMethod(ECsFXDeallocateMethod::Complete),
		DeallocateMethod_Internal(nullptr),
		LifeTime(0.0f),
		DeathTime(0.0f),
		bHideOnQueueDeallocate(false),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity),
		bApplyTransformScale(true),
		IntParameters(),
		FloatParameters(),
		VectorParameters(),
		ScaledParameters()
	{
		DeallocateMethod_Internal = (NCsFX::EDeallocateMethod*)&DeallocateMethod;
	}
	
	FORCEINLINE FCsFX& operator=(const FCsFX& B)
	{
		FX = B.FX;
		FX_LoadFlags = B.FX_LoadFlags;
		FX_Internal = B.FX_Internal;
		Type = B.Type;
		DeallocateMethod = B.DeallocateMethod;
		DeallocateMethod_Internal = (NCsFX::EDeallocateMethod*)&DeallocateMethod;
		LifeTime = B.LifeTime;
		bHideOnQueueDeallocate = B.bHideOnQueueDeallocate;
		AttachmentTransformRules = B.AttachmentTransformRules;
		Bone = B.Bone;
		TransformRules = B.TransformRules;
		Transform = B.Transform;
		bApplyTransformScale = B.bApplyTransformScale;

		IntParameters.Reset(FMath::Max(IntParameters.Max(), B.IntParameters.Num()));

		for (const FCsFXParameterInt& Param : B.IntParameters)
		{
			IntParameters.Add(Param);
		}

		FloatParameters.Reset(FMath::Max(FloatParameters.Max(), B.FloatParameters.Num()));

		for (const FCsFXParameterFloat& Param : B.FloatParameters)
		{
			FloatParameters.Add(Param);
		}

		VectorParameters.Reset(FMath::Max(VectorParameters.Max(), B.VectorParameters.Num()));

		for (const FCsFXParameterVector& Param : B.VectorParameters)
		{
			VectorParameters.Add(Param);
		}
		return *this;
	}

	FORCEINLINE void UpdateInternalPtrs()
	{
		UpdateDeallocateMethodPtr();
	}

	FORCEINLINE void UpdateDeallocateMethodPtr() { DeallocateMethod_Internal = (NCsFX::EDeallocateMethod*)&DeallocateMethod; }

	#define DeallocateMethodType NCsFX::EDeallocateMethod
	FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *((NCsFX::EDeallocateMethod*)(&DeallocateMethod)); }
	#undef DeallocateMethodType

	/**
	* Get the Hard reference to the FX System.
	*
	* return FX System
	*/
	FORCEINLINE UNiagaraSystem* Get() const { return FX_Internal; }

	/**
	* Get the Hard reference to the FX System.
	*
	* @param Context	The calling context.
	* return			FX System
	*/
	FORCEINLINE UNiagaraSystem* GetChecked(const FString& Context) const
	{
		checkf(FX.ToSoftObjectPath().IsValid(), TEXT("%s: FX is NULL."), *Context);

		checkf(FX_Internal, TEXT("%s: FX has NOT been loaded from Path @ %s."), *Context, *(FX.ToSoftObjectPath().ToString()));

		return FX_Internal;
	}

	/**
	* Get the Hard reference to the FX System.
	*
	* return FX System
	*/
	FORCEINLINE UNiagaraSystem* GetChecked() const
	{
		checkf(FX.ToSoftObjectPath().IsValid(), TEXT("FCsFX::GetChecked: FX is NULL."));

		checkf(FX_Internal, TEXT("FCsFX::GetChecked: FX has NOT been loaded from Path @ %s."), *(FX.ToSoftObjectPath().ToString()));

		return FX_Internal;
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void Reset();
};

#pragma endregion FCsFX

// NCsFX::NPayload::EChange
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsFXPayloadChange : uint8
{
	FXSystem						UMETA(DisplayName = "FX System"),							// 0
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),				// 1
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),				// 2
	SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap to Target not Including Scale"),	// 3
	SnapToTargetIncludingScale		UMETA(DisplayName = "Snap to Target Including Scale"),		// 4
	Transform						UMETA(DisplayName = "Transform"),							// 5
	Parameter						UMETA(DisplayName = "Parameter"),							// 6
};

struct CSCORE_API EMCsFXPayloadChange : public TCsEnumFlagMap<ECsFXPayloadChange>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsFXPayloadChange, ECsFXPayloadChange)
};

namespace NCsFXPayloadChange
{
	typedef ECsFXPayloadChange Type;

	namespace Ref
	{
		extern CSCORE_API const Type FXSystem;
		extern CSCORE_API const Type KeepRelativeTransform;
		extern CSCORE_API const Type KeepWorldTransform;
		extern CSCORE_API const Type SnapToTargetNotIncludingScale;
		extern CSCORE_API const Type SnapToTargetIncludingScale;
		extern CSCORE_API const Type Transform;
		extern CSCORE_API const Type Parameter;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#define CS_FX_PAYLOAD_CHANGE_NONE 0

namespace NCsFX
{
	namespace NPayload
	{
		enum class EChange : uint32
		{
			FXSystem						= 1 << 0,
			KeepRelativeTransform			= 1 << 1,
			KeepWorldTransform				= 1 << 2,
			SnapToTargetNotIncludingScale	= 1 << 3,
			SnapToTargetIncludingScale		= 1 << 4,
			Transform						= 1 << 5,
			Parameter						= 1 << 6
		};

		namespace NChange
		{
			FORCEINLINE bool HasAttach(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return true;
				return false;
			}

			FORCEINLINE bool HasAttach(const uint32& Mask, const ECsAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return true;
				return false;
			}

			FORCEINLINE uint32 GetAttachAsMask(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return (uint32)EChange::KeepRelativeTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return (uint32)EChange::KeepWorldTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return (uint32)EChange::SnapToTargetNotIncludingScale;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return (uint32)EChange::SnapToTargetIncludingScale;
				return 0;
			}

			FORCEINLINE EChange FromTransformAttachmentRule(const ECsAttachmentTransformRules& Rules)
			{
				if (Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return EChange::KeepRelativeTransform;
				if (Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return EChange::KeepWorldTransform;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return EChange::SnapToTargetNotIncludingScale;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			struct CSCORE_API FCounter
			{
			protected:
				FCounter() :
					Preserved(0),
					PreservedPercent(0.0f),
					Changed(0),
					ChangedPercent(0.0f),
					Cleared(0),
					ClearedPercent(0.0f),
					Total(0)
				{
				}
				FCounter(const FCounter&) = delete;
				FCounter(FCounter&&) = delete;
			public:
				virtual ~FCounter() {}
			private:
				uint32 Preserved;
				float PreservedPercent;
				uint32 Changed;
				float ChangedPercent;
				uint32 Cleared;
				float ClearedPercent;
				uint32 Total;
			public:
				static FCounter& Get()
				{
					static FCounter Instance;
					return Instance;
				}

			public:

				FORCEINLINE void AddPreserved()
				{
					++Preserved;
					++Total;
					PreservedPercent = (float)Preserved/(float)Total;
				}

				FORCEINLINE void AddChanged()
				{
					++Changed;
					++Total;
					ChangedPercent = (float)Changed/(float)Total;
				}

				FORCEINLINE void AddCleared()
				{
					++Cleared;
					++Total;
					ClearedPercent = (float)Cleared/(float)Total;
				}

				void Reset()
				{
					Preserved = 0;
					PreservedPercent = 0.0f;
					Changed = 0;
					ChangedPercent = 0.0f;
					Cleared = 0;
					ClearedPercent = 0.0f;
					Total = 0;
				}

				FORCEINLINE FString ToString() const
				{
					return FString::Printf(TEXT("Preserved: (%3.3f = %d/%d) Changed: (%3.3f = %d/%d) Cleared: (%3.3f = %d/%d)"), PreservedPercent, Preserved, Total, ChangedPercent, Changed, Total, ClearedPercent, Cleared, Total);
				}
			};
		}
	}
}

#pragma endregion NCsFX::NPayload::EChange