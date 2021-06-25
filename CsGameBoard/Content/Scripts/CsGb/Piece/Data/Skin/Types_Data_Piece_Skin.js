/// <reference path="../../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var FJsEnum = require('Cs/Types/Enum/Enum.js');

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static NPiece = class Piece
        {
            static NData = class Data
            {
                static NSkin = class Skin
                {
                    static ESkin = new FJsEnum("NJsGame.NPiece.NData.NSkin.ESkin");
                }
            }
        }
    }
};