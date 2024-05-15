
# Programming project

## Group elements

- up202306822 Lara da Silva Moreira
- up202306823 Luís Miguel Rosa Santos
- up202306905 Vasco Costa Lemos


## Accomplished tasks

This project focuses on converting SVG (Scalable Vector Graphics) images to PNG 
(Portable Network Graphics) format. The conversion process involves reading SVG 
elements, applying transformations, and drawing a new image. The main SVG elements 
handled include ellipses, circles,  lines, polylines, polygons, and rectangles. 
Additionally,  transformations such as translation, rotation, and scaling are 
applied to these elements. Here's a structured overview of the project's key  
components and tasks:


1. Class Hierarchy for SVG Elements

Base Class: SVGElement

Contains common attributes and methods for SVG elements, such as reading 
attributes from the SVG file, applying transformations, and rendering/drawing.

Derived Classes:

Ellipse: Represents an ellipse, requires a color, coordinates for the center and both radii.

Circle: Subclass of Ellipse, represents a circle, requires a color, coordinates for 
the center and radius.

Polyline: Represents a polyline, requires a series of points and a color for the stroke.

Line: Subclass of Polyline, represents a line, requires two points and a color for the stroke.

Polygon: Represents a polygon, requires a series of points and a color.

Rectangle: Subclass of Polygon, represents a rectangle, requires the top left point, 
width, height and color.

Group: Represents a group of pointers to SVGElements. This concept is explained later.


2. Transformation Functions

Translation: translate(x, y)

Shifts an element by x units along the X-axis and y units along the Y-axis.

Rotation: rotate(v)

Rotates an element by v degrees around a rotation origin. Positive v for clockwise, 
negative for anti-clockwise. The rotation origin is specified by the transform-origin 
attribute or defaults to (0, 0).

Scaling: scale(v)

Scales an element by a factor of v. The scaling origin is specified by the 
transform-origin attribute or defaults to (0, 0). Only integer values v  >= 1 
are considered.


3. <g> (groups) and <use>

The  <g> element in SVG represents a group of other elements, allowing collective 
transformations. It can have the following attributes:


- transform: applies transformations (translate, rotate, scale) to all group elements.
- transform-origin: sets the origin point for transformations.
- id: a unique identifier that can be referenced by <use> elements.

As mentioned, a subclass Group was created to store elements of the same group.

The  <u> element essentially consists of duplicating a given  SVGElement. We added a
get_clone() function to the SVGElement class that is overwritten by every subclass 
to do the job.
