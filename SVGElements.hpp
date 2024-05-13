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
        //Constructor that creats a SVGelement
        SVGElement();
        //Destructor that destrois a SVGelement
        //It will only be override in the Group subclass
        virtual ~SVGElement();
        //!Draw function, it will be ouveride by every subclass
        //!@param img Image File name
        virtual void draw(PNGImage &img) const = 0;
        //!Draw
        virtual void translate(const Point&t) = 0;        
        virtual void rotate(const Point &origin, int degrees) = 0;
        virtual void scale(const Point&origin, int v) = 0;
        virtual std::vector<SVGElement*>& get_elements();
        virtual SVGElement* get_clone() = 0;


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
        void translate( const Point&t)  override;
        void rotate( const Point &origin, int degrees) override;
        void scale(const Point&origin, int v) override;
        virtual Ellipse* get_clone() override;


    protected:
        Color fill_;
        Point center_;
        Point radius_;
    };

    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
        Circle* get_clone() override;
    };


    class Polyline : public SVGElement{
    public:
        Polyline(const std::vector<Point> &points, const Color &stroke);
        void draw(PNGImage &img) const override;
        void translate(const Point&t)  override;
        void rotate(const Point &origin, int degrees)  override;
        void scale(const Point&origin, int v) override;
        virtual Polyline* get_clone() override;
        

    protected:
        std::vector<Point> points_;
        Color stroke_;

    };

    class Line : public Polyline{
    public:
        Line(const Point &first, const Point &second, const Color &stroke);
        Line* get_clone() override;

    };


    class Polygon : public SVGElement
    {
    public:
        Polygon(const std::vector<Point> &points, const Color &fill);
        void draw(PNGImage &img) const override;
        void translate(const Point&t) override;
        void rotate(const Point &origin, int degrees) override;
        void scale(const Point&origin, int v) override;
        virtual Polygon* get_clone() override;
        

    protected:
        std::vector<Point> points_;
        Color fill_;
    };

    class Rectangle : public Polygon
    {
    public:
        Rectangle(const Point &point, const int &width, const int &height, const Color &fill);
        Rectangle* get_clone() override;

    };

    class Group : public SVGElement 
    {
    public:

        Group();
        ~Group();
        std::vector<SVGElement*>& get_elements();
        void draw(PNGImage &img) const override;
        void translate(const Point& t) override;
        void rotate(const Point &origin, int degrees)  override;
        void scale(const Point&origin, int v) override;
        Group* get_clone() override;
        

    protected:
        std::vector<SVGElement*> children_;
    };
    






};
#endif

