twoD
====

twoD is a very simple 2D gaming engine created for didactic purposes using
Allegro 5 and licensed under the LGPL 3 <http://www.gnu.org/licenses/lgpl-3.0.txt>.

I'm developing this on my free time, so things are going slowly :(

*Completed:*
- basic structure
- keyboard keys events
- framerate control
- animated sprites
- play sounds
- text drawing (with buffering)
- draw objects according to layers
- primitives support
- texturized primitives
- movement support (speed, direction)
- parallax scrolling
- Physics (simple version: collision, gravity and bounce)
- Object factory (to be used with TMX files)

*To be done:*
- map building using TMX files from the 'Tiled' software (*working*)
- menu generators
- game example
- read all parameters from a configuration file (instead of hardcoded)
- port to SDL (instead of allegro)
- turn into a library
- optimizations
- documentation using doxygen
- build using automake/autoconf or cmake

*Future optimizations:*
- multi-thread operations (for better performance)
- error handling
- enhanced physics (Box2D)
- make sure no memory is leaking

Yeah, there's still a long way to go :D

