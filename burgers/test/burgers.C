/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    class Field OF example


\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "IFstream.H"
#include "OFstream.H"
#include "IOmanip.H"
#include "fvOptions.H"
#include "simpleControl.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include "addCheckCaseOptions.H"
#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"

simpleControl simple(mesh);


volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField nu
(
    IOobject
    (
        "nu",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar(dimViscosity, Zero)
);

IOdictionary transportProperties
(
    IOobject
    (
    "transportProperties",
    runTime.constant(),
    mesh,
    IOobject::MUST_READ,
    IOobject::NO_WRITE
    )
);

nu = dimensionedScalar("nu", dimViscosity, transportProperties);

#include "createPhi.H"
#include "CourantNo.H"

while(simple.loop())
    {

      Info<< "Time = " << runTime.timeName() << nl << endl;
      
      while(simple.correctNonOrthogonal()){
      	fvVectorMatrix UEqn
          (
	    fvm::ddt(U) + fvm::div(phi, U) == fvm::laplacian(nu, U)
      	  );
      UEqn.relax();
      UEqn.solve();
      U.correctBoundaryConditions();
      phi = (fvc::interpolate(U) & mesh.Sf());
      runTime.write();
      }
    }
    return 0;
}


// ************************************************************************* //
