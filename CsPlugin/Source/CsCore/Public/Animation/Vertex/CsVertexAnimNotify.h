// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
// Log
#include "Utility/CsLog.h"

#include "CsVertexAnimNotify.generated.h"

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FECsVertexAnimNotify : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsVertexAnimNotify)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsVertexAnimNotify)

struct CSCORE_API EMCsVertexAnimNotify : public TCsEnumStructMap<FECsVertexAnimNotify, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsVertexAnimNotify, FECsVertexAnimNotify, uint8)
};

class UObject;

namespace NCsVertexAnimNotify
{
	typedef FECsVertexAnimNotify Type;
	typedef EMCsVertexAnimNotify EnumMapType;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

// NCsAnim::NVertex::FNotify
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NVertex, FNotify)

/**
* Describes a simple event for a Vertex Anim, animation driven through a material
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsVertexAnimNotify
{
	GENERATED_USTRUCT_BODY()

	/** The event to broadcast at Time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	FECsVertexAnimNotify Notify;

	/** The time from the beginning of the Vertex Anim at which to broadcast the event: Notify. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Time;

	FCsVertexAnimNotify() :
		Notify(),
		Time(0.0f)
	{
	}

#define NotifyType NCsAnim::NVertex::FNotify
	void CopyToNotify(NotifyType* Value);
	void CopyToNotifyAsValue(NotifyType* Value) const;
#undef NotifyType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsAnim
{
	namespace NVertex
	{
		/**
		* Describes a simple event for a Vertex Anim, animation driven through a material
		*/
		struct CSCORE_API FNotify
		{
		public:

			static const FNotify Invalid;

		private:

			bool bTriggered;

			CS_DECLARE_MEMBER_WITH_PROXY(Notify, FECsVertexAnimNotify)
			CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

		public:

			FNotify() :
				bTriggered(false),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Notify),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(Notify);
				CS_CTOR_SET_MEMBER_PROXY(Time);
			}

			FNotify(const FECsVertexAnimNotify& InNotify,
				    const float& InTime) :
				bTriggered(false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Notify, InNotify),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, InTime)
			{
				CS_CTOR_SET_MEMBER_PROXY(Notify);
				CS_CTOR_SET_MEMBER_PROXY(Time);
			}

			void CopyAsValue(const FNotify& From)
			{
				SetNotify(From.GetNotify());
				SetTime(From.GetTime());
			}

			FORCEINLINE bool Trigger() { return bTriggered = true; }

			// NOTE: With how this is used, assume ElapsedTime is always <= Anim's Length
			FORCEINLINE bool CanTrigger(const float& ElapsedTime, const float& AnimLength) const
			{
				return !bTriggered && ((ElapsedTime / AnimLength) >= (GetTime() / AnimLength));
			}

			FORCEINLINE void ResetTrigger() { bTriggered = false; }

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Notify, FECsVertexAnimNotify)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
		};
	}
}