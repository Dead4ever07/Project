
# Programming project

## Group elements

Identify all group elements (numbers and names).

- up202306822 Lara da Silva Moreira
- up202306823 Luís Miguel Rosa Santos
- up202306905 Vasco Costa Lemos


## Accomplished tasks

Brief summary of what you implemented.

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
