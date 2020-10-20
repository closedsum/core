// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

class UStaticMeshComponent;
class USkeletalMeshComponent;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			struct CSCORE_API FLibrary : TCsLibrary_InterfaceMap<IVisual>
			{
			// Static Mesh
			#pragma region

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshAndMaterials(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component);

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
				static void SetSafeStaticMeshAndMaterials(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMesh(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component);

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
				static void SetSafeStaticMesh(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component);

			#pragma endregion Static Mesh

			// Skeletal Mesh
			#pragma region

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshAndMaterials(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component);

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
				static void SetSafeSkeletalMeshAndMaterials(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: NCsSkin::NData::NVisual::IVisual.
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMesh(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component);

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
				static void SetSafeSkeletalMesh(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component);

			#pragma endregion Skeletal Mesh
			};
		}
	}
}