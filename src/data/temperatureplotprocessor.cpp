#include "temperatureplotprocessor.h"

#include "lsa_approximator.h"
#include "psr_polynomial.h"


QList<QList<double>> TemperaturePlotProcessor::approximatedData(
    const QList<double> &keys,
    const QList<double> &values,
    std::size_t order
) const
{
    const auto coeffs = lsa::Approximator().polynomial(keys, values, order);
    auto [resultKeys, resultValues] = psr::Polynomial<double>{keys.front(), keys.back()}(1024, coeffs);

    return { coeffs, resultKeys, resultValues };
}
