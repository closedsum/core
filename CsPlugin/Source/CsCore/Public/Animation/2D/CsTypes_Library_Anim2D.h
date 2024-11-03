// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
#include "Animation/2D/CsTypes_Anim2D.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Coroutine/CsTypes_Coroutine.h"

#include "CsTypes_Library_Anim2D.generated.h"

// FCsAnim2DTextureFlipbook_Params
#pragma region

struct FCsAnim2DTextureFlipbook_Params;

// ParamsType (NCsAnim::N2D::NTexture::NPlay::NParams::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsAnim, N2D, NTexture, NPlay, NParams, FParams)

namespace NCsAnim2DTextureFlipbook_Params
{
	using ThisType = FCsAnim2DTextureFlipbook_Params;
	using ParamsType = NCsAnim::N2D::NTexture::NPlay::NParams::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSCORE_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// NCsAnim::N2D::NTexture::NPlay::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsAnim, N2D, NTexture, NPlay, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DTextureFlipbook_Params
{
	GENERATED_USTRUCT_BODY()

private:

	CS_DECLARE_STATIC_LOG_WARNING

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UObject* ContextRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Anim|2D")
	FECsUpdateGroup UpdateGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UObject* Owner;

	//OnAbortType OnAbort;

	//OnEndType OnEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UMaterialInstanceDynamic* MID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	FCsAnim2DFlipbookTexture Anim;

	FCsAnim2DTextureFlipbook_Params() :
		ContextRoot(nullptr),
		UpdateGroup(),
		Owner(nullptr),
		MID(nullptr),
		Anim()
	{
	}

	using ParamsType = NCsAnim::N2D::NTexture::NPlay::NParams::FParams;
	using _Impl = NCsAnim2DTextureFlipbook_Params::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;
};

class UObject;
class UMaterialInstanceDynamic;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NPlay
			{
				namespace NParams
				{
					/**
					*/
					struct CSCORE_API FParams
					{
					private:

						CS_DECLARE_STATIC_LOG_WARNING

						using OnAbortType = NCsCoroutine::FOnAbort;
						using OnEndType = NCsCoroutine::FOnEnd;
						using AnimType = NCsAnim::N2D::NTexture::NFlipbook::FFlipbook;

					public:

						/** ContextRoot for the Coroutine Scheduler. This is 
							usually a reference to the GameInstance. */
						UObject* ContextRoot;
		
						FECsUpdateGroup UpdateGroup;

						UObject* Owner;

						OnAbortType OnAbort;

						OnEndType OnEnd;

						TWeakObjectPtr<UMaterialInstanceDynamic> MID;

						AnimType Anim;

						FParams() :
							ContextRoot(nullptr),
							UpdateGroup(),
							Owner(nullptr),
							OnAbort(),
							OnEnd(),
							MID(nullptr),
							Anim()
						{
						}

						AnimType* GetAnimPtr() { return &Anim; }

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

						void Reset()
						{
							ContextRoot = nullptr;
							UpdateGroup = EMCsUpdateGroup::Get().GetMAX();
							Owner = nullptr;
							OnAbort.Unbind();
							OnEnd.Unbind();
							MID = nullptr;
							Anim.Reset();
						}
					};

					struct CSCORE_API FResource : public TCsResourceContainer<FParams>
					{
						~FResource(){}
					};

					#define CS_PARAMS_PAYLOAD_SIZE 256

					struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
					{
						~FManager(){}
					};

					#undef CS_PARAMS_PAYLOAD_SIZE
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DTextureFlipbook_Params

// FCsAnim2DMaterialFlipbook_Params
#pragma region

// NCsAnim::N2D::NMaterial::NPlay::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsAnim, N2D, NMaterial, NPlay, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DMaterialFlipbook_Params
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UObject* ContextRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Anim|2D")
	FECsUpdateGroup UpdateGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UObject* Owner;

	//OnAbortType OnAbort;

	//OnEndType OnEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	UPrimitiveComponent* Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|2D")
	FCsAnim2DMaterialFlipbook Anim;

	FCsAnim2DMaterialFlipbook_Params() :
		ContextRoot(nullptr),
		UpdateGroup(),
		Owner(nullptr),
		Component(nullptr),
		Anim()
	{
	}

#define ParamsType NCsAnim::N2D::NMaterial::NPlay::NParams::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class UObject;
class UPrimitiveComponent;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			namespace NPlay
			{
				namespace NParams
				{
					/**
					*/
					struct CSCORE_API FParams
					{
					#define OnAbortType NCsCoroutine::FOnAbort
					#define OnEndType NCsCoroutine::FOnEnd
					#define AnimType NCsAnim::N2D::NMaterial::NFlipbook::FFlipbook

					public:

						/** ContextRoot for the Coroutine Scheduler. This is 
							usually a reference to the GameInstance. */
						UObject* ContextRoot;
		
						FECsUpdateGroup UpdateGroup;

						UObject* Owner;

						OnAbortType OnAbort;

						OnEndType OnEnd;

						TWeakObjectPtr<UPrimitiveComponent> Component;

						AnimType Anim;

						FParams() :
							ContextRoot(nullptr),
							UpdateGroup(),
							Owner(nullptr),
							OnAbort(),
							OnEnd(),
							Component(nullptr),
							Anim()
						{
						}

						AnimType* GetAnimPtr() { return &Anim; }

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

						void Reset()
						{
							ContextRoot = nullptr;
							UpdateGroup = EMCsUpdateGroup::Get().GetMAX();
							Owner = nullptr;
							OnAbort.Unbind();
							OnEnd.Unbind();
							Component = nullptr;
							Anim.Reset();
						}

					#undef OnAbortType
					#undef OnEndType
					#undef AnimType
					};

					struct CSCORE_API FResource : public TCsResourceContainer<FParams>
					{
						~FResource(){}
					};

					#define CS_PARAMS_PAYLOAD_SIZE 256

					struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
					{
						~FManager(){}
					};

					#undef CS_PARAMS_PAYLOAD_SIZE
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DMaterialFlipbook_Params