[%%debugger.chrome];

let comp = ReasonReact.statelessComponent("song");

let make =
    (~songList: Types.songList, ~onSongSelect: Types.song => unit, _children) => {
  ...comp,
  render: _self => {
    Js.log("SongList:render");
    let songl =
      Belt.List.map(songList, (s: Types.song) =>
        <Song
          key=(s.id |> string_of_int)
          song=s
          render=(
            _s =>
              <Util.Button label="Select" onClick=(_ev => onSongSelect(s)) />
          )
        />
      )
      |> Array.of_list
      |> ReasonReact.array;
    songl;
  },
};

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let songList: list(Types.song) = [
    Song.Demo.song,
    {
      id: 2,
      title: "Sunday Morning",
      artist: "Maroon 5",
      url: "fghij",
      comments: [],
    },
  ];
  let make = _children => {
    ...comp,
    render: _self =>
      ReasonReact.element(make(~songList, ~onSongSelect=ignore, [||])),
  };
};