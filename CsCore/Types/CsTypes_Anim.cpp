// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Anim.h"

namespace ECsAnimCached
{
	namespace Str
	{
		const CSCORE_API FString Empty = TEXT("");

		const CSCORE_API FString AnimSequence = TEXT("AnimSequence");
		const CSCORE_API FString Anim_Sequence = TEXT("Anim Sequence");
		const CSCORE_API FString AnimMontage = TEXT("AnimMontage");
		const CSCORE_API FString Anim_Montage = TEXT("Anim Montage");
		const CSCORE_API FString BlendSpace1D = TEXT("BlendSpace1D");
		const CSCORE_API FString Blend_Space_1D = TEXT("Blend Space 1D");
		const CSCORE_API FString BlendSpace = TEXT("BlendSpace");
		const CSCORE_API FString Blend_Space = TEXT("Blend Space");
	}
}

namespace ECsFpsAnimMember
{
	namespace Str
	{
		const CSCORE_API TCsString Anim1P = TCsString(TEXT("Anim1P"), TEXT("anim1p"));
		const CSCORE_API TCsString Anim3P = TCsString(TEXT("Anim3P"), TEXT("anim3p"));
		const CSCORE_API TCsString Anim3P_Low = TCsString(TEXT("Anim3P_Low"), TEXT("anim3p_low"));
		const CSCORE_API TCsString AnimVR = TCsString(TEXT("AnimVR"), TEXT("animvr"));
	}

	namespace Ref
	{
		const CSCORE_API Type Anim1P = Type::Anim1P;
		const CSCORE_API Type Anim3P = Type::Anim3P;
		const CSCORE_API Type Anim3P_Low = Type::Anim3P_Low;
		const CSCORE_API Type AnimVR = Type::AnimVR;
		const CSCORE_API Type ECsFpsAnimMember_MAX = Type::ECsFpsAnimMember_MAX;
	}
}