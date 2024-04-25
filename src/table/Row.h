
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_ROW_H
#define ELEMENTAL_SQL_IMPLEMENTATION_ROW_H

#include <vector>
#include <string>

using namespace std;

class Row {
    vector<string> data;

public:
    Row(const vector<string> &data);

    const vector<string> &getData() const;

    void setData(const vector<string> &data);

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_ROW_H
