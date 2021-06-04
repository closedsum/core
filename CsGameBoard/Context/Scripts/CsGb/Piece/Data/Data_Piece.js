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

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static NPiece = class Piece
        {
            static NData = class Data
            {
                static IData = class InterfaceData
                {
                    static IsImplementedByChecked(context, o)
                    {
                        let self = NJsGame.NBoard.NPiece.NData.IData;

                        check(CommonLibrary.IsValidObjectChecked(context, o));

                        // GetType()
                        check(self.Implements_GetTypeChecked(context, o));
                        return true;
                    }

                    static IsImplementedBy(o)
                    {
                        let self = NJsGame.NBoard.NPiece.NData.IData;

                        if (!CommonLibrary.IsValidObject(o))
                            return false;
                        // GetType()
                        if (!self.Implements_GetType(o))
                            return false;
                        return true;
                    }

                    // GetType()
                    static Implements_GetTypeChecked(context, o)
                    {
                        return FunctionLibrary.IsArgCountAndReturn_Int_Checked(context, o.GetType, 0, o);
                    }

                    static Implements_GetType(o)
                    {
                        return FunctionLibrary.IsArgCountAndReturn_Int(o.GetType, 0, o);
                    }
                }
            }
        }
    }
};