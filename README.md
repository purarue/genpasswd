# genpasswd

A password generator with defaults and some shorthands that I like

Mostly written to un-rust my C++ (heh...), but I do use this whenever I need a password

### Usage:

```
usage:
   genpasswd
   genpasswd PASSWD_LENGTH
   genpasswd [-n PASSWD_LENGTH] [-r CHARACTER_SET] [-c COUNT] [-p|-s]

options:
   -n N     length of password to generate
   -c C     number of passwords to generate
   -r R     character set to remove from allowed characters
   -p       shorthand for -n 4 -r lower -r upper -r sym
            to generate a string of random numbers of length 4
            meant to be used for bank pins
   -s       shorthand for -n 16 -r sym
            meant for websites which have strict limits on passwords

character sets:
   lowercase   : l, lower, lowercase
   uppercase   : u, upper, uppercase
   numbers     : n, num, number, numbers
   symbols     : s, sym, symbol, symbols

examples:
   genpasswd 40              : password of length 40
   genpasswd -n 30 -rsym     : password of length 30 without symbols
   genpasswd -p              : generate a bank pin

Type genpasswd -h for help
```

### Install:

Requires `make` and [`cmake`](https://cmake.org/)

```
git clone https://github.com/purarue/genpasswd
cd genpasswd
make
make install
```

#### Environment Variables

Some of the defaults can be modified by changing environment variables.

- `GENPASSWD_LENGTH`: default password length, defaults to 20
- `GENPASSWD_SIMPLE_LENGTH`: defaults simple (-s) password length, defaults to 16
- `GENPASSWD_PIN_LENGTH`: default pin (-p) password length, defaults to 4
- `GENPASSWD_COUNT`: default password count (-c), defaults to 1

#### zsh completion

This adheres to getopts, so you can put this in your zsh config:

```
# if not already present, run compinit
autoload -Uz compinit && compinit
compdef _gnu_generic genpasswd
```

... which generates completion like:

```
genpasswd -
-c  -- number of passwords to generate
-n  -- length of password to generate
-p  -- shorthand for -n 4 -r lower -r upper -r sym
-r  -- character set to remove from allowed characters
-s  -- shorthand for -n 16 -r sym
```

#### Copy to Clipboard

I wrap this in a bash script [here](https://purarue.xyz/d/genpass?dark) that copies the password to my clipboard. That looks something like:

```
#!/usr/bin/env bash
pw=$(genpasswd "$@" | head -n 1 | tr -d "\n")
echo -e "$pw"
# copy to clipboard
echo -en "$pw" | xclip -selection clipboard
```

This uses [xclip](https://linux.die.net/man/1/xclip), but if you don't have that you could use [pbcopy](https://ss64.com/osx/pbcopy.html)/[xsel](https://linux.die.net/man/1/xsel)
