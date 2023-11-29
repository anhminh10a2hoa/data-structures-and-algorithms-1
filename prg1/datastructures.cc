// Datastructures.cc
//
// Student name: Hoang Anh Minh
// Student email: minh.hoang@tuni.fi
// Student number: 152103143

#include "datastructures.hh"

#include <random>

#include <cmath>

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
    return affiliations.size();
}

void Datastructures::clear_all() 
{
    affiliations.clear();
    publications.clear();
    affiliations_by_coord.clear();
    affiliations_distance_increasing.clear();
    affiliations_alphabetically.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations() 
{
    std::vector<AffiliationID> all_affiliations;
    for (auto it = affiliations.begin(); it != affiliations.end(); ++it) {
        all_affiliations.push_back(it->first);
    }
    return all_affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy) {
    if (affiliations.find(id) != affiliations.end()) {
        return false;
    }
    std::shared_ptr<Affiliation> new_affiliation = std::make_shared<Affiliation>();
    new_affiliation->name = name;
    new_affiliation->coord = xy;
    affiliations[id] = new_affiliation;
    affiliations_by_coord[xy].push_back(id);
    affiliations_distance_increasing[std::sqrt(xy.x*xy.x + xy.y*xy.y)].push_back(id);
    affiliations_alphabetically[name].push_back(id);
    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id) 
{
    if (affiliations.find(id) == affiliations.end()) {
        return NO_NAME;
    }
    return affiliations[id]->name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id) 
{
    if (affiliations.find(id) == affiliations.end()) {
        return NO_COORD;
    }
    return affiliations[id]->coord;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically() 
{
    std::vector<AffiliationID> all_affiliations;
    for (auto it = affiliations_alphabetically.begin(); it != affiliations_alphabetically.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            all_affiliations.push_back(*it2);
        }
    }
    return all_affiliations;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> all_affiliations;
    for (auto it = affiliations_distance_increasing.begin(); it != affiliations_distance_increasing.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            all_affiliations.push_back(*it2);
        }
    }
    return all_affiliations;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy) {
    auto it = affiliations_by_coord.find(xy);
    if (it != affiliations_by_coord.end() && !it->second.empty()) {
        return it->second.front();
    }
    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord) 
{
    if (affiliations.find(id) == affiliations.end()) {
        return false;
    }
    Coord old_coord = affiliations[id]->coord;
    affiliations[id]->coord = newcoord;
    for (auto it = affiliations_by_coord[old_coord].begin(); it != affiliations_by_coord[old_coord].end(); ++it) {
        if (*it == id) {
            affiliations_by_coord[old_coord].erase(it);
            break;
        }
    }
    affiliations_by_coord[newcoord].push_back(id);
    for (auto it = affiliations_distance_increasing.begin(); it != affiliations_distance_increasing.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == id) {
                it->second.erase(it2);
                break;
            }
        }
    }
    affiliations_distance_increasing[std::sqrt(newcoord.x*newcoord.x + newcoord.y*newcoord.y)].push_back(id);
    return true;
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    if (publications.find(id) != publications.end()) {
        return false;
    }
    std::shared_ptr<Publication> new_publication = std::make_shared<Publication>();
    new_publication->name = name;
    new_publication->year = year;
    new_publication->affiliations = affiliations;
    new_publication->parent = NO_PARENT;
    publications[id] = new_publication;
    for (auto it = affiliations.begin(); it != affiliations.end(); ++it) {
        if (this->affiliations.find(*it) != this->affiliations.end()) {
            this->affiliations[*it]->publications.push_back(id);
        }
    }
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> all_publications;
    for (auto it = publications.begin(); it != publications.end(); ++it) {
        all_publications.push_back(it->first);
    }
    return all_publications;
}

Name Datastructures::get_publication_name(PublicationID id) 
{
    if (publications.find(id) == publications.end()) {
        return NO_NAME;
    }
    return publications[id]->name;
}

Year Datastructures::get_publication_year(PublicationID id) 
{
    if (publications.find(id) == publications.end()) {
        return NO_YEAR;
    }
    return publications[id]->year;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id) 
{
    if (publications.find(id) == publications.end()) {
        return {NO_AFFILIATION};
    }
    return publications[id]->affiliations;
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid) 
{
    if (publications.find(id) == publications.end() || publications.find(parentid) == publications.end()) {
        return false;
    }
    publications[id]->parent = parentid;
    publications[parentid]->references.push_back(id);
    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    if (publications.find(id) == publications.end()) {
        return {NO_PUBLICATION};
    }
    return publications[id]->references;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    if (affiliations.find(affiliationid) == affiliations.end() || publications.find(publicationid) == publications.end()) {
        return false;
    }
    publications[publicationid]->affiliations.push_back(affiliationid);
    affiliations[affiliationid]->publications.push_back(publicationid);
    return true;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id) 
{
    if (affiliations.find(id) == affiliations.end()) {
        return {NO_PUBLICATION};
    }
    return affiliations[id]->publications;
}

