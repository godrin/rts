/* 
 * File:   agdecryptor.h
 * Author: davidkamphausen
 *
 * Created on 24. Februar 2009, 05:47
 */

#ifndef _AGDECRYPTOR_H
#define _AGDECRYPTOR_H

#include "rk_base.h"

#include <string>

/**
   AGDecryptor provides functionaliy for DRM-plugged images and music-files.
   You have to derive from this class and give an instance when loading a surface.
   When you have done so saving is disabled afterwards.
 */
class AGEXPORT AGDecryptor {
public:
  AGDecryptor();
  AGDecryptor(const AGDecryptor& orig);
  virtual ~AGDecryptor();

  virtual std::string decrypt(const std::string &s, const std::string &n);

private:

};

#endif /* _AGDECRYPTOR_H */

