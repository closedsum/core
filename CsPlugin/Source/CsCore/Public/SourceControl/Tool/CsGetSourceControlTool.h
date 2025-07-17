// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSCORE_API ITool
		{
		public:

			virtual ~ITool() {}

		public:

			/**
			* Use currently set source control provider to check out a file.
			* @note	Blocks until action is complete.
			*
			* @param	InFile		The file to check out - can be either fully qualified path, 
			*						relative path, long package name, asset path or export text path (often stored on clipboard)
			* @param	bSilent		(optional)	if false (default) then write out any error info to the Log. 
			*						Any error text can be retrieved by LastErrorMsg() regardless.
			* @return	true if succeeded, false if failed and can call LastErrorMsg() for more info.
			*/
			virtual bool CheckOutFile(const FString& InFile, bool bSilent=false) = 0;
		};
	}
}

using CsSourceControlToolType = NCsSourceControl::NTool::ITool;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetSourceControlTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetSourceControlTool
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual CsSourceControlToolType* GetSourceControlTool() = 0;
};