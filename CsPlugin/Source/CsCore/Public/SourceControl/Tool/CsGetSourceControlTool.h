// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetSourceControlTool.generated.h"

class UObject;

namespace NCsSourceControl
{
	namespace NTool
	{
		struct CSCORE_API FImpl
		{
		public:

			/**
			* Use currently set source control provider to check out a file.
			* @note	Blocks until action is complete.
			*
			* @param	InFile		The file to check out - can be either fully qualified path, relative path, long package name, asset path or export text path (often stored on clipboard)
			* @param	bSilent		if false (default) then write out any error info to the Log. Any error text can be retrieved by LastErrorMsg() regardless.
			* @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
			*/
			bool(*CheckOutFileImpl)(const FString& /*InFile*/, bool /*bSilent=false*/);

			FImpl() :
				CheckOutFileImpl(nullptr)
			{
			}
		};
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetSourceControlTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetSourceControlTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define SourceControlToolType NCsSourceControl::NTool::FImpl

	virtual SourceControlToolType* GetSourceControlTool() = 0;

#undef SourceControlToolType
};