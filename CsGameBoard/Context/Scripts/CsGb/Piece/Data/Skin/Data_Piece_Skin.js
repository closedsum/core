/// <reference path="../../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var FJsEnum = require('Cs/Types/Enum/Enum.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');
// Data
var NJsSkin1 = require("Cs/Skin/Data/Visual/Material/Data_Skin_VisualMaterial.js");
var NJsSkin2 = require("Cs/Skin/Data/Visual/StaticMesh/Data_Skin_VisualStaticMesh.js");
var NJsSkin3 = require("Cs/Skin/Data/Visual/SkeletalMesh/Data_Skin_VisualSkeletalMesh.js");

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;
var MaterialVisualDataType = NJsSkin1.NData.NVisual.NMaterial.IMaterial;
var StaticMeshVisualDataType = NJsSkin2.NData.NVisual.NStaticMesh.IStaticMesh;
var SkeletalMeshVisualDataType = NJsSkin3.NData.NVisual.NSkeletalMesh.ISkeletalMesh;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var check = CommonLibrary.check;

module.exports = class NJsGame
{
    static NBoard = class Board
    {
        static NPiece = class Piece
        {
            static NData = class Data
            {
                static NSkin = class SkinData
                {
                    static ESkin = new FJsEnum();
                    
                    static ISkin = class InterfaceSkin
                    {
                        static IsImplementedByChecked(context, o)
                        {
                            let self = NJsGame.NBoard.NPiece.NData.NSkin.ISkin;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // MaterialVisualDataType (NJsSkin1.NData.NVisual.NMaterial.IMaterial)
                            let pass_MaterialVisualDataType = MaterialVisualDataType.IsImplementedBy(o);
                            // StaticMeshVisualDataType (NJsSkin2.NData.NVisual.NStaticMesh.IStaticMesh)
                            let pass_StaticMeshVisualDataType = StaticMeshVisualDataType.IsImplementedBy(o);
                            // SkeletalMeshVisualDataType (NJsSkin3.NData.NVisual.NSkeletalMesh.ISkeletalMesh)
                            let pass_SkeletalMeshVisualDataType = SkeletalMeshVisualDataType.IsImplementedBy(o);

                            if (!(pass_StaticMeshVisualDataType || pass_SkeletalMeshVisualDataType) &&
                                !pass_MaterialVisualDataType)
                            {
                                console.error(context + ": o does NOT implement the interfaces:");
                                console.error("- StaticMeshVisualDataType (NJsSkin.NData.NVisual.NStaticMesh.IStaticMesh)");
                                console.error("- MaterialVisualDataType (NJsSkin.NData.NVisual.NMaterial.IMaterial)");
                                console.error("OR");
                                console.error("- SkeletalMeshVisualDataType (NJsSkin.NData.NVisual.NSkeletalMesh.ISkeletalMesh)");
                                console.error("- MaterialVisualDataType (NJsSkin.NData.NVisual.NMaterial.IMaterial)");
                                check(0);
                            }
                            return true;
                        }

                        static IsImplementedBy(o)
                        {
                            let self = NJsGame.NBoard.NData.NSkin.ISkin;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;

                             // MaterialVisualDataType (NJsSkin1.NData.NVisual.NMaterial.IMaterial)
                             let pass_MaterialVisualDataType = MaterialVisualDataType.IsImplementedBy(o);
                             // StaticMeshVisualDataType (NJsSkin2.NData.NVisual.NStaticMesh.IStaticMesh)
                             let pass_StaticMeshVisualDataType = StaticMeshVisualDataType.IsImplementedBy(o);
                             // SkeletalMeshVisualDataType (NJsSkin3.NData.NVisual.NSkeletalMesh.ISkeletalMesh)
                             let pass_SkeletalMeshVisualDataType = SkeletalMeshVisualDataType.IsImplementedBy(o);
 
                             if (!(pass_StaticMeshVisualDataType || pass_SkeletalMeshVisualDataType) &&
                                 !pass_MaterialVisualDataType)
                             {
                                 return false;
                             }
                            return true;
                        }
                    }
                }
            }
        }
    }
};