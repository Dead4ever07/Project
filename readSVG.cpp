#include <string>
#include <iostream>
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

            string name = elem->Name();
            vector<const XMLAttribute*> attributs;
            /*for (const XMLAttribute *attr = elem->FirstAttribute(); attr != nullptr; attr = attr->Next())
            {
                attributs.push_back(attr);
            }*/
            if( name == "ellipse")
            {
            }
            else if(name == "circle")
            {
                
                cout<<elem->Attribute("fill")<<' '<<elem->IntAttribute("cx")<<' '<<elem->IntAttribute("cy")<<' '<< elem->IntAttribute("r")<<endl;
                Circle* node = new Circle( parse_color(elem->Attribute("fill")),{elem->IntAttribute("cx"),elem->IntAttribute("cy")}, elem->IntAttribute("r"));
                svg_elements.push_back(node);
            }

            dump(child, svg_elements);
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

        if(xml_elem->FirstChildElement() != nullptr)
        {

        dump(xml_elem->FirstChildElement(), svg_elements);
        }

        // TODO complete code -->
        
    }
}
