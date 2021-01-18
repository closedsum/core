// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Types/CsTypes_Material.h"
#include "Animation/CsTypes_Anim.h"

#include "CsParams_SkeletalMeshActor.generated.h"
#pragma once

struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;
class UAnimSequence;

namespace NCsSkeletalMeshActor
{
	namespace NParams
	{
		struct CSCORE_API IParams : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IParams() {}
		};

		namespace NAnim
		{
			namespace NSequence
			{
				struct CSCORE_API FOneShot : public IParams
				{
				public:

					static const FName Name;

				private:

					FCsInterfaceMap* InterfaceMap;

				public:

					USkeletalMesh* Mesh;
					USkeletalMesh** Mesh_Emu;

					TArray<UMaterialInterface*> Materials;
					TArray<UMaterialInterface*>* Materials_Emu;

					UAnimSequence* Anim;
					UAnimSequence** Anim_Emu;

					FOneShot();
					~FOneShot();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetMesh(USkeletalMesh** Value) { Mesh_Emu = Value; }
					FORCEINLINE USkeletalMesh* GetMesh() const { return *Mesh_Emu; }

					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Emu = Value; }
					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

					FORCEINLINE void SetAnim(UAnimSequence** Value) { Anim_Emu = Value; }
					FORCEINLINE UAnimSequence* GetAnim() const { return *Anim_Emu; }
				};
			}
		}
	}
}

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMeshAnimSequenceOneShot
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsSkeletalMesh Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsTArrayMaterialnterface Materials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsAnimSequence Anim;

	FCsSkeletalMeshAnimSequenceOneShot() :
		Mesh(),
		Materials(),
		Anim()
	{
	}

#define ParamsType NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot
	void CopyParams(ParamsType* Params);
#undef ParamsType

private:

	FORCEINLINE void __Nothing() const {}
};

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot