/// <reference path="../../../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

module.exports = class NJsSkin
{
    static NData = class Data
    {
        static NVisual = class Visual
        {
            static NSkeletalMesh = class _SkeletalMesh
            {
                static ISkeletalMesh = class InterfaceSkeletalMesh
                {
                    // SkeletalMesh GetSkeletalMesh()

                    static IsImplementedByChecked(context, o)
                    {
                        let self = NJsSkin.NData.NVisual.NSkeletalMesh.ISkeletalMesh;

                        check(CommonLibrary.IsValidObjectChecked(context, o));
                        
                        // GetSkeletalMesh()
                        check(self.Implements_GetSkeletalMeshChecked(context, o));
                        return true;
                    }

                    static IsImplementedBy(o)
                    {
                        let self = NJsSkin.NData.NVisual.NSkeletalMesh.ISkeletalMesh;

                        if (!CommonLibrary.IsValidObject(o))
                            return false;
                        // GetSkeletalMesh()
                        if (!self.Implements_GetSkeletalMesh(o))
                            return false;
                        return true;
                    }

                    // GetSkeletalMesh()
                    static Implements_GetSkeletalMeshChecked(context, o)
                    {
                        let classType = SkeletalMesh;
                        return FunctionLibrary.IsArgCountAndReturn_Instance_Checked(context, o.GetSkeletalMesh, 0, o, classType);
                    }

                    static Implements_GetSkeletalMesh(o)
                    {
                        let classType = SkeletalMesh;
                        return FunctionLibrary.IsArgCountAndReturn_Instance(o.GetSkeletalMesh, 0, o, classType);
                    }
                }
            }
        }
    }
};