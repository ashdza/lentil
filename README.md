# lentil

A musician's feedback service.

## Overview

Musicians submit recordings of performances and receive pointed feedback from other musicians. I am implementing the front-end of this service with ReasonML + React, and will use Hasura's GraphQL server with a Postgres database for the back-end.

The core idea is summarized by this interaction:
![](https://ashdza.github.io/blog/2018/07/02/Lentil-scenario-1/sequence-diagram.png)

I keep some notes on this project on my blog at https://ashdza.github.io/blog/.

## Demo

I keep a running demo of a fairly current version of this app at 
https://lentil.7insights.com.

I currently  use an existing React component over SoundCloud for the audio player, and when paused, the player sometimes overlays an ad. You need to close out that overlay to continue with the player.

## Code Overview

Read the code in the following order:

```
Types.re
Song.re
App.re
```

## Run Project

After cloning this repository:

```sh
npm install
npm start
```
