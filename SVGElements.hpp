//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        Point radius;
    };

    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
    };


    class Polyline : public SVGElement{
    public:
        Polyline(const std::vector<Point> points, const Color stroke);
        void draw(PNGImage &img) const override;

    private:
        Color stroke_;
    };

    class Line : public Polyline{
        Line(const Point &uno, const Point &dos, const Color &stroke);
        void draw(PNGImage &img) const override;

    private:
        Point uno_;
        Point dos_;
    };


    class Polygon : public SVGElement
    {
    public:
        Polygon(const std::vector<Point> &points, const Color &fill);
        void draw(PNGImage &img) const override;

    private:
        Color fill_;
        std::vector<Point> points_;
    };

    class Rectangle : public Polygon
    {
    public:
        Rectangle(const Point &point, const int &width, const int &height, const Color &fill);
        void draw(PNGImage &img) const override;


    };
}
#endif
