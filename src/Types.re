[%%debugger.chrome];

type song = {
  title: string,
  artist: string,
  url: string,
};

type songList = list(song);
type secs = int;

type playingSong = {
  song,
  progress: secs,
};