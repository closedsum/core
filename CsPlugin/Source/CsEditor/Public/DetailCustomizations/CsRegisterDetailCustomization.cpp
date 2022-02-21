// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
#include "CsEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// CVar
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarLogCustomization.h"
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarToggleCustomization.h"
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarDrawCustomization.h"
		// Asset
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
		// Update
#include "DetailCustomizations/EnumStruct/Update/ECsUpdateGroupCustomization.h"
		// Input
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionMapCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCoordinatorGroupCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsGestureTypeCustomization.h"
		// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"
		// FX
#include "DetailCustomizations/EnumStruct/FX/ECsFXCustomization.h"
		// Sound
#include "DetailCustomizations/EnumStruct/Sound/ECsSoundCustomization.h"
		// StaticMesh
#include "DetailCustomizations/EnumStruct/StaticMesh/ECsStaticMeshActorCustomization.h"
		// SkeletalMesh
#include "DetailCustomizations/EnumStruct/SkeletalMesh/ECsSkeletalMeshActorCustomization.h"
		// Sense
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"
		// Surface
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"
		// Team
#include "DetailCustomizations/EnumStruct/Team/ECsTeamCustomization.h"
	// Data
#include "DetailCustomizations/Data/CsData_ECsTestCustomization.h"
	// Asset
#include "DetailCustomizations/Asset/CsMaterialInterfaceCustomization.h"

void FCsRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		// CVar
		CS_TEMP_REGISTER(ECsCVarLog);
		CS_TEMP_REGISTER(ECsCVarToggle);
		CS_TEMP_REGISTER(ECsCVarDraw);
		// Asset
		CS_TEMP_REGISTER(ECsAssetType);
		CS_TEMP_REGISTER(ECsLoadAssetsType);
		// Update
		CS_TEMP_REGISTER(ECsUpdateGroup);
		// Input
		{
			CS_TEMP_REGISTER(ECsInputAction);
			CS_TEMP_REGISTER(ECsInputActionMap);
			CS_TEMP_REGISTER(ECsGameEvent);
			CS_TEMP_REGISTER(ECsGameEventCoordinatorGroup);
			// GestureType
			CS_TEMP_REGISTER(ECsGestureType);
		}
		// SurfaceType
		CS_TEMP_REGISTER(ECsSurfaceType);
		// Process
		CS_TEMP_REGISTER(ECsProcess);
		// FX
		CS_TEMP_REGISTER(ECsFX);
		// Sound
		CS_TEMP_REGISTER(ECsSound);
		// StaticMesh
		{
			CS_TEMP_REGISTER(ECsStaticMeshActor);
		}
		// SkeletalMesh
		{
			CS_TEMP_REGISTER(ECsSkeletalMeshActor);
		}
		// Sense
		CS_TEMP_REGISTER(ECsSenseActorType);
		// Team
		CS_TEMP_REGISTER(ECsTeam);
	}
	// Data
	{
		PropertyModule.RegisterCustomPropertyTypeLayout("CsData_ECsTest", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(FCsData_ECsTestCustomization::MakeInstance)));
	}
	// Asset
	{
		// CsMaterialInterface
		CS_TEMP_REGISTER(CsMaterialInterface);
	}

	#undef CS_TEMP_REGISTER
}