// By: Gonçalo Leão

#include "VertexEdge.h"

/************************* Station  **************************/

Station::Station(int id): id(id) {}

/*
 * Auxiliary function to add an outgoing Segment to a Station (this),
 * with a given destination StatioFn (d) and Segment weight (w).
 */
Segment * Station::addSegment(Station *d, double w, int serv) {
    auto newSegment = new Segment(this, d, w, serv);
    adj.push_back(newSegment);
    d->incoming.push_back(newSegment);
    return newSegment;
}

/*
 * Auxiliary function to remove an outgoing Segment (with a given destination (d))
 * from a Station (this).
 * Returns true if successful, and false if such Segment does not exist.
 */
bool Station::removeSegment(int destID) {
    bool removedSegment = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Segment *Segment = *it;
        Station *dest = Segment->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding Segment from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete Segment;
            removedSegment = true; // allows for multiple Segments to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedSegment;
}

bool Station::operator<(Station & Station) const {
    return this->dist < Station.dist;
}

int Station::getId() const {
    return this->id;
}

std::vector<Segment*> Station::getAdj() const {
    return this->adj;
}

bool Station::isVisited() const {
    return this->visited;
}

bool Station::isProcessing() const {
    return this->processing;
}

unsigned int Station::getIndegree() const {
    return this->indegree;
}

double Station::getDist() const {
    return this->dist;
}

Segment *Station::getPath() const {
    return this->path;
}

std::vector<Segment *> Station::getIncoming() const {
    return this->incoming;
}

void Station::setId(int id) {
    this->id = id;
}

void Station::setVisited(bool visited) {
    this->visited = visited;
}

void Station::setProcesssing(bool processing) {
    this->processing = processing;
}

void Station::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Station::setDist(double dist) {
    this->dist = dist;
}

void Station::setPath(Segment *path) {
    this->path = path;
}

/********************** Segment  ****************************/

Segment::Segment(Station *orig, Station *dest, double w, int service): orig(orig), dest(dest), capacity(w) , service(service){}

Station * Segment::getDest() const {
    return this->dest;
}

double Segment::getCapacity() const {
    return this->capacity;
}

Station * Segment::getOrig() const {
    return this->orig;
}

Segment *Segment::getReverse() const {
    return this->reverse;
}

bool Segment::isSelected() const {
    return this->selected;
}

double Segment::getFlow() const {
    return flow;
}

void Segment::setSelected(bool selected) {
    this->selected = selected;
}

void Segment::setReverse(Segment *reverse) {
    this->reverse = reverse;
}

void Segment::setFlow(double flow) {
    this->flow = flow;
}