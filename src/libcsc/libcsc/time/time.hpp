#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace libcsc::time {
class TimeBase {
protected:
    unsigned long long sec;

    TimeBase(const unsigned long long sec = 0) : sec{sec}
    {
    }

public:
    operator unsigned long long() const
    {
        return sec;
    }

    friend std::ostream& operator<<(std::ostream& os, const TimeBase& time)
    {
        os << std::setfill('0') << std::setw(2) << ((time / 60) / 60) / 24 << "d ";
        os << std::setfill('0') << std::setw(2) << ((time / 60) / 60) % 24 << "h ";
        os << std::setfill('0') << std::setw(2) << (time / 60) % 60 << "m ";
        os << std::setfill('0') << std::setw(2) << time % 60 << "s";
        return os;
    }
};

class TimeSpan : public TimeBase {
public:
    TimeSpan(const unsigned long long sec = 0) : TimeBase{sec}
    {
    }

    TimeSpan(const unsigned long long days, const unsigned long long hours, const unsigned long long minutes, const unsigned long long seconds)
        : TimeBase{((days * 24 + hours) * 60 + minutes) * 60 + seconds}
    {
    }

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
    Time(const unsigned long long sec = 0) : TimeBase{sec}
    {
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
        sec -= std::min((unsigned long long)(rhs), sec);
        return *this;
    }

    friend Time operator-(Time lhs, const TimeSpan& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

TimeSpan operator-(const Time& lhs, const Time& rhs)
{
    const unsigned long long lhs_secs = lhs;
    const unsigned long long rhs_secs = rhs;
    return TimeSpan((lhs_secs < rhs_secs) ? (rhs_secs - lhs_secs) : (lhs_secs - rhs_secs));
}

inline namespace literals {
TimeSpan operator"" _d(unsigned long long sec)
{
    return TimeSpan(sec * 60 * 60 * 24);
}

TimeSpan operator"" _h(unsigned long long sec)
{
    return TimeSpan(sec * 60 * 60);
}

TimeSpan operator"" _m(unsigned long long sec)
{
    return TimeSpan(sec * 60);
}

TimeSpan operator"" _s(unsigned long long sec)
{
    return TimeSpan(sec);
}
};
}