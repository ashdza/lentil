[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type current =
  | Playing(Types.song, float)
  | Neutral;

type state = {
  songList: Types.songList,
  current,
};

type action =
  | Select(Types.song)
  | UpdateProgress(float);

let component = ReasonReact.reducerComponent("App");

let make = (~songList: Types.songList, _children) => {
  ...component,
  initialState: () => {songList, current: Neutral},
  reducer: (action: action, state: state) =>
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({...state, current: Playing(newSong, 0.0)})
    | (UpdateProgress(playedSec), {current: Playing(s, _p)}) =>
      ReasonReact.Update({...state, current: Playing(s, playedSec)})
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div>
      <SongList
        songList
        onSongSelect=((s: Types.song) => self.send(Select(s)))
      />
      (
        switch (self.state.current) {
        | Playing(s, p) =>
          <div>
            <Player
              url=s.url
              onProgress=(
                (progress: Player.progress) =>
                  self.send(UpdateProgress(progress.playedSeconds))
              )
            />
            <Util.Text label=(string_of_float(p)) />
          </div>
        | Neutral => ReasonReact.null
        }
      )
    </div>,
};