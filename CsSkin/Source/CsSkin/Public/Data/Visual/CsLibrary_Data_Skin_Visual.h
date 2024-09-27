// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/Visual/CsData_Skin_Visual.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
// Log
#include "Utility/CsSkinLog.h"

class AActor;
class USceneComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UStaticMesh;
class USkeletalMesh;

// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMesh, IStaticMesh)
// CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NSkeletalMesh, ISkeletalMesh)

// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NMaterial, IMaterial)
// CsMaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsSkin, NData, NVisual, NMaterial, NWithParameters, IWithParameters)

class ICsDeconstructInterfaceSliceMap;

class UMaterialInstanceDynamic;

struct FCsStaticMeshActorPooled;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
		#define CsStaticMeshSkinDataType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
		#define CsSkeletalMeshSkinDataType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh

			struct CSSKIN_API FLibrary : NCsInterfaceMap::TLibrary<CsSkinDataType>
			{
			#define LogLevel void(*Log)(const FString&) = &NCsSkin::FLog::Warning

			public:

				/**
				*/
				static FString PrintObjectAndClass(const CsSkinDataType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const CsSkinDataType* Skin);

				/**
				*/
				static FString PrintSkinAndClass(const CsSkinDataType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const CsStaticMeshSkinDataType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const CsSkeletalMeshSkinDataType* Skin);

				/**
				* 
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return
				*/
				static bool IsValidChecked(const FString& Context, const CsSkinDataType* Skin);

				/**
				*
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Log		(optional)
				* return
				*/
				static bool IsValid(const FString& Context, const CsSkinDataType* Skin, LogLevel);

				/**
				*
				*
				* @param Context	The calling context.
				* @param Name
				* @param Log		(optional)
				* return
				*/
				static ICsDeconstructInterfaceSliceMap* GetSafeDeconstructInterfaceSliceMap(const FString& Context, CsSkinDataType* Skin, LogLevel);

			// Static Mesh
			#pragma region
			public:

				/**
				* Check whether Skin implements the interface: 
				* CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return			Whether the Skin implements the interface:
				*					CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				*/
				static bool ImplementsStaticMeshSkinType(const FString& Context, const CsSkinDataType* Skin);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshAndMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component);

				/**
				* Safely set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				* @param Log		(optional)
				*/
				static void SetSafeStaticMeshAndMaterials(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, LogLevel);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				* @param MIDs		(out) Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetStaticMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				/**
				* Safely set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				* @param MIDs		(out) Material Instance Dynamics to create from Material in the given Skin.
				* @param Log		(optional)
				* return
				*/
				static bool SetSafeStaticMeshAndMIDs(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, LogLevel);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param StaticMeshSkin		Implements the interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* @param Component			StaticMeshComponent
				*/
				static void SetStaticMeshChecked(const FString& Context, const CsStaticMeshSkinDataType* StaticMeshSkin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param StaticMeshSkin		Implements the interface: CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* @param Component			StaticMeshComponent
				*/
				static bool SetSafeStaticMesh(const FString& Context, const CsStaticMeshSkinDataType* StaticMeshSkin, UStaticMeshComponent* Component, LogLevel);

				/**
				* Safely set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: StaticMesh is NOT NULL for appropriate interface slice.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				* @param Log		(optional)
				* return
				*/
				static bool SetSafeStaticMesh(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, LogLevel);

				// Attachment
			#pragma region
			public:

				/**
				* Get the number of Static Mesh attachments for the given Skin.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Skin
				* return				Number of attachments
				*/
				static int32 GetNumAttachmentsChecked(const FString& Context, const UObject* WorldContext, const CsSkinDataType* Skin);

			#pragma endregion Attachment

			#pragma endregion Static Mesh

			// Skeletal Mesh
			#pragma region
			public:

				/**
				* Check whether Skin implements the interface:
				* CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return			Whether the Skin implements the interface:
				*					CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*/
				static bool ImplementsSkeletalMeshSkinType(const FString& Context, const CsSkinDataType* Skin);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshAndMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component);

				/**
				* Safely set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				* @param Log		(optional)
				* return
				*/
				static bool SetSafeSkeletalMeshAndMaterials(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, LogLevel);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetSkeletalMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				/**
				* Safely set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*  Check: Materials count > 0 and Materials are NOT NULL for appropriate interface slice. 
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				* @param Log		(optional)
				* return
				*/
				static bool SetSafeSkeletalMeshAndMIDs(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, LogLevel);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param SkeletalMeshSkin	Implements the interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				* @param Component			SkeletalMeshComponent
				*/
				static void SetSkeletalMeshChecked(const FString& Context, const CsSkeletalMeshSkinDataType* SkeletalMeshSkin, USkeletalMeshComponent* Component);

				/**
				* Safely set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param SkeletalMeshSkin	Implements the interface: CsSkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				* @param Component			SkeletalMeshComponent
				* @param Log				(optional)
				* return
				*/
				static bool SetSafeSkeletalMesh(const FString& Context, const CsSkeletalMeshSkinDataType* SkeletalMeshSkin, USkeletalMeshComponent* Component, LogLevel);

				/**
				* Safely set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin with checks.
				*  Check: Skin is NOT NULL
				*  Check: Component is NOT NULL for appropriate interface slice.
				*  Check: SkeletalMesh is NOT NULL for appropriate interface slice.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				* @param Log		(optional)
				* return
				*/
				static bool SetSafeSkeletalMesh(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, LogLevel);

			#pragma endregion Skeletal Mesh

			// Mesh
			#pragma region
			public:

				/**
				* Set the Mesh (Static or Skeletal) and Materials on a MeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SceneComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param MIDs		(out) Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				struct FSetMeshAndMIDs
				{
					enum class EResult
					{
						None,
						StaticMeshComponent,
						SkeletalMeshComponent
					};
				};

				#define ResultType NCsSkin::NData::NVisual::FLibrary::FSetMeshAndMIDs::EResult

				/**
				* Set the Mesh (Static or Skeletal) and Materials on a StaticMeshComponent or SkeletalMeshComponent
				* (depending on which interface SkinType implements) from the given Skin.
				*
				* @param Context				The calling context.
				* @param Skin					Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param StaticMeshComponent	
				* @param SkeletalMeshComponent
				* @param OutMIDs				(out) Material Instance Dynamics to create from Material in the given Skin.
				* return						0 = None, 1 = StaticMeshComponent, 2 = SkeletalMeshComponent
				*								TODO: NOTE: Use a enum or wrap in a struct.
				*/
				static ResultType SetMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				#undef ResultType

			#pragma endregion Mesh

			// Material
			#pragma region
			public:

			#define CsMaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial
			#define CsMaterialWithParamsSkinDataType NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters

				struct FSetMaterials
				{
					enum class ESkin : uint8
					{
						Material,
						MaterialWithParameters,
						ESkin_MAX
					};

					struct FResult
					{
					public:

						bool bSuccess;

						ESkin Type;

						CsMaterialSkinDataType* MaterialSkinData;

						CsMaterialWithParamsSkinDataType* MaterialWithParamsSkinData;

						FResult() :
							bSuccess(false),
							Type(ESkin::ESkin_MAX),
							MaterialSkinData(nullptr),
							MaterialWithParamsSkinData(nullptr)
						{
						}
					};
				};

			#define ResultType NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult

				/**
				* Set the Materials on MIDs that correspond to a Mesh Component (Static or Skeletal Component)
				* from the given Skin.
				* NOTE: Skin MUST implement the on the interfaces:
				*		- CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*		- CsMaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	PrimitiveComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				* return			Result describing which material skin interface was applied.			
				*/
				static ResultType SetMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				/**
				* Safely set the Materials on MIDs that correspond to a Mesh Component (Static or Skeletal Component)
				* from the given Skin.
				* NOTE: Skin MUST implement the on the interfaces:
				*		- CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*		- CsMaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	PrimitiveComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				* return			Result describing which material skin interface was applied.
				*/
				static ResultType SetSafeMaterials(const FString& Context, const CsSkinDataType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, LogLevel);

			#undef ResultType

			#undef CsMaterialSkinDataType
			#undef CsMaterialWithParamsSkinDataType

			#pragma endregion Material

			// Scale
			#pragma region
			public:

				/**
				* Set the World scale of Component from the given Skin.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				*/
				static void SetUniformScaleChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component);

				/**
				* Set the relative scale of Component from the given Skin.
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				*/
				static void SetUniformScaleRelativeChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component);

				/**
				* Safely set the relative scale of Component from the given Skin.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeUniformScaleRelative(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, LogLevel);

				/**
				* Safely set the relative scale of Component from the given Skin.
				* NOTE: Try default scale skin types
				*		- CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
				*		- CsUniformRangeScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeScaleRelative(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, LogLevel);

				/**
				* Set the scale of Actor from the given Skin.
				* NOTE: Try default scale skin types
				*		- CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
				*		- CsUniformRangeScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Actor		Actor to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static void SetScaleChecked(const FString& Context, const CsSkinDataType* Skin, AActor* Actor);

				/**
				* Safely set the scale of Actor from the given Skin.
				* NOTE: Try default scale skin types
				*		- CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
				*		- CsUniformRangeScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Actor		Actor to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeScale(const FString& Context, const CsSkinDataType* Skin, AActor* Actor, LogLevel);

			#pragma endregion Scale

			#undef LogLevel
			};

		#undef CsStaticMeshSkinDataType
		#undef CsSkeletalMeshSkinDataType
		}
	}
}

using CsSkinDataLibrary = NCsSkin::NData::NVisual::FLibrary;