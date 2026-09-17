#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "SCHEMA.h"
#include "DATA_TYPE.h"

class Field{
private:
    DATA_TYPE fieldType;                     //type of data from enum DATA_TYPE
    std::vector<uint8_t> fieldData;          //vector of raw unsigned bytes (binary)

public:
    //contructor for a integer field
    Field(int value) : fieldType(DATA_TYPE::INT){
        fieldData.resize(sizeof(int));
        std::memcpy(fieldData.data(), &value, sizeof(int));
    }

    // constructor for a string field
    Field(const std::string &value) : fieldType(DATA_TYPE::VARCHAR){
        fieldData.assign(value.begin(), value.end());
    }

    Field() = delete;

    //get methods
    int getInt() const {

        if (fieldType != DATA_TYPE::INT){
            throw std::runtime_error("fieldType: not an INT");
        }

        int value;
        std::memcpy(&value, fieldData.data(),sizeof(int));
        return value;
    }

    std::string getString() const {

        if (fieldType!= DATA_TYPE::VARCHAR){
            throw std::runtime_error("fieldType: not an VARCHAR");
        }

        return std::string(fieldData.begin(),fieldData.end());
    }

    DATA_TYPE getType() const {return fieldType;}
};

class Row{
private:
    std::vector<Field> row_fields;

public:
    void appendFieldToRow(Field &f){
        row_fields.push_back(f);
    }

    Field getField(unsigned int index){
        return row_fields[index];
    }

};

class Table{
private:
    Schema schema;
public:

}
