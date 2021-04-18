<img src="https://github.com/daltomi/8bpl/raw/master/screenshot.png"/>

```
___________________________________________________

 8bpl (8 Bits Per Linux) framework

 Author: daltomi

 Email: daltomi@disroot.org

 https://github.com/daltomi/8bpl
___________________________________________________


Language and libraries:
-----------------------

- Language: C99

- SDL2

- Graphic engine: www.tilengine.org

- https://github.com/RandyGaul/cute_headers

- https://github.com/nothings/stb

- https://github.com/SanderMertens/flecs


Organization of the project:
----------------------------

- Directories:

    Libraries/
            |___Tilengine/ (Note: custom library.)
            |           |___Makefile
            |           |___build.sh
            |           |___LICENSE
            |           |___README.md
            |           |___include/
            |           |         |___Tilengine.h
            |           |___src/
            |                  |___*.c
            |
            |___flecs/
            |        |___Makefile
            |        |___build.sh
            |        |___LICENSE
            |        |___include/
            |        |         |___*.h
            |        |___src/
            |                  |___*.c
            |
            |___cute_headers/
            |              |___README.md
            |              |___include/
            |                        |___*.h
            |
            |___stb/
            |     |___README.md
            |     |___LICENSE
            |     |___include/
            |               |___*.h
            |
            |___8bpl/
                   |___Makefile
                   |___build.sh
                   |___LICENSE
                   |___include/
                   |         |___*.h
                   |___src/
                         |___*.c
    Games/
        |___new_name.sh
        |___Makefiles/
        |           |___Makefile.common
        |           |___Makefile.libTilengine
        |           |___Makefile.libcute_headers
        |           |___Makefile.lib8bpl
        |           |___Makefile.libflecs
        |           |___Makefile.libstb
        |___Templates/
                    |___data/
                    |      |___{font,sound,images}
                    |___main.c.template
                    |___config.h.in.template
                    |___Makefile.template
                    |___gitignore.template



Example create new project:
---------------------------

8bpl ignores any project directory in Games/.
This allows you to create a new repo within your project:

	1) git clone https://github.com/daltomi/8bpl.git

	2) cd 8bpl/Games

	3) ./new_game.sh MyGame
	   (automatically: git init, git add)

	4) cd MyGame

	5) make && (./test)

	6) git remote add <YOUR REMOTE REPO>
	   git commit -a -m 'First commit.'
	   git push
	   ..etc..

Now is has 2 repos, one in 8bpl/ directory and the other in MyGame/ directory.

-----------------
    ...          |
    Libraries/   |   <-- 8bpl/.git
    Games/       |
-----------------
        |___MyGame/
                |___.git/
                |___.gitignore
                |___Makefile
                |___data/
                |      |___{images,sound,etc.}
                |___src/
                |     |___main.c, *.c, *.o
                |___libs/ (gitignore)
                |      |___*.so
                |___include/
                         |___*.h
                         |___*.inc



Example export: (TODO)
---------------

MyGame/
    ...
    |___export/ (ignore by MyGame git)
              |___mygame (exec file)
              |
              |___libs/
              |      |___*.so
              |
              |___data/
              |
              |___Licenses/
              |         |___Tilengine.LICENSE
              |         |___cute_headers.LICENSE
              |         |___mygame.LICENSE
              |___README



new_game.sh options:
---------------

Use --help



EOF
```
