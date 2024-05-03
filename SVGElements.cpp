#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill_(fill), center_(center), radius_(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center_, radius_, fill_);
    }
    void Ellipse::translate(const Point &center,const Point&t) const
    {
        center.translate(t);
    }
    void Ellipse::rotate(const Point &center, const Point &origin, int degrees) const
    {
        center.rotate(origin,degrees);
    }
    void Ellipse::scale(const Point &center, const Point&origin, int v) const 
    {
        center.scale(origin,v);
    }


    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius)
        :Ellipse(fill,center, {radius,radius}){};

    Polyline::Polyline(const std::vector<Point> &points,
                       const Color &stroke)
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

    void Polyline::translate(const std::vector<Point> &points, const Point&t) const
    {
        for(Point p:points)
        {
            p.translate(t);
        }
    }
    void Polyline::rotate(const std::vector<Point> &points, const Point &origin, int degrees) const
    {
        for(Point p:points)
        {
            p.rotate(origin,degrees);
        }
    }
    void Polyline::scale(const std::vector<Point> &points, const Point&origin, int v) const
    {
        for(Point p:points)
        {
            p.scale(origin,v);
        }
    }



    Line::Line(const svg::Point &first,
               const svg::Point &second,
               const svg::Color &stroke)
       : Polyline(std::vector<Point> {first, second}, stroke)
    {
    }

    Polygon::Polygon(const std::vector<Point> &points,
                     const svg::Color &fill)
         : points_(points), fill_(fill)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points_, fill_);
    }
        void Polygon::translate(const std::vector<Point> &points, const Point&t) const
    {
        for(Point p:points)
        {
            p.translate(t);
        }
    }
    void Polygon::rotate(const std::vector<Point> &points, const Point &origin, int degrees) const
    {
        for(Point p:points)
        {
            p.rotate(origin,degrees);
        }
    }
    void Polygon::scale(const std::vector<Point> &points, const Point&origin, int v) const
    {
        for(Point p:points)
        {
            p.scale(origin,v);
        }
    }



    Rectangle::Rectangle(const svg::Point &point,
                         const int &width,
                         const int &height,
                         const svg::Color &fill)
         : Polygon(std::vector<Point> {point, {point.x + width-1, point.y}, {point.x + width-1, point.y + height-1}, {point.x, point.y + height-1}}, fill)
    {
    }
}


