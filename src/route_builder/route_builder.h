#pragma once

#include <QPoint>
#include <vector>

namespace route
{

class RouteBuilder
{
public:
    explicit RouteBuilder(const QPoint& start = QPoint(0, 0), const QPoint& finish = QPoint(0, 0));
    ~RouteBuilder() = default;

    std::vector<QPoint> Build();
    void Reset(const QPoint& start, const QPoint& finish);

private:
    const int max_distance_{10000};
          int nodes_counter_;

    QPoint start_;
    QPoint finish_;

    std::vector<QPoint> BuildNodesList();
    std::vector<std::vector<uint8_t>> BuildLinksMatrix(const std::vector<QPoint>& nodes_list);

    template <typename T>
    T Abs(const T& val)
    {
        if (val < 0)
        {
            return -val;
        }

        return val;
    }
};

} // route
