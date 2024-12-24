// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsTypes_Anim.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Anim)

namespace NCsAnimCached
{
	namespace Str
	{
		CSTYPES_API const FString Empty = TEXT("");

		CSTYPES_API const FString AnimSequence = TEXT("AnimSequence");
		CSTYPES_API const FString Anim_Sequence = TEXT("Anim Sequence");
		CSTYPES_API const FString AnimMontage = TEXT("AnimMontage");
		CSTYPES_API const FString Anim_Montage = TEXT("Anim Montage");
		CSTYPES_API const FString BlendSpace1D = TEXT("BlendSpace1D");
		CSTYPES_API const FString Blend_Space_1D = TEXT("Blend Space 1D");
		CSTYPES_API const FString BlendSpace = TEXT("BlendSpace");
		CSTYPES_API const FString Blend_Space = TEXT("Blend Space");
		CSTYPES_API const FString AimOffsetBlendSpace = TEXT("AimOffsetBlendSpace");
		CSTYPES_API const FString Aim_Offset_Blend_Space = TEXT("Aim Offset Blend Space");
	}
}

// FpvAnimMember
#pragma region

namespace NCsFpvAnimMember
{
	namespace Ref
	{
		typedef EMCsFpvAnimMember EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim1P, "Anim 1P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim3P, "Anim 3P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim3P_Low, "Anim 3P Low");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AnimVR, "Anim VR");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimMember_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsFpvAnimMember_MAX;
}

#pragma endregion EMCsFpvAnimMember

// FCsAnimSequenceInfo
#pragma region

namespace NCsAnimSequenceInfo
{
	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_PTR_TO_PROXY(Info, Anim);
		CS_THIS_COPY_TO_PROXY(Info, PlayRate);
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Anim);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, PlayRate);
	}
}

bool FCsAnimSequenceInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimSequenceInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_VALID(Anim)
	CS_IS_FLOAT_GREATER_THAN(PlayRate, 0.0f)
	return true;
}

bool FCsAnimSequenceInfo::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimSequenceInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_TOP_VALID(Anim)
	CS_IS_FLOAT_GREATER_THAN(PlayRate, 0.0f)
	return true;
}

namespace NCsAnim
{
	namespace NSequence
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetAnim())
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetAnim())
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsTopValidChecked(const FString& Context) const
		{
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsAnimSequenceInfo

// FCsAnimMontageInfo
#pragma region

namespace NCsAnimMontageInfo
{
	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_PTR_TO_PROXY(Info, Anim);
		CS_THIS_COPY_TO_PROXY(Info, PlayRate);
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Anim);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, PlayRate);
	}
}

bool FCsAnimMontageInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimMontageInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_VALID(Anim)
	CS_IS_FLOAT_GREATER_THAN(PlayRate, 0.0f)
	return true;
}

bool FCsAnimMontageInfo::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimMontageInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_TOP_VALID(Anim)
	CS_IS_FLOAT_GREATER_THAN(PlayRate, 0.0f)
	return true;
}

namespace NCsAnim
{
	namespace NMontage
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetAnim())
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetAnim())
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsTopValidChecked(const FString& Context) const
		{
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
			return true;
		}

		bool FInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			return true;
		}
	}
}


#pragma endregion FCsAnimMontageInfo

// FpvAnimBlueprintMember
#pragma region

namespace NCsFpvAnimBlueprintMember
{
	namespace Ref
	{
		typedef EMCsFpvAnimBlueprintMember EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint1P, "Blueprint 1P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint3P, "Blueprint 3P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint3P_Low, "Blueprint 3P Low");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(BlueprintVR, "Blueprint VR");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimBlueprintMember_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsFpvAnimBlueprintMember_MAX;
}

#pragma endregion FpvAnimBlueprintMember

// FpvAnimBlendSpaceMember
#pragma region

namespace NCsFpvAnimBlendSpaceMember
{
	namespace Ref
	{
		typedef EMCsFpvAnimBlendSpaceMember EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend1P, "Blend 1P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend3P, "Blend 3P");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend3P_Low, "Blend 3P Low");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(BlendVR, "Blend VR");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimBlendSpaceMember_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsFpvAnimBlendSpaceMember_MAX;
}

#pragma endregion FpvAnimBlendSpaceMember

// AdditiveBasePoseType
#pragma region

namespace NCsAdditiveBasePoseType
{
	namespace Ref
	{
		typedef EMCsAdditiveBasePoseType EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_None, "None");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_RefPose, "Ref Pose");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_AnimScaled, "Anim Scaled");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_AnimFrame, "Anim Frame");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ABPT_MAX;
}

#pragma endregion AdditiveBasePoseType

// AdditiveAnimationType
#pragma region

namespace NCsAdditiveAnimationType
{
	namespace Ref
	{
		typedef EMCsAdditiveAnimationType EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_None, "None");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_LocalSpaceBase, "Local Space Base");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_RotationOffsetMeshSpace, "Rotation Offset Mesh Space");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::AAT_MAX;
}

#pragma endregion AdditiveAnimationType