#include "arczn.h"
#include "petri.h"

uint64_t	GCW_Linear(const t_cluster *cluster) {
    return (cluster->ratioWeight * cluster->ht->nItems);
}

uint64_t	GCW_LinearWeight(const t_cluster *cluster) {
    return (cluster->ratioWeight * fTree_getTotalweight(&cluster->weightPoints));
}