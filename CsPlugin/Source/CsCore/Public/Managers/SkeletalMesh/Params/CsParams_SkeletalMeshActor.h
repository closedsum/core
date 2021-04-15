// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Types/CsTypes_Material.h"
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

					UAnimSequence* Anim;
					UAnimSequence** Anim_Emu;

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

					UClass* Class;
					UClass** Class_Emu;

					UAnimMontage* Anim;
					UAnimMontage** Anim_Emu;

					float PlayRate;
					float* PlayRate_Emu;

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
						Class = nullptr;
						Class_Emu = &Class;
						Anim = nullptr;
						Anim_Emu = &Anim;
						PlayRate = 1.0f;
						PlayRate_Emu = &PlayRate;
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

				USkeletalMesh* Mesh;
				USkeletalMesh** Mesh_Emu;

				TArray<UMaterialInterface*> Materials;
				TArray<UMaterialInterface*>* Materials_Emu;

				FECsSkeletalMeshActor Type;
				FECsSkeletalMeshActor* Type_Emu;

				DeallocateMethodType DeallocateMethod;
				DeallocateMethodType* DeallocateMethod_Emu;

				float LifeTime;
				float* LifeTime_Emu;

				ECsAttachmentTransformRules AttachmentTransformRules;
				ECsAttachmentTransformRules* AttachmentTransformRules_Emu;

				FName Bone;
				FName* Bone_Emu;

				int32 TransformRules;
				int32* TransformRules_Emu;

				FTransform Transform;
				FTransform* Transform_Emu;

			public:

				ParamsType Params;

			public:

				FOneShot() :
					Mesh(nullptr),
					Mesh_Emu(nullptr),
					Materials(),
					Materials_Emu(nullptr),
					Type(),
					Type_Emu(nullptr),
					DeallocateMethod(DeallocateMethodType::LifeTime),
					DeallocateMethod_Emu(nullptr),
					LifeTime(0.0f),
					LifeTime_Emu(nullptr),
					AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
					AttachmentTransformRules_Emu(nullptr),
					Bone(NAME_None),
					Bone_Emu(nullptr),
					TransformRules(0),
					TransformRules_Emu(nullptr),
					Transform(FTransform::Identity),
					Transform_Emu(nullptr),
					Params()
				{
					Mesh_Emu = &Mesh;
					Materials_Emu = &Materials;
					Type_Emu = &Type;
					DeallocateMethod_Emu = &DeallocateMethod;
					LifeTime_Emu = &LifeTime;
					AttachmentTransformRules_Emu = &AttachmentTransformRules;
					Bone_Emu = &Bone;
					TransformRules_Emu = &TransformRules;
					Transform_Emu = &Transform;
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
					Mesh = nullptr;
					Mesh_Emu = &Mesh;
					Materials.Reset(Materials.Max());
					Materials_Emu = &Materials;
					Type = EMCsSkeletalMeshActor::Get().GetMAX();
					Type_Emu = &Type;
					DeallocateMethod = DeallocateMethodType::LifeTime;
					DeallocateMethod_Emu = &DeallocateMethod;
					LifeTime = 0.0;
					LifeTime_Emu = &LifeTime;
					AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
					AttachmentTransformRules_Emu = &AttachmentTransformRules;
					Bone = NAME_None;
					Bone_Emu = &Bone;
					TransformRules = 0;
					TransformRules_Emu = &TransformRules;
					Transform = FTransform::Identity;
					Transform_Emu = &Transform;
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

				USkeletalMesh* Mesh;
				USkeletalMesh** Mesh_Emu;

				TArray<UMaterialInterface*> Materials;
				TArray<UMaterialInterface*>* Materials_Emu;

				FECsSkeletalMeshActor Type;
				FECsSkeletalMeshActor* Type_Emu;

				DeallocateMethodType DeallocateMethod;
				DeallocateMethodType* DeallocateMethod_Emu;

				float LifeTime;
				float* LifeTime_Emu;

				ECsAttachmentTransformRules AttachmentTransformRules;
				ECsAttachmentTransformRules* AttachmentTransformRules_Emu;

				FName Bone;
				FName* Bone_Emu;

				int32 TransformRules;
				int32* TransformRules_Emu;

				FTransform Transform;
				FTransform* Transform_Emu;

			public:

				ParamsType Params;

			public:

				FOneShot() :
					Mesh(nullptr),
					Mesh_Emu(nullptr),
					Materials(),
					Materials_Emu(nullptr),
					Type(),
					Type_Emu(nullptr),
					DeallocateMethod(DeallocateMethodType::LifeTime),
					DeallocateMethod_Emu(nullptr),
					LifeTime(0.0f),
					LifeTime_Emu(nullptr),
					AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
					AttachmentTransformRules_Emu(nullptr),
					Bone(NAME_None),
					Bone_Emu(nullptr),
					TransformRules(0),
					TransformRules_Emu(nullptr),
					Transform(FTransform::Identity),
					Transform_Emu(nullptr),
					Params()
				{
					Mesh_Emu = &Mesh;
					Materials_Emu = &Materials;
					Type_Emu = &Type;
					DeallocateMethod_Emu = &DeallocateMethod;
					LifeTime_Emu = &LifeTime;
					AttachmentTransformRules_Emu = &AttachmentTransformRules;
					Bone_Emu = &Bone;
					TransformRules_Emu = &TransformRules;
					Transform_Emu = &Transform;
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
					Mesh = nullptr;
					Mesh_Emu = &Mesh;
					Materials.Reset(Materials.Max());
					Materials_Emu = &Materials;
					Type = EMCsSkeletalMeshActor::Get().GetMAX();
					Type_Emu = &Type;
					DeallocateMethod = DeallocateMethodType::LifeTime;
					DeallocateMethod_Emu = &DeallocateMethod;
					LifeTime = 0.0;
					LifeTime_Emu = &LifeTime;
					AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
					AttachmentTransformRules_Emu = &AttachmentTransformRules;
					Bone = NAME_None;
					Bone_Emu = &Bone;
					TransformRules = 0;
					TransformRules_Emu = &TransformRules;
					Transform = FTransform::Identity;
					Transform_Emu = &Transform;
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