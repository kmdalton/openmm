/* -------------------------------------------------------------------------- *
 *                                OpenMMAmoeba                                *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2009 Stanford University and the Authors.      *
 * Authors:                                                                   *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "openmm/Force.h"
#include "openmm/OpenMMException.h"
#include "openmm/AmoebaMultipoleForce.h"
#include "openmm/internal/AmoebaMultipoleForceImpl.h"

using namespace OpenMM;
using std::string;
using std::vector;

AmoebaMultipoleForce::AmoebaMultipoleForce() : nonbondedMethod(NoCutoff), pmeBSplineOrder(5), cutoffDistance(1.0), ewaldErrorTol(1e-4), mutualInducedIterationMethod(SOR), mutualInducedMaxIterations(60),
                                               mutualInducedTargetEpsilon(1.0e-05), scalingDistanceCutoff(100.0), electricConstant(138.9354558456) {
}

AmoebaMultipoleForce::AmoebaNonbondedMethod AmoebaMultipoleForce::getNonbondedMethod( void ) const {
    return nonbondedMethod;
}

void AmoebaMultipoleForce::setNonbondedMethod( AmoebaMultipoleForce::AmoebaNonbondedMethod method) {
    nonbondedMethod = method;
}

double AmoebaMultipoleForce::getCutoffDistance( void ) const {
    return cutoffDistance;
}

void AmoebaMultipoleForce::setCutoffDistance(double distance) {
    cutoffDistance = distance;
}

double AmoebaMultipoleForce::getAEwald() const {		 
    return aewald;		 
}		 
		 
void AmoebaMultipoleForce::setAEwald(double inputAewald ) {			 
    aewald = inputAewald;		 
}		 
 
int AmoebaMultipoleForce::getPmeBSplineOrder( void ) const {		 
    return pmeBSplineOrder;		 
}		 
		 
void AmoebaMultipoleForce::setPmeBSplineOrder(int inputBSplineOrder) {			 
    pmeBSplineOrder = inputBSplineOrder;		 
}		 
 
void AmoebaMultipoleForce::getPmeGridDimensions( std::vector<int>& gridDimension ) const {		 
    if( gridDimension.size() < 3 ){
        gridDimension.resize(3);
    }
    if( pmeGridDimension.size() > 2 ){
        gridDimension[0] = pmeGridDimension[0];
        gridDimension[1] = pmeGridDimension[1];
        gridDimension[2] = pmeGridDimension[2];
    } else {
        gridDimension[0] = gridDimension[1] = gridDimension[2] = 0;
    }
    return;
}		 
		 
void AmoebaMultipoleForce::setPmeGridDimensions( const std::vector<int>& gridDimension ) {
    pmeGridDimension.resize(3);
    pmeGridDimension[0] = gridDimension[0];
    pmeGridDimension[1] = gridDimension[1];
    pmeGridDimension[2] = gridDimension[2];
    return;
}		 
 
AmoebaMultipoleForce::MutualInducedIterationMethod AmoebaMultipoleForce::getMutualInducedIterationMethod( void ) const {
    return mutualInducedIterationMethod;
}

void AmoebaMultipoleForce::setMutualInducedIterationMethod( AmoebaMultipoleForce::MutualInducedIterationMethod inputMutualInducedIterationMethod ) {
    mutualInducedIterationMethod = inputMutualInducedIterationMethod;
}

int AmoebaMultipoleForce::getMutualInducedMaxIterations( void ) const {
    return mutualInducedMaxIterations;
}

void AmoebaMultipoleForce::setMutualInducedMaxIterations( int inputMutualInducedMaxIterations ) {
    mutualInducedMaxIterations = inputMutualInducedMaxIterations;
}

double AmoebaMultipoleForce::getMutualInducedTargetEpsilon( void ) const {
    return mutualInducedTargetEpsilon;
}

void AmoebaMultipoleForce::setMutualInducedTargetEpsilon( double inputMutualInducedTargetEpsilon ) {
    mutualInducedTargetEpsilon = inputMutualInducedTargetEpsilon;
}

double AmoebaMultipoleForce::getScalingDistanceCutoff( void ) const {
    return scalingDistanceCutoff;
}

void AmoebaMultipoleForce::setScalingDistanceCutoff( double inputScalingDistanceCutoff ) {
    scalingDistanceCutoff = inputScalingDistanceCutoff;
}

double AmoebaMultipoleForce::getElectricConstant( void ) const {
    return electricConstant;
}

void AmoebaMultipoleForce::setElectricConstant( double inputElectricConstant ) {
    electricConstant = inputElectricConstant;
}

double AmoebaMultipoleForce::getEwaldErrorTolerance() const {
    return ewaldErrorTol;
}

void AmoebaMultipoleForce::setEwaldErrorTolerance(double tol) {
    ewaldErrorTol = tol;
}

int AmoebaMultipoleForce::addParticle( double charge, const std::vector<double>& molecularDipole, const std::vector<double>& molecularQuadrupole, int axisType, 
                                       int multipoleAtomZ, int multipoleAtomX, int multipoleAtomY, double thole, double dampingFactor, double polarity) {
    multipoles.push_back(MultipoleInfo( charge, molecularDipole, molecularQuadrupole,  axisType, multipoleAtomZ,  multipoleAtomX, multipoleAtomY, thole, dampingFactor, polarity));
    return multipoles.size()-1;
}

void AmoebaMultipoleForce::getMultipoleParameters(int index, double& charge, std::vector<double>& molecularDipole, std::vector<double>& molecularQuadrupole, 
                                                  int& axisType, int& multipoleAtomZ, int& multipoleAtomX, int& multipoleAtomY, double& thole, double& dampingFactor, double& polarity ) const {
    charge                      = multipoles[index].charge;

    molecularDipole.resize( 3 );
    molecularDipole[0]          = multipoles[index].molecularDipole[0];
    molecularDipole[1]          = multipoles[index].molecularDipole[1];
    molecularDipole[2]          = multipoles[index].molecularDipole[2];

    molecularQuadrupole.resize( 9 );
    molecularQuadrupole[0]      = multipoles[index].molecularQuadrupole[0];
    molecularQuadrupole[1]      = multipoles[index].molecularQuadrupole[1];
    molecularQuadrupole[2]      = multipoles[index].molecularQuadrupole[2];
    molecularQuadrupole[3]      = multipoles[index].molecularQuadrupole[3];
    molecularQuadrupole[4]      = multipoles[index].molecularQuadrupole[4];
    molecularQuadrupole[5]      = multipoles[index].molecularQuadrupole[5];
    molecularQuadrupole[6]      = multipoles[index].molecularQuadrupole[6];
    molecularQuadrupole[7]      = multipoles[index].molecularQuadrupole[7];
    molecularQuadrupole[8]      = multipoles[index].molecularQuadrupole[8];

    axisType                    = multipoles[index].axisType;
    multipoleAtomZ              = multipoles[index].multipoleAtomZ;
    multipoleAtomX              = multipoles[index].multipoleAtomX;
    multipoleAtomY              = multipoles[index].multipoleAtomY;

    thole                       = multipoles[index].thole;
    dampingFactor               = multipoles[index].dampingFactor;
    polarity                    = multipoles[index].polarity;
}

void AmoebaMultipoleForce::setMultipoleParameters(int index, double charge, const std::vector<double>& molecularDipole, const std::vector<double>& molecularQuadrupole, 
                                                  int axisType, int multipoleAtomZ, int multipoleAtomX, int multipoleAtomY, double thole, double dampingFactor, double polarity ) {

    multipoles[index].charge                      = charge;

    multipoles[index].molecularDipole[0]          = molecularDipole[0];
    multipoles[index].molecularDipole[1]          = molecularDipole[1];
    multipoles[index].molecularDipole[2]          = molecularDipole[2];

    multipoles[index].molecularQuadrupole[0]      = molecularQuadrupole[0];
    multipoles[index].molecularQuadrupole[1]      = molecularQuadrupole[1];
    multipoles[index].molecularQuadrupole[2]      = molecularQuadrupole[2];
    multipoles[index].molecularQuadrupole[3]      = molecularQuadrupole[3];
    multipoles[index].molecularQuadrupole[4]      = molecularQuadrupole[4];
    multipoles[index].molecularQuadrupole[5]      = molecularQuadrupole[5];
    multipoles[index].molecularQuadrupole[6]      = molecularQuadrupole[6];
    multipoles[index].molecularQuadrupole[7]      = molecularQuadrupole[7];
    multipoles[index].molecularQuadrupole[8]      = molecularQuadrupole[8];

    multipoles[index].axisType                    = axisType;
    multipoles[index].multipoleAtomZ              = multipoleAtomZ;
    multipoles[index].multipoleAtomX              = multipoleAtomX;
    multipoles[index].multipoleAtomY              = multipoleAtomY;
    multipoles[index].thole                       = thole;
    multipoles[index].dampingFactor               = dampingFactor;
    multipoles[index].polarity                    = polarity;

}

void AmoebaMultipoleForce::setCovalentMap(int index, CovalentType typeId, const std::vector<int>& covalentAtoms ) {

    std::vector<int>& covalentList = multipoles[index].covalentInfo[typeId];
    covalentList.resize( covalentAtoms.size() );
    for( unsigned int ii = 0; ii < covalentAtoms.size(); ii++ ){
       covalentList[ii] = covalentAtoms[ii];
    }
}

void AmoebaMultipoleForce::getCovalentMap(int index, CovalentType typeId, std::vector<int>& covalentAtoms ) const {

    // load covalent atom index entries for atomId==index and covalentId==typeId into covalentAtoms

    std::vector<int> covalentList = multipoles[index].covalentInfo[typeId];
    covalentAtoms.resize( covalentList.size() );
    for( unsigned int ii = 0; ii < covalentList.size(); ii++ ){
       covalentAtoms[ii] = covalentList[ii];
    }
}

void AmoebaMultipoleForce::getCovalentMaps(int index, std::vector< std::vector<int> >& covalentLists ) const {

    covalentLists.resize( CovalentEnd );
    for( unsigned int jj = 0; jj < CovalentEnd; jj++ ){
        std::vector<int> covalentList = multipoles[index].covalentInfo[jj];
        std::vector<int> covalentAtoms;
        covalentAtoms.resize( covalentList.size() );
        for( unsigned int ii = 0; ii < covalentList.size(); ii++ ){
           covalentAtoms[ii] = covalentList[ii];
        }
        covalentLists[jj] = covalentAtoms;
    }
}

ForceImpl* AmoebaMultipoleForce::createImpl() {
    return new AmoebaMultipoleForceImpl(*this);
}
