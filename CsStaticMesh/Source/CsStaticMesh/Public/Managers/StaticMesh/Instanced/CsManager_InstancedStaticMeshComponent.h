// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Types
#include "CsMacro_Cached.h"
// Instanced Static Mesh
#include "Components/InstancedStaticMeshComponent.h"
#include "Managers/StaticMesh/Instanced/CsInstancedStaticMeshComponentPooled.h"

#include "CsManager_InstancedStaticMeshComponent.generated.h"

class ICsGetManagerInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;
class USceneComponent;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsManager_InstancedStaticMeshComponent)

UCLASS()
class CSSTATICMESH_API ACsManager_InstancedStaticMeshComponent : public AActor
{
	GENERATED_UCLASS_BODY()

private:	

	using ManagerType = NCsStaticMesh::NInstanced::NComponent::FManager;
	using ResourceType = NCsStaticMesh::NInstanced::NComponent::FResource;

	CS_USING_CACHED_FUNCTION_NAME(CsManager_InstancedStaticMeshComponent);

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// Singleton
#pragma region
public:

	static ACsManager_InstancedStaticMeshComponent* Get(const UObject* InRoot);

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static ACsManager_InstancedStaticMeshComponent* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

	static bool IsValid(const UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<ACsManager_InstancedStaticMeshComponent> ManagerInstancedStaticMeshComponentClass);
	
	static void Shutdown(UObject* InRoot = nullptr);

	static bool HasShutdown(const UObject* InRoot = nullptr);

protected:

	static ICsGetManagerInstancedStaticMeshComponent* Get_GetManagerInstancedStaticMeshComponent(const UObject* InRoot);
	static ICsGetManagerInstancedStaticMeshComponent* GetSafe_GetManagerInstancedStaticMeshComponent(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE const UObject* GetMyRoot() const { return MyRoot; }
	FORCEINLINE UObject* GetMyRoot() { return MyRoot; }

#pragma endregion Root

#pragma endregion Singleton

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

// Pool
#pragma region
private:

	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> Components;

	ManagerType Internal;

public:

	FORCEINLINE const ResourceType* Allocate() { return Internal.Allocate(); }

	FORCEINLINE void Deallocate(const int32& ID) { Internal.DeallocateAt(ID); }

#pragma endregion Pool
};