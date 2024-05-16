
# Programming project

## Group elements

- up202306822 Lara da Silva Moreira
- up202306823 Luís Miguel Rosa Santos
- up202306905 Vasco Costa Lemos


## Accomplished tasks

This project focuses on converting SVG (Scalable Vector Graphics) images to 
PNG (Portable Network Graphics) format. The conversion process involves reading 
SVG elements, applying transformations, and drawing the new image. The class 
hierarchy for SVG elements is as follows:

Base Class: SVGElement;

- Ellipse: Requires color, center coordinates, and radii;
- Circle: A type of Ellipse with a single radius;
- Polyline: Requires points and stroke color;
- Line: A type of Polyline with two points;
- Polygon: Requires points and color;
- Rectangle: A type of Polygon with a top-left point, width, height, and color;
- Group: Holds pointers to SVG elements of the same group (more details below).

SVG elements can undergo multiple transformations via the transform attribute, 
influenced by the transform-origin for certain operations. The supported 
transformations are translate, rotate, and scale.

Additionally, SVG elements can be grouped using the <g> element to share 
transformations and duplicated using the <use> element.

The program will retrieve an SVG file from the input folder and perform the 
following steps:

- Identify the shape (or group, in which case it will run the function again 
for its elements) and parse them into corresponding SVGElements; 
- Check for any transformation functions and adjust the shape accordingly;
- Check the presence of an “id” attribute (which is used to store the attributes 
and reference a shape);
- Draw the final PNG image and save it in the output folder.
