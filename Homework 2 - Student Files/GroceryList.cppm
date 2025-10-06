module;                                                                                             // Global fragment (not part of the module)
  // Empty




/***********************************************************************************************************************************
**  Module GroceryList Interface
**
***********************************************************************************************************************************/
export module GroceryList;                                                                          // Primary Module Interface Definition
import std;
import GroceryItem;


export
{
  class GroceryList
  {
    friend std::ostream & operator<<( std::ostream & stream, GroceryList const & groceryList );
    friend std::istream & operator>>( std::istream & stream, GroceryList       & groceryList );
    friend struct std::formatter<GroceryList>;

    public:
      // Types and Exceptions
      enum class Position {TOP, BOTTOM};

      struct GroceryList_Ex : std::logic_error                                                      // Abstract class forming the base of all errors detected by GroceryItem
      {                                                                                             // Captures errors that are a consequence of faulty logic within GroceryList
        GroceryList_Ex( const std::string_view message, std::source_location location = std::source_location::current() );
       ~GroceryList_Ex() override = 0;
      };
      struct InvalidInternalState_Ex : GroceryList_Ex { using GroceryList_Ex::GroceryList_Ex; };    // Thrown if internal data structures become inconsistent with each other
      struct CapacityExceeded_Ex     : GroceryList_Ex { using GroceryList_Ex::GroceryList_Ex; };    // Thrown if more grocery items are inserted than will fit
      struct InvalidOffset_Ex        : GroceryList_Ex { using GroceryList_Ex::GroceryList_Ex; };    // Thrown if inserting beyond current size



      // Constructors, destructor, and assignments
      //
      // The compiler synthesized copy and move constructors, and copy and move assignment operators work just fine.  But since I also
      // have user defined constructors, I need to explicitly say the compiler synthesized default constructor is also okay.
      GroceryList() = default;                                                                      // constructs an empty grocery list
      GroceryList( std::initializer_list<GroceryItem> const & initList );                           // constructs a grocery list from a braced list of grocery items


      // Queries
      std::size_t size() const;                                                                     // returns the number of grocery items in this grocery list


      // Accessors
      std::size_t find( const GroceryItem & groceryItem ) const;                                    // returns the grocery item's (zero-based) offset from top, size() if grocery item not found


      // Modifiers
      void insert   ( GroceryItem const & groceryItem, Position    position = Position::TOP );      // inserts the grocery item at the top (beginning) or bottom (end) of the grocery list
      void insert   ( GroceryItem const & groceryItem, std::size_t offsetFromTop            );      // inserts before the existing grocery item currently at that offset

      void remove   ( GroceryItem const & groceryItem                                       );      // no change occurs if grocery item not found
      void remove   ( std::size_t         offsetFromTop                                     );      // no change occurs if (zero-based) offsetFromTop >= size()

      void moveToTop( GroceryItem const & groceryItem                                       );      // finds then moves grocery item from its current position to the top of the grocery list

      GroceryList & operator+=( std::initializer_list<GroceryItem> const & rhs );                   // appends (aka concatenates) a braced list of grocery items to the end of this list
      GroceryList & operator+=( GroceryList                        const & rhs );                   // appends (aka concatenates) the rhs list to the bottom of this list


      // Relational Operators
      std::weak_ordering operator<=>( GroceryList const & rhs ) const;
      bool               operator== ( GroceryList const & rhs ) const;


    private:
      // Instance Attributes
      std::array       <GroceryItem, 11>  _gList_array;                                             // underlying containers holding grocery items
      std::vector      <GroceryItem    >  _gList_vector;                                            // operations performed on once container must be
      std::list        <GroceryItem    >  _gList_dll;                                               // replicated across all containers
      std::forward_list<GroceryItem    >  _gList_sll;

      std::size_t                         _gList_array_size = 0;                                    // number of valid elements in _gList_array


      // Helper member functions
      bool        containersAreConsistant() const;
      std::size_t gList_sll_size         () const;                                                  // std::forward_list doesn't maintain size, so calculate it on demand
  };


  std::ostream & operator<<( std::ostream & stream, GroceryList const & groceryList );
  std::istream & operator>>( std::istream & stream, GroceryList       & groceryList );
}    // export







// Not exported but reachable
/***********************************************************************************************************************************
** Formatting Specialization Class Definition for formatting Grocery Lists
***********************************************************************************************************************************/
template<>
struct std::formatter<GroceryList> : std::formatter<std::string>
{
  auto format( const GroceryList & groceryList, auto & ctx ) const
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// For each grocery item in the grocery list, accumulate a string by appending the current grocery item to the back of the
      /// string.  Each grocery item is appended as a new line and preceded with its index (aka offset from top)
    std::string formattedList;
    std::size_t index = 0;

    for (const auto & item : groceryList._gList_vector) // Assuming _gList_vector is the primary container
    {
      formattedList += std::format("{:>3}. {}\n", index++, item);
    }

    return formatter<string>::format(formattedList, ctx);
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }
};















/***********************************************************************************************************************************
** (C) Copyright 2025 by Thomas Bettens. All Rights Reserved.
**
** DISCLAIMER: The participating authors at California State University's Computer Science Department have used their best efforts
** in preparing this code. These efforts include the development, research, and testing of the theories and programs to determine
** their effectiveness. The authors make no warranty of any kind, expressed or implied, with regard to these programs or to the
** documentation contained within. The authors shall not be liable in any event for incidental or consequential damages in
** connection with, or arising out of, the furnishing, performance, or use of these libraries and programs.  Distribution without
** written consent from the authors is prohibited.
***********************************************************************************************************************************/

/**************************************************
** Last modified:  09-AUG-2025
** Last Verified:  09-AUG-2025
** Verified with:  MS Visual Studio 2022 Version 17.14.9,  Compiler Version 19.44.35213 (/std:c++latest)
**                 GCC version 15.1.0 (-std=c++23 )
**                 Clang version 21.0.0 (-std=c++23 -stdlib=libc++)
***************************************************/
