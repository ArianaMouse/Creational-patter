#include "sql_query_builder.h"

#include <cassert>
#include <iostream>

int main() {
    {
        SqlSelectQueryBuilder qb;
        qb.AddColumn("name").AddColumn("phone");
        qb.AddFrom("students");
        qb.AddWhere("id", "42").AddWhere("name", "John");

        const std::string expected = "SELECT name, phone FROM students WHERE id=42 AND name=John;";
        assert(qb.BuildQuery() == expected);
    }

    {
        //Нет AddColumn - SELECT *.
        SqlSelectQueryBuilder qb;
        qb.AddFrom("students");
        assert(qb.BuildQuery() == "SELECT * FROM students;");
    }

    {
        //Порядок вызовов не важен; AddFrom перезаписывает таблицу.
        SqlSelectQueryBuilder qb;
        qb.AddWhere("id", "42");
        qb.AddFrom("teachers");
        qb.AddColumn("name");
        qb.AddFrom("students");
        assert(qb.BuildQuery() == "SELECT name FROM students WHERE id=42;");
    }

    std::cout << "All checks passed\n";
    return 0;
}