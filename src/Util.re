let str = ReasonReact.string;

let show = x => {j|$(x)|j};

let tap = x => {
  Js.log(show(x));
  x;
};

let tap2 = (x: string, y) => {
  Js.log2(x, show(y));
  y;
};

/* useful default do-nothing args for some functions */
let ignoreRender = _ => ReasonReact.null;

let ignore = _ => ();

/* Convenient <Button label="Ok"/> */
module Button = {
  let component = ReasonReact.statelessComponent("Button");

  let make = (~label, ~onClick, ~disabled=false, _children) => {
    ...component,
    render: _self => <button onClick disabled> (str(label)) </button>,
  };
};

/* Convenient <Text label="Hello"/> */
module Text = {
  let component = ReasonReact.statelessComponent("Text");

  let make = (~label, ~style="", _children) => {
    ...component,
    render: _self => <div className=style> (str(label)) </div>,
  };
};

/* drop x from front of list as long as pred(x) is true */
let rec dropWhile = (list, pred) =>
  switch (list) {
  | [] => []
  | [h, ...tl] => ! pred(h) ? list : dropWhile(tl, pred)
  };

/* Experiments making HTML/ReasonReact.elements with just functions, minimal modules or component */
/* Cannot be used for a "reducer" component i.e. with internal state beyond its input params */

/* Reason string inside JSX syntax */
let a = s => <div> (str(s)) </div>;

/* syntactic JSX in JSX */
let a1 = <div> <button /> </div>;

/* syntactic Reason expressions in JSX */
let b = (s1, s2) => <div> (a(s1)) (a(s2)) </div>;

/* syntactic array in JSX must use ...spread */
let c = (s1, s2) => <div> ...[|a(s1), a(s2)|] </div>;

/* list must be |> Array.of_list |> ReasonReact.array */
let d = (l: list((string, string))) =>
  l |> List.map(((x, y)) => b(x, y)) |> Array.of_list |> ReasonReact.array;