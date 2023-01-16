// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Animation/CsLibrary_Skeleton.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Animation
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"

namespace NCsSkeletalMeshActor
{
	namespace NParams
	{
		const FName IParams::Name = FName("NCsSkeletalMeshActor::NParams::IParams");

		namespace NAnim
		{
			namespace NSequence
			{
				const FName FOneShot::Name = FName("NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot");

				FOneShot::FOneShot() :
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FOneShot>(this);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Anim);
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}

				bool FOneShot::IsValidChecked(const FString& Context) const
				{
					// Check Anim is Valid
					CS_IS_PTR_NULL_CHECKED(GetAnim())
					return true;
				}

				bool FOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					// Check Anim is Valid
					CS_IS_PTR_NULL(GetAnim())
					return true;
				}
			}

			namespace NMontage
			{
				const FName FOneShot::Name = FName("NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot");

				FOneShot::FOneShot() :
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Class, nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FOneShot>(this);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Class);
					CS_CTOR_SET_MEMBER_PROXY(Anim);
					CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}

				bool FOneShot::IsValidChecked(const FString& Context) const
				{
					// Check Class is Valid
					CS_IS_PTR_NULL_CHECKED(GetClass())
					// Check Anim is Valid
					CS_IS_PTR_NULL_CHECKED(GetAnim())
					// Check Skeleton are compatible between Class and Anim
					typedef NCsSkeleton::FLibrary SkeletonLibrary;

					check(SkeletonLibrary::IsValidChecked(Context, GetClass(), GetAnim()));
					// Check PlayRate is Valid
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
					return true;
				}

				bool FOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					// Check Class is Valid
					CS_IS_PTR_NULL(GetClass())
					// Check Anim is Valid
					CS_IS_PTR_NULL(GetAnim())
					// Check Skeleton are compatible between Class and Anim
					typedef NCsSkeleton::FLibrary SkeletonLibrary;

					if (!SkeletonLibrary::IsValid(Context, GetClass(), GetAnim(), Log))
						return false;

					// Check PlayRate is Valid
					CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
					return true;
				}
			}
		}
	}
}

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

namespace NCsSkeletalMeshActor
{
	namespace NAnim
	{
		namespace NSequence
		{
			bool FOneShot::IsValidChecked(const FString& Context) const
			{
				// Check Mesh is Valid
				CS_IS_PTR_NULL_CHECKED(GetMesh())
				// Check Materials is Valid
				typedef NCsMaterial::FLibrary MaterialLibrary;

				check(MaterialLibrary::IsValidChecked(Context, GetMesh(), GetMaterials()));
				// Check Type is Valid
				check(EMCsSkeletalMeshActor::Get().IsValidEnumChecked(Context, GetType()));
				// Check DeallocateMethod is Valid
				typedef NCsSkeletalMeshActor::EDeallocateMethod DeallocateMethodType;

				checkf(GetDeallocateMethod() != DeallocateMethodType::EDeallocateMethod_MAX, TEXT("%s: DeallocateMethod: DeallocateMethodType::EDeallocateMethod_MAX is NOT Valid."));

				// Check LifeTime is Valid
				if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					checkf(GetLifeTime() > 0.0f, TEXT("%s: LifeTime: %f is NOT > 0.0f if DeallocateMethod == DeallocateMethodType::LifeTime."), *Context, GetLifeTime());
				}
				// Check Params is Valid
				check(Params.IsValidChecked(Context));
				// Check Skeleton are compatible between Mesh and Params.Anim
				typedef NCsSkeleton::FLibrary SkeletonLibrary;

				check(SkeletonLibrary::IsValidChecked(Context, GetMesh(), Params.GetAnim()));
				return true;
			}

			bool FOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check Mesh is Valid
				CS_IS_PTR_NULL(GetMesh())
				// Check Materials is Valid
				typedef NCsMaterial::FLibrary MaterialLibrary;

				if (!MaterialLibrary::IsValid(Context, GetMesh(), GetMaterials(), Log))
				{
					return false;
				}
				// Check Type is Valid
				if (!EMCsSkeletalMeshActor::Get().IsValidEnum(GetType()))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetType(): %s is NOT Valid."), *Context, GetType().ToChar()));
					return false;
				}
				// Check DeallocateMethod is Valid
				typedef NCsSkeletalMeshActor::EDeallocateMethod DeallocateMethodType;

				if (GetDeallocateMethod() == DeallocateMethodType::EDeallocateMethod_MAX)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeallocateMethod: DeallocateMethodType::EDeallocateMethod_MAX is NOT Valid.")));
					return false;
				}
				// Check LifeTime is Valid
				if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					if (GetLifeTime() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: LifeTime: %f is NOT > 0.0f if DeallocateMethod == DeallocateMethodType::LifeTime."), *Context, GetLifeTime()));
						return false;
					}
				}
				// Check Params is Valid
				if (!Params.IsValid(Context, Log))
					return false;
				// Check Skeleton are compatible between Mesh and Params.Anim
				typedef NCsSkeleton::FLibrary SkeletonLibrary;

				if (!SkeletonLibrary::IsValid(Context, GetMesh(), Params.GetAnim(), Log))
					return false;
				return true;
			}
		}
	}
}

