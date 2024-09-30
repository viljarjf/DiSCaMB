#ifndef _DISCAMB_CRYSTALSTRUCTURE_SPACEGROUP_HPP_
#define _DISCAMB_CRYSTALSTRUCTURE_SPACEGROUP_HPP_

#include "SpaceGroupOperation.h"

#include <vector>
#include <iosfwd>
#include <iostream>

namespace discamb {

/**
 * \addtogroup CrystalStructure
 * @{
 */


/** \brief Container for space group operations forming space group. */

class SpaceGroup{
public:
    SpaceGroup();
    ~SpaceGroup();

    /** 
    Defines space group. It is not tested if the provided operations correspond to any space group.
    \param operations symmetry operations required to generate all the atoms in
    the unit cell. It is analogues to list of symmetry operations used in CIF file.
    E.g. for C 1 2/c 1 it would be:
    <pre>
    x, y, z               -x, y, 1/2-z       -x, -y, -z                x, -y, 1/2 + z
    x+1/2, y+1/2, z+1/2   -x+1/2, y+1/2, - z   -x+1/2, -y+1/2, -z+1/2    x + 1/2, -y + 1/2, z  </pre>
    */
    void set(const std::vector<SpaceGroupOperation> &operations);

    /**
    Defines space group.  It is not tested if the provided operations correspond to any space group. 
    \param operations symmetry operations required to generate all the atoms in
    the unit cell except of those which can be generated by applying
    inversion operation and lattice centering translations to the operations in the set provided.
    E.g. for C&nbsp;1&nbsp;2/c&nbsp;1 it would be two operations:
    (1) any of the two: <pre> x, y, z     -x, -y, -z </pre> (2) and any of the two: <pre>-x, y, 1/2 - z     x,-y,1/2+z</pre>

    \param centering character defining centering - one of the following: A, B, C, I, F, R, H. In the case of
    rhombohedral lattice obverse setting is assumed. Use an alternative version of the method for reverse setting - 
    set(const std::vector<SpaceGroupOperation>&,char,bool).

    \param inversion_center flag indicating if an inversion center is present. If the inversion center is not located at the origin
    an alternative version of the method should be used which allows to specify inversion center location - 
    set(const std::vector<SpaceGroupOperation>&,char,bool).
    */
    void set(const std::vector<SpaceGroupOperation> &operations,
             char centering, bool inversion_center);
    
    /**
    Defines space group. Similar to  SpaceGroup::set(const std::vector<SpaceGroupOperation> &,char,bool) 
    but requires two more parameters - location of the inversion center and explicit specification 
    if the lattice is obverse (meaningful only for rhombohedral lattice)
    */
    
    void set(const std::vector<SpaceGroupOperation> &operations,
             char centering,
             bool obverse,
             bool inversion_center,
             const Vector3<CrystallographicRational> &inv_center_translation);

    /** Corresponds to number of general position points.
    */

    int nSymmetryOperations() const;

    /**
       Number of symmetry operations corresponding to general position points 
       without those which are related by inversion center and lattice centering.
       Also a number of symmetry operations provided as argument to 
       SpaceGroup::set(const std::vector<SpaceGroupOperation> &,char,bool)
    */
    int nSymmetryOperationsInSubset() const;

    /** Specifies if group is centrosymmetric.*/

    bool isCentrosymmetric() const;

    /** Translation operation associated with inversion operation. I.e. \f$ \mathbf{t} \f$ in \f$ \{\bar{\mathbf{1}}|\mathbf{t}\} \f$.*/
    void inversionCenterTranslation(Vector3<CrystallographicRational> &translation) const;
    /** Returns centering symbol (A, B, C, I, F, R, H) and in the case of rhombohedral lattice specifies setting is obverse. */
    char centering(bool &obverse) const;
    /** Returns true in the case of obverse setting of rhombohedral lattice. For the other lattices the result undefined.*/
    bool obverseSetting() const;
    /** Returns number of lattice nodes per unit cell.*/
    int nCenteringNodes() const;
    /** Returns i-th symmetry operation.*/
    const SpaceGroupOperation &getSpaceGroupOperation(int index) const;
    /** Returns space group operation. The operations are grouped into subsets indexed with parameters centering_node and inversion.  
    Some refinement programs require user provided list of symmetry operations corresponding to general position points without those 
    which can be generated by applying centering translations and inversion center. Each of the subsets corresponds to such a set. 
    The division and order of the symmetry operations into subsets may depend on input. The group with parameters centering_node 
    and inversion equal 0 contains the identity element.

    \param centering_node index of centering node ranging from 0 to number of nodes per unit cell
    \param inversion if the group has inversion center it can be either 0 or 1, in the case of 0 the symmetry operations does 
    not change chirality, for groups without inversion center only value 0 is valid
    \param i index of the symmetry operation in subset
    */

    const SpaceGroupOperation &getSpaceGroupOperation(int centering_node,int inversion,int i) const;
    
    /** Prints out information about the space group into output_stream. */
    void show_info(std::ostream &output_stream = std::cout) const;

    /** Returns lattice centering for given set of centering related translations.*/ 
    static char latticeCentering(const std::vector<Vector3<CrystallographicRational> > &centeringTranslations, bool &obverse);
    
    /** Assigns parameter centeringTranslations to vector of translations identified by parameter centering,
        in the case of rhombohedral group it possible to specify if it is obverse or reverse with the parameter 'obverse'*/
    static void centeringTranslations(char centering, std::vector<Vector3<CrystallographicRational> > &centeringTranslations, bool obverse=true);
private:
    // [translation][inv][operation]
    std::vector<std::vector<std::vector<SpaceGroupOperation> > > mOperations;
    std::vector<SpaceGroupOperation> mOperationsPlain;
    bool mIsCentrosymmetric;
    char mCentering;
    bool mObverse;
    std::vector<Vector3<CrystallographicRational> > mCenteringTranslations;
    Vector3<CrystallographicRational> mInversionCenterTranslation;

    /**
    add integer to each component of translation vector so the component is in the (0,1) range
    */
    static void moveTo01(Vector3<CrystallographicRational> &translation);
    void setPlainSpaceGroupOperations();
    static void removeCenteringTranslations(std::vector<Vector3<CrystallographicRational> > &translations, char centering, bool obverse);
    
};

/**@}*/

}// namespace discamb





#endif /*_DISCAMB_CRYSTALSTRUCTURE_SPACEGROUP_HPP_*/