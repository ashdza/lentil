[%%debugger.chrome];

let comp = ReasonReact.statelessComponent("song");

let make = (~songList: Types.songList, _children) => {
  ...comp,
  render: _self => {
    let songl =
      List.map(s => <Song song=s />, songList)
      |> Array.of_list
      |> ReasonReact.array;
    <div> songl </div>;
  },
};

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let songList: list(Types.song) = [
    Song.Demo.song,
    {title: "Sunday Morning", artist: "Maroon 5", url: "fghij"},
  ];
  let make = _children => {
    ...comp,
    render: _self => ReasonReact.element(make(~songList, [||])),
  };
};