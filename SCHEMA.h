#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include "DATA_TYPE.h"

#ifndef INT_FIELD_SIZE
#define INT_FIELD_SIZE 4

class ColumnMetadata{
private:
    DATA_TYPE columnType;
    std::vector<uint8_t> columnName;
    uint8_t columnSize;     //max size = 255bytes

public:
    // constructor
    ColumnMetadata(DATA_TYPE type, const std::string &name) : columnType(type), columnSize(INT_FIELD_SIZE){
        if(type != DATA_TYPE::INT){
            throw std::runtime_error("Not provided {Size of Column} for column of non-default size!");
        }

        columnName.assign(name.begin(), name.end());
    }
    ColumnMetadata(DATA_TYPE type, const std::string &name, uint8_t size) : columnType(type), columnSize(size){
        if(type == DATA_TYPE::INT){
            columnSize = INT_FIELD_SIZE;
        }

        columnName.assign(name.begin(), name.end());
    }

    ColumnMetadata() = delete;

    //gets
    DATA_TYPE getType() const {return columnType;}

    std::string getName() const{
        return std::string(columnName.begin(), columnName.end());
    }

    uint8_t getSize() const{
        return columnSize;
    }
};

class Schema{
private:
    std::vector<ColumnMetadata> columns;
public:

};

#endif
