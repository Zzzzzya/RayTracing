#include "Interval.hpp"
#include "Head.hpp"

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

Interval::Interval() : min(-infinity), max(infinity) {
}
Interval::Interval(double min, double max) : min(min), max(max) {
}
Interval::Interval(const Interval &a, const Interval &b) {
    min = std::min(a.min, b.min);
    max = std::max(a.max, b.max);
}

Interval operator+(const Interval &ival, double displacement) {
    return Interval(ival.min + displacement, ival.max + displacement);
}

Interval operator+(double displacement, const Interval &ival) {
    return ival + displacement;
}
