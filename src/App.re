[%%debugger.chrome];

open Types;

/* App is the top-level Lentil component */
/* App is a Reason-React stateful component, built as a ReasonML module (file). */
/* Its set of actions is defined by Types.action */
/* Its state is defined by Types.state */
/* It uses an initial list of songs to build its initialState */

let component = ReasonReact.reducerComponent("App");

let make = (~initialSongs: list(song), _children) => {
  ...component,
  initialState: () => {songList: initialSongs, playing: None},
  reducer: (action: action, state: state) =>
    /* Js.log(string_of_action(action)); */
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({...state, playing: Some({song: newSong, position: 0.0, enteredText: ""})})
    | (UpdatePosition(playedSec), {songList: _sl, playing: Some({song: s, position: _p, enteredText: t})}) =>
      /* Js.log2("UpdateProgress: ", playedSec); */
      ReasonReact.Update({...state, playing: Some({song: s, position: playedSec, enteredText: t})})
    | (UpdatePosition(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (LeaveComment, {songList: sl, playing: Some({song: s, position: p, enteredText: txt})}) =>
      /* Js.log4("LeaveComment: ", s.title, txt, p); */
      let updatedSong = Song.addFeedbackToSong(txt, p, s);
      let updatedState = {
        songList: List.map((s': song) => s'.id == s.id ? updatedSong : s', sl),
        playing: Some({song: updatedSong, position: p, enteredText: ""}),
      };
      /* Js.log2("Updated State: ", updatedState); */
      ReasonReact.Update(updatedState);
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (CommentTextChange(txt), {songList: _sl, playing: Some({song: s, position: p, enteredText: _t})}) =>
      ReasonReact.Update({...state, playing: Some({song: s, position: p, enteredText: txt})})
    | (CommentTextChange(_), _) =>
      Js.log("ERROR: ENTER TEXT WHEN NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div className="app">
      <div className="app-header">
        <div className="app-title"> (Util.str("Lentil")) </div>
        <div className="app-subtitle"> (Util.str("For Students of Music")) </div>
      </div>
      <div className="app-menu">
        <Util.Text label="MENU" />
        <Util.Text label="Perform" />
        <Util.Text style="bold" label="Review" />
        <Util.Text label="Improve" />
        <Util.Text label="Settings" />
      </div>
      <div className="app-content"> (Song.renderSongList(self.state.songList, self.state.playing, self.send)) </div>
    </div>,
};

module Demo = {
  let demoApp = ReasonReact.element(make(~initialSongs=Song.Demo.initialSongs, [||]));
  /* equivalent to: <App initialSongs=Song.Demo.initialSongs /> */
};