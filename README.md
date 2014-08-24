The Soul engine is an intermediate and high end layer based on pyglet wrapper
for OpenGL. It targets OpenGL 3.X and Python 3000. It provide the mean to draw
	3D models on the screens, manipulating the camera and give access to
	a reasonable particule engine. The proper game engine is build on top of
	pyglet which provide the main event loop and management for input. Thus the
	Soul engine is limited to the realm of graphics. As a learning and
	experimenting project, stability should not be assumed.

The goal of the engine is to provide:
	¤A clean interface for 3D programming
	¤A fast enough engine to render a 3rd person game using modern 3d models
	¤To be based on simple requirement of 3D models as .obj and a custom made container for
	animation.
	¤To provided a basic cutscene API.

The philosphy of development put emphasis on:
	¤KISS principles: simple, readable and reusable code
	¤Layered code: lower end utilities to feed a higher level layer
	¤Modern and agile: comprehensive and modern OpenGL will be prefered to
	achieve decents performance.
	¤DRY: don't repeat yourself, data should be define once
	¤Functionnal: where appropriate, side effect should be avoided

	This mean the code should avoid nasty tricks while focusing on building
	a solid foundation doing most of the legs work. The higher level layer
	should only provide a small API used to load 3D models and manage them as
	games objects. The lower layer should manipulate the data as to feed the
	OpenGL server in an effective manner as to avoid any unecessary bottleneck,
	notably the bus limit. Similar algorithms should look similar.

Project requirement:
	¤Python 3.4 or higher
	¤Pyglet 1.2 or higher
	¤shader.py from Tristam Mcdonald

Project structure:
	¤src: the code, include shader.py
	¤test: testing code
	¤res: various resources
	¤scripts: scripts helping the engine
	¤README.md: this readme

	The project master branch is considered stable and will be updated for any
	major version, all tests should run.
	The dev branch is relatively stable code and should be updated for any
	minor version
	The others branch should never be check out for production purpose

Project versionning:
	The project follow the standard versionning scheme: Major.Minor.Patch
	A Major bump indicate legacy breaking
	A Minor bump indicate the addition or overhaul of a module or aspect of the
	project, it guarantee to not break any working code for the associated
	Major.
	A patch bump represent a small modification to the code: documentation,
	tests, bug fixes, stability or performance enhancement.
	A sufficient number of patch can be grouped as a minor version.

Project packaging:
	[This will change]
	soul.utils		: utilities and often used algorithms
	soul.cutscene	: the cutscene api
	soul.gl			: lower layer, exposed an intermediate api
	soul.engine		: higher layer, the actuals class and methods used by a game
					  engine
