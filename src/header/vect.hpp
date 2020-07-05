#pragma once

#include <vector>
#include <numeric>
#include <cmath>

namespace vect
{

    template <typename T>
    class generic_vect : public std::vector<T>
    {
    public:
        generic_vect() : std::vector<T>(){};
        generic_vect(std::size_t n, const T &value = T()) : std::vector<T>(n, value){};
        template <typename InputIterator>
        generic_vect(InputIterator first, InputIterator last) : std::vector<T>(first, last){};
        generic_vect(const generic_vect<T> &other) : std::vector<T>(other){};

    public:
        generic_vect<T>
        operator+(const generic_vect<T> &other) const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        generic_vect<T> operator-(const generic_vect<T> &other) const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = (*this)[i] - other[i];
            }
            return result;
        }

        generic_vect<T> operator-() const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = -(*this)[i];
            }
            return result;
        }

        generic_vect<T> operator*(const generic_vect<T> &other) const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = (*this)[i] * other[i];
            }
            return result;
        }

        generic_vect<T> operator/(const generic_vect<T> &other) const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = (*this)[i] / other[i];
            }
            return result;
        }

        generic_vect<T> operator%(const generic_vect<T> &other) const
        {
            generic_vect<T> result{this->size()};
            for (std::size_t i = 0; i < this->size(); i++)
            {
                result[i] = (*this)[i] % other[i];
            }
            return result;
        }

        generic_vect<T> &operator++()
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                ++(*this)[i];
            }
            return *this;
        }

        generic_vect<T> operator++(int)
        {
            generic_vect<T> result{*this};
            ++(*this);
            return result;
        }

        generic_vect<T> &operator--()
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                --(*this)[i];
            }
            return *this;
        }

        generic_vect<T> operator--(int)
        {
            generic_vect<T> result{*this};
            --(*this);
            return result;
        }

        bool operator!=(const generic_vect<T> &other) const
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                if ((*this)[i] != other[i])
                    return true;
            }
            return false;
        }

        bool operator==(const generic_vect<T> &other) const
        {
            return !((*this) != other);
        }

        T sum() const
        {
            return std::accumulate(this->begin(), this->end(), 0);
        }

        T dot(const generic_vect<T> &other) const
        {
            return ((*this) * other).sum();
        }

        T range() const
        {
            return std::sqrt(this->dot(*this));
        }

        bool operator<(const generic_vect<T> &other) const
        {
            return this->range() < other.range();
        }

        bool operator>(const generic_vect<T> &other) const
        {
            return this->range() > other.range();
        }

        bool operator<=(const generic_vect<T> &other) const
        {
            return this->range() <= other.range();
        }

        bool operator>=(const generic_vect<T> &other) const
        {
            return this->range() >= other.range();
        }

        const generic_vect<T> &operator+=(const generic_vect<T> &other)
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                (*this)[i] += other[i];
            }
            return *this;
        }

        const generic_vect<T> &operator-=(const generic_vect<T> &other)
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                (*this)[i] -= other[i];
            }
            return *this;
        }

        const generic_vect<T> &operator*=(const generic_vect<T> &other)
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                (*this)[i] *= other[i];
            }
            return *this;
        }

        const generic_vect<T> &operator/=(const generic_vect<T> &other)
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                (*this)[i] /= other[i];
            }
            return *this;
        }

        const generic_vect<T> &operator%=(const generic_vect<T> &other)
        {
            for (std::size_t i = 0; i < this->size(); i++)
            {
                (*this)[i] %= other[i];
            }
            return *this;
        }
    };

    template <typename T>
    generic_vect<T> operator*(const T &scal, const generic_vect<T> &vect)
    {
        generic_vect<T> result{vect.size()};
        for (std::size_t i = 0; i < vect.size(); i++)
        {
            result[i] = scal * vect[i];
        }
        return result;
    }

    typedef generic_vect<double> vectd;
    typedef generic_vect<float> vectf;
    typedef generic_vect<int> vecti;

} // namespace vect