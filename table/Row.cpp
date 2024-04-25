
#include "Row.h"

Row::Row(const vector<string> &data) : data(data) {}

const vector<string> &Row::getData() const {
    return data;
}

void Row::setData(const vector<string> &data) {
    Row::data = data;
}
