// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <algorithm>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return affiliations_.size();
}

void Datastructures::clear_all()
{
    affiliations_.clear();
    publications_.clear();
    sorted_affiliations_by_name_.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> all_affiliations;
    for (const auto& affiliation : affiliations_) { //O(N)
        all_affiliations.push_back(affiliation.first);
    }
    return all_affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name& name, Coord xy)
{
    if (affiliations_.find(id) != affiliations_.end()) { //O(1)
        return false;
    }

    Affiliation new_affiliation = {id, name, xy};
    affiliations_.emplace(id, new_affiliation); //O(1)
    sorted_affiliations_by_name_.emplace(name, id); //O(Nlog(N))
    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto it = affiliations_.find(id); //O(1)
    if( it != affiliations_.end()){
        return it->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
     auto it = affiliations_.find(id); //O(1)
    if( it != affiliations_.end()){
        return it->second.xy;
    }
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::vector<AffiliationID> ids;
    for (const auto& affiliation : sorted_affiliations_by_name_) { // O(N)
        ids.push_back(affiliation.first);
    }
    return ids;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> result;

    return result;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    for (const auto& affiliation : affiliations_) { // O(N)
        if (affiliation.second.xy == xy) {
            return affiliation.first;
        }
    }
    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = affiliations_.find(id); // O(1)
    if (it != affiliations_.end()) {
        it->second.xy = newcoord;
        return true;
    }
    return false;
}

bool Datastructures::add_publication(PublicationID id, const Name& name, Year year, const std::vector<AffiliationID>& affiliations)
{
    if (publications_.find(id) != publications_.end()) { // O(1)
        return false;  // Publication with this ID already exists
    }

    Publication new_publication = {id, name, year, affiliations};
    publications_.emplace(id, new_publication); // O(1)
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> all_publications;
    for (const auto& publication : publications_) { // O(N)
        all_publications.push_back(publication.first);
    }
    return all_publications;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end()) {
        return it->second.year;
    }
    return NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end()) {
        return it->second.affiliations;
    }
    return {NO_AFFILIATION};
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto it = publications_.find(id); // O(1)
    auto parent_it = publications_.find(parentid); // O(1)

    if (it != publications_.end() && parent_it != publications_.end()) {
        it->second.parent = &(parent_it->second);
        parent_it->second.children.push_back(&(it->second));
        return true;
    }

    return false;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end()) {
        std::vector<PublicationID> direct_references;
        for (const auto& child : it->second.children) {
            direct_references.push_back(child->id);
        }
        return direct_references;
    }
    return {NO_PUBLICATION};
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto aff_it = affiliations_.find(affiliationid); // O(1)
    auto pub_it = publications_.find(publicationid); // O(1)

    if (aff_it != affiliations_.end() && pub_it != publications_.end()) {
        pub_it->second.affiliations.push_back(affiliationid);
        return true;
    }

    return false;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> produced_publications;
    for (const auto& publication : publications_) { // O(N)
        if (std::find(publication.second.affiliations.begin(), publication.second.affiliations.end(), id) != publication.second.affiliations.end()) {
            produced_publications.push_back(publication.first);
        }
    }
    return produced_publications;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end() && it->second.parent) {
        return it->second.parent->id;
    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    auto aff_it = affiliations_.find(affiliationid); // O(1)
    if (aff_it != affiliations_.end()) {
        std::vector<std::pair<Year, PublicationID>> result;

        for (const auto& publication : publications_) { // O(N)
            if (std::find(publication.second.affiliations.begin(), publication.second.affiliations.end(), affiliationid) != publication.second.affiliations.end() &&
                publication.second.year >= year) {
                result.push_back({publication.second.year, publication.first});
            }
        }

        // Sort by year, then by ID
        std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return (a.first != b.first) ? a.first < b.first : a.second < b.second;
        });

        return result;
    }

    return {{NO_YEAR, NO_PUBLICATION}};
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id) 
{
    auto it = publications_.find(id); // O(1)
    if (it != publications_.end()) {
        std::vector<PublicationID> referenced_chain;
        std::function<void(const Publication&)> getReferences = [&](const Publication& publication) {
            referenced_chain.push_back(publication.id);
            for (const auto& child : publication.children) {
                getReferences(*child);
            }
        };

        // Check for direct references
        for (const auto& reference : it->second.references) {
            referenced_chain.push_back(reference);
        }

        // Check for indirect references
        if (it->second.parent) {
            getReferences(*(it->second.parent));
        }

        return referenced_chain;
    }
    return {NO_PUBLICATION};
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_all_references()");
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_affiliation()");
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}

bool Datastructures::remove_publication(PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_publication()");
}


