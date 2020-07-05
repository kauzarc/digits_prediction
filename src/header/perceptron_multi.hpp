#pragma once

#include <string>

#include "vect.hpp"

class PerceptronMulti
{
private:
    std::vector<vect::vectd> W;

public:
    PerceptronMulti() = default;
    PerceptronMulti(const unsigned int &dim, const unsigned int &n_class);
    ~PerceptronMulti() = default;

public:
    void init(const unsigned int &dim, const unsigned int &n_class);
    void load(const std::string &file_name);
    void save(const std::string &file_name);

    std::vector<double> predict(const vect::vectd &X);
    void learn(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array, const double &alpha);
    double score(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array);
    double err(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array);

private:
    std::vector<double> one_array(const unsigned int &i);
};