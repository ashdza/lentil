[%%debugger.chrome];

type point =
  | Point(float, float);

type shape =
  | Circle(point, float)
  | Rectangle(point, point)
  | Group(list(shape));

let c = Circle(Point(0.0, 0.0), 1.0);
let r = Rectangle(Point(0.0, 0.0), Point(2.0, 2.0));

let area = s =>
  switch (s) {
  | Circle(_p, r) => 3.14 *. r *. r
  | Rectangle(Point(x1, y1), Point(x2, y2)) => (y2 -. y1) *. (x2 -. x1)
  | Group(_l) => 200.0
  };

let d = <div> (Util.str("Hi")) </div>;

let d2 = <div> d d </div>;

let hellos = (l: list(string)) : list(ReasonReact.reactElement) => {
  let stringToReact = (s: string) : ReasonReact.reactElement =>
    <div> (Util.str("Hi " ++ s)) </div>;
  List.map(stringToReact, l);
};