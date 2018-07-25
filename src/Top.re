let comp = ReasonReact.statelessComponent("top");

let make = (~initCounts: list(int), _children) => {
  ...comp,
  render: _self => {
    let counters =
      List.map(init => <Counter i=init />, initCounts)
      |> Array.of_list
      |> ReasonReact.array;
    <div> counters </div>;
  },
};