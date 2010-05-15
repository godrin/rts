/* 
 * File:   agdecryptor.cpp
 * Author: davidkamphausen
 * 
 * Created on 24. Februar 2009, 05:47
 */

#include "ag_decryptor.h"

#include <string>

AGDecryptor::AGDecryptor() {
}

AGDecryptor::AGDecryptor(const AGDecryptor& orig) {
}

AGDecryptor::~AGDecryptor() {
}

std::string AGDecryptor::decrypt(const std::string &s, const std::string &n)
{
    return s;
}
