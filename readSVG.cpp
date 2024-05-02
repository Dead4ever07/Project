#include <string>
#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void dump(XMLElement *elem, vector<SVGElement *>& svg_elements)
    {

        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            if(child->FirstChildElement()!= nullptr)
            {
            dump(child, svg_elements);

            }
            string name = child->Name();
            vector<const XMLAttribute*> attributs;

            if( name == "ellipse"){
                Ellipse* ellipse_1 = new Ellipse( parse_color(child->Attribute("fill")),{child->IntAttribute("cx"),child->IntAttribute("cy")}, {child->IntAttribute("rx"),child->IntAttribute("ry")});
                svg_elements.push_back(ellipse_1);
            }
            else if(name == "circle")
            {
                
                Circle* node = new Circle( parse_color(child->Attribute("fill")),{child->IntAttribute("cx"),child->IntAttribute("cy")}, child->IntAttribute("r"));
                svg_elements.push_back(node);
            }
            else if(name == "polyline")
            {
                string p = child->Attribute("points");
                for(char &c: p)
                {
                    const char &t = ',';
                    const char &v = ' ';
                    if(c == t){c = v;}
                }
                istringstream in (p);
                vector<Point> vector_p;
                int n;
                int v;
                while (in>>n)
                {
                    in>>v;
                    vector_p.push_back({n,v});
                }
                 
                Polyline* polyl = new Polyline(vector_p,parse_color(child->Attribute("stroke")));
                svg_elements.push_back(polyl);
            }
            else if(name == "line")
            {
                Line* line = new Line({child->IntAttribute("x1"),child->IntAttribute("y1")},{child->IntAttribute("x2"),child->IntAttribute("y2")},parse_color(child->Attribute("stroke")));
                svg_elements.push_back(line);
            }
            else if(name == "polygon")
            {
                                string p = child->Attribute("points");
                for(char &c: p)
                {
                    const char &t = ',';
                    const char &v = ' ';
                    if(c == t){c = v;}
                }
                istringstream in (p);
                vector<Point> vector_p;
                int n;
                int v;
                while (in>>n)
                {
                    in>>v;
                    vector_p.push_back({n,v});
                }
                 
                Polygon* polyg = new Polygon(vector_p,parse_color(child->Attribute("fill")));
                svg_elements.push_back(polyg);
                
            }
            else if(name == "rect")
            {

                Rectangle* rectangle = new Rectangle({child->IntAttribute("x"),child->IntAttribute("y")},child->IntAttribute("width"),child->IntAttribute("height"),parse_color(child->Attribute("fill")));
                svg_elements.push_back(rectangle);
            }


        }
    }
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");


        dump(xml_elem, svg_elements);
        
        // TODO complete code -->
        
    }
}
