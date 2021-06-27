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

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static ITurn = class InterfaceTurn
        {
            // Perform()
            // Complete()
            // bool HasCompleted()
            
            static IsImplementedByChecked(context, o)
            {
                let self = NJsGame.NBoard.ITurn;

                check(CommonLibrary.IsValidObjectChecked(context, o));

                // Perform()
                check(self.Implements_PerformChecked(context, o));
                // Complete()
                check(self.Implements_CompleteChecked(context, o));
                // HasCompleted()
                check(self.Implements_HasCompletedChecked(context, o));
                return true;
            }

            static IsImplementedBy(o)
            {
                let self = NJsGame.NBoard.ITurn;

                if (!CommonLibrary.IsValidObject(o))
                    return false;
                // Perform()
                if (!self.Implements_Perform(o))
                    return false;
                // Complete()
                if (!self.Implements_Complete(o))
                    return false;
                // HasCompleted()
                if (!self.Implements_HasCompleted(o))
                    return false;
                return true;
            }

            // Perform()

            static Implements_PerformChecked(context, o)
            {
                return FunctionLibrary.IsArgCountChecked(context, o.Perform, 0, o);
            }

            static Implements_Perform(o)
            {
                return FunctionLibrary.IsArgCount(o.Perform, 0, o);
            }

            // Complete()
            
            static Implements_CompleteChecked(context, o)
            {
                return FunctionLibrary.IsArgCountChecked(context, o.Complete, 0, o);
            }

            static Implements_Complete(o)
            {
                return FunctionLibrary.IsArgCount(o.Complete, 0, o);
            }

            // HasCompleted()
            
            static Implements_HasCompletedChecked(context, o)
            {
                return FunctionLibrary.IsArgCountChecked(context, o.HasCompleted, 0, o);
            }

            static Implements_HasCompleted(o)
            {
                return FunctionLibrary.IsArgCount(o.HasCompleted, 0, o);
            }
        }
    }
};