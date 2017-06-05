# flashcards

[![WTFPL licensed](https://img.shields.io/badge/license-WTFPL-blue.svg)](./LICENSE)

*flashcards* is a tiny C++ terminal program for computerized flashcards. I created it
for personal use, to improve my spanish vocabulary.

## Building

*flashcards* may be built using `boost.build`, aka `bjam`. Simply type `bjam`
in the root of the project directory. Binaries will be placed in `/stage`.

## Data format

Flashcards files are text files, formatted as follows:

- One line for the front of the card
- One line for the back of the card
- Skip one line

Use unix line endings. There are some examples in the `/data` folder.

Enjoy!
