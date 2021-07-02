// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Material/CsTypes_Material.h"
#include "Animation/CsTypes_Anim.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsParams_SkeletalMeshActor.generated.h"
#pragma once

struct FCsInterfaceMap;
class UAnimSequence;
class UAnimMontage;
class UClass;

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

				private:

					CS_DECLARE_MEMBER_WITH_EMU(Anim, UAnimSequence*)

				public:

					FOneShot();
					~FOneShot();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Anim, UAnimSequence)

					void Reset()
					{
						Anim = nullptr;
						Anim_Emu = &Anim;
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};
			}

			namespace NMontage
			{
				struct CSCORE_API FOneShot : public IParams
				{
				public:

					static const FName Name;

				private:

					FCsInterfaceMap* InterfaceMap;

				private:

					CS_DECLARE_MEMBER_WITH_EMU(Class, UClass*)
					CS_DECLARE_MEMBER_WITH_EMU(Anim, UAnimMontage*)
					CS_DECLARE_MEMBER_WITH_EMU(PlayRate, float)

				public:

					FOneShot();
					~FOneShot();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Class, UClass)
					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Anim, UAnimMontage)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(PlayRate, float)

					void Reset()
					{
						CS_RESET_MEMBER_WITH_EMU(Class, nullptr)
						CS_RESET_MEMBER_WITH_EMU(Anim, nullptr)
						CS_RESET_MEMBER_WITH_EMU(PlayRate, 1.0f)
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};
			}
		}
	}
}

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

class USkeletalMesh;
class UMaterialInterface;
class UAnimSequence;

namespace NCsSkeletalMeshActor
{
	namespace NAnim
	{
		namespace NSequence
		{
			struct CSCORE_API FOneShot
			{
			public:

			#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod
			#define ParamsType NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot

			private:

				CS_DECLARE_MEMBER_WITH_EMU(Mesh, USkeletalMesh*)
				CS_DECLARE_MEMBER_WITH_EMU(Materials, TArray<UMaterialInterface*>)
				CS_DECLARE_MEMBER_WITH_EMU(Type, FECsSkeletalMeshActor)
				CS_DECLARE_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType)
				CS_DECLARE_MEMBER_WITH_EMU(LifeTime, float)
				CS_DECLARE_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules)
				CS_DECLARE_MEMBER_WITH_EMU(Bone, FName)
				CS_DECLARE_MEMBER_WITH_EMU(TransformRules, int32)
				CS_DECLARE_MEMBER_WITH_EMU(Transform, FTransform)

			public:

				ParamsType Params;

			public:

				FOneShot() :
					CS_CTOR_INIT_MEMBER_WITH_EMU(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_ARRAY_WITH_EMU(Materials),
					CS_CTOR_INIT_MEMBER_ENUM_STRUCT_WITH_EMU(Type),
					CS_CTOR_INIT_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType::LifeTime),
					CS_CTOR_INIT_MEMBER_WITH_EMU(LifeTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
					CS_CTOR_INIT_MEMBER_WITH_EMU(Bone, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_EMU(TransformRules, 0),
					CS_CTOR_INIT_MEMBER_WITH_EMU(Transform, FTransform::Identity),
					Params()
				{
					CS_CTOR_SET_MEMBER_EMU(Mesh);
					CS_CTOR_SET_MEMBER_EMU(Materials);
					CS_CTOR_SET_MEMBER_EMU(Type);
					CS_CTOR_SET_MEMBER_EMU(DeallocateMethod);
					CS_CTOR_SET_MEMBER_EMU(LifeTime);
					CS_CTOR_SET_MEMBER_EMU(AttachmentTransformRules);
					CS_CTOR_SET_MEMBER_EMU(Bone);
					CS_CTOR_SET_MEMBER_EMU(TransformRules);
					CS_CTOR_SET_MEMBER_EMU(Transform);
				}

				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Mesh, USkeletalMesh)

				FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
				{
					Materials.Reset(Value.Num());

					for (UMaterialInterface* Material : Value)
					{
						Materials.Add(Material);
					}
					Materials_Emu = &Materials;
				}
				FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Emu = Value; }
				FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Type, FECsSkeletalMeshActor)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(LifeTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Bone, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TransformRules, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Transform, FTransform)

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				void Reset()
				{
					CS_RESET_MEMBER_WITH_EMU(Mesh, nullptr)
					CS_RESET_MEMBER_ARRAY_WITH_EMU(Materials)
					CS_RESET_MEMBER_WITH_EMU(Type, EMCsSkeletalMeshActor::Get().GetMAX())
					CS_RESET_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType::LifeTime)
					CS_RESET_MEMBER_WITH_EMU(LifeTime, 0.0f)
					CS_RESET_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					CS_RESET_MEMBER_WITH_EMU(Bone, NAME_None)
					CS_RESET_MEMBER_WITH_EMU(TransformRules, 0)
					CS_RESET_MEMBER_WITH_EMU(Transform, FTransform::Identity)
					Params.Reset();
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			#undef DeallocateMethodType
			#undef ParamsType
			};
		}
	}
}

// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOnShot)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMeshAnimSequenceOneShot
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSkeletalMeshActorPooledInfo Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsAnimSequence Anim;

	FCsSkeletalMeshAnimSequenceOneShot() :
		Mesh(),
		Anim()
	{
	}

	FORCEINLINE void UpdateInternalPtrs()
	{
		Mesh.UpdateInternalPtrs();
	}

#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
	void CopyToShot(ShotType* Shot);
	void CopyToShotAsValue(ShotType* Shot) const;
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot

// FCsSkeletalMeshAnimMontageOneShot
#pragma region

class USkeletalMesh;
class UMaterialInterface;
class UAnimMontage;

namespace NCsSkeletalMeshActor
{
	namespace NAnim
	{
		namespace NMontage
		{
			struct CSCORE_API FOneShot
			{
			public:

			#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod
			#define ParamsType NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot

			private:

				CS_DECLARE_MEMBER_WITH_EMU(Mesh, USkeletalMesh*)
				CS_DECLARE_MEMBER_WITH_EMU(Materials, TArray<UMaterialInterface*>)
				CS_DECLARE_MEMBER_WITH_EMU(Type, FECsSkeletalMeshActor)
				CS_DECLARE_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType)
				CS_DECLARE_MEMBER_WITH_EMU(LifeTime, float)
				CS_DECLARE_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules)
				CS_DECLARE_MEMBER_WITH_EMU(Bone, FName)
				CS_DECLARE_MEMBER_WITH_EMU(TransformRules, int32)
				CS_DECLARE_MEMBER_WITH_EMU(Transform, FTransform)

			public:

				ParamsType Params;

			public:

				FOneShot() :
					CS_CTOR_INIT_MEMBER_WITH_EMU(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_ARRAY_WITH_EMU(Materials),
					CS_CTOR_INIT_MEMBER_ENUM_STRUCT_WITH_EMU(Type),
					CS_CTOR_INIT_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType::LifeTime),
					CS_CTOR_INIT_MEMBER_WITH_EMU(LifeTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
					CS_CTOR_INIT_MEMBER_WITH_EMU(Bone, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_EMU(TransformRules, 0),
					CS_CTOR_INIT_MEMBER_WITH_EMU(Transform, FTransform::Identity),
					Params()
				{
					CS_CTOR_SET_MEMBER_EMU(Mesh);
					CS_CTOR_SET_MEMBER_EMU(Materials);
					CS_CTOR_SET_MEMBER_EMU(Type);
					CS_CTOR_SET_MEMBER_EMU(DeallocateMethod);
					CS_CTOR_SET_MEMBER_EMU(LifeTime);
					CS_CTOR_SET_MEMBER_EMU(AttachmentTransformRules);
					CS_CTOR_SET_MEMBER_EMU(Bone);
					CS_CTOR_SET_MEMBER_EMU(TransformRules);
					CS_CTOR_SET_MEMBER_EMU(Transform);
				}

				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Mesh, USkeletalMesh)

				FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
				{
					Materials.Reset(Value.Num());

					for (UMaterialInterface* Material : Value)
					{
						Materials.Add(Material);
					}
					Materials_Emu = &Materials;
				}
				FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Emu = Value; }
				FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Type, FECsSkeletalMeshActor)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(LifeTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Bone, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TransformRules, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Transform, FTransform)

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				void Reset()
				{
					CS_RESET_MEMBER_WITH_EMU(Mesh, nullptr)
					CS_RESET_MEMBER_ARRAY_WITH_EMU(Materials)
					CS_RESET_MEMBER_WITH_EMU(Type, EMCsSkeletalMeshActor::Get().GetMAX())
					CS_RESET_MEMBER_WITH_EMU(DeallocateMethod, DeallocateMethodType::LifeTime)
					CS_RESET_MEMBER_WITH_EMU(LifeTime, 0.0f)
					CS_RESET_MEMBER_WITH_EMU(AttachmentTransformRules, ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					CS_RESET_MEMBER_WITH_EMU(Bone, NAME_None)
					CS_RESET_MEMBER_WITH_EMU(TransformRules, 0)
					CS_RESET_MEMBER_WITH_EMU(Transform, FTransform::Identity)
					Params.Reset();
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			#undef DeallocateMethodType
			#undef ParamsType
			};
		}
	}
}

// NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NMontage, FOnShot)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMeshAnimMontageOneShot
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsSkeletalMeshActorPooledInfo Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsAnimBlueprint AnimBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsAnimMontage Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (UIMin = "0.01", ClampMin = "0.01"))
	float PlayRate;

	FCsSkeletalMeshAnimMontageOneShot() :
		Mesh(),
		AnimBlueprint(),
		Anim(),
		PlayRate(1.0f)
	{
	}

	FORCEINLINE void UpdateInternalPtrs()
	{
		Mesh.UpdateInternalPtrs();
	}

	FORCEINLINE float* GetPlayRatePtr() { return &PlayRate; }

#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
	void CopyToShot(ShotType* Shot);
	void CopyToShotAsValue(ShotType* Shot) const;
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsSkeletalMeshAnimMontageOneShot