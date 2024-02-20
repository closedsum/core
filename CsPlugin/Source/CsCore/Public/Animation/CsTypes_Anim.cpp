// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsTypes_Anim.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsAnimCached
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
		CSCORE_API const FString AimOffsetBlendSpace = TEXT("AimOffsetBlendSpace");
		CSCORE_API const FString Aim_Offset_Blend_Space = TEXT("Aim Offset Blend Space");
	}
}

// FpvAnimMember
#pragma region

namespace NCsFpvAnimMember
{
	namespace Ref
	{
		typedef EMCsFpvAnimMember EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim1P, "Anim 1P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim3P, "Anim 3P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Anim3P_Low, "Anim 3P Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AnimVR, "Anim VR");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimMember_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFpvAnimMember_MAX;
}

#pragma endregion EMCsFpvAnimMember

// FCsAnimSequenceInfo
#pragma region

#define InfoType NCsAnim::NSequence::FInfo
void FCsAnimSequenceInfo::CopyToInfo(InfoType* Info)
{
#undef InfoType

	Info->SetAnim(Anim.GetPtr());
	Info->SetPlayRate(&PlayRate);
}

bool FCsAnimSequenceInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimSequenceInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

bool FCsAnimSequenceInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		bool FInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsAnimSequenceInfo

// FCsAnimMontageInfo
#pragma region

#define InfoType NCsAnim::NMontage::FInfo
void FCsAnimMontageInfo::CopyToInfo(InfoType* Info)
{
#undef InfoType

	Info->SetAnim(Anim.GetPtr());
	Info->SetPlayRate(&PlayRate);
}

bool FCsAnimMontageInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Anim);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	return true;
}

bool FCsAnimMontageInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

bool FCsAnimMontageInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		bool FInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint1P, "Blueprint 1P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint3P, "Blueprint 3P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blueprint3P_Low, "Blueprint 3P Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(BlueprintVR, "Blueprint VR");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimBlueprintMember_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFpvAnimBlueprintMember_MAX;
}

#pragma endregion FpvAnimBlueprintMember

// FpvAnimBlendSpaceMember
#pragma region

namespace NCsFpvAnimBlendSpaceMember
{
	namespace Ref
	{
		typedef EMCsFpvAnimBlendSpaceMember EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend1P, "Blend 1P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend3P, "Blend 3P");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Blend3P_Low, "Blend 3P Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(BlendVR, "Blend VR");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFpvAnimBlendSpaceMember_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFpvAnimBlendSpaceMember_MAX;
}

#pragma endregion FpvAnimBlendSpaceMember

// AdditiveBasePoseType
#pragma region

namespace NCsAdditiveBasePoseType
{
	namespace Ref
	{
		typedef EMCsAdditiveBasePoseType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_RefPose, "Ref Pose");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_AnimScaled, "Anim Scaled");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_AnimFrame, "Anim Frame");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ABPT_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ABPT_MAX;
}

#pragma endregion AdditiveBasePoseType

// AdditiveAnimationType
#pragma region

namespace NCsAdditiveAnimationType
{
	namespace Ref
	{
		typedef EMCsAdditiveAnimationType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_LocalSpaceBase, "Local Space Base");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_RotationOffsetMeshSpace, "Rotation Offset Mesh Space");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AAT_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::AAT_MAX;
}

#pragma endregion AdditiveAnimationType