#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

void FCsSkeletalMeshAnimSequenceOneShot::CopyToShot(ShotType* Shot)
{
	Shot->SetMesh(Mesh.Mesh.GetPtr());
	Shot->SetMaterials(Mesh.Materials.GetPtr());
	Shot->SetType(Mesh.GetTypePtr());
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethodPtr());
	Shot->SetLifeTime(Mesh.GetLifeTimePtr());
	Shot->SetAttachmentTransformRules(Mesh.AttachmentTransformRules.ToRule());
	Shot->SetBone(Mesh.GetBonePtr());
	Shot->SetTransformRules(Mesh.GetTransformRulesPtr());
	Shot->SetTransform(Mesh.GetTransformPtr());
	Shot->Params.SetAnim(Anim.GetPtr());
}

void FCsSkeletalMeshAnimSequenceOneShot::CopyToShotAsValue(ShotType* Shot) const
{
	Shot->SetMesh(Mesh.Mesh.Get());
	Shot->SetMaterials(Mesh.Materials.Get());
	Shot->SetType(Mesh.Type);
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethod());
	Shot->SetLifeTime(Mesh.LifeTime);
	Shot->SetAttachmentTransformRules(Mesh.AttachmentTransformRules.ToRule());
	Shot->SetBone(Mesh.Bone);
	Shot->SetTransformRules(Mesh.TransformRules);
	Shot->SetTransform(Mesh.Transform);
	Shot->Params.SetAnim(Anim.Get());
}

#undef ShotType

bool FCsSkeletalMeshAnimSequenceOneShot::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Anim is Valid
	check(Anim.IsValidChecked(Context));
	// Check Skeleton are compatible between Mesh.Mesh and Anim.Anim
	typedef NCsSkeleton::FLibrary SkeletonLibrary;

	check(SkeletonLibrary::IsValidChecked(Context, Mesh.Mesh.Get(), Anim.Get()));
	return true;
}

bool FCsSkeletalMeshAnimSequenceOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Anim is Valid
	if (!Anim.IsValid(Context, Log))
		return false;
	// Check Skeleton are compatible between Mesh.Mesh and Anim.Anim
	typedef NCsSkeleton::FLibrary SkeletonLibrary;

	if (!SkeletonLibrary::IsValid(Context, Mesh.Mesh.Get(), Anim.Get(), Log))
		return false;
	return true;
}

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot

// FCsSkeletalMeshAnimMontageOneShot
#pragma region

namespace NCsSkeletalMeshActor
{
	namespace NAnim
	{
		namespace NMontage
		{
			bool FOneShot::IsValidChecked(const FString& Context) const
			{
				// Check Mesh is Valid
				CS_IS_PTR_NULL_CHECKED(GetMesh())
				// Check Materials is Valid
				typedef NCsMaterial::FLibrary MaterialLibrary;

				check(MaterialLibrary::IsValidChecked(Context, GetMesh(), GetMaterials()));
				// Check Type is Valid
				check(EMCsSkeletalMeshActor::Get().IsValidEnumChecked(Context, GetType()));
				// Check DeallocateMethod is Valid
				typedef NCsSkeletalMeshActor::EDeallocateMethod DeallocateMethodType;

				checkf(GetDeallocateMethod() != DeallocateMethodType::EDeallocateMethod_MAX, TEXT("%s: DeallocateMethod: DeallocateMethodType::EDeallocateMethod_MAX is NOT Valid."));

				// Check LifeTime is Valid
				if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					checkf(GetLifeTime() > 0.0f, TEXT("%s: LifeTime: %f is NOT > 0.0f if DeallocateMethod == DeallocateMethodType::LifeTime."), *Context, GetLifeTime());
				}
				// Check Params is Valid
				check(Params.IsValidChecked(Context));
				// Check Skeleton are compatible between Mesh and Params.Class
				typedef NCsSkeleton::FLibrary SkeletonLibrary;

				check(SkeletonLibrary::IsValidChecked(Context, GetMesh(), Params.GetClass()));
				return true;
			}

			bool FOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check Mesh is Valid
				CS_IS_PTR_NULL(GetMesh())
				// Check Materials is Valid
				typedef NCsMaterial::FLibrary MaterialLibrary;

				if (!MaterialLibrary::IsValid(Context, GetMesh(), GetMaterials(), Log))
				{
					return false;
				}
				// Check Type is Valid
				if (!EMCsSkeletalMeshActor::Get().IsValidEnum(GetType()))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetType(): %s is NOT Valid."), *Context, GetType().ToChar()));
					return false;
				}
				// Check DeallocateMethod is Valid
				typedef NCsSkeletalMeshActor::EDeallocateMethod DeallocateMethodType;

