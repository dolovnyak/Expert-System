# Expert-System

## MacOS - [![Build Status](https://www.travis-ci.com/dolovnyak/Expert-System.svg?branch=master)](https://www.travis-ci.com/dolovnyak/Expert-System)
###

###
Expert system for logical expressions on backward-chaining inference engine.
------------

There are logical expressions, for example:
```
A => B      (A implies B)
C | D => A  (C or D implies A) 
```
All facts (fact is uppercase letter) are false by default, you can set true facts.
###
This program calculates, depending on the entered true facts - all facts values.
```
A=>B
# A - false, B - false
# A=>B - false=>false
# B - false
```
```
A=>B
=A
# A - true, B - false
# A=>B - true=>true (if implying fact is true, then fact which it implies must become true)
# B - true
```

Available logical operations:
---------
- `()` which means high priority. Example: `A + (B | C) => D`
- `!` which means NOT. Example: `!B`
- `+` which means AND. Example: `A + B`
- `|` which means OR. Example: `A | B`
- `ˆ` which means XOR. Example: `A ˆ B`
- `=>` which means "implies". Example: `A + B => C` (expression always true)
- `<=>` which means "if and only if". Example: `A + B <=> C` (expression always true)

Input file example:
--------
```
# this is a comment
C => E          # C implies E
A + B + C => D  # A and B and C implies D
A | B => C      # A or B implies C
A + !B => F     # A and not B implies F
C | !G => H     # C or not G implies H
V ^ W => X      # V xor W implies X
A + B => Y + Z  # A and B implies Y and Z
C | D => X | V  # C or D implies X or V
E + F => !V     # E and F implies not V
A + B <=> C     # A and B if and only if C
A + B <=> !C    # A and B if and only if not C
=ABG            # Initial facts : A, B and G are true. All others are false.
?GVX            # Queries : What are G, V and X ? (it doesn't matter in visual mode)
```

Build and run on `MacOS`:
-------
```
git submodule update --init --recursive
cmake -S . -B build -DINSTALL_DEPS=true
make -C build

./expert_system -v example.txt (visual mode with the ability to change expressions in real time)
or 
./expert_system example.txt (console answer)
or
./expert_system_tests
```

Graphical examples:
----------
### Simple logic example:
![](https://github.com/dolovnyak/Expert-System/blob/master/screenshots/examp1)
### K=true, C=false -> K|C=true -> A=true -> B=true
![](https://github.com/dolovnyak/Expert-System/blob/master/screenshots/screen2)
### K=false, C=false -> K|C=false -> A=false -> B=false
![](https://github.com/dolovnyak/Expert-System/blob/master/screenshots/screen1)
### K=false, C=false -> K|C=false -> !(K|C)=true -> A=true -> B=true
![](https://github.com/dolovnyak/Expert-System/blob/master/screenshots/screen3)
### K=true, C=false -> K|C=true -> !(K|C)=false -> A=false -> B=false
![](https://github.com/dolovnyak/Expert-System/blob/master/screenshots/screen4)
