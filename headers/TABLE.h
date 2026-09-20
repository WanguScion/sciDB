#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>

#include "DATA_TYPE.h"
#include "SCHEMA.h"

using byte = std::uint8_t;

class Field{
private:
    DATA_TYPE fieldType;                     //type of data from enum DATA_TYPE
    std::vector<byte> fieldData;          //vector of raw unsigned bytes (binary)

public:
    //contructor for a integer field
    Field(int32_t value) : fieldType(DATA_TYPE::INT){
        fieldData.resize(sizeof(int32_t));
        std::memcpy(fieldData.data(), &value, sizeof(int32_t));
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
        std::memcpy(&value, fieldData.data(),sizeof(int32_t));
        return value;
    }

    std::string getString() const {

        if (fieldType!= DATA_TYPE::VARCHAR){
            throw std::runtime_error("fieldType: not an VARCHAR");
        }

        return std::string(fieldData.begin(),fieldData.end());
    }

    DATA_TYPE getType() const {
        return fieldType;
    }
};

class Row{
private:
    std::vector<Field> fields;

public:
    //constructor
    Row() = default;

    const Field& getField(size_t index) const {
        if (index >= fields.size()) {
            throw std::out_of_range("Field index out of range: " + std::to_string(index));
        }
        return fields.at(index);
    }
    size_t getRowLength() const{
        return fields.size();
    }
    void appendFieldToRow(const Field &f){
        fields.push_back(f);
    }
};

class Table{
private:
    std::vector<byte> tableName;
    Schema schema;
    std::vector<Row> rows;

public:
    //constructor
    Table(const std::string &name, Schema sc) : schema(sc){
        tableName.assign(name.begin(), name.end());
    }

    const Row validateRow(Row &r){
        //validate row acc. to schema
        // r is addendum row, newRow is schema-complaint row
        Row newRow;

        for(size_t i=0; i<r.getRowLength(); i++){
            Field f = r.getField(i);
            if(f.getType() != schema.getColumn(i).getType()){
                throw std::runtime_error("Mismatching data types, at column :" + std::to_string(i));
            }

            if(f.getType() == DATA_TYPE::INT){
                Field newField(f.getInt());
                newRow.appendFieldToRow(newField);
            }
            else if(f.getType() == DATA_TYPE::VARCHAR){
                std::string s = f.getString().substr(0, schema.getColumn(i).getSize());
                Field newField(s);
                newRow.appendFieldToRow(newField);
            }
        }

        return newRow;
    }

    void addRow(Row &r){
        rows.push_back(validateRow(r));
    }

    void deleteRow(size_t index) {
        if (index >= rows.size()) {
            throw std::out_of_range("Row index out of range: " + std::to_string(index));
        }
        rows.erase(rows.begin() + index);
    }

    void updateRow(size_t index, Row& updated_Row){
        if (index >= rows.size()) {
            throw std::out_of_range("Row index out of range: " + std::to_string(index));
        }
        rows[index] = validateRow(updated_Row);
    }

    const Row& getRow(size_t index) const{
        if (index >= rows.size()) {
            throw std::out_of_range("Row index out of range: " + std::to_string(index));
        }
        return rows.at(index);
    }

    std::string getTableName(){
        return std::string(tableName.begin(), tableName.end());
    }

    const Schema& getSchema() const{
        return schema;
    }

    size_t getRowCount() const{
        return rows.size();
    }
};
