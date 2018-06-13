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

// FpvAnimMember
EMCsFpvAnimMember* EMCsFpvAnimMember::Instance;

EMCsFpvAnimMember& EMCsFpvAnimMember::Get()
{
	if (!Instance)
		Instance = new EMCsFpvAnimMember();
	return *Instance;
}

namespace ECsFpvAnimMember
{
	namespace Ref
	{
		CSCORE_API const Type Anim1P = EMCsFpvAnimMember::Get().Add(Type::Anim1P, TEXT("Anim1P"), TEXT("Anim 1P"));
		CSCORE_API const Type Anim3P = EMCsFpvAnimMember::Get().Add(Type::Anim3P, TEXT("Anim3P"), TEXT("Anim 3P"));
		CSCORE_API const Type Anim3P_Low = EMCsFpvAnimMember::Get().Add(Type::Anim1P, TEXT("Anim3P_Low"), TEXT("Anim 3P Low"));
		CSCORE_API const Type AnimVR = EMCsFpvAnimMember::Get().Add(Type::AnimVR, TEXT("AnimVR"), TEXT("Anim VR"));
		CSCORE_API const Type ECsFpvAnimMember_MAX = EMCsFpvAnimMember::Get().Add(Type::ECsFpvAnimMember_MAX, TEXT("ECsFpvAnimMember_MAX"), TEXT("MAX"));
	}
}

// FpvAnimBlueprintMember
EMCsFpvAnimBlueprintMember* EMCsFpvAnimBlueprintMember::Instance;

EMCsFpvAnimBlueprintMember& EMCsFpvAnimBlueprintMember::Get()
{
	if (!Instance)
		Instance = new EMCsFpvAnimBlueprintMember();
	return *Instance;
}

namespace ECsFpvAnimBlueprintMember
{
	namespace Ref
	{
		extern CSCORE_API const Type Blueprint1P = EMCsFpvAnimBlueprintMember::Get().Add(Type::Blueprint1P, TEXT("Blueprint1P"), TEXT("Blueprint 1P"));
		extern CSCORE_API const Type Blueprint3P = EMCsFpvAnimBlueprintMember::Get().Add(Type::Blueprint3P, TEXT("Blueprint3P"), TEXT("Blueprint 3P"));
		extern CSCORE_API const Type Blueprint3P_Low = EMCsFpvAnimBlueprintMember::Get().Add(Type::Blueprint3P_Low, TEXT("Blueprint3P_Low"), TEXT("Blueprint 3P Low"));
		extern CSCORE_API const Type BlueprintVR = EMCsFpvAnimBlueprintMember::Get().Add(Type::BlueprintVR, TEXT("BlueprintVR"), TEXT("Blueprint VR"));
		extern CSCORE_API const Type ECsFpvAnimBlueprintMember_MAX = EMCsFpvAnimBlueprintMember::Get().Add(Type::ECsFpvAnimBlueprintMember_MAX, TEXT("ECsFpvAnimBlueprintMember_MAX"), TEXT("MAX"));
	}
}

// FpvAnimBlendSpaceMember
EMCsFpvAnimBlendSpaceMember* EMCsFpvAnimBlendSpaceMember::Instance;

EMCsFpvAnimBlendSpaceMember& EMCsFpvAnimBlendSpaceMember::Get()
{
	if (!Instance)
		Instance = new EMCsFpvAnimBlendSpaceMember();
	return *Instance;
}

namespace ECsFpvAnimBlendSpaceMember
{
	namespace Ref
	{
		CSCORE_API const Type Blend1P = EMCsFpvAnimBlendSpaceMember::Get().Add(Type::Blend1P, TEXT("Blend1P"), TEXT("Blend 1P"));
		CSCORE_API const Type Blend3P = EMCsFpvAnimBlendSpaceMember::Get().Add(Type::Blend3P, TEXT("Blend3P"), TEXT("Blend 3P"));
		CSCORE_API const Type Blend3P_Low = EMCsFpvAnimBlendSpaceMember::Get().Add(Type::Blend3P_Low, TEXT("Blend3P_Low"), TEXT("Blend 3P Low"));
		CSCORE_API const Type BlendVR = EMCsFpvAnimBlendSpaceMember::Get().Add(Type::BlendVR, TEXT("BlendVR"), TEXT("Blend VR"));
		CSCORE_API const Type ECsFpvAnimBlendSpaceMember_MAX = EMCsFpvAnimBlendSpaceMember::Get().Add(Type::ECsFpvAnimBlendSpaceMember_MAX, TEXT("ECsFpvAnimBlendSpaceMember_MAX"), TEXT("MAX"));
	}
}

// AdditiveBasePoseType
EMCsAdditiveBasePoseType* EMCsAdditiveBasePoseType::Instance;

EMCsAdditiveBasePoseType& EMCsAdditiveBasePoseType::Get()
{
	if (!Instance)
		Instance = new EMCsAdditiveBasePoseType();
	return *Instance;
}

namespace ECsAdditiveBasePoseType
{
	namespace Ref
	{
		CSCORE_API const Type ABPT_None = EMCsAdditiveBasePoseType::Get().Add(Type::ABPT_None, TEXT("ABPT_None"), TEXT("None"));
		CSCORE_API const Type ABPT_RefPose = EMCsAdditiveBasePoseType::Get().Add(Type::ABPT_RefPose, TEXT("ABPT_RefPose"), TEXT("Ref Pose"));
		CSCORE_API const Type ABPT_AnimScaled = EMCsAdditiveBasePoseType::Get().Add(Type::ABPT_AnimScaled, TEXT("ABPT_AnimScaled"), TEXT("Anim Scaled"));
		CSCORE_API const Type ABPT_AnimFrame = EMCsAdditiveBasePoseType::Get().Add(Type::ABPT_AnimFrame, TEXT("ABPT_AnimFrame"), TEXT("Anim Frame"));
		CSCORE_API const Type ABPT_MAX = EMCsAdditiveBasePoseType::Get().Add(Type::ABPT_MAX, TEXT("ABPT_MAX"), TEXT("MAX"));
	}
}

// AdditiveAnimationType
EMCsAdditiveAnimationType* EMCsAdditiveAnimationType::Instance;

EMCsAdditiveAnimationType& EMCsAdditiveAnimationType::Get()
{
	if (!Instance)
		Instance = new EMCsAdditiveAnimationType();
	return *Instance;
}

namespace ECsAdditiveAnimationType
{
	namespace Ref
	{
		extern CSCORE_API const Type AAT_None = EMCsAdditiveAnimationType::Get().Add(Type::AAT_None, TEXT("AAT_None"), TEXT("None"));
		extern CSCORE_API const Type AAT_LocalSpaceBase = EMCsAdditiveAnimationType::Get().Add(Type::AAT_LocalSpaceBase, TEXT("AAT_LocalSpaceBase"), TEXT("Local Space Base"));
		extern CSCORE_API const Type AAT_RotationOffsetMeshSpace = EMCsAdditiveAnimationType::Get().Add(Type::AAT_RotationOffsetMeshSpace, TEXT("AAT_RotationOffsetMeshSpace"), TEXT("Rotation Offset Mesh Space"));
		extern CSCORE_API const Type AAT_MAX = EMCsAdditiveAnimationType::Get().Add(Type::AAT_MAX, TEXT("AAT_MAX"), TEXT("None"));
	}
}