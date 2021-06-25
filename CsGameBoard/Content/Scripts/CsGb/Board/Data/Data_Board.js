/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsGame1 = require('CsGb/Tile/Types_Tile.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');
var NJsArray = require('Cs/Library/Library_Array.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;
var ArrayLibrary = NJsArray.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

// "typedefs" - enums
var TileType = NJsGame1.NBoard.ETile;

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static NData = class Data
        {
            static IData = class InterfaceData
            {
                // Transform     GetTransform()
                // IntVector[]   GetLayout()

                static IsImplementedByChecked(context, o)
                {
                    let self = NJsGame.NBoard.NData.IData;

                    check(CommonLibrary.IsValidObjectChecked(context, o));

                    // GetTransform()
                    check(self.Implements_GetTransformChecked(context, o));
                    // GetLayout()
                    check(self.Implements_GetLayoutChecked(context, o));
                    return true;
                }

                static IsImplementedBy(o)
                {
                    let self = NJsProjectile.NData.IData;

                    if (!CommonLibrary.IsValidObject(o))
                        return false;
                    // GetTransform()
                    if (!self.Implements_Transform(o))
                        return false;
                    // GetLayout()
                    if (!self.Implements_GetLayout(o))
                        return false;
                    return true;
                }

                // GetTransform()
                static Implements_GetTransformChecked(context, o)
                {
                    let classType = Transform;
                    return FunctionLibrary.IsArgCountAndReturn_Class_Checked(context, o.GetTransform, 0, o, classType);
                }

                static Implements_GetTransform(o)
                {
                    let classType = Transform;
                    return FunctionLibrary.IsArgCountAndReturn_Class(o.GetTransform, 0, o, classType);
                }

                // GetLayout()
                static Implements_GetLayoutChecked(context, o)
                {
                    check(FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context, o.GetLayout, 0, o));

                    let ret = o.GetLayout();
                    let classType = IntVector;

                    check(ArrayLibrary.IsNotEmptyAndAllElements_Class_Checked(context, ret, classType));
                    return true;
                }

                static Implements_GetLayout(o)
                {
                    if (!FunctionLibrary.IsArgCountAndReturn_ArrayAndNotEmpty(o.GetLayout, 0, o))
                        return false;

                    let ret = o.GetLayout();
                    let classType = IntVector;

                    return ArrayLibrary.IsNotEmptyAndAllElements_Class(ret, classType);
                }
            }
        }
    }
};