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
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
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
        for (size_t i = 0; i < len-1; i++) {
            img.draw_line(points_[i], points_[i+1], stroke_);
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

    Rectangle::Rectangle(const svg::Point &point,
                         const int &width,
                         const int &height,
                         const svg::Color &fill)
         : Polygon(std::vector<Point> {point, {point.x + width-1, point.y}, {point.x + width-1, point.y + height-1}, {point.x, point.y + height-1}}, fill)
    {
    }
}


