#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_View.h"
#include "CsData_CharacterMeshSkin.generated.h"

/* Current Order of Categories

01. Skin

*/

UCLASS(Abstract)
class CSCOREDEPRECATED_API UCsData_CharacterMeshSkin : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

	// Skin
#pragma region

	virtual void SetMesh(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void SetMesh(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Character Mesh Skin")
	virtual void SetMesh(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow = false);

	virtual void SetMesh(USkeletalMeshComponent* InMesh);
	virtual void SetMesh(class ASkeletalMeshActor* InActor);
	virtual void SetMesh(UObject* InObject);

#pragma endregion Skin
};