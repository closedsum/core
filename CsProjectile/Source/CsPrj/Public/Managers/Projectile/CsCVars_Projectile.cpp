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
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogProjectileCollision, "Log Projectile Collision");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogProjectileCollision, CsCVarLogProjectileCollision);
	}
}

#pragma endregion CVarLog

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectileImpactNormal, "Draw Projectile Impact Normal");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectileImpactNormalLength, "Draw Projectile Impact Normal Length");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectileImpactNormalThickness, "Draw Projectile Impact Normal Thickness");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectileImpactNormalDuration, "Draw Projectile Impact Normal Duration");

	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectileCollision, "Draw Projectile Collision");

	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectilePath, "Draw Projectile Path");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectilePathInterval, "Draw Projectile Path Interval");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectilePathSegmentsPerInterval, "Draw Projectile Path Segments Per Interval");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawProjectilePathThickness, "Draw Projectile Path Thickness");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectileImpactNormal, CsCVarDrawProjectileImpactNormal);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalLength, CsCVarDrawProjectileImpactNormalLength);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalThickness, CsCVarDrawProjectileImpactNormalThickness);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalDuration, CsCVarDrawProjectileImpactNormalDuration);

		CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectileCollision, CsCVarDrawProjectileCollision);

		CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectilePath, CsCVarDrawProjectilePath);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectilePathInterval, CsCVarDrawProjectilePathInterval);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectilePathSegmentsPerInterval, CsCVarDrawProjectilePathSegmentsPerInterval);
		//CSPRJ_API CS_ADD_TO_CVAR_MAP(DrawProjectilePathThickness, CsCVarDrawProjectilePathThickness);
	}
}

#pragma endregion CVarDraw