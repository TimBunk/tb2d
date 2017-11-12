## About tb2d

tb2d is a framework that is used for making 2D games. It is still a work in progress, but so far so good.

## Compiling

You can use cmake to create the project files.

I have only tested my framework on ubuntu and @rutgerklamer tested it on arch linux for me, so if you are using something else there is no guarentee it will work.
Also you will need to install the sdl2 package if you are on ubuntu run this in the terminal
"sudo apt-get install libsdl2-2.0-0 libsdl2-ttf-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev".

On arch linux you need to install other sdl2 packages too, You can run "sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer"

## Documentation

At the moment there is only a documentation of my game "The Restless Tombs".
To view this documentation go to the root of this folder and type in the terminal "doxygen Doxyfile" it will create a documentation folder and search for index.html and open it.

## Libraries

- glew: <http://glew.sourceforge.net/>
- sdl2: <https://www.libsdl.org/>
- sdl2-ttf <https://www.libsdl.org/projects/SDL_ttf/>
- sdl2-image <https://www.libsdl.org/projects/SDL_image/>
- sdl2-mixer <https://www.libsdl.org/projects/SDL_mixer/>
- glm: <http://glm.g-truc.net/0.9.8/index.html>
- SOIL2: <https://bitbucket.org/SpartanJ/soil2>
- box2d: <http://box2d.org/>

## License & copyright

@ Tim Bunk

Licensed under the [MIT License](LICENSE).
