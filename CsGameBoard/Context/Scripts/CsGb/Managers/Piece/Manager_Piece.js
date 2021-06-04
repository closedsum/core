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

var Core;

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static NPiece = class Piece
        {
            static FManager = class Manager
            {
                constructor()
                {
                    this.DataMap = new Map();
                    this.SkinMap = new Map();
                }

                Init(core)
                {
                    Core = core;
                }

                ConstructDataObject(context, dataName, className)
                {
                    let args = [{value: dataName, type: "string"}, {value: className, type: "string"}];

                    check(FunctionLibrary.IsArgsValidChecked(context, args));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, dataName));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, className));

                    let data_C = Core.GetClassChecked(context, className);
                    let data   = new data_C(Core.GetWorld()); 

                    check(CommonLibrary.IsClassOfChecked(context, data, data_C));

                    this.DataMap.set(dataName, data);
                    data.Init(Core, dataName);
                }

                ConstructSkinObject(context, skinName, className)
                {
                    let args = [{value: skinName, type: "string"}, {value: className, type: "string"}];

                    check(FunctionLibrary.IsArgsValidChecked(context, args));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, skinName));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, className));

                    let skin_C = Core.GetClassChecked(context, className);
                    let skin   = new skin_C(Core.GetWorld());

                    check(CommonLibrary.IsClassOfChecked(context, skin, skin_C));

                    this.SkinMap.set(skinName, skin);
                    skin.Init(Core, skinName);
                }

                GetDataChecked(context, dataName)
                {
                    let args = [{value: dataName, type: "string"}];

                    check(FunctionLibrary.IsArgsValidChecked(context, args));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, dataName));

                    return this.DataMap.get(dataName);
                }

                GetSkinChecked(context, skinName)
                {
                    let args = [{value: skinName, type: "string"}];

                    check(FunctionLibrary.IsArgsValidChecked(context, args));
                    check(CommonLibrary.IsStringNotEmptyChecked(context, skinName));

                    return this.SkinMap.get(skinName);
                }
            }
        }
    }
};