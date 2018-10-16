[%%debugger.chrome];

module Demo = Song.Demo;

/* ReactDOMRe.renderToElementWithId(Demo.demoSongHeader, "target"); */

/* ReactDOMRe.renderToElementWithId(Demo.demoRenderSongNotCurrent, "target"); */

/* ReactDOMRe.renderToElementWithId(Demo.demoRenderSongCurrent, "target"); */

/* ReactDOMRe.renderToElementWithId(Demo.demoRenderSongList, "target"); */

ReactDOMRe.renderToElementWithId(
  <App initialSongs=Song.Demo.initialSongs />,
  "target",
);