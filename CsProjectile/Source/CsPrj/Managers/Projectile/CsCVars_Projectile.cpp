// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsCVars_Projectile.h"

TAutoConsoleVariable<int32> CsCVarLogProjectileCollision(
	TEXT("log.projectile.collision"),
	0,
	TEXT("Log Projectile Collision."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectileImpactNormal(
	TEXT("draw.projectile.impactnormal"),
	0,
	TEXT("Draw the Impact Normal for a Projectile hitting a surface."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalLength(
	TEXT("draw.projectile.impactnormallength"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_LENGTH,
	TEXT("Length of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalThickness(
	TEXT("draw.projectile.impactnormalthickness"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS,
	TEXT("Thickness of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalDuration(
	TEXT("draw.projectile.impactnormalduration"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS,
	TEXT("Duration of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectileCollision(
	TEXT("draw.projectile.collision"),
	0,
	TEXT("Draw the Collision for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectilePath(
	TEXT("draw.projectile.path"),
	0,
	TEXT("Draw the Path for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectilePathInterval(
	TEXT("draw.projectile.pathinterval"),
	CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL,
	TEXT("The interval at which segments are drawn for the Path of a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectilePathSegmentsPerInterval(
	TEXT("draw.projectile.pathsegmentsperinterval"),
	CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL,
	TEXT("Number of segments used to draw the Path for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectilePathThickness(
	TEXT("draw.projectile.paththickness"),
	CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS,
	TEXT("Thickness of the Path to be drawn for a Projectile."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogProjectileCollision, "Log Projectile Collision");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogProjectileCollision, CsCVarLogProjectileCollision);
	}
}

#pragma endregion CVarLog

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectileImpactNormal, "Draw Projectile Impact Normal");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectileImpactNormalLength, "Draw Projectile Impact Normal Length");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectileImpactNormalThickness, "Draw Projectile Impact Normal Thickness");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectileImpactNormalDuration, "Draw Projectile Impact Normal Duration");

	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectileCollision, "Draw Projectile Collision");

	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectilePath, "Draw Projectile Path");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectilePathInterval, "Draw Projectile Path Interval");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectilePathSegmentsPerInterval, "Draw Projectile Path Segments Per Interval");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarDraw, DrawProjectilePathThickness, "Draw Projectile Path Thickness");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectileImpactNormal, CsCVarDrawProjectileImpactNormal);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectileImpactNormalLength, CsCVarDrawProjectileImpactNormalLength);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectileImpactNormalThickness, CsCVarDrawProjectileImpactNormalThickness);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectileImpactNormalDuration, CsCVarDrawProjectileImpactNormalDuration);

		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectileCollision, CsCVarDrawProjectileCollision);

		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectilePath, CsCVarDrawProjectilePath);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectilePathInterval, CsCVarDrawProjectilePathInterval);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectilePathSegmentsPerInterval, CsCVarDrawProjectilePathSegmentsPerInterval);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarDrawMap, DrawProjectilePathThickness, CsCVarDrawProjectilePathThickness);
	}
}

#pragma endregion CVarDraw