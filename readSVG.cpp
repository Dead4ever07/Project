#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    
    void transform_application(const XMLElement* elem, SVGElement* objecto)
    {
        if(elem->Attribute("transform"))
        {   
            string trans_origin;
            Point origin = {0,0};
            if(elem->Attribute("transform-origin"))
            {
                trans_origin = elem->Attribute("transform-origin");
                istringstream iss(trans_origin);
                int x,y;
                iss>>x>>y;
                origin = {x,y};
            }
            string transform_obj = elem->Attribute("transform");
            replace(transform_obj.begin(), transform_obj.end(), ',', ' ');
            // istringstream itt(transform_obj);
            // char t;
            // itt>>t;
            if(transform_obj[0] == 's')
            {
                istringstream iss(transform_obj.substr(6));
                int n;
                iss>>n;
                objecto->scale(origin,n);
            }
            else if(transform_obj[0] == 'r')
            {
                istringstream iss(transform_obj.substr(7));
                int n;
                iss>>n;
                objecto->rotate(origin,n);
            }
            else if(transform_obj[0] == 't')
            {
                istringstream iss(transform_obj.substr(10));
                int x,y;
                iss>>x>>y;
                objecto->translate({x,y});
            }
        }
    }
    void id_get(SVGElement * elemento,vector<pair<string, SVGElement*>>& map_references, const XMLElement* child)
    {
        if(child->Attribute("id"))
        {    
            map_references.emplace_back(child->Attribute("id"), elemento);
        }
    }

    // dump is a recursive function that in each recursion step gets the child 
    // of the previous element while there are children to iterate through
    void dump(XMLElement *elem, vector<SVGElement *>& svg_elements, vector<pair<string, SVGElement*>>& map_references)
    {
        //after get to the base child(the child which doesnt have any children) it iterates through them
        //after iterating through each child, then gets to the end of the for loop, and return to the father of those children
        //then it iterates to the next element with the same depth and if the element has any children it repeats the process
        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
          
            string name = child->Name();
            SVGElement* element;
            if( name == "ellipse"){
                element = new Ellipse( parse_color(child->Attribute("fill")),{child->IntAttribute("cx"),child->IntAttribute("cy")}, {child->IntAttribute("rx"),child->IntAttribute("ry")}) ;
            }
            else if(name == "circle")
            {
                element = new Circle( parse_color(child->Attribute("fill")),{child->IntAttribute("cx"),child->IntAttribute("cy")}, child->IntAttribute("r"));
            }
            else if(name == "polyline")
            {
                string p = child->Attribute("points");
                replace(p.begin(),p.end(), ',', ' ');
                istringstream in (p);
                vector<Point> vector_p;
                int n,v;
                while (in>>n>>v)
                {
                    vector_p.push_back({n,v});
                }
                element = new Polyline(vector_p,parse_color(child->Attribute("stroke")));
            }
            else if(name == "line")
            {
                element = new Line({child->IntAttribute("x1"),child->IntAttribute("y1")},{child->IntAttribute("x2"),child->IntAttribute("y2")},parse_color(child->Attribute("stroke")));
            }
            else if(name == "polygon")
            {   
                string p = child->Attribute("points");
                replace(p.begin(),p.end(), ',', ' ');
                istringstream in(p);
                vector<Point> vector_p;
                int n,v;
                while (in>>n>>v)
                {
                    vector_p.push_back({n,v});
                }
                element = new Polygon(vector_p,parse_color(child->Attribute("fill")));               
            }
            else if(name == "rect")
            {
                element = new Rectangle({child->IntAttribute("x"),child->IntAttribute("y")},child->IntAttribute("width"),child->IntAttribute("height"),parse_color(child->Attribute("fill")));
            }
            else if(name == "g")
            {
                element= new Group();
                dump(child, element->get_elements(), map_references);
            }
            else if(name == "use")
            {
                string ref = child->Attribute("href");
                ref = ref.substr(1);
                for (pair <string, SVGElement*> par : map_references)
                {
                    if (par.first == ref)
                    {
                        element = par.second->get_clone(); 
                    }
                }
            }
            transform_application(child, element);
            svg_elements.push_back(element);
            id_get(element, map_references, child);


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

        vector<pair<string, SVGElement*>> references;
        dump(xml_elem, svg_elements,references);
    }
}