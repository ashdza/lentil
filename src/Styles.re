open Css;

let none = style(empty);

let appTitle = style([fontSize(rem(1.5)), color(darkgray)]);

let song =
  style([
    display(`grid),
    gridTemplateColumns([`percent(30.), `percent(30.), `percent(20.)]),
    gridTemplateRows([`auto, `auto, `auto]),
    backgroundColor(Css.lightgrey),
    boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.6)),
  ]);

let commentsRoll = style([backgroundColor(linen)]);

let clickable = style([cursor(`pointer)]);

let title = style([backgroundColor(papayawhip), alignItems(`center)]);

let artist = style([backgroundColor(linen), alignItems(`center)]);

let playerEditor = style([gridColumnStart(1), gridColumnEnd(3)]);

let comments = style([alignItems(`center)]);

global("body", [margin(px(5))]);

global("div", [margin(px(5))]);