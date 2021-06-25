// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsInteractiveLog.h"

#include "CsInteractiveObject_Hover_Params.generated.h"

class UObject;
class USceneComponent;

namespace NCsInteractive
{
	namespace NObject
	{
		namespace NHover
		{
			namespace NParams
			{
				struct CSINTERACTIVE_API IParams
				{
				public:

					virtual ~IParams() {}

					/** The object instigating the interaction with an object that 
						implements the interface: ICsInteractiveObject. */
					virtual UObject* GetInstigator() const = 0;

					/* The object "physically" doing the interacting with an object that 
					   implements the interface: ICsInteractiveObject. */
					virtual USceneComponent* GetObject() const = 0;

					/** Collision information related from the object interacting with an object that
						implements the interface: ICsInteractiveObject. */
					virtual const FHitResult& GetHitResult() const = 0;
				};
			}
		}
	}
}

// FCsInteractiveObject_Hover_Params
#pragma region

class UObject;
class USceneComponent;

// NCsInteractive::NObject::NHover::NParams::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NHover, NParams, FImpl)

USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FCsInteractiveObject_Hover_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** The object instigating the interaction with an object that
		implements the interface: ICsInteractiveObject. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/* The object "physically" doing the interacting with an object that
	   implements the interface: ICsInteractiveObject. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;

	/** Collision information related from the object interacting with an object that
		implements the interface: ICsInteractiveObject. */
	FCsInteractiveObject_Hover_Params() :
		Instigator(nullptr),
		Object(nullptr),
		HitResult()
	{
	}

#define ParamsType NCsInteractive::NObject::NHover::NParams::FImpl
	void CopyToParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsInteractive::FLog::Warning) const;
};

class UObject;
class USceneComponent;

namespace NCsInteractive
{
	namespace NObject
	{
		namespace NHover
		{
			namespace NParams
			{
			#define ParamsType NCsInteractive::NObject::NHover::NParams::IParams

				struct CSINTERACTIVE_API FImpl : public ParamsType 
				{
				public:

				// (ParamsType) NCsInteractive::NObject::NHover::NParams::IParams

					UObject* Instigator;

					USceneComponent* Object;

					FHitResult HitResult;

					FImpl() :
						Instigator(nullptr),
						Object(nullptr),
						HitResult()
					{
					}

					~FImpl(){}

				// (ParamsType) NCsInteractive::NObject::NHover::NParams::IParams
				#pragma region
				public:

					FORCEINLINE UObject* GetInstigator() const { return Instigator; }

					FORCEINLINE USceneComponent* GetObject() const { return Object; }

					FORCEINLINE const FHitResult& GetHitResult() const { return HitResult; }

				#pragma endregion NCsInteractive::NObject::NHover::NParams::IParams
				};

			#undef ParamsType
			}
		}
	}
}

#pragma endregion FCsInteractiveObject_Hover_Params

class UObject;
class USceneComponent;

namespace NCsInteractive
{
	namespace NObject
	{
		namespace NUnHover
		{
			namespace NParams
			{
				struct CSINTERACTIVE_API IParams
				{
				public:

					virtual ~IParams() {}

					/** The object instigating the interaction with an object that
						implements the interface: ICsInteractiveObject. */
					virtual UObject* GetInstigator() const = 0;

					/* The object "physically" doing the interacting with an object 
					   that implements the interface: ICsInteractiveObject. */
					virtual USceneComponent* GetObject() const = 0;

					/** Collision information related from the object interacting with an object that
						implements the interface: ICsInteractiveObject. */
					virtual const FHitResult& GetHitResult() const = 0;
				};
			}
		}
	}
}

// FCsInteractiveObject_UnHover_Params
#pragma region

class UObject;
class USceneComponent;

// NCsInteractive::NObject::NUnHover::NParams::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsInteractive, NObject, NUnHover, NParams, FImpl)

USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FCsInteractiveObject_UnHover_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** The object instigating the interaction with an object that
		implements the interface: ICsInteractiveObject. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/* The object "physically" doing the interacting with an object that
	   implements the interface: ICsInteractiveObject. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;

	/** Collision information related from the object interacting with an object that
		implements the interface: ICsInteractiveObject. */
	FCsInteractiveObject_UnHover_Params() :
		Instigator(nullptr),
		Object(nullptr),
		HitResult()
	{
	}

#define ParamsType NCsInteractive::NObject::NUnHover::NParams::FImpl
	void CopyToParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsInteractive::FLog::Warning) const;
};

class UObject;
class USceneComponent;

namespace NCsInteractive
{
	namespace NObject
	{
		namespace NUnHover
		{
			namespace NParams
			{
			#define ParamsType NCsInteractive::NObject::NUnHover::NParams::IParams

				struct CSINTERACTIVE_API FImpl : public ParamsType 
				{
				public:

				// (ParamsType) NCsInteractive::NObject::NUnHover::NParams::IParams

					UObject* Instigator;

					USceneComponent* Object;

					FHitResult HitResult;

					FImpl() :
						Instigator(nullptr),
						Object(nullptr),
						HitResult()
					{
					}

					~FImpl(){}

				// (ParamsType) NCsInteractive::NObject::NUnHover::NParams::IParams
				#pragma region
				public:

					FORCEINLINE UObject* GetInstigator() const { return Instigator; }

					FORCEINLINE USceneComponent* GetObject() const { return Object; }

					FORCEINLINE const FHitResult& GetHitResult() const { return HitResult; }

				#pragma endregion NCsInteractive::NObject::NUnHover::NParams::IParams
				};

			#undef ParamsType
			}
		}
	}
}

#pragma endregion FCsInteractiveObject_UnHover_Params