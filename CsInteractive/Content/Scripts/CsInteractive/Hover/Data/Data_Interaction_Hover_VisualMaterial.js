/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');
var NJsArray = require("Cs/Library/Library_Array.js")

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;
var ArrayLibrary = NJsArray.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

module.exports = class NJsInteraction
{
    static NData = class Data
    {
        static NHover = class Hover
        {
            static NVisual = class Visual
            {
                static NMaterial = class Material
                {
                    static IMaterial = class InterfaceMaterial
                    {
                        // MaterialInterface[] GetHoverMaterials()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedByChecked(context /*string*/, o /*object*/)
                        {
                            let self = NJsInteraction.NData.NHover.NVisual.NMaterial.IMaterial;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // GetHoverMaterials()
                            check(self.Implements_GetHoverMaterialsChecked(context, o));
                            return true;
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedBy(o /*object*/)
                        {
                            let self = NJsInteraction.NData.NHover.NVisual.NMaterial.IMaterial;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;
                            // GetHoverMaterials()
                            if (!self.Implements_GetHoverMaterials(o))
                                return false;
                            return true;
                        }

                        // GetHoverMaterials()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetHoverMaterialsChecked(context /*string*/, o /*object*/)
                        {
                            check(FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context, o.GetHoverMaterials, 0, o));

                            let mats = o.GetHoverMaterials();

                            check(ArrayLibrary.AreAllElements_Class_Checked(context, mats, MaterialInterface));

                            return true;
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetHoverMaterials(o /*object*/)
                        {
                            if (!FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty(o.GetHoverMaterials, 0, o))
                                return false;

                            let mats = o.GetHoverMaterials();

                            if (!ArrayLibrary.AreAllElements_Class(mats, MaterialInterface))
                                return false;
                            return true;
                        }
                    }
                }
            }
        }
    }
};