PublicationID Datastructures::get_parent(PublicationID id) 
{
    if (publications.find(id) == publications.end()) {
        return NO_PARENT;
    }
    return publications[id]->parent;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year) 
{
    std::vector<std::pair<Year, PublicationID> > publications_after;
    if (affiliations.find(affiliationid) == affiliations.end()) {
        return publications_after;
    }
    for (auto it = affiliations[affiliationid]->publications.begin(); it != affiliations[affiliationid]->publications.end(); ++it) {
        if (publications.find(*it) != publications.end() && publications[*it]->year >= year) {
            publications_after.push_back(std::make_pair(publications[*it]->year, *it));
        }
    }
    return publications_after;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> referenced_by_chain;
    PublicationID temp_id = id;

    if (publications.find(id) == publications.end()) {
        return {NO_PUBLICATION};
    }

    while (temp_id != NO_PARENT) {
        if(temp_id != id) {
            referenced_by_chain.push_back(temp_id);
        }
        if(publications.find(temp_id) != publications.end()) {
            temp_id = publications[temp_id]->parent;
        } else {
            break;
        }
    }

    std::sort(referenced_by_chain.begin(), referenced_by_chain.end(), [](PublicationID id1, PublicationID id2) {
        return id1 < id2;
    });

    return referenced_by_chain;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id) 
{
    std::vector<PublicationID> all_references;
    if (publications.find(id) == publications.end()) {
        return {NO_PUBLICATION};
    }
    std::vector<PublicationID> direct_references = publications[id]->references;
    for (auto it = direct_references.begin(); it != direct_references.end(); ++it) {
        std::vector<PublicationID> indirect_references = get_all_references(*it);
        all_references.insert(all_references.end(), indirect_references.begin(), indirect_references.end());
    }
    all_references.insert(all_references.end(), direct_references.begin(), direct_references.end());
    return all_references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy) 
{
    std::vector<AffiliationID> closest_affiliations;
    std::vector<AffiliationID> all_affiliations;
    for (auto it = affiliations_by_coord.begin(); it != affiliations_by_coord.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            all_affiliations.push_back(*it2);
        }
    }
    std::sort(all_affiliations.begin(), all_affiliations.end(), [this, xy](AffiliationID id1, AffiliationID id2) {
        return std::sqrt(std::pow(affiliations[id1]->coord.x - xy.x, 2) + std::pow(affiliations[id1]->coord.y - xy.y, 2)) < std::sqrt(std::pow(affiliations[id2]->coord.x - xy.x, 2) + std::pow(affiliations[id2]->coord.y - xy.y, 2));
    });
    if (all_affiliations.size() > 3) {
        closest_affiliations.push_back(all_affiliations[0]);
        closest_affiliations.push_back(all_affiliations[1]);
        closest_affiliations.push_back(all_affiliations[2]);
    } else {
        closest_affiliations = all_affiliations;
    }
    return closest_affiliations;
}

bool Datastructures::remove_affiliation(AffiliationID id) 
{
    if (affiliations.find(id) == affiliations.end()) {
        return false;
    }
    for (auto it = affiliations[id]->publications.begin(); it != affiliations[id]->publications.end(); ++it) {
        for (auto it2 = publications[*it]->affiliations.begin(); it2 != publications[*it]->affiliations.end(); ++it2) {
            if (*it2 == id) {
                publications[*it]->affiliations.erase(it2);
                break;
            }
        }
    }
    for (auto it = affiliations_by_coord.begin(); it != affiliations_by_coord.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == id) {
                it->second.erase(it2);
                break;
            }
        }
    }
    for (auto it = affiliations_distance_increasing.begin(); it != affiliations_distance_increasing.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == id) {
                it->second.erase(it2);
                break;
            }
        }
    }
    for (auto it = affiliations_alphabetically.begin(); it != affiliations_alphabetically.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == id) {
                it->second.erase(it2);
                break;
            }
        }
    }
    affiliations.erase(id);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2) 
{
    if (publications.find(id1) == publications.end() || publications.find(id2) == publications.end()) {
        return NO_PUBLICATION;
    }
    std::vector<PublicationID> id1_chain = get_referenced_by_chain(id1);
    std::vector<PublicationID> id2_chain = get_referenced_by_chain(id2);
    for (auto it = id1_chain.begin(); it != id1_chain.end(); ++it) {
        for (auto it2 = id2_chain.begin(); it2 != id2_chain.end(); ++it2) {
            if (*it == *it2) {
                return *it;
            }
        }
    }
    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid) 
{
    auto publication = publications.find(publicationid);
    if (publication == publications.end()) {
        return false;
    }

    auto& target = publication->second;

    // Remove references to the target publication
    for (auto refID : target->references) {
        auto refPublication = publications.find(refID);
        if (refPublication != publications.end()) {
            refPublication->second->parent = NO_PARENT;
        }
    }

    // Remove the target publication from its affiliations
    for (auto affID : target->affiliations) {
        auto aff = affiliations.find(affID);
        if (aff != affiliations.end()) {
            auto& publications = aff->second->publications;
            publications.erase(std::remove(publications.begin(), publications.end(), publicationid), publications.end());
        }
    }

    // Remove the publication from the data structures
    publications.erase(publicationid);

    return true;
}


