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


#include "fvOptions.H"
#include "simpleControl.H"

#include "fvCFD.H"
#include "IFstream.H"
#include "OFstream.H"
#include "IOmanip.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"

#include "addCheckCaseOptions.H"
 

volScalarField T
    (
       IOobject
       (
       "T",
       runTime.timeName(),
       mesh,
       IOobject::MUST_READ,
       IOobject::AUTO_WRITE
       ),
       mesh
    );

volScalarField DT
(
    IOobject
    (
        "DT",
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
DT = dimensionedScalar("DT", dimViscosity, transportProperties);


volScalarField k
(
    IOobject
    (
        "k",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("k", dimless/(dimTime * dimTemperature), -2)
);

volScalarField G
(
    IOobject
    (
        "G",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("G", dimViscosity, 1)
);


  while(runTime.run()) // цикл по времени
    {
      runTime++;
      Info<< "Time = " << runTime.timeName() << nl << endl;
      
      //scalar CFL = max(G * DT / deltaX);
      //Info<< "CFL = "<< CFL << endl;

      fvScalarMatrix TEqn
      (
	  fvm::ddt(T) -  fvm::laplacian(G, T) == fvm::Sp(k * T, T)
      );

      TEqn.solve();

      //T.correctBoundaryConditions();

      runTime.write();
    }
    return 0;
}


// ************************************************************************* //
