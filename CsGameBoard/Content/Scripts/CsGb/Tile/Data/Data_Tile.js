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
                static IData = class InterfaceData
                {
                    /**
                     * @param {string} context 
                     * @param {object} o 
                     * @returns {boolean}
                     */
                    /*bool*/ static IsImplementedByChecked(context /*string*/, o /*object*/)
                    {
                        let self = NJsGame.NBoard.NData.IData;

                        check(CommonLibrary.IsValidObjectChecked(context, o));
                        return true;
                    }

                    /**
                     * @param {object} o 
                     * @returns {boolean}
                     */
                    static /*bool*/ IsImplementedBy(o /*object*/)
                    {
                        let self = NJsProjectile.NData.IData;

                        if (!CommonLibrary.IsValidObject(o))
                            return false;
                        return true;
                    }
                }
            }
        }
    }
};