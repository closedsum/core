/// <reference path="../../typings/ue.d.ts">/>
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

module.exports = class NJsInteractive
{
    static NObject = class Object
    {
        static NSelect = class Select
        {
            static ISelect = class InterfaceSelect
            {
                // Select(SelectParamsType: paramsType)

                // Deselect(DeselectParamsType: paramsType)

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ IsImplementedByChecked(context /*string*/, o /*object*/)
                {
                    let self = NJsInteractive.NObject.NSelect.ISelect;

                    check(CommonLibrary.IsValidObjectChecked(context, o));

                    // Select()
                    check(self.Implements_SelectChecked(context, o));
                    // Deselect()
                    check(self.Implements_DeselectChecked(context, o));
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
                    // Select()
                    if (!self.Implements_Select(o))
                        return false;
                    // Deselect()
                    if (!self.Implements_Deselect(o))
                        return false;
                    return true;
                }

                // Select()

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ Implements_SelectChecked(context /*string*/, o /*object*/)
                {
                    return FunctionLibrary.IsArgCountChecked(context, o.Select, 1, o);
                }

                /**
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ Implements_Select(o /*object*/)
                {
                    return FunctionLibrary.IsArgCount(o.Select, 1, o);
                }

                // Deselect()

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                 static /*bool*/ Implements_DeselectChecked(context /*string*/, o /*object*/)
                 {
                     return FunctionLibrary.IsArgCountChecked(context, o.Deselect, 1, o);
                 }
 
                /**
                 * @param {object} o 
                 * @returns {boolean}
                 */
                 static /*bool*/ Implements_Deselect(o /*object*/)
                 {
                     return FunctionLibrary.IsArgCount(o.Deselect, 1, o);
                 }
            }
        }
    }
};