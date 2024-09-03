#include "interpolator.h"

Interpolator::Interpolator(QObject *parent)
    : QObject{parent}
{}

void Interpolator::interpolateData(const QList<QPointF> &dataPoints)
{
    m_calculatedSegments = calculateCubicSplines(dataPoints);
}

double Interpolator::functionResult(double x)
{
    return evaluateSpline(m_calculatedSegments, x);
}

QVector<Interpolator::SplineSegment> Interpolator::calculateCubicSplines(const QList<QPointF> &inputDataPoints)
{
    QList<QPointF> dataPoints = inputDataPoints;
    // Сортировка точек по x
    std::sort(dataPoints.begin(), dataPoints.end(), [](const QPointF &a, const QPointF &b) {
        return a.x() < b.x();
    });
    int numberOfSegments = dataPoints.size() - 1;
    QVector<double> segmentWidths(numberOfSegments), coefficients(numberOfSegments);
    QVector<double> lDiagonal(numberOfSegments + 1), lowerDiagonal(numberOfSegments), zVector(numberOfSegments + 1);
    QVector<double> secondDerivatives(numberOfSegments + 1), linearCoefficients(numberOfSegments), cubicCoefficients(numberOfSegments);
    QVector<double> constantTerms(numberOfSegments);
    QVector<SplineSegment> splineSegments(numberOfSegments);
    // Инициализация массива ширин сегментов
    for (int i = 0; i < numberOfSegments; i++) {
        segmentWidths[i] = dataPoints[i + 1].x() - dataPoints[i].x();
    }
    // Инициализация коэффициентов для системы уравнений
    for (int i = 1; i < numberOfSegments; i++) {
        coefficients[i] = (3.0 / segmentWidths[i]) * (dataPoints[i + 1].y() - dataPoints[i].y())
                          - (3.0 / segmentWidths[i - 1]) * (dataPoints[i].y() - dataPoints[i - 1].y());
    }
    // Настройка трехдиагональной системы уравнений
    lDiagonal[0] = 1.0;
    lowerDiagonal[0] = 0.0;
    zVector[0] = 0.0;
    for (int i = 1; i < numberOfSegments; i++) {
        lDiagonal[i] = 2.0 * (dataPoints[i + 1].x() - dataPoints[i - 1].x()) - segmentWidths[i - 1] * lowerDiagonal[i - 1];
        lowerDiagonal[i] = segmentWidths[i] / lDiagonal[i];
        zVector[i] = (coefficients[i] - segmentWidths[i - 1] * zVector[i - 1]) / lDiagonal[i];
    }
    lDiagonal[numberOfSegments] = 1.0;
    zVector[numberOfSegments] = 0.0;
    secondDerivatives[numberOfSegments] = 0.0;
    // Обратный ход для нахождения вторых производных и коэффициентов сплайна
    for (int j = numberOfSegments - 1; j >= 0; j--) {
        secondDerivatives[j] = zVector[j] - lowerDiagonal[j] * secondDerivatives[j + 1];
        linearCoefficients[j] = (dataPoints[j + 1].y() - dataPoints[j].y()) / segmentWidths[j]
                                - segmentWidths[j] * (secondDerivatives[j + 1] + 2 * secondDerivatives[j]) / 3.0;
        cubicCoefficients[j] = (secondDerivatives[j + 1] - secondDerivatives[j]) / (3.0 * segmentWidths[j]);
        constantTerms[j] = dataPoints[j].y();
    }
    // Сохранение коэффициентов в структуру
    for (int i = 0; i < numberOfSegments; ++i) {
        splineSegments[i] = {constantTerms[i], linearCoefficients[i], secondDerivatives[i], cubicCoefficients[i], dataPoints[i].x()};
    }
    return splineSegments;
}

double Interpolator::evaluateSpline(const QVector<SplineSegment> &splineSegments, double x)
{
    for (int i = 0; i < splineSegments.size(); i++) {
        const auto &segment = splineSegments[i];
        // Проверяем, находится ли x в пределах текущего сегмента
        double nextX = (i == splineSegments.size() - 1) ? std::numeric_limits<double>::max() : splineSegments[i + 1].startX;
        if (x >= segment.startX && x < nextX) {
            // Вычисление y на основе кубической функции сплайна
            double deltaX = x - segment.startX;
            return segment.valueAtStart
                   + segment.firstDerivative * deltaX
                   + segment.secondDerivative * pow(deltaX, 2)
                   + segment.thirdDerivative * pow(deltaX, 3);
        }
    }
    // Возвращаем NaN, если x не попадает ни в один из сегментов
    return std::numeric_limits<double>::quiet_NaN(); // Не найдено подходящего сегмента
}
