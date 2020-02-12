#include "route_builder.h"

namespace route
{

RouteBuilder::RouteBuilder(const QPoint& start, const QPoint& finish)
{
    start_  = start;
    finish_ = finish;

    nodes_counter_ = (Abs(start_.x() - finish_.x()) + 1) * (Abs(start_.y() - finish_.y()) + 1);
}

void RouteBuilder::Reset(const QPoint& start, const QPoint& finish)
{
    start_  = start;
    finish_ = finish;

    nodes_counter_ = (Abs(start_.x() - finish_.x()) + 1) * (Abs(start_.y() - finish_.y()) + 1);
}

std::vector<QPoint> RouteBuilder::Build()
{
    const auto nodes_list   = BuildNodesList();
    const auto links_matrix = BuildLinksMatrix(nodes_list);

    const auto begin_index = 0;
          auto min_index   = 0;
          auto min         = 0;
          auto distance    = std::vector<int> (nodes_list.size());
          auto visited     = std::vector<bool>(nodes_list.size());

    for (auto i = 0; i < nodes_counter_; i++)
    {
        distance[i] = max_distance_;
        visited [i] = false;
    }

    distance[begin_index] = 0;
    do
    {
        min_index = max_distance_;
        min       = max_distance_;

        for (auto i = 0; i < nodes_list.size(); i++)
        {
            if (!visited[i] && distance[i] < min)
            {
                min = distance[i];
                min_index = i;
            }
        }

        if (min_index != max_distance_)
        {
            for (auto i = 0; i < nodes_list.size(); i++)
            {
                if (links_matrix[min_index][i] > 0)
                {
                    const auto temp = min + links_matrix[min_index][i];
                    if (temp < distance[i])
                    {
                        distance[i] = temp;
                    }
                }
            }

            visited[min_index] = true;
        }

    } while (min_index < max_distance_);

    auto end_index = nodes_list.size() - 1;
    auto weight    = distance[end_index];

    auto path_points = std::vector<QPoint>();
    path_points.push_back(nodes_list[end_index]);

    while (end_index != begin_index)
    {
        for (auto i = 0; i < nodes_list.size(); i++)
        {
            if (links_matrix[end_index][i])
            {
               const auto temp_weight = weight - links_matrix[end_index][i];
               if (temp_weight == distance[i])
               {
                   weight    = temp_weight;
                   end_index = i;

                   path_points.push_back(nodes_list[i]);
               }
            }
        }
    }

    return path_points;
}

std::vector<QPoint> RouteBuilder::BuildNodesList()
{
    auto node       = start_;
    auto nodes_list = std::vector<QPoint>();
    while (nodes_list.size() < nodes_counter_)
    {
        nodes_list.push_back(node);

        auto tmp_node = node;
        while (Abs(tmp_node.x() - finish_.x()))
        {
            if (tmp_node.x() > finish_.x())
            {
                tmp_node.rx()--;
            }
            else
            {
                tmp_node.rx()++;
            }
            nodes_list.push_back(tmp_node);
        }

        if (node.y() > finish_.y())
        {
            node.ry()--;
        }
        else
        {
            node.ry()++;
        }
        
    }

    return nodes_list;
}

std::vector<std::vector<uint8_t>> RouteBuilder::BuildLinksMatrix(const std::vector<QPoint>& nodes_list)
{
    auto links_matrix  = std::vector<std::vector<uint8_t>>(nodes_counter_);
    for (auto& cols : links_matrix)
    {
        cols.resize(nodes_counter_);
    }

    for (auto i = 0; i < nodes_counter_; i++)
    {
        for (auto j = 0; j < nodes_counter_; j++)
        {
            if (i == j)
            {
                links_matrix[i][j] = 0;
            }
            else
            {
                if ((Abs(nodes_list[i].x() - nodes_list[j].x()) + Abs(nodes_list[i].y() - nodes_list[j].y())) == 1)
                {
                    links_matrix[i][j] = 1;
                }
            }
        }
    }

    return links_matrix;
}

} // path
