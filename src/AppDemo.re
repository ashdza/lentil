[%%debugger.chrome];

let comp = ReasonReact.statelessComponent("demo");
let initialSongs: list(Types.song) = [
  Song.Demo.song,
  {
    id: 3,
    title: "Sunday Morning",
    artist: "Maroon 5",
    url: "https://soundcloud.com/maroon-5/sunday-morning",
    comments: [],
  },
];

let make = _children => {...comp, render: _self => <App initialSongs />};