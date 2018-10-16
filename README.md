# lentil

A musician's feedback service.

## Demo

I keep a running demo of a fairly current version of this app at 
https://lentil.7insights.com. The current version uses an existing React component over SoundCloud for the audio player, and when paused, the player will sometimes overlay some kind of ad. You need to close out that overlay to continue with the player.

## Overview

Musicians submit recordings of performances and receive pointed feedback from other musicians. I am implementing the front-end of this service with ReasonML + React, and will use Hasura's GraphQL server with a Postgres database for the back-end.

I keep some notes on this project on my blog at https://ashdza.github.io/blog/.

## Run Project

```sh
npm install
npm start
```
