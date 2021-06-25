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
        static NSelect = class Select
        {
            static NVisual = class Visual
            {
                static NMaterial = class Material
                {
                    static IMaterial = class InterfaceMaterial
                    {
                        // MaterialInterface[] GetSelectMaterials()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedByChecked(context /*string*/, o /*object*/)
                        {
                            let self = NJsInteractive.NObject.NSelect.ISelect;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // GetSelectMaterials()
                            check(self.Implements_GetSelectMaterialsChecked(context, o));
                            return true;
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedBy(o /*object*/)
                        {
                            let self = NJsInteractive.NObject.NSelect.ISelect;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;
                            // GetSelectMaterials()
                            if (!self.Implements_GetSelectMaterials(o))
                                return false;
                            return true;
                        }

                        // GetSelectMaterials()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetSelectMaterialsChecked(context /*string*/, o /*object*/)
                        {
                            check(FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context, o.GetSelectMaterials, 0, o));

                            let mats = o.GetSelectMaterials();

                            check(ArrayLibrary.AreAllElements_Class_Checked(context, mats, MaterialInterface));

                            return true;
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetSelectMaterials(o /*object*/)
                        {
                            if (!FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty(o.GetSelectMaterials, 0, o))
                                return false;

                            let mats = o.GetSelectMaterials();

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