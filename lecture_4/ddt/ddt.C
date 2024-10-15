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
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  argList::addOption
    (
        "T0",
	"scalar",
        "initial temperature"
    );
  argList::addOption
    (
        "sigma",
	"scalar",
        "coeff"
    );

#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"

   scalar T0 = 300.0;
   scalar sigma = 1;

 if (args.readIfPresent("T0", T0))
    {
       Info << "T0 = " << T0 << endl;
    }
 if (args.readIfPresent("sigma", sigma))
    {
       Info << "sigma = " << sigma << endl;
    }

 
 volScalarField T                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T", dimTemperature, T0) // начальное размерное значение
     );

 volScalarField T_theory                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T_theory",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T_theory", dimTemperature, T0) // начальное размерное значение
     );

 volScalarField sigma_v                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "sigma",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("sigma", dimless/pow(dimTemperature, 3)/dimTime, sigma) // начальное размерное значение
     );
 
  while(runTime.loop()) // цикл по времени
    {
      Info<< "Time = " << runTime.timeName() << nl << endl;
      
      fvScalarMatrix TEqn
	(
	 fvm::ddt(T)
	 ==
	 sigma_v*pow(T,4)
	 );
      
      TEqn.solve();
      
      runTime.write();
    }
    return 0;
}


// ************************************************************************* //
