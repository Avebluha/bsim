#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QObject>
#include <QPointF>

class Interpolator : public QObject
{
    Q_OBJECT

    struct SplineSegment {
        double valueAtStart, firstDerivative, secondDerivative, thirdDerivative, startX;
    };

public:
    explicit Interpolator(QObject *parent = nullptr);

    void interpolateData(const QList<QPointF> &dataPoints);
    double functionResult(double x);
    QList<QPointF> interpolatedData() const;

private:
    QVector<SplineSegment> m_calculatedSegments;

    QVector<SplineSegment> calculateCubicSplines(const QList<QPointF> &dataPoints);
    double evaluateSpline(const QVector<SplineSegment> &splineSegments, double x);
};

#endif // INTERPOLATOR_H
