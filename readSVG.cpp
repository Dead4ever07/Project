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
    //! Function that applies the transformations of the element passed
    //! @param elem Element where the attributes are located
    //! @param objecto SVGElement where the transformations will be applied
    void transform_aplication(const XMLElement* elem, SVGElement* objecto)
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
    
    //! By checking the presence of the id attribute, it creates a pair with the id and the respective SVGelement
    //! and adds it to the vector creating a map of all element with an id.
    //! @param elemento SVGelement that is going to be mapped
    //! @param map_references vector of pairs where the elements are going to be stored
    //! @param child XMLElement were the id attribute is going to be extracted
    void id_get(SVGElement * elemento,vector<pair<string, SVGElement*>>& map_references, const XMLElement* child)
    {
        if(child->Attribute("id"))
        {    
            map_references.push_back({child->Attribute("id"), elemento});
        }
    }

    //! Function that iterates through the elements that are children of the parameter elem
    //! In the case that the element is a group and it has children, the function
    //! will recursively pass to the children of the group element.
    //! For each element there will be created a dynamically allocated variable 
    //! and according to its name it will call a function in the the class SVGElement.
    //! Then, the function transform_aplication will be called and the element will be 
    //! tranformed as needed.
    //! Afterwards, the dynamically allocated variable will be added to the vector svg_elements
    //! to be later deleted.
    //! Lastly, the function id_get will be called to check if element has and id attribute.
    //! @param elem Pointer to the XMLElement whose children are currently being 
    //! analysed by the function
    //! @param svg_elements Vector where the pointers to the SVGElements being analysed 
    //! are being stored
    //! @param map_references Vector with pairs which will store only the SVGElements
    //! that have an identity, and their respective id 
    void SVGread_recursive(XMLElement *elem, vector<SVGElement *>& svg_elements, vector<pair<string, SVGElement*>>& map_references)
    {
        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        { 
            string name = child->Name();
            SVGElement* element;
            if( name == "ellipse")
            {
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
                int x,y;
                while (in>>x>>y)
                {
                    vector_p.push_back({x,y});
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
                int x,y;
                while (in>>x>>y)
                {
                    vector_p.push_back({x,y});
                }
                element = new Polygon(vector_p,parse_color(child->Attribute("fill")));               
            }
            else if(name == "rect")
            {
                element = new Rectangle({child->IntAttribute("x"),child->IntAttribute("y")},child->IntAttribute("width"),child->IntAttribute("height"),parse_color(child->Attribute("fill")));
            }
            else if(name == "g")
            {
                vector<SVGElement*> children;
                SVGread_recursive(child, children, map_references);
                element= new Group(children);
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
            transform_aplication(child, element);
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
        SVGread_recursive(xml_elem, svg_elements,references);
    }
}