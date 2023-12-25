/// <reference path="custom_typings/Cs.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Globals
var FileShortName = "Empty";

function main()
{
    let context = "Entry Point - " + FileShortName;
    console.log(context);

    purge_modules();
    gc();
}

main();