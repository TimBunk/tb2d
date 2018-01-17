## About tb2d

tb2d is a basic framework that is used for making 2D games. It is still a work in progress, but so far so good.

## Compiling

You can use CMake to create the project files.

I have only tested my framework on windows 10 with visual studio 2017. So if you are using something else there is no guarantee it will work.

## Documentation

For documentation you need to download both Doxygen and Graphviz, Graphviz has to be installed in `C:/Program Files (x86)/Graphviz2.38` or open the Doxyfile with a text editor and change `DOT_PATH` to your path.

To generate the documentation open your command prompt(or terminal depending on your os), run doxygen (with Doxyfile as input) in the root directory of this project:

```
  doxygen Doxyfile
```

Then open `index.html` in the `documentation/html` directory.

## Libraries

- glew: <http://glew.sourceforge.net/>
- glfw: <http://www.glfw.org/>
- freetype2: <https://www.freetype.org/>
- freetypeGL: <https://github.com/rougier/freetype-gl>
- SOIL2: <https://bitbucket.org/SpartanJ/soil2>
- glm: <http://glm.g-truc.net/0.9.8/index.html>
- Box2D: <http://box2d.org/>

## License & copyright

@ Tim Bunk

Licensed under the [MIT License](LICENSE).
