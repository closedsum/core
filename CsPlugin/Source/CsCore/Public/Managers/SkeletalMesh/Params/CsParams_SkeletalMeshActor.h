// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Material/CsTypes_Material.h"
#include "Animation/CsTypes_Anim.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsParams_SkeletalMeshActor.generated.h"

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

					CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimSequence*)

				public:

					FOneShot();
					~FOneShot();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimSequence)

					void Reset()
					{
						CS_RESET_MEMBER_WITH_PROXY(Anim, nullptr)
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

					CS_DECLARE_MEMBER_WITH_PROXY(Class, UClass*)
					CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimMontage*)
					CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)

				public:

					FOneShot();
					~FOneShot();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Class, UClass)
					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimMontage)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)

					void Reset()
					{
						CS_RESET_MEMBER_WITH_PROXY(Class, nullptr)
						CS_RESET_MEMBER_WITH_PROXY(Anim, nullptr)
						CS_RESET_MEMBER_WITH_PROXY(PlayRate, 1.0f)
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

				CS_DECLARE_MEMBER_WITH_PROXY(Mesh, USkeletalMesh*)
				CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsSkeletalMeshActor)
				CS_DECLARE_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
				CS_DECLARE_MEMBER_WITH_PROXY(LifeTime, float)
				CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
				CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)
				CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
				CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform)

			public:

				ParamsType Params;

			public:

				FOneShot() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Materials),
					CS_CTOR_INIT_MEMBER_ENUM_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType::LifeTime),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform::Identity),
					Params()
				{
					CS_CTOR_SET_MEMBER_PROXY(Mesh);
					CS_CTOR_SET_MEMBER_PROXY(Materials);
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(DeallocateMethod);
					CS_CTOR_SET_MEMBER_PROXY(LifeTime);
					CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
					CS_CTOR_SET_MEMBER_PROXY(Bone);
					CS_CTOR_SET_MEMBER_PROXY(TransformRules);
					CS_CTOR_SET_MEMBER_PROXY(Transform);
				}

				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, USkeletalMesh)

				FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
				{
					Materials.Reset(Value.Num());

					for (UMaterialInterface* Material : Value)
					{
						Materials.Add(Material);
					}
					Materials_Proxy = &Materials;
				}
				FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Proxy = Value; }
				FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsSkeletalMeshActor)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform)

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Mesh, nullptr)
					CS_RESET_MEMBER_ARRAY_WITH_PROXY(Materials)
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsSkeletalMeshActor::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType::LifeTime)
					CS_RESET_MEMBER_WITH_PROXY(LifeTime, 0.0f)
					CS_RESET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale)
					CS_RESET_MEMBER_WITH_PROXY(Bone, NAME_None)
					CS_RESET_MEMBER_WITH_PROXY(TransformRules, 0)
					CS_RESET_MEMBER_WITH_PROXY(Transform, FTransform::Identity)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Params")
	FCsSkeletalMeshActorPooledInfo Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Params")
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

				CS_DECLARE_MEMBER_WITH_PROXY(Mesh, USkeletalMesh*)
				CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)
				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsSkeletalMeshActor)
				CS_DECLARE_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
				CS_DECLARE_MEMBER_WITH_PROXY(LifeTime, float)
				CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
				CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)
				CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
				CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform)

			public:

				ParamsType Params;

			public:

				FOneShot() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Materials),
					CS_CTOR_INIT_MEMBER_ENUM_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType::LifeTime),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Transform, FTransform::Identity),
					Params()
				{
					CS_CTOR_SET_MEMBER_PROXY(Mesh);
					CS_CTOR_SET_MEMBER_PROXY(Materials);
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(DeallocateMethod);
					CS_CTOR_SET_MEMBER_PROXY(LifeTime);
					CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
					CS_CTOR_SET_MEMBER_PROXY(Bone);
					CS_CTOR_SET_MEMBER_PROXY(TransformRules);
					CS_CTOR_SET_MEMBER_PROXY(Transform);
				}

				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, USkeletalMesh)

				FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
				{
					Materials.Reset(Value.Num());

					for (UMaterialInterface* Material : Value)
					{
						Materials.Add(Material);
					}
					Materials_Proxy = &Materials;
				}
				FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Proxy = Value; }
				FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsSkeletalMeshActor)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform)

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Mesh, nullptr)
					CS_RESET_MEMBER_ARRAY_WITH_PROXY(Materials)
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsSkeletalMeshActor::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(DeallocateMethod, DeallocateMethodType::LifeTime)
					CS_RESET_MEMBER_WITH_PROXY(LifeTime, 0.0f)
					CS_RESET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale)
					CS_RESET_MEMBER_WITH_PROXY(Bone, NAME_None)
					CS_RESET_MEMBER_WITH_PROXY(TransformRules, 0)
					CS_RESET_MEMBER_WITH_PROXY(Transform, FTransform::Identity)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh|Params")
	FCsSkeletalMeshActorPooledInfo Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh|Params")
	FCsAnimBlueprint AnimBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh|Params")
	FCsAnimMontage Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Skeletal Mesh|Params", meta = (UIMin = "0.01", ClampMin = "0.01"))
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