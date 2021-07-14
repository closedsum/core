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
            static NMaterial = class Material
            {
                static IMaterial = class InterfaceMaterial
                {
                    // MaterialInterface[] GetMaterials()

                    static IsImplementedByChecked(context, o)
                    {
                        let self = NJsSkin.NData.NVisual.NMaterial.IMaterial;

                        check(CommonLibrary.IsValidObjectChecked(context, o));

                        // GetMaterials()
                        check(self.Implements_GetMaterialsChecked(context, o));
                        return true;
                    }

                    static IsImplementedBy(o)
                    {
                        let self = NJsSkin.NData.NVisual.NMaterial.IMaterial;

                        if (!CommonLibrary.IsValidObject(o))
                            return false;
                        // GetMaterials()
                        if (!self.Implements_GetMaterials(o))
                            return false;
                        return true;
                    }

                    // GetMaterials()
                    static Implements_GetMaterialsChecked(context, o)
                    {
                        return FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context, o.GetMaterials, 0, o);
                    }

                    static Implements_GetMaterials(o)
                    {
                        return FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty(o.GetMaterials, 0, o);
                    }
                }
            }
        }
    }
};