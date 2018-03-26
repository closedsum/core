#pragma once
#include "Player/CsPlayerPawn.h"
#include "CsFpsPawn.generated.h"

// Enums
#pragma region

namespace ECsFpsPawnRoutine
{
	enum Type
	{
		ECsFpsPawnRoutine_MAX = ECsPlayerPawnRoutine::ECsPlayerPawnRoutine_MAX,
	};
}

namespace ECsFpsPawnRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return Type::ECsFpsPawnRoutine_MAX;
	}
}

#define ECS_FPS_PAWN_ROUTINE_MAX (uint8)ECsFpsPawnRoutine::ECsFpsPawnRoutine_MAX
typedef ECsFpsPawnRoutine::Type TCsFpsPawnRoutine;

#pragma endregion Enums

UCLASS(config=Game)
class CSCORE_API ACsFpsPawn : public ACsPlayerPawn
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn")
	class USceneComponent* Eye;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UCsSkeletalMeshComponent* Mesh1P;

// View
#pragma region
public:

	virtual TEnumAsByte<ECsViewType::Type> GetCurrentViewType() override;

#pragma endregion View

// Camera
#pragma region
public:

	float EyeHeight;

	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// Mesh
#pragma region
public:

	virtual USkeletalMeshComponent* GetCurrentMesh();

#pragma endregion Mesh

// Weapons
#pragma region
public:

	virtual void ApplyData_Weapon() override;

#pragma endregion Weapons
};

