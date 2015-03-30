#ifndef IF97COMMON_H
#define IF97COMMON_H

enum I97parameters {IF97_DMASS, IF97_HMASS, IF97_T, IF97_P, IF97_SMASS, IF97_UMASS, IF97_CPMASS, IF97_CVMASS, IF97_W};
struct RegionIdealElement
{
    int J; ///< The first index
    double n; ///< The leading numerical constant
};
struct RegionResidualElement
{
    int I, ///< The first index
        J; ///< The second index
    double n; ///< The leading numerical constant
};

#endif
