// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"
#pragma once

class UStaticMeshComponent;
class USkeletalMeshComponent;

// NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMesh, IStaticMesh)
// NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NSkeletalMesh, ISkeletalMesh)

class ICsDeconstructInterfaceSliceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
		#define SkinType NCsSkin::NData::NVisual::IVisual
		#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
		#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh

			struct CSCORE_API FLibrary : TCsLibrary_InterfaceMap<SkinType>
			{
			public:

				/**
				*/
				static FString PrintObjectAndClass(SkinType* Skin);

				/**
				* 
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* return
				*/
				static bool IsValidChecked(const FString& Context, SkinType* Skin);

				/**
				*
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Log		(optional)
				* return
				*/
				static bool IsValid(const FString& Context, SkinType* Skin, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				*
				*
				* @param Context	The calling context.
				* @param Name
				* @param Log		(optional)
				* return
				*/
				static ICsDeconstructInterfaceSliceMap* GetSafeDeconstructInterfaceSliceMap(const FString& Context, SkinType* Skin, void(*Log)(const FString&) = FCsLog::Warning);

			// Static Mesh
			#pragma region

				/**
				* Check whether Skin implements the interface: 
				* StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* return			Whether the Skin implements the interface:
				*					StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				*/
				static bool ImplementsStaticMeshSkinType(const FString& Context, SkinType* Skin);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component);

				/**
				* Safely set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetSafeStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				* @param MIDs		Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs);

				/**
				* Safely set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				* @param MIDs		Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetSafeStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param StaticMeshSkin		Implements the interface: NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh.
				* @param Component			StaticMeshComponent
				*/
				static void SetStaticMesh(const FString& Context, StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component);

				/**
				* Safely set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetSafeStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component);

			#pragma endregion Static Mesh

			// Skeletal Mesh
			#pragma region

				/**
				* Check whether Skin implements the interface:
				* SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* return			Whether the Skin implements the interface:
				*					SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*/
				static bool ImplementsSkeletalMeshSkinType(const FString& Context, SkinType* Skin);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component);

				/**
				* Safely set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSafeSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				* @param MIDs		Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetSkeletalMeshAndMIDs(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs);

				/**
				* Safely set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				* @param MIDs		Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetSafeSkeletalMeshAndMIDs(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param SkeletalMeshSkin	Implements the interface: NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh.
				* @param Component			SkeletalMeshComponent
				*/
				static void SetSkeletalMesh(const FString& Context, SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component);

				/**
				* Safely set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSafeSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component);

			#pragma endregion Skeletal Mesh

			// Mesh
			#pragma region
			public:

				/**
				* Set the Mesh (Static or Skeletal) and Materials on a MeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SceneComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param MIDs		Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetMeshAndMIDs(const FString& Context, SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs);

			#pragma endregion Mesh
			};

		#undef SkinType
		#undef StaticMeshSkinType
		#undef SkeletalMeshSkinType
		}
	}
}