// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

class AActor;
class USceneComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

// NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMesh, IStaticMesh)
// NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NSkeletalMesh, ISkeletalMesh)

// NCsSkin::NData::NVisual::NMaterial::IMaterial
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NMaterial, IMaterial)
// NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters
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
		#define SkinType NCsSkin::NData::NVisual::IVisual
		#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
		#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh

			struct CSCORE_API FLibrary : NCsInterfaceMap::TLibrary<SkinType>
			{
			public:

				/**
				*/
				static FString PrintObjectAndClass(const SkinType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const SkinType* Skin);

				/**
				*/
				static FString PrintSkinAndClass(const SkinType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const StaticMeshSkinType* Skin);

				/**
				*/
				static FString PrintNameAndClass(const SkeletalMeshSkinType* Skin);

				/**
				* 
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return
				*/
				static bool IsValidChecked(const FString& Context, const SkinType* Skin);

				/**
				*
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Log		(optional)
				* return
				*/
				static bool IsValid(const FString& Context, const SkinType* Skin, void(*Log)(const FString&) = &FCsLog::Warning);

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
			public:

				/**
				* Check whether Skin implements the interface: 
				* StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return			Whether the Skin implements the interface:
				*					StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				*/
				static bool ImplementsStaticMeshSkinType(const FString& Context, const SkinType* Skin);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshAndMaterialsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component);

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
				static void SetSafeStaticMeshAndMaterials(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Set the Static Mesh and Materials on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				* @param MIDs		(out) Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetStaticMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

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
				static bool SetSafeStaticMeshAndMIDs(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	StaticMeshComponent
				*/
				static void SetStaticMeshChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param StaticMeshSkin		Implements the interface: StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* @param Component			StaticMeshComponent
				*/
				static void SetStaticMeshChecked(const FString& Context, const StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component);

				/**
				* Set the Static Mesh on a StaticMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param StaticMeshSkin		Implements the interface: StaticMeshSkinType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* @param Component			StaticMeshComponent
				*/
				static bool SetSafeStaticMesh(const FString& Context, const StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

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
				static bool SetSafeStaticMesh(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

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
				static int32 GetNumAttachmentsChecked(const FString& Context, const UObject* WorldContext, const SkinType* Skin);

				/**
				* Set Static Mesh attachments on Component from the given Skin.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Skin
				* @param Component		SceneComponent to attach Static Mesh attachments to.
				* @param OutAttachments (out)
				*/
				static void SetAttachmentsChecked(const FString& Context, const UObject* WorldContext, const SkinType* Skin, USceneComponent* Component, TArray<FCsStaticMeshActorPooled*>& OutAttachments);
				
			#pragma endregion Attachment

			#pragma endregion Static Mesh

			// Skeletal Mesh
			#pragma region
			public:

				/**
				* Check whether Skin implements the interface:
				* SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* return			Whether the Skin implements the interface:
				*					SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				*/
				static bool ImplementsSkeletalMeshSkinType(const FString& Context, const SkinType* Skin);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshAndMaterialsChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component);

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
				static bool SetSafeSkeletalMeshAndMaterials(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Set the Skeletal Mesh and Materials on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				*/
				static void SetSkeletalMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

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
				static bool SetSafeSkeletalMeshAndMIDs(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	SkeletalMeshComponent
				*/
				static void SetSkeletalMeshChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component);

				/**
				* Set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param SkeletalMeshSkin	Implements the interface: SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				* @param Component			SkeletalMeshComponent
				*/
				static void SetSkeletalMeshChecked(const FString& Context, const SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component);

				/**
				* Safely set the Skeletal Mesh on a SkeletalMeshComponent (Component)
				* from the given Skin
				*
				* @param Context			The calling context.
				* @param SkeletalMeshSkin	Implements the interface: SkeletalMeshSkinType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				* @param Component			SkeletalMeshComponent
				* @param Log				(optional)
				* return
				*/
				static bool SetSafeSkeletalMesh(const FString& Context, const SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

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
				static bool SetSafeSkeletalMesh(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

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
				static void SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

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
				static ResultType SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				#undef ResultType

			#pragma endregion Mesh

			// Material
			#pragma region
			public:

			#define MaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial
			#define MaterialWithParamsSkinDataType NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters

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

						MaterialSkinDataType* MaterialSkinData;

						MaterialWithParamsSkinDataType* MaterialWithParamsSkinData;

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
				*		- MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*		- MaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	PrimitiveComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				* return			Result describing which material skin interface was applied.			
				*/
				static ResultType SetMaterialsChecked(const FString& Context, const SkinType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs);

				/**
				* Safely set the Materials on MIDs that correspond to a Mesh Component (Static or Skeletal Component)
				* from the given Skin.
				* NOTE: Skin MUST implement the on the interfaces:
				*		- MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*		- MaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	PrimitiveComponent (SHOULD be StaticMeshComponent or SkeletalMeshComponent).
				* @param OutMIDs	(out) Material Instance Dynamics to create from Material in the given Skin.
				* return			Result describing which material skin interface was applied.
				*/
				static ResultType SetSafeMaterials(const FString& Context, const SkinType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) = &FCsLog::Warning);

			#undef ResultType

			#undef MaterialSkinDataType
			#undef MaterialWithParamsSkinDataType

			#pragma endregion Material

			// Scale
			#pragma region
			public:

				/**
				* Set the relative scale of Component from the given Skin.
				* 
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				*/
				static void SetUniformScaleRelativeChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component);

				/**
				* Safely set the relative scale of Component from the given Skin.
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeUniformScaleRelative(const FString& Context, const SkinType* Skin, USceneComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely set the relative scale of Component from the given Skin.
				* NOTE: Try default scale skin types
				*		- UniformScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
				*		- UniformRangeScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Component	Scene Component to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeScaleRelative(const FString& Context, const SkinType* Skin, USceneComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely set the scale of Actor from the given Skin.
				* NOTE: Try default scale skin types
				*		- UniformScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
				*		- UniformRangeScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
				*
				* @param Context	The calling context.
				* @param Skin		Implements the interface: SkinType (NCsSkin::NData::NVisual::IVisual).
				* @param Actor		Actor to scale.
				* @param Log		(optional)
				* return			Whether the scale was set
				*/
				static bool SetSafeScale(const FString& Context, const SkinType* Skin, AActor* Actor, void(*Log)(const FString&) = &FCsLog::Warning);

			#pragma endregion Scale
			};

		#undef SkinType
		#undef StaticMeshSkinType
		#undef SkeletalMeshSkinType
		}
	}
}