#include "sql_query_builder.h"

#include <sstream>

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& name) {
    columns_.push_back(name);
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
    table_ = table;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& field,
    const std::string& value) {
    where_.emplace_back(field, value);
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::ostringstream query;
    query << "SELECT ";

    if (columns_.empty()) {
        query << "*";
    }
    else {
        for (std::size_t i = 0; i < columns_.size(); ++i) {
            if (i != 0) {
                query << ", ";
            }
            query << columns_[i];
        }
    }

    query << " FROM " << table_;

    if (!where_.empty()) {
        query << " WHERE ";
        for (std::size_t i = 0; i < where_.size(); ++i) {
            if (i != 0) {
                query << " AND ";
            }
            query << where_[i].first << "=" << where_[i].second;
        }
    }

    query << ";";
    return query.str();
}