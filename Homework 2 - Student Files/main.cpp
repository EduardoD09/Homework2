import std;

import GroceryItem;
import GroceryList;




namespace
{
  void basicScenario()
  {
    // Let's start a grocery list
    GroceryList thingsToBuy = { { "milk"     },
                                { "hot dogs" },
                                { "eggs"     },
                                { "bread"    } };

    // Changed my mind, I want to make sure I can get eggs before running out of money so I'm going to move that to the top of my list
    thingsToBuy.moveToTop( { "eggs" } );

    // Let's see what's on the list so far
    std::cout << "My Grocery List" << thingsToBuy << "\n\n";



    // Hmm ..., no.  Need to add a few more things
    thingsToBuy += { { "apples"  },
                     { "bananas" } };




    // My roommate also has a grocery list
    GroceryList roommatesList = { { "potato chips", "Frito Lays" },
                                  { "potato chips", "Ruffles"    },
                                  { "beer",         "Bud Lite"   },
                                  { "eggs"                       },
                                  { "pretzels"                   } };

    std::cout << std::format( "My roommate's Grocery List{}\n\n", roommatesList );

    // Let's combine the lists (if different) and go shopping
    if( thingsToBuy != roommatesList ) thingsToBuy += roommatesList;


    // Oops, forgot butter.  Let's add that right before bread.
    thingsToBuy.insert( { "butter", "Lakes 'Ole" }, thingsToBuy.find( { "bread" } ) );

    // And beer, really?  You should be studying!
    thingsToBuy.remove( { "beer", "Bud Lite" } );


    // Now let's see what's on the list
    std::print( std::cout, "Combined Grocery Lists{}\n\n", thingsToBuy );



    // Did you get it right?
    //
    // I could construct "expectedResults" with the list of grocery items as above, but I want to exercise GroceryList's extraction
    // operator.  To do that, I could:
    //   1) read the list of grocery items from standard input and type the data at the keyboard, but that is time consuming and
    //      error prone.  That's easily handled by creating a text file with grocery item data then redirecting that text file to
    //      standard input at the command line when launching the program.  But then I would have to separately maintain that file
    //      and include it in the set of student files.  More importantly, that would prevent you from doing that in the TO-DO
    //      section below.
    //   2) open a text file directly using either command line arguments that supply the file's path and name, or hard coding the
    //      file's path and name.  But that would require using (and understanding) the standard's ifstream interface, which is easy
    //      enough given sufficient time, but I don't want to go down that rabbit hole in this course.
    //   3) create an in-memory text file (well, more accurately, an in-memory input stream) and read from there.  This allows me to
    //      exercise the extraction operator while avoiding the perils described in options 1) and 2) above.
    // So, as a design decision, let's chose option 3), create an in-memory input stream and read from there.
    //
    //                                            UPC | Brand Name   | Product Name   | Price
    //                                            ----+--------------+----------------+--------
    std::istringstream expectedResultsStream( R"( "",   "",            "eggs",          0.0
                                                  "",   "",            "milk",          0.0
                                                  "",   "",            "hot dogs",      0.0
                                                  "",   "Lakes 'Ole",  "butter",        0.0
                                                  "",   "",            "bread",         0.0
                                                  "",   "",            "apples",        0.0
                                                  "",   "",            "bananas",       0.0
                                                  "",   "Frito Lays",  "potato chips",  0.0
                                                  "",   "Ruffles",     "potato chips",  0.0
                                                  "",   "",            "pretzels",      0.0 )"   // multi-line raw string literal of grocery items
                                               );

    GroceryList expectedResults;
    expectedResultsStream >> expectedResults;

    std::print( std::cout, "\nExpected results:{}\n\n"
                           "\nActual results:  {}\n\n"
                           "\nTest results:    {}\n",

                           expectedResults,
                           thingsToBuy,
                           thingsToBuy != expectedResults ? "FAIL" : "PASS" );
  }
}




int main()
{
  try
  {
    basicScenario();


    ///////////////////////// TO-DO (1) //////////////////////////////
     /// Create, manipulate, and display your own GroceryList object here.  Not looking for anything specific but don't just repeat
     /// what I've already done above.  Be imaginative and create your own story.  Maybe you're restocking a depleted food bank, or
     /// preparing for a holiday meal, or catering a banquette, or planning an all night study session, or ...  You *must* use all
     /// the functions of the GroceryList interface, including the insertion, extraction, and relational operators.  Try inserting
     /// grocery items from both the top and the bottom of the lists using the enumerated position values TOP and BOTTOM as well as
     /// indexed offsets.  Remove grocery items from the top, middle, and bottom.  Create, concatenate, rearrange, and compare
     /// several (more than two) lists. Have some fun with it!  The purpose is to show me you, as a GroceryList class consumer
     /// (i.e., the client) understand how to *use* the GroceryList.

     
// Let's plan a holiday meal for Thanksgiving
GroceryList mainCourse = { { "turkey", "Organic" }, 
                           { "stuffing" } };
mainCourse.insert({ "mashed potatoes" }, GroceryList::TOP);
mainCourse.insert({ "green beans" }, 2); // insert at index 2

GroceryList desserts = { { "pumpkin pie" }, 
                         { "apple pie" } };
desserts.insert({ "whipped cream" }, GroceryList::BOTTOM);

GroceryList beverages = { { "cranberry juice" }, 
                          { "apple cider" } };

std::cout << "Main Course:" << mainCourse << "\n\n";
std::cout << "Desserts:" << desserts << "\n\n";
std::cout << "Beverages:" << beverages << "\n\n";

// Combine the lists
GroceryList holidayList = mainCourse;
holidayList += desserts;
holidayList += beverages;

std::cout << "Holiday List:" << holidayList << "\n\n";

// Remove an item from the middle
holidayList.remove({ "stuffing" });

std::cout << "Updated Holiday List:" << holidayList << "\n\n";

// Compare lists
GroceryList shoppingList = holidayList;
std::cout << "Are holidayList and shoppingList equal? " << (holidayList == shoppingList ? "Yes" : "No") << "\n\n";

// Create an in-memory input stream to test extraction operator
std::istringstream holidayListStream(R"( "",   "Organic",  "turkey",          0.0
                                          "",   "",         "mashed potatoes", 0.0
                                          "",   "",         "green beans",    0.0
                                          "",   "",         "pumpkin pie",    0.0
                                          "",   "",         "apple pie",     0.0
                                          "",   "",         "whipped cream",  0.0
                                          "",   "",         "cranberry juice",0.0
                                          "",   "",         "apple cider",    0.0
                                        )");

GroceryList extractedList;
holidayListStream >> extractedList;

std::cout << "Extracted List:" << extractedList << "\n\n";
std::cout << "Are holidayList and extractedList equal? " << (holidayList == extractedList ? "Yes" : "No") << "\n\n";
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }

  catch( const std::exception & ex )
  {
    std::print( std::cerr, "Fatal Error:  unhanded exception {:?}\n"
                           "{}\n",
                           typeid( ex ).name(),
                           ex.what() );
  }
}
