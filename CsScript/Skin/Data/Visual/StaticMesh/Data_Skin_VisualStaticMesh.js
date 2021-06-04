/// <reference path="../../../../typings/ue.d.ts">/>
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
            static NStaticMesh = class _StaticMesh
            {
                static IStaticMesh = class InterfaceStaticMesh
                {
                    static IsImplementedByChecked(context, o)
                    {
                        let self = NJsSkin.NData.NVisual.NStaticMesh.IStaticMesh;

                        check(CommonLibrary.IsValidObjectChecked(context, o));
                        
                        // GetStaticMesh()
                        check(self.Implements_GetStaticMeshChecked(context, o));
                        return true;
                    }

                    static IsImplementedBy(o)
                    {
                        let self = NJsSkin.NData.NVisual.NStaticMesh.IStaticMesh;

                        if (!CommonLibrary.IsValidObject(o))
                            return false;
                        // GetStaticMesh()
                        if (!self.Implements_GetStaticMesh(o))
                            return false;
                        return true;
                    }

                    // GetStaticMesh()
                    static Implements_GetStaticMeshChecked(context, o)
                    {
                        let classType = StaticMesh;
                        return FunctionLibrary.IsArgCountAndReturn_Class_Checked(context, o.GetStaticMesh, 0, o, classType);
                    }

                    static Implements_GetStaticMesh(o)
                    {
                        let classType = StaticMesh;
                        return FunctionLibrary.IsArgCountAndReturn_Class(o.GetStaticMesh, 0, o, classType);
                    }
                }
            }
        }
    }
};