// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsObjectPathDependencyGroup.generated.h"

// ObjectPathDependencyGroup
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsObjectPathDependencyGroup : uint8
{
	// Enum (UserDefinedEnum)
	Enum								UMETA(DisplayName = "Enum"),
	// Texture | Render Target
	Texture								UMETA(DisplayName = "Texture"),
	// Font | Font Face
	Font								UMETA(DisplayName = "Font"),
	// Material Parameter Collection 
	MaterialParameterCollection			UMETA(DisplayName = "Material Parameter Collection"),
	// Material Function
	MaterialFunction					UMETA(DisplayName = "Material Function"),
	// Material
	Material							UMETA(DisplayName = "Material"),
	// Material Instance
	MaterialInstance					UMETA(DisplayName = "Material Instnace"),
	// Static Mesh
	StaticMesh							UMETA(DisplayName = "Static Mesh"),
	// Skeletal Mesh | Physics Asset | Skeleton
	Skeletal							UMETA(DisplayName = "Skeletal"),
	// TODO: Need a way to capture other sound plugins (i.e. Wise)
	Sound								UMETA(DisplayName = "Sound"),
	// Particle System | TODO: Niagara (need to be careful what Niagara references)
	FX									UMETA(DisplayName = "FX"),
	// Anim Sequence
	AnimationAsset						UMETA(DisplayName = "Animation Asset"),
	// Blend Space
	BlendSpace							UMETA(DisplayName = "Blend Space"),
	// Anim Montage | Anim Composite
	AnimComposite						UMETA(DisplayName = "Anim Composite"),
	// Blueprints: General umbrella: Anim Blueprint, ... etc
	Blueprint							UMETA(DisplayName = "Blueprint"),
	// IMovieScenePlayer (UMovieSceneSequencePlayer) | IMovieScenePlaybackClient | IMovieSceneBindingOwnerInterface | UMovieSceneSignedObject
	Sequencer							UMETA(DisplayName = "Sequencer"),
	DataTable							UMETA(DisplayName = "DataTable"),
	// Catch all for anything not categorized (UserDefinedStruct, ... etc)
	Other								UMETA(DisplayName = "Other"),
	ECsObjectPathDependencyGroup_MAX	UMETA(Hidden),
};


struct CSTYPES_API EMCsObjectPathDependencyGroup : public TCsEnumMap<ECsObjectPathDependencyGroup>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsObjectPathDependencyGroup, ECsObjectPathDependencyGroup)
};

namespace NCsObjectPathDependencyGroup
{
	typedef ECsObjectPathDependencyGroup Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Enum;
		extern CSTYPES_API const Type Texture;
		extern CSTYPES_API const Type Font;
		extern CSTYPES_API const Type MaterialParameterCollection;
		extern CSTYPES_API const Type MaterialFunction;
		extern CSTYPES_API const Type Material;
		extern CSTYPES_API const Type MaterialInstance;
		extern CSTYPES_API const Type StaticMesh;
		extern CSTYPES_API const Type Skeletal;
		extern CSTYPES_API const Type Sound;
		extern CSTYPES_API const Type FX;
		extern CSTYPES_API const Type AnimationAsset;
		extern CSTYPES_API const Type BlendSpace;
		extern CSTYPES_API const Type AnimComposite;
		extern CSTYPES_API const Type Blueprint;
		extern CSTYPES_API const Type Sequencer;
		extern CSTYPES_API const Type DataTable;
		extern CSTYPES_API const Type Other;
		extern CSTYPES_API const Type ECsObjectPathDependencyGroup_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

#pragma endregion ObjectPathDependencyGroup