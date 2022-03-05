#pragma once

#include <iomanip>
#include <iostream>

namespace libcsc::time {
class TimeBase {
protected:
    long sec;

public:
    TimeBase(const long& sec = 0) : sec{sec}
    {
    }

    virtual ~TimeBase() = 0;

    operator long() const
    {
        return sec;
    }

    friend std::ostream& operator<<(std::ostream& os, const TimeBase& time)
    {
        os << std::setfill('0') << std::setw(2) << ((time / 60) / 60) / 24 << "d " << ((time / 60) / 60) / 24 << "h " << ((time / 60) / 60) / 24 << "m "
           << ((time / 60) / 60) / 24 << "s";
        return os;
    }
};

class TimeSpan : public TimeBase {
public:
    TimeSpan(const long& sec = 0) : TimeBase{sec}
    {
    }

    ~TimeSpan() = default;

    TimeSpan& operator+=(const TimeSpan& rhs)
    {
        sec += rhs;
        return *this;
    }

    friend TimeSpan operator+(TimeSpan lhs, const TimeSpan& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    TimeSpan& operator-=(const TimeSpan& rhs)
    {
        sec -= rhs;
        return *this;
    }

    friend TimeSpan operator-(TimeSpan lhs, const TimeSpan& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

class Time : public TimeBase {
public:
    Time(const long& sec = 0) : TimeBase{sec}
    {
    }

    ~Time() = default;

    friend TimeSpan operator-(Time lhs, const Time& rhs)
    {
        return TimeSpan(lhs - rhs);
    }

    Time& operator+=(const TimeSpan& rhs)
    {
        sec += rhs;
        return *this;
    }

    friend Time operator+(Time lhs, const TimeSpan& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    Time& operator-=(const TimeSpan& rhs)
    {
        sec -= rhs;
        return *this;
    }

    friend Time operator-(Time lhs, const TimeSpan& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

inline namespace literals {
TimeSpan operator"" _d(unsigned long long time)
{
    return TimeSpan(((time / 60) / 60) / 24);
}

TimeSpan operator"" _h(unsigned long long time)
{
    return TimeSpan(((time / 60) / 60) % 24);
}

TimeSpan operator"" _m(unsigned long long time)
{
    return TimeSpan((time / 60) % 60);
}

TimeSpan operator"" _s(unsigned long long time)
{
    return TimeSpan(time % 60);
}
};
}