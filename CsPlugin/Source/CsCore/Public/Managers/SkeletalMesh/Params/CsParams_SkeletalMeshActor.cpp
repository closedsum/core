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
					Mesh(nullptr),
					Mesh_Emu(nullptr),
					Materials(),
					Materials_Emu(nullptr),
					Anim(nullptr),
					Anim_Emu(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FOneShot::Name);

					typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));

					Mesh_Emu = &Mesh;
					Materials_Emu = &Materials;
					Anim_Emu = &Anim;
				}

				FOneShot::~FOneShot()
				{
					delete InterfaceMap;
				}
			}
		}
	}
}

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

#define ParamsType NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot
void FCsSkeletalMeshAnimSequenceOneShot::CopyParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetMesh(&(Mesh.Mesh_Internal));
	Params->SetMaterials(Materials.GetPtr());
	Params->SetAnim(&(Anim.Anim_Internal));
}

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot