#ifndef DOUBLERANGEVALIDATOR_H
#define DOUBLERANGEVALIDATOR_H

#include <QDoubleValidator>

class DoubleRangeValidator : public QDoubleValidator
{
    Q_OBJECT
public:
    explicit DoubleRangeValidator(QObject *parent = nullptr);
    DoubleRangeValidator(double bottom, double top, int decimals, QObject* parent = nullptr);

    QValidator::State validate(QString& s, int& i) const override;
};

#endif // DOUBLERANGEVALIDATOR_H
