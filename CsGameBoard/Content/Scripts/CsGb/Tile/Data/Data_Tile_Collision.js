/// <reference path="../../../typings/ue.d.ts">/>
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
        static NTile = class Tile
        {
            static NData = class Data
            {
                static NCollision = class Collision
                {
                    static ICollision = class InterfaceCollision
                    {
                        // CsCollisionPreset GetCollisionPreset()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedByChecked(context /*string*/, o /*object*/)
                        {
                            let self = NJsGame.NBoard.NTile.NData.NCollision.ICollision;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // GetCollisionPreset()
                            check(self.Implements_GetCollisionPresetChecked(context, o));
                            return true;
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ IsImplementedBy(o /*object*/)
                        {
                            let self = NJsGame.NBoard.NTile.NData.NCollision.ICollision;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;
                            // GetCollisionPreset()
                            if (!self.Implements_GetStaticMesh(o))
                                return false;
                            return true;
                        }

                        // GetCollisionPreset()

                        /**
                         * @param {string} context 
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetCollisionPresetChecked(context /*string*/, o /*object*/)
                        {
                            let classType = CsCollisionPreset;
                            return FunctionLibrary.IsArgCountAndReturn_Class_Checked(context, o.GetCollisionPreset, 0, o, classType);
                        }

                        /**
                         * @param {object} o 
                         * @returns {boolean}
                         */
                        static /*bool*/ Implements_GetCollisionPreset(o /*object*/)
                        {
                            let classType = CsCollisionPreset;
                            return FunctionLibrary.IsArgCountAndReturn_Class(o.GetCollisionPreset, 0, o, classType);
                        }   
                    }
                }
            }
        }
    }
};