'use strict';

var App$Lentil = require("./App.bs.js");
var Belt_Debug = require("bs-platform/lib/js/belt_Debug.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Song$Lentil = require("./Song.bs.js");

Belt_Debug.setupChromeDebugger(/* () */0);

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, App$Lentil.make(Song$Lentil.Demo[/* initialSongs */5], /* array */[])), "target");

var Demo = 0;

exports.Demo = Demo;
/*  Not a pure module */
