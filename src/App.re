[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type songInProgress = {
  song: Types.song,
  prog: float,
  text: string,
};

type state = {
  songList: Types.songList,
  current: option(songInProgress),
};

type action =
  | Select(Types.song)
  | UpdateProgress(float)
  | LeaveComment
  | TextChange(string);

let string_of_action = a =>
  switch (a) {
  | Select(s) => "Select: " ++ s.title
  | UpdateProgress(t) => "UpdateProgress: " ++ string_of_float(t)
  | LeaveComment => "LeaveComment"
  | TextChange(s) => "TextChange: " ++ s
  };

let component = ReasonReact.reducerComponent("App");

let addFeedbackToSong = (comment, loc, song: Types.song) => {
  let c: Types.feedback = {location: loc, comment};
  let compareComments = (c1: Types.feedback, c2: Types.feedback) =>
    Pervasives.compare(c1.location, c2.location);
  {
    ...song,
    comments: Belt.List.add(song.comments, c) |> List.sort(compareComments),
  };
};

let rec dropWhile = (list, pred) =>
  switch (list) {
  | [] => []
  | [h, ...tl] => ! pred(h) ? list : dropWhile(tl, pred)
  };

let renderCommentsRoll = (songInProgress: songInProgress, style) =>
  <div className=style>
    <Util.Text label="Rolling Comments:" style="bold" />
    (
      songInProgress.song.comments
      |. dropWhile(c => c.location < songInProgress.prog)
      |> List.map((c: Types.feedback) =>
           <Util.Text
             label=(c.comment ++ Format.sprintf(" (at %0.1f)", c.location))
           />
         )
      |> Array.of_list
      |> ReasonReact.array
    )
  </div>;

let renderPlayerOnCurrentSong =
    (currentlyPlaying, send: action => unit, style) => {
  let {song: s, prog: p, text: t} = currentlyPlaying;
  <div className=style>
    <Player
      url=s.url
      onProgress=((progress: Player.secs) => send(UpdateProgress(progress)))
      progressInterval=100
    />
    <Util.Text
      label=("Edit Comment @ Position: " ++ Format.sprintf("%0.1f", p))
      style="bold"
    />
    <textarea
      className="comment-entry"
      cols=60
      rows=5
      value=t
      onChange=(ev => send(TextChange(ReactEvent.Form.target(ev)##value)))
    />
    <Util.Button
      label="Submit"
      onClick=(_event => send(LeaveComment))
      disabled=(t == "")
    />
  </div>;
};

let renderSong = (song: Types.song, currentlyPlaying, send: action => unit) => {
  let header =
    Song.renderSongHeader(song, s => send(Select(s)), "song-header");
  let (player, scroll) =
    switch (currentlyPlaying) {
    | Some({song: s, prog: _p, text: _t} as inProgress) when s.id == song.id => (
        renderPlayerOnCurrentSong(inProgress, send, "song-player"),
        renderCommentsRoll(inProgress, "song-comments"),
      )
    | _ => (ReasonReact.null, ReasonReact.null)
    };
  <div className="song-grid"> header player scroll </div>;
};

let demoRenderSongNotCurrent = renderSong(Song.example, None, Song.ignore);

let demoCurrentlyPlaying =
  Some({song: Song.example, prog: 13.293, text: "Editing comment ..."});

let demoRenderSongCurrent =
  renderSong(Song.example, demoCurrentlyPlaying, Song.ignore);

let renderSongList = (songList, currentlyPlaying, send) =>
  List.map(s => renderSong(s, currentlyPlaying, send), songList)
  |> Array.of_list
  |> ReasonReact.array;

let make = (~initialSongs: Types.songList, _children) => {
  ...component,
  initialState: () => {songList: initialSongs, current: None},
  reducer: (action: action, state: state) =>
    /* Js.log(string_of_action(action)); */
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0, text: ""}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: _p, text: t})},
      ) =>
      /* Js.log2("UpdateProgress: ", playedSec); */
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      })
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: sl, current: Some({song: s, prog: p, text: txt})},
      ) =>
      /* Js.log4("LeaveComment: ", s.title, txt, p); */
      let updatedSong = addFeedbackToSong(txt, p, s);
      let updatedState = {
        songList: List.map(s' => s'.Types.id == s.id ? updatedSong : s', sl),
        current: Some({song: updatedSong, prog: p, text: ""}),
      };
      /* Js.log2("Updated State: ", updatedState); */
      ReasonReact.Update(updatedState);
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        TextChange(txt),
        {songList: _sl, current: Some({song: s, prog: p, text: _t})},
      ) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: p, text: txt}),
      })
    | (TextChange(_), _) =>
      Js.log("ERROR: ENTER TEXT WHEN NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div className="app">
      <div className=Styles.(appTitle ++ " app-header bold")>
        (Util.str("Lentil"))
      </div>
      <div className="app-menu">
        <Util.Text label="MENU" />
        <Util.Text label="Performer" />
        <Util.Text style="bold" label="Reviewer" />
        <Util.Text label="Settings" />
      </div>
      <div className="app-content">
        (
          renderSongList(
            Util.tap(self.state.songList),
            self.state.current,
            self.send,
          )
        )
      </div>
    </div>,
};