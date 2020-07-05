#include "../header/perceptron_multi.hpp"

#include <algorithm>
#include <fstream>

PerceptronMulti::PerceptronMulti(const unsigned int &dim, const unsigned int &n_class)
{
    init(dim, n_class);
}

void PerceptronMulti::init(const unsigned int &dim, const unsigned int &n_class)
{
    W = std::vector<vect::vectd>(n_class);
    for (vect::vectd &Wl : W)
    {
        Wl.reserve(dim);
        for (unsigned int i = 0; i < dim; i++)
        {
            Wl.emplace_back(drand48());
        }
    }
}

union W_info
{
    struct
    {
        int32_t n_class, dim;
    };

    char bytes[sizeof(int32_t) * 2];
};

void PerceptronMulti::load(const std::string &file_name)
{
    std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);
    if (file)
    {
        W.clear();
        W_info info;
        file.read(info.bytes, sizeof(W_info));

        W.reserve(info.n_class);
        for (int l = 0; l < info.n_class; l++)
        {
            W.emplace_back(info.dim);
            file.read((char *)W[l].data(), info.dim * sizeof(double));
        }
    }
}

void PerceptronMulti::save(const std::string &file_name)
{
    std::ofstream file(file_name, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    if (file && W.size() > 0)
    {
        W_info info = {(int32_t)W.size(), (int32_t)W[0].size()};
        file.write(info.bytes, sizeof(W_info));

        for (vect::vectd &Wl : W)
            file.write((char *)Wl.data(), sizeof(double) * Wl.size());
    }
}

std::vector<double> PerceptronMulti::predict(const vect::vectd &X)
{
    std::vector<double> result;
    result.reserve(W.size());

    for (unsigned int l = 0; l < W.size(); l++)
        result.push_back(exp(W[l].dot(X)));

    double sum = std::accumulate(result.begin(), result.end(), 0.);

    for (double &y : result)
        y /= sum;

    return result;
}

void PerceptronMulti::learn(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array, const double &alpha)
{
    for (unsigned int i = 0; i < Y_array.size(); i++)
    {
        std::vector<double> Y_prediction = predict(X_array[i]);
        std::vector<double> Y_one = one_array(Y_array[i]);

        for (unsigned int l = 0; l < W.size(); l++)
        {
            W[l] -= alpha * (Y_prediction[l] - Y_one[l]) * X_array[i];
        }
    }
}

std::vector<double> PerceptronMulti::one_array(const unsigned int &i)
{
    std::vector<double> result(W.size(), 0.);
    result[i] = 1;
    return result;
}

double PerceptronMulti::score(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array)
{
    double result = 0.;

    for (unsigned int i = 0; i < Y_array.size(); i++)
    {
        std::vector<double> Y_prediction = predict(X_array[i]);
        result += log(Y_prediction[Y_array[i]]);
    }

    return result / Y_array.size();
}

double PerceptronMulti::err(const std::vector<vect::vectd> &X_array, const std::vector<int> &Y_array)
{
    int result = 0;

    for (unsigned int i = 0; i < Y_array.size(); i++)
    {
        std::vector<double> Y_prediction = predict(X_array[i]);
        int max_index = std::max_element(Y_prediction.begin(), Y_prediction.end()) - Y_prediction.begin();

        if (max_index != Y_array[i])
            result++;
    }

    return (double)result / (double)Y_array.size();
}