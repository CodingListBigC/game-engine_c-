#ifndef READ_JSON_H
#define READ_JSON_H

#include <fstream>
#include <iostream>    // Added for error logging
#include <json/json.h> // Changed from <jsoncpp/json/json.h>
#include <string>

inline Json::Value getJsonData(std::string file_path) {
  std::ifstream file(file_path, std::ifstream::binary);

  Json::Value data;

  // Check if the file exists and opened correctly
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << file_path << std::endl;
    return data; // Returns a null Json::Value
  }

  Json::CharReaderBuilder readerBuilder;
  std::string errs;

  // Parse the stream
  if (!Json::parseFromStream(readerBuilder, file, &data, &errs)) {
    std::cerr << "Json Parsing Error: " << errs << std::endl;
  }

  file.close();
  return data;
}

#endif // READ_JSON_H
