#pragma once

class Interval {
  public:
    double min, max;
    Interval();
    Interval(double min, double max);
    Interval(const Interval &a, const Interval &b);
    inline double size() const {
        return max - min;
    }

    inline bool contains(double x) const {
        return min <= x && x <= max;
    }

    inline bool surrounds(double x) const {
        return min < x && x < max;
    }

    inline double clamp(double x) const {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    inline Interval expand(double delta) const {
        return Interval(min - delta / 2, max + delta / 2);
    }

    static const Interval empty, universe;
};
