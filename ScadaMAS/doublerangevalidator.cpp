#include "doublerangevalidator.h"

DoubleRangeValidator::DoubleRangeValidator(QObject *parent)
    : QDoubleValidator{parent}
{}

DoubleRangeValidator::DoubleRangeValidator(double bottom, double top, int decimals, QObject* parent)
    : QDoubleValidator(bottom, top, decimals, parent)
{}

QValidator::State DoubleRangeValidator::validate(QString& s, int& i) const
{
    if(s.isEmpty() || s == "-"){
        return QValidator::Intermediate;
    }
    QString decimalPoint = locale().decimalPoint();

    if(s.indexOf(decimalPoint) != -1) {
        int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

        if (charsAfterPoint > decimals()) {
            return QValidator::Invalid;
        }
    }

    bool ok;
    double d = locale().toDouble(s, &ok);

    if (ok && d >= bottom() && d <= top()) {
        return QValidator::Acceptable;
    } else {
        return QValidator::Invalid;
    }
}
