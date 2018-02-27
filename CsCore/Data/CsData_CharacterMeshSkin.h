#pragma once
#include "Data/CsData.h"
#include "CsData_CharacterMeshSkin.generated.h"

/* Current Order of Categories

01. Skin

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_CharacterMeshSkin : public ACsData
{
	GENERATED_UCLASS_BODY()

	// Skin
#pragma region

	virtual void SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType);
	virtual void SetMesh(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType);

	UFUNCTION(BlueprintCallable, Category = "Character Mesh Skin")
	virtual void SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType);

	virtual void SetMesh(USkeletalMeshComponent* InMesh);
	virtual void SetMesh(class ASkeletalMeshActor* InActor);
	virtual void SetMesh(UObject* InObject);

#pragma endregion Skin
};