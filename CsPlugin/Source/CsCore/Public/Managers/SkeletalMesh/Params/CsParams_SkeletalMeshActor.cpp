// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

// Containers
#include "Containers/CsInterfaceMap.h"

namespace NCsSkeletalMeshActor
{
	namespace NParams
	{
		const FName IParams::Name = FName("NCsSkeletalMeshActor::NParams::IParams");

		namespace NAnim
		{
			namespace NSequence
			{
				const FName FOneShot::Name = FName("NCsSkeletalMeshActor::NParams::FOneShot");

				FOneShot::FOneShot() :
					InterfaceMap(nullptr),
					Materials(),
					Materials_Emu(nullptr),
					Anim(nullptr),
					Anim_Emu(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FOneShot::Name);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					Materials_Emu = &Materials;
					Anim_Emu = &Anim;
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}

				bool FOneShot::IsValidChecked(const FString& Context) const
				{
					return true;
				}
			}
		}
	}

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

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
void FCsSkeletalMeshAnimSequenceOneShot::CopyShot(ShotType* Shot)
{
#undef ShotType

	Shot->SetMesh(&(Mesh.Mesh_Internal));
	Shot->SetType(&(Mesh.Type));
	Shot->SetDeallocateMethod(Mesh.GetDeallocateMethodPtr());
	Shot->SetLifeTime(&(Mesh.LifeTime));
	Shot->SetAttachmentTransformRules(&(Mesh.AttachmentTransformRules));
	Shot->SetBone(&(Mesh.Bone));
	Shot->SetTransformRules(&(Mesh.TransformRules));
	Shot->SetTransform(&(Mesh.Transform));
	Shot->Params.SetMaterials(&(Materials.Materials_Internal));
	Shot->Params.SetAnim(&(Anim.Anim_Internal));
}

bool FCsSkeletalMeshAnimSequenceOneShot::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot