# Anime Watchlist Manager

A command-line program written in C for tracking anime you're watching — add titles, log how many episodes you've watched, rate them, and remove entries you're done with.

## About

This project was built to practice manual memory management in C: dynamically growing an array of structs at runtime, allocating and freeing heap memory for each entry, and using Valgrind to catch and fix real memory bugs along the way.

## Features

- Add an anime with a title, number of episodes watched, and a rating
- List all anime currently in your watchlist
- Remove an anime by its position in the list
- Dynamically resizes its internal storage as you add more entries (no fixed limit)
- Cleans up all allocated memory on exit

## Built With

- C
- GDB and Valgrind (for debugging and memory-safety verification)
- Git / GitHub

## Running Locally

Clone the repo and compile with gcc:

```bash
git clone git@github.com:ekshalab/anime-watchlist.git
cd anime-watchlist
gcc -g -o watchlist main.c
./watchlist
```

You'll get a menu to add, list, or remove anime from your watchlist.

## Memory Safety

While testing, Valgrind caught a use-after-free bug: removing an anime from the list didn't correctly decrement the internal count, which caused the program to read from (and eventually double-free) memory that had already been freed. I traced the issue back to a missing `count--;` statement in the `remove_anime` function, fixed it, and checked it again with Valgrind:
