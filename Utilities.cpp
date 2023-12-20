// Name: Samaneh Hajigholam
// Seneca Student ID: 119751220
// Seneca email: shajigholam@myseneca.ca
// Date of completion: Nov 9, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"

#include <iostream>
#include <string>

namespace sdds {
    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }
    
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }
    //extracts a token from string str referred to by the first parameter.
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        //uses the delimiter to extract the next token from str starting at position next_pos.If successful, return a copy of the extracted token found (without spaces at the beginning/end), update next_pos with the position of the next token, and set more to true (false otherwise).

        if (str.at(next_pos) == m_delimiter) {
            more = false;
            throw "No Token";
        }

        size_t i = str.find_first_of(m_delimiter, next_pos);
        std::string token = str.substr(next_pos, i - next_pos);
        //sets more to true if the delimiter is found and false if the delimiter is not found
        more = (i != std::string::npos);
        next_pos = i + 1;

        //trimming leading whitespace added
        token.erase(0, token.find_first_not_of(' '));

        if (m_widthField < token.length()){
            m_widthField = token.length();
        }

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    std::string trim(const std::string& str)
    {
        const auto strStart = str.find_first_not_of(' ');
        if (strStart == std::string::npos)
            return "";
        const auto strEnd = str.find_last_not_of(' ');
        const auto strRange = strEnd - strStart + 1;

        return str.substr(strStart, strRange);
    }
}
