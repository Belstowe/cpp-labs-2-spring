#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace libcsc::time {
class TimeBase {
protected:
    unsigned long sec;

public:
    TimeBase(const unsigned long& sec = 0) : sec{sec}
    {
    }

    virtual ~TimeBase() = default;

    operator unsigned long() const
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
    TimeSpan(const unsigned long& sec = 0) : TimeBase{sec}
    {
    }

    TimeSpan(const unsigned long& days, const unsigned long& hours, const unsigned long& minutes, const unsigned long& seconds)
        : TimeBase{((days * 24 + hours) * 60 + minutes) * 60 + seconds}
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
    Time(const unsigned long& sec = 0) : TimeBase{sec}
    {
    }

    ~Time() = default;

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
        sec -= std::min((unsigned long)(rhs), sec);
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
    const unsigned long& lhs_secs = lhs;
    const unsigned long& rhs_secs = rhs;
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