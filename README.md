# minishell
a tcsh-like shell, complete with redirections and pipes, hierarchy of execution, and environment handling. It also handles history, in-line edits, and quotes.

It supports these redirectors:

    <  <<  >  >>  |  ; () && ||

## Build

To compile the binary:

    make
    # or
    make re

The compiled binary will be called:

    42sh

## Disclaimer

This project is for educational purposes only. It should not be used as a replacement for a real shell in a production environment.

