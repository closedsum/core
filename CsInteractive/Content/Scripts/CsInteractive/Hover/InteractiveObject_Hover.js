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
        static NHover = class Hover
        {
            static IHover = class InterfaceHover
            {
                // Hover(HoverParamsType: paramsType)

                // UnHover(UnHoverParamsType: paramsType)

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ IsImplementedByChecked(context /*string*/, o /*object*/)
                {
                    let self = NJsInteractive.NObject.NHover.IHover;

                    check(CommonLibrary.IsValidObjectChecked(context, o));

                    // Hover()
                    check(self.Implements_HoverChecked(context, o));
                    // UnHover()
                    check(self.Implements_UnHoverChecked(context, o));
                    return true;
                }

                /**
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ IsImplementedBy(o /*object*/)
                {
                    let self = NJsInteractive.NObject.NHover.IHover;

                    if (!CommonLibrary.IsValidObject(o))
                        return false;
                    // Hover()
                    if (!self.Implements_Hover(o))
                        return false;
                    // UnHover()
                    if (!self.Implements_UnHover(o))
                        return false;
                    return true;
                }

                // Hover()

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ Implements_HoverChecked(context /*string*/, o /*object*/)
                {
                    return FunctionLibrary.IsArgCountChecked(context, o.Hover, 1, o);
                }

                /**
                 * @param {object} o 
                 * @returns {boolean}
                 */
                static /*bool*/ Implements_Hover(o /*object*/)
                {
                    return FunctionLibrary.IsArgCount(o.Hover, 1, o);
                }

                // UnHover()

                /**
                 * @param {string} context 
                 * @param {object} o 
                 * @returns {boolean}
                 */
                 static /*bool*/ Implements_UnHoverChecked(context /*string*/, o /*object*/)
                 {
                     return FunctionLibrary.IsArgCountChecked(context, o.UnHover, 1, o);
                 }
 
                /**
                 * @param {object} o 
                 * @returns {boolean}
                 */
                 static /*bool*/ Implements_UnHover(o /*object*/)
                 {
                     return FunctionLibrary.IsArgCount(o.UnHover, 1, o);
                 }
            }
        }
    }
};