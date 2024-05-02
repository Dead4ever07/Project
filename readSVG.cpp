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

        elem->Name();
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
                string p = elem->Attribute("points");
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
