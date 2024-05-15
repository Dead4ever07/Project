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
        // Constructor that creats a SVGelement
        SVGElement();
        // Destructor that destrois a SVGelement
        // It will only be override in the Group subclass
        virtual ~SVGElement();
        //! Draw function, it will be ouveride by every subclass
        //! @param img Image File name
        virtual void draw(PNGImage &img) const = 0;
        //! Translate function, used to translate an 
        //! element by x and y unities
        //! @param t Cordinates to translate
        virtual void translate(const Point&t) = 0;
        //! Rotate function, rotates an element with angle v, 
        //! (clockwise for a positive value and anti-clockwise
        //! for a negative value) in relation to the rotation origin
        //! @param origin Rotation Origin
        //! @param degrees Rotation degrees
        virtual void rotate(const Point &origin, int degrees) = 0;
        //! Scale function, scales an element with angle v in relation 
        //! to a scaling origin
        //! @param origin Scale Origin
        //! @param v scale factor
        virtual void scale(const Point&origin, int v) = 0;
        //! Get_clone function, clones the elements 
        //! In the Group Subclass, it clones the Group and all its inner elements
        //! @return A dynamically allocated clone of the element
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
        //! Color of the Ellipse
        Color fill_;
        //! Center Point of the Ellipse
        Point center_;
        //! x and y radius of the Ellipse
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
        void translate(const Point&t)  override;
        void rotate(const Point &origin, int degrees)  override;
        void scale(const Point&origin, int v) override;
        virtual Polyline* get_clone() override;
        

    protected:
        //! Vector of the points of the Polyline
        std::vector<Point> points_;
        //! Color of the line
        Color stroke_;

    };

    class Line : public Polyline{
    public:
        Line(const Point &first, const Point &second, const Color &stroke);
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
        //! Vector of the points of the Polygon
        std::vector<Point> points_;
        //! Color of the line
        Color fill_;
    };

    class Rectangle : public Polygon
    {
    public:
        Rectangle(const Point &point, const int &width, const int &height, const Color &fill);
    };

    class Group : public SVGElement 
    {
    public:

        Group(std::vector<SVGElement*> elements);
        ~Group();
        void draw(PNGImage &img) const override;
        void translate(const Point& t) override;
        void rotate(const Point &origin, int degrees)  override;
        void scale(const Point&origin, int v) override;
        Group* get_clone() override;
        

    protected:
        //! Vector of the elements inside the group
        std::vector<SVGElement*> children_;
    };
};
#endif

