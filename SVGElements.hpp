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
        virtual void translate(const Point &center, const Point&t) const = 0;
        virtual void translate(const std::vector<Point> &points, const Point&t) const = 0;        
        virtual void rotate(const Point &center, const Point &origin, int degrees) const = 0;
        virtual void rotate(const std::vector<Point> &points, const Point &origin, int degrees) const = 0;
        virtual void scale(const Point &center, const Point&origin, int v) const = 0;
        virtual void scale(const std::vector<Point> &points, const Point&origin, int v) const = 0;

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
        void translate(const Point &center, const Point&t) const override;
        void rotate(const Point &center, const Point &origin, int degrees) const override;
        void scale(const Point &center, const Point&origin, int v) const override;

    private:
        Color fill_;
        Point center_;
        Point radius_;
    };

    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
    };


    class Polyline : public SVGElement{
    public:
        Polyline(const std::vector<Point> &points, const Color &stroke);
        void draw(PNGImage &img) const override;
        void translate(const std::vector<Point> &points, const Point&t) const override;
        void rotate(const std::vector<Point> &points, const Point &origin, int degrees) const override;
        void scale(const std::vector<Point> &points, const Point&origin, int v) const override;

    private:
        std::vector<Point> points_;
        Color stroke_;

        void draw(PNGImage &img);
    };

    class Line : public Polyline{
    public:
        Line(const Point &first, const Point &second, const Color &stroke);


    private:
        Point First_;
        Point Second_;
    };


    class Polygon : public SVGElement
    {
    public:
        Polygon(const std::vector<Point> &points, const Color &fill);
        void draw(PNGImage &img) const override;
        void translate(const std::vector<Point> &points, const Point&t) const override;
        void rotate(const std::vector<Point> &points, const Point &origin, int degrees) const override;
        void scale(const std::vector<Point> &points, const Point&origin, int v) const override;

    private:
        std::vector<Point> points_;
        Color fill_;
    };

    class Rectangle : public Polygon
    {
    public:
        Rectangle(const Point &point, const int &width, const int &height, const Color &fill);

    };
}
#endif

