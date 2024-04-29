// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsTypesLog.h"

#include "CsTypes_AnimMontage.generated.h"

// FCsAnimMontage_PlayParams
#pragma region

class UAnimMontage;

// NCsAnimMontage::NPlay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnimMontage, NPlay, FParams)

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontage_PlayParams
{
	GENERATED_USTRUCT_BODY()

	/** The AnimMontage to Play. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Anim")
	UAnimMontage* Anim;

	/** Whether it is okay to Play over an existing (i.e. SAME) animatiom that is playing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Anim")
	bool bPlayOverExisting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Anim")
	float PlayRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float TimeToStartAt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Anim")
	bool bStopAll;

public:

	FCsAnimMontage_PlayParams() :
		Anim(nullptr),
		bPlayOverExisting(true),
		PlayRate(1.0f),
		TimeToStartAt(0.0f),
		bStopAll(true)
	{
	}

#define ParamsType NCsAnimMontage::NPlay::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

class UAnimMontage;

namespace NCsAnimMontage
{
	namespace NPlay
	{
		struct CSTYPES_API FParams
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimMontage*)
			CS_DECLARE_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DECLARE_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DECLARE_MEMBER_WITH_PROXY(bStopAll, bool)

		public:
		
			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bPlayOverExisting, true),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeToStartAt, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bStopAll, false)
			{
				CS_CTOR_SET_MEMBER_PROXY(Anim);
				CS_CTOR_SET_MEMBER_PROXY(bPlayOverExisting);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(TimeToStartAt);
				CS_CTOR_SET_MEMBER_PROXY(bStopAll);
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			FParams(FParams& B)
			{
				Copy(B);
			}

			void Copy(const FParams& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Anim);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bPlayOverExisting);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, PlayRate);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, TimeToStartAt);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bStopAll);
			}

			static FParams Make(const FCsAnimMontage_PlayParams& B)
			{
				FParams P;
				P.SetAnim(B.Anim);
				P.SetbPlayOverExisting(B.bPlayOverExisting);
				P.SetPlayRate(B.PlayRate);
				P.SetTimeToStartAt(B.TimeToStartAt);
				P.SetbStopAll(B.bStopAll);
				return P;
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimMontage)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			FORCEINLINE const bool& ShouldPlayOverExisting() const { return GetbPlayOverExisting(); }
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bStopAll, bool)
			FORCEINLINE const bool& ShouldStopAll() const { return GetbStopAll(); }

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsAnimMontage_PlayParams