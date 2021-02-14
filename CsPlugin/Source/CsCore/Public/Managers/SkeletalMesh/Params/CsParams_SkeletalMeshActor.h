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

					FORCEINLINE void SetAnim(UAnimSequence* Value)
					{
						Anim = Value;
						Anim_Emu = &Anim;
					}
					FORCEINLINE void SetAnim(UAnimSequence** Value) { Anim_Emu = Value; }
					FORCEINLINE UAnimSequence* GetAnim() const { return *Anim_Emu; }

					bool IsValidChecked(const FString& Context) const;
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

					FORCEINLINE void SetClass(UClass* Value)
					{
						Class = Value;
						Class_Emu = &Class;
					}
					FORCEINLINE void SetClass(UClass** Value) { Class_Emu = Value; }
					FORCEINLINE UClass* GetClass() const { return *Class_Emu; }

					FORCEINLINE void SetAnim(UAnimMontage* Value)
					{
						Anim = Value;
						Anim_Emu = &Anim;
					}
					FORCEINLINE void SetAnim(UAnimMontage** Value) { Anim_Emu = Value; }
					FORCEINLINE UAnimMontage* GetAnim() const { return *Anim_Emu; }

					FORCEINLINE void SetPlayRate(const float& Value)
					{
						PlayRate = Value;
						PlayRate_Emu = &PlayRate;
					}
					FORCEINLINE void SetPlayRate(float* Value) { PlayRate_Emu = Value; }
					FORCEINLINE const float& GetPlayRate() const { return *PlayRate_Emu; }

					bool IsValidChecked(const FString& Context) const;
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
				ECsAttachmentTransformRules* AttachementTransformRules_Emu;

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
					AttachementTransformRules_Emu(nullptr),
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
					AttachementTransformRules_Emu = &AttachmentTransformRules;
					Bone_Emu = &Bone;
					TransformRules_Emu = &TransformRules;
					Transform_Emu = &Transform;
				}

				FORCEINLINE void SetMesh(USkeletalMesh* Value)
				{
					Mesh = Value;
					Mesh_Emu = &Mesh;
				}
				FORCEINLINE void SetMesh(USkeletalMesh** Value) { Mesh_Emu = Value; }
				FORCEINLINE USkeletalMesh* GetMesh() const { return *Mesh_Emu; }

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

				FORCEINLINE void SetType(const FECsSkeletalMeshActor& Value)
				{
					Type = Value;
					Type_Emu = &Type;
				}
				FORCEINLINE void SetType(FECsSkeletalMeshActor* Value) { Type_Emu = Value; }
				FORCEINLINE const FECsSkeletalMeshActor& GetType() const { return *Type_Emu; }

				FORCEINLINE void SetDeallocateMethod(const DeallocateMethodType& Value)
				{
					DeallocateMethod = Value;
					DeallocateMethod_Emu = &DeallocateMethod;
				}
				FORCEINLINE void SetDeallocateMethod(DeallocateMethodType* Value) { DeallocateMethod_Emu = Value; }
				FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *DeallocateMethod_Emu; }

				FORCEINLINE void SetLifeTime(const float& Value)
				{
					LifeTime = Value;
					LifeTime_Emu = &LifeTime;
				}
				FORCEINLINE void SetLifeTime(float* Value) { LifeTime_Emu = Value; }
				FORCEINLINE const float& GetLifeTime() const { return *LifeTime_Emu; }

				FORCEINLINE void SetAttachmentTransformRules(const ECsAttachmentTransformRules& Value)
				{
					AttachmentTransformRules = Value;
					AttachementTransformRules_Emu = &AttachmentTransformRules;
				}
				FORCEINLINE void SetAttachmentTransformRules(ECsAttachmentTransformRules* Value) { AttachementTransformRules_Emu = Value; }
				FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRules() const { return *AttachementTransformRules_Emu; }

				FORCEINLINE void SetBone(const FName& Value)
				{
					Bone = Value;
					Bone_Emu = &Bone;
				}
				FORCEINLINE void SetBone(FName* Value) { Bone_Emu = Value; }
				FORCEINLINE const FName& GetBone() const { return *Bone_Emu; }

				FORCEINLINE void SetTransformRules(const int32& Value)
				{
					TransformRules = Value;
					TransformRules_Emu = &TransformRules;
				}
				FORCEINLINE void SetTransformRules(int32* Value) { TransformRules_Emu = Value; }
				FORCEINLINE const int32& GetTransformRules() const { return *TransformRules_Emu; }

				FORCEINLINE void SetTransform(const FTransform& Value)
				{
					Transform = Value;
					Transform_Emu = &Transform;
				}
				FORCEINLINE void SetTransform(FTransform* Value) { Transform_Emu = Value; }
				FORCEINLINE const FTransform& GetTransform() const { return *Transform_Emu; }

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				bool IsValidChecked(const FString& Context) const;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsSkeletalMeshActorPooledInfo Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
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
	void CopyShot(ShotType* Shot);
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
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
				ECsAttachmentTransformRules* AttachementTransformRules_Emu;

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
					AttachementTransformRules_Emu(nullptr),
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
					AttachementTransformRules_Emu = &AttachmentTransformRules;
					Bone_Emu = &Bone;
					TransformRules_Emu = &TransformRules;
					Transform_Emu = &Transform;
				}

				FORCEINLINE void SetMesh(USkeletalMesh* Value)
				{
					Mesh = Value;
					Mesh_Emu = &Mesh;
				}
				FORCEINLINE void SetMesh(USkeletalMesh** Value) { Mesh_Emu = Value; }
				FORCEINLINE USkeletalMesh* GetMesh() const { return *Mesh_Emu; }

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

				FORCEINLINE void SetType(const FECsSkeletalMeshActor& Value)
				{
					Type = Value;
					Type_Emu = &Type;
				}
				FORCEINLINE void SetType(FECsSkeletalMeshActor* Value) { Type_Emu = Value; }
				FORCEINLINE const FECsSkeletalMeshActor& GetType() const { return *Type_Emu; }

				FORCEINLINE void SetDeallocateMethod(const DeallocateMethodType& Value)
				{
					DeallocateMethod = Value;
					DeallocateMethod_Emu = &DeallocateMethod;
				}
				FORCEINLINE void SetDeallocateMethod(DeallocateMethodType* Value) { DeallocateMethod_Emu = Value; }
				FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *DeallocateMethod_Emu; }

				FORCEINLINE void SetLifeTime(const float& Value)
				{
					LifeTime = Value;
					LifeTime_Emu = &LifeTime;
				}
				FORCEINLINE void SetLifeTime(float* Value) { LifeTime_Emu = Value; }
				FORCEINLINE const float& GetLifeTime() const { return *LifeTime_Emu; }

				FORCEINLINE void SetAttachmentTransformRules(const ECsAttachmentTransformRules& Value)
				{
					AttachmentTransformRules = Value;
					AttachementTransformRules_Emu = &AttachmentTransformRules;
				}
				FORCEINLINE void SetAttachmentTransformRules(ECsAttachmentTransformRules* Value) { AttachementTransformRules_Emu = Value; }
				FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRules() const { return *AttachementTransformRules_Emu; }

				FORCEINLINE void SetBone(const FName& Value)
				{
					Bone = Value;
					Bone_Emu = &Bone;
				}
				FORCEINLINE void SetBone(FName* Value) { Bone_Emu = Value; }
				FORCEINLINE const FName& GetBone() const { return *Bone_Emu; }

				FORCEINLINE void SetTransformRules(const int32& Value)
				{
					TransformRules = Value;
					TransformRules_Emu = &TransformRules;
				}
				FORCEINLINE void SetTransformRules(int32* Value) { TransformRules_Emu = Value; }
				FORCEINLINE const int32& GetTransformRules() const { return *TransformRules_Emu; }

				FORCEINLINE void SetTransform(const FTransform& Value)
				{
					Transform = Value;
					Transform_Emu = &Transform;
				}
				FORCEINLINE void SetTransform(FTransform* Value) { Transform_Emu = Value; }
				FORCEINLINE const FTransform& GetTransform() const { return *Transform_Emu; }

				FORCEINLINE const ParamsType* GetParamsPtr() const { return &Params; }

				bool IsValidChecked(const FString& Context) const;

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
	void CopyShot(ShotType* Shot);
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSkeletalMeshAnimMontageOneShot