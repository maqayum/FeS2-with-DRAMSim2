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

#ifndef StoreTrace_H
#define StoreTrace_H

#include "Global.h"
#include "Address.h"
#include "Histogram.h"

class StoreTrace {
public:
  // Constructors
  StoreTrace() { }
  explicit StoreTrace(const Address& addr);

  // Destructor
  ~StoreTrace();
  
  // Public Methods
  void store(NodeID node);
  void downgrade(NodeID node);
  int getTotal() const { return m_total_samples; } 
  static void initSummary();
  static void printSummary(ostream& out);
  static void clearSummary();

  void print(ostream& out) const;
private:
  // Private Methods

  // Private copy constructor and assignment operator
  //  StoreTrace(const StoreTrace& obj);
  //  StoreTrace& operator=(const StoreTrace& obj);

  // Class Members (s_ prefix)
  static bool s_init;
  static int64 s_total_samples; // Total number of store lifetimes of all lines
  static Histogram* s_store_count_ptr;
  static Histogram* s_store_first_to_stolen_ptr;
  static Histogram* s_store_last_to_stolen_ptr;
  static Histogram* s_store_first_to_last_ptr;
  
  // Data Members (m_ prefix)

  Address m_addr;
  NodeID m_last_writer;
  Time m_first_store;
  Time m_last_store;
  int m_stores_this_interval;

  int64 m_total_samples; // Total number of store lifetimes of this line
  Histogram m_store_count;
  Histogram m_store_first_to_stolen;
  Histogram m_store_last_to_stolen;
  Histogram m_store_first_to_last;
};

bool node_less_then_eq(const StoreTrace* n1, const StoreTrace* n2);

// Output operator declaration
ostream& operator<<(ostream& out, const StoreTrace& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const StoreTrace& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif //StoreTrace_H