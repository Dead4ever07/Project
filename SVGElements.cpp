#include "SVGElements.hpp"

namespace svg
{
    SVGElement::SVGElement()
    = default;
    SVGElement::~SVGElement() 
    = default;

    std::vector<SVGElement*>& SVGElement::get_elements()
    {
        std::vector<SVGElement*> v;
        std::vector<SVGElement*>&  a = v;
        return a;
    }

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        :fill_(fill), center_(center), radius_(radius) 
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center_, radius_, fill_);
    }
    void Ellipse::translate(const Point&t)
    {
        center_ = this->center_.translate(t);
        
    }
    void Ellipse::rotate(const Point &origin, int degrees) 
    {
        center_ = this->center_.rotate(origin,degrees);
    }
    void Ellipse::scale(const Point&origin, int v) 
    {
        center_ = this->center_.scale(origin,v);
        radius_ = this->radius_.scale({0,0},v);
    }
    Ellipse* Ellipse::get_clone()
    {
        Ellipse* ellipse_clone = new Ellipse(this->fill_, this->center_, this->radius_) ;
        return ellipse_clone;
    }


    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius
                   )
        :Ellipse(fill,center, {radius,radius}){}

    Circle* Circle::get_clone()
    {
        Circle* clone_circle = new Circle(this->fill_,this->center_,this->radius_.x);
        return clone_circle;
    }

    Polyline::Polyline(const std::vector<Point> &points,
                       const Color &stroke )
       : points_(points), stroke_(stroke)
    {
    }
    void Polyline::draw(PNGImage &img) const
    {
        size_t len = points_.size();
        for (size_t i = 0; i < len-1; i++) 
        {
            img.draw_line(points_[i], points_[i+1], stroke_);
        }
    }

    void Polyline::translate( const Point&t)
    {
        for(Point& p:this->points_)
        {
            p = p.translate(t);
        }
    }
    void Polyline::rotate( const Point &origin, int degrees)
    {
        for(Point& p:this->points_)
        {
            p = p.rotate(origin,degrees);
        }
    }
    void Polyline::scale(const Point&origin, int v) 
    {
        for(Point& p:this->points_)
        {
            p = p.scale(origin,v);
        }
    }
    Polyline* Polyline::get_clone()
    {
        Polyline* clone_polyline = new Polyline(this->points_,this->stroke_);
        return clone_polyline;
    }



    Line::Line(const svg::Point &first,
               const svg::Point &second,
               const svg::Color &stroke)
       : Polyline(std::vector<Point> {first, second}, stroke)
    {
    }

    Line* Line::get_clone()
    {
        Line *clone_line = new Line(this->points_[0],this->points_[1],this->stroke_);
        return clone_line;
    }

    Polygon::Polygon(const std::vector<Point> &points,
                     const svg::Color &fill)
         :points_(points), fill_(fill)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points_, fill_);
    }
    void Polygon::translate(const Point&t)
    {
        for(Point& p:this->points_)
        {
            p = p.translate(t);
        }
    }
    void Polygon::rotate(const Point &origin, int degrees)
    {
        for(Point& p:this->points_)
        {
            p = p.rotate(origin,degrees);
        }
    }
    void Polygon::scale(const Point&origin, int v) 
    {
        for(Point& p:this->points_)
        {
            p = p.scale(origin,v);
        }
    }

    Polygon* Polygon::get_clone()
    {
        Polygon* clone_polygon = new Polygon(this->points_, this->fill_);
        return clone_polygon;
    }



    Rectangle::Rectangle(const svg::Point &point,
                         const int &width,
                         const int &height,
                         const svg::Color &fill)
         : Polygon(std::vector<Point> {point, {point.x + width-1, point.y}, {point.x + width-1, point.y + height-1}, {point.x, point.y + height-1}}, fill) {}
    
    Rectangle* Rectangle::get_clone()
    {
        Rectangle* clone_rectangle = new Rectangle(this->points_[0], this->points_[2].x-this->points_[0].x+1,this->points_[2].y-this->points_[0].y+1, this->fill_);
        return clone_rectangle;
    }
    
    Group::Group()= default;



    Group::~Group()
    {
        for (SVGElement* child : this->children_)
        {
            delete child;
        }
    }
    
    std::vector<SVGElement*>& Group::get_elements()
    {
        return children_;
    }

    void Group::draw(PNGImage &img) const 
    {
        for(SVGElement* child : this->children_ )
        {
            child->draw(img);
           
        }
    }

    void Group::translate(const Point& t)
    {
        for(SVGElement* child : this->children_ )
        {
            child->translate(t);
        }
    }
    void Group::rotate(const Point &origin, int degrees) 
    {
        for(SVGElement* child : this->children_ )
        {
            child->rotate(origin, degrees);
        }
    }
    void Group::scale(const Point&origin, int v) 
    {
        for(SVGElement* child : this->children_ )
        {
            child->scale(origin, v);
        }
    }

    Group* Group::get_clone()
    {

        Group* clone_group = new Group();
        for(SVGElement* c : this->children_){
            clone_group->get_elements().push_back(c->get_clone());
        }
        return clone_group;
    }

}


