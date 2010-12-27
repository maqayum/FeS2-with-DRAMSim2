/* This file is part of the Ruby Multiprocessor Memory System
   Simulator, a component of the Multifacet GEMS (General
   Execution-driven Multiprocessor Simulator) software toolset
   originally developed at the University of Wisconsin-Madison.

   Ruby was originally developed primarily by Milo Martin and Daniel
   Sorin with contributions from Ross Dickson, Carl Mauer, and Manoj
   Plakal.

   Substantial further development of Multifacet GEMS at the
   University of Wisconsin was performed by Alaa Alameldeen, Brad
   Beckmann, Ross Dickson, Pacia Harper, Milo Martin, Michael Marty,
   Carl Mauer, Kevin Moore, Manoj Plakal, Daniel Sorin, Min Xu, and
   Luke Yen.

   Additional development was performed at the University of
   Pennsylvania by Milo Martin.

   --------------------------------------------------------------------

   Copyright (C) 1999-2005 by Mark D. Hill and David A. Wood for the
   Wisconsin Multifacet Project.  Contact: gems@cs.wisc.edu
   http://www.cs.wisc.edu/gems/

   This file is based upon a pre-release version of Multifacet GEMS
   from 2004 and may also contain additional modifications and code
   Copyright (C) 2004-2007 by Milo Martin for the Penn Architecture
   and Compilers Group.  Contact: acg@lists.seas.upenn.edu
   http://www.cis.upenn.edu/acg/

   --------------------------------------------------------------------

   Multifacet GEMS is free software; you can redistribute it and/or
   modify it under the terms of version 2 of the GNU General Public
   License as published by the Free Software Foundation.  This 
   software comes with ABSOLUTELY NO WARRANTY.  For details see the 
   file LICENSE included with the distribution.
*/
// -----------------------------------------------------------------------------
//
//  This file is part of FeS2.
//
//  FeS2 is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  FeS2 is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with FeS2.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------

#ifndef CACHEPROFILER_H
#define CACHEPROFILER_H

#include "Global.h"
#include "NodeID.h"
#include "Histogram.h"
#include "AccessModeType.h"
#include "PrefetchBit.h"
#include "CacheRequestType.h"

template <class KEY_TYPE, class VALUE_TYPE> class Map;

class CacheProfiler {
public:
  // Constructors
  CacheProfiler(const string& description);

  // Destructor
  ~CacheProfiler();  
  
  // Public Methods
  void printStats(ostream& out) const;
  void clearStats();

  void addStatSample(CacheRequestType request_type, AccessModeType type, int msgSize, PrefetchBit pfBit);

  void print(ostream& out) const;
private:
  // Private Methods

  // Private copy constructor and assignment operator
  CacheProfiler(const CacheProfiler& obj);
  CacheProfiler& operator=(const CacheProfiler& obj);
  
  // Data Members (m_ prefix)
  string m_description;
  Histogram m_requestSize;
  int64 m_misses;
  int64 m_prefetches;
  Vector<int64> m_accessModeType_vec;
  Vector<int64> m_requestType_vec;
};

// Output operator declaration
ostream& operator<<(ostream& out, const CacheProfiler& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const CacheProfiler& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif //CACHEPROFILER_H
