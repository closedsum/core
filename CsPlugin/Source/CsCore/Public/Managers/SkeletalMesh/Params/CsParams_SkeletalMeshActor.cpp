// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Animation
#include "Animation/AnimBlueprintGeneratedClass.h"

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
					Anim(nullptr),
					Anim_Emu(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FOneShot::Name);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					Anim_Emu = &Anim;
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}

				bool FOneShot::IsValidChecked(const FString& Context) const
				{
					// Check Anim is Valid
					checkf(GetAnim(), TEXT("%s: Anim is NULL."), *Context);
					return true;
				}
			}

			namespace NMontage
			{
				const FName FOneShot::Name = FName("NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot");

				FOneShot::FOneShot() :
					InterfaceMap(nullptr),
					Class(nullptr),
					Class_Emu(nullptr),
					Anim(nullptr),
					Anim_Emu(nullptr),
					PlayRate(1.0f),
					PlayRate_Emu(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FOneShot::Name);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					Class_Emu = &Class;
					Anim_Emu = &Anim;
					PlayRate_Emu = &PlayRate;
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}

				bool FOneShot::IsValidChecked(const FString& Context) const
				{
					// Check Class is Valid
					checkf(GetClass(), TEXT("%s: Class is NULL."), *Context);
					// Check Anim is Valid
					checkf(GetAnim(), TEXT("%s: Anim is NULL."), *Context);
					// Check PlayRate is Valid
					checkf(PlayRate_Emu, TEXT("%s: PlayRate_Emu is NULL."), *Context);
					checkf(GetPlayRate() > 0.0f, TEXT("%s: PlayRate: %d is NOT > 0.0f."), *Context, GetPlayRate());
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
				checkf(GetMesh(), TEXT("%s: Mesh is NULL."), *Context);
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
				return true;
			}
		}
	}
}

#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
void FCsSkeletalMeshAnimSequenceOneShot::CopyShot(ShotType* Shot)
{
#undef ShotType

	Shot->SetMesh(Mesh.Mesh.GetPtr());
	Shot->SetMaterials(Mesh.Materials.GetPtr());
	Shot->SetType(Mesh.GetTypePtr());
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethodPtr());
	Shot->SetLifeTime(Mesh.GetLifeTimePtr());
	Shot->SetAttachmentTransformRules(Mesh.GetAttachmentTransformRulesPtr());
	Shot->SetBone(Mesh.GetBonePtr());
	Shot->SetTransformRules(Mesh.GetTransformRulesPtr());
	Shot->SetTransform(Mesh.GetTransformPtr());
	Shot->Params.SetAnim(Anim.GetPtr());
}

bool FCsSkeletalMeshAnimSequenceOneShot::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
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
				checkf(GetMesh(), TEXT("%s: Mesh is NULL."), *Context);
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
				return true;
			}
		}
	}
}

#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
void FCsSkeletalMeshAnimMontageOneShot::CopyShot(ShotType* Shot)
{
#undef ShotType

	Shot->SetMesh(Mesh.Mesh.GetPtr());
	Shot->SetMaterials(Mesh.Materials.GetPtr());
	Shot->SetType(Mesh.GetTypePtr());
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethodPtr());
	Shot->SetLifeTime(Mesh.GetLifeTimePtr());
	Shot->SetAttachmentTransformRules(Mesh.GetAttachmentTransformRulesPtr());
	Shot->SetBone(Mesh.GetBonePtr());
	Shot->SetTransformRules(Mesh.GetTransformRulesPtr());
	Shot->SetTransform(Mesh.GetTransformPtr());
	Shot->Params.SetAnim(Anim.GetPtr());
	Shot->Params.SetClass((UClass**)AnimBlueprint.GetPtr());
	Shot->Params.SetPlayRate(GetPlayRatePtr());
}

bool FCsSkeletalMeshAnimMontageOneShot::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

#pragma endregion FCsSkeletalMeshAnimMontageOneShot