				if (GetDeallocateMethod() == DeallocateMethodType::EDeallocateMethod_MAX)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeallocateMethod: DeallocateMethodType::EDeallocateMethod_MAX is NOT Valid."), *Context));
					return false;
				}
				// Check LifeTime is Valid
				if (GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					if (GetLifeTime() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: LifeTime: %f is NOT > 0.0f if DeallocateMethod == DeallocateMethodType::LifeTime."), *Context, GetLifeTime()));
						return false;
					}
				}
				// Check Params is Valid
				if (!Params.IsValid(Context, Log))
					return false;
				// Check Skeleton are compatible between Mesh and Params.Class
				typedef NCsSkeleton::FLibrary SkeletonLibrary;

				if (!SkeletonLibrary::IsValid(Context, GetMesh(), Params.GetClass(), Log))
					return false;
				return true;
			}
		}
	}
}

#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

void FCsSkeletalMeshAnimMontageOneShot::CopyToShot(ShotType* Shot)
{
	Shot->SetMesh(Mesh.Mesh.GetPtr());
	Shot->SetMaterials(Mesh.Materials.GetPtr());
	Shot->SetType(Mesh.GetTypePtr());
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethodPtr());
	Shot->SetLifeTime(Mesh.GetLifeTimePtr());
	Shot->SetAttachmentTransformRules(Mesh.AttachmentTransformRules.ToRule());
	Shot->SetBone(Mesh.GetBonePtr());
	Shot->SetTransformRules(Mesh.GetTransformRulesPtr());
	Shot->SetTransform(Mesh.GetTransformPtr());
	Shot->Params.SetAnim(Anim.GetPtr());
	Shot->Params.SetClass((UClass**)AnimBlueprint.GetPtr());
	Shot->Params.SetPlayRate(GetPlayRatePtr());
}

void FCsSkeletalMeshAnimMontageOneShot::CopyToShotAsValue(ShotType* Shot) const
{
	Shot->SetMesh(Mesh.Mesh.Get());
	Shot->SetMaterials(Mesh.Materials.Get());
	Shot->SetType(Mesh.Type);
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethod());
	Shot->SetLifeTime(Mesh.LifeTime);
	Shot->SetAttachmentTransformRules(Mesh.AttachmentTransformRules.ToRule());
	Shot->SetBone(Mesh.Bone);
	Shot->SetTransformRules(Mesh.TransformRules);
	Shot->SetTransform(Mesh.Transform);
	Shot->Params.SetAnim(Anim.Get());
	Shot->Params.SetClass((UClass*)AnimBlueprint.Get());
	Shot->Params.SetPlayRate(PlayRate);
}

#undef ShotType

bool FCsSkeletalMeshAnimMontageOneShot::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check AnimBlueprint is Valid
	check(AnimBlueprint.IsValidChecked(Context));
	// Check Anim is Valid
	check(Anim.IsValidChecked(Context));

	typedef NCsSkeleton::FLibrary SkeletonLibrary;
	// Check Skeleton are compatible between Mesh.Mesh and AnimBlueprint.Blueprint
	check(SkeletonLibrary::IsValid(Context, Mesh.Mesh.Get(), AnimBlueprint.Get()));
	// Check Skeleton are compatible between Mesh.Mesh and Anim.Anim
	check(SkeletonLibrary::IsValid(Context, Mesh.Mesh.Get(), Anim.Get()));
	// Check PlayRate is Valid
	checkf(PlayRate > 0.0f, TEXT("%s: PlayRate: %f is NOT > 0.0f"), *Context, PlayRate);
	return true;
}

bool FCsSkeletalMeshAnimMontageOneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check AnimBlueprint is Valid
	if (!AnimBlueprint.IsValid(Context, Log))
		return false;
	// Check Anim is Valid
	if (!Anim.IsValid(Context, Log))
		return false;

	typedef NCsSkeleton::FLibrary SkeletonLibrary;
	// Check Skeleton are compatible between Mesh.Mesh and AnimBlueprint.Blueprint
	if (!SkeletonLibrary::IsValid(Context, Mesh.Mesh.Get(), AnimBlueprint.Get(), Log))
		return false;
	// Check Skeleton are compatible between Mesh.Mesh and Anim.Anim
	if (!SkeletonLibrary::IsValid(Context, Mesh.Mesh.Get(), Anim.Get(), Log))
		return false;
	// Check PlayRate is Valid
	if (PlayRate <= 0.0f)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayRate: %f is NOT > 0.0f"), *Context, PlayRate));
		return false;
	}
	return true;
}

#pragma endregion FCsSkeletalMeshAnimMontageOneShot