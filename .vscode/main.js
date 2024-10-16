/// <reference path="/home/marwinkas/.vscode/extensions/nur.script-0.2.1/@types/api.global.d.ts" />
/// <reference path="/home/marwinkas/.vscode/extensions/nur.script-0.2.1/@types/vscode.global.d.ts" />

const { TerminalLink } = require("vscode")

//  @ts-check
//  API: https://code.visualstudio.com/api/references/vscode-api

function activate(_context) {
   TerminalLink
}

function deactivate() {}

module.exports = { activate, deactivate }
