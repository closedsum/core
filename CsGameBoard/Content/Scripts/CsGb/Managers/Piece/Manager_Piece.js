/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsGame1 = require('CsGb/Piece/Types_Piece.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;
var IsArgsValidChecked = FunctionLibrary.IsArgsValidChecked;
var IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked;

// "typedefs" - enums
var PieceType = NJsGame1.NBoard.EPiece;

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
                    this.ClassMap = new Map();
                    this.DataMap = new Map();
                    this.SkinMap = new Map();

                    this.Pieces = [];
                }

                Init(core)
                {
                    Core = core;
                }

                /**
                 * @param {string} context 
                 * @param {string} dataName 
                 * @param {string} className 
                 */
                ConstructDataObject(context /*string*/, dataName /*string*/, className /*string*/)
                {
                    let args = [{value: dataName, type: "string"}, {value: className, type: "string"}];

                    check(IsArgsValidChecked(context, args));
                    check(IsStringNotEmptyChecked(context, dataName));
                    check(IsStringNotEmptyChecked(context, className));

                    let data_C = Core.GetClassChecked(context, className);
                    let data   = new data_C(Core.GetWorld()); 

                    check(CommonLibrary.IsClassOfChecked(context, data, data_C));

                    this.DataMap.set(dataName, data);
                    data.Init(Core, dataName);
                }

                /**
                 * @param {string} context 
                 * @param {string} skinName 
                 * @param {string} className 
                 */
                ConstructSkinObject(context /*string*/, skinName /*string*/, className /*string*/)
                {
                    let args = [{value: skinName, type: "string"}, {value: className, type: "string"}];

                    check(IsArgsValidChecked(context, args));
                    check(IsStringNotEmptyChecked(context, skinName));
                    check(IsStringNotEmptyChecked(context, className));

                    let skin_C = Core.GetClassChecked(context, className);
                    let skin   = new skin_C(Core.GetWorld());

                    check(CommonLibrary.IsClassOfChecked(context, skin, skin_C));

                    this.SkinMap.set(skinName, skin);
                    skin.Init(Core, skinName);
                }

                /**
                 * @param {string} context 
                 * @param {string} dataName
                 * @returns {NJsGame.NBoard.NPiece.NData.IData} 
                 */
                /*DataType*/ GetDataChecked(context /*string*/, dataName /*string*/)
                {
                    let args = [{value: dataName, type: "string"}];

                    check(IsArgsValidChecked(context, args));
                    check(IsStringNotEmptyChecked(context, dataName));

                    return this.DataMap.get(dataName);
                }

                /**
                 * @param {string} context 
                 * @param {NJsGame.NBoard.EPiece} pieceType
                 * @returns {NJsGame.NBoard.NPiece.NData.IData} 
                 */
                /*DataType*/ GetDataByTypeChecked(context /*string*/, pieceType /*PieceType*/)
                {
                    let args = [{value: pieceType, type: PieceType}];

                    check(IsArgsValidChecked(context, args));
                 
                    return this.GetDataChecked(context, pieceType.GetName());
                }

                /**
                 * @param {string} context 
                 * @param {string} skinName 
                 * @returns {NJsGame.NBoard.NPiece.NData.NSkin.ISkin} 
                 */
                /*SkinType*/ GetSkinChecked(context /*string*/, skinName /*string*/)
                {
                    let args = [{value: skinName, type: "string"}];

                    check(IsArgsValidChecked(context, args));
                    check(IsStringNotEmptyChecked(context, skinName));

                    return this.SkinMap.get(skinName);
                }

                /**
                 * @param {string} context 
                 * @param {string} dataName
                 * @param {FJsCPiece_C} 
                 */
                /*FJsCPiece_C*/ GetClassChecked(context /*string*/, dataName /*string*/)
                {
                    let args = [{value: dataName, type: "string"}];

                    check(IsArgsValidChecked(context, args));
                    check(IsStringNotEmptyChecked(context, dataName));

                    return this.ClassMap.get(dataName);
                }

                /**
                 * @param {string} context 
                 * @param {NJsGame.NBoard.EPiece} pieceType
                 * @param {FJsCPiece_C} 
                 */
                /*FJsCPiece_C*/ GetClassByTypeChecked(context /*string*/, pieceType /*PieceType*/)
                {
                    let args = [{value: pieceType, type: PieceType}];

                    check(IsArgsValidChecked(context, args));

                    return this.GetClassChecked(context, pieceType.GetName());
                }

                /**
                 * @param {string} context 
                 * @param {NJsGame.NBoard.EPiece} pieceType 
                 * @returns {FJsCPiece_C}
                 */
                /*FJsCPiece_C*/ SpawnChecked(context /*string*/, pieceType /*PieceType*/)
                {
                    let classType = this.GetClassByTypeChecked(context, pieceType);
                    let piece = new classType(Core.GetWorld());

                    check(CommonLibrary.IsValidObjectChecked(context, piece));

                    this.Pieces.push(piece);
                    
                    return piece;
                }
            }
        }
    }
};