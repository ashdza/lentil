'use strict';

var App$Lentil = require("./App.bs.js");
var Belt_Debug = require("bs-platform/lib/js/belt_Debug.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");

Belt_Debug.setupChromeDebugger(/* () */0);

ReactDOMRe.renderToElementWithId(App$Lentil.demoRenderSongCurrent, "target");

/*  Not a pure module */
