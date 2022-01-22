# srt-timeshift

This is a command-line program written in C to fix out-of-sync .srt files. It can be improved (probably a lot) but I wrote it in a few hours as a quick solution while I was in a cabin without an internet connection and the subtitles of the series I was watching were out-of-sync. Currently, it only takes integers as offsets, though it'd be easy to modify it so it can offset floating point values. I didn't bother because I only needed to offset +3s.

```USAGE: ./timeshift subtitles.srt output.srt ±offset```

Keep in mind `offset` must be an integer (you can pass a floating point value but they'll be truncated). I'll probably update it to support other formats, support floating-point values and improve efficiency some time in the future. Suggestions are welcomed.
