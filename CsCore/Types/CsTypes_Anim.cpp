// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Anim.h"

namespace ECsAnimCached
{
	namespace Str
	{
		CSCORE_API const FString Empty = TEXT("");

		CSCORE_API const FString AnimSequence = TEXT("AnimSequence");
		CSCORE_API const FString Anim_Sequence = TEXT("Anim Sequence");
		CSCORE_API const FString AnimMontage = TEXT("AnimMontage");
		CSCORE_API const FString Anim_Montage = TEXT("Anim Montage");
		CSCORE_API const FString BlendSpace1D = TEXT("BlendSpace1D");
		CSCORE_API const FString Blend_Space_1D = TEXT("Blend Space 1D");
		CSCORE_API const FString BlendSpace = TEXT("BlendSpace");
		CSCORE_API const FString Blend_Space = TEXT("Blend Space");
	}
}

namespace ECsFpsAnimMember
{
	namespace Str
	{
		CSCORE_API const TCsString Anim1P = TCsString(TEXT("Anim1P"), TEXT("anim1p"));
		CSCORE_API const TCsString Anim3P = TCsString(TEXT("Anim3P"), TEXT("anim3p"));
		CSCORE_API const TCsString Anim3P_Low = TCsString(TEXT("Anim3P_Low"), TEXT("anim3p_low"));
		CSCORE_API const TCsString AnimVR = TCsString(TEXT("AnimVR"), TEXT("animvr"));
	}

	namespace Ref
	{
		CSCORE_API const Type Anim1P = Type::Anim1P;
		CSCORE_API const Type Anim3P = Type::Anim3P;
		CSCORE_API const Type Anim3P_Low = Type::Anim3P_Low;
		CSCORE_API const Type AnimVR = Type::AnimVR;
		CSCORE_API const Type ECsFpsAnimMember_MAX = Type::ECsFpsAnimMember_MAX;
	}
}