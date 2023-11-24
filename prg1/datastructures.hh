// Datastructures.hh
//
// Student name: Hoang Anh Minh
// Student email: minh.hoang@tuni.fi
// Student number: 

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <random>
#include <regex>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <utility>
#include <variant>
#include <bitset>
#include <cassert>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The clear function for unordered_map and map
    // has a constant time complexity as it deallocates the memory used by the containers,
    // and the size of the containers does not affect the time taken for clearing.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function iterates through all elements
    // in the 'affiliations' unordered_map, and for each element, it performs a constant
    // time operation (push_back) to add the AffiliationID to the 'all_affiliations' vector.
    // Therefore, the overall time complexity is linear in the number of affiliations.
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function involves basic operations such as
    // checking if the affiliation ID already exists in the 'affiliations' unordered_map,
    // creating a shared_ptr, and inserting elements into unordered_map and maps, all of
    // which have constant time complexities. The function performs a fixed number of
    // operations regardless of the size of the data structures.
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function performs a constant number of operations
    // regardless of the size of the 'affiliations' unordered_map. The lookup in the unordered_map
    // and the subsequent access to the 'name' member of the affiliated structure are both constant-time
    // operations.
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function performs a constant number of operations
    // regardless of the size of the 'affiliations' unordered_map. The lookup in the unordered_map
    // and the subsequent access to the 'coord' member of the affiliated structure are both constant-time
    // operations.
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function iterates through all elements in the 'affiliations_alphabetically'
    // map, and for each element, it iterates through its associated vector, performing a constant time operation
    // (push_back) for each AffiliationID. Therefore, the overall time complexity is linear in the total number of
    // affiliations.
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function iterates through all elements in the 'affiliations_distance_increasing'
    // map, and for each element, it iterates through its associated vector, performing a constant time operation
    // (push_back) for each AffiliationID. Therefore, the overall time complexity is linear in the total number of
    // affiliations.
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'affiliations_by_coord' unordered_map, which is an average
    // constant time operation. Additionally, the function performs a constant time operation
    // to check if the vector associated with the given coordinate is empty or not.
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves updating the 'coord' member of the
    // affiliated structure, which is a constant time operation. However, the function also includes
    // iterating through the vectors associated with the old and new coordinates, and in the worst case,
    // it might iterate through all affiliations in 'affiliations_distance_increasing' map. Therefore,
    // the overall time complexity is linear in the number of affiliations.
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: The function involves creating a new Publication, adding it to the 'publications'
    // unordered_map, and updating the 'publications' vector for each affiliated structure. The time complexity is
    // proportional to the number of affiliations (m) and the number of publications (k) being added.
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function iterates through all elements in the 'publications'
    // unordered_map and performs a constant-time operation (push_back) for each PublicationID.
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'publications' unordered_map and access to the 'name' member
    // of the Publication structure, both of which are constant-time operations.
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'publications' unordered_map and access to the 'year' member
    // of the Publication structure, both of which are constant-time operations.
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'publications' unordered_map and access to the 'affiliations' member
    // of the Publication structure, both of which are constant-time operations.
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including lookups in the 'publications' unordered_map for both the 'id' and 'parentid'
    // and updating the 'parent' member and the 'references' vector of the Publication structures,
    // all of which are constant-time operations.
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'publications' unordered_map and access to the 'references' member
    // of the Publication structure, both of which are constant-time operations.
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including lookups in the 'affiliations' and 'publications' unordered_maps,
    // and updating the 'affiliations' and 'publications' vectors of the respective structures,
    // all of which are constant-time operations.
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'affiliations' unordered_map and access to the 'publications' member
    // of the Affiliation structure, both of which are constant-time operations.
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves a constant number of operations,
    // including a lookup in the 'publications' unordered_map and access to the 'parent' member
    // of the Publication structure, both of which are constant-time operations.
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function involves iterating through the 'publications' vector
    // of the specified affiliation, and for each publication, it performs constant-time operations,
    // including lookups in the 'publications' unordered_map and access to the 'year' member of the
    // Publication structure.
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: The function iterates through the chain of referenced publications,
    // where the height of the chain is h. For each publication, it performs constant-time operations,
    // including lookups in the 'publications' unordered_map and access to the 'parent' member of the
    // Publication structure. Sorting the vector at the end adds a logarithmic factor to the overall complexity.
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);


private:
    PublicationID NO_PARENT = -1;
    struct Affiliation {
        Name name;
        Coord coord;
        std::vector<PublicationID> publications;
    };
    struct Publication{
        Name name;
        Year year;
        std::vector<AffiliationID> affiliations;
        std::vector<PublicationID> references;
        PublicationID parent;
    };
    std::unordered_map<AffiliationID, std::shared_ptr<Affiliation>> affiliations;
    std::unordered_map<PublicationID, std::shared_ptr<Publication>> publications;
    std::unordered_map<Coord, std::vector<AffiliationID>, CoordHash> affiliations_by_coord;
    std::map<Distance, std::vector<AffiliationID>> affiliations_distance_increasing;
    std::map<Name, std::vector<AffiliationID>> affiliations_alphabetically;
};

#endif // DATASTRUCTURES_HH
