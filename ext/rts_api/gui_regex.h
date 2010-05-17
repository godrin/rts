/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_regex.h
 * by David Kamphausen (david.kamphausen@web.de)
 *
 * The "Antargis" project, including all files needed to compile it,
 * is free software; you can redistribute it and/or use it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.
 */

#ifndef AG_REGEX_H
#define AG_REGEX_H


#ifdef UNDEF

#include <regex.h>
#include <sys/types.h>
#include <string>

// uses extended regex's
class AGEXPORT RegEx
{
  regex_t matcher;
public:
  RegEx(const std::string &s, bool newline=false)
    {
      int flags=REG_EXTENDED;//|REG_NOSUB;
      if(newline)
        flags|=REG_NEWLINE;
      int ret=regcomp(&matcher,s.c_str(),flags);
      switch(ret)
      {
      case REG_BADPAT:
        err("A regular expression was invalid.");break;
      case REG_ECOLLATE:
        err("An invalid collating element was referenced.");break;
      case REG_ECTYPE:
        err("An invalid character class type was referenced.");break;
      case REG_EESCAPE:
        err("A trailing \\ was in the pattern.");break;
      case REG_ESUBREG:
        err("A number in \\digit was invalid or in error.");break;
      case REG_EBRACK:
        err("A [ ] imbalance exists");break;
      case REG_ENOSYS:
        err("The function is not supported.");break;
      case REG_EPAREN:
        err("A \\( \\) or ( ) imbalance exists.");break;
      case REG_EBRACE:
        err("A \\{ \\} imbalance exists.");break;
      case REG_BADBR:
        err("The contents of \\{ \\} are invalid: not a number, number too large, more than two numbers, first larger than second.");break;
      case REG_ERANGE:
        err("An endpoint in a range expression is invalid.");break;
      case REG_ESPACE:
        err("Out of memory.");break;
      case REG_BADRPT:
        err("?, * or + is not preceded by valid regular expression.");break;
      }
    }
  ~RegEx()
    {
      regfree(&matcher);
    }
  void err(const std::string &s)
    {
      std::cout<<"An error occured:"<<s<<std::endl;
    }
  bool matchFirst(const std::string &s)
    {
      regmatch_t pmatch[1];
      int ret=regexec(&matcher, s.c_str(), 0, pmatch,0);// REG_NOTBOL);
      return ret==0;
    }
  int first(const std::string &s)
    {
      regmatch_t pmatch[3];
      int ret=regexec(&matcher, s.c_str(), 3, pmatch,0);
      if(ret==0)
        return pmatch[0].rm_so;
      return -1;
    }
  std::pair<int,int> firstMatch(const std::string &s)
  {
    regmatch_t pmatch[3];
    int ret=regexec(&matcher, s.c_str(), 3, pmatch,0);
    if(ret==0)
      return std::make_pair(pmatch[0].rm_so,pmatch[0].rm_eo);
    return std::make_pair(-1,-1);
  }

};


#endif

#endif
