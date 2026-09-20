#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "DATA_TYPE.h"

#define INT_FIELD_SIZE 4

using byte = std::uint8_t;

class ColumnMetadata{
private:
    DATA_TYPE columnType;
    std::vector<byte> columnName;
    byte columnSize;     //max size = 255bytes

public:
    // constructor for Int field
    ColumnMetadata(DATA_TYPE type, const std::string &name) : columnType(type), columnSize(INT_FIELD_SIZE){
        if(type != DATA_TYPE::INT){
            throw std::runtime_error("Not provided {Size of Column} for column of non-default size!");
        }

        columnName.assign(name.begin(), name.end());
    }
    // constructor for Varchar (sized) field
    ColumnMetadata(DATA_TYPE type, const std::string &name, byte size) : columnType(type), columnSize(size){
        if(type == DATA_TYPE::INT){
            columnSize = INT_FIELD_SIZE;
        }

        columnName.assign(name.begin(), name.end());
    }

    ColumnMetadata() = delete;

    //gets
    DATA_TYPE getType() const {
        return columnType;
    }

    std::string getName() const{
        return std::string(columnName.begin(), columnName.end());
    }

    byte getSize() const{
        return columnSize;
    }
};


class Schema {
private:
    std::vector<ColumnMetadata> columns;

public:
    Schema(std::initializer_list<ColumnMetadata> cols) : columns(cols) {}
    Schema() = default;

    size_t getColumnCount() const {
        return columns.size();
    }

    const ColumnMetadata& getColumn(size_t index) const {
        if (index >= columns.size()) {
            throw std::out_of_range("Column index out of range: " + std::to_string(index));
        }
        return columns.at(index);
    }

    void addColumn(const ColumnMetadata& column) {
        columns.push_back(column);
    }
};
